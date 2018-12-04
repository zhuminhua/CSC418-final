#include "Sphere.h"
#include "Ray.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return false;
  // (d · d)t2 + 2d · (e − c)t + (e − c) · (e − c) − R2 = 0 intersect
  Eigen::Vector3d e_minus_c = ray.origin - center;
  Eigen::Vector3d d = ray.direction;
  double discriminant = (d.dot(e_minus_c)) * (d.dot(e_minus_c)) - (d.dot(d)) * (e_minus_c.dot(e_minus_c) - radius * radius);

  if (discriminant < 0) {return false;}

  double t_minus = (-1 * d.dot(e_minus_c) - sqrt(discriminant)) / (d.dot(d));
  double t_plus = (-1 * d.dot(e_minus_c) + sqrt(discriminant)) / (d.dot(d));

  if (t_minus < 0 && t_plus < 0) {return false;}

  if (t_minus <= t_plus && t_minus >= 0) {
    t = t_minus;
  }
  else {
    t = t_plus;
  }

  Eigen::Vector3d p = ray.origin + t * ray.direction;
  n = (p - center) / radius;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

