#include <sys/file.h> // for flock(2)
#include <sys/stat.h> // for S_* constants
#include <string.h>   // for strerror(3) prototype
#include <stdio.h>    // for fprintf(3),printf(3),stderr protype
#include <errno.h>    // for errno prototype
#include <unistd.h>   // for close(2) prototypes
#include <iostream>   // for C++ cin and cout
#define FILENAME "/tmp/flock.example"

using namespace std;

int main(int argc,char **argv) {
   int fd; char buf;
   fd = open(FILENAME,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

   // Aquire an exclusive lock
   if (flock(fd,LOCK_EX) == -1)  
      return -1; 
   cout << "Press ctl-D to release the lock." << endl;
   cin >> buf;

   // Release the exclusive lock
   if (flock(fd,LOCK_UN)==-1)    
      return -1;
   printf("Released!\n");
   if(close(fd)==-1)
      return 0;
}
