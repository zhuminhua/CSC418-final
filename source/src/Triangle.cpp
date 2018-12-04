#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <iostream>

using namespace std;

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return false;
  // amother implement method
  //e + td = a + β(b − a) + γ(c − a). B R > 0 B + R < 1
  // Eigen::Vector3d e1 = get<1>(corners) - get<0>(corners);
  // Eigen::Vector3d e2 = get<2>(corners) - get<0>(corners);

  // Eigen::Vector3d normal = e1.cross(e2);
  // n = normal / (normal.norm() * 1.0);

  // Eigen::Vector3d q = ray.direction.cross(e2);
  // double a = e1.dot(q);

  // if ((n.dot(ray.direction) >= 0) || (abs(a) < 1e-9)) {
  //   return false;
  // }

  // Eigen::Vector3d s = (ray.origin - get<0>(corners)) / a;
  // Eigen::Vector3d r = s.cross(e1);

  // double b0 = s.dot(q);
  // double b1 = r.dot(ray.direction);
  // double b2 = 1.0f - b0 - b1;

  // if ((b0 < 0.0f) || (b1 < 0.0f) || (b2 < 0.0f)) return false;

  // t = e2.dot(r);
  // return (t >= 0.0f);
  Eigen::Vector3d e1 = get<0>(corners) - get<1>(corners);
  Eigen::Vector3d e2 = get<0>(corners) - get<2>(corners);
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e3 = get<0>(corners) - ray.origin;

  double eihf = e2[1]*d[2] - d[1]*e2[2];
  double gfdi = d[0]*e2[2] - e2[0]*d[2];
  double dheg = e2[0]*d[1] - e2[1]*d[0];
  double akjb = e1[0]*e3[1] - e3[0]*e1[1];
  double jcal = e3[0]*e1[2] - e1[0]*e3[2];
  double blkc = e1[1]*e3[2] - e3[1]*e1[2];
  double M = e1[0]*eihf + e1[1]*gfdi + e1[2]*dheg;

  double T = e2[2]*akjb + e2[1]*jcal + e2[0]*blkc;
  t = - T / M;
  if (t < min_t) return false;

  double R = d[2]*akjb + d[1]*jcal + d[0]*blkc;
  double r = R / M;
  if ((r < 0) || (r > 1)) return false;

  double B = e3[0]*eihf + e3[1]*gfdi + e3[2]*dheg;
  double b = B / M;
  if ((b < 0) || (b > 1-r)) return false;

  Eigen::Vector3d normal = e1.cross(e2);
  //n = normal / (normal.norm() * 1.0);
  n = normal.normalized();
  return true;
 
  ////////////////////////////////////////////////////////////////////////////
}


