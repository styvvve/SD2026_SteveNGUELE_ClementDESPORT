package domain;

import domain.Controller.GameController;
import domain.cli.*;
import domain.cli.command.*;

import java.util.Scanner;

public class App {

    public static void main(String[] args) {

        GameService svr = new GameService();

        Thread orchestrator = new Thread(svr);
        orchestrator.setDaemon(true);
        orchestrator.start();

        //cli
        CommandPrompt prompt = new CommandPrompt();
        CliParser parser = new CliParser();
        CommandRegistry registry = new CommandRegistry();
        registry.register(new StartCommand());
        registry.register(new InitCommand());
        registry.register(new HistCommand());
        registry.register(new ListCommand());
        registry.register(new ConfigureCommand());
        GameController controller = new GameController(svr, parser, registry);

        //Boolean that knows when the party is over
        boolean partyNotOver = true;

        Scanner scanner = new Scanner(System.in);

        while (partyNotOver) {
            String line = prompt.readLine();
            partyNotOver = controller.handleCommand(line);
        }
    }
}
