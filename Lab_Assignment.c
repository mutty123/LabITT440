#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

void sigint_handler (int sig);

int main ()
{
   int fd[2];
   char buffer[50] = {0};
   pid_t pid[2];

//Q3 - detect control + c .
    if (signal(SIGINT,sigint_handler) == SIG_ERR)
       {
          perror ("signal");
          exit(1);
        }

    // to create pipe
    if (pipe(fd) == -1)
       {
          perror("pipe");
          exit (1);
       }

//Q1 - forking into multiple child passing mesage from parent using pipe
    for(int i = 0; i < 2; i++)
        { 
          int fd_child[2];  //creates seperate pipe for child.

          if (pipe(fd_child) == -1)
            {
               perror ("pipe");
               exit(1);
            }

           //enables forking.
          pid [i] = fork();

          if (pid[i] == 0) //child process
           {
             close (fd[1]);
             close (fd_child[1]);
             read(fd_child[0], buffer,sizeof(buffer));
             printf("\nThe child %d with parent id %d message you entered is : %s\n",i+1,getppid(), buffer);
             close(fd_child[0]);
             close(fd[0]);
             exit(0);

           }

//Q2 - parent process gets input from user & child displays it.
         else if (pid[i] > 0) //parent process
            {
              close(fd[0]);
              printf ("\n(PID : %d) Enter a message for child %d :", getpid(), i+1);
              fgets(buffer,sizeof (buffer),stdin);
              write (fd_child[1], buffer, strlen(buffer)+1); 
              close (fd_child[1]);
              close(fd[1]);
              wait(NULL);
              memset (buffer,0,sizeof(buffer));
           }
       }//end of for loop

return (EXIT_SUCCESS);
}

void sigint_handler (int sig)
{
     printf ("\nLooks like you pressed ctrl+c! Program was interputed!\n");
}
