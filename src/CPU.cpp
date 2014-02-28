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

        if (OPCODE_MATCH(opcode, 1,0,0,1, 0,1,0,X, X,X,X,X, 1,1,0,X)) {
            // jmp
            int addr = EXTRACT_BITS(opcode, 7, 5)<<17;
            addr |= EXTRACT_BITS(opcode, 15, 1)<<16;
            addr |= rom.readWord();
            addr *= 2;
            jmp(addr);
        
        } else if (OPCODE_MATCH(opcode, 0,0,1,0, 0,1,X,X, X,X,X,X, X,X,X,X)) {
            // eor
            int d = EXTRACT_BITS(opcode, 7, 5);
            int r = (EXTRACT_BITS(opcode, 6, 1)<<5) | EXTRACT_BITS(opcode, 12, 4);
            eor(r, d);
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
        OPCODE_DEBUG("eor r%d,r%d\n", r, d);
        R[d] = R[r] ^ R[d];
        V = 0;
        N = (R[d]>>7)&1;
        S = V^N;
        Z = (R[d] == 0);
    }
}
