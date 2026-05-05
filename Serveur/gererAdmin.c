#include "gererAdmin.h"
#include <sys/wait.h>

#define TAILLEBUF 100

void gererAdmin(int socket,int *pipe_tcp_admin) {

    int nb_octets_admin;
    socklen_t lg;
    char buffer[TAILLEBUF]; 

    int nread;
    char message_recu_pipe[100];
    


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

        nread = read(pipe_tcp_admin[0],message_recu_pipe,100);

        switch (nread){
            case -1: 
                if (errno == EAGAIN){
                    printf("VIDE\n");
                    sleep(1);
                    break;
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