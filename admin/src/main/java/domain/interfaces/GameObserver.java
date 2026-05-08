package domain.interfaces;


import domain.Game;

import java.nio.file.Path;

/**
 * Interface to set the Observer design pattern
 */
public interface GameObserver {
    void saveEachGameLog(Game game, int number, Path path);
}
