package main.java.infra;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.*;

/**
 * Class that will manage the connection between the java administrator and the server
 * @author Steve
 */

public class connexionUDP extends Thread {

    private InetAddress adr;
    private DatagramSocket socket;
    private DatagramPacket packet;


    //2 constructors

    /**
     * Constructor for any port
     *
     */
    public connexionUDP(String server) {
        try {
            this.socket = new DatagramSocket(4000);
            adr = InetAddress.getByName(server);
        } catch (SocketException s) {
            System.out.println("Error during socket creation " + s);
        } catch (UnknownHostException u) {
            System.out.println("Unknow host " + u);
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
