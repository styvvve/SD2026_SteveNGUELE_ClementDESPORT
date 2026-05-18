package domain.cli.command;

public class StartCommand implements Command {

    @Override
    public String name() {
        return "start";
    }

    @Override
    public String description() {
        return "Start a new game";
    }

}
