package domain.cli;

import domain.Game;
import domain.Player;
import domain.enu.GameMode;
import domain.enu.Level;
import domain.exception.NotEnoughPlayersException;
import domain.factory.GameFactory;
import infra.ConnexionUDP;
import infra.ConnexionUDPFactory;

import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.List;

/**
 * Class for methods to handle inputs from the CLI -> More precisely, it's the couch between the CLI and the GameService
 * where we made all the networks calls and complex business logic for the service class.
 * <ul>
 *     <li>Initialize a connection between server and admin</li>
 *     <li>Configure a game</li>
 *     <li>Start a game</li>
 *     <li>List players</li>
 *     <li>See the game history</li>
 * </ul>
 */
public class HandleInputs {

    /**
     * Initialize a connection between server and admin after the user commands
     * @param server
     * @param serverPort
     * @return Response
     */
    public static Response<ConnexionUDP> initializeConnection(String server, int serverPort, ConnexionUDPFactory factory) {
        try {
            return Response.ok(factory.create(server, serverPort)); //true
        } catch (SocketException s) {
            System.err.println("Unable to create a socket " + s);
        } catch (UnknownHostException u) {
            System.err.println("Unknown host " + u);
        }

        return Response.fail("Error");
    }

    /**
     * call the factory method to create a game with the parameter pass in arguments
     * The order of the args is given like that
     * <ul>
     *     <li>mode</li>
     *     <li>level</li>
     *     <li>health</li>
     *     <li>moles-number</li>
     * </ul>
     * @param args passed in arguments from the CLI
     * @param connexionUDP the connection to the server
     * @return Response<Game>
     */
    public static Response<Game> configureGame(String[] args, ConnexionUDP connexionUDP) {
        //first: we check if the args are good
        if (args.length != 4) {
            return Response.fail("Illegal arguments number");
        }

        GameMode mode = null; Level level = null; int health = 0; int molesNumber = 0;

        try {
            mode = GameMode.valueOf(args[0]);
            level = Level.valueOf(args[1]);
            health = Integer.parseInt(args[2]);
            molesNumber = Integer.parseInt(args[3]);
        } catch (IllegalArgumentException e) {
            return Response.fail("Illegal arguments " + e);
        }

        Game newG = GameFactory.createGame(mode, level, health, molesNumber);

        //send the config to the server
        try {
            boolean isOK = connexionUDP.sendMessage('c', newG);
            if (!isOK) {
                return Response.fail("Unable to connect to the server");
            }
        } catch (IOException e) {
            System.out.println("Error during sendToServer " + e);
        }

        return Response.ok(newG);
    }

    /**
     * Start the game
     * @param game the game to start
     * @param connexionUDP the connection to the server
     * @return Response<Game>
     */
    public static Response<Game> startGame(Game game, ConnexionUDP connexionUDP) throws NotEnoughPlayersException {
        //verification of the game
        if (game.getPlayers().size() < 2) {
            return Response.fail("Not enough players");
        }

        try {
            boolean isOK = connexionUDP.sendMessage('s', game);
            if (!isOK) {
                return Response.fail("Unable to connect to the server");
            }
            String resp = connexionUDP.receiveFromServer(); //we should get a "started" response if is ok or no
            if (!resp.equals("started")) {
                return Response.fail("Game could not be started by the server.");
            }
            return Response.ok(game);
        } catch (IOException e) {
            System.out.println("Error during sendToServer " + e);
        }

        return Response.fail("ERROR");
    }

    /**
     * List players of the game passed in parameter
     * @param game the game to list
     * @return Response<List<Player>>
     */
    public static Response<List<Player>> listPlayers(Game game) {
        return game.getPlayers().isEmpty() ?
                Response.fail("Any player.")
                : Response.ok(game.getPlayers());
    }

    /**
     * Give the history of games played connect to the RMI server
     * @return Response<List<Game>>
     */
    public static Response<List<Game>> history() {
        return Response.ok(null);
    }

}
