/**
 *  @author: Aurelia Haas
 *           260787990
 *  Assignment 1 - Operating Systems
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

#include "a1_lib.h"
#include "Message.h"
#include "frontend.h"


int main(int argc, char *argv[])
{
  // set up the host IP and Port while compiling
  char host_ip[20];
  int host_port;
  sscanf(argv[1], "%s", host_ip);
  sscanf(argv[2], "%d", &host_port);

  // create the socket and the necessary variables to send the message from the client to the user
  int sockfd;
  char user_input[BUFSIZE] = {0};
  char server_msg[BUFSIZE] = {0};

  // connect to server
  if (connect_to_server(host_ip, host_port, &sockfd) < 0)
  {
    fprintf(stderr, "oh no\n");
    return -1;
  }

  // the client is active until we quit or exit
  while ((strcmp(user_input, "quit\n")) && (strcmp(user_input, "exit\n")))
  {
    memset(user_input, 0, sizeof(user_input));
    memset(server_msg, 0, sizeof(server_msg));

    // read user input from command line
    printf(">>  ");
    if (fgets(user_input, BUFSIZE, stdin)){} // if to avoid a warning
    
    // call parse function in order to parse the user input 
    parse(user_input);

    // create memory in order to send the message to the server
    char buffer[BUFSIZE];
    memcpy(&buffer, &message, BUFSIZE);
    send_message(sockfd, buffer, BUFSIZE);
    // receive a message from the server
    ssize_t byte_count = recv_message(sockfd, server_msg, sizeof(server_msg));
    if (byte_count <= 0)
    {
      break;
    }
    // print the message from the server
    printf("%s\n", server_msg);
  }
  return 0;
}

// parse the input command line
void parse(char *msg)
{
  // reset the commands and arguments from the struct
  message.cmd[0] = '\0';
  message.arg1 = 0;
  message.arg2 = 0;

  // break command line into tokens
  char *token = strtok(msg, " ");

  // set the command and arguments to the right place in the struct
  for (int i = 0; token != NULL; i++)
  {
    if (i == 0)
    {
      strcpy(message.cmd, token);
    }
    else if (i == 1)
    {
      message.arg1 = atof(token); // change the string to double
    }
    else if (i == 2 && (strcmp(message.cmd, "sleep") == 0 || strcmp(message.cmd, "factorial") == 0))
    {
      printf("Too many arguments, the last argument(s) will not be taken into consideration\n");
    }
    else if (i == 2)
    {
      message.arg2 = atof(token); // change the string to double
    }
    else if (i >= 3)
    {
      printf("Too many arguments, the last argument(s) will not be taken into consideration\n");
      break;
    }
    token = strtok(NULL, " ");
  }
}