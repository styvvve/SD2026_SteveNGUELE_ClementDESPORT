package domain.exception;

public class NotEnoughPlayersException extends RuntimeException {
    public NotEnoughPlayersException() {}
    public NotEnoughPlayersException(String message) {
        super(message);
    }
}
