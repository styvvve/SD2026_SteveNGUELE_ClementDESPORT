package main.java.domain;

import java.io.Serializable;

/**
 * Player class represents a computer in the distributed system
 */

public class Player implements Serializable {

    private int id;
    private int health;

    public Player(int id, int health) {
        this.id = id;
        this.health = health;
    }

    public int getId() { return this.id; }
    public int getHealth() { return this.health; }

    public void setHealth(int health) { this.health = health; }
    public void setId(int id) { this.id = id; }
}
