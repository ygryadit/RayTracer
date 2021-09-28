#include "scene.h"

void Scene::add(Figure* f)
{
    figures.push_back(f);
}

void Scene::add_light(Light* l)
{
    light_sources.push_back(l);
}

Figure* Scene::intersect(const Ray& ray, Vec3& point) const
{
    point = Vec3::not_a_point();
    Figure* min_f = 0;
    double min = std::numeric_limits<double>::infinity();
    
    for (size_t i = 0; i < figures.size(); i++)
    {
        Vec3 p = figures[i]->intersect(ray, -1e-5);       
        if (p != Vec3::not_a_point())
        {
            double dist = (ray.point - p).length();
            if (dist < min)
            {
                min = dist;
                min_f = figures[i];
                point = p;
            } 
        }
    }
    return min_f;
}

int Scene::num_lights() const
{
    return light_sources.size();
}

Light* Scene::get_light(int i) const
{
    return light_sources[i];
}

void Scene::set_ambient(const Vec3& color)
{
    ambient = color;
}

Vec3 Scene::get_ambient() const
{
    return ambient;
}

