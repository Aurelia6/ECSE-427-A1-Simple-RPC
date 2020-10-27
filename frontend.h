/**
 *  @author: Aurelia Haas
 *           260787990
 *  Assignment 1 - Operating Systems
 */

#ifndef FRONTEND_H_
#define FRONTEND_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

#include "a1_lib.h"
#include "Message.h"

#define BUFSIZE 1024

message_t message;

//function
void parse(char *msg); //parse the command line into a struct
/**
 *  Parse the command line into a struct.
 *
 *  @params:
 *    *msg:    The address of the command line/input from the user.
 */


#endif /* FRONTEND_H_ */
