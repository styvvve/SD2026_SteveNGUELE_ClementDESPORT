package domain.cli;

import domain.Game;
import infra.ConnexionUDP;

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
        //getOptionValues passed in parameter we have a one-world tab
        String mode = args[0];
        String level = args[1];
        int health = Integer.parseInt(args[2]);
        int molesNumber = Integer.parseInt(args[3]);

        return Response.fail("Error to configure the game");
    }

    public static Response<Game> startGame(Game game) {
        //verification of the game
        if (game.getPlayers().size() < 2) {
            return Response.fail("Not enough players");
        }

        //send the game to the server
        return Response.ok(game);
    }

}
