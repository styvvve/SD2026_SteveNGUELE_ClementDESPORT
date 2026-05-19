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




//Creation d'une manche à envoyer aux multicast
char *creation_d_une_manche(int equipe, char *taupe, struct_partage *variablePartage);

//Fonction qui permet de créé deux equipe équilibré
void creation_equipe(struct_partage *variablePartage);

//Mélange un tableau
void shuffle(int nbr, int joueur[nbr]);

#endif
