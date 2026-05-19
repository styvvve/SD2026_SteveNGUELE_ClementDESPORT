# Competitive "Whac-A-Mole" game

This project completed as part of the "Systèmes Distribués" course in the third year of Bachelor at the University of Pau.

## Objectives

This project consists of building a distributed Whac-A-Mole game. A C server sends moles to client computer using UDP multicast, and players must hit them quickly as possible.

## Features

- Connexion de plusieurs joueurs simultanément via UDP multicast
- Modes de jeu : **équipe** et **facile** (fonctionnels) — bataille royale en cours
- Administration à distance : configuration, démarrage, liste des joueurs, historique
- Gestion de la perte de connexion avec tentative de reconnexion automatique
- Architecture multithreadée côté admin (Producer-Consumer sur `BlockingQueue`)


## Architecture
### Vue d'ensemble

```
┌─────────────────────────────────────────────────────┐
│                  Administrateur (Java)               │
│                                                     │
│  Thread 1 (CLI)      Thread 3 (Orchestrateur)       │
│  CommandPrompt  ──►  GameService.run()              │
│  GameController       └─ consomme BlockingQueue     │
│                                                     │
│  Thread 2 (Listener UDP)   Thread 4 (Watcher)       │
│  ConnexionUDP              TestConnectionUDP        │
│  ServerMessageHandler  ──► gameOrchestration ◄──┘  │
└───────────────────────────┬─────────────────────────┘
                            │ UDP
┌───────────────────────────▼─────────────────────────┐
│                    Serveur (C)                       │
│                                                     │
│  Processus 1          Processus 2   Processus 3     │
│  Admin TCP      ◄──►  Clients TCP ◄─ Multicast UDP  │
│                        │                            │
│            pipe_tcp_admin  pipe_tcp_multicast        │
└─────────────────────────────────────────────────────┘
                            │ UDP Multicast
┌───────────────────────────▼─────────────────────────┐
│               Clients / Joueurs (C)                  │
│  Appuie espace pour frapper une taupe               │
└─────────────────────────────────────────────────────┘
```

### Côté Java (admin)

Le module admin suit une architecture en couches :

```
domain/
├── cli/
│   ├── command/        Commandes CLI (InitCommand, StartCommand…)
│   ├── CliParser       Parse la saisie → Map<String, String[]>
│   └── HandleInputs    Logique réseau et validation des inputs
├── Controller/
│   └── GameController  Dispatch des commandes vers GameService
├── interfaces/
│   ├── ConnectionObserver  Observer pattern pour la connexion
│   └── ServerHandler       Callback pour les messages UDP reçus
├── factory/            Fabrique de jeux et de connexions
├── enu/                GameMode, Level
├── exception/          NotEnoughPlayersException…
├── App                 Point d'entrée, démarrage des threads
├── Game / Player / Round / Mole   Modèles du domaine
├── GameService         Orchestrateur central (Runnable + ConnectionObserver)
└── ServerMessageHandler  Traitement des messages serveur entrants
 
infra/
├── ConnexionUDP        Sockets UDP (envoi + écoute dans un thread dédié)
├── ConnexionUDPFactory Interface de fabrication
└── TestConnectionUDP   Surveillance de la connexion (ScheduledExecutorService)
```
## Technologies
| Administrateur | Java 17, UDP, BlockingQueue, ScheduledExecutorService |
| Serveur | C, sockets UDP/TCP, processus, pipes, mutex (pthread) |
| Joueurs | C, UDP multicast, terminal non canonique |
| Communication | UDP (multicast + unicast) |
## Installation & execution

### Serveur C

```bash
cd Serveur/
make clean 
make
./server <port_clients> <port_administrateur>
```

### Joueurs C

```bash
cd Clients/
make clean
make
./player <nom_machine_serveur> <port_serveur>
```

> Le joueur appuie sur **espace** pour frapper une taupe (mode terminal non canonique).


### Admininistrateur Java

```bash
# 1. Trouve et compile tous les fichiers .java d'un coup
javac $(find . -name "*.java")

# 2. Lance le programme (en spécifiant le package de la classe principale)
java domain.App
```

Commandes Java (Administrateur):
| `init <host> <port>` | Initialise la connexion UDP avec le serveur |
| `configure <mode> <level> <health> <moles>` | Configure une nouvelle partie |
| `start` | Démarre la partie courante |
| `list` | Liste les joueurs connectés |
| `hist` | Historique des parties |
| `help` | Affiche l'aide |
| `exit` | Quitte l'application |

## État du projet

pas terminé
- mode équipe fonctionnel en facile lancer la commande
`configure TEAM EASY 2 2`   
- Gestion de connexion UDP
- RMI à compléter - pas complet

## Sources Java citées dans la javadoc

## Tests

Dans le deuxième dossier `src/java` se trouve des tests unitaires.

## PARTIE EN C

Sources utilisé:

    (Mémoire partagé)
    -https://www.ibm.com/docs/fr/aix/7.3.0?topic=memory-creating-shared-segment-shmat-subroutine
    -https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmget.html?utm_source=copilot.com

    (Pipe non bloquante)
    -https://www.geeksforgeeks.org/c/non-blocking-io-with-pipes-in-c/

    (Séparation d'une chaine de caractère par un seul caractère)
    -https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html

    (Mutex)
    -https://tala-informatique.fr/index.php?title=C_pthread

    (Création d'un teminal non canonique. Pour que détecter si (en l'occurrence) la barre 'espace' à été appuyée sans avoir appuyé sur 'Entrée')
    -https://stackoverflow.com/questions/63751531/non-canonical-terminal-mode-buffer-stdout-in-c-program



## Compilation et execution C

Serveur: Serveur/Makefile ---> $make clean ---> $make ---> $./server (port clients) (port administrateur)

Clients/Joueurs: Clients/MakeFile ---> $make clean ---> $make ---> $./player (nom machine serveur) (port serveur)


## Conceptions et implémentations

Le serveur est divisé en 3 processus (Administrateur TCP, Clients TCP, Clients Multicast) pour gerer en même temps ces 3 cas de communication.

Utilisation de pipe pour communiquer entre ces processus. 

                    EXEMPLE: 
                            Connexion d'un nouveau joueur (Clients TCP) ---> pipe_tcp_admin ---> Reception de l'ID (Administrateur TCP) ---> Notifie l'administrateur d'une nouvelle connexion



Utilisation de thread pour effectuer plusieurs tâche pour le même processus.

                    EXEMPLE:
                            2 thread pour l'administrateur (Reception et Envoie) pour être capable à la fois d'envoyer à l'administrateur à tout moment et de recevoir à tout moment un message dela part de l'admin


## Répartition travail
 
 
NGUELE Steve (JAVA + un peu de C) , DESPORT Clément (C)