/**
 * CSS434 Parallel and Distributed Computing
 * Spring 2014
 * Lab2 - MPI Java
 * Christopher Tran
 * Student ID: 1368253
 *
 * Modify Myprogram.java to implement a distributed program to calculare the square root of array size 100
 * Each index starts as the index of the array from 0 to 99
 *
 * Modifications
 * Support for nodes with remainder division of size ie if (size % nodes) > 0
 */
import mpi.*;   // for mpiJava

public class MyProgram {
    private final static int aSize = 100; // the size of dArray
    private final static int master = 0;  // the master rank
    private final static int tag = 0;     // Send/Recv's tag is always 0.
    private static int size;
    private static int myRank;

    public static void main(String[] args) throws MPIException {
        // Start the MPI library.
        MPI.Init(args);

        // Compute what each rank will process
        size = MPI.COMM_WORLD.Size();
        myRank = MPI.COMM_WORLD.Rank();
        int stripe = aSize / size; // each portion of array
        int extra = aSize % size;  // extra arrays
        int numToProcess[] = new int[size]; //How many numbers each rank processes

        //Calculate how many each rank should process
        for(int i = 0; i < size; i++) {
            //Check if a rank is less than the remainder and add an additional number to process
            numToProcess[i] = stripe + (i < extra ? 1 : 0);
        }

        //Each rank allocates an unspecified size dArray
        double[] dArray = null;

        if (myRank == 0) { // master

            // initialize dArray[100].
            dArray = new double[aSize];
            //Populate dArray with values
            for (int i = 0; i < aSize; i++)
                dArray[i] = i;

            // send a portion of dArray[100] to each slave
            // (1) implement by yourself
            //Keep track of offset for each rank
            //First offset is after rank 0
            int offset = numToProcess[0];
            for (int i = 1; i < size; i++) {
                //Send dArray with offset and how many numbers to process
                MPI.COMM_WORLD.Send(dArray, offset, numToProcess[i], MPI.DOUBLE, i, tag);
                //Increment offset by how many numbers the rank processes
                offset += numToProcess[i];
            }

        } else { // slaves: rank 0 to rank n - 1

            // allocates dArray[] with size of numbers to process
            dArray = new double[numToProcess[myRank]];

            // receive a portion of dArray[100] from the master
            // (2) implement by yourself
            MPI.COMM_WORLD.Recv(dArray, 0, numToProcess[myRank], MPI.DOUBLE, 0, tag);
        }

        // compute the square root of each array element
        for (int i = 0; i < numToProcess[myRank]; i++)
            dArray[i] = Math.sqrt(dArray[i]);

        if (MPI.COMM_WORLD.Rank() == 0) { // master

            // receive answers from each slave
            // (3) implement by yourself
            //Keep track of offset for each rank
            //First offset is after rank 0
            int offset = numToProcess[0];
            for (int i = 1; i < size; i++) {
                //Receive a portion of the dArray
                MPI.COMM_WORLD.Recv(dArray, offset, numToProcess[i], MPI.DOUBLE, i, tag);
                offset += numToProcess[i];
            }

            // print out the results
            for (int i = 0; i < aSize; i++) {
                System.out.println("dArray[ " + i + " ] = " + dArray[i]);
            }
        } else { // slaves: rank 0 to rank n - 1

            // send the results back to the master
            // (4) implement by yourself
            MPI.COMM_WORLD.Send(dArray, 0, numToProcess[myRank], MPI.DOUBLE, 0, tag);

        }

        // Terminate the MPI library.
        MPI.Finalize();
    }
}
