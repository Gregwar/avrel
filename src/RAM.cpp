#include "RAM.h"

namespace avrel
{
    RAM::RAM(unsigned int size_)
        : size(size_)
    {
        data.resize(size);
    }
    
    uint16_t RAM::readWord(unsigned int position)
    {
        return (readByte(position))|(readByte(position+1)<<8);
    }

    uint8_t RAM::readByte(unsigned int position)
    {
        if (position < size) {
            return data[position];
        } else {
            return 0x00;
        }
    }

    void RAM::writeByte(unsigned int position, uint8_t value)
    {
        if (position < size) {
            data[position] = value;
        }
    }

    void RAM::writeWord(unsigned int position, uint16_t value)
    {
        writeByte(position, value&0xff);
        writeByte(position+1, (value>>8)&0xff);
    }
}
