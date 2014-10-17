import java.io.*;
import java.net.UnknownHostException;
import java.rmi.*;
import java.net.*;
import java.rmi.server.UnicastRemoteObject;


public class FileClient
        extends UnicastRemoteObject
        implements ClientInterface {
    private BufferedReader input = null;
    private static final String ramDiskFile = "/tmp/mfukuda.txt";
    private ServerInterface server = null;
    private File file = null;

    public FileClient(String paramString1, String paramString2)
            throws RemoteException {
        try {
            this.server = ((ServerInterface) Naming.lookup("rmi://" + paramString1 + ":" + paramString2 + "/fileserver"));
        } catch (Exception localException) {
            localException.printStackTrace();
        }
        this.file = new FileClient.File(this);


        this.input = new BufferedReader(new InputStreamReader(System.in));
    }

    public void loop() {
        for (; ; ) {
            FileClient.WritebackThread localWritebackThread = new FileClient.WritebackThread(this);
            localWritebackThread.start();


            String str1 = null;
            String str2 = null;
            try {
                System.out.println("FileClient: Next file to open:");
                System.out.print("\tFile name: ");
                str1 = this.input.readLine();
                if ((str1.equals("quit")) || (str1.equals("exit"))) {
                    if (this.file.isStateWriteOwned()) {
                        this.file.upload();
                    }
                    System.exit(0);
                } else if (str1.equals("")) {
                    System.err.println("Do it again");
                    localWritebackThread.kill();
                    continue;
                }
                System.out.print("\tHow(r/w): ");
                str2 = this.input.readLine();
                if ((!str2.equals("r")) && (!str2.equals("w"))) {
                    System.err.println("Do it again");
                    localWritebackThread.kill();
                    continue;
                }
            } catch (IOException localIOException) {
                localIOException.printStackTrace();
            }
            localWritebackThread.kill();
            if (this.file.hit(str1, str2) != true) {
                if (this.file.isStateWriteOwned()) {
                    this.file.upload();
                }
                this.file.download(str1, str2);
            }
            this.file.launchEmacs(str2);
        }
    }

    public boolean invalidate() {
        return this.file.invalidate();
    }

    public boolean writeback() {
        return this.file.writeback();
    }

    public static void main(String[] paramArrayOfString) {
        if (paramArrayOfString.length != 2) {
            System.err.println("usage: java FileClient server_ip port#");
            System.exit(-1);
        }
        try {
            FileClient localFileClient = new FileClient(paramArrayOfString[0], paramArrayOfString[1]);

            Naming.rebind("rmi://localhost:" + paramArrayOfString[1] + "/fileclient", localFileClient);

            System.out.println("rmi://localhost: " + paramArrayOfString[0] + "/fileclient" + " invokded");


            localFileClient.loop();
        } catch (Exception localException) {
            localException.printStackTrace();
            System.exit(1);
        }
    }

    class WritebackThread
            extends Thread {
        private boolean active = false;

        public WritebackThread(FileClient paramFileClient) {
            this.active = true;
        }

        public void run() {
            while (isActive()) {
                if (FileClient.this.file.isStateBackToReadShared()) {
                    FileClient.this.file.upload();
                }
            }
        }

        synchronized void kill() {
            this.active = false;
            try {
                join();
            } catch (InterruptedException localInterruptedException) {
                localInterruptedException.printStackTrace();
            }
        }

        synchronized boolean isActive() {
            return this.active;
        }
    }


    class File {
        private static final int state_invalid = 0;
        private static final int state_readshared = 1;
        private static final int state_writeowned = 2;
        private static final int state_back2readshared = 3;
        private int state = 0;
        private boolean inEdit = false;
        private String name = "";
        private boolean ownership = false;
        private byte[] bytes = null;
        private String myIpName = null;

        public File(FileClient paramFileClient) {
            try {
                InetAddress localInetAddress = InetAddress.getLocalHost();
                this.myIpName = localInetAddress.getHostName();
            } catch (UnknownHostException localUnknownHostException) {
                localUnknownHostException.printStackTrace();
            }
        }

        public synchronized boolean isStateInvalid() {
            return this.state == state_invalid;
        }

        public synchronized boolean isStateReadShared() {
            return this.state == state_readshared;
        }

        public synchronized boolean isStateWriteOwned() {
            System.out.println("name = " + this.name + " state = " + this.state + " ownership = " + this.ownership);


            return this.state == state_writeowned;
        }

        public synchronized boolean isStateBackToReadShared() {
            return this.state == state_back2readshared;
        }

        public synchronized boolean invalidate() {
            if (this.state == state_readshared) {
                this.state = state_invalid;
                System.out.println("file( " + this.name + ") invalidated...state " + this.state);

                return true;
            }
            return false;
        }

        public synchronized boolean writeback() {
            if (this.state == state_writeowned) {
                this.state = state_back2readshared;
                return true;
            }
            return false;
        }

        public synchronized boolean hit(String paramString1, String paramString2) {
            if (!this.name.equals(paramString1)) {
                System.out.println("file: " + paramString1 + " does not exist.");
                return false;
            }
            if (this.state == 3) {
                System.out.println("file: " + paramString1 + " must be written back.");
                return false;
            }
            if ((paramString2.equals("r")) && (this.state != state_invalid)) {
                System.out.println("file: " + paramString1 + " exists for read.");
                return true;
            }
            if ((paramString2.equals("w")) && (this.state == state_writeowned)) {
                System.out.println("file: " + paramString1 + " is owned for write");
                return true;
            }
            System.out.println("file: " + paramString1 + " accessed with " + paramString2);
            return false;
        }

        public boolean download(String paramString1, String paramString2) {
            System.out.println("downloading: " + paramString1 + " with " + paramString2 + " mode");
            synchronized (this) {
                switch (this.state) {
                    case 0:
                        if (paramString2.equals("r")) {
                            this.state = 1;
                        } else if (paramString2.equals("w")) {
                            this.state = 2;
                        }
                        break;
                    case 1:
                        if (paramString2.equals("w")) {
                            this.state = 2;
                        }
                        break;
                }
            }
            this.name = paramString1;
            this.ownership = paramString2.equals("w");
            try {

                FileContents fc = FileClient.this.server.download(this.myIpName, this.name, paramString2);


                this.bytes = fc.get();
            } catch (RemoteException localRemoteException) {
                localRemoteException.printStackTrace();
                return false;
            }
            return true;
        }

        public boolean upload() {
            System.out.println("uploading: " + this.name + " start");
            synchronized (this) {
                switch (this.state) {
                    case 2:
                        this.state = 0;
                        break;
                    case 3:
                        this.state = 1;
                }
            }

            FileContents fc = new FileContents(this.bytes);

            try {
                FileClient.this.server.upload(this.myIpName, this.name,fc);
            } catch (RemoteException localRemoteException) {
                localRemoteException.printStackTrace();
                return false;
            }
            System.out.println("uploading: " + this.name + " completed");
            return true;
        }

        private boolean execUnixCommand(String paramString1, String paramString2, String paramString3) {
            String[] arrayOfString = paramString3.equals("") ? new String[2] : new String[3];

            arrayOfString[0] = paramString1;
            arrayOfString[1] = paramString2;
            if (!paramString3.equals("")) {
                arrayOfString[2] = paramString3;
            }
            try {
                Runtime localRuntime = Runtime.getRuntime();
                Process localProcess = localRuntime.exec(arrayOfString);
                int i = localProcess.waitFor();
            } catch (IOException localIOException) {
                localIOException.printStackTrace();
                return false;
            } catch (InterruptedException localInterruptedException) {
                localInterruptedException.printStackTrace();
                return false;
            }
            return true;
        }

        public boolean launchEmacs(String paramString) {
            if (!execUnixCommand("chmod", "600", "/tmp/mfukuda.txt")) {
                return false;
            }
            try {
                FileOutputStream localFileOutputStream = new FileOutputStream("/tmp/mfukuda.txt");
                localFileOutputStream.write(this.bytes);
                localFileOutputStream.flush();
                localFileOutputStream.close();
            } catch (FileNotFoundException localFileNotFoundException1) {
                localFileNotFoundException1.printStackTrace();
                return false;
            } catch (IOException localIOException1) {
                localIOException1.printStackTrace();
                return false;
            }
            if (!execUnixCommand("chmod", paramString.equals("r") ? "400" : "600", "/tmp/mfukuda.txt")) {
                return false;
            }
            boolean bool = execUnixCommand("emacs", "/tmp/mfukuda.txt", "");
            if ((bool == true) && (paramString.equals("w"))) {
                try {
                    FileInputStream localFileInputStream = new FileInputStream("/tmp/mfukuda.txt");
                    this.bytes = new byte[localFileInputStream.available()];
                    localFileInputStream.read(this.bytes);
                    localFileInputStream.close();
                } catch (FileNotFoundException localFileNotFoundException2) {
                    localFileNotFoundException2.printStackTrace();
                    return false;
                } catch (IOException localIOException2) {
                    localIOException2.printStackTrace();
                    return false;
                }
            }
            return true;
        }
    }

}
