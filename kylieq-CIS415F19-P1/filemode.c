int filemode(char file_name[]) {
	char *buffer = (char *)malloc(300*sizeof(char));
	int file = open(filename, O_RDONLY);

	if (file == -1) {
		printf("Error! File not found: %s\n");
		exit(1);
	}


}
/*	FILE *fp = fopen(file_name, "r");

	if (fp == NULL) {
		printf("Error: File not found: %s\n", file_name);
		exit(1);
	}

	char *buffer = NULL;
	size_t bufsize = 100;
	size_t num_char = 0;

	const char *s = " \n";
	char *token;

	char **ptr;
	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		int ctr = 0;
		ptr = (char**)malloc(20*sizeof(char*));

		token = strtok(buffer, s);

		ptr[0] = token;
		ctr = 1;

        while (token != NULL) {
           	token = strtok(NULL, s);
          	ptr[ctr++] = token;
        }

        ptr[ctr-1] = "NULL";
        splitTokens(ptr, -1);
        free(ptr);
	}
*/
	/*Free the allocated memory*/
//	free(buffer);
//	fclose(fp);
//	return 1;
//}