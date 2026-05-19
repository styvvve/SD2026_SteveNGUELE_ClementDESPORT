#ifndef STRUCTURE_PARTAGE_H
#define STRUCTURE_PARTAGE_H
#include <stdbool.h>

//Structure de la configuration de la partie 
typedef struct struct_jeu {
    int level;         //Le niveau
    int mode;          //Le mode 
    int player[100];   //La liste des participants (tableau d'ID) (BATTLE ROYALE)
    int vie[100];      //Le nombre de vie des participants (BATTLE ROYALE)
    int manche;        //Le nombre de manche (EQUIPE)
    int temps_imparti; //Le temps pour cliquer sur la taupe
    int nbr_taupe;     //Le nombre de taupes qu'apparait (EQUIPE)
}struct_jeu;

typedef struct equipes{
    int score_1;        //Le score de l'équipe 1 (à l'instant T)
    int score_2;        //Le score de l'équipe 2 (à l'instant T)
    int nbr_joueur_1;   //Le nombre de joueurs dans l'équipe 1 (à l'instant T)
    int nbr_joueur_2;   //Le nombre de joueurs dans l'équipe 2 (à l'instant T)
    int equipe_1[50];   //Les joueurs (tableau d'ID) de l'équipe 1
    int equipe_2[50];   //Les joueurs (tableau d'ID) de l'équipe 1
}equipes;

typedef struct struct_partage{
    bool joueurConnecte[100];  //Les joueurs connecté (à l'instant T). ID == indices dans le tableau 
    bool jeu;                  //Booléen pour savoir si le jeu est en cours ou pas
    struct_jeu jeu_config;     
    equipes jeu_equipes;       
} struct_partage;

#endif