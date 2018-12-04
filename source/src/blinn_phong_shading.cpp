#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>
#include "Object.h"
#include "Ray.h"

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return Eigen::Vector3d(0,0,0);
  //based on algorithm from https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model

  Eigen::Vector3d ka;//ambient
  Eigen::Vector3d kd;//diffuse
  Eigen::Vector3d ks;//specular
  Eigen::Vector3d km;//mirror color
  //float diffuse_p; //IDK
  //float specular_p;//IDK
  double specular_h;//IDK
  Eigen::Vector3d v_dir;//IDK
  Eigen::Vector3d I;

  Eigen::Vector3d L(0,0,0);

  //if (1) {
  std::shared_ptr<Object> object = objects[hit_id];
  ka = object->material->ka;
  L += ka;
    for(auto light:lights)
    {
      //ka = object->material->ka;
      I = light->I;
      kd = object->material->kd;
      ks = object->material->ks;
      //L += (ka.array() * I.array()).matrix();

      Eigen::Vector3d q, d, h, diffuse, specular;
      double max_t;
      q = ray.origin + t * ray.direction;
      light->direction(q, d, max_t);
      d.normalize();
      double intensity = std::max(0.0,n.dot(d));
      //if(intensity > 0)//Mary's little shit
      //{
        // shadow
        int shadow_hit_id;
        double shadow_t = 0.0;
        Eigen::Vector3d shadow_n;
        Ray shadow_ray;
        shadow_ray.origin = q;
        shadow_ray.direction = d;
        bool shadow_hit = first_hit(shadow_ray,1e-7,objects,shadow_hit_id,shadow_t,shadow_n);
        if (!shadow_hit || shadow_t > max_t) {
          diffuse = (kd.array()*I.array()).matrix()*intensity;

          //v_dir = ray.direction;
          //h = (d - v_dir).normalized();
          //h.normalize();
          h = (d + (-ray.direction).normalized()).normalized();
          specular_h = object->material->phong_exponent;
          double intensity2 = pow(std::max(0.0,n.dot(h)),specular_h);
          specular = (ks.array()*I.array()).matrix()*intensity2;

          L = L + diffuse + specular;
        }
      //}
    }
  //}
  return L;
  ////////////////////////////////////////////////////////////////////////////
}
