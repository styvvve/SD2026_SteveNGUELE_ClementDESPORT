package domain;

import domain.cli.CliParser;
import domain.cli.HandleInputs;
import domain.cli.Response;
import domain.factory.GameFactory;
import domain.interfaces.ConnectionObserver;
import infra.ConnexionUDP;
import infra.ConnexionUDPFactory;
import infra.TestConnectionUDP;
import org.apache.commons.cli.CommandLine;

import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

public class App {

    public static void main(String[] args) {

        ConnectionObserver svr = new GameService();

        //Boolean that knows when the party is over
        boolean partyOver = false;

        while (!partyOver) {

        }
    }
}
