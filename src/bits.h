#ifndef _AVREL_BITS_H
#define _AVREL_BITS_H

static inline bool bitsMatch(int X, std::initializer_list<int> list)
{
    int k =0; 
    int size = list.size();
    for (int i : list) {
        int b = (X>>(size-k-1))&1;
        if (i!=-1 && i!=b) {
            return false;
        }   
        k++;
    }   

    return true;
}

static inline int bitsExtract(int x, int size, std::initializer_list<int> list)
{
    int n = 0;
    for (int i : list) {
        n <<= 1;
        n |= ((x>>(size-1-i))&1);
    }
    return n;
}

static inline int bitsSign(int value, int length)
{
    return ((value < (1<<(length-1))) ? 
            (value) 
            : (value-(1<<length)));
}

static inline int bitsGet(int value, int n)
{
    return ((value>>n)&1);
}

#endif
