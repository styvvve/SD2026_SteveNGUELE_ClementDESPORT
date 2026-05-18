package domain.cli.command;

import domain.GameService;

public class StartCommand implements Command {

    @Override
    public String name() {
        return "start";
    }

    @Override
    public String description() {
        return "Start a new game";
    }

    @Override
    public void execute(String[] args, GameService svr) {
        svr.handleStart();
    }
}
