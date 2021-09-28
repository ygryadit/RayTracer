#include "plane.h"
#include <cmath>
#include <iostream>

Vec3 Plane::do_intersect(const Ray& ray, double eps) const
{
    if (ray.dir[2] == 0)
        return Vec3::not_a_point();
        
    if ((ray.point[2] - eps) * ray.dir[2] > 0)
        return Vec3::not_a_point();
        
    double k = -ray.point[2] / ray.dir[2];

    if (k <= 0)
        return Vec3::not_a_point();

    return Vec3(ray.point[0] + k*ray.dir[0], ray.point[1] + k*ray.dir[1], 0);
}

Vec3 Plane::do_normal(const Vec3& at_point) const
{
    return Vec3(0, 0, 1);
}
