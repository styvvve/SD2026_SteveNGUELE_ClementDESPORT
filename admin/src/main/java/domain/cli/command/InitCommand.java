package domain.cli.command;

public class InitCommand implements Command {

    @Override
    public String name() {
        return "init";
    }

    @Override
    public String description() {
        return "Initialize the game";
    }

}
