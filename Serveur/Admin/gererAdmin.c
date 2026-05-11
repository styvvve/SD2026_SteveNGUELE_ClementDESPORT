#include "gererAdmin.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <stdbool.h>

#include "../Jeu/jeu.h"

#define TAILLEBUF 100


/*bool testConnectionAdmin(int socket, int lg,struct sockaddr_in *addr_admin){
    char message[100];
    char message_recue[100];
    int nb_octets_admin;
    char buffer[TAILLEBUF]; 
    int a;

    snprintf(message,sizeof(message)/sizeof(char),"test");
    a=sendto(socket, message, strlen(message)+1, 0,(struct sockaddr*)addr_admin, lg);
    if (a==-1){
        perror("Test t ");
    }
    usleep(50000);
    nb_octets_admin = recvfrom(socket, buffer, TAILLEBUF, 0,(struct sockaddr *)addr_admin, &lg);
    if (nb_octets_admin > 0){
        memcpy(message_recue, buffer, nb_octets_admin);
        printf("Test : %s\n", message_recue);
        return true;
    }
    else {
        return false;
    }
}*/

void gererAdmin(int socket,int *pipe_tcp_admin, bool *joueurconnecte) {
    /*
    int nbrConnecte;

    while(1){
        nbrConnecte=nombreDeJoueurConnecter(joueurconnecte);
        printf("Joueur connecte à l'instant : %d \n",nbrConnecte);
        usleep(700000);
    }
    */

    struct timeval temps_select;


    temps_select.tv_sec=2;
    temps_select.tv_usec=0;


    fd_set rfds;

    int nb_octets_admin;
    socklen_t lg;
    char buffer[TAILLEBUF]; 

    int nread;
    char message_recu_pipe[100];

    char message_recu_configuration_partie[1024];
    


    // adresse de la socket coté admin
    static struct sockaddr_in addr_admin;
    struct hostent *host_admin;
    // descripteur de la socket locale pour l'UDP admin

    lg = sizeof(struct sockaddr_in); 


    nb_octets_admin = recvfrom(socket, buffer, TAILLEBUF, 0,(struct sockaddr *)&addr_admin, &lg);
    if (nb_octets_admin == -1) {
        perror("erreur réception paquet");
        exit(1);
    }


    host_admin = gethostbyaddr(&(addr_admin.sin_addr), sizeof(long), AF_INET);
    if (host_admin == NULL) {
        perror("erreur gethostbyaddr");
        exit(1);
    }



    while (1){
        //Met à zero l'ensemble de "recherche" du select
        FD_ZERO(&rfds);
        //Ajoute la socket à surveiller 
        FD_SET(socket, &rfds);

        char message[100];
        char message_recue[100];
        int nb_octets_admin;
        char buffer[TAILLEBUF]; 
        int a;

        snprintf(message,sizeof(message)/sizeof(char),"test");
        a=sendto(socket, message, strlen(message)+1, 0,(struct sockaddr*)&addr_admin, lg);
        if (a==-1){
            perror("Test t ");
        }
        usleep(500000);
        if (select(socket + 1, &rfds,NULL,NULL,&temps_select)>0){
            printf("TRUE");
        }
        else {
            printf("false");
        }

        /*SELECT Pour avoir un recvfrom non bloquant*/
        //https://learn.microsoft.com/fr-fr/windows/win32/api/winsock2/nf-winsock2-select
        //https://stackoverflow.com/questions/15941005/making-recvfrom-function-non-blocking
        //https://www.developpez.net/forums/d1197400/c-cpp/c/fonction-select-c/
        //http://manpagesfr.free.fr/man/man2/select.2.html




        // Si au bout de 100ms (ou à modifier) si aucune socket alors 
        if (select(socket + 1, &rfds,NULL,NULL,&temps_select)>0){
            nb_octets_admin = recvfrom(socket, buffer, TAILLEBUF, 0,(struct sockaddr *)&addr_admin, &lg);
            if (nb_octets_admin > 0){
                memcpy(message_recu_configuration_partie, buffer, nb_octets_admin);
                printf("Configuration : %s\n", message_recu_configuration_partie);
                /*
                configure_partie(message_recu_configuration_partie);
                */
            }
        }



        nread = read(pipe_tcp_admin[0],message_recu_pipe,100);

        switch (nread){
            case -1: 
                //Si la pipe est vide
                if (errno == EAGAIN){
                    printf("PIPE VIDE\n");
                    usleep(50000);
                    continue;
                }
                else{
                    perror("Erreur dans la lecture de la pipe vide");
                    exit(1);
                }
            case 0:
                printf("Fermeture de la pipe");
                close(pipe_tcp_admin[0]);
                exit(0);
            default:
                // Envoie du message pour l'admin
                nb_octets_admin = sendto(socket, message_recu_pipe, strlen(message_recu_pipe)+1, 0,(struct sockaddr*)&addr_admin, lg);
                if (nb_octets_admin == -1) {
                    perror("erreur envoi réponse");
                    exit(1);
                }
        }
    }

}