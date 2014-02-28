#ifndef _AVREL_RAM_H
#define _AVREL_RAM_H

#include <stdint.h>
#include <string>

namespace avrel
{
    class RAM
    {
        public:
            RAM(unsigned int size);

            uint16_t readWord(unsigned int position);
            uint8_t readByte(unsigned int position);
            
            void writeByte(unsigned int position, uint8_t value);
            void writeWord(unsigned int position, uint16_t value);

        protected:
            unsigned int size;
            std::string data;
    };
}

#endif
