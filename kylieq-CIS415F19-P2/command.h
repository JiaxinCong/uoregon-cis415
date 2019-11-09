struct ProcessControlBlock **PCBS;
int PCBS_len;
typedef enum {NOTSTARTED, RUNNING, PAUSED, TERMINATED} STATES; 

struct ProcessControlBlock {
	pid_t pid;
	char *cmd;
	char **args;
	int count;
	STATES STATE;
};

/* Read file */
int get_line(char *filename, char *buffer, size_t bufferSize);

/* Split line read from file into individual commands */
int parseCommand(char **arr, size_t arrSize, struct ProcessControlBlock **PCBS);

/* Free struct ProcessControlBlock */
int freePCB(struct ProcessControlBlock **PCBS);