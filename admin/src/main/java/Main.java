package main.java;

import main.java.domain.Game;
import main.java.domain.GameService;
import main.java.domain.Player;
import main.java.domain.factory.GameFactory;
import main.java.infra.connexionUDP;

import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        //initialize the connection
        connexionUDP connexion = null; 
        while (true) {
            try {
                connexion = new connexionUDP("scinfe182", 3000);
            } catch (SocketException | UnknownHostException e) {
                System.out.println("Error during connexion " + e);
            }

            GameService svr = new GameService();
            Game newGame = GameFactory.createGame(new ArrayList<>());
            svr.addGame(newGame);
            try {
                connexion.sendToServer("TEST");
            } catch (IOException e) {
                System.out.println("Error during sendToServer " + e);
            }

            try {
                String chaineRecu = connexion.receiveFromServer();
                System.out.println(chaineRecu);
                String[] commande = chaineRecu.split("\\|");
                if (commande[0].equals("addPlayer")) {
                    for (String txt : commande) {
                        System.out.println(txt);
                    }
                    newGame.addPlayer(new Player(Integer.parseInt(commande[1])));
                }
                System.out.println(newGame);
            } catch (IOException e) {
                System.out.println("Error during receiveFromServer " + e);
            }
        }
    }
}
