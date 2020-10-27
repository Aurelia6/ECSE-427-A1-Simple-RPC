9 files are provided:
a1_lib.c
a1_lib.h
backend.c
backend.h
frontend.c
frontend.h
Makefile
Message.h
README.txt


When using the program:
add, multiply, divide, sleep, factorial, exit and quit can be called.

- Adding more than 3 arguments for add, multiply and divide will print 
an error message but will do the calculations using the second and third arguments.
- Adding more than 2 arguments for sleep and factorial will print 
an error message but will do the calculations using the second argument.

This code has a limit of 10 children.

If the command "quit" is called, it will close the server with a terminated signal as well as the user in which the command has been written. If other clients were open at the same time, they will not be shutdown, but writing any command will shut them down.
