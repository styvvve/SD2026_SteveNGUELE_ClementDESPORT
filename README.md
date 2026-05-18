# Competitive "Whac-A-Mole" game

This project completed as part of the "Systèmes Distribués" course in the third year of Bachelor at the University of Pau.

## Objectives

This project consists of building a distributed Whac-A-Mole game. A C server sends moles to client computer using UDP multicast, and players must hit them quickly as possible.

## Features

## Architecture

## Technologies

## Installation

## Screenshots

## Tests



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