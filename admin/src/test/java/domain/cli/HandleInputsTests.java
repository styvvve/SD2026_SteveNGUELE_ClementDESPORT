package domain.cli;

import infra.ConnexionUDP;
import infra.ConnexionUDPFactory;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.mock;

public class HandleInputsTests {

    @Test
    public void shouldReturnOkWhenConnectionSucceeds() throws Exception {
        ConnexionUDP mockConn = null; //mock the behavior of the UDP connection class

        ConnexionUDPFactory fact = (s, p) -> mockConn;

        Response<ConnexionUDP> res = HandleInputs.initializeConnection("localhost", 3000, fact);

        assertTrue(res.isOk());
    }
}
