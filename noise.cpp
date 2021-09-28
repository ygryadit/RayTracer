#include "noise.h"
#include <stdlib.h>
#include <math.h>

Noise::Noise()
{
    srand48(1366613);
    for (int i1 = 0; i1 < DIM; i1++)
        for (int i2 = 0; i2 < DIM; i2++)
            for (int i3 = 0; i3 < DIM; i3++)
                table[i1][i2][i3] = drand48();
}

double Noise::operator() (const Vec3& p) const
{
    int a[3], b[3];
    double s[3];

    for (int j = 0; j < 3; ++j)
    {
        a[j] = floor(p.x[j] * DIM);
        s[j] = p.x[j] * DIM - a[j];//s[j] = p.x[j] * DIM - i[j];
        s[j] = s[j]*s[j]*(3 - 2*s[j]);
        a[j] %= DIM;
        if (a[j] < 0) a[j] += DIM;
        b[j] = (a[j] + 1) % DIM;
    }

    return (1 - s[0])*(1 - s[1])*(1 - s[2])*table[a[0]][a[1]][a[2]]
         + (1 - s[0])*(1 - s[1])*(    s[2])*table[a[0]][a[1]][b[2]]
         + (1 - s[0])*(    s[1])*(1 - s[2])*table[a[0]][b[1]][a[2]]
         + (1 - s[0])*(    s[1])*(    s[2])*table[a[0]][b[1]][b[2]]
         + (    s[0])*(1 - s[1])*(1 - s[2])*table[b[0]][a[1]][a[2]]
         + (    s[0])*(1 - s[1])*(    s[2])*table[b[0]][a[1]][b[2]]
         + (    s[0])*(    s[1])*(1 - s[2])*table[b[0]][b[1]][a[2]]
         + (    s[0])*(    s[1])*(    s[2])*table[b[0]][b[1]][b[2]];
}

double Noise::turbulence(const Vec3& p, int harmonics) const
{
    double result = 0, extent = 1;

    for (int i = 0; i < harmonics; i++)
    {
        extent *= 2;
        result +=  (*this)(p*extent)/extent;
    }
    return result;
}

