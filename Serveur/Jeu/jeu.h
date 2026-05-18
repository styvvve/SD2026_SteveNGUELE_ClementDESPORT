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

//Permet d'ajouter un nouveau joueur à une équipe
void ajoute_joueur_equipe(struct_partage *variablePartage,int id);


//Permet de supprimer un joueur d'une équipe
void supprime_joueur_equipe(struct_partage *variablePartage,int id);


//Fonction qui permet de faire +1 point à l'équipe du joueur
void repond_juste(struct_partage *variablePartage,int id);


//Fonction qui permet de faire -1 point à l'équipe du joueur
void repond_faux(struct_partage *variablePartage,int id);


//Fonction pour verifier une configuration de jeu 
bool verifeConfiguration(struct_jeu jeu);


//Permet de configurer une partie à l'aide des données qu'envoie l'administrateur
void configurePartie(char config_partie[1024],struct_partage *variablePartage);


//Permet de compter le nombre de joueur connecte actuellement
int nombreDeJoueurConnecter(struct_partage variablePartage);


//Permet de verifier si il y a plus de 2 joueur
bool verifeJoueurSup2(struct_partage variablePartage);


//Fonction qui lance une partie en mode EQUIPE
void lancerPartieEquipe(struct_partage *variablePartage,int *pipe_jeu_multicast,int *pipe_tcp_admin);


//Fonction qui lance une partie en mode BATTLE ROYALE
void lancerPartieBattleRoyale(struct_partage *variablePartage, int *pipe_jeu_multicast, int *pipe_tcp_admin);


//Fonction qui lance une partie et regarde quelle mode à été selectionner par l'admin
void lancerPartie(struct_partage *variablePartage,int *pipe_jeu_multicast, int *pipe_tcp_admin);

#endif
