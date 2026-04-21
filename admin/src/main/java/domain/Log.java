package main.java.domain;

import main.java.domain.interfaces.GameObserver;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;

public class Log implements GameObserver {

    //Observer pattern matching
    @Override
    public void saveEachGameLog(Game game, int number, Path path) {
        //writing each log to save the game progress
        StringBuilder playersList = new StringBuilder();
        game.getPlayers().forEach(p -> {
            playersList.append(p.getId()).append("\n");
        });
        String myLog = String.format("LOG N°%d. [GAME ID] : %s | [GAME MODE] : %s | [LEVEL] : %s | [ROUND N°] : %d | [PLAYERS] : { %s }",
                number,
                game.getId(),
                game.getMode().toString(),
                game.getLevel().toString(),
                game.getRounds().getLast().getRoundNumber(),
                playersList
                );

        try {
            Files.writeString(path, myLog,
                    StandardCharsets.UTF_8,
                    StandardOpenOption.CREATE,
                    StandardOpenOption.APPEND);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
