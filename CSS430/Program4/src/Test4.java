/**
 * CSS430 Operating Systems
 * Professor Stephen Dame
 * Program4 : Test4
 * Christopher Tran
 */

import java.util.*;

public class Test4 extends Thread{
    private boolean useCache; //Trigger for using cache or disk
    private int testNum; //The passed in test number
    private Random rando; //Rando Calrissian
    private long start; //Start time for performance report
    private long end; //end time for performance report


    public Test4(String args[]) {
        //Use cache if first argument is enabled or number 1
        useCache  = (args[0].equals("enabled") || Integer.parseInt(args[0]) == 1);
        //Get the test number from second argument
        testNum = Integer.parseInt(args[1]);
        //Call Rando Calrissian to help us
        rando = new Random();
    }

    /**
     * Determines which test case to run
     * Random
     * Localized
     * Mixed
     * Adversary
     */
    public void run() {
        SysLib.flush(); //Flush the cache
        start = new Date().getTime();
        switch (testNum) {
            case 1: //RANDOM
                random();
                end = new Date().getTime();
                getReport("Random");
                break;
            case 2: //LOCALIZED
                localized();
                end = new Date().getTime();
                getReport("Localized");
                break;
            case 3: //MIXED
                mixed();
                end = new Date().getTime();
                getReport("Mixed");
                break;
            case 4: //ADVERSARY
                adversary();
                end = new Date().getTime();
                getReport("Adversary");
                break;
            case 5: //RUN ALL
                random();
                end = new Date().getTime();
                getReport("Random");

                start = new Date().getTime();
                localized();
                end = new Date().getTime();
                getReport("Localized");

                start = new Date().getTime();
                mixed();
                end = new Date().getTime();
                getReport("Mixed");

                start = new Date().getTime();
                adversary();
                end = new Date().getTime();
                getReport("Adversary");
                break;
        }
        SysLib.exit();
    }





    /**
     * Random location data access
     * Should have a high probability of cache misses
     */
    private void random() {
        //create Byte array
        byte[] outData = new byte[512];
        //Fill with random Data
        for(int i = 0; i < 512; i++) {
            outData[i] = (byte)Math.abs(rando.nextInt());
        }
        //create array for random numbers to be used for writing and reading in the same order
        int[] randomNumbers = new int[200];

        //Writiing 200 times
        for(int i = 0; i < 200; i++) {
            //Get a random number and store into random array, disk has 1000 blocks
            randomNumbers[i] = Math.abs(rando.nextInt()% 1000);

            //write outData
            writeData(randomNumbers[i],outData);
        }

        //Array for incoming data
        byte[] inData = new byte[512];
        //Reading 200 times
        for(int i = 0; i < 200; i++) {
            //read data
            readData(randomNumbers[i],inData);
            //Check if data matches what was written
            for(int j = 0; j < 512; j++) {
                if(inData[j] != outData[j]) {
                    SysLib.cerr("ERROR\n");
                    SysLib.exit();
                }
            }
        }
    }

    /**
     * Localized location data access
     * cache data and read form cache without causing additional disk access
     */
    private void localized() {
        //create Byte array
        byte[] outData = new byte[512];
        //Fill with random Data
        for(int i = 0; i < 512; i++) {
            outData[i] = (byte)Math.abs(rando.nextInt());
        }

        //Array for incoming data
        byte[] inData = new byte[512];

        //200 with 10 pages is 20 iterations
        for(int i = 0; i < 20; i++) {
            //Each DISK block is 512 bytes, we can use consecutive blocks to write
            for(int j = 0; j < 10; j ++) {
                writeData(j,outData);
            }
            //read data back and check for consistency

            for(int j = 0; j < 10; j ++) {
                readData(j,inData);
                for(int k = 0; k < 512; k++) {
                    if (inData[k] != outData[k]) {
                        SysLib.cerr("ERROR\n");
                        SysLib.exit();
                    }
                }
            }
        }
    }

    /**
     * Mix of Random and Localized
     * 90% localized, 10% random
     */
    private void mixed() {
        //create Byte array
        byte[] outData = new byte[512];
        //Fill with random Data
        for(int i = 0; i < 512; i++) {
            outData[i] = (byte)Math.abs(rando.nextInt());
        }
        //create array of random numbers to be used for writing and reading in the same order
        int[] randomNumbers = new int[200];
        int rNumber;

        for(int i = 0; i < 200; i++) {
            //Get a random number
            rNumber = Math.abs(rando.nextInt());

            //to get 10% random, check if the singles digit is 0
            if(rNumber % 10 == 0) {
                //10% will go to any block on disk
                randomNumbers[i] = rNumber % 1000;
            } else {
                //the remaining 90% chance will target the first 10 blocks of the disk
                randomNumbers[i] = rNumber % 10;
            }
        }

        //Writing 200 times
        for(int i = 0; i < 200; i++) {
            writeData(randomNumbers[i],outData);
        }
        byte[] inData = new byte[512];

        //Read 200 times
        for(int i = 0; i < 200; i++) {
            readData(randomNumbers[i],inData);
            for(int j = 0; j < 512; j++) {
                if (inData[j] != outData[j]) {
                    SysLib.cerr("ERROR\n");
                    SysLib.exit();
                }
            }
        }
    }

    /**
     * Scenario where cache access is most terrible
     * Each hit should be a cache miss and cause disk to cache copying
     *
     * Each hit should also skip a tracks are at index 0 and every 100 blocks on disk
     */
    private void adversary() {
        byte[] outData = new byte[512];
        //Fill with random Data
        for(int i = 0; i < 512; i++) {
            outData[i] = (byte)Math.abs(rando.nextInt());
        }

        int[] adversarySequence = new int[200];
        //Create adversary sequence
        //Ever number in the sequence is far enough from each other to
        //cause a cache miss and a track jump
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                adversarySequence[(i*10)+j] = i + (j*100);
            }
        }

        //write 200 times
        for(int i = 0; i < 200; i++) {
            writeData(adversarySequence[i],outData);
        }

        byte[] inData = new byte[512];
        //read 200 times and check consistency
        for(int i = 0; i < 200; i++) {
            readData(adversarySequence[i],inData);
            for(int j = 0; j < 512; j++) {
                if (inData[j] != outData[j]) {
                    SysLib.cerr("ERROR\n");
                    SysLib.exit();
                }
            }
        }
    }

    /**
     * Write data to either disk or cache
     * Same parameters as rawwrite except will use cache when enabled
     *
     * @param blockID Integer of BlockID
     * @param data Byte array to write
     */
    private void writeData(int blockID, byte[] data) {
        if(useCache) {
            SysLib.cwrite(blockID,data);
        } else {
            SysLib.rawwrite(blockID,data);
        }
    }

    /**
     * Read data from either disk or cache
     * Same parameters as rawread except will use cache when enabled
     *
     * @param blockID Integer of BlockID
     * @param data Byte array to read into
     */
    private void readData(int blockID, byte[] data) {
        if(useCache) {
            SysLib.cread(blockID,data);
        } else {
            SysLib.rawread(blockID,data);
        }
    }

    /**
     * Get report from start and end times
     * Type of test will be replaced with any String parameter
     *
     * @param s String for reporting
     */
    private void getReport(String s) {
        if(useCache) {
            SysLib.cout("Test " + s + "(cache enabled): " + (end - start) + "\n");
        } else {
            SysLib.cout("Test " + s + "(cache disabled): " + (end - start) + "\n");
        }
    }

    private void sync() {
        if(useCache) {
            SysLib.csync();
        } else {
            SysLib.sync();
        }
    }
}
