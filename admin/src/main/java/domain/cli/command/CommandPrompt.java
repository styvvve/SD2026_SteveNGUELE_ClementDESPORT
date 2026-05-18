package domain.cli.command;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Class to handle the user's prompt in the command line
 */
public class CommandPrompt {

    private final String promptSymbol;
    private final BufferedReader reader;

    public CommandPrompt() {
        this.promptSymbol = "> ";
        this.reader = new BufferedReader(new InputStreamReader(System.in));
    }

    public CommandPrompt(String promptSymbol, BufferedReader reader) {
        this.promptSymbol = promptSymbol;
        this.reader = reader;
    }

    public void printPrompt() {
        System.out.print(promptSymbol);
        System.out.flush(); // force the print "flush"
    }

    /**
     * Read a line with blocking
     */
    public String readLine() {
        printPrompt();

        try {
            String line = reader.readLine();
            if (line == null) {
                return "";
            }

            return line.trim();
        } catch (IOException e) {
            System.err.println("READING ERROR : " + e.getMessage());
            return "";
        }
    }
}
