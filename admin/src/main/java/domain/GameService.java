package domain;

import java.util.ArrayList;
import java.util.List;

/**
 * Centralized service for the game, it's the king instance
 * @author Steve
 * @version 1.0
 */
public class GameService {

    private final List<Game> games = new ArrayList<>();

    public List<Game> getGames() { return this.games; }

    public void addGame(Game game) {
        this.games.add(game);
    }
}
