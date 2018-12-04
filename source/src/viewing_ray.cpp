#include "viewing_ray.h"
#include <Eigen/Core>
#include <iostream>

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  Eigen::Vector3d eye = camera.e;
  ray.origin = eye;

  double nu = (-0.5 * camera.width) + (camera.width * (j + 0.5)) / width;
  double nv = (0.5 * camera.height) - (camera.height * (i + 0.5)) / height;

  ray.direction = (nu * camera.u + nv * camera.v  - camera.d * camera.w).normalized();
}

