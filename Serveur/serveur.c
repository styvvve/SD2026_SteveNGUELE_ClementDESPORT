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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>


//Pipe
#include <fcntl.h>

#include "Admin/gererAdmin.h"
#include "Socket/socket.h"
#include "Joueur/gererJoueur.h"
#include "Jeu/jeu.h"

#include "Processus/proc_Multicast_UDP.h"
#include "Processus/proc_Admin_UDP.h"
#include "Processus/proc_TCP.h"

#include "structure_partage.h"


#define TAILLEBUF 100


void fermeture_processus(){
    fermeture_proc_admin();
    fermeture_proc_multi();
    fermeture_proc_tcp();
}

int main(int argc, char* argv[]) {

    /* Creation Pipe */
    int pipe_tcp_admin[2];
    int pipe_jeu_multicast[2];
    int pipe_tcp_jeu[2];


    if (pipe(pipe_tcp_admin) == -1){
        perror("Erreur dans la création de pipe");
        exit(1);
    }

    if (pipe(pipe_jeu_multicast) == -1){
        perror("Erreur dans la création de pipe");
        exit(1);
    }

    if (pipe(pipe_tcp_jeu) == -1){
        perror("Erreur dans la création de pipe");
        exit(1);
    }

    /*  Permet de crée une pipe non bloquant (read : non bloquant)
        Pour que le processus (gererAdmin) lis en continue pour voir
        Si il y a des nouveaux clients */

    //https://www.geeksforgeeks.org/c/non-blocking-io-with-pipes-in-c/


    if (fcntl(pipe_tcp_admin[0], F_SETFL, O_NONBLOCK) < 0){
        perror("Erreur dans la création de la pipe non bloquant.");
        exit(2);
    }

    if (fcntl(pipe_jeu_multicast[0], F_SETFL, O_NONBLOCK) < 0){
        perror("Erreur dans la création de la pipe non bloquant.");
        exit(2);
    }


    if (fcntl(pipe_tcp_jeu[0], F_SETFL, O_NONBLOCK) < 0){
        perror("Erreur dans la création de la pipe non bloquant.");
        exit(2);
    }

    // Mémoire partagé
    //https://www.ibm.com/docs/fr/aix/7.3.0?topic=memory-creating-shared-segment-shmat-subroutine
    //https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmget.html?utm_source=copilot.com
    /** 
    IPC_PRIVATE : Pas besoin d'ID pour les fils
    IPC_CREAT : Pour créer le segment de partage
    0666 : Lecture et Ecriture pour chaque processus
    **/
    int shm_id = shmget(IPC_PRIVATE, sizeof(struct_partage), IPC_CREAT | 0666);

    if (shm_id == -1) {
        perror("Erreur dans la mémoire partagée");
        exit(EXIT_FAILURE);
    }

    /** 
    shmat : Pour mettre le tableau dans la mémoire partagé
    shm_id : ID
    NULL et 0 : Pour choisir automatiquement l'adresse de stockage et pas de restriction
    **/
    


    struct_partage *variablePartage = (struct_partage *)shmat(shm_id, NULL, 0);

    // Initialisation du tableau des joueurs connecte

    for (int i=0;i<100;i++){
        variablePartage->joueurConnecte[i]=false;
    }

    /*variablePartage->joueurConnecte[0]=true;
    variablePartage->joueurConnecte[8]=true;
    variablePartage->joueurConnecte[15]=true;
    variablePartage->joueurConnecte[4]=true;
    variablePartage->joueurConnecte[3]=true;
    variablePartage->joueurConnecte[59]=true;
    */
    
    /*variablePartage->jeu_config.manche = 2;
    variablePartage->jeu_config.nbr_taupe = 2;
    variablePartage->jeu_config.level = 1;
    variablePartage->jeu_config.mode = 1;
    variablePartage->jeu_config.temps_imparti=5;*/



    //lancerPartieEquipe(variablePartage);

    

    pid_t pid_proc_Admin_UDP = fork();
    if (pid_proc_Admin_UDP==0){
        proc_Admin_UDP(pipe_tcp_admin,pipe_jeu_multicast,variablePartage,argv);
        exit(0);
    }


    pid_t pid_proc_TCP = fork();
    if (pid_proc_TCP==0){
        proc_TCP(pipe_tcp_admin,variablePartage,argv);
        exit(0);
    }

    pid_t pid_proc_Multicast_UDP = fork();
    if (pid_proc_Multicast_UDP==0){
        proc_Multicast_UDP(pipe_jeu_multicast);
        exit(0);
    }

    while(1){}

}