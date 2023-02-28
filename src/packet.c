/* Code to test turning data into packet from input data */

#include "../include/PSP.h"

/*
Read packets from bus, and forward to transport layer
*/
int packetRead_BUSNAME_() {
    /* 
    Size based on what stage the sat is currently in. It would adapt to what size is expected from the sender.
    There would be different read packetRead functions based on what line. Size and priority of packet will depend on
    stage, and this can be accomplished with a simple if statement in this function.
    */
    while(1) {
        struct buffer * buf = requestBuffer(30); 
        read(0, (void *)buf->data); //Blocks on bus

        /* Assignment of priority and initalization of other header information done here */
        /* If this is coming from a NON cots component we would have to read buf->data to determine header info */

        //Set priority to 3 (11xxxxxx)
        buf->header.priSourcePort |= 0xF0; //Set last 4 bits to 1
        buf->header.priSourcePort ^= 0x30; //XOR operator unsent the first 2 of the flast 4 bits

        //Set source port to 59 (xx111011)
        buf->header.priSourcePort |= 0x3F; //Set the first 2 of the last 4 bits to 1, and set the the first 4 bits to 1
        buf->header.priSourcePort ^= 0x04; //XOR operator to set that middle bit to 0 

        //Set dest port to 28 (011100xx)
        buf->header.destPortReserved |= 0xFC; //Set last 6 bits to be 1
        buf->header.destPortReserved ^= 0x0C; //XOR operator to set last 2 of first 4 bits to 0
        buf->header.destPortReserved ^= 0x80; //XOR operator to unsent last bit

        //Set flags to be (1101)
        buf->header.reservedFlags |= 0x0D; 


        /* Forwarding to transport code done here. Add to end of queue*/
        if (transportQ.prev == NULL) {
            buf->prev = NULL;
        } else {
            buf->prev = transportQ.prev;
            buf->prev->next = buf;
        }
        transportQ.prev = buf;
        if (transportQ.next == NULL) {
            transportQ.next = buf;
        }
        
        break; //Take out this break
        
    }
    /* What should happen is that it adds to a queue that the transport layer then reads from when it runs
    rather than doing it one at a time to deal with "burts". This function then runs in a while loop forever unless blocked. */
    return 1;
}

/*
Write packets to bus, that came from transport layer (due to error or application sending data)
*/
int packetWrite_BUSNAME_(void * b) {
    struct buffer * buf = b;
    write(0, (void *)buf->data, buf->size);
    return 1;
}
