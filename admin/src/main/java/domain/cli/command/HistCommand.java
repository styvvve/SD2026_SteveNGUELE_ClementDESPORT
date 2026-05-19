package domain.cli.command;

import domain.GameService;
import domain.cli.HandleInputs;

public class HistCommand implements Command {

    @Override
    public String name() {
        return "hist";
    }

    @Override
    public String description() {
        return "Show the history of the game";
    }

    @Override
    public void execute(String[] args, GameService svr) {
        svr.handleHistory();
    }
}
