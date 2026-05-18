package domain.cli.command;

public class ListCommand implements Command {

    @Override
    public String name() {
        return "list";
    }

    @Override
    public String description() {
        return "List all the players";
    }

}
