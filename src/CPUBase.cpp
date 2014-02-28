#include <iostream>
#include "timing/Chrono.h"
#include "CPUBase.h"
#include "opcode.h"
#include "registers.h"

namespace avrel
{
    CPUBase::CPUBase(ROM &rom_, RAM &ram_, int frequency_)
        : rom(rom_), ram(ram_), frequency(frequency_), cycles(0)
    {
        reset();
    }

    void CPUBase::reset()
    {
        rom.jumpTo(0);
        I = T = H = S = V = N = Z = C = false;
        unsigned int i;
        for (i=0; i<sizeof(registers); i++) {
            registers[i] = 0;
        }
    }

    int CPUBase::readRegister(unsigned int reg)
    {
        switch (reg) {
            case SREG:
                return getSreg();
                break;
            case SPL:
                return SP&0xff;
                break;
            case SPH:
                return (SP>>8)&0xff;
                break;
        }

        if (reg < sizeof(registers)) {
            return registers[reg];
        }

        return 0;
    }
            
    void CPUBase::writeRegister(unsigned int reg, int value)
    {
        switch (reg) {
            case SREG:
                setSreg(value);
                break;
            case SPL:
                SP = (SP&0xff00)|value;
                break;
            case SPH:
                SP = (SP&0x00ff)|(value<<8);
                break;
        }

        if (reg < sizeof(registers)) {
            registers[reg] = value;
        }

        if (reg == PORTB) {
            printf("PORTB: %02x\n", value);
        }
    }

    void CPUBase::setSreg(int value)
    {
        I = (value>>7)&1;
        T = (value>>6)&1;
        H = (value>>5)&1;
        S = (value>>4)&1;
        V = (value>>3)&1;
        N = (value>>2)&1;
        Z = (value>>1)&1;
        C = (value>>0)&1;
    }

    int CPUBase::getSreg()
    {
        return
            ((I ? 1 : 0)<<7) |
            ((T ? 1 : 0)<<6) |
            ((H ? 1 : 0)<<5) |
            ((S ? 1 : 0)<<4) |
            ((V ? 1 : 0)<<3) |
            ((N ? 1 : 0)<<2) |
            ((Z ? 1 : 0)<<1) |
            ((C ? 1 : 0)<<0);
    }

    // Utils

    void CPUBase::pushByte(int byte)
    {
        ram.writeByte(SP--, byte);
    }
    
    void CPUBase::pushWord(int word)
    {
        ram.writeWord(SP, word);
        SP-=2;
    }

    // Opcodes

    void CPUBase::jmp(int addr)
    {
        OPCODE_DEBUG("jmp %x\n", addr);
        rom.jumpTo(addr);
    }

    void CPUBase::call(int addr)
    {
        OPCODE_DEBUG("call %x\n", addr);
        pushWord(rom.getPosition());
        rom.jumpTo(addr);
    }

    void CPUBase::eor(int r, int d)
    {
        OPCODE_DEBUG("eor r%d, r%d\n", r, d);
        R[d] = R[r] ^ R[d];
        V = 0;
        N = (R[d]>>7)&1;
        S = V^N;
        Z = (R[d] == 0);
    }

    void CPUBase::out(int r, int A)
    {
        OPCODE_DEBUG("out r%d, %x\n", r, A);
        writeRegister(A, R[r]);
    }

    void CPUBase::sts(int r, int A)
    {
        OPCODE_DEBUG("sts r%d, %x\n", r, A);
        writeRegister(A, R[r]);
    }

    void CPUBase::in(int r, int A)
    {
        OPCODE_DEBUG("in r%d, %x\n", r, A);
        R[r] = readRegister(A);
    }

    void CPUBase::ldi(int d, int K)
    {
        OPCODE_DEBUG("ldi r%d, %x\n", d, K);
        R[d] = K;
    }

    void CPUBase::cli()
    {
        OPCODE_DEBUG("cli\n");
        I = false;
    }

    void CPUBase::sei()
    {
        OPCODE_DEBUG("sei\n");
        I = true;
    }
    
    void CPUBase::sbi(int A, int b)
    {
        OPCODE_DEBUG("sbi %x, %d\n", A, b);
        int value = readRegister(A);
        value |= (1<<b);
        writeRegister(A, value);
    }

    void CPUBase::cbi(int A, int b)
    {
        OPCODE_DEBUG("cbi %x, %d\n", A, b);
        int value = readRegister(A);
        value &= ~(1<<b);
        writeRegister(A, value);
    }
            
    void CPUBase::subi(int d, int K)
    {
        OPCODE_DEBUG("subi r%d, %x\n", d, K);
        C = (K > R[d]);
        R[d] -= K;
        Z = (R[d] == 0);
        N = (R[d]>>7)&1;
        // XXX: H, V et S non maintenus
    }
            
    void CPUBase::sbci(int d, int K)
    {
        OPCODE_DEBUG("sbci r%d, %x\n", d, K);
        K += (C ? 1 : 0);
        C = (K > R[d]);
        R[d] -= K;
        Z = (R[d] == 0);
        N = (R[d]>>7)&1;
        // XXX: H, V et S non maintenus
    }
            
    bool CPUBase::brne(int k)
    {
        OPCODE_DEBUG("brne %d\n", k);
        
        if (!Z) {
            rom.jumpRelative(k);
            return true;
        } else {
            return false;
        }
    }

    void CPUBase::rjmp(int k)
    {
        OPCODE_DEBUG("rjmp %d\n", k);
        rom.jumpRelative(k);
    }

    void CPUBase::nop()
    {
        OPCODE_DEBUG("nop\n");
    }

    // X Y & Z

    void CPUBase::setX(int value)
    {
        R[27] = (value>>8)&0xff;
        R[26] = (value>>0)&0xff;
    }

    void CPUBase::setY(int value)
    {
        R[29] = (value>>8)&0xff;
        R[28] = (value>>0)&0xff;
    }

    void CPUBase::setZ(int value)
    {
        R[31] = (value>>8)&0xff;
        R[30] = (value>>0)&0xff;
    }

    int CPUBase::getX()
    {
        return (R[27]<<8)|R[26];
    }

    int CPUBase::getY()
    {
        return (R[29]<<8)|R[28];
    }

    int CPUBase::getZ()
    {
        return (R[31]<<8)|R[30];
    }
}
