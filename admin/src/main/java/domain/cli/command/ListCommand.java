package domain.cli.command;

import domain.GameService;

public class ListCommand implements Command {

    @Override
    public String name() {
        return "list";
    }

    @Override
    public String description() {
        return "List all the players";
    }

    @Override
    public void execute(String[] args, GameService svr) {
        svr.handleListPlayers();
    }
}
