# Processes

## ch3_319
#zombie_process #fork #processes

This exercise is an illustration of zombie processes.
When the child process execution finishes and its parent process has not called wait,
the child process would still be on the process table.

By hanging the parent process with a while(1) loop,
one could use the command ps -l to check the existence of such zombie process.

Send the execution to the background by adding an ampersand to the end of the command, and then ps -l to check.

## ch3_320
#pid_manager #release_pid #allocate_pid
Implementation of allocate_pid and release_pid to imitate the behaviour of the pid_manager.
This exercise is more of a play-around with some simple data structure.

## ch3_321
#fork #wait

Implementation of parent and child processes with fork, and let the child execute something while the parent process waits until the child process is finished.

## ch3_322
#smh_open #ftruncate #mmap

Using the shared memory system service to allow communication between parent / child processes.

## ch3_326
#pipe

Using 2 pipes to allow two way communication between the parent and child process.


## shell_project.c
An simple implementation of the shell. A parent process that prompts the user to input command, and then fork a child process to execute the command.
The history command is implemented with a linked list. By storing all of the command into a CommandNode and add the CommandNode to the tail of the link list, the program is able to show all commands a user has entered without worrying about predefined size of a list.
