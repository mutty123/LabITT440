#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler (int sig);

int main ()
{
int p[2];
int num;
pid_t pid;

if (signal (SIGINT,sigint_handler) == SIG_ERR)
{
perror ("signal");
exit (1);
}

if (pipe (p) == -1){
perror ("pipe");
exit (1);
}

pid = fork ();

if (pid == -1)
{
perror ("fork");
exit (1);
}

if (pid ==0)
{
close (p[0]);
printf ("Enter a number : ");
fflush (stdout);
scanf ("%d", &num);


if (write(p[1], &num , sizeof(num)) == -1 ){
perror ("write");
exit (1);
}

close (p[1]);
exit (0);
}

else {

close (p[1]);

if (read (p[0], &num, sizeof (num)) == -1 )
{
perror ("read");
exit(1);
}

int is_prime = 1;

for (int i =2 ; i<= num /2 ; i++){
if (num %i == 0)
{
is_prime = 0;
break;
}
}

if (is_prime ) 
printf ("\nIt is  a prime number\n");

else 
printf ("\nIt is not a prime number");

close (p[0]);
exit(0);
}
}

void sigint_handler (int sig)
{
printf("YOU ENABLED SIGINT\n");
exit (0);

}
