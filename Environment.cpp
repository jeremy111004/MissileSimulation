#include "Environment.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <iostream>
#include <random>

Environment::Environment(Vector3D grav, double air, Vector3D wind)
    : m_gravity(grav), m_airDensity(air), m_wind(wind),
      m_rng(std::random_device{}()), m_dist(0.0, 1.0) {}

void Environment::stochasticWind(double dt) {
  // Now we just pull numbers from the existing engine
  double nx = m_dist(m_rng);
  double ny = m_dist(m_rng);
  double nz = m_dist(m_rng);

  double sigma = 10;
  double step = sigma * std::sqrt(dt);

  m_wind = Vector3D(m_wind.x() + nx * step, m_wind.y() + ny * step,
                    m_wind.z() + nz * step);
};
double Environment::atmosphericStratification(double z) const {
  double rho = 1.225; // sea level density
  double H = 8500.0;  // earth scale height
  if (z < 0) {
    return rho;
  }
  return rho * std::exp(-z / H);
};
