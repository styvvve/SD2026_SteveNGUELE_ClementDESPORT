package domain.cli.command;

import domain.GameService;
import domain.cli.HandleInputs;

public class ConfigureCommand implements Command {

    @Override
    public String name() {
        return "configure";
    }

    @Override
    public String description() {
        return "Configure the game";
    }

    @Override
    public void execute(String[] args, GameService svr) {
        HandleInputs.configureGame(args, svr.getConnection());
    }
}
