#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int call() {
	char whatsup[] = "what's up\n";
	int file;
	if ((file = open("output.txt", O_WRONLY | O_APPEND)) < 0) {
		perror("Problem in opening the file in append mode");
		exit(1);
	}

	ssize_t bytes_written;
	if ((bytes_written = write(file, whatsup, strlen(whatsup))) < 0) {
		perror("Problem in writing to file");
		exit(1);
	}

	printf("Successfully written to file\n");
	close(file);
	return 0;
}

int main() {	
	char hello[] = "hello\n";
	int file = open("output.txt", O_RDWR | O_CREAT, S_IRWXU);// S_IRUSR);

	if (file < 0) {
		perror("Problem in opening the file\n");
		exit(1);
	}

	write(file, hello, strlen(hello));
	close(file);
	call();

	return 0;
}
