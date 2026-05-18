package domain;

import java.io.Serializable;

/**
 * Player class represents a computer in the distributed system
 */

public class Player implements Serializable {

    private int id;
    private int health;

    /**
     * Complete constructor
     * @param id
     * @param health
     */
    public Player(int id, int health) {
        this.id = id;
        this.health = health;
    }

    /**
     * This code id from me here -> <a href="https://github.com/styvvve/uppaBank/blob/main/src/main/java/bank/domain/Account.java"></a>
     * @param o the reference object with which to compare.
     * @return true if this object is the same as the obj argument; false otherwise.
     */
    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Player)) return false; //si ce n'est pas un Player
        else  return this.id == ((Player) o).id && this.health == ((Player) o).health;
    }

    /**
     * Very simple hashcode
     * @return the hashcode
     */
    @Override
    public int hashCode() {
        return this.id;
    }

    /**
     * Constructor with default health
     * @param id
     */
    public Player(int id) {
        this(id, 100);
    }

    public int getId() { return this.id; }
    public int getHealth() { return this.health; }

    public void setHealth(int health) { this.health = health; }
    public void setId(int id) { this.id = id; }
}
