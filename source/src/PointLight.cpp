#include "PointLight.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  Eigen::Vector3d light = p - q;
  d = light.normalized();
  max_t = light.norm();

}
