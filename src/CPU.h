#ifndef _AVREL_CPU_H
#define _AVREL_CPU_H

#include <functional>
#include "CPUBase.h"

namespace avrel
{
    class CPU : public CPUBase
    {
        public:
            CPU(ROM &rom, RAM &ram, int frequency);
            
            void cache();

            // Schedule the CPU
            void run();
            
            // Process the next opcode
            std::function<void ()> processOpcode();

        protected:
            std::function<void ()> *operations;
    };
}

#endif
