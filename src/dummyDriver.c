/* Code to emulate (not really) a driver */

#include "../include/PSP.h"

/* 
Drivers would read from line, storing into the buffer specified by the user, 
and the user would then be able to acess the contents in the buffer
*/
int read(int fd, void * buf) {
    //Wait for something to come in
    char * temp = "This is what was read in";
    memcpy(buf, temp, strlen(temp));
    return 1;
}

/*
Drivers would write to line with the data stored in the buffer passed in by the user
*/
int write(int fd, void *buf, int size) {
    char * outputData = buf;
    char * imagineThisIsOutPutLine = malloc(size);
    memcpy(imagineThisIsOutPutLine, outputData, size);
#if PACKETWRITEDEBUG
    fprintf(stderr, "This is what was written: %s\n", imagineThisIsOutPutLine);
#endif
    return 1;
}