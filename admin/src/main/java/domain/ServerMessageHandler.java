package domain;

import domain.interfaces.ServerHandler;

/**
 * Class that will handle the messages received from the server.
 * Messages are received in a different thread than the main thread in the form: "method|parameter"
 * @see ServerHandler
 * @see infra.ConnexionUDP#listenToServer(ServerHandler)
 */
public class ServerMessageHandler implements ServerHandler {

    private final GameService gameService;

    public ServerMessageHandler(GameService gameService) {
        this.gameService = gameService;
    }

    @Override
    public void handle(String message) {
        String[] messageParts = message.split("\\|");
        String method = messageParts[0];
        String parameter = messageParts[1];

        switch (method) {
            case "addPlayer" -> gameService.addPlayer(Integer.parseInt(parameter));
            case "removePlayer" -> gameService.removePlayer(Integer.parseInt(parameter));
            case "playerWin" -> gameService.playerWin(Integer.parseInt(parameter));
            case "playerLose" -> gameService.playerLose(Integer.parseInt(parameter));
        }
    }

}
