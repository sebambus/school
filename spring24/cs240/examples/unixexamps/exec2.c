/* Program 2.7 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void main(int argc, char *argv[])
{
   pid_t childpid, waitreturn;
   int status;

   if ((childpid = fork()) == -1) {
      perror("The fork failed");
      exit(1);
   } else if (childpid == 0) {          /* child code */
      if (execvp(argv[1], &argv[1]) < 0) {
         perror("The exec of command failed");
         exit(1);
      }
   } else                               /* parent code */
      while(childpid != (waitreturn = wait(&status)))
         if ((waitreturn == -1) && (errno != EINTR))
            break;
   exit(0);
}
