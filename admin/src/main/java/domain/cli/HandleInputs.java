package domain.cli;

import infra.ConnexionUDP;

import java.net.SocketException;
import java.net.UnknownHostException;

/**
 * Class for methods to handle inputs from the CLI
 * - Initialize a connection between server and admin
 * - Configure a game
 * - Start a game
 * - List players
 * - See the game history
 */
public class HandleInputs {

    /**
     * Initialize a connection between server and admin after the user commands
     * @param server
     * @param serverPort
     * @return
     */
    public static ConnexionUDP initializeConnection(String server, int serverPort) {
        try {
            return new ConnexionUDP(server, serverPort);
        } catch (SocketException s) {
            System.err.println("Unable to create a socket " + s);
        } catch (UnknownHostException u) {
            System.err.println("Unknown host " + u);
        }

        return null;
    }

    public static void configureGame() {

    }

    public static void startGame() {

    }

}
