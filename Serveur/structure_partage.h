#ifndef STRUCTURE_PARTAGE_H
#define STRUCTURE_PARTAGE_H


typedef struct struct_jeu {
    int level;
    int mode;
    int player[100];
    int vie[100];
    int manche;
    int temps_imparti;
    int nbr_taupe;  
    int nbr_joueur_1;
    int nbr_joueur_2;
}struct_jeu;

typedef struct struct_partage{
    bool joueurConnecte[100];
    bool jeu;
    struct_jeu *jeu_config;
} struct_partage;



#endif