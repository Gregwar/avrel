#ifndef _AVREL_OPCODE_H
#define _AVREL_OPCODE_H

// Disable opcode debugging
// #define OPCODE_DEBUG(...) 

// Enable opcode debugging
#define OPCODE_DEBUG(...) printf(__VA_ARGS__)

// Checks that an opcode match the given pattern
#define OPCODE_MATCH(opcode, b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15) \
    ((b0==-1) || (((opcode>>15)&0x1)==b0)) && \
    ((b1==-1) || (((opcode>>14)&0x1)==b1)) && \
    ((b2==-1) || (((opcode>>13)&0x1)==b2)) && \
    ((b3==-1) || (((opcode>>12)&0x1)==b3)) && \
    ((b4==-1) || (((opcode>>11)&0x1)==b4)) && \
    ((b5==-1) || (((opcode>>10)&0x1)==b5)) && \
    ((b6==-1) || (((opcode>>9)&0x1)==b6)) && \
    ((b7==-1) || (((opcode>>8)&0x1)==b7)) && \
    ((b8==-1) || (((opcode>>7)&0x1)==b8)) && \
    ((b9==-1) || (((opcode>>6)&0x1)==b9)) && \
    ((b10==-1) || (((opcode>>5)&0x1)==b10)) && \
    ((b11==-1) || (((opcode>>4)&0x1)==b11)) && \
    ((b12==-1) || (((opcode>>3)&0x1)==b12)) && \
    ((b13==-1) || (((opcode>>2)&0x1)==b13)) && \
    ((b14==-1) || (((opcode>>1)&0x1)==b14)) && \
    ((b15==-1) || (((opcode>>0)&0x1)==b15))

// Extract the bits from nth with length l
#define EXTRACT_BITS(opcode, from, length) \
        ((opcode>>(16-from-length))&((1<<length)-1))

#endif
