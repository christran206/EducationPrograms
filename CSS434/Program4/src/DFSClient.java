import java.io.*;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 * Created by Christopher on 6/8/2014.
 */
public class DFSClient extends UnicastRemoteObject implements ClientInterface {
    private BufferedReader input = null;
    public static final String tempFile = "/tmp/ctran206.txt";
    protected ServerInterface server = null;
    protected File file = null;

    public DFSClient(String serverName, String port) throws RemoteException {
        try {
            //Connect to Server
            server = (ServerInterface)Naming.lookup("rmi://" + serverName + ":" + port + "/dfsserver");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }

        //Get new file class and connect to server
        file = new File(this);

        //For console input
        input = new BufferedReader(new InputStreamReader(System.in));
    }

    public static void main(String[] args) {
        //Must have two arguements for server and port
        if(args.length != 2) {
            System.out.println("Usage: java DFSClient serverIP Port#");
            System.exit(-1);
        }

        try {
            //make object to run as DFS Client
            DFSClient dfsClient = new DFSClient(args[0],args[1]);

            //Rebind for RMI
            Naming.rebind("rmi://localhost:" + args[1] + "/dfsclient", dfsClient);

            //Output for console verification
            System.out.println("rmi://localhost:" + args[1] + "/dfsclient invoked");

            dfsClient.run();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    //Infinite loop function to access files from DFSServer
    private void run() {
        //run indefinitely
        while(true) {
            //Inspired by Fukuda example program, aditional class to
            WriteBackThread wbt = new WriteBackThread(this);
            wbt.start();

            String fileName = null;
            String fileMode = null;

            //Get user input to download file
            System.out.print("DFSClient: Next file to open\n\tFileName or quit to exit: ");
            try {
                fileName = input.readLine();
            } catch (IOException e) {
                System.err.println("Error input for file name");
                e.printStackTrace();
            }

            //if input is blank, try again
            if(fileName.equals("")) {
                wbt.kill();
                continue;
            }

            //IF the user wants to quit, write file back if needed
            if(fileName.equals("quit")) {
                if(file.isWrite()) {
                    file.upload();
                }
                wbt.kill();
                System.exit(0);
            }

            //Get file mode
            System.out.print("\tHow(r\\w): ");
            try {
                fileMode = input.readLine();
            } catch (IOException e) {
                System.err.println("Error input for file mode");
                e.printStackTrace();
            }

            //Check if anything but r and w
            if(!fileMode.equals("r") && !fileMode.equals("w")) {
                System.err.println("File mode not recognized");
                wbt.kill();
                continue;
            }
            wbt.kill();

            boolean success = false;
            //If the file is not already stored, download the file
            if(!file.hasFile(fileName,fileMode)) {
                //Write back any existing file
                if(file.isWrite()) {
                    file.upload();
                }
                success = file.download(fileName,fileMode);
            }

            //If file was downloaded, open in editor
            if(!file.isNullFile()) {
                file.runEditor(fileMode);
            } else {
                System.err.println("File unable to download or was null");
                continue;
            }
        }
    }

    public boolean invalidate() {
        return file.invalidate();
    }

    public boolean writeback() {
        return file.writeback();
    }

    class File {
        //State variables
        private static final int INVALID = 0;
        private static final int READ = 1;
        private static final int WRITE = 2;
        private static final int WRITEBACK = 3;

        private int state = INVALID; //start at invalid
        private String fileName = "";
        private boolean isOwned = false;
        private byte[] fileData = null;
        private String localName = null;

        public File(DFSClient client) {
            try {
                InetAddress iNet = InetAddress.getLocalHost();
                localName = iNet.getHostName();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            }
        }

        //State Check Function
        public synchronized boolean isInvalid() {
            return state == INVALID;
        }

        //State Check Function
        public synchronized boolean isReadShared() {
            return state == READ;
        }

        //State Check Function
        public synchronized  boolean isWrite() {
            System.out.println("Name: " + fileName + "\tState: " + state + "\tOwnership: " + isOwned);
            return state == WRITE;
        }

        //State Check Function
        public synchronized  boolean isToWriteBack() {
            return state == WRITEBACK;
        }

        //Change state to Invalid
        //Invalidate read only copy
        public synchronized boolean invalidate() {
            if(state == READ) {
                state = INVALID;
                return true;
            }
            return false;
        }

        //Writee back data
        public synchronized boolean writeback() {
            if(state == WRITE) {
                state = WRITEBACK;
                return true;
            }
            return false;
        }

        //Check if local cache has file
        public synchronized boolean hasFile(String file, String mode) {
            //Check if client has file
            if(!fileName.equals(file)) {
                System.out.println("File: " + file + " does not exist.");
                return false;
            }
            //Check if file needs to be written to server so client doesn't have proper file
            if(state == WRITEBACK) {
                System.out.println("File: " + file + " must be written back.");
                return false;
            }

            //Client has file for reading
            if(state != INVALID && mode.equals("r")) {
                System.out.println("File: " + file + " exist for read.");
                return true;
            }

            //Client has file for writing
            if(state == WRITE && mode.equals("w")) {
                System.out.println("File: " + file + " is owned for write");
                return true;
            }
            System.out.println("File: " + file + " accessed with " + mode);
            return false;
        }

        //Download file to local cache
        public boolean download(String file, String mode) {
            System.out.println("Downloading: " + file + " with " + mode + " mode");
            synchronized (this) {
                //If state is invalid, set the mode to read or write depending on the input
                if(mode.equals("r")) {
                    state = READ;
                } else if(mode.equals("w")) {
                    state = WRITE;
                } else {
                    //r or w not detected, return false
                    return false;
                }

            }

            fileName = file;
            isOwned = (state == WRITE);

            try {
                FileContents fc = DFSClient.this.server.download(localName,fileName,mode);
                fileData = fc.get();
            } catch( RemoteException e) {
                e.printStackTrace();
                return false;
            }
            return true;
        }

        //Upload file to server
        public boolean upload() {
            System.out.println("Uploading: " + fileName + " start");
            synchronized (this) {
                if(state == WRITE) {
                    state = INVALID;
                } else if(state == WRITEBACK) {
                    state = READ;
                } else {
                    //State is either invalid or read, return false since we shouldn't upload
                    return false;
                }

            }

            FileContents fc = new FileContents(fileData);
            //Upload file data
            try {
                DFSClient.this.server.upload(localName,fileName,fc);
            } catch (RemoteException e) {
                e.printStackTrace();
                return false;
            }
            System.out.println("Upload: " + fileName + " completed");
            return true;
        }

        //Run the Text Editor: emacs
        public Boolean runEditor(String fileMode) {
            //Get runtime to execute commands
            Runtime runtime = Runtime.getRuntime();
            //Generate String array to execute command with exec
            //First command is changing temp file to OWNER:READandWRITE
            String[] command = {"chmod","600",DFSClient.this.tempFile};
            //Try to run command
            try {
                Process process = runtime.exec(command);
                process.waitFor();
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            } catch (InterruptedException e) {
                e.printStackTrace();
                return false;
            }

            //Output file data from File to temp file
            try {
                FileOutputStream fos = new FileOutputStream(DFSClient.this.tempFile);
                fos.write(fileData);
                fos.flush();
                fos.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                return false;
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }

            //If mode is read, change mode to read only
            if(fileMode.equals("r")) {
                //Change index 1 from 600 to 400 for OWNER:READ
                command[1] = "400";
                try {
                    Process process = runtime.exec(command);
                    process.waitFor();
                } catch (IOException e) {
                    e.printStackTrace();
                    return false;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    return false;
                }
            }

            //Open emacs
            command = new String[]{"emacs", DFSClient.this.tempFile};
            try {
                Process process = runtime.exec(command);
                process.waitFor();
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            } catch (InterruptedException e) {
                e.printStackTrace();
                return false;
            }

            //If write mode, write data back to temp file
            if(fileMode.equals("w")) {
                try {
                    FileInputStream fis = new FileInputStream(DFSClient.this.tempFile);
                    fileData = new byte[fis.available()];
                    fis.read(fileData);
                    fis.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                    return false;
                } catch (IOException e) {
                    e.printStackTrace();
                    return false;
                }
            }

            return true;
        }

        //If data downloaded is null, file is probably incorrect
        public boolean isNullFile() {
            return fileData == null;
        }
    }

    class WriteBackThread extends Thread {
        private boolean isRunning = false;

        public WriteBackThread(DFSClient client) {
            isRunning = true;
        }

        //Writeback when state is toRead
        public void run() {
            while(isRunning) {
                if(DFSClient.this.file.isToWriteBack()) {
                    DFSClient.this.file.upload();
                }
            }
        }

        //Kill thread by joining
        synchronized void kill() {
            isRunning = false;

            try {
                join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}

