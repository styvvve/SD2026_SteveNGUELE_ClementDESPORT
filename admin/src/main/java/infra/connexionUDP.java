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

public class connexionUDP {

    private InetAddress adr;
    private DatagramSocket socket;
    private final int serverPort;


    //2 constructors

    /**
     * Constructor with the name of the server and the server port
     */
    public connexionUDP(String server, int serverPort) throws SocketException, UnknownHostException {
         this.socket = new DatagramSocket();
         adr = InetAddress.getByName(server);
         this.serverPort = serverPort;
         System.out.println("connexion UDP OK " + adr + "\n");
    }

    /**
     * Function to wait a packet from the server
     * @return the string received from the server
     * @throws IOException if receiving fails
     */
    public String receiveFromServer() throws IOException {
        byte[] data = new byte[11];
        DatagramPacket packet = new DatagramPacket(data, data.length);

        socket.receive(packet);

        return new String(packet.getData(), 0, packet.getLength(), StandardCharsets.UTF_8);
    }

    /**
     * Function to send data to the server
     * @param text the string to send
     * @throws IOException
     */
    public void sendToServer(String text) throws IOException {
        byte[] data = text.getBytes(StandardCharsets.UTF_8);
        DatagramPacket packet = new DatagramPacket(data, data.length, adr, serverPort);

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
