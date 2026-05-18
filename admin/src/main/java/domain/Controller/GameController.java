package domain.Controller;

import domain.GameService;
import domain.cli.CliParser;
import domain.cli.command.Command;
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

        if (line == null || line.isBlank()) return false;

        Map<String, String[]> parsed = cliParser.parse(line);

        String commandName = parsed.keySet().iterator().next();
        String[] args = parsed.get(commandName);

        if (commandName.equals("exit")) {
            return false;
        }
        if (commandName.equals("help")) { registry.printHelp(); return true; }

        Command cmd = registry.getCommand(commandName);

        if (cmd == null) { registry.printHelp(); return true; }

        cmd.execute(args, gameService);
        return true;
    }
}
