#include <stdio.h>
#include <stdlib.h>

#include "connexionTCP.h"
#include "connexionMulticastUDP.h"

int main(int argc, char* argv[]) {
    pid_t proc_multicast = fork(); 

    if (proc_multicast == 0) {

        struct ip_mreq multicast_group;
        struct sockaddr_in addr;

        int sock = sock_multicastUDP(); 
        if (join_muliticastGroup(sock, &addr, IP_MULTICAST, 1234, &multicast_group) == 0) { 
            char message_multicast[100]; 
            while (1) {
                int n = recvfrom(sock, message_multicast, sizeof(message_multicast), 0, NULL, 0);
                if (n > 0) {
                    message_multicast[n] = '\0';
                    printf("%s\n", message_multicast);
                    if (strcmp(message_multicast, "q") == 0) {
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
    printf("Valeur de la socket : %d\n", sock); 
    (connexion_TCP(sock, "scinfe131", 2001) == 0) ? printf("ok\n"): printf("non\n");

    /*if (test_connection_TCP(sock) == 0) {
        printf("OK"); 
    } else {
        printf("non"); 
    }*/
    char test[100]; 
    while (strcmp(test, "q") != 0) {
        printf("communication tjrs en cours\n"); 
        scanf("%s", test);
        
        write(sock, test, strlen(test)+1); 
        
        if (strcmp(test, "q") == 0){
            printf("message de fin envoye\n");
            //kill(proc_multicast, SIGTERM);
        }
    }
    close(sock); 

    return 0; 
}