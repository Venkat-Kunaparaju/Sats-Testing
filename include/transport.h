
#define NUMPORTS 64

struct sentinel transportQ; //Q for messages that transport layer handles

struct sentinel portQ[NUMPORTS]; //Q for messages for each port (application binds to port) ordered by priority

struct buffer * dequeTransportQ(void);

int insertInQ(struct buffer *, struct buffer *, int);

int transportInit(void);

void printPortQs(void);

int transportMain(void);