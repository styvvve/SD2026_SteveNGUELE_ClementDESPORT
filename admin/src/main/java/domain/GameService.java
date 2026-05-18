package domain;

import domain.cli.CliParser;
import domain.cli.HandleInputs;
import domain.cli.Response;
import domain.interfaces.ConnectionObserver;
import infra.ConnexionUDP;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Centralized service for the game, it's the king instance -> a kind of deliberate 'god object'
 * The idea of this is to manage the interaction and handle the user inputs and server interaction in one big logic.
 * For example, the last instance of Game in the arrayList "games" is the current game. We will get all the instances of Game made
 * in the memory by calling the method with the RMI server.
 * We can resume the class with one verb: orchestrate.
 * <h3>Thread scheduling</h3>
 * 4 threads are used with the multithreaded Producer-Consumer model:
 * <ul>
 *     <li>1 thread(1) for the CLI</li>
 *     <li>1 thread(2) for the server listening</li>
 *     <li>1 thread(3) for the game orchestration</li>
 *     <li>1 thread(4) for the one-off send and receive from the server</li>
 *     <li>1 thread(5) for the test connection "Special thread" because he's backdoor</li>
 * </ul>
 * All the thread post messages in gameOrchestration
 * @author Steve
 * @version 1.0
 * @see <a href="https://www.baeldung.com/java-blocking-queue></a>
 */
public class GameService implements ConnectionObserver, Runnable {

    /**Protected list of all the games, because all threads could add, edit, or delete. The current game is added to this list*/
    private final List<Game> games = Collections.synchronizedList(new ArrayList<>());
    /**One thread could write, and it's immediately visible by all the other threads*/
    private volatile boolean isConnected = false;
    /**The connection to the server, one thread could write, and it's immediately visible by all the other threads*/
    private volatile ConnexionUDP connection;

    /**
     * Blocking queue for the threads
     */
    private volatile BlockingQueue<String> gameOrchestration = new LinkedBlockingQueue<>();


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
     * Checking if the action is valid with the state of service
     */
    public boolean hasGame() { return !this.games.isEmpty(); }
    public boolean hasConnection() { return this.isConnected && this.connection != null; }
    public boolean canExecuteAction() {
        if (!this.hasGame()) {
            System.out.println("No game to perform the action");
            return false;
        }

        if (!this.hasConnection()) {
            System.out.println("No connection to the server");
            return false;
        }

        return true;
    }

    /**
     * Methods for the handle of the user inputs
     */
    public void handleInitialize(String[] args) {

        Response<ConnexionUDP> resp = HandleInputs.initializeConnection(args[0], Integer.parseInt(args[1]), ConnexionUDP::new);

        if (resp.isOk()) {
            this.connection = resp.data();
        } else {
            System.out.println("Error during connection");
        }
    }

    public void handleConfigure(String[] args) {
        if (!this.canExecuteAction()) return;
        //the last game is the current game, so if it's not finished, we can't configure another one
        Game currentGame = this.games.get(this.games.size() - 1);
        if (!currentGame.isFinished()) {
            System.out.println("Current game " + currentGame.getId() + " is not finished");
            return;
        }

        Response<Game> resp = HandleInputs.configureGame(args, this.connection);

        if (resp.isOk()) {
            Game newGame = resp.data();
            this.addGame(newGame);
        } else {
            System.out.println("Error during configuration");
        }
    }

    public void handleStart() {
        if (!this.canExecuteAction()) return;
        //the last game...
        Game currentGame = this.games.get(this.games.size() - 1);
        if (currentGame.isFinished()) {
            System.out.println("Current game " + currentGame.getId() + " is already finished");
            return;
        }

        Response<Game> resp = HandleInputs.startGame(currentGame, this.connection);

        if (resp.isOk()) {
            System.out.println("Game started");
        }
    }

    public void handleListPlayers() {
        Game currentGame = this.games.get(this.games.size() - 1);
        if (currentGame.isFinished()) {
            System.out.println("Current game " + currentGame.getId() + " is finished");
            return;
        }

        Response<List<Player>> resp = HandleInputs.listPlayers(currentGame);
        if (resp.isOk()) {
            List<Player> players = resp.data();
            players.forEach(p -> System.out.println(p.getId()));
        }
    }

    public synchronized void handleHistory() {
        Response<List<Game>> resp = HandleInputs.history();

        //TODO
        if (resp.isOk()) {
            List<Game> games = resp.data();
            games.forEach(g -> System.out.println(g.getId()));
        }
    }

    /**
     * Handle the received operation from the server and update the state. These methods are "synchronized" because of the access from the thread who
     * listening to the server to the games list
     */
    public synchronized void addPlayer(int playerId) {
        Game currentGame = this.games.get(this.games.size() - 1);
        currentGame.addPlayer(new Player(playerId, currentGame.getHealth()));
    }
    public synchronized void removePlayer(int playerId) {
        Game currentGame = this.games.get(this.games.size() - 1);
        currentGame.getPlayers().stream().filter(p -> p.getId() == playerId).findFirst().ifPresent(playerToDelete -> currentGame.getPlayers().remove(playerToDelete));
    }
    public synchronized void playerWin(int playerId) {
        Game currentGame = this.games.get(this.games.size() - 1);

        //check le mode
    }
    public synchronized void playerLose(int playerId) {
        //if the mode is battle royal, the player loses one's health
        Game currentGame = this.games.get(this.games.size() - 1);
        currentGame.getPlayers().stream().filter(p -> p.getId() == playerId).findFirst().ifPresent(player -> player.setHealth(player.getHealth() - 1));
    }

}
