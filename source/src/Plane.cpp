#include "Plane.h"
#include "Ray.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <iostream>

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return false;
  n = normal.normalized();
  double denom = n.dot(ray.direction);

  if (denom == 0) return false;
  
  t = (n.dot(point) - n.dot(ray.origin)) / (denom * 1.0);
  return (t >= min_t);
  ////////////////////////////////////////////////////////////////////////////
}

