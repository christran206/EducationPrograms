import java.io.*;
import UWAgent.*;

public class TestAgent extends UWAgent implements Serializable {
    private String destination = null;
    public TestAgent( String[] args ) {

    }
    public TestAgent( ) { 

    }

    public void init( ) {
	hop( "uw1-320-20", "func1", null );
    }

    public void func1( ) {
	System.out.println( "hop" );
	hop( "uw1-320-21", "func2", null );
    }

    public void func2( ) {
	System.out.println( "step" );
	hop( "uw1-320-22", "func3", null );
    }

    public void func3( ) {
	System.out.println( "jump" );
    }
}
