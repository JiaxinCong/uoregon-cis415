#include<stdio.h> 
  
// chdir function is declared 
// inside this header 
#include<unistd.h>  
int main() 
{    
    char s[100]; 
  
    // printing current working directory 
    printf("cwd1: %s\n", getcwd(s, 100)); 
  
    // using the command 
    chdir("CIS415"); 
  
    // printing current working directory 
    printf("cwd2: %s\n", getcwd(s, 100)); 
  
    // after chdir is executed 
    return 0; 
} 

