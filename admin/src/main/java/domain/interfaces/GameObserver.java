package main.java.domain.interfaces;

import main.java.domain.Game;

import java.nio.file.Path;

public interface GameObserver {
    void saveEachGameLog(Game game, int number, Path path);
}
