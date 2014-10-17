/*
CSS430B Spring 2014
Professor Stephen Dame
Programming Assignment 2 Part 2 Multi-Level Queue Scheduler

Specification
Has three queues from 0 to 2
Added Threads always go into Queue 0
Threads in Queue 0 get execution time of timeSlice / 2
Threads in Queue 1 get execution time of timeSlice
Threads in Queue 2 get execution time of timeSlice * 2
When a Thread reaches the maximum execution time in a queue, it gets moved into a higher queue
	except Threads in Queue 2 get moved to the end of Queue 2
At intervals of timeSlice / 2, restart at Queue 0 to determine any new threads

Grading Requirements
	queue[0] has 500 msec time quantum (Completed)
	queue[1] has 1000 msec time quantum (Completed)
	queue[2] has 2000 msec time quantum (Completed)
	New threads enqueued in queue[0] by addThread( ) (Completed)
	Threads searched from queue[0], [1], and [2] by getMyTcb( ) (Completed)
	The next thread picked up from the highest queue every 500msec (Completed)
	A thread resumed for the its remaining time quantum (Completed)
	Correct behavior (by Test2 and Test2b) (Completed)

Current Implementation
Array of size 3 containing Queues implemented using LinkedLists
	Linked Lists were chosen for quick performance since random
	search is not a key feature of Scheduler
Queue implementation is LinkedLists and uses Iterator object in getMyTCB
Added DEFAULT_CYCLE equal to half of timeSlice
maxCycles array determines how many cycles in each Queue
	Queue0 : 1 cycle = 500ms
	Queue1 : 2 cycles = 1000ms
	Queue2 : 4 cycles = 2000ms
Class supports Queue levels beyond 3 and scales based on cycle pattern
    Queue0 : 2^0 cycles = 500ms
	Queue1 : 2^1 cycles = 1000ms
	Queue2 : 2^2 cycles = 2000ms
	Queue3 : 2^3 cycles = 4000ms
	.....
Ideal Implementation

*/
import java.util.*;

public class Scheduler extends Thread {

    private Queue<TCB>[] queue; //Array of Queues for MLQS
    private int timeSlice;  //Amount of time each Thread gets to execute
    private int[] cycles;   //Number of cycles a thread has executed
    private int[] maxCycles; //Number of cycles a thread is allowed in each queue
    private static final int DEFAULT_TIME_SLICE = 1000; //Default timeSlice
    private static final int DEFAULT_CYCLE = DEFAULT_TIME_SLICE/2; //Default cycle time
    private static final int QUEUE_LEVEL = 3; //Number of Queues

    // New data added to p161
    private boolean[] tids; //Allocation for TIDs
    private static final int DEFAULT_MAX_THREADS = 10000; //Maximum amount of TIDs to allow

    // A new feature added to p161
    // Allocate an ID array, each element indicating if that id has been used
    // Reused Code from base Scheduler
    // Sets all array values to false since no TIDs allocated yet
    // Keeps index of the next TID to give out so no need to check from beginning
    private int nextId = 0;
    private void initTid(int maxThreads) {
        tids = new boolean[maxThreads];
        for(int i = 0; i < tids.length; i++) {
            tids[i] = false;
        }
    }

    // A new feature added to p161
    // Search an available thread ID and provide a new thread with this ID
    // Returns the next available TID position starting from the index nextId
    private int getNewTid() {
        for ( int i = 0; i < tids.length; i++ ) {
            int tentative = ( nextId + i ) % tids.length;
            if ( tids[tentative] == false ) {
                tids[tentative] = true;
                nextId = ( tentative + 1 ) % tids.length;
                return tentative;
            }
        }
        return -1;
    }

    // A new feature added to p161
    // Return the thread ID and set the corresponding tids element to be unused
    private boolean returnTid( int tid ) {
        if ( tid >= 0 && tid < tids.length && tids[tid] == true ) {
            tids[tid] = false;
            return true;
        }
        return false;
    }

    // A new feature added to p161
    // Retrieve the current thread's TCB from the queue
	/**
	* Modified using a for loop to go through the array of Queues
	* Uses an iterator for each Queue to go through Queue for a match
	*/
    public TCB getMyTcb( ) {
        Thread myThread = Thread.currentThread( ); // Get my thread object
        synchronized( queue ) {
            for(int i = 0; i < queue.length; i++){
                Iterator it = queue[i].iterator();
                while(it.hasNext()) {
                    TCB tcb = (TCB)it.next();
                    Thread thread = tcb.getThread();
                    if (thread == myThread) // if this is my TCB, return it
                        return tcb;
                }
            }
        }
        return null;
    }

    // A new feature added to p161
    // Return the maximal number of threads to be spawned in the system
    public int getMaxThreads( ) {
        return tids.length;
    }

    /**
     * Default Constructor
     */
    public Scheduler( ) {
        timeSlice = DEFAULT_CYCLE;
        cycles = new int[QUEUE_LEVEL];
        Arrays.fill(cycles,0);
        queue = new Queue[QUEUE_LEVEL];
        setupMaxCycles(QUEUE_LEVEL);
        setupQueue(QUEUE_LEVEL);
        initTid( DEFAULT_MAX_THREADS );
    }

    /**
     * Constructor allowing a custom timeSlice
     * In the case of MLQS, sets cycle time
     * @param quantum
     */
    public Scheduler( int quantum ) {
        timeSlice = quantum;
        cycles = new int[QUEUE_LEVEL];
        Arrays.fill(cycles,0);
        queue = new Queue[QUEUE_LEVEL];
        setupQueue(QUEUE_LEVEL);
        initTid( DEFAULT_MAX_THREADS );
    }

    // A new feature added to p161
    // A constructor to receive the max number of threads to be spawned
    public Scheduler( int quantum, int maxThreads ) {
        timeSlice = quantum;
        cycles = new int[QUEUE_LEVEL];
        Arrays.fill(cycles,0);
        queue = new Queue[QUEUE_LEVEL];
        setupQueue(QUEUE_LEVEL);
        initTid( maxThreads );
    }

    /**
     * Scheduler sleeps to allow a running Thread to execute uninterrupted for
     * a period of time equal to timeSlice
     */
    private void schedulerSleep( ) {
        try {
            Thread.sleep( timeSlice );
        } catch ( InterruptedException e ) {
        }
    }

    /**
     * Setup Multi Level Queue
     * Queue is implemented using Linked List for performance
     * @param levels Number of Queues
     */
    private void setupQueue(int levels) {
        for(int i = 0; i < levels; i++) {
            queue[i] = new LinkedList<TCB>();
        }
    }

    /**
     * Sets up an array with the maximum number
     * of cycles a Thread is allowed to execute
     * @param levels
     */
    private void setupMaxCycles(int levels) {
        maxCycles = new int[levels];
        for(int i = 0; i < levels; i++) {
            maxCycles[i] = (int)Math.pow(2,i);
        }

    }

    // A modified addThread of p161 example
    /**
     * Modified to add new TCBs into queue[0] instead of queue
     * @param t
     * @return
     */
    public TCB addThread( Thread t ) {
        TCB parentTcb = getMyTcb( ); // get my TCB and find my TID
        int pid = ( parentTcb != null ) ? parentTcb.getTid( ) : -1;
        int tid = getNewTid( ); // get a new TID
        if ( tid == -1)
            return null;
        TCB tcb = new TCB( t, tid, pid ); // create a new TCB
        queue[0].add(tcb);
        return tcb;
    }

    // A new feature added to p161
    // Removing the TCB of a terminating thread
    public boolean deleteThread( ) {
        TCB tcb = getMyTcb( );
        if ( tcb!= null )
            return tcb.setTerminated( );
        else
            return false;
    }

    public void sleepThread( int milliseconds ) {
        try {
            sleep( milliseconds );
        } catch ( InterruptedException e ) { }
    }

    /**
     * Checks if all Queues in array are empty
     * @return
     */
    private boolean isEmpty() {
        for(int i = 0; i < QUEUE_LEVEL; i++) {
            if(!queue[i].isEmpty()) {
                return false;
            }
        }
        return true;
    }

    //Loop will repeat every cycle time, in the case of the current configuration, this will be
    //aproximately 500ms due to the additional tasks that may or may not happen
    //Break will be used to exit the foor loop at specific key locations to ensure that
    //Scheduler checks the beginning for any Threads that may have been
    //added and need to be processed first
    public void run() {
        Thread current = null;
        while(true) {
            try {
                //If all queues are empty, do nothing
                if(isEmpty()) {
                    continue;
                }
                //One of the queues is not empty, process queues
                //Loop through each queue
                for(int i = 0; i < QUEUE_LEVEL; i++) {
                    //if it's not empty, let the head of the Queue execute for one cycle
                    if(!queue[i].isEmpty()) {
                        //Check if the head of the queue has been terminated and remove from queue
                        TCB currentTCB = queue[i].element();
                        if ( currentTCB.getTerminated( ) == true ) {
                            queue[i].remove();
                            returnTid( currentTCB.getTid( ) );
                            //Break out of for loop to repeat from beginning of Queue
                            break;
                        }
                        //Get the current thread to execute
                        current = currentTCB.getThread();
                        //If the thread is continuting, resume, otherwise start the thread
                        if(current != null) {
                            if(current.isAlive()) {
                                current.resume();
                            } else {
                                current.start();
                            }
                        }
                        //Sleep for a cycle time/timeSlice
                        schedulerSleep();
                        //Increase the value in cycles array at the same index as the queue to track
                        //cycle progress in the event that a higher queue executes
                        //This will ensure that processes in higher queues still only
                        //get the execution time allowed
                        cycles[i]++;
                        synchronized ( queue ) {
                            //Check if Thread completed and remove
                            if ( currentTCB.getTerminated( ) == true ) {
                                queue[i].remove();
                                returnTid( currentTCB.getTid( ) );
                                //Set the cycle at index of queue location to reset for next thread
                                cycles[i] = 0;
                                //Break out of for loop to repeat from beginning of Queue
                                break;
                            }
                            //Suspend the thread
                            if ( current != null && current.isAlive( ) )
                                current.suspend();
                            //If the thread has executed its allotment of cycles, move it to the next queue
                            //While cycles should never get above the maxCycles at the same index,
                            //Check just in case someone tried to introduce a bug
                            if(cycles[i] >= maxCycles[i]) {
                                queue[i].remove(); // rotate this TCB to the end
                                //Move to the next queue, if next queue is higher than possible, add
                                //To the largest queue
                                queue[(i + 1) >= QUEUE_LEVEL ? (QUEUE_LEVEL - 1) : i + 1].add(currentTCB);
                                //Set current cycles to 0 for the next Thread
                                cycles[i] = 0;
                                //Break out of for loop to repeat from beginning of Queue
                                break;
                            } else {
                                //Break out of for loop to repeat from beginning of Queue
                                break;
                            }
                        }
                    }
                }

            }catch (NullPointerException e) {

            }
        }
    }
}
