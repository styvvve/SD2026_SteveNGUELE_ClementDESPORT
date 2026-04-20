package main.java.domain;

import main.java.domain.interfaces.GameObserver;

import java.util.ArrayList;
import java.util.List;

public class Log implements GameObserver {

    private int number;

    public Log(int number) {
        this.number = number;
    }

    //Observer pattern matching
    @Override
    public void saveEachGameLog(Game game) {
        //writing each log to save the game progress
        StringBuilder playersList = new StringBuilder();
        game.getPlayers().forEach(p -> {
            playersList.append(p.getId()).append("\n");
        });
        String myLog = String.format("LOG N°%d. [GAME ID] : %d | [GAME MODE] : %s | [LEVEL] : %s | [ROUND N°] : %d | [PLAYERS] : { %s }",
                game.getId(),
                game.getMode().toString(),
                game.getLevel().toString(),
                game.getRounds().getLast(),
                playersList
                );
    }
}
