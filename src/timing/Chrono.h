#ifndef _AVREL_CHRONO_H
#define _AVREL_CHRONO_H

#include <chrono>

class Chrono
{
    public:
        Chrono();
        void reset();
        double getTime();

    protected:
        std::chrono::time_point<std::chrono::system_clock> point;
};

#endif
