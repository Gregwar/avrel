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
        operations = new std::function<void ()>[rom.getSize()];
        cache();
    }

    void CPU::cache()
    {
        rom.jumpTo(0);
        for (int i=0; i<rom.getSize()/2; i++) {
            operations[i] = processOpcode();
        }
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
                int i = PC;
                PC+=2;
                operations[i/2]();
            }

            cycles -= toDo;
            if (toDo < 10000) {
                ms_sleep(3);
            }
        }
    }

    std::function<void ()> CPU::processOpcode()
    {
        const int opcode = rom.readWord();

#define X -1
#define EXTRACT(a, b) EXTRACT_BITS(opcode, a, b)
#define MATCH(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15) \
        OPCODE_MATCH(opcode,b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15)

        if (MATCH(1,0,0,1, 0,1,0,X, X,X,X,X, 1,1,0,X)) {
            // jmp
            int addr = EXTRACT(7, 5)<<17;
            addr |= EXTRACT(15, 1)<<16;
            addr |= rom.readWord();
            addr *= 2;

            return [this,addr]() {
                this->jmp(addr);
                this->cycles+=3;
            };

        } else if (MATCH(1,0,0,1, 0,1,0,X, X,X,X,X, 1,1,1,X)) {
            // call
            int addr = EXTRACT(7, 5)<<17;
            addr |= EXTRACT(15, 1)<<16;
            addr |= rom.readWord();
            addr *= 2;

            return [this,addr]() {
                this->call(addr);
                this->cycles+=4;
            };
        
        } else if (MATCH(1,0,0,1, 0,0,1,X, X,X,X,X, 0,0,0,0)) {
            // sts
            int d = EXTRACT(7, 5);
            int addr = rom.readWord();

            return [this,d,addr]() {
                this->sts(d, addr);
                this->cycles+=1;
            };
        
        } else if (MATCH(0,0,1,0, 0,1,X,X, X,X,X,X, X,X,X,X)) {
            // eor
            int d = EXTRACT(7, 5);
            int r = (EXTRACT(6, 1)<<4) | EXTRACT(12, 4);

            return [this,r,d]() {
                this->eor(r, d);
                this->cycles++;
            };

        } else if (MATCH(1,0,1,1, 1,X,X,X, X,X,X,X, X,X,X,X)) {
            // out
            int r = EXTRACT(7, 5);
            int A = (EXTRACT(5, 2)<<4) | EXTRACT(12, 4);

            return [this,r,A]() {
                this->out(r, A);
                this->cycles++;
            };

        } else if (MATCH(1,0,1,1, 0,X,X,X, X,X,X,X, X,X,X,X)) {
            // in
            int r = EXTRACT(7, 5);
            int A = (EXTRACT(5, 2)<<4) | EXTRACT(12, 4);

            return [this,r,A]() {
                this->in(r, A);
                this->cycles++;
            };

        } else if (MATCH(1,1,1,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // ldi
            int d = EXTRACT(8, 4) + 16;
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12, 4);
            
            return [this,d,K]() {
                this->ldi(d, K);
                this->cycles++;
            };

        } else if (MATCH(1,0,0,1, 0,1,0,0, 1,1,1,1, 1,0,0,0)) {
            // cli
            
            return [this]() {
                cli();
                cycles++;
            };

        } else if (MATCH(1,0,0,1, 0,1,0,0, 0,1,1,1, 1,0,0,0)) {
            // sei

            return [this]() {
                sei();
                cycles++;
            };

        } else if (MATCH(1,0,0,1, 1,0,0,0, X,X,X,X, X,X,X,X)) {
            // cbi
            int A = EXTRACT(8, 5);
            int b = EXTRACT(13, 3);

            return [this,A,b]() {
                this->cbi(A, b);
                this->cycles+=2;
            };

        } else if (MATCH(1,0,0,1, 1,0,1,0, X,X,X,X, X,X,X,X)) {
            // sbi
            int A = EXTRACT(8, 5);
            int b = EXTRACT(13, 3);

            return [this,A,b]() {
                this->sbi(A, b);
                this->cycles+=2;
            };

        } else if (MATCH(0,1,0,1, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // subi
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12,4);
            int d = 16+EXTRACT(8, 4);

            return [this,d,K]() {
                this->subi(d, K);
                this->cycles++;
            };

        } else if (MATCH(0,1,0,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // sbci
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12,4);
            int d = 16+EXTRACT(8, 4);

            return [this,d,K]() {
                this->sbci(d, K);
                this->cycles++;
            };

        } else if (MATCH(1,1,1,1, 0,1,X,X, X,X,X,X, X,0,0,1)) {
            // brne
            int k = VALUE_SIGN(EXTRACT(6, 7), 7);
            k *= 2;

            return [this,k]() {
                this->cycles += this->brne(k) ? 2 : 1;
            };

        } else if (MATCH(1,1,0,0, X,X,X,X, X,X,X,X, X,X,X,X)) {
            int k = VALUE_SIGN(EXTRACT(4, 12), 12);
            k *= 2;
            
            return [this,k]() {
                this->rjmp(k);
                this->cycles+=2;
            };

        } else if (MATCH(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0)) {
            // nop
            return [this]() {
                this->nop();
                this->cycles++;
            };

        } else if (MATCH(0,0,1,1, X,X,X,X, X,X,X,X, X,X,X,X)) {
            // cpi
            int K = (EXTRACT(4, 4)<<4) | EXTRACT(12, 4);
            int d = EXTRACT(8, 4) + 16;

            return [this,K,d]() {
                this->cpi(d, K);
                this->cycles++;
            };

        } else if (MATCH(0,0,0,0, 0,1,X,X, X,X,X,X, X,X,X,X)) {
            // cpc
            int d = EXTRACT(7, 5);
            int r = (EXTRACT(6, 1)<<4) | EXTRACT(12, 4);

            return [this,d,r]() {
                this->cpc(d, r);
                this->cycles++;
            };

        } else if (MATCH(1,0,0,1, 0,1,0,1, 1,0,0,1, 1,0,0,0)) {
            // break
            return [this]() {
                this->xbreak();
                this->cycles++;
            };

        } else {
            return [opcode, this]() {
                printf("[%d] Unknown opcode: %04x\n", this->PC, opcode);
                printf("Aborting.\n");
                exit(0);
            };
        }    
    }
}
