package domain.factory;


import domain.Game;
import domain.GameService;
import domain.Mole;
import domain.Player;
import domain.enu.GameMode;
import domain.enu.Level;

import java.nio.file.Path;
import java.util.Collections;
import java.util.List;

/**
 * Set the factory design pattern for the Game class
 * @see Game
 * @see GameService
 */
public class GameFactory {

    private GameFactory() {
        throw new IllegalStateException("Utility class");
    }
    /**
     * Factory method to create a new game with the given players but with default parameters
     * @return Game
     */
    public static Game createGame(List<Player> players) {
        return new Game(GameMode.BATTLE_ROYAL, Level.MEDIUM, Path.of("game.log"), players);
    }

    /**
     * Factory method to create a new game with the given standard parameters
     * @return Game
     */
    public static Game createGame(GameMode mode, Level level, int health, int molesNumber) {
        return new Game(mode, level, Path.of("game.log"), health, molesNumber);
    }
}
