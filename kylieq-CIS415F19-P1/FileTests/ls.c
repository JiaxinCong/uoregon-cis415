#include <stdio.h> 
#include <dirent.h> 
  
int main(void) { 
  
	DIR *dir = opendir("."); 
  	struct dirent *dirEntry;

    	if (dir == NULL) { 
        	printf("Could not open current directory\n"); 
    	} 
    	else { 
    		while ((dirEntry = readdir(dir)) != NULL) {
        		printf("%s\n", dirEntry->d_name); 
 		}
    	} 
    
    	closedir(dir);     
    	return 0; 
} 

