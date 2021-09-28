#include "camera.h"
#include <cmath>

Camera::Camera(const Vec3& eye, const Vec3& dir, double aspect, double fovy, const Vec3& up)
  : eye(eye)
{
    x_axis = 2*tan(fovy/2)*aspect*cross(dir, up);
    y_axis = 2*tan(fovy/2)*up;
    screen_corner = eye + dir - 0.5*(x_axis + y_axis);
}

Ray Camera::get_ray(double x, double y) const
{
    Ray r;
    r.point = eye;
    Vec3 d = (screen_corner + x * x_axis + y * y_axis) - eye;
    r.dir = d / d.length();
    return r;
}
