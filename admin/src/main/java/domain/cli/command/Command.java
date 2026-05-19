package domain.cli.command;

import domain.GameService;

/**
 * All the conception of this CLI is largely inspired from the TOO course and
 */
public interface Command {
    String name();
    String description();
    void execute(String[] args, GameService svr);
}
