#include "dbg.h"

static inline void dbg()
{
    asm ("break");
}
