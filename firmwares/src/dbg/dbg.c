#include <avr/io.h>
#include "dbg.h"

#define DBG _SFR_MEM16(0xF4)

void dbg(const char *message)
{
    DBG = message;
    asm("break");
}
