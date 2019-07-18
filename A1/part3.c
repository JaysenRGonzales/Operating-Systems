#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>

//Author: Jaysen Gonzales JRG301

int main(int argc, char *argv[])
{
    //if child process
    if(fork() == 0){
        printf("Child Process is running %s\n", argv[1]);
        printf("Parent pid: %d\n",getppid());
        printf("Child pid: %d\n",getpid());
        system(argv[1]);
    }
    //if creation of child process FAILS
    else if(fork() == -1){
        printf("child failed");
    }
    //returned to parent
    else{
        wait(NULL);
    }
    
    return 0;
}

