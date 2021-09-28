#ifndef __NOISE__
#define __NOISE__

#include "vector.h"

class Noise
{
public:
    Noise();
    double operator() (const Vec3& p) const;
    double turbulence(const Vec3& p, int harmonics) const;
private:
    enum { DIM = 60 };
    double table[DIM][DIM][DIM];
};



#endif

