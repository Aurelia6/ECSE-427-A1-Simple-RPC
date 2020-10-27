# .DEFAULT_GOAL=all

CC=gcc
CFLAGS=-fsanitize=signed-integer-overflow -fsanitize=undefined -g -std=gnu99 -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

FRONTEND=frontend
BACKEND=backend

rpc: a1_lib.c frontend.c  backend.c
	$(CC) -o $(FRONTEND) $(CFLAGS) frontend.c a1_lib.c
	$(CC) -o $(BACKEND) $(CFLAGS) backend.c a1_lib.c

clean:
	rm -rf $(FRONTEND) $(BACKEND)

