#include "revolution.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

static bool plane_ray(
        const Ray& ray,
        int plane,
        double d,
        const Vec2& min_xy,
        const Vec2& max_xy
     )
{
    double dh = ray.dir[plane];
    if (fabs(dh) < 1e-8) return false;

    double h = ray.point[plane] - d;

    double t = -h / dh;
    if (t <= 0) return false;

    Vec3 point = ray.point + t*ray.dir;

    for (int i = 0, k = 0; i < 3; ++i)
    {
        if (i == plane) continue;
        if (point[i] < min_xy[k] || point[i] > max_xy[k])
            return false;
        ++k;
    }

    return true;
}

static bool box_ray(
        const Ray& ray,
        const Vec3& min,
        const Vec3& max
       )
{
    return plane_ray(ray, 0, min[0], Vec2(min[1], min[2]), Vec2(max[1], max[2]))
        || plane_ray(ray, 0, max[0], Vec2(min[1], min[2]), Vec2(max[1], max[2]))
        || plane_ray(ray, 1, min[1], Vec2(min[0], min[2]), Vec2(max[0], max[2]))
        || plane_ray(ray, 1, max[1], Vec2(min[0], min[2]), Vec2(max[0], max[2]))
        || plane_ray(ray, 2, min[2], Vec2(min[0], min[1]), Vec2(max[0], max[1]))
        || plane_ray(ray, 2, max[2], Vec2(min[0], min[1]), Vec2(max[0], max[1]));

}


Revolution::Revolution(const Bezier& bez)
    : bezier(bez)
{
    double maxr = 0.0;
    double minz = std::numeric_limits<double>::infinity();
    double maxz = -minz;
    for (int i = 0; i < bez.nodes(); ++i)
    {
        double r = fabs(bez[i].point[0]);
        if (r > maxr)
            maxr = r;
        if (bez[i].point[1] < minz)
            minz = bez[i].point[1];
        if (bez[i].point[1] > maxz)
            maxz = bez[i].point[1];
    }

    maxr += 1e-5;

    bound_min = Vec3(-maxr, -maxr, minz - 1e-5);
    bound_max = Vec3(maxr, maxr, maxz + 1e-5);
}


Vec3 Revolution::do_intersect(const Ray& ray, double eps) const
{
    if ( ray.point[0] < bound_min[0] || ray.point[0] > bound_max[0]
      || ray.point[1] < bound_min[1] || ray.point[1] > bound_max[1]
      || ray.point[2] < bound_min[2] || ray.point[2] > bound_max[2] )
    {
        if (!box_ray(ray, bound_min, bound_max))
            return Vec3::not_a_point();
    }

    double pp = ray.point[0]*ray.point[0] + ray.point[1]*ray.point[1];
    double pa = ray.point[0]*ray.dir[0] + ray.point[1]*ray.dir[1];
    double aa = ray.dir[0]*ray.dir[0] + ray.dir[1]*ray.dir[1];

    double min_t = std::numeric_limits<double>::infinity();
    int min_i = -1;

    for (int i = 1; i < bezier.nodes(); ++i)
    {
        double z0 = bezier[i - 1].point[1];
        double r1 = fabs(bezier[i - 1].point[0]);
        double h = bezier[i].point[1] - z0;
        double r2 = fabs(bezier[i].point[0]);

        double R = r2 - r1;

        double alpha = h / ray.dir[2];
        double beta = (z0 - ray.point[2]) / ray.dir[2];

        double a = R*R - alpha*alpha*aa;
        double b = 2*R*r1 - 2*alpha*beta*aa - 2*alpha*pa;
        double c = r1*r1 - pp - 2*beta*pa - beta*beta*aa;

        double D = b*b - 4*a*c;
        if (D < 0) continue;

        double ss[2] = { (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a) };
        double s = -1.0;
        double t = std::numeric_limits<double>::infinity();

        for (int j = 0; j < 2; ++j)
            if (ss[j] >= 0 && ss[j] <= 1)
            {
                double tt = alpha*ss[j] + beta;
                if (tt < t && tt > -eps)
                {
                    t = tt;
                    s = ss[j];
                }
            }

        if (s < 0) continue;

        if (t < min_t)
        {
            min_t = t;
            min_i = i;
            last_s = s;
        }
    }

    if (min_i != -1)
        last_intersection = ray.point + min_t * ray.dir;
    else
        last_intersection = Vec3::not_a_point();

    last_node = min_i - 1;

    return last_intersection;
}


Vec3 Revolution::do_normal(const Vec3& at_point) const
{
    if ((at_point - last_intersection).length() < 1e-8 && last_node >= 0)
    {
        int segment = bezier[last_node].segment;

        double t0 = bezier[last_node].t;
        double t1 = bezier[last_node + 1].t;

        if (t1 == 0.0) t1 = 1.0;

        double t = (1 - last_s)*t0 + last_s*t1;

        Vec2 n2 = bezier.normal(segment, t);
        Vec3 n(-n2[0], 0, n2[1]);

        Vec2 d(at_point[0], at_point[1]);
        double l = d.length();
        if (l > 0)
        {
            d /= l;
            n[0] = -n2[0]*d[0];
            n[1] = -n2[0]*d[1];
        }

        return n;
    }

    throw std::logic_error("Not implemented");
    return Vec3::not_a_point();
}
