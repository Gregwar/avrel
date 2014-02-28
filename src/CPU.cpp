#include <iostream>
#include "timing/Chrono.h"
#include "CPU.h"
#include "opcode.h"

namespace avrel
{
    CPU::CPU(ROM &rom_, int frequency_)
        : rom(rom_), frequency(frequency_), cycles(0)
    {
        reset();
    }

    void CPU::reset()
    {
        rom.jumpTo(0);
    }

    void CPU::run()
    {
        Chrono chrono;
        double last = 0;

        while (true) {
            double time = chrono.getTime();
            double delta = time-last;
            int toDo = delta*frequency;
            last = time;

            while (cycles < toDo) {
                processOpcode();
            }

            cycles -= toDo;
        }
    }

    void CPU::processOpcode()
    {
        const int opcode = rom.readWord();
        int X = -1;

#define EXTRACT(a, b) EXTRACT_BITS(opcode, a, b)
#define MATCH(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15) \
        OPCODE_MATCH(opcode,b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15)

        if (MATCH(1,0,0,1, 0,1,0,X, X,X,X,X, 1,1,0,X)) {
            // jmp
            int addr = EXTRACT(7, 5)<<17;
            addr |= EXTRACT_BITS(opcode, 15, 1)<<16;
            addr |= rom.readWord();
            addr *= 2;
            jmp(addr);
        
        } else if (MATCH(0,0,1,0, 0,1,X,X, X,X,X,X, X,X,X,X)) {
            // eor
            int d = EXTRACT(7, 5);
            int r = (EXTRACT(6, 1)<<4) | EXTRACT(12, 4);
            eor(r, d);

        } else if (MATCH(1,0,1,1, 1,X,X,X, X,X,X,X, X,X,X,X)) {
            // out
            int r = EXTRACT(7, 5);
            int A = (EXTRACT(5, 2)<<4) | EXTRACT(12, 4);
            out(r, A);

        } else if (MATCH(1,1,1,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // ldi
            int d = EXTRACT(8, 4) + 16;
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12, 4);
            ldi(d, K);

        } else {
            printf("Unknown opcode: %04x\n", opcode);
            printf("Aborting.\n");
            exit(0);
        }
        
        cycles++;
    }

    void CPU::jmp(int addr)
    {
        OPCODE_DEBUG("jmp %x\n", addr);
        rom.jumpTo(addr);
    }

    void CPU::eor(int r, int d)
    {
        OPCODE_DEBUG("eor r%d, r%d\n", r, d);
        R[d] = R[r] ^ R[d];
        V = 0;
        N = (R[d]>>7)&1;
        S = V^N;
        Z = (R[d] == 0);
    }

    void CPU::out(int r, int A)
    {
        OPCODE_DEBUG("out r%d, %x\n", r, A);
    }

    void CPU::ldi(int d, int K)
    {
        OPCODE_DEBUG("ldi r%d, %x\n", d, K);
    }
}
