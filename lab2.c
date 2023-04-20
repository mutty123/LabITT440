#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void entername (int childnum )
{
char name[50];
printf("\nName child %d : ", childnum);
scanf ("%s", name);
printf("\nname for child %d is %s", childnum, name);
}

int main ()
{
for (int i = 1; i<= 4 ; i++)
{
pid_t pid  = fork ();

if (pid == 0)
{
entername (i);
exit (0);
}

else if (pid > 0 )
wait (NULL);
}
printf("\nJob is done");
return EXIT_SUCCESS;
}
