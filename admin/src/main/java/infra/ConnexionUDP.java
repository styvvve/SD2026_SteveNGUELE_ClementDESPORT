package infra;

import domain.Game;
import domain.cli.Response;

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
         System.out.println("connexion UDP OK " + adr + serverPort + "\n");
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
     * @throws IOException if sending fails
     */
    public void sendToServer(String text) throws IOException {
        byte[] data = text.getBytes(StandardCharsets.UTF_8);
        DatagramPacket packet = new DatagramPacket(data, data.length, adr, serverPort);

        socket.send(packet);
    }

    /**
     * Method to test if the connection is ok at any time. We test it 3 times
     */
    public boolean testConnection() {
        for (int i = 0; i < 3; i++) {
            try {
                //System.out.println("Tentative " + (i + 1));
                this.sendToServer("test");
                String response = this.receiveFromServer();
                return response.equals("test");
            } catch (SocketTimeoutException e) {
                try {
                    Thread.sleep(2000); //wait 2s before trying again
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                }
            } catch (IOException e) {
                return false;
            }
        }

        return false;
    }

    /**
     * Send a message to the server with the communication protocol
     * <ul>
     *     <li>configure 'c' - to configure a game</li>
     *     <li>start 's' - to start a game</li>
     * </ul>
     */
    public String createMessage(char command, Game game) throws IOException {
        return switch (command) {
            case 'c' -> "configure" + game.serializeGame();
            case 's' -> "start";
            default -> throw new IllegalArgumentException("Invalid command");
        };
    }

    /**
     * The protocol of the communication with the server is :
     */
    public boolean sendMessage(char command, Game game) throws IOException {
        String msg = this.createMessage(command, game);

        final int MAX_RETRIES = 3;
        final int MAX_DELAY_MS = 5000;
        for (int i = 0; i < MAX_RETRIES; i++) {

            try {
                this.sendToServer(msg);
                return true;
            } catch (IOException e) {
                try {
                    Thread.sleep(MAX_DELAY_MS);
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                    return false;
                }
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
