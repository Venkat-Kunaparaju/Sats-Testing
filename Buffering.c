/* Code to test temporarily buffering input data */

#include "PSP.h"

#define BIGNUMBUFFERS 5
#define BIGMAXSIZEBUFFER 50

#define SMALLNUMBUFFERS 10
#define SMALLMAXSIZEBUFFER 20

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
    struct 

};

int initializeBuffers() {
    for (int i = 0; i < BIGNUMBUFFERS; i++) {
        
    }
}

int main() {
    //fprintf(stderr, "Size of buffer: %lu\n", sizeof(struct buffer));


    return 1;
}