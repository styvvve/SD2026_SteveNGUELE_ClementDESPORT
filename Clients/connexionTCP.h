#ifndef CONNEXION_TCP_H
#define CONNEXION_TCP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

/*----------------CONSTANTES---------------*/
/**
 * @brief the max size of the buff
 */
#define TAILLEBUFF 1024


/**
 * @file connexionTCP.h
 * @brief connection between server and a single player
 * @version 1.0
 */


/**
 * @brief Create a socket for TCP communication
 * @return the sock id
 * @return -1 if an error occured
 */
int socket_TCP(); 

/**
 * @brief Establish the connection between the player and the server
 * @param socket
 * @param server_name 
 * @param server_port
 * @return 0 if the connection OK and other if anything going wrong
 */
int connexion_TCP(int socket, char* server_name, int server_port); 

/**
 * @brief Test the connection each time
 * @return 0 if is ok
 * @return 1 if is not
 */
int test_connection_TCP(int socket); 

#endif