/*
CSS430B Spring 2014
Professor Stephen Dame
Programming Assignment 1 Part 1

Specification
Creating a C++ program that mimics the command of "ps -A | grep argv[1] | wc -l"
Command will get all processes, filter only process that match argument, and then give a final count

Implementation details
Parent waits for child with no change to STDIN and STDOUT
Child process executes wc -l using read end of pipe from Grand Child
Grand Child process executes grep argv[1] using read end of pipe from Great Grand Child and outputs to write end of pipe to Child
Great Grand Child process executes ps -A and outputs to write end of pipe to Grand Child

Test commands
processes mingetty
ps -A | grep mingetty | wc -l

processes ksand
ps -A | grep kscand | wc -l

processes sendmail
ps -A | grep sendmail | wc -l

Current Implementation (DONE)
Nested if statements with each process following the forking process

Ideal Implementation (Not Started)
Recursive function
Brainstorming Ideas
Step 1 take input into string array (in this case string would already be set)
Step 2 reverse parse string until pipe is hit
Step 3 send string, end of string, location of pipe
Step 4 create pipe and fork (somehow need to keep track of number of pipes, vector probably)
step 5 repeat step 2 using (pipe location -1) as end and (pipe location-2) as start
step 6 if start is at 0, build command using start and end
step 7 process closes the read end of the pipe that existed
step 8 process closes write end of pipe that process created
step 9 use dup2 to link pipe to STDIN and STDOUT
step 10 execute command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	//enum to define read and write for pipe descriptor
    enum {
    RD,
    WR};

	//declare all pid_t variables for all child processes
    pid_t pid1,pid2,pid3;
	
	//Parent Process forks a child process and checks for success
    pid1 = fork();
    if(pid1 < 0) {
        perror("FORK FAILED");
        exit(EXIT_FAILURE);
    }
	//If Child Process, Execute Child Procedure
    if(pid1 == 0) {
		//Child process creates pipe to grand-child
        int fd2[2];
        if(pipe(fd2) < 0) {
            perror("Child PIPE Failed");
            exit(EXIT_FAILURE);
        }
		//Child Process forks to create grand-child
        pid2 = fork();
        if(pid2 < 0) {
            perror("Child Fork Failed");
            exit(EXIT_FAILURE);
        }
		//If grand-child, execute grand-child procedures
        if(pid2 == 0){
			//grand-child creates pipe to great-grand-child
            int fd3[2];
            if(pipe(fd3) < 0) {
                perror("Great Grand Child Pipe Failed");
                exit(EXIT_FAILURE);
            }
			//grand-child forks to create great-grand-child (ggc) process
            pid3 = fork();
            if(pid3 < 0) {
                perror("Great Grand Child Fork Failed");
                exit(EXIT_FAILURE);
            }
			//If ggc, execute ggc procedure
            if(pid3 == 0) {
				//Great Grand Child procedure
				//ggc closes read end of pipe since it's unnecessary
                close(fd3[RD]);
				//gcc uses write end of pipe with STDOUT
                dup2(fd3[WR],1);
				//Executes ps -A and outputs to pipe for grand-child
                execlp("/bin/ps","ps","-A",NULL);
            } else {
                //Grand Child procedures
                close(fd2[RD]);//close read to child
                dup2(fd2[WR],1);//stdout to grand childs pipe write
                close(fd3[WR]);//close write to great grand child
                dup2(fd3[RD],0);//stdin
                wait(NULL); //wait for gcc to complete
				//Execute grep command using input from pipe from gcc
				//Output goes into the pipe linked to the child process
                execlp("/bin/grep","grep","-e",argv[1],NULL);
            }
        } else {
            //Child Procedure
            close(fd2[WR]); //close write end of pipe to grand child
            dup2(fd2[RD],0); //STDIN linked to pipe read
            wait(NULL); //wait for grand child process
            execlp("/usr/bin/wc","wc","-l",NULL); //execute word count command
        }
    } else {
		//Parent Procedure
        wait(NULL); //wait for child process
		
        return EXIT_SUCCESS;
    }
}
