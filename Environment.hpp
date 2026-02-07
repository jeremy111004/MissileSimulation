#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Vector3D.hpp"
#include <random>

class Environment {
private:
  Vector3D m_gravity;
  double m_airDensity;
  Vector3D m_wind;

  std::mt19937 m_rng;
  std::normal_distribution<double> m_dist;

public:
  Environment(Vector3D grav, double air, Vector3D wind);

  Vector3D get_grav() const { return m_gravity; }
  double get_airD() const { return m_airDensity; }
  Vector3D get_wind() const { return m_wind; }

  void stochasticWind(double dt);
  double atmosphericStratification(double z) const;
};
#endif // !E
