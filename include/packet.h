

int packetRead_BUSNAME_(void);

int packetWrite_BUSNAME_(void *);

struct packetHeader {
    unsigned char priSourcePort; //left most two bits is priority, right most 6 bits is source port
    unsigned char destPortReserved; //left most 6 bits is dest port, right most 2 bits are reserved
    unsigned char reservedFlags; //left most 4 bits are reserved, right most 4 are for flags (checksum, which protocol, encyprtion, etc.)
};
