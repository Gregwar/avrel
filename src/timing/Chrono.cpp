#include "Chrono.h"

Chrono::Chrono()
{
    reset();
}

void Chrono::reset()
{
    point = std::chrono::system_clock::now();
}

double Chrono::getTime()
{
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = now-point;

    return duration.count();
}
