package domain;

import domain.interfaces.ConnectionObserver;
import infra.ConnexionUDP;

import java.util.ArrayList;
import java.util.List;
/**
 * Centralized service for the game, it's the king instance
 * @author Steve
 * @version 1.0
 */
public class GameService implements ConnectionObserver{

    private final List<Game> games = new ArrayList<>();

    private boolean isConnected = false;

    public void addGame(Game game) {
        this.games.add(game);
    }


    @Override
    public void connectionLost() {
        this.setConnected(false);
        //we try to reconnect

        System.out.println("Connection lost");
    }

    @Override
    public void connectionRestored() {
        //get all the missing data from the server
        System.out.println("Connection restored");
    }

    public boolean isConnected() {
        return isConnected;
    }

    public void setConnected(boolean connected) {
        isConnected = connected;
    }
    public List<Game> getGames() { return this.games; }
}
