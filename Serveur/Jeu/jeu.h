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
#include "../structure_partage.h"


bool verifeConfiguration(struct_jeu jeu);

void configure_partie(char config_partie[1024]);

int nombreDeJoueurConnecter(struct_partage variablePartage);

bool verifeJoueurSup2(struct_partage variablePartage);

#endif
