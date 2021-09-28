#ifndef __CAMERA__
#define __CAMERA__

#include "vector.h"
#include "ray.h"

class Camera
{
    Vec3 eye;
    Vec3 x_axis;
    Vec3 y_axis;
    Vec3 screen_corner;
public:
    Camera(const Vec3& eye, const Vec3& dir, double aspect, double fovy, const Vec3& up);
    Ray get_ray(double x, double y) const;
};

#endif
