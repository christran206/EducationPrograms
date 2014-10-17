import java.io.*;
import java.nio.*;
import java.nio.channels.*;

public class MemoryMapReadOnly {
   // Assume page size of 4K
   public static final int PAGE_SIZE = 4096;

   public static void main (String args[]) throws IOException {
      RandomAccessFile inFile = new RandomAccessFile(args[0], "r");

      FileChannel in = inFile.getChannel();
      MappedByteBuffer mappedBuffer = in.map(FileChannel.MapMode.READ_ONLY, 0, in.size());
      long numPages = in.size() / (long)PAGE_SIZE;
      if( (in.size() % PAGE_SIZE) > 0)  ++numPages;

      // we will "touch" the first byte of every page
      int position = 0;
      for (long i=0; i < numPages; i++) {
         byte item = mappedBuffer.get(position);
         position += PAGE_SIZE;
      }
      in.close();
      inFile.close();
   }
}
