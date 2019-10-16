int main(int argc, char argv[]) {
	char file_name[] = argv[1];
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error: File not found: %s\n", file_name);
		exit(1);
	}

	char *buffer;
	size_t bufsize = 100;
	size_t num_char;

	const char s[3]= " \n";
	char *token;

	char **ptr;
	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		int ctr = 0;
		ptr = (char**)malloc(20*sizeof(char*));

		printf("\n%s\n", buffer);

		token = strtok(buffer, s);
		ptr[0] = token;
		ctr = 1;

        while (token != NULL) {
        	checkCommand(token);
           	token = strtok(NULL, s);
          	ptr[ctr++] = token;
        }
        ptr[ctr-1] = "NULL";
        splitFile(ptr);
	}

	/*Free the allocated memory*/
	free(ptr);
	fclose(fp);
	return 1;
}
