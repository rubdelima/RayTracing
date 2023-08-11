#ifndef RAY_H
#define RAY_H 
#include "vec3.hpp"
class Ray{
    public:
        vec3 orig;
        vec3 dir;
        Ray() {}
        Ray(const vec3& origin, const vec3& direction){
            orig = origin; dir = direction;
            }
        vec3 origin() const {return orig;};
        vec3 direction() const {return dir;}
        vec3 pointAtParameter(double t) const {
            return orig + t*dir;
        }
};
#endif