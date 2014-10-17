#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#define PACKAGE "mmap"

int main(int argc, char *argv[]) {
   int input, output;
   size_t filesize;
   void *source, *target;

   if((input = open(argv[1], O_RDONLY)) == -1) exit(-1);
   if((output = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1) exit(-1);

   if((source = mmap(0, filesize, PROT_READ, MAP_SHARED, input, 0)) == (void *) -1) exit(-1);
   if((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *) -1) exit(-1);

   memcpy(target, source, filesize);
   munmap(source, filesize);
   munmap(target, filesize);

   close(input);
   close(output);
   return 0;
}
