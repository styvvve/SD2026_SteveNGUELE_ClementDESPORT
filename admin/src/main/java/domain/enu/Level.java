package domain.enu;

/**
 * Level of the game (EASY, MEDIUM, HARD) or 1, 2, 3 respectively to transfer the level to the server
 */
public enum Level {
    EASY(1),
    MEDIUM(2),
    HARD(3);

    int number;
    Level(int number) { this.number = number; }
    public int getNumber() { return this.number; }
}
