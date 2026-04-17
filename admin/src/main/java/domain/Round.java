package main.java.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Round implements Serializable {
    private int roundNumber;
    private List<Player> players = new ArrayList<>();
    private List<Mole> moles = new ArrayList<>();

    public Round(int roundNumber) {
        this.roundNumber = roundNumber;
    }
}
