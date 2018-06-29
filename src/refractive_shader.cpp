#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. 
        //      If so update the reflectance_ratio for total internal refraction
        //
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        
        //
        vec3 normal;
        double n_i, n_r;
        if (is_exiting) 
        {
            n_i = refractive_index;
            n_r = REFRACTIVE_INDICES::AIR;
            normal = -1.0 * same_side_normal;
        }
        else
        {
            n_r = refractive_index;
            n_i = REFRACTIVE_INDICES::AIR;
            normal = same_side_normal;
        }
        
        double n_ratio = n_i/n_r;
        double cos_theta_i = (dot(-1.0 * ray.direction, normal) / (ray.direction.magnitude()));
        double cos_theta_r = sqrt(1 - pow(n_ratio, 2) * (1 - pow(cos_theta_i, 2)));
        
        
        
        
        
        
        if( 1 - pow(n_ratio, 2) * (1 - pow(cos_theta_i, 2)) < 0 )
        {
            reflectance_ratio = 1;
            refraction_color = vec3(0,0,0);
        }
        
        
        else 
        {
            vec3 d = ray.direction.normalized();
            vec3 T = n_ratio * (d - dot(normal,d) * normal) - (cos_theta_r * normal);
            
            Ray refractive_ray;
            refractive_ray.endpoint = intersection_point;
            refractive_ray.direction = T;
            refraction_color = world.Cast_Ray(refractive_ray, recursion_depth + 1);
        }
    }

    if(!world.disable_fresnel_reflection){
        
        Ray reflected_ray;
        reflected_ray.endpoint = intersection_point;
        reflected_ray.direction = (-2 * dot(ray.direction, same_side_normal)*same_side_normal + ray.direction);
        reflection_color = world.Cast_Ray(reflected_ray, recursion_depth + 1);
    }
    

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // reflectance_ratio = 1;
    color = reflectance_ratio * reflection_color + (1 - reflectance_ratio) * refraction_color;
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

 