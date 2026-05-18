package domain.cli.command;

import java.util.ArrayList;
import java.util.List;

/**
 * Class to register all the commands and print a help
 */
public class CommandRegistry {

    public final List<Command> commands = new ArrayList<>();

    /**
     * Register a new comman
     * @param command the command to register
     */
    public void register(Command command) {
        commands.add(command);
    }

    /**
     * Get a command by name
     * @param commandName the name of the command
     * @return the command or null if not found
     */
    public Command getCommand(String commandName) {
        return commands.stream()
                .filter(c -> c.name().equalsIgnoreCase(commandName))
                .findFirst()
                .orElse(null);
    }

    public void printHelp() {
        System.out.println("Welcome to the Whack-a-mole game!");
        System.out.println("Available commands:");
        for (Command command : commands) {
            System.out.println(command.name() + " -- " + command.description());
        }
    }
}
