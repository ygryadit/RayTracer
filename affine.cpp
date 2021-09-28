#include "affine.h"

Vec3 Transform:: operator() (const Vec3& x) const
{
    return linear*x + translation;
}

Transform:: Transform() {}

Transform:: Transform(const Vec3& b,const Mat3& A)
{
    translation = b;
    linear = A;
}

Transform Transform::inverse() const
{
    Transform r;
    r.linear = linear.inverse();
    r.translation = -1*linear.inverse()*translation;
    return r;
}


Transform operator* (const Transform& t1, const Transform& t2)
{
    Transform t;
    t.linear = t1.linear * t2. linear;
    t.translation = t1.linear*t2.translation + t1.translation;
    return t;
}

Vec3 operator* (const Transform& t, const Vec3& v)
{
    return t.linear*v + t.translation;
}

Transform Transform::translate(const Vec3& v)
{
    return Transform(v, Mat3());
}

Transform Transform::scale(const Vec3& s)
{
    Mat3 mat;
    mat.A[0][0] = s[0];
    mat.A[1][1] = s[1];
    mat.A[2][2] = s[2];
    return Transform(Vec3(), mat);
}
