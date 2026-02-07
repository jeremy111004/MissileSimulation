#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Environment.hpp"
#include "Vector3D.hpp"
#include <expected>
#include <utility>

enum class mathErrorHandling {
  belowGround,
  mathError

};

class Projectile {
private:
  Vector3D m_position;
  Vector3D m_velocity;
  double m_mass;
  double m_crossSecA;
  double m_magnusCoef;
  Vector3D m_spinVector;
  static constexpr double s_baseCd = 0.2;

public:
  Projectile(Vector3D pos, Vector3D vel, double mass, double croSecA,
             double mCoef, Vector3D spinV)
      : m_position(pos), m_velocity(vel), m_mass(mass), m_crossSecA(croSecA),
        m_magnusCoef(mCoef), m_spinVector(spinV) {};
  double get_x() const { return m_position.x(); }
  double get_y() const { return m_position.y(); }
  double get_z() const { return m_position.z(); }
  void update(double dt, const Environment &env);
  double getCdrag(double s) const;
  std::expected<std::pair<Vector3D, Vector3D>, mathErrorHandling>
  solver(const Vector3D &vel, const Vector3D &pos,
         const Environment &env) const;
};

#endif
