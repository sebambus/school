/* Example 2.1 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void)
{
   printf("Process ID: %ld\n", (long)getpid());
   printf("Parent process ID: %ld\n", (long)getppid());
   printf("Owner user ID: %ld\n", (long)getuid());
}
