package infra;

import domain.interfaces.ConnectionObserver;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

/**
 * Class to test the connection between the server and the admin each 2 seconds
 * @see <a href=https://www.baeldung.com/java-executor-service-tutorial></a>
 * @see <a href="https://www.geeksforgeeks.org/java/what-is-java-executor-framework/"></a>
 */
public class TestConnectionUDP {

    private final ConnexionUDP connexion;
    private final ScheduledExecutorService scheduler;
    private boolean lastState = true;
    private final List<ConnectionObserver> observers = new ArrayList<>();

    public TestConnectionUDP(ConnexionUDP connexion) {
        this.connexion = connexion;
        this.scheduler = Executors.newSingleThreadScheduledExecutor();
    }

    public void addObserver(ConnectionObserver obs) {
        observers.add(obs);
    }

    /**
     * Method to start the test connection
     */
    public void start() {
        int delay = 6;
        scheduler.scheduleAtFixedRate(() -> {
            boolean isConnected = connexion.testConnection();

            if (!isConnected && lastState) {
                //if we lose connection and the lastState was true, we notify all the observers
                observers.forEach(ConnectionObserver::connectionLost);
            } else if (isConnected && !lastState) {
                //if we reconnect and the lastState was false, we notify all the observers
                observers.forEach(ConnectionObserver::connectionRestored);
            }

            lastState = isConnected;
        }, 1, delay, TimeUnit.SECONDS);
    }

    public void stop() {
        scheduler.shutdown();
    }
}
