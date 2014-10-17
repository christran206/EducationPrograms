import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public class KernelDecom {
    public static final int INTERRUPT_SOFTWARE = 1;
    public static final int INTERRUPT_DISK = 2;
    public static final int INTERRUPT_IO = 3;
    public static final int BOOT = 0;
    public static final int EXEC = 1;
    public static final int WAIT = 2;
    public static final int EXIT = 3;
    public static final int SLEEP = 4;
    public static final int RAWREAD = 5;
    public static final int RAWWRITE = 6;
    public static final int SYNC = 7;
    public static final int READ = 8;
    public static final int WRITE = 9;
    public static final int CREAD = 10;
    public static final int CWRITE = 11;
    public static final int CSYNC = 12;
    public static final int CFLUSH = 13;
    public static final int OPEN = 14;
    public static final int CLOSE = 15;
    public static final int SIZE = 16;
    public static final int SEEK = 17;
    public static final int FORMAT = 18;
    public static final int DELETE = 19;
    public static final int STDIN = 0;
    public static final int STDOUT = 1;
    public static final int STDERR = 2;
    public static final int OK = 0;
    public static final int ERROR = -1;
    private static Scheduler scheduler;
    private static Disk disk;
    private static Cache cache;
    private static SyncQueue waitQueue;
    private static SyncQueue ioQueue;

    private static final int COND_DISK_REQ = 1;
    private static final int COND_DISK_FIN = 2;
    private static BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

    public KernelDecom() {
    }

    public static int interrupt(int irq, int cmd, int param, Object args) {
        TCB myTcb;
        switch (irq) {
            case INTERRUPT_SOFTWARE:

                int pid;
                Object localObject2;
                Object localObject1;
                switch (cmd) {
                    case BOOT:
                        scheduler = new Scheduler();
                        scheduler.start();


                        disk = new Disk(1000);
                        disk.start();


                        cache = new Cache(disk.blockSize, 10);


                        ioQueue = new SyncQueue();
                        waitQueue = new SyncQueue(scheduler.getMaxThreads());



                        return OK;
                    case EXEC:
                        return sysExec((String[]) args);
                    case WAIT:
                        if ((myTcb = scheduler.getMyTcb()) != null) {
                            pid = myTcb.getTid();
                            return waitQueue.enqueueAndSleep(pid);
                        }
                        return ERROR;
                    case EXIT:
                        if ((myTcb = scheduler.getMyTcb()) != null) {
                            pid = myTcb.getPid();
                            int j = myTcb.getTid();
                            if (pid != -1) {
                                waitQueue.dequeueAndWakeup(pid, j);

                                scheduler.deleteThread();
                                return OK;
                            }
                        }
                        return ERROR;
                    case SLEEP:
                        scheduler.sleepThread(param);
                        return OK;
                    case RAWREAD:
                        while (!disk.read(param, (byte[]) args)) {
                            ioQueue.enqueueAndSleep(COND_DISK_FIN);
                        }
                        while (!disk.testAndResetReady()) {
                            ioQueue.enqueueAndSleep(COND_DISK_REQ);
                        }
                        return OK;
                    case RAWWRITE:
                        while (!disk.write(param, (byte[]) args)) {
                            ioQueue.enqueueAndSleep(COND_DISK_FIN);
                        }
                        while (!disk.testAndResetReady()) {
                            ioQueue.enqueueAndSleep(COND_DISK_REQ);
                        }
                        return OK;
                    case SYNC:
                        while (!disk.sync()) {
                            ioQueue.enqueueAndSleep(COND_DISK_FIN);
                        }
                        while (!disk.testAndResetReady()) {
                            ioQueue.enqueueAndSleep(COND_DISK_REQ);
                        }
                        return OK;
                    case READ:
                        switch (param) {
                            case STDIN:
                                try {
                                    String str = input.readLine();
                                    if (str == null) {
                                        return ERROR;
                                    }
                                    localObject2 = (StringBuffer) args;


                                    ((StringBuffer) localObject2).append(str);


                                    return str.length();
                                } catch (IOException localIOException) {
                                    System.out.println(localIOException);
                                    return ERROR;
                                }
                            case STDOUT:
                            case STDERR:
                                System.out.println("threaOS: caused read errors");
                                return ERROR;
                        }
//                        if ((myTcb = scheduler.getMyTcb()) != null) {
//                            localObject1 = myTcb.getFtEnt(param);
//                            if (localObject1 != null) {
//                                return fs.read((FileTableEntry) localObject1, (byte[]) args);
//                            }
//                        }
                        return ERROR;
                    case WRITE:
                        switch (param) {
                            case 0:
                                System.out.println("threaOS: cannot write to System.in");
                                return ERROR;
                            case 1:
                                System.out.print((String) args);
                                return OK;
                            case 2:
                                System.err.print((String) args);
                                return OK;
                        }
//                        if ((myTcb = scheduler.getMyTcb()) != null) {
//                            localObject1 = myTcb.getFtEnt(param);
//                            if (localObject1 != null) {
//                                return fs.write((FileTableEntry) localObject1, (byte[]) args);
//                            }
//                        }
                        return ERROR;
                    case CREAD:
                        return cache.read(param, (byte[]) args) ? 0 : -1;
                    case CWRITE:
                        return cache.write(param, (byte[]) args) ? 0 : -1;
                    case CSYNC:
                        cache.sync();
                        return OK;
                    case CFLUSH:
                        cache.flush();
                        return OK;
                    case OPEN:
                        if ((myTcb = scheduler.getMyTcb()) != null) {
                            localObject1 = (String[]) args;
                            return myTcb.getFd(fs.open(localObject1[0], localObject1[1]));
                        }
                        return ERROR;
                    case CLOSE:
                        if ((myTcb = scheduler.getMyTcb()) != null) {
                            localObject1 = myTcb.getFtEnt(param);
                            if ((localObject1 == null) || (!fs.close((FileTableEntry) localObject1))) {
                                return ERROR;
                            }
                            if (myTcb.returnFd(param) != localObject1) {
                                return ERROR;
                            }
                            return OK;
                        }
                        return ERROR;
                    case SIZE:
                        if ((myTcb = scheduler.getMyTcb()) != null) {
                            localObject1 = myTcb.getFtEnt(param);
                            if (localObject1 != null) {
                                return fs.fsize((FileTableEntry) localObject1);
                            }
                        }
                        return ERROR;
                    case SEEK:
                        if ((myTcb = scheduler.getMyTcb()) != null) {
                            localObject1 = (int[]) args;
                            localObject2 = myTcb.getFtEnt(param);
                            if (localObject2 != null) {
                                return fs.seek((FileTableEntry) localObject2, localObject1[0], localObject1[1]);
                            }
                        }
                        return ERROR;
                    case FORMAT:
                        return fs.format(param) == true ? 0 : -1;
                    case DELETE:
                        return fs.delete((String) args) == true ? 0 : -1;
                }
                return ERROR;
            case INTERRUPT_DISK:
                ioQueue.dequeueAndWakeup(2);


                ioQueue.dequeueAndWakeup(1);

                return OK;
            case INTERRUPT_IO:
                return OK;
        }
        return OK;
    }

    private static int sysExec(String[] args) {
        String thrName = args[0];
        Object thrObj = null;
        try {
            Class thrClass = Class.forName(thrName);
            if (args.length == 1) {
                thrObj = thrClass.newInstance();
            } else {
                String thrArgs[] = new String[args.length - 1];
                for (int i = 1; i < args.length; i++) {
                    thrArgs[(i - 1)] = args[i];
                }
                Object[] constructorArgs = new Object[]{thrArgs};


                Constructor thrConst = thrClass.getConstructor(new Class[]{String[].class});


                thrObj = thrConst.newInstance(constructorArgs);
            }
            Object localObject2 = new Thread((Runnable) thrObj);


            Object localObject3 = scheduler.addThread((Thread) localObject2);
            return localObject3 != null ? ((TCB) localObject3).getTid() : -1;
        } catch (ClassNotFoundException e) {
            System.out.println(e);
            return ERROR;
        } catch (NoSuchMethodException e) {
            System.out.println(e);
            return ERROR;
        } catch (InstantiationException e) {
            System.out.println(e);
            return ERROR;
        } catch (IllegalAccessException e) {
            System.out.println(e);
            return ERROR;
        } catch (InvocationTargetException e) {
            System.out.println(e);
            return ERROR;
        }
    }
}
