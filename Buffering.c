/* Code to test temporarily buffering input data */

/*
Instead of having a multiLevelStack operating on fixed sizes 
(which means that the design won't be modular) because changes
would need to be made to all 3 general functions outlined

*/

#include "PSP.h"

/* Specifies the number of buffers for a specifc size and the size of data the buffer will hold */
#define BIGNUMBUFFERS 5
#define BIGMAXSIZEBUFFER 50

#define MEDNUMBUFFERS 7
#define MEDMAXSIZEBUFFER 35

#define SMALLNUMBUFFERS 10
#define SMALLMAXSIZEBUFFER 20


/* Debugging */
#define BUFFERINITDEBUG 0
#define BUFFERREQUESTDEBUG 0
#define BUFFERINPUTDEBUG 0

/* Buffer to store data */
struct buffer {
    struct segment header; //Store header of buffer
    struct buffer * next; //Store next available buffer
    int size;
    char data[0]; //Store data
};

#define STRUCTBUFFERSIZE sizeof(struct buffer)

/* Sentinel used for storing head of buffer blocks */
struct sentinel {
    void *next;
};

/* Stores a different size buffers at each index in decreasing order (0 stores highest) */
struct sentinel multiLevelStack[3]; 

/* Initialize buffers, both big and small */
int initializeBuffers() {
    struct buffer *new;
    struct buffer *old;

    /* Allocate big sized buffers */
    for (int i = 0; i < BIGNUMBUFFERS; i++) {
        new = (struct buffer *)malloc(STRUCTBUFFERSIZE + BIGMAXSIZEBUFFER);
        new->size = BIGMAXSIZEBUFFER;
        if (i == 0) {
            multiLevelStack[0].next = new;
        } else {
            old->next = new;
        }
        old = new;
    }
    /* Allocate medium sized buffers */
    for (int i = 0; i < MEDNUMBUFFERS; i++) {
        new = (struct buffer *)malloc(STRUCTBUFFERSIZE + MEDMAXSIZEBUFFER);
        new->size = MEDMAXSIZEBUFFER;
        if (i == 0) {
            multiLevelStack[1].next = new; //Changed per for loop
        } else {
            old->next = new;
        }
        old = new;
    }
    /* Allocate small sized buffers */
    for (int i = 0; i < SMALLNUMBUFFERS; i++) {
        new = (struct buffer *)malloc(STRUCTBUFFERSIZE + SMALLMAXSIZEBUFFER);
        new->size = SMALLMAXSIZEBUFFER;
        if (i == 0) {
            multiLevelStack[2].next = new; //Changed per for loop
        } else {
            old->next = new;
        }
        old = new;
    }

    return 1;
}

/* Debugging function to print multiLevelStack */
void printMultiLevelStack() {
    int i = 0;
    struct buffer * head = multiLevelStack[0].next;
    while (head != NULL) {
        i ++;
        head = head->next;
    }
    fprintf(stderr, "Number of big buffers is: %d\n", i);

    i = 0;
    head = multiLevelStack[1].next;
    while (head != NULL) {
        i ++;
        head = head->next;
    }
    fprintf(stderr, "Number of med buffers is: %d\n", i);

    i = 0;
    head = multiLevelStack[2].next;
    while (head != NULL) {
        i ++;
        head = head->next;
    }
    fprintf(stderr, "Number of small buffers is: %d\n", i);
}

/* Remove and return buffer based on size */
struct buffer * requestBuffer(int size) {
    struct buffer * output;
    if (size <= SMALLMAXSIZEBUFFER) {
        output = multiLevelStack[2].next;
        multiLevelStack[2].next = output->next;
    }
    else if (size <= MEDMAXSIZEBUFFER) {
        output = multiLevelStack[1].next;
        multiLevelStack[1].next = output->next;
    }
    else if (size <= BIGMAXSIZEBUFFER) {
        output = multiLevelStack[0].next;
        multiLevelStack[0].next = output->next;
    } 
    else {
        return NULL;
    }
    output->next = NULL;
    return output;
}

int inputBuffer(struct buffer *input) {
    if (input->size <= SMALLMAXSIZEBUFFER) {
        input->next = multiLevelStack[2].next;
        multiLevelStack[2].next = input;
    }
    else if (input->size <= MEDMAXSIZEBUFFER) {
        input->next = multiLevelStack[1].next;
        multiLevelStack[1].next = input;
    }
    else if (input->size <= BIGMAXSIZEBUFFER) {
        input->next = multiLevelStack[0].next;
        multiLevelStack[0].next = input;
    } 
    else {
        return -1;
    }
    return 1;
}

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
    check2->size = 32;

    struct buffer *check3 = (struct buffer *)malloc(STRUCTBUFFERSIZE + SMALLMAXSIZEBUFFER);
    check3->size = 15;

    fprintf(stderr, "Inser Check: %d, %d, %d", inputBuffer(check1), inputBuffer(check2), inputBuffer(check3));

    // Ensuring buffers are added - WORKS
    printMultiLevelStack();

#endif


    return 1;
}