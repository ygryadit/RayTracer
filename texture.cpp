#include "texture.h"
#include "noise.h"
#include <cmath>

Vec3 Texture::get_color(const Vec3& point) const
{
    return do_get_color(inverse*point);
}

void Texture::transform(const Transform& t)
{
    direct = t*direct;
    inverse = direct.inverse();
}

Vec3 Checkerboard_round::do_get_color(const Vec3& point) const
{
    double phi = atan2(point.x[0], point.x[1]);
    double r = point.length();
    double theta = acos(point.x[2] / r);

    int phi_cells = 14;
    int theta_cells = 10;

    int i = (phi / (2.0 * M_PI) + 0.5) * phi_cells;
    int j = (theta / M_PI) * theta_cells;
    int k = r * 3.8267126723;

    return (((i + j + k) % 2 + 2) % 2) * Vec3(1, 1, 1);
}

Vec3 Checkerboard::do_get_color(const Vec3& point) const
{
    int x = floor(point.x[0]);
    int y = floor(point.x[1]);
    int z = floor(point.x[2]);

    return (((x + y + z) % 2 + 2) % 2) * Vec3(1, 1, 1);
}

Vec3 Marble::do_get_color(const Vec3& point_) const
{
    Vec3 point = point_ / 21.0;
    double k = sin((20.0*point[0] + 30.0*point[1] + 10.0*point[2] + 8.0*noise.turbulence(point, 9)));

    k = 0.5 + 0.5*copysign(pow(fabs(k), 0.7), k);

    Vec3 v1 = Vec3(255, 234, 244) / 255.0 * 2;
    Vec3 v2 = Vec3(107, 107, 107) / 255.0 * 1;
    Vec3 v3 = Vec3(255, 234, 244) / 255.0 * 2;
    //return (1 - k) * v1 + k*v2;
    if (k < 0.5)
        return 2*((0.5 - k) * v1 + k*v2);
    return 2*((1.0 - k) * v2 + (k - 0.5)*v3);

}
