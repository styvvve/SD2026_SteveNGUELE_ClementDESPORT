#ifndef JEU_H
#define JEU_H

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


void configure_partie(char config_partie[1024]);

int nombreDeJoueurConnecter(bool *joueurconnecte);

#endif
