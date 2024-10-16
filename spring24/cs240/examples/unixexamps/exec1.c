/* Program 2.6 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    pid_t childpid;
    int status;

    if ((childpid = fork()) == -1)  {
       perror("Error in the fork");
       exit(1);
    } else  if (childpid == 0) {               /* child code */
       if (execl("/bin/ls", "ls", "-l", NULL) < 0) {
          perror("Exec of ls failed");
          exit(1);
       } 
    } else if (childpid != wait(&status))   /* parent code */
       perror("A signal occurred before the child exited");
      else
          fprintf(stderr, "Child terminated normally. So will I!\n");
    exit(0);
}
