package domain.cli;

import domain.Game;
import domain.enu.GameMode;
import domain.enu.Level;
import domain.exception.NotEnoughPlayersException;
import domain.factory.GameFactory;
import infra.ConnexionUDP;
import infra.ConnexionUDPFactory;

import java.net.SocketException;
import java.net.UnknownHostException;

/**
 * Class for methods to handle inputs from the CLI
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
    public static Response<ConnexionUDP> initializeConnection(String server, int serverPort) {
        try {
            return Response.ok(new ConnexionUDP(server, serverPort)); //true
        } catch (SocketException s) {
            System.err.println("Unable to create a socket " + s);
        } catch (UnknownHostException u) {
            System.err.println("Unknown host " + u);
        }

        return Response.fail("Error");
    }

    /**
     * Replication for the tests
     * @param server
     * @param serverPort
     * @param factory
     * @return
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
     * @param args
     * @return Response<Game>
     */
    public static Response<Game> configureGame(String[] args) {
        //first: check if the args are good
        //getOptionValues passed in parameter, we have a one-world tab
        GameMode mode = GameMode.valueOf(args[0]);
        Level level = Level.valueOf(args[1]);
        int health = Integer.parseInt(args[2]);
        int molesNumber = Integer.parseInt(args[3]);

        Game newG = GameFactory.createGame(mode, level, health, molesNumber);

        return Response.ok(newG);
    }

    /**
     * Start the game
     * @param game
     * @return Response<Game>
     */
    public static Response<Game> startGame(Game game) {
        //verification of the game
        if (game.getPlayers().size() < 2) {
            return Response.fail("Not enough players");
        }



        //send the game to the server
        return Response.ok(game);
    }

}
