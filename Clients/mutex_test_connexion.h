#include <stdbool.h>
#include <pthread.h>




//https://tala-informatique.fr/index.php?title=C_pthread
typedef struct mutex_test {
	bool serveur_connecte;
    int socket;
    pthread_mutex_t mutex;
} mutex_test;