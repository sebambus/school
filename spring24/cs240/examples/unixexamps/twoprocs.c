#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main(void)
{
    pid_t childpid;

    printf("\nMy shell's PID is %ld\n", (long)getppid());
    if ((childpid = fork()) == 0) {
       fprintf(stderr, "\nI am the child, ID = %ld\n", (long)getpid());
       sleep(20);
       fprintf(stderr, "\nChild slept for 20 secs\n");    
          /*   child code goes here  */
    } else if (childpid > 0) {
       fprintf(stderr, "\nI am the parent, ID = %ld\n", (long)getpid());
       sleep(30);
       fprintf(stderr, "\nParent slept for 30 secs\n");
          /*  parent code goes here */
    }

}

