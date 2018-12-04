#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return false;
  // for (int i = 0; i < triangles.size(); i ++) {
  //   if (triangles[i] -> intersect(ray,min_t,t,n) == true) {
  //     return true;
  //   }
  // }
  // return false;
  int hit_id;
  return first_hit(ray,min_t,triangles,hit_id,t,n);
  ////////////////////////////////////////////////////////////////////////////
}



