import java.io.*;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;

public class WhoServer extends UnicastRemoteObject 
    implements ServerInterface {
    
    public WhoServer( ) throws RemoteException {
    }

    public static void main( String args[] ) {
	if ( args.length != 1 ) {
	    System.err.println( "usage: java WhoServer port#" );
	    System.exit( -1 );
	}
	try {
	    WhoServer who = new WhoServer( );
	    Naming.rebind( "rmi://127.0.0.1:" + args[0] + "/whoserver", who );
	} catch ( Exception e ) {
	    e.printStackTrace( );
	    System.exit( 1 );
	}
    }

    public Vector get( ) {
	Vector<String> output = new Vector<String>( );
	String line;
	try {
	    Runtime runtime = Runtime.getRuntime( );
	    Process process = runtime.exec( "who" );
	    InputStream input = process.getInputStream();
	    BufferedReader bufferedInput
		= new BufferedReader( new InputStreamReader( input ) );
	    while ( ( line = bufferedInput.readLine( ) ) != null ) {
		System.out.println( line );
		output.addElement( line );
	    }
	} catch ( IOException e ) {
	    e.printStackTrace( );
	    return output;
	}
	return output;
    }
}
