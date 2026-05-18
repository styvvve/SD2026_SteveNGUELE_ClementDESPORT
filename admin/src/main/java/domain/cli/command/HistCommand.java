package domain.cli.command;

public class HistCommand implements Command {

    @Override
    public String name() {
        return "hist";
    }

    @Override
    public String description() {
        return "Show the history of the game";
    }
}
