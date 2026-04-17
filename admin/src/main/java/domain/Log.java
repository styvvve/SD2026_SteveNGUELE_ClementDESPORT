package main.java.domain;

import java.util.ArrayList;
import java.util.List;

public class Log {

    private int number;
    private List<Player> players = new ArrayList<>();
    private List<Mole> moles =  new ArrayList<>();

    public Log(int number) {
        this.number = number;
    }

    public int getNumber() {
        return number;
    }
    public void setNumber(int number) { this.number = number; }
    public List<Player> getPlayers() { return players; }
    public void addPlayer(Player player) { this.players.add(player); }
    public void addMole(Mole mole) { this.moles.add(mole); }

    public int removePlayer(Player player) {
        if (this.players.contains(player)) {
            players.remove(player);
            return 1;
        }
        return 0;
    }
}
