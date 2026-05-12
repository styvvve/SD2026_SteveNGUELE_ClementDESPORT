#ifndef STRUCTURE_JEU_H
#define STRUCTURE_JEU_H

typedef struct struct_jeu {
    int level;
    int mode;
    int player[100];
    int vie[100];
    int manche;
    int temps_imparti;
    int nbr_taupe;  
}struct_jeu;


#endif