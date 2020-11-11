/// @author Ricardo Beltrán Muriel
/// Math Library implementation

#ifndef __MATH_R1_H__
#define __MATH_R1_H__ 1

#include<math.h>

namespace RBM{
  
  struct Vec2{
    float x,y;
  };
   
  struct Vec3{
    float x,y,z;
  };

  struct Vec4{
    float x,y,z,t;
  };
    
    
  struct Mat3{
    float m[9];
  };
    
  struct Transform2{
    Vec2 position;
    float rotation;
    Vec2 scale;
  };
  
  const Vec3 rect_points_c[4]={{0.5f,   0.5f,1.0f},
                             {-0.5f,  0.5f,1.0f},
                             {-0.5f, -0.5f,1.0f},
                             {0.5f,  -0.5f,1.0f},};
                             
  const Vec3 rect_points[4]={{0.0f, 0.0f, 1.0f},
                             {1.0f, 0.0f, 1.0f},
                             {1.0f, 1.0f, 1.0f},
                             {0.0f, 1.0f, 1.0f},};
  //Vec2
  
  Vec2 AddVec2(const Vec2* v1, const Vec2* v2);
   
  //Vec3
  
  Vec3 M3ProductVec3(Mat3 m, Vec3 v);
  void PrintV3(const Vec3* v);

  //Vec4
  
  //Mat2
  
  //Mat3
  
  Mat3  M3Identity();
  Mat3  M3Translate(const float x, const float y);
  Mat3  M3Rotation(const float alfa);
  Mat3  M3Scale(const float sc_x, const float sc_y);
  Mat3  M3Product(Mat3 m1, Mat3 m2);
  
  //Mat4
  
  //Others



}

#endif