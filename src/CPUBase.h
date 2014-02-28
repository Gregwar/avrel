#ifndef _AVREL_CPU_BASE_H
#define _AVREL_CPU_BASE_H

#include "ROM.h"

namespace avrel
{
    class CPUBase
    {
        public:
            CPUBase(ROM &rom, int frequency);

            // CPUBase reset
            void reset();

            // Write a value to a register
            void writeRegister(int reg, int value);
            void setSreg(int value);
            int getSreg();

            // X, Y & Z
            void setX(int value);
            void setY(int value);
            void setZ(int value);
            int getX();
            int getY();
            int getZ();
            
            // Opcodes
            void jmp(int addr);
            void eor(int r, int d);
            void out(int r, int A);
            void ldi(int d, int K);

        protected:
            ROM &rom;
            int frequency;
            int cycles;

            // Registers
            uint16_t R[32];

            // Stack pointer;
            uint16_t SP;

            // S_reg bits
            bool I,T,H,S,V,N,Z,C;
    };
}

#endif
