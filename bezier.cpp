#include "bezier.h"
#include <cmath>

Bezier::Bezier (const Vec2* points, int segments, double eps)
    : spline(points, points + 3*segments + 1), eps(eps)
{
    for (int i = 0; i < segments; ++i)
    {
        int p = 3*i;
        Node node = { points[p], i, 0.0 };
        polyline.push_back(node);
        subdivide(i, points[p], points[p+1], points[p+2], points[p+3], 0.0, 1.0);
    }

    Node node = { points[3*segments], segments - 1, 1.0 };
    polyline.push_back(node);
}


int Bezier::nodes() const
{
    return polyline.size();
}


const Bezier::Node&
Bezier::operator[] (int i) const
{
    return polyline[i];
}


Vec2 Bezier::normal(int segment, double t) const
{
    int p = segment * 3;
    double s = 1.0 - t;

    Vec2 tangent = -s*s*spline[p] + s*(1- 3*t)*spline[p+1] + t*(2 - 3*t)*spline[p+2] + t*t*spline[p+3];
    Vec2 normal(-tangent[1], tangent[0]);
    return normal / normal.length();
}

void
Bezier::subdivide(int segment, const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, double t0, double t1)
{
    Vec2 p12 = 0.5*(p1 + p2);
    Vec2 p23 = 0.5*(p2 + p3);
    Vec2 p34 = 0.5*(p3 + p4);
    Vec2 p123 = 0.5*(p12 + p23);
    Vec2 p234 = 0.5*(p23 + p34);
    Vec2 p1234 = 0.5*(p123 + p234);

    Vec2 d = p4 - p1;

    double area = fabs(cross(p2 - p4, d)) + fabs(cross(p3 - p4, d));

    double tcenter = 0.5*(t0 + t1);
    if (area*area < eps*dot(d, d))
    {
        Node node = {
            p1234, segment, tcenter
        };
        polyline.push_back(node);
        return;
    }

    subdivide(segment, p1, p12, p123, p1234, t0, tcenter);
    subdivide(segment, p1234, p234, p34, p4, tcenter, t1);
}
