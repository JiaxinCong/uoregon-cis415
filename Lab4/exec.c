#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	pid_t pid = fork();
	printf("pid: %d\n", getpid());
	if (pid == 0) { 
		execvp(argv[1], NULL);
		exit(-1);
	}
	printf("Done\n");
	return 0;
}
