/* Main file, used for debugging and testing implementation */




#include "../include/PSP.h"


int main() {
    //fprintf(stderr, "Size of buffer: %lu\n", STRUCTBUFFERSIZE);
    initializeBuffers();


#if BUFFERINITDEBUG
    // Buffer check - WORKS
    printMultiLevelStack();
#endif

#if BUFFERREQUESTDEBUG
    //Requested size is good - WORKS
    fprintf(stderr, "Size of  46 request buffer is: %d\n", requestBuffer(46)->size);
    fprintf(stderr, "Size of  26 request buffer is: %d\n", requestBuffer(26)->size);
    fprintf(stderr, "Size of  15 request buffer is: %d\n", requestBuffer(15)->size);

    // Ensuring buffers are removed - WORKS
    printMultiLevelStack();

#endif

#if BUFFERINPUTDEBUG
    //Created buffers and seeing if they input successfully - WORKS
    struct buffer *check1 = (struct buffer *)malloc(STRUCTBUFFERSIZE + SMALLMAXSIZEBUFFER);
    check1->size = 40;

    struct buffer *check2 = (struct buffer *)malloc(STRUCTBUFFERSIZE + SMALLMAXSIZEBUFFER);
    check2->size = 35;

    struct buffer *check3 = (struct buffer *)malloc(STRUCTBUFFERSIZE + SMALLMAXSIZEBUFFER);
    check3->size = 15;

    fprintf(stderr, "Inser Check: %d, %d, %d\n", inputBuffer(check1), inputBuffer(check2), inputBuffer(check3));

    // Ensuring buffers are added - WORKS
    printMultiLevelStack();

#endif

#if PACKETREADDEBUG
    struct buffer * buf = packetRead_BUSNAME_();
    fprintf(stderr, "Successful Packet Read: %s\n", buf->data);
    fprintf(stderr, "Header of packet read: \n%u\n%u\n%u\n", buf->header.priSourcePort, buf->header.destPortReserved, buf->header.reservedFlags);

    //Extract last 2 bits to obtain the priority field value (would be done in transport layer code)
    unsigned char prioMask = 0xC0;
    unsigned char priority = buf->header.priSourcePort & prioMask;
    priority = priority>>6;
    fprintf(stderr, "Extracted priority field: %u\n", priority);

#endif

#if PACKETWRITEDEBUG
    struct buffer * buf = packetRead_BUSNAME_();
    packetWrite_BUSNAME_(buf);
    memcpy(buf->data, "DATA", strlen("DATA"));
    packetWrite_BUSNAME_(buf);
#endif


    return 1;
}