/* Code to test temporarily buffering input data */

#include "PSP.h"

#define BIGNUMBUFFERS 5
#define BIGMAXSIZEBUFFER 50

#define SMALLNUMBUFFERS 10
#define SMALLMAXSIZEBUFFER 20

#define BUFFERINITDEBUG 0

struct bigBuffer {
    struct segment header; //Store header of buffer
    char data[BIGMAXSIZEBUFFER]; //Store data to be forwarded
    struct bigBuffer * next; //Store next available buffer
};

struct smallBuffer {
    struct segment header;
    char data[SMALLMAXSIZEBUFFER];
    struct smallBuffer * next; 
};

struct sentinel {
    void *next;
};

struct sentinel bigBufferHead;
struct sentinel smallBufferHead;

int initializeBuffers() {
    struct bigBuffer *new;
    struct bigBuffer *old;
    for (int i = 0; i < BIGNUMBUFFERS; i++) {
        new = (struct bigBuffer *)malloc(sizeof(struct bigBuffer));
        if (i == 0) {
            bigBufferHead.next = new;
        } else {
            old->next = new;
        }
        old = new;
    }

    struct smallBuffer *new2;
    struct smallBuffer *old2;
    for (int i = 0; i < SMALLNUMBUFFERS; i++) {
        new2 = (struct smallBuffer *)malloc(sizeof(struct smallBuffer));
        if (i == 0) {
            smallBufferHead.next = new2;
        } else {
            old2->next = new2;
        }
        old2 = new2;
    }
    return 1;
}

int removeBuffer() {
    if 
    return 1;
}

int main() {
    //fprintf(stderr, "Size of buffer: %lu\n", sizeof(struct buffer));
    initializeBuffers();

#if BUFFERINITDEBUG
    // Buffer check - WORKS
    int i = 0;
    struct bigBuffer * head = bigBufferHead.next;
    while (head != NULL) {
        i ++;
        head = head->next;
    }
    fprintf(stderr, "Number of big Buffers is: %d\n", i);

    i = 0;
    struct smallBuffer * head2 = smallBufferHead.next;
    while (head2 != NULL) {
        i ++;
        head2 = head2->next;
    }
    fprintf(stderr, "Number of small Buffers is: %d\n", i);
#endif





    return 1;
}