#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <pthread.h>
#define TAILLEBUF 100
#include "connexionTCP.h"
#include "connexionMulticastUDP.h"
#include "mutex_test_connexion.h"
#include "id_joueur.h"
#include <sys/shm.h>

void joue(const char *message, int len){
    char cp_message[500];
    strcpy(cp_message, message);
    char *p = strtok(cp_message,"#");
    int num=0;

    int temps;
    char taupe[200];
    while (p != NULL){
        switch (num){
            case 0:
                break;
            case 1:
                snprintf(taupe,sizeof(taupe)/sizeof(char),"%s",p);
                break;
            case 2:
                temps=atoi(p);
                break;
        }
        num++;
        p = strtok(NULL, "#");
    }
    printf("%s\n\n",taupe);

    printf("TEST temps : %d\n",temps);
}

void *test_connexion(void *data) {
    mutex_test *mutex_t = (mutex_test*) data;
    int sock = mutex_t->socket;
    struct timeval temps_select;
    fd_set rfds;
    char message_test_envoie[100];
    char message_recu_serveur[100];
    while(1){
        snprintf(message_test_envoie,sizeof(message_test_envoie)/sizeof(char),"test|");
        write(sock, message_test_envoie, strlen(message_test_envoie)+1);
        //Met à zero l'ensemble de "recherche" du select
        FD_ZERO(&rfds);
        //Ajoute la socket à surveiller 
        FD_SET(sock, &rfds);
        //5 seconde
        temps_select.tv_sec=5;
        temps_select.tv_usec=0;
        if (select(sock + 1, &rfds,NULL,NULL,&temps_select)>0){
            if(read(sock,message_recu_serveur,sizeof(message_recu_serveur))==0){
                printf("Le serveur c'est déconnecté. Veuillez relancer si le serveur est lancé. \n");
            }
        }else{
            pthread_mutex_lock(&(*mutex_t).mutex);
            (*mutex_t).serveur_connecte=false;
            // Dévérouillage du mutex
            pthread_mutex_unlock(&(*mutex_t).mutex);
            printf("Le serveur n'est plus disponible.");
            break;
        }
        usleep(100000);
    }
    pthread_exit(NULL);
}
int main(int argc, char* argv[]) {
    int shm_id = shmget(IPC_PRIVATE, sizeof(bool) * 100, IPC_CREAT | 0666);

    if (shm_id == -1) {
        perror("Erreur dans la mémoire partagée");
        exit(EXIT_FAILURE);
    }

    /** 
    shmat : Pour mettre le tableau dans la mémoire partagé
    shm_id : ID
    NULL et 0 : Pour choisir automatiquement l'adresse de stockage et pas de restriction
    **/
    


    struct_joueur *id_partage = (struct_joueur *)shmat(shm_id, NULL, 0);



    pid_t proc_multicast = fork(); 
    if (proc_multicast == 0) {
        struct ip_mreq multicast_group;
        struct sockaddr_in addr;
        int sock = sock_multicastUDP(); 
        if (join_muliticastGroup(sock, &addr, IP_MULTICAST, 1234, &multicast_group) == 0) { 
            char message_multicast[500]; 
            while (1) {
                int n = recvfrom(sock, message_multicast, sizeof(message_multicast), 0, NULL, 0);
                message_multicast[n] = '\0';
                char cp_message[500];
                strcpy(cp_message, message_multicast);

                if (n > 0) {
                    /*AFFICHE LA TAUPE SI C'EST SON ID*/
                    char *p = strtok(cp_message,"#");
                    char id[10];
                    snprintf(id, sizeof(id), "%d", id_partage->id_joueur);
                    if (p && strcmp(p,id)==0){
                        joue(message_multicast,n);
                    }
                    else if (strcmp(message_multicast, "q") == 0) {
                        if (quit_multicastGroup(sock, &multicast_group) == 0) {
                            break; 
                        }
                    }
                }
            }
            printf("Fin du multicast."); 
        } else {
            printf("non"); 
        }
    }
    int sock = socket_TCP(); 
    if (connexion_TCP(sock, argv[1], atoi(argv[2])) != 0){
        perror("Erreur dans la connexion avec le serveur");
    }

    int nb_octets;
    char message_recu_serveur[100];
    nb_octets = read(sock, message_recu_serveur, 100);
    if (nb_octets>0){
        id_partage->id_joueur = atoi(message_recu_serveur);
    }

    mutex_test mutex_t;
    pthread_mutex_init(&mutex_t.mutex, NULL);
    mutex_t.serveur_connecte = true;
    mutex_t.socket = sock;
    
    pthread_t thread;
    pthread_create(&thread, NULL, test_connexion, &mutex_t);
    char message[100]= ""; 
    bool connecte=true;

    printf("Bienvenu dans le jeu tape-taupe, veuillez attendre que l'administrateur lance la partie \n\n");



    while (strcmp(message, "q") != 0 && connecte) {

        scanf("%s", message);
        //write(sock, message, srlen(message)+1); 
        
        pthread_mutex_lock(&mutex_t.mutex);
        connecte = mutex_t.serveur_connecte;
        pthread_mutex_unlock(&mutex_t.mutex);
        write(sock, message, strlen(message)+1);
        if (strcmp(message, "q") == 0){
            snprintf(message,sizeof(message)/sizeof(char),"quit|"); //pour fair comprendre que le client à quitter volontairement
            write(sock, message, strlen(message)+1);
        }
    }
    pthread_join(thread, NULL);
    close(sock); 
    pthread_mutex_destroy(&mutex_t.mutex);
    
    return 0; 
}