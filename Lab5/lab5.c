/*
* Description: A simple lab showing signal processing
*
* Author: Jared Hall
*
* Date: 10/21/2019
*
* Notes:
* 1. to be done in lab
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
void handler(int sig_num) {
    if (sig_num == SIGUSR1) {
        printf("Process: %i - Received signal: %d\n", getpid(), SIGUSR1);
    }
    sleep(1);
}

void signaler(pid_t *pids, int sig_num) {
    for (int i=0; i<5; i++) { /* SIGUSR1 signal */
        kill(pids[i], sig_num);
    }
    sleep(1);
    for (int i=0; i<5; i++) { /* SIGUSR1 signal */
        kill(pids[i], sig_num);
    }
    sleep(1);
    for (int i=0; i<5; i++) { /* Stop processes */
        if (kill(pids[i], SIGINT) == 0) {
            printf("Process: %d - Received signal: %d\n", pids[i], SIGINT);
        }
    }
}

int	main() {
	//variable definitions
	pid_t  pid, w;
	int wstatus, i;
	i=0;

    struct sigaction act;
    sigset_t set;
    int sig;

    /* Initialize signal set to exclude all of the defined signals.
       Then add SIGUSR1 to the signal set */
    sigemptyset(&set);
    sigaddset(&set,SIGUSR1);

    act.sa_flags = 0;
    act.sa_mask = set;
    act.sa_handler = handler;

	int *pids = (int *)malloc(5 * sizeof(int));
	
	for (int i=0; i<5; i++) {
		pids[i] = fork();
		if (pids[i] == 0) {
			sigaction(SIGUSR1, &act, NULL);

			printf("	Child Process: %i - Starting infinite loop...\n", getpid());

			while(1) {
				i++;
				if(i%10000) {
					printf("	Child Process: %i - Running infinite loop...\n", getpid());
					i = 0;
				}
			}

			exit(-1);
		} 
		else {
			//else this is an existing proc i.e. the parent
			printf("Parent Process: %i, Waiting for child to finish...\n", getpid());
			signaler(pids, SIGUSR1);
			w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
			printf("All child processes joined. Exiting.\n");
		}
	}
	free(pids);
}
/*-----------------------------Program End-----------------------------------*/
