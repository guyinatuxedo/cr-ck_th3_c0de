NOT DONE, STILL IN PROGRESS

Let's take a look at the source code...

```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	time_t var0;
	var0 = time(NULL);
	srand(var0);

	int var1;
	var1 = 0;
	char buf0[10];
	char buf1[10];

	while (var1<50)
		{
		int var2 = rand() % 100;
		printf("Your number is %d\n", var2);
		sprintf(buf1, "%d", var2);
		fgets(buf0, sizeof(buf0), stdin);
		if (strcmp(buf0, buf1) == 0)
			{
			printf(buf0);
			printf("How very predictable.\n");
			exit(0);
			}
		var1++;			
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

We can see here, that it is using time as a seed. Thing is, if you have the same seed, then you will have the same output. Since we know the seed, we can write a C program that will generate the same output.

exploit.c
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int check;
	time_t t;
	t = time(NULL);
	srand(t);
	int r = rand() % 100;
	printf("%d\n", r);
}
```

Now we just need to pipe the output of our exploit into the challenge.
```
guyinatuxedo@tux:/Hackery/cr@ck_th3_c0de/hole/h1$ echo `./exploit` | ./h1
Your number is 96
Your number is 19
Your number is 26
Your number is 36
Your number is 80
Your number is 66
Your number is 18
Your number is 80
Your number is 98
Your number is 52
Your number is 14
Your number is 2
Your number is 73
Your number is 94
Your number is 13
Your number is 48
Your number is 84
Your number is 52
Your number is 53
Your number is 96
Your number is 26
Your number is 75
Your number is 28
Your number is 77
Your number is 99
Your number is 49
Your number is 41
Your number is 72
Your number is 78
Your number is 37
Your number is 65
Your number is 26
Your number is 56
Your number is 91
Your number is 15
Your number is 88
Your number is 57
Your number is 85
Your number is 69
Your number is 8
Your number is 37
Your number is 35
Your number is 10
Your number is 10
Your number is 81
Your number is 23
Your number is 10
Your number is 66
Your number is 27
Your number is 15
How very unpredictable. Level Cleared
```

And just like that we pwned the binary. Now let's patch it. 

The vulnerability in the program lied in the fact that it used the system time as a seed, which if an attacker gets them they could generate the random values. However
in linux, the kernel creates a file "/dev/urandom" that contains random numbers that are safe to use as a seed. So if we just used "/dev/urandom" as a seed instead of time,
then the issue will be resolved.

```

```




