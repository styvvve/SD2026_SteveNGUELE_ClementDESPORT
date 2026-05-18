package domain.cli.command;

public class ExitCommand implements Command {

    @Override
    public String name() {
        return "exit";
    }

    @Override
    public String description() {
        return "Exit the application";
    }

}
