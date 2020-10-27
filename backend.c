/**
 *  @author: Aurelia Haas
 *           260787990
 *  Assignment 1 - Operating Systems
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "a1_lib.h"
#include "Message.h"
#include "backend.h"


int main(int argc, char *argv[])
{
  // set up the host IP and Port while compiling
  char host_ip[20];
  int host_port;
  sscanf(argv[1], "%s", host_ip);
  sscanf(argv[2], "%d", &host_port);

  // create the socket and the necessary variables to receive and send the message to the client
  int sockfd, clientfd, newSockfd;
  char buffer[BUFSIZE];
  char result[BUFSIZE];

  // fork
  pid_t pid;
  int children = 0;

  // create server
  if (create_server(host_ip, host_port, &sockfd) < 0)
  {
    fprintf(stderr, "oh no\n");
    return -1;
  }

  while (children < 10)
  {
    // accept a new connection
    newSockfd = accept_connection(sockfd, &clientfd);
    if (newSockfd < 0)
    {
      fprintf(stderr, "oh no\n");
      return -1;
    }
    // increment children number
    children++;
    printf("Connection accepted from %s : %d – Client %d\n", host_ip, host_port, children);

    // starts a new process/child
    if ((pid = fork()) == 0)
    {
      while (strcmp(buffer, "quit\n"))
      {
        // reset the result that will be send to the client
        result[0] = '\0';

        // create a struct and a memory in order to receive the message from the client
        memset(buffer, 0, sizeof(buffer));
        message_t *msg;
        ssize_t byte_count = recv_message(clientfd, buffer, BUFSIZE);
        msg = (message_t *)&buffer;

        if (byte_count <= 0)
        {
          break;
        }

        // Calculator
        if (strcmp(msg->cmd, "add") == 0)
        {
          sprintf(result, "%d", addInts((int)(msg->arg1), (int)(msg->arg2)));
        }
        else if (strcmp(msg->cmd, "multiply") == 0)
        {
          sprintf(result, "%d", multiplyInts((int)(msg->arg1), (int)(msg->arg2)));
        }
        else if (strcmp(msg->cmd, "divide") == 0)
        {
          sprintf(result, "%f", divideFloats(msg->arg1, msg->arg2));
          if (strcmp(result, "-1.000000") == 0)
          {
            strcpy(result, "Error: Division by zero");
          }
        }
        else if (strcmp(msg->cmd, "sleep") == 0)
        {
          sleep((int)(msg->arg1));
          strcpy(result, "\r");
        }
        else if (strcmp(msg->cmd, "factorial") == 0)
        {
          sprintf(result, "%ld", factorial(msg->arg1));
        }
        else if (strcmp(msg->cmd, "exit\n") == 0)
        {
          printf("Client %d left\n", children);
          strcpy(result, "Goodbye!");
        }
        else if (strcmp(msg->cmd, "quit\n") == 0)
        {
          strcpy(result, "Goodbye!");
          send_message(clientfd, result, strlen(result));
          kill(pid, SIGTERM); // kill all the active children
          exit(1); // exit from the server so we can't reconnect from a client
        }
        else // command not found
        {
          char print[] = "Error: Command '";
          strcat(print, msg->cmd);
          removeChar(print, '\n');
          strcat(print, "' not found");
          strcpy(result, print);
        }
        send_message(clientfd, result, strlen(result));
      }
      return 0;
    } 
  }
  return 0;
}



// functions
int addInts(int a, int b)
{
  // add two integers
  return a + b;
}


int multiplyInts(int a, int b)
{
  // multiple two integers
  return a * b;
}


double divideFloats(float a, float b)
{
  // divide float numbers (report divide by zero error)
  if (b == 0)
  {
    return -1;
  }
  return (double)(a / b);
}


uint64_t factorial(int x)
{
  // return factorial x
  if (x == 0)
  {
    return 1;
  }
  return x * factorial(x - 1);
}


void removeChar(char *str, char toRemove)
{
  // remove useless/unecessary characters
  char *src, *dst;
  for (src = dst = str; *src != '\0'; src++)
  {
    *dst = *src;
    if (*dst != toRemove)
      dst++;
  }
  *dst = '\0';
}
