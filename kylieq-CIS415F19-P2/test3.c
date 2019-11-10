#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "command.h"

int CHECK = 0;
int COUNTER = 0;
int EXIT = 0;

void AwaitTermination() {
    while(!EXIT) {
        usleep(300);
    }
}

/*int CheckAllTerminated() {
    for (int i=0; i<PCBS_len; i++) {
        if (PCBS[i]->exit_status == 0) {
            return 0; // There is still a process currently running.
        }
    }
    return 1;
}*/

int CheckAllTerminated() {
    for (int i=0; i<PCBS_len; i++) {
        if (PCBS[i]->exit_status == 0) {
            return 1; // There is still a process currently running.
        }
    }
    return 0;
}

void sigusr1_handler(int sig_num) {
    if (sig_num == SIGUSR1) { 
        printf("Process: %i - Received signal SIGUSR1\n", getpid());
        CHECK = 1;
        sleep(1);
    }
}

/*void sigchld_handler(int sig_num) {
    int status;
    for (int i=0; i<PCBS_len; i++) {
        if (waitpid(PCBS[i]->pid, &status, WNOHANG) > 0) {
            if (WIFEXITED(status)) {
                printf("Process: %d - Ended\n", PCBS[i]->pid);
                PCBS[i]->exit_status = 1;
                PCBS[i]->STATE = TERMINATED; 
            }
        }
    }
}*/

static int alarmed = 0;
void sigalrm_handler(int sig_num) {
    printf("Received alarm\n");
    alarm_check = 1;
}

void idk() {
 int status = -1;
    while(status){
        //reset our current cummulative status
        status = 0;

        //check the status of all the processes
        for (int i = 0; i < PCBS_len; i++){

            //check if this process is still running
            if (PCBS[i]->STATE != TERMINATED){
                //see if we need to wake it up
                if (PCBS[i]->STATE == NOTSTARTED)
                    //wake it up
                    kill(PCBS[i]->pid, SIGUSR1);
                //see if we need to continue it
                else if (PCBS[i]->STATE == READY)
                    //continue it
                    kill(PCBS[i]->pid, SIGCONT);

                //from the above, we should have it running now
                //so update state
                PCBS[i]->STATE = RUNNING;
                printf("Program #%d is running\n", PCBS[i]->pid);

                //reset alarm flag
                alarmed = 0;

                //set an alarm for 1 second
                alarm(1);

                //now we wait (should be 1 second)
                //for the alarm flag to flip
                while(!alarmed) {
                    usleep(300);
                }

                //stop the current process and get ready for next one
                printf("killing pid: %d\n", PCBS[i]->pid);
                kill(PCBS[i]->pid, SIGSTOP);

                //get the status of the process we stopped above
                int w;
                waitpid(PCBS[i]->pid, &w, WUNTRACED);

                //check if the process is done or not
                if (WIFEXITED(w)){
                    //if so, terminate it
                    printf("terminating pid: %d\n", PCBS[i]->pid);
                    PCBS[i]->STATE = TERMINATED;
                }
                //if the if gives something else, that means its not done
                //so put it to the back and get ready for next one
                else{
                    printf("enqueued back pid: %d\n", PCBS[i]->pid);
                    PCBS[i]->STATE = READY;
                }
            }

            //if all states are 0, then change status to 0 and loop will break
            //if we have any state that isn't 0 (not terminated), then status
            //will be non zero and loop will continue
            status |= PCBS[i]->STATE;
        }
    }

/*void sigalrm_handler(int sig_num) {
    sleep(5);
    printf("MADE IT TO SIGALRM\n");

    raise(SIGCHLD);
    if (CheckAllTerminated() == 1) {
        EXIT = 1;
    }

    while(1) {
        if (PCBS[COUNTER]->exit_status == 1) {
            COUNTER = (COUNTER+1)%PCBS_len;
        }
        else {
            break;
        }
    }

    printf("Process: %d Ctr: %d Counter: %d\n", PCBS[COUNTER]->pid, (COUNTER+1)%PCBS_len, COUNTER);
    while(1) {
        if (PCBS[COUNTER]->STATE == RUNNING && PCBS[COUNTER]->exit_status != 1) {
            printf("Proccess %d has PROPER STATES TO BE STOPPED\n", PCBS[COUNTER]->pid);
            int result = kill(PCBS[COUNTER]->pid, SIGSTOP);
            printf("RESULT OF STOP: %d\n", result);
            //if (kill(PCBS[COUNTER]->pid, SIGSTOP) == 0) {
            if(result == 0) {
                printf("Process: %d - Received Signal SIGALRM - Suspended\n", PCBS[COUNTER]->pid);
                PCBS[COUNTER]->STATE = STOPPED;
                sleep(1);
            }
            COUNTER = (COUNTER+1)%PCBS_len;
            break;
        }   
        else if (PCBS[COUNTER]->STATE == STOPPED) {
            break;
        }
        else {
            COUNTER = (COUNTER+1)%PCBS_len;
        }
    }

    while(1) {
        if (PCBS[COUNTER]->STATE == STOPPED && PCBS[COUNTER]->exit_status != 1) {
            printf("PROPER STATES TO CONTINUE\n");
            if (kill(PCBS[COUNTER]->pid, SIGCONT) == 0) {
                printf("Process: %d - Received Signal SIGALRM - Continued\n", PCBS[COUNTER]->pid);
                PCBS[COUNTER]->STATE = RUNNING;
            }
            break;
        }
        else if (PCBS[COUNTER]->STATE == RUNNING) {
            break;
        }
        else {
            COUNTER = (COUNTER+1)%PCBS_len;
        }
    }

    alarm(1);
}*/

/* Stop all processes but the first one */
void SuspendAllProcesses() {
    sleep(1);
    for (int i=0; i<PCBS_len; i++) { /* Stop processes */
        if (kill(PCBS[i]->pid, SIGSTOP) == 0) {
            printf("Process: %d - Suspended\n", PCBS[i]->pid);
            PCBS[i]->STATE = STOPPED; 
            sleep(1);
        }
    }
}

void ContinueAllProcesses() {
    for (int i=0; i<PCBS_len; i++) { /* Continue processes */
        if (kill(PCBS[i]->pid, SIGCONT) == 0) {
            printf("Process: %d - Continued\n", PCBS[i]->pid);
            PCBS[i]->STATE = RUNNING;
            sleep(1);
        }
    }
}

int TerminateAllProcesses() {
    for (int i=0; i<PCBS_len; i++) { /* Terminate processes */
        wait(NULL);
        printf("Process: %d - Ended\n", PCBS[i]->pid);
        PCBS[i]->STATE = TERMINATED; 
        PCBS[i]->exit_status = 1;
        sleep(1);
    } 
    return 1;
}

int MakeCall() {
    for (int i=0; i<PCBS_len; i++) {
        PCBS[i]->pid = fork();
        PCBS[i]->STATE = RUNNING;

        if (PCBS[i]->pid < 0) {
            printf("Unable to fork process.\n");
            exit(1);
        }
        if (PCBS[i]->pid == 0) {
            /* Have process wait until it receives SIGUSR1 signal */
            while(!CHECK) {
                usleep(300);
            }

            /* Launch workload programs */
            if (execvp(PCBS[i]->cmd, PCBS[i]->args) < 0) {
                //printf("Process failed to execute command: %s. Exiting.\n", PCBS[i]->cmd);
            }

            exit(-1);
        }
    }

    sleep(1);

    for (int i=0; i<PCBS_len; i++) { /* SIGUSR1 signal */
        printf("Process: %d - Joined\n", PCBS[i]->pid);
        kill(PCBS[i]->pid, SIGUSR1);
    }
    sleep(1);
    return 1;
}

int main(int argc, char *argv[]) {
    signal(SIGUSR1, sigusr1_handler);
    //signal(SIGALRM, sigalrm_handler);
    //signal(SIGCHLD, sigchld_handler);

    char *filename = argv[1];

    char *buffer = NULL;
    size_t bufferSize = 300;
    ssize_t inputSize = 0;

    /* Allocate memory for the input buffer. */
    buffer = (char *)malloc(bufferSize * sizeof(char));

    /* Read text file given by the user. */
    inputSize = GetLine(filename, buffer, bufferSize);

    /* Place '\0' at the end of the string held in the input buffer 
       to signify the end of the string. */
    if (inputSize > 0) {
        buffer[strlen(buffer)] = '\0';
    }
    else {
        buffer[0] = '\0';
    }

    char *token;

    size_t ptrSize = 300;
    char **ptr = (char **)malloc(ptrSize * sizeof(char*));
 
    /* Initialize values of the ptr to NULL */
    for (int i=0; i<ptrSize; i++) {
        ptr[i] = NULL;
    }  

    /* Tokenize the input string with the delimiters ';', newline character '\n'
       and carriage return '\r', and place each token in ptr. This collection of
       tokens represents a single command and its arguments. */
    token = strtok(buffer, "\n\r");
    ptr[0] = token;
    int line_ctr = 1;

    while (token != NULL) {
        token = strtok(NULL, "\n\r");
        ptr[line_ctr] = token;
        line_ctr++;
    }   

    /* Collection of PCB's */
    PCBS_len = 0;
    PCBS = malloc(line_ctr * sizeof(struct ProcessControlBlock*));

    /* Send the command and its arguments (held in ptr) to parseCommand */
    ParseCommand(ptr, line_ctr, PCBS);

    /* Make calls */
    MakeCall();
    //SuspendAllProcesses();
    //alarm(1);
    idk();
    //AwaitTermination();
    //TerminateAllProcesses();

    FreePCB(PCBS);
    free(ptr);
    free(buffer);
    return 0;
}

