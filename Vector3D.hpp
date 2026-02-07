#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <array>

class Vector3D {
private:
  std::array<double, 3> m_data;

public:
  Vector3D(double x, double y, double z) : m_data{x, y, z} {}

  double x() const { return m_data[0]; }
  double y() const { return m_data[1]; }
  double z() const { return m_data[2]; }

  Vector3D operator+(const Vector3D &other) const {
    return Vector3D(m_data[0] + other.m_data[0], m_data[1] + other.m_data[1],
                    m_data[2] + other.m_data[2]);
  }

  Vector3D operator*(double scalar) const {
    return Vector3D(m_data[0] * scalar, m_data[1] * scalar, m_data[2] * scalar);
  }

  Vector3D operator-(const Vector3D &other) const {
    return Vector3D(m_data[0] - other.m_data[0], m_data[1] - other.m_data[1],
                    m_data[2] - other.m_data[2]);
  }

  double magnitude() const;
  Vector3D normalize() const;
  double dot(const Vector3D &other) const {
    return m_data[0] * other.m_data[0] + m_data[1] * other.m_data[1] +
           m_data[2] * other.m_data[2];
  };
};

inline Vector3D operator*(double scalar, const Vector3D &vec) {
  return vec * scalar;
}

inline Vector3D crossProduct(const Vector3D &vec1, const Vector3D &vec2) {
  return Vector3D(vec1.y() * vec2.z() - vec1.z() * vec2.y(),
                  vec1.z() * vec2.x() - vec1.x() * vec2.z(),
                  vec1.x() * vec2.y() - vec1.y() * vec2.x());
}

#endif
