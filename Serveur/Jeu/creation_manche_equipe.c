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
#include <time.h>

#include "../structure_partage.h"

#include "creation_manche_equipe.h"



//Crée une seule manche pour les deux modes (ID si c'est en battle royal. ID_Equipe si c'est en équipe)
char *creation_d_une_manche(int id, char *taupe, struct_partage *variablePartage){
    char *manche = malloc(500);
    snprintf(manche,500,"%d#%s#%d#%d",id,taupe,variablePartage->jeu_config.temps_imparti,variablePartage->jeu_config.level);
    /* Exemple : 1#              _____
            \"_   _"/
            |(*)-(*)|
          ./  " O "  \.
     ---"(((---------)))"---#4*/

     // 1 == id ; 4 == Seconde impartie
     return manche;
}


void shuffle(int nbr, int joueur[nbr]){
     int temp;
     int j;
     for (int i=nbr-1;i>1;i--){
          j= rand() % i;
          temp=joueur[i];
          joueur[i]=joueur[j];
          joueur[j]=temp;
     }
}

void creation_equipe(struct_partage *variablePartage){
     int joueur[100];
     int ind_tab=0;
     for (int i=0;i<100;i++){
          joueur[i]=-1;
     }
     for (int i=0;i<100;i++){
          if (variablePartage->joueurConnecte[i]==true){
               joueur[ind_tab]=i;
               ind_tab++;
          }
     }

     //shuffle les ID
     shuffle(ind_tab,joueur);

     //Cree une variable 'EQUIPE_COURANTE' (pour connaitre dans quelle equipe mettre)
     int equipe_courante=0;
     int ind_equipe_1=0;
     int ind_equipe_2=0;


     //Met dans les deux equipe
     for (int i=0;i<ind_tab;i++){
          if (equipe_courante==0){
               variablePartage->jeu_equipes.equipe_1[ind_equipe_1]=joueur[i];
               ind_equipe_1++;
               equipe_courante=1;
          } else if (equipe_courante==1){
               variablePartage->jeu_equipes.equipe_2[ind_equipe_2]=joueur[i];
               ind_equipe_2++;
               equipe_courante=0;
          } else{
               perror("Erreur dans creation_equipe, equipe_courant ");
               exit(0);
          }
     }

     variablePartage->jeu_equipes.nbr_joueur_1=ind_equipe_1;
     variablePartage->jeu_equipes.nbr_joueur_2=ind_equipe_2;
}