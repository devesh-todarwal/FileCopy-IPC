## FileCopy-IPC
Use of Inter Process Communications and OS Pipes to develop a simple filecopying program.

## Problem Statement
Design a file-copying program using ordinary pipes. This program will be passed two parameters: the name of the file to be copied and the name of the copied file. The program will then create an ordinary pipe and write the contents of the file to be copied to the pipe. The child process will read this file from the pipe and write it to the destination file.

## Instructions
- Compile the file “filecopy.c” using the following command - `gcc filecopy.c -o filecopy`
- Run the “filecopy” file thus created- `./filecopy <source_file> <destination_file>`
- Example:`./filecopy input.txt output.txt`

## Requirements
- A Linux-based Operating System to handle wait/type operations.
