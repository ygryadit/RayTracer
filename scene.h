#ifndef __SCENE__
#define __SCENE__

#include "figure.h"

#include <vector>

class Light;

class Scene
{
public:
    void add(Figure* f);
    void add_light(Light* l);
    Figure* intersect(const Ray& ray, Vec3& point) const;
    int num_lights() const;
    Light* get_light(int i) const;
    void set_ambient(const Vec3& color);
    Vec3 get_ambient() const;

private:
    std::vector<Figure*> figures;
    std::vector<Light*> light_sources;

    Vec3 ambient;
};

#endif

