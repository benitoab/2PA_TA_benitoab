/// @author Javier Benito Abolafio <benitoab@esat-alumni.com>
/// Math Library definition
#ifndef __MATH_H__
#define __MATH_H__ 1

#include <stdio.h>
#include <math.h>

namespace JBA{

	const float PI = 3.14159265359;

  // Vector 2D
	struct Vector2{

		float x, y;
	
	};

  // Vector 3D
  struct Vector3{

		float x, y, z;
	
	};

  // Vector 4D
  struct Vector4{

		float x, y, z, w;
	
	};

  // Matrix 3x3
  struct Matrix3{

    float mat[9];

  };

  // Transform Matrix 3x3
  Matrix3 M3Identity();
  Matrix3 M3Translate(const float x, const float y);
  Matrix3 M3Rotate(float alpha);
  Matrix3 M3Scale(float x, float y);

}

#endif // __MATH_H__