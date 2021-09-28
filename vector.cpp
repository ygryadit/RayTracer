#include "vector.h"
#include <cmath>

Vec3:: Vec3()
{
    x[0] = x[1] = x[2] = 0.0;
}

Vec3:: Vec3(double a, double b, double c)
{
    x[0] = a;
    x[1] = b;
    x[2] = c; 
}

Vec3& Vec3:: operator+= (const Vec3& b)
{
    x[0] += b.x[0];
    x[1] += b.x[1];
    x[2] += b.x[2]; 
    return *this;
}

Vec3& Vec3:: operator-= (const Vec3& b)
{
    x[0] -= b.x[0];
    x[1] -= b.x[1];
    x[2] -= b.x[2]; 
    return *this;
}

Vec3 Vec3:: operator-() const
{
    Vec3 r;
    r.x[0] = -x[0]; 
    r.x[1] = -x[1]; 
    r.x[2] = -x[2];
    return r;
}
    
Vec3 operator+ (const Vec3& a, const Vec3& b)
{
    Vec3 r = a;
    return r += b;
}

Vec3 operator- (const Vec3& a, const Vec3& b)
{
    Vec3 r = a;
    return r -= b;
}

Vec3& Vec3:: operator*= (double b)
{
    x[0] *= b; 
    x[1] *= b; 
    x[2] *= b;
    return *this;
}

Vec3 operator* (const Vec3& a, double b)
{
    Vec3 r = a;
    return r *= b;
}

Vec3 operator* (double b, const Vec3& a)
{
    Vec3 r = a;
    return r *= b;
}

Vec3 Vec3:: operator/ (double b) const
{
    Vec3 r;
    r.x[0] = x[0]/b;
    r.x[1] = x[1]/b;
    r.x[2] = x[2]/b;
    return r;
}

bool operator==(const Vec3& a, const Vec3& b)
{
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

bool operator!=(const Vec3& a, const Vec3& b)
{
    return a[0] != b[0] || a[1] != b[1] || a[2] != b[2];
}

double dot(const Vec3& a, const Vec3& b)
{
    return a.x[0] * b.x[0] + a.x[1] * b.x[1] + a.x[2] * b.x[2];
}

Vec3 cross(const Vec3& a, const Vec3& b)
{
    Vec3 r;
    r.x[0] = a.x[1] * b.x[2] - a.x[2] * b.x[1];
    r.x[1] = a.x[2] * b.x[0] - a.x[0] * b.x[2];
    r.x[2] = a.x[0] * b.x[1] - a.x[1] * b.x[0];
    return r;
}
double Vec3::length() const
{
    return sqrt(dot(*this, *this));
}

Vec3 operator* (const Vec3& a, const Vec3& b)
{
    return Vec3(a[0]*b[0], a[1]*b[1], a[2]*b[2]);
}

Vec3& Vec3::operator/=  (double b)
{
    x[0] /= b;
    x[1] /= b;
    x[2] /= b;
    return *this;
}

std::ostream&
operator<< (std::ostream& o, const Vec3& v)
{
    o << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    return o;
}

////////////////////////////////////////////////////////////////////////

Vec2 Vec2::operator -() const
{
    return Vec2(-x[0], -x[1]);
}


Vec2::Vec2(double a, double b)
{
    x[0] = a;
    x[1] = b;
}


double Vec2::length() const
{
    return sqrt(x[0]*x[0] + x[1]*x[1]);
}


Vec2 & Vec2::operator *=(double b)
{
    x[0] *= b;
    x[1] *= b;
    return *this;
}


Vec2::Vec2()
{
    x[0] = x[1] = 0.0;
}


Vec2 & Vec2::operator+= (const Vec2 & b)
{
    x[0] += b.x[0];
    x[1] += b.x[1];
    return *this;
}


Vec2 & Vec2::operator-= (const Vec2 & b)
{
    x[0] -= b.x[0];
    x[1] -= b.x[1];
    return *this;
}


Vec2 Vec2::operator/ (double b) const
{
    return Vec2(x[0] / b, x[1] / b);
}


Vec2 & Vec2::operator/= (double b)
{
    x[0] /= b;
    x[1] /= b;
    return *this;
}

Vec2 operator+ (const Vec2& a, const Vec2& b)
{
    return Vec2(a.x[0] + b.x[0], a.x[1] + b.x[1]);
}

Vec2 operator- (const Vec2& a, const Vec2& b)
{
    return Vec2(a.x[0] - b.x[0], a.x[1] - b.x[1]);
}

Vec2 operator* (const Vec2& a, double b)
{
    return Vec2(a.x[0]*b, a.x[1]*b);
}

Vec2 operator* (double b, const Vec2& a)
{
    return Vec2(a.x[0]*b, a.x[1]*b);
}


double dot(const Vec2& a, const Vec2& b)
{
    return a.x[0] * b.x[0] + a.x[1] * b.x[1];
}

double cross(const Vec2& a,const Vec2& b)
{
    return a.x[0] * b.x[1] - a.x[1] * b.x[0];
}

std::ostream& operator<< (std::ostream& o, const Vec2& v)
{
    o << '(' << v[0] << ", " << v[1] << ')';
    return o;
}
