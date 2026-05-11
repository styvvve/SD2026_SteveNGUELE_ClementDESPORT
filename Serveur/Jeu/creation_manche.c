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

//Cree une seule manche pour le mode equipe
void creation_manche_equipe(int equipe, char *taupe, struct_jeu jeu){
    char manche[100];
    snprintf(manche,sizeof(manche)/sizeof(char),"%s||%s||%d",equipe,taupe,jeu.temps_impartie);
    /* Exemple : 1||              _____
            \"_   _"/
            |(*)-(*)|
          ./  " O "  \.
     ---"(((---------)))"---||4*/

     // 1 == Equipe ; 4 == Seconde impartie
}

