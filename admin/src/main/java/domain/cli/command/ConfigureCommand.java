package domain.cli.command;

public class ConfigureCommand implements Command {

    @Override
    public String name() {
        return "configure";
    }

    @Override
    public String description() {
        return "Configure the game";
    }

}
