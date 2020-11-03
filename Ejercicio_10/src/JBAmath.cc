/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Math Library implementation
#include "JBAmath.h"

// Matrix 3 Identity
JBA::Matrix3 JBA::M3Identity() {

  JBA::Matrix3 m = {1, 0, 0,
                    0, 1, 0,
                    0, 0, 1};

  return m;

}

// Translates a Matrix 3 of points to another location
JBA::Matrix3 JBA::M3Translate(const float x, const float y) {

  JBA::Matrix3 m = JBA::M3Identity();

  m.mat[6] = x;
  m.mat[7] = y;

  return m;

}

// Rotates a Matrix 3 of points around a given one
JBA::Matrix3 JBA::M3Rotate(float alpha) {

  JBA::Matrix3 m = {(float)cos(alpha), (float)sin(alpha), 0,
                    (float)-sin(alpha), (float)cos(alpha), 0,
                    0, 0, 1};

  return m;

}

// Scales a Matrix 3 of points with a size given
JBA::Matrix3 JBA::M3Scale(float x, float y) {

  JBA::Matrix3 m = JBA::M3Identity();

  m.mat[0] = x;
  m.mat[4] = y;

  return m;

}