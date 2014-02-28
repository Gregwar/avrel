#ifndef _AVREL_CPU_BASE_H
#define _AVREL_CPU_BASE_H

#include "ROM.h"
#include "RAM.h"

namespace avrel
{
    class CPUBase
    {
        public:
            CPUBase(ROM &rom, RAM &ram, int frequency);

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

            // Utils
            void pushByte(int byte);
            void pushWord(int value);
            
            // Opcodes
            void jmp(int addr);
            void call(int addr);
            void eor(int r, int d);
            void out(int r, int A);
            void ldi(int d, int K);

        protected:
            ROM &rom;
            RAM &ram;
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
