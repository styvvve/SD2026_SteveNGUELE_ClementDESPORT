package domain.cli;


import java.util.Arrays;
import java.util.List;
import java.util.Map;

/**
 * Class that will parse the command line arguments
 * @author Steve
 */

public class CliParser {

    public Map<String, String[]> parse(String command) {
        String[] args = command.trim().split(" ");

        if (args.length == 0) return null;

        String commandName = args[0];
        String[] commandArgs = Arrays.copyOfRange(args, 1, args.length);

        return Map.of(commandName, commandArgs);
    }
}
