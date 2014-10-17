import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.io.*;
import java.util.*;

/**
 * Created by Christopher on 6/6/2014.
 */
public class DFSServer extends UnicastRemoteObject implements ServerInterface{
    private String port = null;
    private Vector<File> cache = null;

    public DFSServer(String args) throws RemoteException {
        port = args;
        cache = new Vector<File>();
    }

    public static void main(String[] args) {
        if(args.length != 1) {
            System.out.println("Usage: java DFSServer port#");
            System.exit(-1);
        }

        try {
            DFSServer server = new DFSServer(args[0]);
            Naming.rebind("rmi://localhost:" + args[0] + "/dfsserver", server);

            System.out.println("rmi://localhost: " + args[0] + "/dfsserver invoked");
        } catch(Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    //send file to client file to client
    public FileContents download(String client, String filename, String mode) throws RemoteException {
        File file = null;
        synchronized (cache) {
            //Check if file already exists in the cache
            for(int i = 0; i < cache.size(); i++) {
                file = cache.elementAt(i);
                //If file has been found, break
                if(file.isFile(filename)) {
                    break;
                }
                file = null;
            }

            //if file is not found in cache, get a new file.
            if(file == null) {
                file = new File(this, filename, port);
                cache.add(file);
            }
        }
        return file.download(client,mode);
    }

    //get file from clients
    public boolean upload(String client, String filename, FileContents contents) throws RemoteException {
        File file = null;
        synchronized (cache) {
            //Check if file exists to be written back to
            for(int i = 0; i < cache.size(); i++) {
                file = cache.elementAt(i);
                if(file.isFile(filename)) {
                    break;
                }
                file = null;
            }
        }

        //If cache has file, attempt to update the contents
        if(file != null) {
            System.out.println(client + " upload: file " + filename);
            return file.upload(client, contents);
        }

        return false;
    }

    class File {
        //Condition by value
        private static final int NONE = 0;
        private static final int READ = 1;
        private static final int WRITE = 2;
        private static final int TODISK = 3;
        //Class variables
        private int state; //Stores current state
        private String fileName; //Stores the name of the file
        private byte[] fileData; //Stores the file data
        private Vector<String> readers = null; //Container for all readers of file
        private String writeUser = null; //user that is writing to file
        private String port = null; //port
        private Thread toWrite = null; //Synchronized object for readers to wait on for writing

        //Constructor
        public File(DFSServer dfs, String name, String port) {
            state = NONE; //State begins with none
            this.fileName = name; //Store file name
            readers = new Vector<String>();
            writeUser = null;
            this.port   = port;
            toWrite = new Thread();
            fileData = readFromFile();
        }


        //Read a file from the directory
        private byte[] readFromFile() {
            byte[] fileData = null;
            //REad file into byte array and return null data at any exception
            try {
                FileInputStream fin = new FileInputStream(fileName);
                fileData = new byte[fin.available()];
                fin.read(fileData);
                fin.close();
            } catch(FileNotFoundException e) {
                e.printStackTrace();
                return null;
            } catch(IOException e) {
                e.printStackTrace();
                return null;
            }

            System.out.println("File read from " + fileName + ": " + fileData.length + " bytes");

            return fileData;
        }

        //Write to file in directory
        private boolean writeToFile() {
            try {
                FileOutputStream fos = new FileOutputStream(fileName);
                fos.write(fileData);
                fos.flush();
                fos.close();
            } catch(FileNotFoundException e) {
                e.printStackTrace();
                return false;
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }

            System.out.println("File written to " + fileName + ": " + fileData.length + " fileData");

            return true;
        }

        //download will upload a file for client to download
        public synchronized FileContents download(String reader, String mode) {
            //If no file name, no need to do anything
            if(fileName.equals("")) {
                return null;
            }

            //Check if file is waiting to be writen back and halt download until finished
            while(state == TODISK) {
                synchronized (toWrite) {
                    try{
                        System.out.println(reader + " now wait on file writing");
                        toWrite.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

            //
            int currentState = state;
            boolean success = true;

            switch(state) {
                case NONE:
                    //If file isn't in a state, change to read or write
                    if(mode.equals("r")) {
                        state = READ;
                        readers.add(reader);
                    } else if(mode.equals("w")) {
                        state = WRITE;
                        if(writeUser == null) {
                            writeUser = reader;
                        } else {
                            success = false;
                        }
                    } else {
                        success = false;
                    }
                    break;
                case READ:
                    //file is in read state and needs to check if adding to readers or writing
                    deleteReader(reader);
                    if(mode.equals("r")) {
                        readers.add(reader);
                    } else if(mode.equals("w")) {
                        state = WRITE;
                        if(writeUser == null) {
                            writeUser = reader;
                        } else {
                            success = false;
                        }
                    } else {
                        success = false;
                    }
                    break;
                case WRITE:
                    //File is in write mode for another user
                    deleteReader(reader);
                    if(mode.equals("r")) {
                        readers.add(reader);
                    } else if (mode.equals("w")) {
                        state = TODISK;

                        //Connect to client that has the current write and force them to write back to server
                        ClientInterface ci = null;
                        try {
                            ci = (ClientInterface)Naming.lookup("rmi://" + writeUser + ":" + port + "/dfsclient");
                        } catch (Exception e) {
                            e.printStackTrace();
                            success = false;
                        }

                        //Tell current writer to write back to server
                        if (ci != null) {
                            try {
                                ci.writeback();
                            } catch (RemoteException e) {
                                e.printStackTrace();
                                success = false;
                            }

                            System.out.print("Download( " + fileName + " ): " + writeUser + "'s copy was invalidated");
                        }


                        if(success) {
                            try {
                                System.out.println("Download " + fileName + " ): " + reader + " waits for writeback");
                                wait();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                                success = false;;
                            }

                            writeUser = reader;
                        }
                    } else {
                        success = false;;
                    }
                    break;
            }

            printReport(reader, "download", mode, currentState, state);

            FileContents fc = new FileContents(fileData);
            if(success) {
                if (currentState == TODISK) {
                    synchronized (toWrite) {
                        toWrite.notifyAll();
                        System.out.println(reader + " making up all threads waiting on write");
                    }
                }
            } else {
                return null;
            }
            return fc;
        }

        //Get file from client
        public synchronized boolean upload(String reader, FileContents source) {
            boolean success = true;

            //Can't upload if file is blank or in none or read state
            if(fileName.equals("") || state == NONE || state == READ) {
                success = false;
            }

            //Invalidate all readers copies
            for( int j = 0; success && j < readers.size(); j++) {
                String currentReader = readers.elementAt(j);

                ClientInterface ci = null;

                try {
                    ci = (ClientInterface) Naming.lookup("rmi://" + currentReader + ":" + port + "/dfsclient");
                } catch (Exception e) {
                    e.printStackTrace();
                    success = false;
                }

                if(ci == null) {
                    try {
                        ci.invalidate();
                    } catch(RemoteException e) {
                        e.printStackTrace();
                    }

                    System.out.println("Update( " + fileName + " ): " + currentReader + "'s copy was invalidated");
                }
            }
            //Readers are no longer valid so remove them all
            readers.removeAllElements();

            //Keep old state for reporting
            int currentState = state;

            if(success) {
                //Get the data
                fileData = source.get();
                System.out.println("Bytes = " + fileData);

                switch(state) {
                    case WRITE:
                        state = NONE;
                        writeUser = null;
                        success = writeToFile();
                        break;
                    case TODISK:
                        state = WRITE;
                        writeUser = reader;
                        notify();
                }
            }

            printReport(reader, "upload", "w", currentState, state);

            return success;
        }

        //Remove reader from active list of file readers
        private boolean deleteReader(String reader) {
            for(int i = 0; i < readers.size(); i++) {
                if(readers.elementAt(i).equals(reader)) {
                    readers.remove(i);
                    return true;
                }
            }
            return false;
        }

        //Show the users that are active on the file
        private void showReaders() {
            System.out.println("# Readers = " + readers.size());
            for(int i = 0; i < readers.size(); i++) {
                System.out.println("\tReader = " + readers.elementAt(i));
            }
        }

        public synchronized boolean isNotShared() {
            return state == NONE;
        }

        public synchronized boolean isReadShared() {
            return state == READ;
        }

        public synchronized  boolean isWriteShared() {
            return state == WRITE;
        }

        public synchronized boolean isToWriteShared() {
            return state == TODISK;
        }

        //Check if the current file exists
        public synchronized boolean isFile(String target) {
            return fileName.equals(target);
        }


        //Print out transition reports
        private void printReport(String clientName, String task, String stringMode, int oldState, int newState) {
            String fromState = stateToString(oldState);
            String toState = stateToString(newState);

            System.out.println("File(" + fileName + ") requested by " + clientName + ":" + task + "(" + stringMode + "): state( " + fromState + " --> " + toState + " )");

            showReaders();
            System.out.println("Owner = " + writeUser);
        }

        //Get string of state for transition report
        private String stateToString(int inState) {
            switch(inState) {
                case NONE:
                    return "notshared";
                case READ:
                    return "readshared";
                case WRITE:
                    return "writeshared";
                case TODISK:
                    return "back2writeshared";
                default:
                    return "notrecognized";
            }
        }
    }

}

