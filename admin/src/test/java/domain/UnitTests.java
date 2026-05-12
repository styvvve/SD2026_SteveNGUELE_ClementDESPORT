package domain;

import domain.enu.GameMode;
import domain.enu.Level;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

public class UnitTests {

    Game newGame;

    @BeforeEach
    public void setup() {
        newGame = new Game(GameMode.BATTLE_ROYAL, Level.EASY, Path.of("test.log"));
    }

    @Test
    public void testGameClass() {

        assertEquals(GameMode.BATTLE_ROYAL, newGame.getMode());
        assertEquals(Level.EASY, newGame.getLevel());

        assertEquals(6, newGame.getRounds().size());
        assertEquals(0, newGame.getPlayers().size());

        newGame.addPlayer(new Player(1, 5));

        assertEquals(1, newGame.getPlayers().size());

    }

    @Test
    public void shouldCreateAValidStringGameObject() {
        String gameString = newGame.toString();
        assertEquals("|1|1|3|10|6|6", gameString);
    }

    /*@Test
    public void shouldCreateAValidLogGame() {

        GameObserver obs = new Log();
        newGame.addObserver(obs);

        newGame.addPlayer(new Player(1, 5));
        newGame.addPlayer(new Player(12, 5));
        newGame.gameService();

        assertTrue(Files.exists(Path.of("test.log")));

    }*/
}
