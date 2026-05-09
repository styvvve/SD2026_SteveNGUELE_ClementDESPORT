package domain;

import java.io.Serializable;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import domain.enu.*;
import domain.interfaces.*;

/**
 * This is the main class for the whole game. The class implements Serializable interface for the communication with the persistence server in RMI
 * @author Steve
 */
public class Game implements Serializable {

    private final String id;
    private GameMode mode;
    private List<Player> players = new ArrayList<>();
    private Level level;
    private List<Round> rounds = new ArrayList<>();
    private List<GameObserver> loggers = new ArrayList<>();
    private boolean isFinished = false;
    private int health;

    private Path filePath;

    /**
     * Standard constructor
     * @param mode
     * @param level
     * @param filePath
     */
    public Game(GameMode mode, Level level, Path filePath) {
        this.id = UUID.randomUUID().toString();
        this.mode = mode;
        this.level = level;
        this.filePath = filePath;
        this.isFinished = false;
        this.health = 3;
        //the round number is 6 by default
        for (int i = 0; i < 6; i++) {
            Round round = new Round(i);
            this.rounds.add(round);
        }
    }

    /**
     * Constructor with players
     * @param mode
     * @param level
     * @param filePath
     * @param players
     */
    public Game(GameMode mode, Level level, Path filePath, List<Player> players) {
        this(mode, level, filePath);
        this.players = players;
    }

    /**
     * constructor with health and rounds number
     * @param
     */
    public Game(GameMode mode, Level level, Path filePath, int health) {
        this(mode, level, filePath);
        this.health = health;
    }

    public String getId() {
        return this.id;
    }

    /**
     * Getters
     */
    public GameMode getMode() { return this.mode; }
    public Level getLevel() { return this.level; }
    public List<Player> getPlayers() { return this.players; }
    public List<Round> getRounds() { return this.rounds; }
    public List<GameObserver> getLoggers() { return this.loggers; }
    public boolean isFinished() { return this.isFinished; }
    public int getHealth() { return this.health; }

    /**
     * Setters
     */
    public void addPlayer(Player player) {
        this.players.add(player);
    }
    public void addRounds(Round round) {
        this.rounds.add(round);
    }
    public void addObserver(GameObserver obs) {
        this.loggers.add(obs);
    }
    public void setFinished(boolean finished) { this.isFinished = finished; }
    public void setHealth(int health) { this.health = health; }
    public void addRound(Round round) { this.rounds.add(round); }


    /**
     * Define a mole and randomly choose the location
     * @return Mole
     */
    public Mole defineMole() {

        return null;
    }
}
