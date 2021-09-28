#include <cmath>
#include "sphere.h"
#include <algorithm>

Vec3 Sphere:: do_intersect(const Ray& ray, double eps) const
{
    double a = dot(ray.dir, ray.dir);
    double b = dot(ray.dir, ray.point);
    double c = dot(ray.point, ray.point) - 1;
    
    double D = b*b - a*c;
    
    if  (D < 0)
        return Vec3::not_a_point();
        
    double p1 = -b - sqrt(D);
    double p2 = -b + sqrt(D);
    
    if (p1 < -eps && p2 < -eps)
        return Vec3::not_a_point();
        
    double p;
    if (p1 < -eps)
        p = p2;
    else if (p2 < -eps)
        p = p1;
    else
        p = std::min(p1, p2);

    return ray.point + ray.dir*p;
}

Vec3 Sphere::do_normal(const Vec3& at_point) const
{
    return at_point;
}
