#include "Environment.hpp"
#include "Projectile.hpp"
#include "Vector3D.hpp"
#include <fstream>
#include <iostream>

int main() {
  std::ofstream outFile("trajectory.csv");
  outFile << "time,x,y,z,wind_x,wind_y,wind_z\n";
  std::ofstream landings("landings.csv");
  landings << "x,y\n";

  int numSim{100000};
  double dt = 0.01;

  for (int z = 0; z < numSim; ++z) {
    // Updated Constructor:
    // Position, Velocity, Mass (15kg), Area (0.01m^2), Magnus Coef (0.001),
    // Spin Vector
    Projectile missile(Vector3D(0.0, 0.0, 0.0), Vector3D(50.0, 100.0, 100.0),
                       15.0, 0.01, 0.001, Vector3D(0.0, 0.0, 50.0));

    Environment earth(Vector3D(0.0, 0.0, -9.81), 1.225,
                      Vector3D(5.0, 2.0, 0.0));

    double time = 0.0;
    while (missile.get_z() >= 0 && time < 500) {
      // Log only 1% of trajectories to avoid giant files
      if (z < numSim / 100) {
        outFile << time << "," << missile.get_x() << "," << missile.get_y()
                << "," << missile.get_z() << "," << earth.get_wind().x() << ","
                << earth.get_wind().y() << "," << earth.get_wind().z() << "\n";
      }

      missile.update(dt, earth);
      earth.stochasticWind(dt);
      time += dt;
    }

    // Log up to 1000 landing points for the distribution cloud
    if (z < 1000) {
      landings << missile.get_x() << ',' << missile.get_y() << "\n";
    }
  }

  outFile.close();
  landings.close();
  return 0;
}
