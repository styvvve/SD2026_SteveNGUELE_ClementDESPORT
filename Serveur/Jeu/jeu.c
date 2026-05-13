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

#define NOMBRE_MAX_JOUEUR 100




//Verifie si la configuration est correcte pour le mode équipe
bool verifeConfiguration_equipe(struct_jeu *jeu){
    if (jeu->level<=0 && jeu->level>3){
        return false;
    }
    if (jeu->mode==2){
        return false;
    }
    if (jeu->nbr_taupe<0){
        return false;
    }
    if(jeu->temps_imparti<=0){
        return false;
    }
    if(jeu->manche%2!=0){
        return false;
    }
    return true;
}

//Verifie si la configuration est correcte pour le mode battle royal
bool verifeConfiguration_battle_royal(struct_jeu *jeu){
    if (jeu->level<=0 && jeu->level>3){
        return false;
    }
    if (jeu->mode==1){
        return false;
    }
    if(jeu->temps_imparti<=0){
        return false;
    }
    if(jeu->manche<=0){
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


    // Exemple de chaine à recevoir : config|  1  | 2  | 3 |      5      |   18    |    6     (sans espace bien sûr)
    //                                config|level|mode|vie|temps_imparti|nbr_taupe|nbr_manche
    
    // Ajouter tout les joueurs connecté
    for (int i=0;i<100;i++){
        if (joueurConnecte[i]==true){
            jeu.player[i]=true;
        }
    }

    while (p != NULL){
        switch (num){
            case 0:
                break;
            case 1:
                jeu.level=atoi(p);
                break;
            
            case 2:
                jeu.mode=atoi(p);
                break;

            case 3:
                for (int i=0;i<100;i++){
                    if (jeu.player[i]==true){
                        jeu.vie[i]=atoi(p);
                    }
                }
                break;

            case 4:
                jeu.temps_imparti=atoi(p);
                break;

            case 5:
                jeu.nbr_taupe=atoi(p);
                break;

            case 6:
                jeu.manche=atoi(p);
                break;
            default :
                perror("Erreur dans le switch. Trop d'argument");
                break;
        }
        
        num++;
        p = strtok(NULL, "|");
    }
    if (verifeConfiguration_equipe(&jeu)){
        printf("Configuration mode équipe \n");
        //ToDo : faire la suite pour equipe
    }
    else if(verifeConfiguration_battle_royal(&jeu)){
        printf("Configuration mode battle royal \n");
        //ToDo : faire la suite pour battle royal
    }
}




//Compte le nombre exacte de joueur connecte (Joueur + Spectateur)
int nombreDeJoueurConnecter(struct_partage *variablePartage){
    int nbrConnecte=0;
    for (int i=0;i<NOMBRE_MAX_JOUEUR;i++){
        if (variablePartage->joueurConnecte[i]==true){
            nbrConnecte++;
        }
    }
    return nbrConnecte;
}

//Verifie si il y a au moins 2 joueurs connecte
bool verifeJoueurSup2(struct_partage *variablePartage){
    if (nombreDeJoueurConnecter(variablePartage)>=2){
        return true;
    }
    else{
        return false;
    }
}