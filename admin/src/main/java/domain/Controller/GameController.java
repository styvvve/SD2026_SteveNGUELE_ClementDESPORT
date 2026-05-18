package domain.Controller;

import domain.GameService;
import domain.cli.CliParser;
import domain.cli.command.CommandRegistry;

import java.util.Map;

public class GameController {

    private final CliParser cliParser;
    private final GameService gameService;
    private final CommandRegistry registry;

    public GameController(GameService gameService, CliParser cliParser, CommandRegistry registry) {
        this.gameService = gameService;
        this.cliParser = cliParser;
        this.registry = registry;
    }

    public boolean handleCommand(String line) {

        if (line == null) return false;

        Map<String, String[]> cmd = cliParser.parse(line);

        String commandName = cmd.keySet().toString();

        if (commandName.equals("help")) {
            registry.printHelp();
            return false;
        }

        String[] args = cmd.get(commandName);

        if (commandName.equals("exit")) {
            return false;
        }

        switch (commandName) {
            case "init" -> gameService.handleInitialize(args);
            case "configure" -> gameService.handleConfigure(args);
            case "start" -> gameService.handleStart();
            case "list" -> gameService.handleListPlayers();
            case "hist" -> gameService.handleHistory();
            default -> registry.printHelp();
        }

        return true;
    }
}
