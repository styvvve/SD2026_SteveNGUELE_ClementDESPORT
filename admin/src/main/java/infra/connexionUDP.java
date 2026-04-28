package main.java.infra;

import main.java.domain.Round;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.*;
import java.nio.charset.StandardCharsets;

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

    //conversion to byte


    /**
     * Function to wait a packet from the server
     * @return the string received from the server
     * @throws IOException
     */
    public String receiveFromServer() throws IOException {
        byte[] data = new byte[1024];
        packet = new DatagramPacket(data, data.length);


        socket.receive(packet);
        return new String(packet.getData(), 0, packet.getLength(), StandardCharsets.UTF_8);
    }

    /**
     * Function to send data to the server
     * @param chaine
     * @throws IOException
     */
    public void sendToServer(String chaine) throws IOException {
        byte[] data = chaine.getBytes();
        packet.setData(data);
        packet.setLength(data.length);

        socket.send(packet);
    }

    /*public int sendRound(Round round) {
        try (ByteArrayOutputStream bos = new ByteArrayOutputStream();
             ObjectOutputStream oos = new ObjectOutputStream(bos)) {
            oos.writeObject(round);

            packet = new DatagramPacket((byte[]) oos, ((byte[]) oos).length);
        } catch (IOException e) {
            System.out.println("Error during sendRound " + e);
            return -1;
        }

        return 0;
    }*/
}
