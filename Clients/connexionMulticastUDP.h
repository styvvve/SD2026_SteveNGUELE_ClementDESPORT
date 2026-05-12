#ifndef CONNEXIONMULTICASTUDP_H
#define CONNEXIONMULTICASTUDP_H
/**
 * @brief encapsulation of multicast functions here
 * @file connexionMulticastUDP.H
 */
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
 * @brief the ip address we use for the multicast
 */

#define IP_MULTICAST "226.1.2.3"

/**
 * @brief Create a socket for Multicast UDP connection
 * @return the sock id
 * @return -1 if an error occured
 */
int sock_multicastUDP(); 

/**
 * @brief Configurations, bind and join the multicast group via ip address and port pass to parameter
 * @param sock
 * @param addr
 * @param ip 
 * @param port
 * @param multicast_group
 * @return 0 if the connection to the multicast group is ok 
 * @return 1 if anything going wrong
 * @see https://gist.github.com/dksmiffs/d67afe6bda973d67752ae63dc49a7310
 * @see course slides
 * 
 * -enable mutiple instances to receive copies of the packets)
 * -bind to the proper port number 
 * -join the multicast group
 */
int join_muliticastGroup(int sock, struct sockaddr_in *addr, char *ip, int port, struct ip_mreq *multicast_group); 

/**
 * @brief Quit the multicast group
 * @param sock 
 * @param multicast_group 
 * @return 0 if is ok
 * @return anything else if something it failed
 */
int quit_multicastGroup(int sock, struct ip_mreq *multicast_group); 

/**
 * @brief This function receives a packet from the multicast group which she places on a string passed in parameter
 * @param sock
 * @param message
 * @return 0 if is ok
 * @return 1 if is not
 */
int receive_message_from_multicastGroup(int sock, char *message); 


#endif