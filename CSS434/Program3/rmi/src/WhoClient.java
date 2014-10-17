/**
 * Created by Christopher on 5/18/2014.
 */

import java.rmi.*;
import java.util.*;

public class WhoClient {

    private Vector users = new Vector();
    private ServerInterface server;

    public WhoClient(String[] args) {
        //first arguement is the port number
        //Get port number in string to be converted to int later
        String port = args[0];
        int repeats = Integer.parseInt(args[1]);
        long start = new Date().getTime();
        //Iterations
        for(int i = 1; i <= repeats; i++) {
            users.add("Loop: " + i);
            //look through each additional argument starting at 1
            for (int j = 2; j < args.length; j++) {
                //Try to connect to server
                try {
                    //loopup in form of “rmi://serverIp:serverPort/symbolic_name”
                    //“rmi://HOSTNAME:PORT/whoserver”
                    server = (ServerInterface) Naming.lookup("rmi://" + args[j] + ":" + port + "/whoserver");
                } catch (Exception e) {
                    //Print the stack, to be changed or removed for a smaller error
                    System.out.println(args[j] + ": Host not found.");
                    //If host not found, continue to the next one
                    continue;
                }

                Vector incoming;

                //Get incoming data from servers
                try {
                    incoming = server.get();
                } catch (RemoteException e) {
                    //Print out error
                    System.out.println(args[j] + ": Unable to retrieve data.");
                    //if data is not received, continue to next host
                    continue;
                }
                //add the host name to the list before users of that host
                users.add(args[j] + ":");
                //Add all users for the host
                for (int k = 0; k < incoming.size(); k++) {
                    users.add(incoming.elementAt(k));
                }
            }
        }

        //Print out the list of Hosts and users
        for (Object line : users) {
            //Cast each item as a String and print
            System.out.println((String) line);
        }

        long end = new Date().getTime();
        System.out.println("Run Time = "+ (end-start) + "milliseconds");
    }

    public static void main(String[] args) {
        //Minimum arguments is a port and a hostname, size of 2
        if(args.length >= 3) {
            int port = Integer.parseInt(args[0]);
            if(port <= 1024 || port > 65535) {
                System.out.println("Invalid port: range must be 1025-65535");
                System.exit(-1);
            }
            new WhoClient(args);
        } else {
            System.out.println("Minimum of three(3) arguments needed");
            System.out.println("Syntax: java WhoClient port repeats host1 host2 host3 ...");
            System.exit(-2);
        }
    }
}
