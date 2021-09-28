#ifndef __TRACER__
#define __TRACER__

#include "scene.h"
#include "camera.h"
#include "image.h"
#include "ray.h"

class Tracer
{
public:
    Tracer(const Scene& scene);
    void trace(const Camera& camera, ImageWriter& image);
    Vec3 cast_ray(const Ray& ray, int max_depth);

private:
    const Scene& scene;
};

#endif

