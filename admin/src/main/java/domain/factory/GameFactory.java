package main.java.domain.factory;

import main.java.domain.Game;
import main.java.domain.Player;
import main.java.enu.GameMode;
import main.java.enu.Level;

import java.nio.file.Path;
import java.util.List;

/**
 * Set the factory design pattern for the Game class
 * @see main.java.domain.Game
 * @see main.java.domain.GameService
 */
public class GameFactory {
    /**
     * Factory method to create a new game with the given players but with default parameters
     * @return Game
     */
    public static Game createGame(List<Player> players) {
        return new Game(GameMode.BATTLE_ROYAL, Level.MEDIUM, Path.of("game.log"), players);
    }
}
