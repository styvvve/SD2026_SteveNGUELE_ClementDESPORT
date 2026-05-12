#ifndef GERER_ADMIN_H
#define GERER_ADMIN_H

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
#include <stdbool.h>

#include "../structure_partage.h"

void gererAdmin(int socket,int *pipe_tcp_admin, struct_partage *variablePartage); 

#endif