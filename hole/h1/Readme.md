let's take a look at the code...

```
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char buf0[10];
	float var0;
		
	fgets(buf0, sizeof(buf0), stdin);
	var0 = atof(buf0);
	if (var0 < 37.35928559)
	{
		printf("Too low just like you're chances of reaching the bottom.\n");
		exit(0);
	}

	if (var0 > 37.35928559)
  {
    printf("To high just like your hopes of reaching the bottom.\n");
    exit(0);
  }

	else 
	{

		printf("Oh wait, there might be a bottom to this. Level cleared\n");
	}

}

```

So this code seems simple enough. It takes input, converts it to a float and sees if it is greater than or less than a fixed value. If 
it is neither then you beat the level. The only way for a number to neither be greater than or less than to a number, is if it is equal to that number.
So we should just be able to input that value and clear the level. Let's try it.

```
root@tux:/Hackery/cr@ck_th3_c0de/hole/h1# ./h1
37.35928559
Too low just like you're chances of reaching the bottom.
```
What that didn't work? We inputted the same value and it evaluated it as less than that value. However when we take a closer look at the code we see something that would cause this.

```
  char buf0[10];
	float var0;
		
	fgets(buf0, sizeof(buf0), stdin);
```

So the buffer is only 10 bytes, It isn;t large enough to hold all of the characters in the value. As a result certain characters are being left out
and it is ending up with a value less than the one it uses to evaluate. In addition to that we are working with floats. Floating point numbers cannot accuratly hold 
decimal place values such as the one we're given (they can usually hold about 7), so even if the char was big enough for the number it still wouldn't be percise enough. So we can't input the numerical value
which will clear the level. However since we are dealling with floats, we have the option to set the float equal to nan (not a number). The buffer will be big
enough to hold that, the float will be able to accuratly store it, and it is neither greater than or less than 37.35928559 so it should clear the level.

```
root@tux:/Hackery/cr@ck_th3_c0de/hole/h1# ./h1
nan
Oh wait, there might be a bottom to this. Level cleared
```

And just like that, we pwned the challenge. Now to patch it.

Since the fact that floating point numbers can be nan means that we can't really change that. However we can check for it.

```
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char buf0[10];
	double var0;
		
	fgets(buf0, sizeof(buf0), stdin);
	var0 = atof(buf0);
	printf("%f\n", var0);
	if (var0 < 37.35928559)
	{
		printf("Too low just like you're chances of reaching the bottom.\n");
		exit(0);
	}

	if (var0 > 37.35928559)
  {
    printf("To high just like your hopes of reaching the bottom.\n");
    exit(0);
  }
		if (var0 != var0)
	{
		printf("Someone's getting creative\n");
		exit(0);
	}
	

	else 
	{

		printf("Oh wait, there might be a bottom to this. Level cleared\n");
	}

}
```

You see in my code that I added in my patch an extra if then statment. For doubles and floats, if they are not equal to themselces then they
are nan. This is one way of checking for them. Also you will see that I changed the data value from float to double, since double's can hold more accurate decimal places however it still isn't enough to solve the challenge.

```
root@tux:/Hackery/cr@ck_th3_c0de/hole/h1# ./h1_secure 
37.35928559
37.359285
Too low just like you're chances of reaching the bottom.
root@tux:/Hackery/cr@ck_th3_c0de/hole/h1# ./h1_secure 
nan
nan
Someone's getting creative
```

And just like that, we patched the binary.

