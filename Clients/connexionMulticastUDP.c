#include "connexionMulticastUDP.h"

int sock_multicastUDP() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock == -1) {
        perror("Error during socket creation\n"); 
        printf("Error description : %s\n", strerror(errno)); 
        return sock; 
    }

    return sock; 
}

int join_muliticastGroup(int sock, struct sockaddr_in *addr, char *ip, int port, struct ip_mreq *multicast_group) {
    //local address
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);

    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("Error setting socket option: SO_REUSEADDR\n");
        printf("Error description: %s\n", strerror(errno)); 
        return -1; 
    }

    if (bind(sock, (struct sockaddr*)addr, sizeof(struct sockaddr)) < 0) {
        perror("Error bind multicast player\n");
        printf("Error description: %s\n", strerror(errno)); 
        return -1; 
    }   

    // abonnement au groupe du multicast
    multicast_group->imr_multiaddr.s_addr = inet_addr(ip);
    multicast_group->imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, multicast_group, sizeof(multicast_group)) < 0) {
        perror("Error multicast subscription");
        printf("Error description: %s\n", strerror(errno)); 
        return -1; 
    }

    return 0; 
}

int quit_multicastGroup(int sock, struct ip_mreq *multicast_group) {
    if (setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, multicast_group, sizeof(multicast_group)) < 0) {
        perror("Error during discription\n"); 
        printf("Error description: %s\n", strerror(errno)); 
        return 1; 
    }
    close(sock);
    return 0; 
}

int receive_message_from_multicastGroup(int sock, char *message) {
    char message_multicast[50]; 
    int n = recvfrom(sock, message_multicast, sizeof(message_multicast), 0, NULL, 0);
    if (n < 0) {
        perror("Error during reception\n"); 
        printf("Error description: %s\n", strerror(errno)); 
        return 1; 
    }
    message_multicast[n] = '\0';
    memcpy(message, message_multicast, sizeof(message_multicast)); 
    return 0; 
}

