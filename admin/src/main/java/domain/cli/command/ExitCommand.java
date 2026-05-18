package domain.cli.command;

import domain.GameService;
import domain.cli.HandleInputs;

public class ExitCommand implements Command {

    @Override
    public String name() {
        return "exit";
    }

    @Override
    public String description() {
        return "Exit the application";
    }

    @Override
    public void execute(String[] args, GameService svr) {
        System.exit(0);
    }
}
