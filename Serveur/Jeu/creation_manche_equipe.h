#ifndef CREATION_MANCHE_H
#define CREATION_MANCHE_H

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

#include "../structure_partage.h"
#include "structure_equipe.h"





char *creation_d_une_manche(int equipe, char *taupe, struct_partage *variablePartage);

void creations_manches_equipe(struct_jeu jeu);

struct_equipe creation_equipe(struct_partage *variablePartage);

void shuffle(int nbr, int joueur[nbr]);

#endif
