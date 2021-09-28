#ifndef __FIGURE__
#define __FIGURE__
#include "vector.h"
#include "affine.h"
#include "ray.h"
#include "texture.h"

struct Material
{
    Vec3    ambient;
    Vec3    diffuse;
    Vec3    specular;
    double  shininess;
    Vec3    mirror;
    
    Material();
};

class Figure
{
public:
  Figure();
  const Transform& get_transform() const;

  void set_material(const Material& mat);
  const Material& get_material() const;
  void set_texture(Texture* tex);
  Texture* get_texture() const;
  
  void transform(const Transform& t);
  Vec3 intersect(const Ray& ray, double eps) const;
  Vec3 normal(const Vec3& at_point) const;

  
  virtual ~Figure() {}
protected:
  virtual Vec3 do_intersect(const Ray& ray, double eps) const = 0;
  virtual Vec3 do_normal(const Vec3& at_point) const = 0;

private:
  Transform direct;
  Transform inverse;
  Material material;
  Texture* texture;
};
#endif
