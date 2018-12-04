#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return Eigen::Vector3d(0,0,0);
  Eigen::Vector3d out;
  out = in - 2*(in.dot(n))*n;
  return out;
  ////////////////////////////////////////////////////////////////////////////
}
