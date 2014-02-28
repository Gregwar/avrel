#ifndef _AVREL_UTIL_H
#define _AVREL_UTIL_H

// Sign an expression
#define VALUE_SIGN(value, length) \
    ((value < (1<<(length-1))) ? \
    (value) \
    : (value-(1<<length)))

// Get the nth bit
#define GETBIT(value,n) \
    ((value>>n)&1)

#endif
