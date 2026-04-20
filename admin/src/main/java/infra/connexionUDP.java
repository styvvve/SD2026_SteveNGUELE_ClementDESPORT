package main.java.infra;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * Class that will manage the connection between the java administrator and the server
 * @author Steve
 */

public class connexionUDP extends Thread {

    InetAddress adr;
    DatagramSocket socket;
    DatagramPacket packet;

    //constructor for any port and a port choiced
    //
    public connexionUDP() {
        try {
            this.socket = new DatagramSocket(4000);
        } catch (SocketException s) {
            System.out.println("Error during socket creation " + s);
        }
    }

    public connexionUDP(int port) {
        try {
            this.socket = new DatagramSocket(port);
        } catch (SocketException s) {
            System.out.println("Error during socket creation " + s);
        }
    }

    //create a packet of Game
}
