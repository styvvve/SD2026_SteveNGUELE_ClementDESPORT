#include <stdbool.h>
#include <pthread.h>

#include "../structure_partage.h"



//https://tala-informatique.fr/index.php?title=C_pthread
typedef struct mutex_admin {
	bool admin_connecte;
    int socket;
    struct sockaddr_in addr_admin;
    socklen_t lg;
	pthread_mutex_t mutex;
    int *pipe_tcp_admin;
    int *pipe_jeu_multicast;
    struct_partage *variablePartage;
} mutex_admin;