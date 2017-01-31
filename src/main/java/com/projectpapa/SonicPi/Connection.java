package com.projectpapa.SonicPi;

import com.illposed.osc.*;

import java.io.IOException;
import java.net.InetAddress;
import java.util.*;

/**
 * This class represents a connection to Sonic Pi, which can be used to
 * execute Sonic Pi code or suspend all running code on the server.
 * Commands will raise IOException if connection with the server cannot be
 * established.
 */
public class Connection {
    public static String RUN_COMMAND = "/run-code";
    public static String STOP_COMMAND = "/stop-all-jobs";
    public static String PING_COMMAND = "/ping";
    public static int PORT = 4557;
    public static String GUI_ID = "PROJECT_PAPA";

    private static OSCPortOut client;

    private OSCPortOut getClient() throws IOException {
        if (client == null) {
            client = new OSCPortOut(InetAddress.getByName("localhost"), PORT);
        }
        return client;
    }

    /**
     * Creates a new Sonic Pi connection.
     * The underlying connection is a singleton, so only one connection will
     * exist at any one time.
     *
     * @throws IOException
     */
    public Connection() throws IOException {
        getClient();
    }

    /**
     * Sends the code of a Command object to be run.
     *
     * @param obj The object to convert to ruby code and run.
     * @throws IOException
     */
    public void run(Command obj) throws IOException {
        run(obj.toCode());
    }

    /**
     * Sends some code to the Sonic Pi server to be run.
     *
     * @param code Ruby code to be run by the server.
     * @throws IOException
     */
    public void run(String code) throws IOException {
        sendCommand(RUN_COMMAND, code);
    }

    /**
     * Sends a stop signal to stop all runs on the Sonic Pi server.
     *
     * @throws IOException
     */
    public void stop() throws IOException {
        sendCommand(STOP_COMMAND);
    }

    /**
     * Pings the server.
     * TODO: receive /ack messages to indicate success
     * @throws IOException
     */
    public void ping() throws IOException {
        sendCommand(PING_COMMAND);
    }

    private void sendCommand(String callType, Object... args) throws IOException {
        OSCPortOut client = getClient();

        ArrayList<Object> payload = new ArrayList<Object>();
        payload.add(GUI_ID);
        Collections.addAll(payload, args);

        OSCMessage message = new OSCMessage(callType, payload);
        client.send(message);
    }

    public static void main(String[] args) throws IOException {
        Connection pi = new Connection();

        pi.run("live_loop :test do\nsample :bd_haus;\nsleep 0.5\nend");
        //pi.stop();
    }
}

