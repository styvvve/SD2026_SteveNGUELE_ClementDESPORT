#ifndef GERER_JOUEUR_H
#define GERER_JOUEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <netdb.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <errno.h> 
#include <string.h> 
#include <limits.h>


void gererJoueur(int socket,int id_joueur,int *pipe_tcp_admin); 

#endif
