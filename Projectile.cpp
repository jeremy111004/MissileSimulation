#include "Projectile.hpp"
#include "Environment.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <expected>
#include <optional>
#include <utility>
double Projectile::getCdrag(double s) const {
  double temp = 288.15 - 0.0065 * m_position.z();
  double soundSpeed = 20.05 * std::sqrt(temp);
  double mach = s / soundSpeed;

  if (mach < 0.8)
    return s_baseCd;
  if (mach < 1.2)
    return s_baseCd + 2.5 * s_baseCd * (mach - 0.8);

  static constexpr double peakCd = 0.2 + 2.5 * 0.2 * (1.2 - 0.8);
  return peakCd * (1.2 / mach);
}
enum class mathErrorHandling {
  belowGround,
  mathError

};
std::expected<std::pair<Vector3D, Vector3D>, mathErrorHandling>
Projectile::solver(const Vector3D &vel, const Vector3D &pos,
                   const Environment &env) const {
  Vector3D gravityForce = m_mass * env.get_grav();
  Vector3D relVel = vel - env.get_wind();
  double speed = relVel.magnitude();
  if (pos.z() < 0) {
    return std::unexpected(mathErrorHandling::belowGround);
  }
  double rho = env.atmosphericStratification(pos.z());
  double currentCd = getCdrag(speed);

  Vector3D Fdrag(0, 0, 0);
  if (speed > 1e-6) {
    double FDragMagn = 0.5 * rho * speed * speed * m_crossSecA * currentCd;
    Fdrag = relVel.normalize() * (-FDragMagn);
  }
  if (m_mass <= 0) {
    return std::unexpected(mathErrorHandling::mathError);
  }

  Vector3D Fmagnus = crossProduct(m_spinVector, relVel) * (rho * m_magnusCoef);
  Vector3D acceleration = (gravityForce + Fdrag + Fmagnus) * (1.0 / m_mass);

  return std::pair<Vector3D, Vector3D>{vel, acceleration};
}

void Projectile::update(double dt, const Environment &env) {
  auto k1 = solver(m_velocity, m_position, env);

  Vector3D v2 = m_velocity + (k1->second * (dt * 0.5));
  Vector3D p2 = m_position + (k1->first * (dt * 0.5));
  auto k2 = solver(v2, p2, env);

  Vector3D v3 = m_velocity + (k2->second * (dt * 0.5));
  Vector3D p3 = m_position + (k2->first * (dt * 0.5));
  auto k3 = solver(v3, p3, env);

  Vector3D v4 = m_velocity + (k3->second * dt);
  Vector3D p4 = m_position + (k3->first * dt);
  auto k4 = solver(v4, p4, env);

  Vector3D combined_vel =
      (k1.first + (k2->first * 2.0) + (k3->first * 2.0) + k4->first) *
      (1.0 / 6.0);
  Vector3D combined_acc =
      (k1->second + (k2->second * 2.0) + (k3->second * 2.0) + k4->second) *
      (1.0 / 6.0);

  m_position = m_position + (combined_vel * dt);
  m_velocity = m_velocity + (combined_acc * dt);
}
