#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    vec3 color;
    vec3 normal;
    vec3 diffuse;
    vec3 specular;
    
    // if (is_exiting) normal = same_side_normal*(-1);
    // else normal = same_side_normal;
    
    normal = same_side_normal;
    
    vec3 ambient = world.ambient_intensity * world.ambient_color * color_ambient;
    color = ambient;
    
    for (unsigned i = 0; i < world.lights.size(); i++)
    {
    
        vec3 l = world.lights.at(i)->position - intersection_point;
        vec3 r = 2*dot(l.normalized(), normal)*normal - l.normalized();
        
        Ray light_ray;
        light_ray.endpoint = intersection_point;
        light_ray.direction = l.normalized();
    
        Hit h;
        // Object *obj = world.Closest_Intersection(light_ray, h);
        // if(!world.Closest_Intersection(light_ray,h))
        // if(!world.enable_shadows || (obj == NULL && world.enable_shadows) || ((l.normalized() - intersection_point).magnitude() <= (light_ray.Point(h.t) - intersection_point).magnitude() && world.enable_shadows))
        
        if(world.enable_shadows)
        {
            if(world.Closest_Intersection(light_ray, h))
            {
                if (l.magnitude() > h.t) continue;
            }
        }
            
            diffuse += (world.lights.at(i)->Emitted_Light(ray)/l.magnitude_squared()) * color_diffuse * std::max(dot(l.normalized(), normal), 0.0);
            specular += (world.lights.at(i)->Emitted_Light(ray)/l.magnitude_squared()) * color_specular * pow(std::max(dot(r.normalized(), (world.camera.position - intersection_point).normalized()), 0.0), specular_power);
        
    }
    
    color += diffuse + specular;
    return color;
}
