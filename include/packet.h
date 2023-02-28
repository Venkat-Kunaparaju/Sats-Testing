

int packetRead_BUSNAME_(void);

int packetWrite_BUSNAME_(void *);

struct packetHeader {
    unsigned char priSourcePort; //First two bits is priority, Last 6 bits is source port
    unsigned char destPortReserved; //First 6 bits is dest port, last 2 bits are reserved
    unsigned char reservedFlags; //First 4 bits are reserved, last 4 are for flags (checksum, which protocol, encyprtion, etc.)
};
