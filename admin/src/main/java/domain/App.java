package domain;

import domain.cli.CliParser;
import domain.cli.HandleInputs;
import domain.cli.Response;
import domain.factory.GameFactory;
import domain.interfaces.ConnectionObserver;
import infra.ConnexionUDP;
import infra.ConnexionUDPFactory;
import infra.TestConnectionUDP;
import org.apache.commons.cli.CommandLine;

import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

public class App {

    //Boolean that knows when the party is over
    private static boolean partyOver = false;

    public static void main(String[] args) {

        //initialize the connection
        /*connexionUDP connexion = null;
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
        }*/
        //test of the CLI
       CliParser cli = new CliParser();
       CommandLine cmd = cli.parse(args);

        if (cmd.hasOption("h")) {
            cli.printHelp();
            System.exit(0);
        }

        switch (cli.getSelected()) {
            case "i" -> {
                String[] values = cmd.getOptionValues("i");

                Response<ConnexionUDP> resp = HandleInputs.initializeConnection(values[0], Integer.parseInt(values[1]));

                TestConnectionUDP testConn = new TestConnectionUDP(resp.data());
                ConnectionObserver svr = new GameService();

                testConn.addObserver(svr);

                testConn.start();

                System.out.println("Appuie sur Entrée pour quitter...");
                new Scanner(System.in).nextLine();
                testConn.stop();
            }
            case "c" -> System.out.println("configure");
            case "s" -> System.out.println("start");
            case "l" -> System.out.println("liste des joueurs");
            case "hi" -> System.out.println("historique des parties");
        }
    }
}
