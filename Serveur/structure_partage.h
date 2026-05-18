#ifndef STRUCTURE_PARTAGE_H
#define STRUCTURE_PARTAGE_H
#include <stdbool.h>


typedef struct struct_jeu {
    int level;
    int mode;
    int player[100];
    int vie[100];
    int manche;
    int temps_imparti;
    int nbr_taupe;  
}struct_jeu;

typedef struct equipes{
    int score_1;
    int score_2;
    int nbr_joueur_1;
    int nbr_joueur_2;
    int equipe_1[50];
    int equipe_2[50];
}equipes;


typedef struct struct_partage{
    bool joueurConnecte[100];
    bool jeu;
    struct_jeu jeu_config;
    equipes jeu_equipes;
} struct_partage;



#endif