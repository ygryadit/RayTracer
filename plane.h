#ifndef __PLANE__
#define __PLANE__
#include "figure.h"
class Plane: public Figure
{
protected:
    virtual Vec3 do_intersect(const Ray& ray, double eps) const; 
    virtual Vec3 do_normal(const Vec3& at_point) const;
};
#endif
