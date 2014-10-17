/**
 * ChatServer.java:<p>
 * realizes communication with other clients through a central chat server.
 *
 * @author Christopher Tran (CSS, University of Washington, Bothell)
 * @since 4/20/14
 * @version 4/20/14
 */
import java.net.*; // For Socket
import java.io.*; //For IOException
import java.util.Iterator; //For List Iteration
import java.util.Vector; //For Vector

public class ChatServer {
    private ServerSocket server = null; // Server Socket
    private Vector<Connection> connectionList = new Vector<Connection>(); // Vector for storing multiple clients
    private Iterator<Connection> iter1; //Vector iterator

    /**
     * Creates a Server Socket and listens for ChatClients to establish a connection
     * Goes into a while loop in that :<p>
     *
     * <ol>
     *     <li>accepts any incoming socket connections and adds clients to list</li>
     *     <li>Iterates through client list for incoming messages</li>
     *     <li>Iterates through client list and sends message to all except sender</li>
     * </ol>
     *
     * @param port Listening port for Chat Server
     */
    public ChatServer(int port) {
        try {
            //Create a listening socket
            System.out.println("Binding to port " + port + ", please wait  ...");
            server = new ServerSocket(port);
            //Set timeout of server to 500ms due to blocking calls
            server.setSoTimeout(500);
            System.out.println("Server started: " + server);
            System.out.println("Waiting for Clients");

            while(true) {
                try {
                    //Accept any existing socket connections
                    Socket s = server.accept();
                    System.out.println("Client connected from "+ s.getLocalAddress().getHostName());
                    //Add client to client list
                    connectionList.add(new Connection(s));
                } catch(SocketTimeoutException e) {
                }
                //Iterate starting at beginning of clientlist
                iter1 = connectionList.iterator();

                //Check all clients for incoming messages
                while(iter1.hasNext()) {
                    //System.out.println("Checking for messages");
                    Connection c = iter1.next();
                    //if a client has a message, forward to all other clients
                    if(c.hasMessage()) {
                        while(c.hasMessage()) {
                            //Read the incoming message
                            String message = c.readMessage();
                            System.out.println("Message received from " + c.name());
                            //Second iterator to send message to all clients
                            Iterator<Connection> iter2 = connectionList.iterator();
                            while (iter2.hasNext()) {
                                Connection c2 = iter2.next();
                                //Check if sending to the message source and skip
                                if(c.equals(c2)) {
                                    continue;
                                }
                                System.out.println("Sending message from " + c.name() + " to " + c2.name());
                                //If sending a message results in error, assume client is invalid and remove
                                //from client list
                                try {
                                    //Send message to client
                                    c2.writeMessage(message);
                                } catch (IOException e) {
                                    //remove from client list
                                    System.out.println("Connection lost to " + c2.name());
                                    c2.close();
                                    iter2.remove();
                                }
                            }
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Usage: java ChatServer <port>
     *
     *
     * @param args Receives a port number
     */
    public static void main(String args[]) {
        ChatServer server = null;
        //Check args length, should be equal to 1 for a single argument port
        if (args.length != 1) {
            System.out.println("Usage: java ChatServer port");
        } else {
            //Create new ChatServer with port
            server = new ChatServer(Integer.parseInt(args[0]));
        }
    }
}

/**
 *
 */
class Connection {
    private Socket socket;
    private InputStream rawIn;
    private DataInputStream streamIn;
    private DataOutputStream streamOut;
    private String name;
    private int port;

    /**
     *  Connection Constructor
     *  Takes a valid socket and creates a persistent connection
     *
     * @param s
     */
    public Connection(Socket s) {
        socket = s;
        try {
            port = socket.getPort();
            rawIn = socket.getInputStream();
            streamIn = new DataInputStream(rawIn);
            streamOut = new DataOutputStream(socket.getOutputStream());
            name = streamIn.readUTF();
            streamOut.writeUTF("Your name is: " + name);
            streamOut.flush();
            System.out.println("Client " + name + " has connected");
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Reads a message from the InputStream
     * as a string
     *
     * @return String
     * @throws IOException
     */
    public String readMessage() throws IOException {
        if(hasMessage()) {
            return name + ": " + streamIn.readUTF();
        } else {
            return null;
        }
    }

    /**
     * Checks if the Connection has a message
     *
     * @return Boolean
     * @throws IOException
     */
    public boolean hasMessage() throws IOException{
        return rawIn.available() > 0;
    }

    /**
     * Writes a message to the Connection to send to remote client
     *
     * @param str String with message
     * @throws IOException
     */
    public void writeMessage(String str) throws IOException {
            streamOut.writeUTF(str);
            streamOut.flush();
    }

    /**
     *
     * @return String name
     */
    public String name() {
        return name;
    }

    /**
     * Close the open sockets
     */
    public void close() {
        try {
            streamOut.close();
            streamIn.close();
            rawIn.close();
            socket.close();
        } catch (IOException e) {
            System.out.println("error Closing");
        }
    }

    /**
     * Compared two connection objects to determine equality
     *
     * Connection objects are equal if the name and port
     * are identical
     *
     * @param obj Connection object
     * @return
     */
    public boolean equals(Object obj) {
        if(obj == null || !(obj instanceof  Connection)) {
            return false;
        }
        if(obj == this) {
            return true;
        }

        Connection rhs = (Connection) obj;
        if(this.name == rhs.name && this.port == rhs.port) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * hashCode implementation to work with List functions
     *
     * @return int
     */
    public int hashCode() {
        int hash = 100;
        hash = hash + port;
        return hash;
    }
}