#include "tracer.h"
#include <iostream>
#include <cmath>
#include "light.h"
#include <algorithm>

Tracer::Tracer(const Scene& scene)
    : scene(scene)
{}


void Tracer::trace(const Camera& camera, ImageWriter& image)
{
    for (int i = 0; i < image.height(); i++)
    {

        for (int j = 0; j < image.width(); j++)
        {

            double x = double(j)/image.width();
            double y = 1 - double(i)/image.height();

            int antialias_x = 4, antialias_y = 4;
            double dx = 1.0 / (image.width() * antialias_x);
            double dy = 1.0 / (image.height() * antialias_y);
            Vec3 color;
            for (int sub_y = 0; sub_y < antialias_y; ++sub_y)
                for (int sub_x = 0; sub_x < antialias_x; ++sub_x)
                {
                    Ray ray = camera.get_ray(x + sub_x*dx + dx/2, y - sub_y*dy - dy/2);
                    color += cast_ray(ray, 10);
                }

            image.write(color/(antialias_x * antialias_y));
        }
    }
}


Vec3 Tracer::cast_ray(const Ray& ray, int max_depth)
{
    Vec3 point, color;
    Figure* figure = scene.intersect(ray, point);
    if (figure)
    {
        Vec3 normal = figure->normal(point);
        Vec3 dir_to_eye = ray.point - point;
        dir_to_eye /= dir_to_eye.length();

        Vec3 texture_color(1, 1, 1);
        if (Texture* tex = figure->get_texture())
            texture_color = tex->get_color(point);

        color = figure->get_material().ambient*scene.get_ambient() * texture_color;

        for (int l = 0; l < scene.num_lights(); l++)
        {
            Light* light = scene.get_light(l);
            Vec3 intensity = light->intensity(point, scene);

            Vec3 dir_to_light = light->get_location() - point;
            dir_to_light /= dir_to_light.length();

            color += intensity * figure->get_material().diffuse
                   * std::max(0.0, dot(dir_to_light, normal)) * texture_color;

            Vec3 reflected = 2.0 * dot(dir_to_light, normal) * normal - dir_to_light;
            reflected /= reflected.length();

            double ks = pow(std::max(0.0, dot(dir_to_eye, reflected)), figure->get_material().shininess);
            color += intensity * figure->get_material().specular * ks * texture_color;
        }

        if (figure->get_material().mirror.length() > 1e-5 && max_depth > 0)
        {
            Vec3 reflected_dir = 2.0 * dot(dir_to_eye, normal) * normal - dir_to_eye;
            Ray reflected_ray(point, reflected_dir);
            Vec3 reflection_color = cast_ray(reflected_ray, max_depth - 1);
            color += reflection_color * figure->get_material().mirror;
        }
    }

    return color;
}
