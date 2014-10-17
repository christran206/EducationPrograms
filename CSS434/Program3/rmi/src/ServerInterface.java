import java.rmi.*;
import java.util.*;

public interface ServerInterface extends Remote {
    public Vector get( ) throws RemoteException;
}
