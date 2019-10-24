#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	execvp(argv[1], NULL);
	printf("Done\n");
	return 0;
}
