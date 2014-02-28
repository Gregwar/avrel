#ifndef _AVREL_CPU_H
#define _AVREL_CPU_H

#include "ROM.h"

namespace avrel
{
    class CPU
    {
        public:
            CPU(ROM &rom, int frequency);

            // CPU reset
            void reset();

            // Schedule the CPU
            void run();
            
            // Process the next opcode
            void processOpcode();
            
            // Opcodes
            void jmp(int addr);
            void eor(int r, int d);

        protected:
            ROM &rom;
            int frequency;
            int cycles;

            // Registers
            uint16_t R[32];

            // S_reg bits
            bool I,T,H,S,V,N,Z,C;
    };
}

#endif
