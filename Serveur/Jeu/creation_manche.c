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

//Crée une seule manche pour les deux modes (ID si c'est en battle royal. ID_Equipe si c'est en équipe)
char *creation_d_une_manche(int equipe, char *taupe, struct_jeu jeu){
    char *manche = malloc(100);
    snprintf(manche,100,"%d||%s||%d",equipe,taupe,jeu.temps_impartie);
    /* Exemple : 1||              _____
            \"_   _"/
            |(*)-(*)|
          ./  " O "  \.
     ---"(((---------)))"---||4*/

     // 1 == Equipe ; 4 == Seconde impartie
     return manche;
}

