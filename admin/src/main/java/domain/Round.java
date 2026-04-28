package main.java.domain;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;
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

    public int getRoundNumber() {
        return roundNumber;
    }
    public void setRoundNumber(int roundNumber) {}

    public byte[] toBytes() {
        try (ByteArrayOutputStream bos = new ByteArrayOutputStream();
             ObjectOutputStream oos = new ObjectOutputStream(bos)) {
            oos.writeObject(this);

            return bos.toByteArray();
        } catch (IOException e) {
            System.out.println("Error during Round to bytes conversion " + e);
        }

        return null;
    }
}
