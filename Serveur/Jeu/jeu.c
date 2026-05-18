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


#define NOMBRE_MAX_JOUEUR 100

void ajoute_joueur_equipe(struct_partage *variablePartage,int id){
    if(variablePartage->jeu_equipes.nbr_joueur_1 <= variablePartage->jeu_equipes.nbr_joueur_2){
        variablePartage->jeu_equipes.equipe_1[variablePartage->jeu_equipes.nbr_joueur_1]= id;
        variablePartage->jeu_equipes.nbr_joueur_1++;
    }else{
        variablePartage->jeu_equipes.equipe_2[variablePartage->jeu_equipes.nbr_joueur_2]= id;
        variablePartage->jeu_equipes.nbr_joueur_2++;
    }
}


void supprime_joueur_equipe(struct_partage *variablePartage,int id){
    bool trouve=false;
    int ind=0;
    int temp;
    while(!trouve && ind<variablePartage->jeu_equipes.nbr_joueur_1){
        if (variablePartage->jeu_equipes.equipe_1[ind]==id){
            temp=variablePartage->jeu_equipes.equipe_1[variablePartage->jeu_equipes.nbr_joueur_1-1];
            variablePartage->jeu_equipes.equipe_1[variablePartage->jeu_equipes.nbr_joueur_1-1]=variablePartage->jeu_equipes.equipe_1[ind];
            variablePartage->jeu_equipes.equipe_1[ind]=temp;
            variablePartage->jeu_equipes.nbr_joueur_1--;
            trouve=true;
        }
        ind++;
    }
    ind=0;
    if (!trouve){
        while (!trouve && ind<variablePartage->jeu_equipes.nbr_joueur_2){
            if (variablePartage->jeu_equipes.equipe_2[ind]==id){
            temp=variablePartage->jeu_equipes.equipe_2[variablePartage->jeu_equipes.nbr_joueur_2-1];
            variablePartage->jeu_equipes.equipe_2[variablePartage->jeu_equipes.nbr_joueur_2-1]=variablePartage->jeu_equipes.equipe_2[ind];
            variablePartage->jeu_equipes.equipe_2[ind]=temp;
            variablePartage->jeu_equipes.nbr_joueur_2--;
            trouve=true;
        }
        ind++;
        }
    }
}

void repond_juste(struct_partage *variablePartage,int id){
    if (variablePartage->jeu_config.mode==2){
        bool trouve=false;
        int equipe;
        int ind=0;

        while (trouve!=true && variablePartage->jeu_equipes.equipe_1[ind]!=id){
            ind ++;
            if(variablePartage->jeu_equipes.equipe_1[ind]==id){
                trouve=true;
            }
        }
        if (trouve==true){
            variablePartage->jeu_equipes.score_1++;

        }else{
            variablePartage->jeu_equipes.score_2++;
        }
    }
    //else battleroyal
}

void repond_faux(struct_partage *variablePartage,int id){
    if (variablePartage->jeu_config.mode==1){
        bool trouve=false;
        int equipe;
        int ind=0;

        while (trouve!=true && variablePartage->jeu_equipes.equipe_1[ind]!=id){
            ind ++;
            if(variablePartage->jeu_equipes.equipe_1[ind]==id){
                trouve=true;
            }
        }
        if (trouve==true){
            variablePartage->jeu_equipes.score_1--;

        }else{
            variablePartage->jeu_equipes.score_2--;
        }
    }
    //else battleroyal
}


//Verifie si la configuration est correcte pour le mode équipe
bool verifeConfiguration_equipe(struct_partage *variablePartage){
    if (variablePartage->jeu_config.level<=0 || variablePartage->jeu_config.level>3){
        return false;
    }
    if (variablePartage->jeu_config.mode==2){
        return false;
    }
    if (variablePartage->jeu_config.nbr_taupe<0){
        return false;
    }
    if(variablePartage->jeu_config.temps_imparti<=0){
        return false;
    }
    if(variablePartage->jeu_config.manche%2!=0){
        return false;
    }
    return true;
}

//Verifie si la configuration est correcte pour le mode battle royal
bool verifeConfiguration_battle_royal(struct_partage *variablePartage){
    if (variablePartage->jeu_config.level  <=0 || variablePartage->jeu_config.level>3){
        return false;
    }
    if (variablePartage->jeu_config.mode==1){
        return false;
    }
    if(variablePartage->jeu_config.temps_imparti<=0){
        return false;
    }
    if(variablePartage->jeu_config.manche!=0){
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



    
    /** 
     * @see https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html
    */
    // Pour séparer les caractères (pour la configuration)

    char *p = strtok(config_partie,"|");



    // Exemple de chaine à recevoir : config|  1  | 2  | 3 |      5      |   18    |    6     (sans espace bien sûr)
    //                                config|level|mode|vie|temps_imparti|nbr_taupe|nbr_manche
    
    // Ajouter tout les joueurs connecté
    /*for (int i=0;i<100;i++){
        if (variablePartage->joueurConnecte[i]==true){
            variablePartage->jeu_config.player[i]=true;
        }
    }*/
    while (p != NULL){
        switch (num){
            case 0:
                break;
            case 1:

                variablePartage->jeu_config.level=atoi(p);
                break;
            
            case 2:

                printf("MODE :%d\n",atoi(p));
                variablePartage->jeu_config.mode=atoi(p);
                break;

            case 3:
                for (int i=0;i<100;i++){
                    if (variablePartage->jeu_config.player[i]==true){
                        variablePartage->jeu_config.vie[i]=atoi(p);
                    }
                }
                break;

            case 4:
                variablePartage->jeu_config.temps_imparti=atoi(p);
                break;

            case 5:
                variablePartage->jeu_config.nbr_taupe=atoi(p);
                break;

            case 6:
                variablePartage->jeu_config.manche=atoi(p);
                break;
            default :
                perror("Erreur dans le switch. Trop d'argument");
                break;
        }
        num++;
        p = strtok(NULL, "|");
    }
    printf("config fin\n");
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

void lancerPartieEquipe(struct_partage *variablePartage,int *pipe_jeu_multicast, int *pipe_tcp_admin){

    printf("TEST EQUIPE\n");

    variablePartage->jeu=true;

    printf("1 %d\n",variablePartage->jeu_equipes.score_1);

    variablePartage->jeu_equipes.score_1=0;
    printf("2 %d\n",variablePartage->jeu_equipes.score_1);

    variablePartage->jeu_equipes.score_2=0;

    char *taupe;

    srand( time( NULL ) );


    if (variablePartage->jeu_config.level==1){
        taupe =
        "            _________\n"
        "            \\_     _/\n"
        "            |(*)-(*)|\n"
        "          ./    O    \\.\n"
        "      ---(((---------)))---";
    }


    printf("TEST EQUIPE 2\n");


    creation_equipe(variablePartage);
    int tab_ordre[variablePartage->jeu_config.manche];
    int ind_tab_manche=0;
    char message_play[100];
    for (int i=0;i<variablePartage->jeu_config.manche/2;i++){
        tab_ordre[i]=1;
    }
    for (int i=variablePartage->jeu_config.manche/2;i<variablePartage->jeu_config.manche;i++){
        tab_ordre[i]=2;
    }
    
    shuffle(variablePartage->jeu_config.manche,tab_ordre);

    char manche[variablePartage->jeu_config.manche*variablePartage->jeu_config.nbr_taupe][500];    
    for (int i=0;i<variablePartage->jeu_config.manche*variablePartage->jeu_config.nbr_taupe;i++){
        snprintf(manche[i],500," ");
    }
    printf("TEST EQUIPE 3\n");


    for (int i=0;i<variablePartage->jeu_config.manche;i++){
        //EQUIPE 1
        printf("TEST manche 2 %d\n",i);

        if (tab_ordre[i]==1){
            if (variablePartage->jeu_equipes.nbr_joueur_1 > variablePartage->jeu_config.nbr_taupe){
                shuffle(variablePartage->jeu_equipes.nbr_joueur_1,variablePartage->jeu_equipes.equipe_1);
                for (int j=0;j<variablePartage->jeu_config.nbr_taupe;j++){
                printf("TEST 4 %d\n",j);


                    char *man=creation_d_une_manche(variablePartage->jeu_equipes.equipe_1[j],taupe,variablePartage);
                    write(pipe_jeu_multicast[1],man,500);
                    free(man);
                    usleep(50000);
                }
            }else{
                for (int j=0;j<variablePartage->jeu_equipes.nbr_joueur_1;j++){
                printf("TEST 7 %d\n",j);

                    char *man=creation_d_une_manche(variablePartage->jeu_equipes.equipe_1[j],taupe,variablePartage);
                    write(pipe_jeu_multicast[1],man,500);
                    free(man);
                    usleep(50000);
                }
            }


        }else{
            if (variablePartage->jeu_equipes.nbr_joueur_2 > variablePartage->jeu_config.nbr_taupe){
                shuffle(variablePartage->jeu_equipes.nbr_joueur_2,variablePartage->jeu_equipes.equipe_2);
                for (int j=0;j<variablePartage->jeu_config.nbr_taupe;j++){
                printf("TEST 5%d\n",j);

                    char *man=creation_d_une_manche(variablePartage->jeu_equipes.equipe_2[j],taupe,variablePartage);
                    write(pipe_jeu_multicast[1],man,500);
                    free(man);
                    snprintf(message_play,sizeof(message_play)/sizeof(char),"playerPlay|%d",variablePartage->jeu_equipes.equipe_1[j]);
                    //write(pipe_tcp_admin[1],message_play,strlen(message_play));
                    usleep(50000);
                }
            }else{
                for (int j=0;j<variablePartage->jeu_equipes.nbr_joueur_2;j++){
                printf("TEST 6 %d\n",j);

                    char *man=creation_d_une_manche(variablePartage->jeu_equipes.equipe_2[j],taupe,variablePartage);
                    write(pipe_jeu_multicast[1],man,500);
                    free(man);
                    snprintf(message_play,sizeof(message_play)/sizeof(char),"playerPlay|%d",variablePartage->jeu_equipes.equipe_2[j]);
                    //write(pipe_tcp_admin[1],message_play,strlen(message_play));
                    usleep(50000);
                }
            }
        }
        sleep(variablePartage->jeu_config.temps_imparti + 2);
    }   

    printf("FINI %d\n");

    variablePartage->jeu=false;
    

    //finishGame|score_1|score_2
    char message_fin[100];
    snprintf(message_fin,sizeof(message_fin)/sizeof(char),"finishGame|%d|%d",variablePartage->jeu_equipes.score_1,variablePartage->jeu_equipes.score_2);
    write(pipe_tcp_admin[1],message_fin,strlen(message_fin));

}


void lancerPartieBattleRoyale(struct_partage *variablePartage, int *pipe_jeu_multicast, int *pipe_tcp_admin){

    printf("TEST DEBUT BATTLE\n");

    close(pipe_jeu_multicast[0]);
    variablePartage->jeu=true;
    srand( time( NULL ) );
    char *taupe;
    if (variablePartage->jeu_config.level==1){
        taupe =
        "            _________\n"
        "            \\_     _/\n"
        "            |(*)-(*)|\n"
        "          ./    O    \\.\n"
        "      ---(((---------)))---";
    }


    int ind=0;
    char message_play[100];
    for (int i=0;i<100;i++){
        if (variablePartage->joueurConnecte[i]==true){
            variablePartage->jeu_config.player[ind]=i;
            //variablePartage->jeu_config.vie[i]=variablePartage->jeu_config;
        }
    }
    
    int nbr_vivant;
    while (variablePartage->jeu==true){
        nbr_vivant=0;
        int i=0;
        while(nbr_vivant<=1 && i<ind){
            if (variablePartage->jeu_config.vie[variablePartage->jeu_config.player[i]]>0){
                nbr_vivant++;
            }
            i++;
        }
        if (nbr_vivant==1){
            variablePartage->jeu=false;
            break;
        }

        int random=rand () % ind-1;
        if (variablePartage->joueurConnecte[variablePartage->jeu_config.player[random]]==true){
            char *man=creation_d_une_manche(variablePartage->jeu_config.player[random],taupe,variablePartage);
            write(pipe_jeu_multicast[1],man,500);
            free(man);
            snprintf(message_play,sizeof(message_play)/sizeof(char),"playerPlay|%d",variablePartage->jeu_config.player[random]);
            write(pipe_tcp_admin[1],message_play,strlen(message_play));
            usleep(50000);
        }
        sleep(variablePartage->jeu_config.temps_imparti + 2);
    }

    int gagnant;
    for (int i=0;i<ind;i++){
        if (variablePartage->jeu_config.vie[variablePartage->jeu_config.player[i]]>0){
            gagnant = variablePartage->jeu_config.player[i];
            break;
        }
    }

    //firstPlayer|id_joueur
    char message_fin[100];
    snprintf(message_fin,sizeof(message_fin)/sizeof(char),"firstPlayer|%d",gagnant);
    write(pipe_tcp_admin[1],message_fin,strlen(message_fin));

}

void lancerPartie(struct_partage *variablePartage,int *pipe_jeu_multicast, int *pipe_tcp_admin){
    if (variablePartage->jeu_config.mode==2){
        //Jeu equipe
        printf("TEST EQUIPE\n");
        lancerPartieEquipe(variablePartage,pipe_jeu_multicast,pipe_tcp_admin);
    }else{
        lancerPartieBattleRoyale(variablePartage,pipe_jeu_multicast,pipe_tcp_admin);
    }
}