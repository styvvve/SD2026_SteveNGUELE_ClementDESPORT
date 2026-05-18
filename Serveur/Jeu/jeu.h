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
#include "../structure_partage.h"

void ajoute_joueur_equipe(struct_partage *variablePartage,int id);
void supprime_joueur_equipe(struct_partage *variablePartage,int id);

void repond_juste(struct_partage *variablePartage,int id);

void repond_faux(struct_partage *variablePartage,int id);


bool verifeConfiguration(struct_jeu jeu);


void configurePartie(char config_partie[1024]);

int nombreDeJoueurConnecter(struct_partage variablePartage);

bool verifeJoueurSup2(struct_partage variablePartage);

void lancerPartieEquipe(struct_partage *variablePartage,int *pipe_jeu_multicast,int *pipe_tcp_admin);

void lancerPartie(struct_partage *variablePartage,int *pipe_jeu_multicast, int *pipe_tcp_admin);

#endif
