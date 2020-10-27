/**
 *  @author: Aurelia Haas
 *           260787990
 *  Assignment 1 - Operating Systems
 */

#ifndef BACKEND_H_
#define BACKEND_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "a1_lib.h"
#include "Message.h"

#define BUFSIZE 1024

// functions
int addInts(int a, int b);
/**
 *  Add two integers
 *
 *  @params:
 *    a:    The first integer.
 *    b:    The second integer.
 *  @return:    The sum of both integers as an integer.
 */

int multiplyInts(int a, int b); 
/**
 *  Multiple two integers
 *
 *  @params:
 *    a:    The first integer.
 *    b:    The second integer.
 *  @return:    The product of both integers as an integer.
 */

double divideFloats(float a, float b);
/**
 *  Divide two floats
 *
 *  @params:
 *    a:    The first float which is the dividend.
 *    b:    The second float which is the divisor.
 *  @return:    The division of both floats as a double or
 *              an error if the divisor is 0.
 */

uint64_t factorial(int x); // return factorial x
/**
 *  Calculation of the factorial
 *
 *  @params:
 *    x:    The integer that we want the factorial of.
 *  @return:    The factorial of x.
 */

void removeChar(char *str, char toRemove);
/**
 *  Remove useless or unecessary characters
 *
 *  @params:
 *    *str: The address of the char in which we want to remove a character.
 *    toRemove: The character(s) we want to remove.   
 */

#endif /* BACKEND_H_ */
