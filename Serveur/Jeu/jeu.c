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

#define NOMBRE_MAX_JOUEUR 100




//Verifie si la configuration est correcte ou pas
bool verifeConfiguration(struct_jeu jeu){
    if (jeu.level<=0 && jeu.level>3){
        return false;
    }
    if (jeu.mode<=0 && jeu.mode>2){
        return false;
    }
    if (jeu.nbr_taupe<0){
        return false;
    }
    if(jeu.temps_impartie<=0){
        return false;
    }
    if(jeu.mode==2 && jeu.manche%2!=0){
        return false;
    }
    return true;
}

//Configure la partie en modifiant/créant une structure Jeu
void configurePartie(char config_partie[1024],bool *joueurConnecte){
    int num=0;
    struct_jeu jeu;
    
    /*

    typedef struct struct_jeu {
        int level;
        int mode;
        int manche;
        int player[100];
        int vie[100];
        int temps_impartie;
        int nbr_taupe;  
    }struct_jeu;

    */


    
    /** 
     * @see https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html
    */
    // Pour séparer les caractères (pour la configuration)

    char *p = strtok(config_partie,"|");


    // Exemple de chaine à recevoir : 1|2|3|5|18|6
    
    // Ajouter tout les joueurs connecté
    for (int i=0;i<100;i++){
        if (joueurConnecte[i]==true){
            jeu.player[i]=true;
        }
    }

    while (p != NULL){
        switch (num){
            case 0:
                jeu.level=atoi(p);
                break;
            
            case 1:
                jeu.mode=atoi(p);
                break;

            case 2:
                for (int i;i<100;i++){
                    if (jeu.player[i]==true){
                        jeu.vie[i]=atoi(p);
                    }
                }
                break;

            case 3:
                jeu.temps_impartie=atoi(p);
                break;

            case 4:
                jeu.nbr_taupe=atoi(p);
                break;

            case 5:
                jeu.manche=atoi(p);
            default :
                perror("Erreur dans le switch. Trop d'argument");
                break;
        }
        
        num++;
        p = strtok(NULL, "|");
    }
    if (verifeConfiguration(jeu)){
        printf("test");
        //ToDo la suite
    }
}






//Compte le nombre exacte de joueur connecte (Joueur + Spectateur)
int nombreDeJoueurConnecter(bool *joueurconnecte){
    int nbrConnecte=0;
    for (int i=0;i<NOMBRE_MAX_JOUEUR;i++){
        if (joueurconnecte[i]==true){
            nbrConnecte++;
        }
    }
    return nbrConnecte;
}

//Verifie si il y a au moins 2 joueurs connecte
bool verifeJoueurSup2(bool *joueurconnecte){
    if (nombreDeJoueurConnecter(joueurconnecte)>=2){
        return true;
    }
    else{
        return false;
    }
}