#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{

int fd[2];
pid_t pid;
int input;
pipe (fd);

pid = fork ();

if (pid > 0)
{
close (fd[0]);
printf ("Enter an integer: ");
scanf ("%d", &input);
write (fd[1], &input, sizeof (input));
close (fd[1]);
close (fd[0]);
}

else if (pid == 0);
{
close (fd[1]);
read (fd[0], &input , sizeof(input));
close (fd[0]);
printf ("\n the input is : %d", input);
close (fd[1]);
exit (0);
}
return (EXIT_SUCCESS);
}

