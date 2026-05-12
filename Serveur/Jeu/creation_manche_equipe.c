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
#include <stdbool.h>
#include "structure_jeu.h"
#include "../structure_partage.h"

#include "creation_manche_equipe.h"


//Crée une seule manche pour les deux modes (ID si c'est en battle royal. ID_Equipe si c'est en équipe)
char *creation_d_une_manche(int equipe, char *taupe, struct_jeu jeu){
    char *manche = malloc(100);
    snprintf(manche,100,"%d||%s||%d",equipe,taupe,jeu.temps_imparti);
    /* Exemple : 1||              _____
            \"_   _"/
            |(*)-(*)|
          ./  " O "  \.
     ---"(((---------)))"---||4*/

     // 1 == Equipe ; 4 == Seconde impartie
     return manche;
}


void creations_manches_equipe(struct_jeu jeu){
     for (int i=0; i<jeu.manche;i++){
          
     }
}


/*
//Fonction qui renvoie un tableau deux de tableau de 50 int. exemple : tab[[1,2,3][4,5,6]]
void creation_equipe(struct_partage *variablePartage){
     int joueur[100];
     int ind_tab=0;
     for (int i=0;i<100;i++){
          if (variablePartage->joueurConnecte[i]==true){
               joueur[ind_tab]=i;
               ind_tab++;
          }
     }
     //Cree 2 equipe
     //Cree une variable 'EQUIPE_COURANTE' (pour connaitre dans quelle equipe mettre)


     //Renvoyer les deux équipes
}

*/