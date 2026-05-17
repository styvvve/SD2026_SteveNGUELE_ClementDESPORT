package domain.Controller;

import domain.GameService;
import domain.cli.CliParser;
import domain.interfaces.ConnectionObserver;
import org.apache.commons.cli.CommandLine;

public class GameController {

    private final GameService gameService;

    public GameController(GameService gameService) {
        this.gameService = gameService;
    }

    public void workWithCommand(String[] args) {
        CliParser cli = new CliParser();
        CommandLine cmd = cli.parse(args);

        if (cmd.hasOption("h")) {
            cli.printHelp();
            System.exit(0);
        }

        switch (cli.getSelected()) {
            case "i" -> gameService.handleInitialize(cmd);
            case "c" -> gameService.handleConfigure(cmd);
            case "s" -> gameService.handleStart(cmd);
            case "l" -> gameService.handleListPlayers();
            case "hi" -> gameService.handleHistory();
        }
    }
}
