package domain;

import domain.cli.CliParser;
import domain.cli.HandleInputs;
import domain.cli.Response;
import domain.interfaces.ConnectionObserver;
import infra.ConnexionUDP;
import org.apache.commons.cli.CommandLine;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
/**
 * Centralized service for the game, it's the king instance -> a kind of deliberate 'god object'
 * The idea of this is to manage the interaction and handle the user inputs and server interaction in one big logic.
 * For example, the last instance of Game in the arrayList "games" is the current game. We will get all the instances of Game made
 * in the memory by calling the method with the RMI server.
 * We can resume the class with one verb: orchestrate.
 * @author Steve
 * @version 1.0
 */
public class GameService implements ConnectionObserver, Runnable {

    /**Protected list of all the games, because all threads could add, edit, or delete. The current game is added to this list*/
    private final List<Game> games = Collections.synchronizedList(new ArrayList<>());
    /**One thread could write, and it's immediately visible by all the other threads*/
    private volatile boolean isConnected = false;
    /**The connection to the server, one thread could write, and it's immediately visible by all the other threads*/
    private volatile ConnexionUDP connection;


    public void addGame(Game game) {
        this.games.add(game);
    }

    @Override
    public void run() {}


    @Override
    public void connectionLost() {
        this.setConnected(false);
        //we try to reconnect
    }

    @Override
    public void connectionRestored() {
        //get all the missing data from the server
        System.out.println("Connection restored");
        this.setConnected(true);
    }

    public boolean isConnected() {
        return this.isConnected;
    }

    public void setConnected(boolean connected) {
        isConnected = connected;
    }
    public List<Game> getGames() { return this.games; }

    /**
     * Methods for the handle of the user inputs
     */
    public void handleInitialize(CommandLine cmd) {
        String[] values = cmd.getOptionValues("i");

        Response<ConnexionUDP> resp = HandleInputs.initializeConnection(values[0], Integer.parseInt(values[1]), ConnexionUDP::new);

        if (resp.isOk()) {
            this.connection = resp.data();
        }
    }

}
