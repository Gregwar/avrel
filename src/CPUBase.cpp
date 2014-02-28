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
    }
            
    void CPUBase::writeRegister(int reg, int value)
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

    void CPUBase::jmp(int addr)
    {
        OPCODE_DEBUG("jmp %x\n", addr);
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
        writeRegister(A, r);
    }

    void CPUBase::ldi(int d, int K)
    {
        OPCODE_DEBUG("ldi r%d, %x\n", d, K);
        R[d] = K;
    }

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
