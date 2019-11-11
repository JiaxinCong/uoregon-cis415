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
    printf("Done!\n");
}

int CheckAllTerminated() {
    for (int i=0; i<PCBS_len; i++) {
        if (PCBS[i]->exit_status == 0) {
            return 0; // There is still a process currently running.
        }
    }
    return 1;
}

void sigusr1_handler(int sig_num) {
    if (sig_num == SIGUSR1) { 
        printf("Process: %i - Received signal: SIGUSR1\n", getpid());
        CHECK = 1;
        sleep(1);
    }
}

void sigchld_handler(int sig_num) {
    int status;
    for (int i=0; i<PCBS_len; i++) {
        if (waitpid(PCBS[i]->pid, &status, WNOHANG) > 0) {
            if (WIFEXITED(status)) {
                printf("Process: %d - Terminated\n", PCBS[i]->pid);
                PCBS[i]->exit_status = 1;
                PCBS[i]->state = TERMINATED;
            }
        }
    }
}

/*void sigalrm_handler(int sig_num) {
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

    while(1) {
        if (PCBS[COUNTER]->state == RUNNING && PCBS[COUNTER]->exit_status != 1) {
            kill(PCBS[COUNTER]->pid, SIGSTOP);
            printf("Process: %d - Received Signal SIGALRM - Suspended\n", PCBS[COUNTER]->pid);
            PCBS[COUNTER]->state = STOPPED;
            COUNTER = (COUNTER+1)%PCBS_len;
            break;
        }   
        else {
            COUNTER = (COUNTER+1)%PCBS_len;
        }
    }

    while(1) {
        if (PCBS[COUNTER]->state == STOPPED && PCBS[COUNTER]->exit_status != 1) {
            kill(PCBS[COUNTER]->pid, SIGCONT);
            printf("Process: %d - Received Signal SIGALRM - Continued\n", PCBS[COUNTER]->pid);
            PCBS[COUNTER]->state = RUNNING;
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
    for (int i=0; i<PCBS_len; i++) { /* Stop processes */
        if (kill(PCBS[i]->pid, SIGSTOP) == 0) {
            printf("Process: %d - Suspended\n", PCBS[i]->pid);
            PCBS[i]->state = STOPPED; 
            sleep(1);
        }
    }
}

void ContinueAllProcesses() {
    for (int i=0; i<PCBS_len; i++) { /* Continue processes */
        if (kill(PCBS[i]->pid, SIGCONT) == 0) {
            printf("Process: %d - Continued\n", PCBS[i]->pid);
            PCBS[i]->state = RUNNING;
            sleep(1);
        }
    }
}

int TerminateAllProcesses() {
    for (int i=0; i<PCBS_len; i++) { /* Terminate processes */
        wait(NULL);
        printf("Process: %d - Terminated\n", PCBS[i]->pid);
        PCBS[i]->state = TERMINATED; 
        PCBS[i]->exit_status = 1;
        sleep(1);
    } 
    return 1;
}

int MakeCall() {
    for (int i=0; i<PCBS_len; i++) {
        PCBS[i]->pid = fork();
        PCBS[i]->state = RUNNING;

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

            exit(1);
        }
    }

    sleep(1);

    for (int i=0; i<PCBS_len; i++) { /* SIGUSR1 signal */
        printf("Process: %d - Joined\n", PCBS[i]->pid);
        kill(PCBS[i]->pid, SIGUSR1);
    }

    return 1;
}


static int alarmFlg = 0;
void alarmHandler(int signal){

    alarmFlg=1;

}

int exist_test(int exist[], int count){

    for(int x=0; x<count; x++){
        if(exist[x] == 0){                                          // if any of element in exist is 0 keep while loop
            return 1;
        }
        return 0;
    }

}


int main(int argc, char *argv[]) {
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGALRM, sigalrm_handler);
    signal(SIGCHLD, sigchld_handler);

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
    sleep(1);
    SuspendAllProcesses();
//    alarm(1);


    system("sleep 1");
    int runPid, exist[PCBS_len], a=1, b=0;
    pid_t w;

    for(int i=0; i<PCBS_len; i++){
        exist[i] = 0;
    }

    signal(SIGALRM, alarmHandler);  
    kill(PCBS[0]->pid,SIGCONT);
    w = waitpid(PCBS[0]->pid, &wstatus, WNOHANG);
    while(a){
        for(runPid=0; runPid<PCBS_len; runPid++){
            alarm(1);
            system("sleep 1");
            if(w == 0 ){
                if(alarmFlg==1){
                    printf("stopping signal to %d\n", PCBS[runpid]->pid);     
                    kill(PCBS[runpid]->pid, SIGSTOP);                         // sending stop signal
                    printf("running signal to %d\n", PCBS[(runPid+1)%PCBS_len]->pid);
                    kill(PCBS[(runPid+1)%PCBS_len]->pid, SIGCONT);                    // sending start signal
                    alarmFlg = 0 ;
                }
                        
            }else if(w == -1 ){
                exist[b] = -1;                                          // respectively put -1 when pid is finished running 
                b++;
                continue;
            }
            w = waitpid(PCBS[(runPid+1)%PCBS_len]->pid, &wstatus, WNOHANG);
        }
        //system("sleep 1");
        a = exist_test(exist, PCBS_len);
    }       
    for(k=0; k<j; k++){
        printf("pid is waiting %d\n", PCBS[k]->pid);
        waitpid(PCBS[k]->pid, &wstatus, WNOHANG );
    }


    AwaitTermination();

    FreePCB(PCBS);
    free(ptr);
    free(buffer);
    return 0;
}