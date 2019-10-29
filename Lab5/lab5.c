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
void handler(signo) {
	static int first = 1;

	if (first) {
		first = 0;
		printf("Child process: %i - Received signal: %d\n", getpid(), SIGUSR1);
	}
}

int	main() {
	//variable definitions
	pid_t  pid, w;
	int wstatus, i;
	i=0;

	extern void handler();
	struct sigaction act;
	sigset_t set;

    /* Initialize signal set to exclude all of the defined signals.
       Then add SIGUSR1 to the signal set */
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);

    /* Block SIGUSR1 to prevent interrupts */
    sigprocmask(SIG_BLOCK, &set, NULL);

	act.sa_flags = 0;
	act.sa_mask = set;
	act.sa_handler = &handler;
	sigaction(SIGUSR1, &act, NULL);

	//kill(getpid(), SIGUSR1);

	for (i=0; i<5; i++) {
	
		pid = fork();

		/* Send signal */
        kill(pid, SIGUSR1);

		if (pid == 0) {
			printf("	Child Process: %i - Starting infinite loop...\n", getpid());
			while(1) {
				i++;
				int sig;

				/* SIGUSR1 is blocked and pending. sigwait will return 0 immediately
                   after receiving signal */
				sigwait(&set, &sig);

	            /* SIGUSR1 no longer pending. Send signal again and then unblock it */
            	kill(pid, SIGUSR1);

				if(i%10000) {
					printf("	Child Process: %i - Running infinite loop...\n", getpid());
	
					//if (sigwait(&set, &sig) == 0) { 
					//	break; 
					//}
	            	//kill(pid, SIGUSR1);

					i=0;
				}
				sigprocmask(SIG_UNBLOCK, &set, NULL);
			}
		} else {
			//else this is an existing proc i.e. the parent
			printf("Parent Process: %i, Waiting for child to finish...\n", getpid());
			w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
			printf("All child processes joined. Exiting.\n");
		}
	}
}
/*-----------------------------Program End-----------------------------------*/
