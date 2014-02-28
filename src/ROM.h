#ifndef _AVREL_ROM_H
#define _AVREL_ROM_H

#include <stdint.h>
#include <string>

namespace avrel
{
    class ROM
    {
        public:
            ROM(std::string file);

            // Read an unsigned short
            uint16_t readWord();

            // Read chars
            uint8_t readChar();

            // Jump cursor to position
            void jumpTo(int position);

            int getPosition();

        protected:
            int size;
            int position;
            std::string data;
    };
}

#endif
