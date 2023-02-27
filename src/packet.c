/* Code to test turning data into packet from input data */

#include "../include/PSP.h"

int packetRead() {
    /* 
    Size based on what stage the sat is currently in. It would adapt to what size is expected from the sender.
    There would be different read packetRead functions based on line, and on stage. Launch a packetRead depending on
    What is exepected.
    */
    struct buffer * buf = requestBuffer(30); 
    read(0, (void *)buf->data);

    return 1;
}