package domain.factory;


import domain.Game;
import domain.GameService;
import domain.Mole;
import domain.Player;
import domain.enu.GameMode;
import domain.enu.Level;

import java.nio.file.Path;
import java.util.List;

/**
 * Set the factory design pattern for the Game class
 * @see Game
 * @see GameService
 */
public class GameFactory {
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
        Game newGame =  new Game(mode, level, Path.of("game.log"), health);
        newGame.getRounds().forEach(r -> {
            for (int i = 0; i < molesNumber; i++) {
                //add x moles
                r.addMole(new Mole());
            }
        });
    }
}
