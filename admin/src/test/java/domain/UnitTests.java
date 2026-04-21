package test.java.domain;

import main.java.domain.Game;
import main.java.domain.interfaces.GameObserver;
import main.java.domain.Log;
import main.java.domain.Player;
import main.java.enu.GameMode;
import main.java.enu.Level;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

public class UnitTests {

    @Test
    public void testGameClass() {
        Game newGame = new Game(GameMode.BATTLE_ROYAL, Level.EASY, Path.of("rien"));

        assertEquals(GameMode.BATTLE_ROYAL, newGame.getMode());
        assertEquals(Level.EASY, newGame.getLevel());

        assertEquals(0, newGame.getRounds().size());
        assertEquals(0, newGame.getPlayers().size());

        newGame.addPlayer(new Player(1, 5));

        assertEquals(1, newGame.getPlayers().size());

    }

    @Test
    public void shouldCreateAValidLogGame() {

        Game newGame = new Game(GameMode.BATTLE_ROYAL, Level.EASY, Path.of("test.log"));

        GameObserver obs = new Log();
        newGame.addObserver(obs);

        newGame.addPlayer(new Player(1, 5));
        newGame.addPlayer(new Player(12, 5));
        newGame.gameService();

        assertTrue(Files.exists(Path.of("test.log")));

    }
}
