/* Code to test turning data into packet from input data */

#include "../include/PSP.h"


/*
Read packets from bus, and forward to transport layer
*/
struct buffer * packetRead_BUSNAME_() {
    /* 
    Size based on what stage the sat is currently in. It would adapt to what size is expected from the sender.
    There would be different read packetRead functions based on what line. Size and priority of packet will depend on
    stage, and this can be accomplished with a simple if statement in this function.
    */
    struct buffer * buf = requestBuffer(30); 
    read(0, (void *)buf->data); //Blocks on bus

    /* Assignment of priority and initalization of other header information done here */

    /* Forwarding to transport code done here */

    return buf;
}


/*
Write packets to bus, that came from transport layer (due to error or application sending data)
*/
int packetWrite_BUSNAME_(struct buffer * buf) {
    write(0, (void *)buf->data, buf->size);
    return 1;
}
