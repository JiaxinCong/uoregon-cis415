struct ProcessControlBlock **PCBS;
int PCBS_len;
typedef enum {NOTSTARTED, RUNNING, STOPPED, TERMINATED} STATES; 
//                        1        0
struct ProcessControlBlock {
	pid_t pid;
	char *cmd;
	char **args;
	int count;
	int exit_status;
	STATES STATE;
};

/* Read file */
int GetLine(char *filename, char *buffer, size_t bufferSize);

/* Split line read from file into individual commands */
int ParseCommand(char **arr, size_t arrSize, struct ProcessControlBlock **PCBS);

/* Free struct ProcessControlBlock */
int FreePCB(struct ProcessControlBlock **PCBS);