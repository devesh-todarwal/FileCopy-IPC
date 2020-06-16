#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#define mem_size 50

int main(int args_main, char* arg_v[]) 
{
    int file_index[2];

    pid_t child_id;

    char Buffer_read[mem_size];
    //stores the data copied from a file before transferring to destination file

    pipe(file_index);

    //file_index is used to return two file descriptors referring to the ends of the pipe where:
    //0 = Read End of Pipe
    //1 = Write End of Pipe 

    if(args_main != 3) 
    {
        printf("ERROR: Need exactly 2 parameters.\n");
        exit(1);
    }
    int Source_File = open(arg_v[1], 0);
    int Dest_File = open(arg_v[2], O_RDWR|O_CREAT|O_APPEND, 0666);
    if (Source_File == -1 || Dest_File == -1) 
    {
        printf("Error in opening files\n");
        exit(1);
    }
    
    //forking a child process to start reading from the input source file

    child_id = fork();
    if(child_id<0)
        printf("Fork Unsuccesful!");

    if (child_id == 0) 
    {
        close(file_index[1]);
	    while (read(file_index[0], Buffer_read, sizeof(Buffer_read)) > 0) 
	    {
		    write(Dest_File, Buffer_read, strlen(Buffer_read) - 1);
        }
        close(file_index[0]);
        close(Dest_File);
    }
    else
    // parent executing, waiting for the execution of the child process
    {
        close(file_index[0]);
        //Writing final output on 
	    while (read(Source_File, Buffer_read, sizeof(Buffer_read)) > 0) 
	    {
            write(file_index[1], Buffer_read, sizeof(Buffer_read));
        }
        close(file_index[1]);
        close(Source_File);
        wait(NULL);
    }
}