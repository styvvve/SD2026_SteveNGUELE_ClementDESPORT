package main.java.domain;

import main.java.enu.GameMode;
import main.java.enu.Level;

import java.io.Serializable;
import java.util.List;

public class Game implements Serializable {

    private String id;
    private GameMode mode;
    private List<Player> players;
    private Level level;

}
