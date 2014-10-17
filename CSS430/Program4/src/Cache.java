/**
 * CSS430 Operating Systems
 * Professor Stephen Dame
 * Program4 : Cache
 * Christopher Tran
 */
public class Cache {
    private int[] blockStored; //information on which blockID is stored in location
    private boolean[] isReferenced; //Index based recent reference status
    private boolean[] isDirty; //index based dirty status
    private byte[][] pageData; //Two dimensional array containing cached data
    private int nextIndex; //location tracker for second algorithm to begin at
    private int cacheBlocks; //Number of blocks
    private int blockSize; //Size of each block

    /**
     * Initialize the object with a number of cacheBlocks with a specific size
     * @param blockSize Size of each cache page
     * @param cacheBlocks Number of pages in cache
     */
    public Cache(int blockSize, int cacheBlocks) {
        //Initialize local class variables
        this.cacheBlocks = cacheBlocks;
        this.blockSize = blockSize;
        //Initialize all arrays
        initialize(cacheBlocks);
        //Initialize cache array
        pageData = new byte[cacheBlocks][blockSize];
    }

    /**
     * Reads specific data based on Block ID. If data is not in the cache, it will be read into the cache
     *
     * @param blockId   BlockID to be read
     * @param buffer    Buffer array to store data to pass back to function caller
     * @return True if read correctly
     */
    public synchronized boolean read(int blockId, byte buffer[]) {
        //Check if parameter contains a valid block ID, should be greater than 0
        if(blockId < 0) {
            return false;
        }
        //Get location of the BlockID in the cache
        int page = doesExist(blockId);
        //If the block ID is in the cache, read from cache into th parameter buffer passed in
        if(page != -1) {
            //Copy pageData to parameter byte array
            System.arraycopy(pageData[page],0,buffer,0, blockSize);
        } else {
            //If the BlockID is not in the Cache, read into cache
            //Get pageData from disk
            //get the next available page to copy the pageData into
            page = findAvailablePage();

            //Read into the cache
            SysLib.rawread(blockId, pageData[page]);

            //Copy from cache to parameter buffer
            System.arraycopy(pageData[page],0,buffer,0, blockSize);

            //Set frame number and reference
            blockStored[page] = blockId;
            isReferenced[page] = true;
        }
        return true;
    }

    /**
     * Writes data into a specific BlockID and store it into the cache
     *
     * @param blockId   BlockID to store
     * @param buffer    Parameter with data to store
     * @return True if written properly
     */
    public synchronized boolean write(int blockId, byte buffer[]) {
        //Check if parameter contains a valid block ID, should be greater than 0
        if(blockId < 0) {
            return false;
        }

        //Get location of Block ID in the cache
        int page = doesExist(blockId);

        //If the cache contains the blockID, write to the same page location
        if(page != -1) {
            //Copy from buffer to the cache where page is stored
            System.arraycopy(buffer,0, pageData[page],0,blockSize);
            isReferenced[page] = true; //Page has been referenced
            isDirty[page] = true; //page has been modified
        } else {
            //Get an available page
            page = findAvailablePage();

            //copy from buffer to cache
            System.arraycopy(buffer,0, pageData[page],0,blockSize);

            blockStored[page] = blockId; //Store blockID into page details
            isReferenced[page] = true; //page has been referenced
            isDirty[page] = true; //page has been modified
        }
        return true;
    }

    /**
     * Check all pages and write data to disk
     * Send dirty data back to DISK
     */
    public synchronized void sync(){
        //Visit each page and write the data
        for(int i = 0; i < cacheBlocks; i++) {
            writeToDisk(i);
        }
        //System Sync
        SysLib.sync();
    }

    /**
     * Write all data to disk and revert back to an empty cache
     */
    public synchronized void flush() {
        for(int i = 0; i < cacheBlocks; i++) {
            writeToDisk(i); //Write page data to disk
            isReferenced[i] = false; //No longer needs reference
            blockStored[i] = -1; //Revert all BlockIDs to an invalid int
            isDirty[i] = false; //No longer dirty
        }
        nextIndex = 0; //reset tracker index to 0
        //System sync
        SysLib.sync();
    }

    /**
     * Initialize class arrays based on size
     *
     * @param size Number of pages in cache
     */
    private void initialize(int size) {
        isReferenced = new boolean[size];
        isDirty = new boolean[size];
        blockStored = new int[size];
        for(int i = 0; i < size; i++) {
            isReferenced[i] = false;
            isDirty[i] = false;
            blockStored[i] = -1;
        }
    }

    /**
     * Determine if a BlockID exists in the cache and returns the index location
     * Returns -1 if not found
     *
     * @param blockId Block number to check for existence
     * @return Index location if data is cached, otherwise -1
     */
    private int doesExist(int blockId) {
        for(int i = 0; i < cacheBlocks; i++) {
            if(blockStored[i] == blockId) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Uses second chance algorithm to determine an available page
     *
     * @return Returns index
     */
    private int findAvailablePage() {
        //Keep searching until a page is found
        while(true) {

            //get the nextIndex to start from a previous search
            int currentIndex = nextIndex % cacheBlocks;
            //Determine if a frame is empty by checking for -1
            if(blockStored[currentIndex] == -1) {
                //change the nextIndex to start next search at the next nextIndex
                nextIndex++;
                //return the empty index
                return currentIndex;
            }

            //If the isReferenced bit is true, change to false
            //and then continue search
            if(isReferenced[currentIndex] == true) {
                isReferenced[currentIndex] = false;
                nextIndex++;
                continue; //Start next search
            } else {
                //if page is dirty, write data before giving page number
                if(isDirty[currentIndex]) {
                    writeToDisk(currentIndex);
                }
                nextIndex++;
                return currentIndex;
            }
        }
    }

    /**
     * Write page data from cache back to Disk
     *
     * @param pageNum Index of the page to write back to disk
     */
    private void writeToDisk(int pageNum){
        //check if the page has data and is dirty
        if(blockStored[pageNum] != -1 && isDirty[pageNum] == true) {
            //write to disk using the blockStored and the pageData
            SysLib.rawwrite(blockStored[pageNum], pageData[pageNum]);
            isDirty[pageNum] = false; //Page is no longer dirty
        }
    }
}


