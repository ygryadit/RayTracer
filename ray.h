#ifndef __RAY__
#define __RAY__

struct Ray
{
    Vec3 point;
    Vec3 dir;
    
    Ray(){}
    
    Ray(const Vec3& point, const Vec3& dir)
       : point(point), dir(dir / dir.length())
    { }
};

#endif

