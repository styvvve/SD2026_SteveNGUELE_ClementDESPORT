package main.java.domain;

import main.java.domain.interfaces.GameObserver;
import main.java.enu.GameMode;
import main.java.enu.Level;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * This is the main class for the whole game
 * @author Steve
 */
public class Game implements Serializable {

    private String id;
    private GameMode mode;
    private List<Player> players = new ArrayList<>();
    private Level level;
    private List<Round> rounds = new ArrayList<>();
    private List<Log> loggers = new ArrayList<>();

    public Game(GameMode mode, Level level) {
        this.mode = mode;
        this.level = level;
    }

    public String getId() {
        return id;
    }
    public void setId(String id) {}

    public GameMode getMode() { return this.mode; }

    public Level getLevel() { return this.level; }

    public List<Player> getPlayers() { return this.players; }
    public List<Round> getRounds() { return this.rounds; }

    public void addRounds(Round round) {

    }

    public void addObserver(GameObserver obs) {

    }
}
