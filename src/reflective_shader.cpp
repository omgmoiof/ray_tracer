#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 color;
    
    //REFLECTION
    Ray reflected_ray;
    // vec3 normal = same_side_normal;
    // vec3 ray_direction = (intersection_point - ray.endpoint).normalized();
    
    reflected_ray.endpoint = intersection_point;
    reflected_ray.direction = (-2 * dot(ray.direction, same_side_normal)*same_side_normal + ray.direction);
    // recursion_depth++;
    
    vec3 reflected_color = world.Cast_Ray(reflected_ray, recursion_depth + 1);
    
    
    //LOCAL COLOR
    vec3 shader_color = shader->Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth, false);
    
    color = (reflectivity * reflected_color + (1 - reflectivity) * shader_color); 
    return color;
}
