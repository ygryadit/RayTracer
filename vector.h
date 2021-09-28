#ifndef __VECTOR__
#define __VECTOR__
#include <limits>
#include <ostream>

class Vec3
{
public:
    double x[3];
    Vec3();
    Vec3(double a, double b, double c);
    Vec3&   operator+=  (const Vec3& b);
    Vec3&   operator-=  (const Vec3& b);
    Vec3&   operator*=  (double b);
    Vec3&   operator/=  (double b);
    Vec3    operator-   () const;
    Vec3    operator/   (double b) const;
    double length() const;
    
    double operator[] (int i) const { return x[i]; }
    double& operator[] (int i) { return x[i]; }
    
    static Vec3 not_a_point() 
    {
        double inf = std::numeric_limits<double>::infinity();
        return Vec3(inf, inf, inf);
    }
};

Vec3 operator+ (const Vec3& a, const Vec3& b);
Vec3 operator- (const Vec3& a, const Vec3& b);
Vec3 operator* (const Vec3& a, double b);
Vec3 operator* (double b, const Vec3& a);
Vec3 operator* (const Vec3& a, const Vec3& b);

bool operator==(const Vec3& a, const Vec3& b);
bool operator!=(const Vec3& a, const Vec3& b);

double dot(const Vec3& a,const Vec3& b);
Vec3 cross(const Vec3& a,const Vec3& b);

std::ostream& operator<< (std::ostream& o, const Vec3& v);


class Vec2
{
public:
    double x[2];

    Vec2();
    Vec2(double a, double b);
    Vec2&   operator+=  (const Vec2& b);
    Vec2&   operator-=  (const Vec2& b);
    Vec2&   operator*=  (double b);
    Vec2&   operator/=  (double b);
    Vec2    operator-   () const;
    Vec2    operator/   (double b) const;
    double length() const;

    double operator[] (int i) const { return x[i]; }
    double& operator[] (int i) { return x[i]; }

    static Vec2 not_a_point()
    {
        double inf = std::numeric_limits<double>::infinity();
        return Vec2(inf, inf);
    }
};

Vec2 operator+ (const Vec2& a, const Vec2& b);
Vec2 operator- (const Vec2& a, const Vec2& b);
Vec2 operator* (const Vec2& a, double b);
Vec2 operator* (double b, const Vec2& a);


double dot(const Vec2& a, const Vec2& b);
double cross(const Vec2& a,const Vec2& b);

std::ostream& operator<< (std::ostream& o, const Vec2& v);

#endif

