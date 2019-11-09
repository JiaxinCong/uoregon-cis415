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

void sigusr1_handler(int sig_num) {
    if (sig_num == SIGUSR1) { 
        printf("Process: %i - Received signal: SIGUSR1\n", getpid());
        CHECK = 1;
        sleep(1);
    }
}

void sigalrm_handler(int sig_num) {
    printf("MADE IT TO SIGALRM\n");

    //while(1) {
        if (PCBS[COUNTER]->STATE == RUNNING) {
            kill(PCBS[COUNTER]->pid, SIGSTOP);
            printf("Process: %d - Received Signal SIGALRM - Suspended\n", PCBS[COUNTER]->pid);
            PCBS[COUNTER]->STATE = PAUSED;
            //break;
        }   
        else {
            COUNTER++;
        }
    //}

    //while(1) {
        if (PCBS[COUNTER]->STATE == PAUSED) {
            kill(PCBS[COUNTER]->pid, SIGCONT);
            printf("Process: %d - Received Signal SIGALRM - Continued\n", PCBS[COUNTER]->pid);
            PCBS[COUNTER]->STATE = RUNNING;
            //break;
        }
        else {
            COUNTER++;
        }
    //}
    //alarm(3);
}

/* Stop all processes but the first one */
void SuspendAllProcesses(struct ProcessControlBlock **PCBS) {
    for (int i=1; i<PCBS_len; i++) { /* Stop processes */
        if (kill(PCBS[i]->pid, SIGSTOP) == 0) {
            printf("Process: %d - Suspended\n", PCBS[i]->pid);
            PCBS[i]->STATE = NOTSTARTED;
            sleep(1);
        }
    }
    sleep(5);
}

void ContinueAllProcesses(struct ProcessControlBlock **PCBS) {
    for (int i=0; i<PCBS_len; i++) { /* Continue processes */
        if (kill(PCBS[i]->pid, SIGCONT) == 0) {
            printf("Process: %d - Continued\n", PCBS[i]->pid);
            PCBS[i]->STATE = RUNNING;
            sleep(1);
        }
    }
    sleep(5);
}

int TerminateAllProcesses(struct ProcessControlBlock **PCBS) {
    for (int i=0; i<PCBS_len; i++) { /* Terminate processes */
        wait(NULL);
        printf("Process: %d - Ended\n", PCBS[i]->pid);
        PCBS[i]->STATE = TERMINATED;
        sleep(1);
    } 
    return 1;
}

int makeCall(struct ProcessControlBlock **PCBS) {
    for (int i=0; i<PCBS_len; i++) {
        PCBS[i]->pid = fork();

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
                printf("Process failed to execute command: %s. Exiting.\n", PCBS[i]->cmd);
            }

            exit(-1);
        }
    }

    sleep(1);

    for (int i=0; i<PCBS_len; i++) { /* SIGUSR1 signal */
        printf("Process: %d - Joined\n", PCBS[i]->pid);
        kill(PCBS[i]->pid, SIGUSR1);
    }

    return 1;
}

int main(int argc, char *argv[]) {

//    struct sigaction act;
//    sigset_t set;

    /* Initialize signal set to exclude all of the defined signals.
       Then add SIGUSR1 to the signal set */
/*    sigemptyset(&set);
    sigaddset(&set,SIGUSR1);
    sigaddset(&set,SIGALRM);

    act.sa_flags = 0;
    act.sa_mask = set;
    act.sa_handler = handler;
*/
    /* Set signal handler for SIGUSR1 */
//    sigaction(SIGUSR1, &act, NULL);
//    sigaction(SIGALRM, &act, NULL);
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGALRM, sigalrm_handler);

    char *filename = argv[1];

    char *buffer = NULL;
    size_t bufferSize = 300;
    ssize_t inputSize = 0;

    /* Allocate memory for the input buffer. */
    buffer = (char *)malloc(bufferSize * sizeof(char));

    /* Read text file given by the user. */
    inputSize = get_line(filename, buffer, bufferSize);

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
    parseCommand(ptr, line_ctr, PCBS);

    /* Make calls */
    makeCall(PCBS);
    sleep(1);
    SuspendAllProcesses(PCBS);
    while(1) {
        alarm(1);
    }
    TerminateAllProcesses(PCBS);

    freePCB(PCBS);
    free(ptr);
    free(buffer);
    return 0;
}
