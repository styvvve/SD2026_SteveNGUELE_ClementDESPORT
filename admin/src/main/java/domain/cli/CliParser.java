package domain.cli;

import org.apache.commons.cli.*;

/**
 * Class that will parse the command line arguments
 * Class designed on the basis of the documentation of Apache Commons CLI and some online tutorial and discussions on some forums
 * @see <a href="https://commons.apache.org/proper/commons-cli/apidocs/index.html"></a>
 * @see <a href="https://www.baeldung.com/apache-commons-cli"></a>
 * @see <a href="https://www.javaspring.net/blog/parsing-arguments-to-a-java-command-line-program/"></a>
 * @author Steve
 */

public class CliParser {

    private final Options options;
    private final OptionGroup optionGroup;
    private final HelpFormatter formatter;

    public CliParser() {
        this.optionGroup = buildGroup();
        this.options = buildOptions(this.optionGroup);
        this.formatter = new HelpFormatter();
    }

    /**
     * Method to build a group of options of the CLI
     * @return Options
     */
    private OptionGroup buildGroup() {
        OptionGroup group = new OptionGroup();
        group.setRequired(true); //option obligatoire et exclusive

        group.addOption(Option.builder("i")
                .longOpt("init")
                .hasArgs()
                .argName("nom-du-serveur port-du-serveur")
                .desc("Initialize a connection between the administrator and the server")
                .build());

        group.addOption(Option.builder("c")
                .longOpt("config")
                .hasArgs()
                .argName("options de la partie dans cet ordre (espace entre chaque mot : mode niveau vies nombre-de-taupes fichier-mot temps-imparti")
                .desc("Initialize a game and wait for players to join")
                .build());

        group.addOption(Option.builder("s")
                .longOpt("start")
                .hasArg(false)
                .desc("Start the previous configured game")
                .build());

       group.addOption(Option.builder("l")
                .longOpt("list")
                .hasArg(false)
                .desc("The list of players connected")
                .build());

        group.addOption(Option.builder("hi")
                .longOpt("history")
                .hasArg(false)
                .desc("The game history")
                .build());

        group.addOption(Option.builder("h")
                .longOpt("help")
                .hasArg(false)
                .desc("Print help")
                .build());

        return group;
    }

    /**
     * After building the group, we build the options
     * @param group
     * @return Options
     */
    private Options buildOptions(OptionGroup group) {
        Options options = new Options();
        options.addOptionGroup(group);
        return options;
    }

    /**
     * The method that will parse the command line arguments
     * @param args
     * @return CommandLine
     */
    public CommandLine parse(String[] args) {
        try {
            return new DefaultParser().parse(options, args);
        } catch (ParseException e) {
            System.err.println("Error during parsing arguments : " + e.getMessage());
            formatter.printHelp("java -jar game.jar", options);
            System.exit(1);
            return null;
        }
    }

    /**
     * A getter for the options entered by the user
     */
    public String getSelected() {
        return this.optionGroup.getSelected();
    }

    /**
     * Print the help.
     */
    public void printHelp() {
        formatter.printHelp("java -jar game.jar", options);
    }
}
