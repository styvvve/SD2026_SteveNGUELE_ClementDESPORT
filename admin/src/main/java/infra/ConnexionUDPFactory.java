package infra;

import java.net.SocketException;
import java.net.UnknownHostException;

/**
 * This interface is set to be used for the unit tests, but we ll use it for another reason of conception
 */
@FunctionalInterface
public interface ConnexionUDPFactory {
    ConnexionUDP create(String server, int serverPort) throws SocketException, UnknownHostException;
}
