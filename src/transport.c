/* Code to test transporting, error handling, etc. */

#include "../include/PSP.h"

struct buffer * dequeTransportQ() {
    struct buffer * output = transportQ.next;
    transportQ.next = output->next;
    return output;
}

int transportInit() {
    transportQ.prev = NULL;
    transportQ.next = NULL;
    return 1;
}
int transportMain() {
    while(1) {
        while (transportQ.next != NULL) { //While there is something in the Q, then do something
            dequeTransportQ();
            fprintf(stderr, "Do something\n"); //Do error checking packet and forwarding then move on to next one
        }
        break; //Remove break
    }
    return 1;
}

