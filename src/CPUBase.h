#ifndef _AVREL_CPU_BASE_H
#define _AVREL_CPU_BASE_H

#include "ROM.h"
#include "RAM.h"
#include "registers.h"

namespace avrel
{
    class CPUBase
    {
        public:
            CPUBase(ROM &rom, RAM &ram, int frequency);

            // CPUBase reset
            void reset();

            // Write a value to a register
            void writeData(unsigned int reg, int value);
            int readData(unsigned int reg);
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
            void setFlags(int A, int B, int R);
            
            // Opcodes
            void jmp(int addr);
            void call(int addr);
            void sts(int r, int A);
            void eor(int r, int d);
            void out(int r, int A);
            void in(int r, int A);
            void ldi(int d, int K);
            void cli();
            void sei();
            void sbi(int A, int b);
            void cbi(int A, int b);
            void subi(int d, int K);
            void sbci(int d, int K);
            bool brne(int k);
            void nop();
            void rjmp(int k);
            void cpi(int d, int K);

        protected:
            ROM &rom;
            RAM &ram;
            int frequency;
            int cycles;

            // Registers
            uint8_t R[32];
            uint8_t registers[REGISTERS_SIZE];

            // Stack pointer;
            uint16_t SP;

            // S_reg bits
            bool I,T,H,S,V,N,Z,C;
    };
}

#endif
