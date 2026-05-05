package main.java;

import main.java.infra.connexionUDP;

import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Main {

    public static void main(String[] args) {

        //initialize the connection
        connexionUDP connexion = null; 
        
        try {
            connexion = new connexionUDP("scinfe182", 3000);
        } catch (SocketException | UnknownHostException e) {
            System.out.println("Error during connexion " + e);
        }
        try {
            connexion.sendToServer("test");
        } catch (IOException e) {
            System.out.println("Error during sendToServer " + e);
        }

        try {
            String chaineRecu = connexion.receiveFromServer();
            System.out.println(chaineRecu);
        } catch (IOException e) {
            System.out.println("Error during receiveFromServer " + e);
        }
    }
}
