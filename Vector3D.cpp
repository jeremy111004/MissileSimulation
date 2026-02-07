#include "Vector3D.hpp"
#include <cmath>

double Vector3D::magnitude() const { return std::sqrt(this->dot(*this)); }

Vector3D Vector3D::normalize() const {
  double mag = magnitude();
  if (mag < 1e-10)
    return Vector3D(0.0, 0.0, 0.0);
  return *this * (1 / mag);
}
