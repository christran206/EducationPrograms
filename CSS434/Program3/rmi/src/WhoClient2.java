/**
 * Created by Christopher on 5/18/2014.
 */
import java.io.PrintStream;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Vector;

class WhoClient2
{
    Vector<String> allusers;
    ServerInterface server;

    public WhoClient2(String[] args)
    {
        this.allusers = new Vector();
        String str = args[0];
        for (int i = 1; i < args.length; i++)
        {
            try
            {
                this.server = ((ServerInterface)Naming.lookup("rmi://" + args[i] + ":" + str + "/whoserver"));
            }
            catch (Exception e)
            {
                e.printStackTrace();
                continue;
            }
            Vector incoming;
            try
            {
                incoming = this.server.get();
            }
            catch (RemoteException e)
            {
                e.printStackTrace();
                continue;
            }
            this.allusers.add(new String(args[i] + ":"));
            for (int j = 0; j < incoming.size(); j++) {
                this.allusers.add((String)incoming.elementAt(j));
            }
        }
        for (int i = 0; i < this.allusers.size(); i++) {
            System.out.println((String)this.allusers.elementAt(i));
        }
    }

    public static void main(String[] args)
    {
        if (args.length < 2)
        {
            System.err.println("usage: java WhoeClient port# ip1 ip2 ip3..");
            System.exit(-1);
        }
        new WhoClient(args);
    }
}
