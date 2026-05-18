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

#include "creation_manche_equipe.h"
#include "../structure_partage.h"
#include "structure_equipe.h"


#define NOMBRE_MAX_JOUEUR 100




//Verifie si la configuration est correcte pour le mode équipe
bool verifeConfiguration_equipe(struct_partage *variablePartage){
    if (variablePartage->jeu_config->level<=0 || variablePartage->jeu_config->level>3){
        return false;
    }
    if (variablePartage->jeu_config->mode==2){
        return false;
    }
    if (variablePartage->jeu_config->nbr_taupe<0){
        return false;
    }
    if(variablePartage->jeu_config->temps_imparti<=0){
        return false;
    }
    if(variablePartage->jeu_config->manche%2!=0){
        return false;
    }
    return true;
}

//Verifie si la configuration est correcte pour le mode battle royal
bool verifeConfiguration_battle_royal(struct_partage *variablePartage){
    if (variablePartage->jeu_config->level  <=0 || variablePartage->jeu_config->level>3){
        return false;
    }
    if (variablePartage->jeu_config->mode==1){
        return false;
    }
    if(variablePartage->jeu_config->temps_imparti<=0){
        return false;
    }
    if(variablePartage->jeu_config->manche<=0){
        return false;
    }
    return true;
}

//Configure la partie en modifiant/créant une structure Jeu
void configurePartie(char config_partie[1024],struct_partage *variablePartage){
    int num=0;
    
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

    if (variablePartage->jeu_config == NULL) {
        variablePartage->jeu_config = malloc(sizeof(struct_jeu));
    }


    
    /** 
     * @see https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html
    */
    // Pour séparer les caractères (pour la configuration)

    char *p = strtok(config_partie,"|");


    // Exemple de chaine à recevoir : config|  1  | 2  | 3 |      5      |   18    |    6     (sans espace bien sûr)
    //                                config|level|mode|vie|temps_imparti|nbr_taupe|nbr_manche
    
    // Ajouter tout les joueurs connecté
    for (int i=0;i<100;i++){
        if (variablePartage->joueurConnecte[i]==true){
            variablePartage->jeu_config->player[i]=true;
        }
    }

    while (p != NULL){
        switch (num){
            case 0:
                break;
            case 1:
                variablePartage->jeu_config->level=atoi(p);
                break;
            
            case 2:
                variablePartage->jeu_config->mode=atoi(p);
                break;

            case 3:
                for (int i=0;i<100;i++){
                    if (variablePartage->jeu_config->player[i]==true){
                        variablePartage->jeu_config->vie[i]=atoi(p);
                    }
                }
                break;

            case 4:
                variablePartage->jeu_config->temps_imparti=atoi(p);
                break;

            case 5:
                variablePartage->jeu_config->nbr_taupe=atoi(p);
                break;

            case 6:
                variablePartage->jeu_config->manche=atoi(p);
                break;
            default :
                perror("Erreur dans le switch. Trop d'argument");
                break;
        }
        num++;
        p = strtok(NULL, "|");
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

void lancerPartieEquipe(struct_partage *variablePartage,int *pipe_jeu_multicast){
    close(pipe_jeu_multicast[0]);

    srand( time( NULL ) );
    char *taupe =
    "         ________\n"
    "            \\_     _/\n"
    "            |(*)-(*)|\n"
    "          ./    O    \\.\n"
    "      ---(((---------)))---";





    struct_equipe equipes = creation_equipe(variablePartage);
    int tab_ordre[variablePartage->jeu_config->manche];
    int ind_tab_manche=0;
    for (int i=0;i<variablePartage->jeu_config->manche/2;i++){
        tab_ordre[i]=1;
    }
    for (int i=variablePartage->jeu_config->manche/2;i<variablePartage->jeu_config->manche;i++){
        tab_ordre[i]=2;
    }
    
    shuffle(variablePartage->jeu_config->manche,tab_ordre);

    char manche[variablePartage->jeu_config->manche*variablePartage->jeu_config->nbr_taupe][500];    
    for (int i=0;i<variablePartage->jeu_config->manche*variablePartage->jeu_config->nbr_taupe;i++){
        snprintf(manche[i],500," ");
    }


    for (int i=0;i<variablePartage->jeu_config->manche;i++){
        //EQUIPE 1
        if (tab_ordre[i]==1){
            shuffle(variablePartage->jeu_config->nbr_joueur_1,equipes.equipe_1);
            if (variablePartage->jeu_config->nbr_joueur_1 > variablePartage->jeu_config->nbr_taupe){
                for (int j=0;j<variablePartage->jeu_config->nbr_taupe;j++){
                    char *man=creation_d_une_manche(equipes.equipe_1[j],taupe,variablePartage);
                    snprintf(manche[ind_tab_manche],500,"%s",man);
                    ind_tab_manche++;
                    free(man);
                }
            }else{
                for (int j=0;j<variablePartage->jeu_config->nbr_joueur_1;j++){
                    char *man=creation_d_une_manche(equipes.equipe_1[j],taupe,variablePartage);
                    snprintf(manche[ind_tab_manche],500,"%s",man);
                    ind_tab_manche++;
                    free(man);
                }
            }


        }else{
            if (variablePartage->jeu_config->nbr_joueur_2 > variablePartage->jeu_config->nbr_taupe){
                shuffle(variablePartage->jeu_config->nbr_joueur_2,equipes.equipe_2);
                for (int j=0;j<variablePartage->jeu_config->nbr_taupe;j++){
                    char *man=creation_d_une_manche(equipes.equipe_2[j],taupe,variablePartage);
                    snprintf(manche[ind_tab_manche],500,"%s",man);
                    ind_tab_manche++;
                    free(man);
                }
            }else{
                for (int j=0;j<variablePartage->jeu_config->nbr_joueur_2;j++){
                    char *man=creation_d_une_manche(equipes.equipe_2[j],taupe,variablePartage);
                    snprintf(manche[ind_tab_manche],500,"%s",man);
                    ind_tab_manche++;
                    free(man);
                }
            }
        }
    }   

    /*
    for (int i=0;i<variablePartage->jeu_config->manche*variablePartage->jeu_config->nbr_taupe;i++){
        printf("[%d] = %s \n",i,manche[i]);
    }
    */         

    ind_tab_manche=0;
    for (int i=0;i<variablePartage->jeu_config->manche;i++){
        for (int j=0;j<variablePartage->jeu_config->nbr_taupe;j++){
            write(pipe_jeu_multicast[1],manche[ind_tab_manche],500);
            ind_tab_manche++;
            usleep(5000);
        }
        sleep(3);
    }
}