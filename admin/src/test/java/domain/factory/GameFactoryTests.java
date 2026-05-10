package domain.factory;

import domain.Game;
import domain.Player;
import domain.enu.GameMode;
import domain.enu.Level;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Tests for the GameFactory class
 */
public class GameFactoryTests {

    List<Player> players = new ArrayList<>();

    @BeforeEach
    public void setup() {
        players.add(new Player(1, 5));
        players.add(new Player(2, 5));
    }

    @Test
    public void shouldCreateGameWithDefaultParametersAndGivenPlayers() {

        Game newG = GameFactory.createGame(players);

        assertEquals(GameMode.BATTLE_ROYAL, newG.getMode());
        assertEquals(Level.MEDIUM, newG.getLevel());
        assertEquals(newG.getPlayers().getFirst(), players.getFirst());
        assertEquals(newG.getPlayers().getLast(), players.getLast());
    }

    /*@Test
    public void shouldCreateGameWithGivenParameters() {

        Game newG = GameFactory.createGame(GameMode.BATTLE_ROYAL, Level.EASY, 5, 3);

        assertEquals(GameMode.BATTLE_ROYAL, newG.getMode());
        assertEquals(6, newG.getRounds().size());
        assertEquals(Level.EASY, newG.getLevel());
        for (int i = 0; i < 6; i++) {
            assertEquals(3, newG.getRounds().get(i).getMoles().size());
        }
    }*/
}
