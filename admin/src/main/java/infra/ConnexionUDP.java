package infra;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;

/**
 * Class that will manage the connection between the java administrator and the server
 * @author Steve
 */

public class ConnexionUDP {

    private InetAddress adr;
    private DatagramSocket socket;
    private final int serverPort;


    //2 constructors

    /**
     * Constructor with the name of the server and the server port
     */
    public ConnexionUDP(String server, int serverPort) throws SocketException, UnknownHostException {
         this.socket = new DatagramSocket();
         this.socket.setSoTimeout(1000);
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
        byte[] data = new byte[100];
        DatagramPacket packet = new DatagramPacket(data, data.length);

        socket.receive(packet);

        return new String(packet.getData(), 0, packet.getLength(), StandardCharsets.UTF_8);
    }

    /**
     * Function to send a text to the server -> we ll use it to send some text to test the connection with the server at any time
     * @param text the string to send
     * @throws IOException
     *
     */
    public void sendToServer(String text) throws IOException {
        byte[] data = text.getBytes(StandardCharsets.UTF_8);
        DatagramPacket packet = new DatagramPacket(data, data.length, adr, serverPort);

        System.out.println("Socket locale ouverte sur le port : " + this.socket.getLocalPort());

        socket.send(packet);
    }

    /**
     * Method to test if the connection is ok at any time. We test 3 times
     */
    public boolean testConnection() {
        for (int i = 0; i < 3; i++) {
            try {
                System.out.println("Tentative " + (i + 1));
                this.sendToServer("test");
                String response = this.receiveFromServer();
                return response.equals("test");
            } catch (SocketTimeoutException e) {
                try {
                    Thread.sleep(1000); //wait 1s before trying again
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                }
            } catch (IOException e) {
                return false;
            }
        }

        return false;
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
