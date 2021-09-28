#ifndef __LIGHT__
#define __LIGHT__

#include "vector.h"
#include "ray.h"
#include "scene.h"

class Light
{
public:
    virtual Vec3 intensity(const Vec3& at_point, const Scene& scene) const = 0;
    virtual Vec3 get_location() const = 0;
    virtual ~Light() {}
};


class PointLight : public Light
{
public:
    PointLight (const Vec3& location,const Vec3& color);

    virtual Vec3 intensity(const Vec3& at_point, const Scene& scene) const;
    virtual Vec3 get_location() const;
private:    
    Vec3 location;
    Vec3 color;
};

class SphereLight : public Light
{
public:
    SphereLight (const Vec3& location, double radius, const Vec3& color);

    virtual Vec3 intensity(const Vec3& at_point, const Scene& scene) const;
    virtual Vec3 get_location() const;
private:
    Vec3 location;
    double radius;
    Vec3 color;
};



#endif
