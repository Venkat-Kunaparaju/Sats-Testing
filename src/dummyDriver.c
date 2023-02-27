/* Code to emulate (not really) a driver */

#include "../include/PSP.h"

/* 
Drivers would read from line, storing into the buffer specified by the user, 
and the user would then be able to acess the contents in the buffer
*/
int read(int fd, void * buf) {
    char * temp = "This is what was read in";
    memcpy(buf, temp, strlen(temp));

    return 1;
}