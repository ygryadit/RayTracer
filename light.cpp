#include "light.h"
#include "vector.h"
#include <cmath>
#include <algorithm>
#include <iostream>


PointLight::PointLight(const Vec3& location, const Vec3& color)
: location(location), color(color)
{}

Vec3 PointLight::intensity(const Vec3& at_point, const Scene& scene) const
{
    Vec3 temp_point, dist = location - at_point;

    if (scene.intersect(Ray(at_point, dist), temp_point) && ((temp_point - at_point).length() < dist.length()))
        return Vec3();
    return color/dot(dist, dist);
}

Vec3 PointLight::get_location() const
{
    return location;
}


SphereLight::SphereLight (const Vec3& location, double radius, const Vec3& color)
: location(location), radius(radius), color(color)
{}

Vec3 SphereLight::intensity(const Vec3& at_point, const Scene& scene) const
{
    Vec3 dir = at_point - location;
    dir /= dir.length();

    Vec3 abs_dir(fabs(dir[0]), fabs(dir[1]), fabs(dir[2]));
    int max_i = std::max_element(&abs_dir.x[0], &abs_dir.x[0] + 3) - &abs_dir.x[0];
    Vec3 indep(1,1,1);
    indep[max_i] = 0;

    Vec3 v1 = cross(dir, indep), v2 = cross(dir, v1);
    v1 /= v1.length(); v2 /= v2.length();


    Vec3 intensity;

    int nh = 1, nphi = 4;
    for (int step = 0; step < 2; ++step)
    {
        intensity = Vec3();
        double hstep = radius/nh, phistep = 2*M_PI/nphi;
        int n = 0;
        for (int i = 0; i < nh; i++)
        {
            double hshift = 0.5;
            double h = (i + hshift)*hstep;
            double r = sqrt(radius*radius - h*h);

            for (int j = 0; j < nphi; j++)
            {
                double phishift = 0.5;
                double phi = (j + phishift) * phistep;

                Vec3 p = location + dir*h + r*(v1*cos(phi) + v2*sin(phi));

                Ray ray;
                ray.point = at_point;
                ray.dir = p - at_point;

                double dist = ray.dir.length();
                ray.dir /= dist;

                Vec3 temp_point;

                if ( !(scene.intersect(ray, temp_point) && ((temp_point - ray.point).length() < dist)) )
                {
                    intensity += color / ((dist * dist) * (nh * nphi));
                    ++n;
                }
            }
        }

        if (step) break;
        if (n == 0 || n == nphi*nh) break;

        nphi = 20;
        nh = 4;
    }

    return intensity;
}

Vec3 SphereLight::get_location() const
{
    return location;
}
