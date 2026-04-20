package main.java.domain.interfaces;

import main.java.domain.Game;

public interface GameObserver {
    void saveEachGameLog(Game game);
}
