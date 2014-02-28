#include <iostream>
#include "timing/Chrono.h"
#include "timing/sleep.h"
#include "CPU.h"
#include "opcode.h"
#include "util.h"

namespace avrel
{
    CPU::CPU(ROM &rom_, RAM &ram_, int frequency_)
        : CPUBase(rom_, ram_, frequency_)
    {
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
            if (toDo < 10000) {
                ms_sleep(1);
            }
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
            cycles+=3;

        } else if (MATCH(1,0,0,1, 0,1,0,X, X,X,X,X, 1,1,1,X)) {
            // call
            int addr = EXTRACT(7, 5)<<17;
            addr |= EXTRACT_BITS(opcode, 15, 1)<<16;
            addr |= rom.readWord();
            addr *= 2;
            call(addr);
            cycles+=4;
        
        } else if (MATCH(1,0,0,1, 0,0,1,X, X,X,X,X, 0,0,0,0)) {
            // sts
            int d = EXTRACT(7, 5);
            int addr = rom.readWord();
            sts(d, addr);
            cycles+=1;
        
        } else if (MATCH(0,0,1,0, 0,1,X,X, X,X,X,X, X,X,X,X)) {
            // eor
            int d = EXTRACT(7, 5);
            int r = (EXTRACT(6, 1)<<4) | EXTRACT(12, 4);
            eor(r, d);
            cycles++;

        } else if (MATCH(1,0,1,1, 1,X,X,X, X,X,X,X, X,X,X,X)) {
            // out
            int r = EXTRACT(7, 5);
            int A = (EXTRACT(5, 2)<<4) | EXTRACT(12, 4);
            out(r, A);
            cycles++;

        } else if (MATCH(1,0,1,1, 0,X,X,X, X,X,X,X, X,X,X,X)) {
            // in
            int r = EXTRACT(7, 5);
            int A = (EXTRACT(5, 2)<<4) | EXTRACT(12, 4);
            in(r, A);
            cycles++;

        } else if (MATCH(1,1,1,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // ldi
            int d = EXTRACT(8, 4) + 16;
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12, 4);
            ldi(d, K);
            cycles++;

        } else if (MATCH(1,0,0,1, 0,1,0,0, 1,1,1,1, 1,0,0,0)) {
            // cli
            cli();
            cycles++;

        } else if (MATCH(1,0,0,1, 0,1,0,0, 0,1,1,1, 1,0,0,0)) {
            // sei
            sei();
            cycles++;

        } else if (MATCH(1,0,0,1, 1,0,0,0, X,X,X,X, X,X,X,X)) {
            // cbi
            int A = EXTRACT(8, 5);
            int b = EXTRACT(13, 3);
            cbi(A, b);
            cycles+=2;

        } else if (MATCH(1,0,0,1, 1,0,1,0, X,X,X,X, X,X,X,X)) {
            // sbi
            int A = EXTRACT(8, 5);
            int b = EXTRACT(13, 3);
            sbi(A, b);
            cycles+=2;

        } else if (MATCH(0,1,0,1, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // subi
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12,4);
            int d = 16+EXTRACT(8, 4);
            subi(d, K);
            cycles++;

        } else if (MATCH(0,1,0,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // sbci
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12,4);
            int d = 16+EXTRACT(8, 4);
            sbci(d, K);
            cycles++;

        } else if (MATCH(1,1,1,1, 0,1,X,X, X,X,X,X, X,0,0,1)) {
            // brne
            int k = VALUE_SIGN(EXTRACT(6, 7), 7);
            k *= 2;
            cycles += brne(k) ? 2 : 1;

        } else if (MATCH(1,1,0,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            int k = VALUE_SIGN(EXTRACT(4, 12), 12);
            k *= 2;
            rjmp(k);
            cycles+=2;

        } else if (MATCH(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0)) {
            // nop
            nop();
            cycles++;

        } else if (MATCH(0,0,1,1, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // cpi
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12, 4);
            int d = EXTRACT(8, 4) + 16;
            cpi(d, K);
            cycles++;

        } else if (MATCH(0,0,0,0, 0,1,X,X, X,X,X,X, X,X,X,X)) {
            // cpc
            int d = EXTRACT(7, 5);
            int r = (EXTRACT(6, 1)<<4) | EXTRACT(12, 4);
            cpc(d, r);
            cycles++;

        } else {
            printf("Unknown opcode: %04x\n", opcode);
            printf("Aborting.\n");
            exit(0);
        }    
    }
}
