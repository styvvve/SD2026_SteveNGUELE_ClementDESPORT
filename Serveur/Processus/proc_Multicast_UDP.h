#ifndef PROC_MULTICAST_UDP_H
#define PROC_MULTICAST_UDP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/wait.h>


void proc_Multicast_UDP(int *pipe_jeu_multicast);
#endif