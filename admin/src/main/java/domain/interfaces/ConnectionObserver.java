package domain.interfaces;

/**
 * Observer interface for the connection. Set the observer design pattern
 * @see <a href=https://refactoring.guru/design-patterns/observer></a>
 */
public interface ConnectionObserver {
    void connectionLost();
    void connectionRestored();
}
