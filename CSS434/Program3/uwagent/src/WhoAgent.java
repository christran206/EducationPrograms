/**
 * CSS434
 * Created by Christopher on 5/18/2014.
 */

import UWAgent.UWAgent;
import java.io.*;
import java.net.*;
import java.util.*;

public class WhoAgent extends UWAgent implements Serializable {

    Vector users; //Container for all inputs
    String[] servers; //List of servers
    int hopPosition; //Hop position in server array
    int repetitions; //Repetition cycles
    int cycles; //Number of cycles completed for repetition
    String origin; //Originating Host
    long start; //Start Date for performance evaluation

    //Left to implement
    //Arguements is 2 or larger for repetitions and hosts
    //Repetitions is 0 or greater
    public WhoAgent(String[] args) {
        start = new Date().getTime(); //Get the start time to evaluate time performance later
        users = new Vector();
        //Set hop position to 0
        hopPosition = 0;
        cycles = 0;
        //Get number of repetitions from arguement 0
        repetitions = Integer.parseInt(args[0]);
        //System.out.println("Repeating: " + repetitions + "times");
        if(args != null) {
            //ignore arg 0 and copy the rest into servers
            servers = Arrays.copyOfRange(args, 1, args.length);
        } else {
            System.out.println("No Servers");
        }
    }

    //get host name for return Object and hop to first server
    public void init() {
        //Must have at least one server
        if(servers.length > 0) {
            try {
                //get the local host name and store it before any hopping
                InetAddress iNet = InetAddress.getLocalHost();
                origin = iNet.getHostAddress();
                //System.out.println("init Stage");
                hop(servers[hopPosition],"who",null);
            } catch (UnknownHostException e) {
                e.printStackTrace();
            }
        }
    }

    public void who() {
        //if first hop, add the Loop indication
        //System.out.println("Running who on "+ servers[0]);
        if(hopPosition == 0 && repetitions != 1) {
            users.add("Loop: "+(cycles+1));
        }
        //Create vector to store the results of command execution
        Vector whoResult = new Vector();
        //Get the machine runtime
        Runtime run = Runtime.getRuntime();
        try {
            //System.out.println("Executing Who on Local Host");
            //Exeute Who and store output into Vector
            Process proc = run.exec("who");
            InputStream iStream = proc.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(iStream));
            String line = br.readLine();
            //Check each line and add to whoResult
            while(line != null) {
                System.out.println(line);
                whoResult.add(line);
                line = br.readLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        //If there is output, add to the class users Vector
        if(!whoResult.isEmpty()) {
            users.add(servers[hopPosition] + ":");
            for(int i = 0; i < whoResult.size(); i++) {
                users.add(whoResult.elementAt(i));
            }
        }
        //Increase Hop Number to hop to next server
        hopPosition++;
        //If there are more servers to run who on
        if(hopPosition < servers.length) {
            hop(servers[hopPosition],"who",null);
        } else {
            //System.out.println("End of Cycle " + (cycles+1));
            //Since no more hops left, increase cycle count
            cycles++;
            //If more repetitions are needed, reset hopPosition back to 0
            //Hop back to first host
            if(cycles < repetitions) {
                hopPosition = 0;
                hop(servers[0],"who",null);
            } else {
                //System.out.println("End of All Cycles: Print to Host");
                //Hop back to host to send the updated Vector and print
                hop(origin, "printWho", null);
            }
        }
    }

    //Function to print output for when all work is done
    public void printWho() {
        //System.out.println("Host is printing");
        for(int i = 0; i < users.size(); i++) {
            System.out.println((String)users.elementAt(i));
        }
        long end = new Date().getTime();
        System.out.println("Run Time = "+ (end-start) + " milliseconds");
    }
}
