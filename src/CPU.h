#ifndef _AVREL_CPU_H
#define _AVREL_CPU_H

#include "CPUBase.h"
#include "ROM.h"

namespace avrel
{
    class CPU : public CPUBase
    {
        public:
            CPU(ROM &rom, int frequency);

            // Schedule the CPU
            void run();
            
            // Process the next opcode
            void processOpcode();
            
    };
}

#endif
