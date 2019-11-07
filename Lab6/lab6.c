/*-----------------------------------------------------------------------------
File name: Lab6.c
Description: A simple lab showing the use of signals.
Author: Kylie Quan
-----------------------------------------------------------------------------*/

/*---------------------------Preprocessor Directives-------------------------*/
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
/*---------------------------------------------------------------------------*/

/*---------------------------------Functions---------------------------------*/
void send_sig(pid_t pid) {
    printf("    Child process: %d - Stopped...\n", pid);
    kill(pid, SIGSTOP);
    sleep(3);
    printf("    Child process: %d - Continued...\n", pid);
    kill(pid, SIGCONT);
}
/*---------------------------------------------------------------------------*/

/*--------------------------------Program Main-------------------------------*/
int main(void) 
{
    //variable declarations
    pid_t pid, w;
    int wstatus;

    //create a child process
    pid = fork();
    if(pid < 0) {
        perror("Error! could not create a new process.\n");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0) {
        //This code runs in the child process only
	    printf("    Child process: %d - Starting...\n", getpid());
	    //Add your while loop here
        int ctr = 1;
        while (ctr <= 10) {
            sleep(1);
            printf("    Child process: %d - Still alive after for %d seconds...\n", getpid(), ctr);
            ctr++;
        }
	    exit(EXIT_SUCCESS);
    } 
    else if(pid > 0) {
        //This code runs in the parent process only
        printf("Parent process: %d - Sending signals to child...\n", getpid());
	    //Add code to send your signals  in a loop here
        printf("Parent process: %d - Waiting for child to complete...\n", getpid());

        w = waitpid(pid, &wstatus, WNOHANG);

        sleep(1);
        while (w == 0) {
            send_sig(pid);
            sleep(1);
            w = waitpid(pid, &wstatus, WNOHANG);

        }

	    printf("Parent process: %d - Finished\n", getpid());
    }
    
    //exit out of program
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
