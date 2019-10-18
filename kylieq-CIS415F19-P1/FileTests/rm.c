#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

int main(int argc, char *argv[]) {
    int status;
    char *file_name = argv[1];

//    status = remove(file_name);
    status = unlink(file_name);
    if (status == 0) {
        printf("file deleted successfully\n");
    }

    else {
        printf("Unable to delete file\n");
    }
    return 0;
}   

