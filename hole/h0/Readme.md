(This challenge was inspired by the challenge game from bitsctf on 2/04/17)

Let's take a look at the source code...

```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
	int i;
	time_t var0;
	var0 = time(NULL);
	srand(var0);

	int var1;
	var1 = 0;
	char buf0[500];
	char buf1[500];

	for (i=0; i<50; i++)
		{
		int var2 = rand() % 100;
		printf("You've been falling for %d days. Strange, that is %d days more than you will spend outside.\n", i, i);
		sprintf(buf1, "%d", var2);
		scanf(" %s", buf0);
		strtok(buf0, "\n");
		if (strcmp(buf1, buf0) != 0)
			{			
			printf("How very predictable.\n");
			printf("Your number was %s\n", buf1);
			exit(0);
			}				
		}
	printf("How very unpredictable. Level Cleared\n");
}
```

So looking at this, we can see that if we just reach the end of the program we will pass the level. However before that happens,
a loop is iterated 50 times. In this loop, it generates a random number and asks us for it. If we get it wrong, then the application exits
and we don't clear the level. So we will have to come up with a method to generate the same numbers as the algorithm. We can see that it is
using the rand() function which requires a seed (which is essentially just a base) for the rand() function to generate a random number. Let's see what it is.

```
	time_t var0;
	var0 = time(NULL);
	srand(var0);
```

We can see here, that it is using time as a seed. With this in mind if you have the same seed, then you will have the same output. Since we know the seed, we can write a C program that will generate the same output.

exploit.c
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i;
	time_t t;
	t = time(NULL);
	srand(t);
	for (i=0; i<50; i++) 
	{
		int r = rand() % 100;
		printf("%d\n", r);
	}
}
```

Now we just need to compile the code and pipe the output of our exploit into the challenge.
```
root@tux:/Hackery/cr@ck_th3_c0de/hole/h0# gcc exploit.c -o exploit
root@tux:/Hackery/cr@ck_th3_c0de/hole/h0# echo `./exploit` | ./h0
You've been falling for 0 days. Strange, that is 0 days more than you will spend outside.
You've been falling for 1 days. Strange, that is 1 days more than you will spend outside.
You've been falling for 2 days. Strange, that is 2 days more than you will spend outside.
You've been falling for 3 days. Strange, that is 3 days more than you will spend outside.
You've been falling for 4 days. Strange, that is 4 days more than you will spend outside.
You've been falling for 5 days. Strange, that is 5 days more than you will spend outside.
You've been falling for 6 days. Strange, that is 6 days more than you will spend outside.
You've been falling for 7 days. Strange, that is 7 days more than you will spend outside.
You've been falling for 8 days. Strange, that is 8 days more than you will spend outside.
You've been falling for 9 days. Strange, that is 9 days more than you will spend outside.
You've been falling for 10 days. Strange, that is 10 days more than you will spend outside.
You've been falling for 11 days. Strange, that is 11 days more than you will spend outside.
You've been falling for 12 days. Strange, that is 12 days more than you will spend outside.
You've been falling for 13 days. Strange, that is 13 days more than you will spend outside.
You've been falling for 14 days. Strange, that is 14 days more than you will spend outside.
You've been falling for 15 days. Strange, that is 15 days more than you will spend outside.
You've been falling for 16 days. Strange, that is 16 days more than you will spend outside.
You've been falling for 17 days. Strange, that is 17 days more than you will spend outside.
You've been falling for 18 days. Strange, that is 18 days more than you will spend outside.
You've been falling for 19 days. Strange, that is 19 days more than you will spend outside.
You've been falling for 20 days. Strange, that is 20 days more than you will spend outside.
You've been falling for 21 days. Strange, that is 21 days more than you will spend outside.
You've been falling for 22 days. Strange, that is 22 days more than you will spend outside.
You've been falling for 23 days. Strange, that is 23 days more than you will spend outside.
You've been falling for 24 days. Strange, that is 24 days more than you will spend outside.
You've been falling for 25 days. Strange, that is 25 days more than you will spend outside.
You've been falling for 26 days. Strange, that is 26 days more than you will spend outside.
You've been falling for 27 days. Strange, that is 27 days more than you will spend outside.
You've been falling for 28 days. Strange, that is 28 days more than you will spend outside.
You've been falling for 29 days. Strange, that is 29 days more than you will spend outside.
You've been falling for 30 days. Strange, that is 30 days more than you will spend outside.
You've been falling for 31 days. Strange, that is 31 days more than you will spend outside.
You've been falling for 32 days. Strange, that is 32 days more than you will spend outside.
You've been falling for 33 days. Strange, that is 33 days more than you will spend outside.
You've been falling for 34 days. Strange, that is 34 days more than you will spend outside.
You've been falling for 35 days. Strange, that is 35 days more than you will spend outside.
You've been falling for 36 days. Strange, that is 36 days more than you will spend outside.
You've been falling for 37 days. Strange, that is 37 days more than you will spend outside.
You've been falling for 38 days. Strange, that is 38 days more than you will spend outside.
You've been falling for 39 days. Strange, that is 39 days more than you will spend outside.
You've been falling for 40 days. Strange, that is 40 days more than you will spend outside.
You've been falling for 41 days. Strange, that is 41 days more than you will spend outside.
You've been falling for 42 days. Strange, that is 42 days more than you will spend outside.
You've been falling for 43 days. Strange, that is 43 days more than you will spend outside.
You've been falling for 44 days. Strange, that is 44 days more than you will spend outside.
You've been falling for 45 days. Strange, that is 45 days more than you will spend outside.
You've been falling for 46 days. Strange, that is 46 days more than you will spend outside.
You've been falling for 47 days. Strange, that is 47 days more than you will spend outside.
You've been falling for 48 days. Strange, that is 48 days more than you will spend outside.
You've been falling for 49 days. Strange, that is 49 days more than you will spend outside.
How very unpredictable. Level Cleared
```

And just like that we pwned the binary. Now let's patch it. 

The vulnerability in the program lied in the fact that it used the system time as a seed, which if an attacker gets them they could generate the random values. However
in linux, the kernel creates a file "/dev/urandom" that contains random numbers that are safe to use as a seed. So if we just used "/dev/urandom" as a seed instead of time,
then the issue will be resolved.

```
#include <stdio.h>
#include <stdlib.h>
#include <linux/random.h>
#include <string.h>

int main()
{
	int i;
	int fd;
	int r;
	fd = fopen("/dev/urandom", "rb");
	char buf2[30];
	fread(buf2, sizeof(buf2), 1, fd);

	srand(buf2);

	int var1;
	var1 = 0;
	char buf0[500];
	char buf1[500];

	for (i=0; i<50; i++)
		{
		int var2 = rand() % 100;
		printf("You've been falling for %d days. Strange, that is %d days more than you will spend outside.\n", i, i);
		sprintf(buf1, "%d", var2);
		scanf(" %s", buf0);
		strtok(buf0, "\n");
		if (strcmp(buf1, buf0) != 0)
               	 	{
                	printf("How very predictable.\n");
                        printf("Your number was %s\n", buf1);
                        exit(0);
                	}
		}
	printf("How very unpredictable. Level Cleared\n");
}
```

As you can see here, instead of using time as a seed we read data from "/dev/urandom" and use the data as a seed. That way it is crptographically secure and someone just can't use system time as a seed and generate the same sequence.


