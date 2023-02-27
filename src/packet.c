/* Code to test turning data into packet from input data */

#include "../include/PSP.h"

struct buffer * packetRead_BUSNAME_() {
    /* 
    Size based on what stage the sat is currently in. It would adapt to what size is expected from the sender.
    There would be different read packetRead functions based on what line. Size and priority of packet will depend on
    stage, and this can be accomplished with a simple if statement in this function.
    */
    struct buffer * buf = requestBuffer(30); 
    read(0, (void *)buf->data);

    /* Assignment of priority and initalization of other header information done here */

    return buf;
}