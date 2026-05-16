package domain.Controller;

import domain.GameService;
import domain.cli.CliParser;
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
            case "c" -> System.out.println("configure");
            case "s" -> System.out.println("start");
            case "l" -> System.out.println("liste des joueurs");
            case "hi" -> System.out.println("historique des parties");
        }
    }
}
