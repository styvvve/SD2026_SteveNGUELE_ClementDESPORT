package domain.cli.command;

import domain.GameService;
import domain.cli.HandleInputs;

public class InitCommand implements Command {

    @Override
    public String name() {
        return "init";
    }

    @Override
    public String description() {
        return "Initialize the game";
    }

    @Override
    public void execute(String[] args, GameService svr) {
        svr.handleInitialize(args);
    }
}
