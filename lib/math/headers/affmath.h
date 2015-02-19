
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once

#include <cmath>
#include <cassert>

// Defines are wrapped in parenthesis to prevent precedence issues when expansions are evaluated.
#define __PI__      (4.0f   * atan(1.0f))
#define __TAU__     (8.0f   * atan(1.0f))
#define __DEG2RAD__ (__PI__ / 180.0f    )
#define __RAD2DEG__ (180.f  / __PI__    )

namespace AlJeEngine
{
  namespace Math
  {
    typedef unsigned char byte;

    enum coordType
    {
      Vector2D,
      Point2D
    };

#pragma region vec2
    class vec2
    {
    public:
      /*****************************************************************************/
      /***************************** Constructors **********************************/
      /*****************************************************************************/
      vec2()                              ;
      vec2(const float X, const float Y)  ;
      vec2(const vec2 &rhs)               ;

      // utility
      void  zero()                           ;
      float length()                  const  ;
      vec2  normalize()               const;
      vec2  normal()                         ;
      vec2  rotate(float degrees)            ;
      vec2  rotateRad(float radians)         ;
      float angle(vec2 &rhs)          const  ;

      // accessors and mutators
      inline const float  X() const  ;
      inline const float  Y() const  ;
      inline       float& X()        ;
      inline       float& Y()        ;

      // const operator overloads
      vec2  operator-()                    const  ;
      vec2  operator-(const vec2 &rhs)     const  ;
      vec2  operator+(const vec2 &rhs)     const  ;
      vec2  operator*(const float scalar)  const  ;
      float operator*(const vec2 &rhs)     const  ;
      vec2  operator/(const float rhs)     const;

      // assignment operators
      vec2& operator+=(const vec2 &rhs)     ;
      vec2& operator+=(const float rhs)     ;
      vec2& operator-=(const vec2 &rhs)     ;
      vec2& operator-=(const float rhs)     ;
      vec2& operator*=(const float scalar)  ;

      // comparison operators
      bool operator==(const vec2 &rhs) const  ;
      bool operator!=(const vec2 &rhs) const  ;

      friend class mat3;

    private:
      // if I want to do point2d in the same struct this makes it easy.
      //vec2(const float X, const float Y, const float W)  ;
      float x = 0.f;
      float y = 0.f;
    };
#pragma endregion


#pragma region vec4

    class vec4
    {
    public:
      // accessors
      inline const float  X() const  ;
      inline const float  Y() const  ;
      inline const float  Z() const  ;
      inline const float  W() const  ;

      // mutators
      inline       float& X()        ;
      inline       float& Y()        ;
      inline       float& Z()        ;
      inline       float& W()        ;


    private:
      float x;
      float y;
      float z;
      float w;
    };
#pragma endregion

#pragma region colorVec
    struct colorVec
    {
      byte r = 0;
      byte g = 0;
      byte b = 0;
      byte a = 255;


    };
#pragma endregion

#pragma region mat3
    class mat3
    {
    public:

      // constructors
      // this intentionally doesn't initialize values for speed.
      mat3()  ;
      mat3(const vec2 &col1, const vec2 &col2, const vec2 &col3)  ;

      // operator overloads
      mat3 operator+(const mat3 &rhs) const  ;
      mat3 operator*(const mat3 &rhs) const  ;

      // transform a point
      vec2 operator*(const vec2 &rhs) const  ;

    private:
      float matrix[3][3];
    };

#pragma endregion

  }; // namespace math



}; // namespace AlJeEngine