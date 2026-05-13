#include "gererAdmin.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>


#include "mutex.h"
#include "../Jeu/jeu.h"
#include "../structure_partage.h"

#define TAILLEBUF 100



void * reception(void *data){
    struct timeval temps_select;

    temps_select.tv_sec=5;
    temps_select.tv_usec=0;


    fd_set rfds;

    mutex_admin *mutex_ad = (mutex_admin*) data;


    char message[100];
    char message_recu_admin[100];
    int nb_octets_admin;
    char buffer[TAILLEBUF]; 
    int a;
    while(1){
        //Met à zero l'ensemble de "recherche" du select
        FD_ZERO(&rfds);
        //Ajoute la socket à surveiller 
        FD_SET(mutex_ad->socket, &rfds);
        if (select(mutex_ad->socket + 1, &rfds,NULL,NULL,&temps_select)>0){
            mutex_ad->admin_connecte=true;
            nb_octets_admin = recvfrom(mutex_ad->socket, buffer, TAILLEBUF, 0,(struct sockaddr *)&mutex_ad->addr_admin, &mutex_ad->lg);
            if (nb_octets_admin > 0){
                memcpy(message_recu_admin, buffer, nb_octets_admin);
                printf("Message reçu de l'admin :%s\n", message_recu_admin);
                char *p = strtok(message_recu_admin,"|");
                if (strcmp(p,"config")==0){
                    /*
                        configure_partie(message_recu_configuration_partie);
                    */
                }
                if (strcmp(p,"lancer")==0){
                    /*
                        ToDo : fonction pour lancer une partie
                    */
                }
                if (strcmp(p,"test")==0){
                    snprintf(message,sizeof(message)/sizeof(char),"OK");
                    a=sendto(mutex_ad->socket, message, strlen(message)+1, 0,(struct sockaddr*)&mutex_ad->addr_admin, mutex_ad->lg);
                    if (a==-1){
                        perror("Erreur dans envoie socket dans 'reception'");
                    }
                }
            }
        }
        else {
            mutex_ad->admin_connecte=false;
            if (mutex_ad->variablePartage->jeu){
                /*
                    ToDo : Ne rien faire, la partie continue et informer à la fin de la partie à tout les clients que l'admin est partie et donc attendre..
                */
            }else{
                /*
                    ToDo: Informer les clients que l'admin est partie et donc attendre..
                */
            }
            
        }
    }
    pthread_exit(NULL);
}


void * envoie(void *data){
    mutex_admin *mutex_ad = (mutex_admin*) data;
    int nread;
    int nb_octets_admin;
    char message_recu_pipe[100];

    while (mutex_ad->admin_connecte){
        if (mutex_ad->admin_connecte){
            nread = read(mutex_ad->pipe_tcp_admin[0],message_recu_pipe,100);
            switch (nread){
                case -1: 
                    //Si la pipe est vide
                    if (errno == EAGAIN){
                        usleep(100000);
                        continue;
                    }
                    else{
                        perror("Erreur dans la lecture de la pipe vide");
                        exit(1);
                    }
                case 0:
                    printf("Fermeture de la pipe");
                    close(mutex_ad->pipe_tcp_admin[0]);
                    exit(0);
                default:
                    // Envoie du message pour l'admin
                    nb_octets_admin = sendto(mutex_ad->socket, message_recu_pipe, strlen(message_recu_pipe)+1, 0,(struct sockaddr*)&mutex_ad->addr_admin, mutex_ad->lg);
                    if (nb_octets_admin == -1) {
                        perror("erreur envoi réponse");
                        exit(1);
                    }
            }
        }else{
            nread = read(mutex_ad->pipe_tcp_admin[0],message_recu_pipe,100);
            switch (nread){
                case -1: 
                    //Si la pipe est vide
                    if (errno == EAGAIN){
                        usleep(100000);
                        continue;
                    }
                    else{
                        perror("Erreur dans la lecture de la pipe vide");
                        exit(1);
                    }
                case 0:
                    printf("Fermeture de la pipe");
                    close(mutex_ad->pipe_tcp_admin[0]);
                    exit(0);
                default:
                //envoie dans un fichier
            }
        }
    }
    pthread_exit(NULL); 
}


void gererAdmin(int socket,int *pipe_tcp_admin, struct_partage *variablePartage) {

    int nb_octets_admin;
    socklen_t lg;
    char buffer[TAILLEBUF]; 

    
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

    //https://tala-informatique.fr/index.php?title=C_pthread
    mutex_admin mutex_ad;

    pthread_t tid_reception;
    pthread_t tid_envoie;

    //Creation mutex variable partage
    mutex_ad.admin_connecte=true;
    mutex_ad.addr_admin=addr_admin;
    mutex_ad.lg=lg;
    mutex_ad.pipe_tcp_admin=pipe_tcp_admin;
    mutex_ad.socket=socket;
    mutex_ad.variablePartage=variablePartage;
    

    if (pthread_mutex_init(&mutex_ad.mutex, NULL) != 0) {
		perror("Erreur dans la creation du mutex 'gererAdmin'");
        exit(0);
	}

    //Creation thread reception
    int err1 = pthread_create(&tid_reception,NULL, reception, &mutex_ad);
		if (err1 != 0) {
			perror("Erreur dans la creation du thread 'reception'");
			exit(0);
		}
    //Creation thread envoie    
    int err2 = pthread_create(&tid_envoie, NULL, envoie, &mutex_ad);
		if (err2 != 0) {
			perror("Echec de la création du thread de la création");
			exit(0);
		}


    pthread_join(tid_reception, NULL);
    pthread_join(tid_envoie, NULL);

    //Destruction du mutex
    pthread_mutex_destroy(&mutex_ad.mutex);
}