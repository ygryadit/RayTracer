#ifndef BEZIER_H_
#define BEZIER_H_

#include "vector.h"
#include <vector>

class Bezier
{
public:
    struct Node
    {
        Vec2    point;
        int     segment;
        double  t;
    };

    Bezier (const Vec2* points, int segments, double eps);

    int nodes() const;
    const Node& operator[] (int i) const;

    Vec2 normal(int segment, double t) const;

private:
    std::vector<Node>   polyline;
    std::vector<Vec2>   spline;
    double              eps;

    void subdivide(int segment, const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, double t0, double t1);
};

#endif /* BEZIER_H_ */
