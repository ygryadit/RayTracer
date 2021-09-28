#include "figure.h"

Material::Material()
    : ambient(0.2, 0.2, 0.2),
      diffuse(1.0, 1.0, 1.0),
      specular(0.0, 0.0, 0.0),
      shininess(1.0)
{}

Figure::Figure()
  : texture(0)
{}

void Figure:: transform(const Transform& t)
{
    direct = t*direct;
    inverse = direct.inverse();    
}

Vec3 Figure:: intersect(const Ray& ray, double eps) const
{
    Ray temp;
    Vec3 point_of_inter;
    temp.point = inverse*ray.point;
    temp.dir = inverse.linear*ray.dir;
    point_of_inter = do_intersect(temp, eps);

    if (point_of_inter == Vec3::not_a_point())
        return point_of_inter;

    return direct*point_of_inter;
}

Vec3 Figure::normal(const Vec3& at_point) const
{
    Vec3 temp = inverse*at_point;
    Vec3 n = direct.linear*do_normal(temp);
    return n / n.length();
}

void Figure::set_material(const Material& mat)
{
    material = mat;
}

const Material& Figure::get_material() const
{
    return material;
}

void Figure::set_texture(Texture* tex)
{
    texture = tex;
}

Texture* Figure::get_texture() const
{
    return texture;
}

const Transform& Figure::get_transform() const
{
    return direct;
}
