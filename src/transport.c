/* Code to test transporting, error handling, etc. */

#include "../include/PSP.h"

/* Masks for getting data */
unsigned char prioMask = 0xC0;
unsigned char srcPortMask = 0x3F;
unsigned char destPortMask = 0xFC;
unsigned char flagsMask = 0x0F;

//Get next buffer in queue to handle
struct buffer * dequeTransportQ() {
    struct buffer * output = transportQ.next;
    transportQ.next = output->next;
    return output;
}

//Insert before head
int insertInQ(struct buffer * head, struct buffer * buf, int port) {
    buf->prev = head->prev;
    if (head->prev != NULL) {
        head->prev->next = buf;
    } else {
        portQ[port].next = buf;
    }
    buf->next = head;
    head->prev = buf;
    return 1;
}

int transportInit() {
    transportQ.prev = NULL;
    transportQ.next = NULL;
    return 1;
}

//Debugging function for printing messages in each port
void printPortQs() {
    for (int i = 0; i < 64; i++) {
        struct buffer *head = portQ[i].next;
        int c = 0;
        while (head != NULL) {
            c++;
            head = head->next;
        } 
        fprintf(stderr, "Number of buffers at port %d is: %d\n", i, c);
    }
}

int transportMain() {
    while(1) {
        while (transportQ.next != NULL) { //While there is something in the Q, then do something (Block on transportQ)
            struct buffer * buf = dequeTransportQ();
            fprintf(stderr, "Do something\n"); //Do error checking packet

            /* Forward packet to correct Q based on dest port and put it in right index (sorted descending by priority)*/
            unsigned char srcPort = buf->header.priSourcePort & srcPortMask;
            unsigned char prio = buf->header.priSourcePort & prioMask;
            prio = prio>>6;
            struct buffer * head = portQ[srcPort].next;
            while (head != NULL) {
                
                unsigned char prio2 = head->header.priSourcePort & prioMask;
                prio2 = prio2>>6;
                if (prio >= prio2) {
                    insertInQ(head, buf, srcPort);
                    break;
                }
                if (head->next == NULL) {
                    buf->prev = head;
                    head->next = buf;
                }
                head = head->next;
            }
            if (head == NULL) {
                buf->next = NULL;
                buf->prev = NULL;
                portQ[srcPort].next = buf;
            }

        }
        break; //Remove break
    }
    return 1;
}

