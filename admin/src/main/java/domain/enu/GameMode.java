package domain.enu;

/**
 * Game mode of the game (BATTLE_ROYAL, TEAM) or 1, 2 respectively to transfer the mode to the server
 */
public enum GameMode {
    BATTLE_ROYAL(1),
    TEAM(2);

    int number;
    GameMode(int number) { this.number = number; }
    public int getNumber() { return this.number; }
}
