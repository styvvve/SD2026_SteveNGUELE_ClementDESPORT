package domain;

import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;

import infra.connexionUDP;
import domain.factory.GameFactory;

public class App {

    //Boolean that knows when the party is over
    private static boolean partyOver = false;

    public static void main(String[] args) {

        //initialize the connection
        connexionUDP connexion = null;
        System.out.println("test");
        while (!partyOver) {
            try {
                connexion = new connexionUDP("localhost", 3000);
            } catch (SocketException | UnknownHostException e) {
                System.out.println("Error during connexion " + e);
            }

            GameService svr = new GameService();
            Game newGame = GameFactory.createGame(new ArrayList<>());
            svr.addGame(newGame);
            try {
                connexion.sendToServer("test");
            } catch (IOException e) {
                System.out.println("Error during sendToServer " + e);
            }

            try {
                String chaineRecu = connexion.receiveFromServer();
                System.out.println(chaineRecu);
                String[] commande = chaineRecu.split("\\|");
                if (commande[0].equals("addPlayer")) {
                    newGame.addPlayer(new Player(Integer.parseInt(commande[1]), Integer.parseInt(commande[1])));
                }
                System.out.println(newGame);
            } catch (IOException e) {
                System.out.println("Error during receiveFromServer " + e);
            }
        }
    }
}
