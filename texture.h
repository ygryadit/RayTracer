#ifndef __TEXTURE__
#define __TEXTURE__

#include "vector.h"
#include "affine.h"
#include "noise.h"

class Texture
{
public:
    Vec3 get_color(const Vec3& point) const;
    void transform(const Transform& t);

    virtual ~Texture() {}
protected:
    virtual Vec3 do_get_color(const Vec3& point) const = 0;
private:
    Transform direct;
    Transform inverse;
};

class Checkerboard : public Texture
{
protected:
    virtual Vec3 do_get_color(const Vec3& point) const;
};

class Checkerboard_round: public Texture
{
protected:
    virtual Vec3 do_get_color(const Vec3& point) const;
};

class Marble : public Texture
{
protected:
    virtual Vec3 do_get_color(const Vec3& point) const;
private:
    Noise noise;
};
#endif
