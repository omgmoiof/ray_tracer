#include "sphere.h"
#include "ray.h"
#include <cmath>


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    
    
    double b = 2 * dot(ray.direction, ray.endpoint - center);
    double c = dot(ray.endpoint - center, ray.endpoint - center) - pow(radius,2);
    
    double determinant = pow(b,2) - 4*c;
    
    if (determinant > 0)
    {
        Hit h1, h2;
        double t1, t2;
        t1 = (-b - sqrt(determinant)) / 2;
        t2 = (-b + sqrt(determinant)) / 2;
        
        if (t1 > 0)
        {
            h1.t = t1;
            h1.object = this;
            h1.ray_exiting = false;
            hits.push_back(h1);
        }
        
        else
        {
            h1.t = 0;
            h1.object = this;
            h1.ray_exiting = true;
            hits.push_back(h1);
        }
        
        h2.t = t2;
        h2.object = this;
        h2.ray_exiting = true;
        hits.push_back(h2);
        return true;
        
        
    }    
        
    else 
    {
        if (determinant == 0)
        {
            double t = -b / 2;
            if (t > 0)
            {
                Hit h;
                h.t = t;
                h.object = this;
                h.ray_exiting = true;
                hits.push_back(h);
            }
            return true;
            
        }
        
        else return false;
    }
}
        

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    normal = (point - center).normalized();
    return normal;
}
