#include "first_hit.h"
#include <iostream>
#include <cmath>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //return false;
  bool hit = false;
  double t_cur;
  Eigen::Vector3d n_cur;
  t = std::numeric_limits<double>::max();
  for (int i = 0; i < objects.size(); i ++) { 
    bool b = objects[i]->intersect(ray,min_t,t_cur,n_cur);
    if (b && (t_cur < t)) {
      t = t_cur;
      n = n_cur;
      hit_id = i;
      hit = true;
    }
  }
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

