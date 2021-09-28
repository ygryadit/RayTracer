#ifndef REVOLUTION_H_
#define REVOLUTION_H_

#include "bezier.h"
#include "figure.h"

class Revolution : public Figure
{
public:
    Revolution(const Bezier& bez);
protected:
    virtual Vec3 do_intersect(const Ray& ray, double eps) const;
    virtual Vec3 do_normal(const Vec3& at_point) const;

private:
    Bezier bezier;
    mutable Vec3 last_intersection;
    mutable int last_node;
    mutable double last_s;
    Vec3    bound_min;
    Vec3    bound_max;
};

#endif /* REVOLUTION_H_ */
