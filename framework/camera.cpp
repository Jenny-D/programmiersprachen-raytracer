#define _USE_MATH_DEFINES
#include "camera.hpp"
#include <iostream>

float Camera::distance() const {
  // Breite der Ebene auf 1 normieren
  float c = 1;
  // Öffnungswinkel in Bogenmaß umrechnen
  float Y = ((2 * M_PI) / 360) * fov_x_;
  // Seitenlängen berechnen
  float a = (c / (std::sin(Y / 2))) / 2;
  // Entfernung zwischen Koordinatenursprung und Bildebene berechnen
  float d = 0.5 * (std::sqrt((4 * a * a) - (c * c)));

  return d;
}
