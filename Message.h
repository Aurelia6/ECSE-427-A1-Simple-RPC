/**
 *  @author: Aurelia Haas
 *           260787990
 *  Assignment 1 - Operating Systems
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#define CMD_LENGTH 20

typedef struct message_t{
    char cmd[CMD_LENGTH];
    double arg1;
    double arg2;
} message_t;

#endif //MESSAGE_H_