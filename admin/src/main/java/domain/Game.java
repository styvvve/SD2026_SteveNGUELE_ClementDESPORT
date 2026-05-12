package domain;

import java.io.Serializable;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.Random;

import domain.enu.*;
import domain.exception.NotEnoughPlayersException;
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
    private boolean isFinished = false;
    private int health = 3;
    private int molesNumber = 6;
    private int time = 10; //in seconds

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
     * constructor with health and moles number
     * @param
     */
    public Game(GameMode mode, Level level, Path filePath, int health, int molesNumber) {
        this(mode, level, filePath);
        this.health = health;
        this.molesNumber = molesNumber;
    }


    /**
     * Getters
     */
    public String getId() { return this.id; }
    public GameMode getMode() { return this.mode; }
    public Level getLevel() { return this.level; }
    public List<Player> getPlayers() { return this.players; }
    public List<Round> getRounds() { return this.rounds; }
    public boolean isFinished() { return this.isFinished; }
    public int getHealth() { return this.health; }
    public int getTime() { return this.time; }
    public int getMolesNumber() { return this.molesNumber; }

    /**
     * Setters
     */
    public void addPlayer(Player player) {
        this.players.add(player);
    }
    public void addRounds(Round round) {
        this.rounds.add(round);
    }

    public void setFinished(boolean finished) { this.isFinished = finished; }
    public void setHealth(int health) { this.health = health; }
    public void addRound(Round round) { this.rounds.add(round); }
    public void setTime(int time) { this.time = time; }


    /**
     * Define a mole and randomly choose the location
     * @param number the number of the mole
     * @param words the list of words -> if it's level 3 and the list is empty, we use a predefined list
     * @return Mole
     * @throws NotEnoughPlayersException if the number of players is not enough to define a mole (at least 2 players)
     */
    public Mole defineMole(int number, List<String> words) throws NotEnoughPlayersException {
        Random random = new Random();
        if (players.size() < 2) {
            throw new NotEnoughPlayersException("Not enough players to define a mole");
        }

        Player player = players.get(random.nextInt(players.size()));
        String word = words.isEmpty() ? "" : words.get(random.nextInt(words.size()));

        return new Mole(number, player, word);
    }

    /**
     * Convert a Game object after configuration into a String with the format:
     * -> |level|mode|health|time|numberOfMoles|numberOfRounds all in integer
     * @return String
     */
    public String toString() {
        int level = this.getLevel().getNumber();
        int mode = this.getMode().getNumber();
        int health = this.getHealth();
        int time = this.getTime();
        int numberOfMoles = this.getMolesNumber();
        int numberOfRounds = this.getRounds().size();

        return String.format("|%d|%d|%d|%d|%d|%d", level, mode, health, time, numberOfMoles, numberOfRounds);
    }
}
