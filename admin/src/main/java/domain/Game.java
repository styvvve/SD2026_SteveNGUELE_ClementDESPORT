package domain;

import java.io.Serializable;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import domain.enu.*;
import domain.interfaces.*;

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
    private List<GameObserver> loggers = new ArrayList<>();
    private boolean isFinished = false;

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
        this.isFinished = false;
    }

    public String getId() {
        return id;
    }
    public void setId(String id) {}

    public GameMode getMode() { return this.mode; }

    public Level getLevel() { return this.level; }

    public List<Player> getPlayers() { return this.players; }
    public List<Round> getRounds() { return this.rounds; }

    public void addPlayer(Player player) {

    }

    public void addRounds(Round round) {
        this.rounds.add(round);
    }

    public void addObserver(GameObserver obs) {
        this.loggers.add(obs);
    }

    public void gameService() {
    }
}
