Let's take a look at the code...
'''

'''

So we can see here the code has multiple vulnerabillities. It has two buffer overflow vulnerabillities discussed in the buf_ovf section. In addition to that it has a format string vulnerabillity. Let's take a look at this line of code.

'''

'''

As you can see here it is printing out the contents a buffer. Thing is, it is not formatted properley. So 
