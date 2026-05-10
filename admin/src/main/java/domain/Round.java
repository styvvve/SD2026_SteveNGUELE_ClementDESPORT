package domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Round class represents a round of the game. Each round has a different number of players and different mole
 * The number of moles for one round is 1 by default
 * @see Player
 * @see Mole
 * @see Game
 */
public class Round implements Serializable {
    private final int roundNumber;
    private List<Player> players = new ArrayList<>();
    private List<Mole> moles = new ArrayList<>();

    /**
     * Very standard constructor
     * @param roundNumber
     */
    public Round(int roundNumber) {
        this.roundNumber = roundNumber;
    }

    public int getRoundNumber() {
        return roundNumber;
    }
    public List<Mole> getMoles() { return this.moles; }
    public void setRoundNumber(int roundNumber) {}
    public void addMole(Mole mole) { this.moles.add(mole); }
}
