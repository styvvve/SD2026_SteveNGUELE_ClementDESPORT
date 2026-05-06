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

#include "structure_jeu.h"



void configurePartie(char config_partie[1024]){
    int num=0;
    struct_jeu jeu;
    
    /*

    typedef struct struct_jeu {
        int level;
        int mode;
        int player[100];
        int vie[100];
        int temps_impartie;
        int nbr_taupe;  
    }struct_jeu;

    */


    // https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html
    // Pour séparer les caractères (pour la configuration)
    char *p = strtok(config_partie,"|");
    while (p != NULL){
        switch (num){
            case 0:
                jeu.level=atoi(p);
                break;
            
            case 1:
                jeu.mode=atoi(p);
                break;

            case 2:
                // ToDo player[100]
                break;

            case 3:
                // ToDo vie[100]
                break;

            case 4:
                jeu.temps_impartie=atoi(p);
                break;

            case 5:
                jeu.nbr_taupe=atoi(p);
                break;

            default :
                perror("Erreur dans le switch. Trop d'argument");
                break;
        }
        
        num++;
        p = strtok(NULL, "|");
    }
}