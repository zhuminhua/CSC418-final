#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  rgb = Eigen::Vector3d(0,0,0);
  // return false;
  int hit_id;
  double t;
  Eigen::Vector3d n, p, kd, ks, km, blinn_phong;
  bool hit = first_hit(ray,min_t,objects,hit_id,t,n);
  if (hit) {
    std::shared_ptr<Object> object = objects[hit_id];
    km = object->material->km;
    blinn_phong = blinn_phong_shading(ray,hit_id,t,n,objects,lights);
    rgb = blinn_phong;
    if (num_recursive_calls == 5) {
      return true;
    }
    else {
      Ray next_ray;
      Eigen::Vector3d next_n;
      next_ray.origin = ray.origin + t * ray.direction;
      next_ray.direction = reflect(ray.direction,n);
      Eigen::Vector3d prev_rgb;
      raycolor(next_ray,1e-7,objects,lights,num_recursive_calls+1,prev_rgb);
      rgb = rgb + (km.array() * prev_rgb.array()).matrix();
      return true;
    }
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
