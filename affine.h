#ifndef __AFFINE__
#define __AFFINE__

#include "vector.h"
#include "matrix.h"

class Transform
{
public:
    Vec3 translation;
    Mat3 linear;
    
    Transform();
    Transform(const Vec3& b,const Mat3& A);
    Vec3 operator() (const Vec3& x) const;
    Transform inverse() const;

    static Transform translate(const Vec3& v);
    static Transform scale(const Vec3& s);
};
Transform operator* (const Transform& t1, const Transform& t2);
Vec3 operator* (const Transform& t, const Vec3& v);
#endif
