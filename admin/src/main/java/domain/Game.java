package main.java.domain;

import main.java.domain.interfaces.GameObserver;
import main.java.enu.GameMode;
import main.java.enu.Level;

import java.io.Serializable;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

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

    private Path filePath;

    //exclusively for the gameService method
    int nextRoundNumber = 0;

    public Game(GameMode mode, Level level,  Path filePath) {
        this.id = UUID.randomUUID().toString();
        this.mode = mode;
        this.level = level;
        this.filePath = filePath;
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
        this.players.add(player);
    }

    public void addRounds(Round round) {
        this.rounds.add(round);
    }

    public void addObserver(GameObserver obs) {
        this.loggers.add(obs);
    }

    /**
     * this method is a "service" engine that manage the game process
     *
     * @throws
     */
    public void gameService() {
        nextRoundNumber++;
        int logs = 1;

        Round newRound = new Round(nextRoundNumber);
        this.addRounds(newRound);

        loggers.forEach(l -> l.saveEachGameLog(this, logs, filePath));
    }
}
