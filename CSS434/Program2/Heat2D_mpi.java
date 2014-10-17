/*
 * CSS434 Parallel and Distributed Computing
 * Spring 2014
 * Program 2: Heat2D
 * Christopher Tran
 * Student ID: 1368253
 */
import java.util.Date;
import mpi.*;

/*
 * Class Heat2D_mpi
 *
 * Modification of a sequential execution of Eulers Heat Simulation algorithm
 * Takes in a given size, running time, heat time and simulates using a heat equation
 * Heat source is located in the first row using the center one third of the size
 *
 */
public class Heat2D_mpi {
    //Variables kept from Heat2D Sequential
    private static double a = 1.0;
    private static double dt = 1.0;
    private static double dd = 2.0;
    private static int size = 0;

    /*
     * Main
     *
     * @param args four integers in the order of size, time to run, time to heat, and output interval
     * @throws MPIException
     */
    public static void main(String[] args) throws MPIException {
        int myRank = 0; //Rank value for each Node
        int nodeNum = 1; //Number of total nodes

        //Initialize MPI
        MPI.Init(args);

        //Node keeps track of Rank and total size of nodes
        myRank = MPI.COMM_WORLD.Rank();
        nodeNum = MPI.COMM_WORLD.Size();

        //Program takes 4 arguements. Due to MPI, this is equal to 1+2N for a total of 9
        if (args.length != 9) {
            if (myRank == 0) {
                System.err.println("args.length = " + args.length);
                System.err.println("usage: prunjava #cpus Heat2D_mpi size max_time heat_time interval");
            }
            MPI.Finalize();
            System.exit(-1);
        }

        //Get arguement integer values from user input
        size = Integer.parseInt(args[1]);
        int max_time = Integer.parseInt(args[2]);
        int heat_time = Integer.parseInt(args[3]);
        int interval = Integer.parseInt(args[4]);

        //Taken from base Heat2D
        double r = a * dt / (dd * dd);

        //Initialize all array indexes to 0.0
        //Probably not needed since by default, Java initializes to 0.0
        double[] z = new double[2 * size * size];
        for (int p = 0; p < 2; p++) {
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    z[indexOf(p, x, y)] = 0.0;
                }
            }
        }

        //Time of Start for Performance Tracking
        Date startDate = new Date();

        //Taken from MatrixMult
        //Avg rows for each node to process
        int avgRows = size / nodeNum;
        //Extra rows that need to be added to beginning nodes due to remainder division
        int extRows = size % nodeNum;

        //Arrays to keep track of each nodes section
        //Adapted from MyProgram
        int[] rowsToProcess = new int[nodeNum];
        int[] rowOffset = new int[nodeNum];
        int[] endRow = new int[nodeNum];
        for (int i = 0; i < nodeNum; i++) {
            //How many rows each node processes
            rowsToProcess[i] = avgRows + (i < extRows ? 1 : 0);
            //The offset that each node starts at
            rowOffset[i] = i < extRows ? avgRows * i + i : avgRows * i + extRows;
            //The end row for each node
            endRow[i] = (rowOffset[i] + rowsToProcess[i] - 1);
        }

        //Run for as long as max_time
        for (int i = 0; i < max_time; i++) {
            //Select between first and second array by tick
            int p = i % 2;
            //Two upper and lower rows are identical
            for (int y = 0; y < size; y++) {
                z[indexOf(p, 0, y)] = z[indexOf(p, 1, y)];
                z[indexOf(p, size - 1, y)] = z[indexOf(p, size - 2, y)];
            }

            //Two left and right most columns are identical
            //Optimized to only process current ranks allotment
            for (int x = rowOffset[myRank]; x <= endRow[myRank]; x++) {
                z[indexOf(p, x, 0)] = z[indexOf(p, x, 1)];
                z[indexOf(p, x, size - 1)] = z[indexOf(p, x, size - 2)];
            }

            //keep heating the bottom while t < heat_time
            //Master will always have the first row assigned
            if (i < heat_time) {
                for (int x = size / 3; x < size / 3 * 2; x++) {
                    z[indexOf(p, x, 0)] = 19.0;
                }
            }


            //When there are more than one nodes, trade border information
            if (nodeNum > 1) {
                //Even ranks Receive then Send, Odd Ranks are opposire
                //This should help to increase performance and reduce blocking
                //Idea taken from MPIJava examples
                if (myRank % 2 == 0) {
                    //EVEN RANKS
                    //Master rank skips receiving from rank-1 since it doesn't exist
                    if (myRank != 0) {
                        //Receive a row of information from rank-1 and place it below my information
                        MPI.COMM_WORLD.Recv(z, indexOf(p, rowOffset[myRank] - 1, 0), size, MPI.DOUBLE, myRank - 1, 0);
                    }
                    //Last node skips receiving from tank+1 since it doesn't exist
                    if (myRank != nodeNum - 1) {
                        //Receive a row of information from rank+1 and place it above my information
                        MPI.COMM_WORLD.Recv(z, indexOf(p, endRow[myRank] + 1, 0), size, MPI.DOUBLE, myRank + 1, 0);
                    }
                    //Master rank skips sending to rank-1 since it doesnt exist
                    if (myRank != 0) {
                        //Send the first row of this rank to rank-1
                        MPI.COMM_WORLD.Send(z, indexOf(p, rowOffset[myRank], 0), size, MPI.DOUBLE, myRank - 1, 0);
                    }
                    //Last node skips sending to rank+1 since it doesnt exist
                    if (myRank != nodeNum - 1) {
                        //Send the last row to from this rank to rank+1
                        MPI.COMM_WORLD.Send(z, indexOf(p, endRow[myRank], 0), size, MPI.DOUBLE, myRank + 1, 0);
                    }
                } else {
                    //ODD RANKS
                    //Last node skips sending to rank+1 since it doesnt exist
                    if (myRank != nodeNum - 1) {
                        //Send the last row to from this rank to rank+1
                        MPI.COMM_WORLD.Send(z, indexOf(p, endRow[myRank], 0), size, MPI.DOUBLE, myRank + 1, 0);
                    }
                    //Master rank skips sending to rank-1 since it doesnt exist
                    if (myRank != 0) {
                        //Send the first row of this rank to rank-1
                        MPI.COMM_WORLD.Send(z, indexOf(p, rowOffset[myRank], 0), size, MPI.DOUBLE, myRank - 1, 0);
                    }
                    //Last node skips receiving from tank+1 since it doesn't exist
                    if (myRank != nodeNum - 1) {
                        //Receive a row of information from rank+1 and place it above my information
                        MPI.COMM_WORLD.Recv(z, indexOf(p, endRow[myRank] + 1, 0), size, MPI.DOUBLE, myRank + 1, 0);
                    }
                    //Master rank skips receiving from rank-1 since it doesn't exist
                    if (myRank != 0) {
                        //Receive a row of information from rank-1 and place it below my information
                        MPI.COMM_WORLD.Recv(z, indexOf(p, rowOffset[myRank] - 1, 0), size, MPI.DOUBLE, myRank - 1, 0);
                    }

                }
            }

            //Print out to console if beginning, end, or an interval is reached
            //Kept from Heat2D
            if ((interval != 0) && ((i % interval == 0) || (i == max_time - 1))) {
                //Assemble entire array when we need to print
                if (myRank == 0) {
                    //Get information from all other nodes
                    for (int source = 1; source < nodeNum; source++) {
                        MPI.COMM_WORLD.Recv(z, indexOf(p, rowOffset[source], 0), size * rowsToProcess[source], MPI.DOUBLE, source, 0);
                    }
                    System.out.println("time = " + i);
                    for (int y = 0; y < size; y++) {
                        for (int x = 0; x < size; x++) {
                            System.out.print((int)( Math.floor(z[indexOf(p, x, y)] / 2)) + " ");
                        }
                        System.out.println();
                    }
                    System.out.println();
                } else {
                    //Send information to master
                    MPI.COMM_WORLD.Send(z, indexOf(p, rowOffset[myRank], 0), size * rowsToProcess[myRank], MPI.DOUBLE, 0, 0);
                }
            }

            //perform forward Euler method
            //kept from Heat2D
            int p2 = (p + 1) % 2;
            for (int x = rowOffset[myRank]; x <= endRow[myRank]; x++) {
                //Skip the first row and last row
                if ((x != 0) && (x != size - 1)) {
                    //Skip the first column and last column
                    for (int y = 1; y < size - 1; y++) {
                        z[indexOf(p2, x, y)] = (z[indexOf(p, x, y)] +
                                r * (z[indexOf(p, x + 1, y)] - 2.0 * z[indexOf(p, x, y)] + z[indexOf(p, x - 1, y)]) +
                                r * (z[indexOf(p, x, y + 1)] - 2.0 * z[indexOf(p, x, y)] + z[indexOf(p, x, y - 1)]));
                    }
                }
            }
        }

        //print out end time for performance evaluation
        if (myRank == 0) {
            Date endDate = new Date();
            System.out.println("Elapsed time = " + (endDate.getTime() - startDate.getTime()));
        }
        MPI.Finalize();



    }

    /**
     * Converts a three-dimensional value to match a one-dimensional array
     * Necessary due to limitation of on dimentional array through MPIJava
     * @param p Equivilent p value
     * @param x Equivilent x value
     * @param y Equivilent y value
     * @return
     */
    public static int indexOf(int p, int x, int y) {
        //return (p)+(x)+(y)
        return (p * size * size) + (x * size) + y;
    }
}