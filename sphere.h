#ifndef __SPHERE__
#define __SPHERE__
#include "figure.h"

class Sphere: public Figure
{
protected:
    virtual Vec3 do_intersect(const Ray& ray, double eps) const; 
    virtual Vec3 do_normal(const Vec3& at_point) const;
};
#endif
