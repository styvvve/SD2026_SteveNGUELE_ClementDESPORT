package main.java.domain;

import java.io.Serializable;

public class Mole implements Serializable {
    private int number;
    private Player location;
    private String content;
    private boolean success;

    public Mole(int number, Player location, String content) {
        this.number = number;
        this.location = location;
        this.content = content;
        this.success = false;
    }

    public int  getNumber() { return number; }
    public Player getLocation() { return location; }
    public String getContent() { return content; }
    public boolean isSuccess() { return success; }


    public void setNumber(int number) { this.number = number; }
    public void setLocation(Player location) { this.location = location; }
    public void setContent(String content) { this.content = content; }
    public void setSuccess(boolean success) { this.success = success; }
}
