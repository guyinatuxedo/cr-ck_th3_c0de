#include <stdio.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    char input1[20];
    char input2[5];
    int f;
    int c = 0;
    f = rand() % 100 + 1;
    
    printf("Enter your username\n");
    gets(input1);
    printf(input1);
    printf("Enter your password\n");
    gets(input2);
    c = atoi(input2);
    if(c == f)
    {
       	printf("Welcome to the Kremlin. Now get to work for the glory of the Motherland. Level Cleared\n");	
    }

   else
   {
	printf("Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now \n");
   }
}


