#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // if (dot(ray.direction, normal) == 0) return false;
    double t = dot(x1 - ray.endpoint, normal)/dot(ray.direction, normal);
    
    Hit h;
    h.t = t;
    h.object = this;
    h.ray_exiting = true;
    
    if (dot(ray.direction, normal) == 0)
    {
        h.t = 0;
        hits.push_back(h);
        return true;
    }
    
    
    if (t > 0)
    {
        hits.push_back(h);
        return true;
    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
