import java.io.PrintStream;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Vector;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Vector;

public class FileServer
        extends UnicastRemoteObject
        implements ServerInterface {
    private String port = null;
    private Vector<FileServer.File> cache = null;

    public FileServer(String paramString)
            throws RemoteException {
        this.port = paramString;
        this.cache = new Vector();
    }

    public static void main(String[] paramArrayOfString) {
        if (paramArrayOfString.length != 1) {
            System.err.println("usage: java FileServer port#");
            System.exit(-1);
        }
        try {
            FileServer localFileServer = new FileServer(paramArrayOfString[0]);
            Naming.rebind("rmi://localhost:" + paramArrayOfString[0] + "/fileserver", localFileServer);

            System.out.println("rmi://localhost: " + paramArrayOfString[0] + "/fileserver" + " invokded");
        } catch (Exception localException) {
            localException.printStackTrace();
            System.exit(1);
        }
    }

    public FileContents download(String paramString1, String paramString2, String paramString3) {
        FileServer.File localFile = null;
        synchronized (this.cache) {
            for (int i = 0; i < this.cache.size(); i++) {
                localFile = (FileServer.File) this.cache.elementAt(i);
                if (localFile.hit(paramString2)) {
                    break;
                }
                localFile = null;
            }
            if (localFile == null) {
                localFile = new FileServer.File(this, paramString2, this.port);
                this.cache.add(localFile);
            }
        }
        return localFile.download(paramString1, paramString3);
    }

    public boolean upload(String paramString1, String paramString2, FileContents paramFileContents) {
        FileServer.File localFile = null;
        synchronized (this.cache) {
            for (int i = 0; i < this.cache.size(); i++) {
                localFile = (FileServer.File) this.cache.elementAt(i);
                if (localFile.hit(paramString2)) {
                    break;
                }
                localFile = null;
            }
        }
        System.out.println(paramString1 + " upload: file = " + localFile);
        return localFile == null ? false : localFile.upload(paramString1, paramFileContents);
    }


    class File {
        private static final int state_notshared = 0;
        private static final int state_readshared = 1;
        private static final int state_writeshared = 2;
        private static final int state_back2writeshared = 3;
        private int state;
        private String name;
        private byte[] bytes = null;
        private Vector<String> readers = null;
        private String owner = null;
        private String port = null;
        private Object inStateBack2WriteShared = null;

        private boolean removeReader(String paramString) {
            for (int i = 0; i < this.readers.size(); i++) {
                String str = (String) this.readers.elementAt(i);
                if (paramString.equals(str)) {
                    this.readers.remove(i);
                    return true;
                }
            }
            return false;
        }

        private void listReaders() {
            System.out.println("# readers = " + this.readers.size());
            for (int i = 0; i < this.readers.size(); i++) {
                String str = (String) this.readers.elementAt(i);
                System.out.println("\treader = " + str);
            }
        }

        private void printTransition(String paramString1, String paramString2, String paramString3, int paramInt1, int paramInt2, int paramInt3) {
            System.out.println("file(" + this.name + ") requested by " + paramString1 + ":" + paramString2 + "(" + paramString3 + "): state( " + (paramInt1 == 2 ? "writeshared" : paramInt1 == 1 ? "readshared" : paramInt1 == 0 ? "notshared" : "back2writeshared") + " --> " + (paramInt2 == 2 ? "writeshared" : paramInt2 == 1 ? "readshared" : paramInt2 == 0 ? "notshared" : "back2writeshared") + " ) " + " error_code = " + paramInt3);


            listReaders();
            System.out.println("owner = " + this.owner);
        }

        public File(FileServer paramFileServer, String paramString1, String paramString2) {
            this.state = 0;
            this.name = paramString1;
            this.readers = new Vector();
            this.owner = null;
            this.port = paramString2;
            this.inStateBack2WriteShared = new Object();


            this.bytes = fileRead();
        }

        private byte[] fileRead() {
            byte[] arrayOfByte = null;
            try {
                FileInputStream localFileInputStream = new FileInputStream(this.name);
                arrayOfByte = new byte[localFileInputStream.available()];
                localFileInputStream.read(arrayOfByte);
                localFileInputStream.close();
            } catch (FileNotFoundException localFileNotFoundException) {
                localFileNotFoundException.printStackTrace();
                return null;
            } catch (IOException localIOException) {
                localIOException.printStackTrace();
                return null;
            }
            System.out.println("file read from " + this.name + ": " + arrayOfByte.length + " bytes");

            return arrayOfByte;
        }

        private boolean fileWrite() {
            try {
                FileOutputStream localFileOutputStream = new FileOutputStream(this.name);
                localFileOutputStream.write(this.bytes);
                localFileOutputStream.flush();
                localFileOutputStream.close();
            } catch (FileNotFoundException localFileNotFoundException) {
                localFileNotFoundException.printStackTrace();
                return false;
            } catch (IOException localIOException) {
                localIOException.printStackTrace();
                return false;
            }
            System.out.println("file written to " + this.name + ": " + this.bytes.length + " bytes");

            return true;
        }

        public synchronized FileContents download(String paramString1, String paramString2) {
            if (this.name.equals("")) {
                return null;
            }
            while (this.state == 3) {
                synchronized (this.inStateBack2WriteShared) {
                    try {
                        System.out.println(paramString1 + "now wait on " + "inStateBack2WriteShared");

                        this.inStateBack2WriteShared.wait();
                    } catch (InterruptedException localInterruptedException1) {
                        localInterruptedException1.printStackTrace();
                    }
                }
            }
            int i = this.state;
            int j = 0;
            switch (this.state) {
                case 0:
                    if (paramString2.equals("r")) {
                        this.state = 1;
                        this.readers.add(paramString1);
                    } else if (paramString2.equals("w")) {
                        this.state = 2;
                        if (this.owner != null) {
                            j = 1;
                        } else {
                            this.owner = paramString1;
                        }
                    } else {
                        j = 2;
                    }
                    break;
                case 1:
                    removeReader(paramString1);
                    if (paramString2.equals("r")) {
                        this.readers.add(paramString1);
                    } else if (paramString2.equals("w")) {
                        this.state = 2;
                        if (this.owner != null) {
                            j = 3;
                        } else {
                            this.owner = paramString1;
                        }
                    } else {
                        j = 4;
                    }
                    break;
                case 2:
                    removeReader(paramString1);
                    if (paramString2.equals("r")) {
                        this.readers.add(paramString1);
                    } else if (paramString2.equals("w")) {
                        this.state = 3;


                        ClientInterface ci = null;
                        try {
                            ci = (ClientInterface) Naming.lookup("rmi://" + this.owner + ":" + this.port + "/fileclient");
                        } catch (Exception localException) {
                            localException.printStackTrace();
                            j = 5;
                        }
                        if (ci != null) {
                            try {
                                (ci).writeback();
                            } catch (RemoteException localRemoteException) {
                                localRemoteException.printStackTrace();
                                j = 6;
                            }
                            System.out.println("download( " + this.name + " ): " + this.owner + "'s copy was invalidated");
                        }
                        if (j == 0) {
                            try {
                                System.out.println("download " + this.name + " ): " + paramString1 + " waits for writeback");


                                wait();
                            } catch (InterruptedException localInterruptedException2) {
                                localInterruptedException2.printStackTrace();
                                j = 7;
                            }
                            this.owner = paramString1;
                        }
                    } else {
                        j = 8;
                    }
                    break;
            }
            printTransition(paramString1, "download", paramString2, i, this.state, j);
            if (j > 0) {
                return null;
            }
            FileContents fc = new FileContents(this.bytes);
            if (i == 3) {
                synchronized (this.inStateBack2WriteShared) {
                    this.inStateBack2WriteShared.notifyAll();
                    System.out.println(paramString1 + " woke up all waiting" + " on inStateBack2WriteShared");
                }
            }
            return fc;
        }

        public synchronized boolean upload(String paramString, FileContents paramFileContents) {
            int i = this.name.equals("") ? 1 : 0;
            i = (this.state == 0) || (this.state == 1) ? 2 : 0;
            for (int j = 0; (i == 0) && (j < this.readers.size()); j++) {
                String str = (String) this.readers.elementAt(j);


                ClientInterface localClientInterface = null;
                try {
                    localClientInterface = (ClientInterface) Naming.lookup("rmi://" + str + ":" + this.port + "/fileclient");
                } catch (Exception localException) {
                    localException.printStackTrace();
                    i = 3;
                }
                if (localClientInterface != null) {
                    try {
                        localClientInterface.invalidate();
                    } catch (RemoteException localRemoteException) {
                        localRemoteException.printStackTrace();
                    }
                    System.out.println("update( " + this.name + " ): " + str + "'s copy was invalidated");
                }
            }
            this.readers.removeAllElements();

            int j = this.state;
            if (i == 0) {
                this.bytes = paramFileContents.get();
                System.out.println("bytes = " + new String(this.bytes));
                switch (this.state) {
                    case 2:
                        this.state = 0;
                        this.owner = null;
                        i = !fileWrite() ? 4 : 0;
                        break;
                    case 3:
                        this.state = 2;
                        this.owner = paramString;
                        notify();
                }
            }
            printTransition(paramString, "upload", "w", j, this.state, i);

            return i == 0;
        }

        public synchronized boolean isStateNotShared() {
            return this.state == 0;
        }

        public synchronized boolean isStateReadShared() {
            return this.state == 1;
        }

        public synchronized boolean isStateWriteShared() {
            return this.state == 2;
        }

        public synchronized boolean isStatebackToWriteShared() {
            return this.state == 3;
        }

        public synchronized boolean hit(String paramString) {
            return this.name.equals(paramString);
        }
    }

}
