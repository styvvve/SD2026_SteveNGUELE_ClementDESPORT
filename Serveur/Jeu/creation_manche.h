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


#include "structure_jeu.h"



void creation_manche_equipe(int equipe, char *taupe, struct_jeu jeu);