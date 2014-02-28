#ifndef _AVREL_RAM_H
#define _AVREL_RAM_H

#include <string>

namespace avrel
{
    class RAM
    {
        public:
            RAM(int size);
            uint16_t readWord(int position);
            uint8_t readChar(int position);

        protected:
            int size;
            std::string data;
    };
}

#endif
