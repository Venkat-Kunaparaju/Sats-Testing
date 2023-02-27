

struct buffer * packetRead_BUSNAME_(void);

int packetWrite_BUSNAME_(struct buffer *);

struct segment{
    unsigned char priSourcePort;
    unsigned char destPortFlags;
};
