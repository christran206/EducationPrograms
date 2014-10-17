import UWAgent.UWAgent;

import java.io.Serializable;
import java.util.Vector;


/**
 * Created by v-ctran on 5/19/2014.
 */
public class ArgTest extends UWAgent implements Serializable {
    Vector v = new Vector();

    public ArgTest() {}

    public ArgTest(String[] args) {

        if(args != null) {
            System.out.println(args.length);
            for(int i = 0; i < args.length; i++) {
                System.out.println("Argument " + i + " : " + args[i]);
            }

        } else {
            System.out.println("");
        }
    }


    public void init() {
        System.out.println("Testing Arguements");
    }
}
