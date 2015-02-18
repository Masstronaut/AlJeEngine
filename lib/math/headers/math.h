
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
      vec2()                             noexcept;
      vec2(const float X, const float Y) noexcept;
      vec2(const vec2 &rhs)              noexcept;

      // utility
      void  zero()                          noexcept;
      float length()                  const noexcept;
      vec2  normalize()               const;
      vec2  normal()                        noexcept;
      vec2  rotate(float degrees)           noexcept;
      vec2  rotateRad(float radians)        noexcept;
      float angle(vec2 &rhs)          const noexcept;

      // accessors and mutators
      inline const float  X() const noexcept;
      inline const float  Y() const noexcept;
      inline       float& X()       noexcept;
      inline       float& Y()       noexcept;

      // const operator overloads
      vec2  operator-()                    const noexcept;
      vec2  operator-(const vec2 &rhs)     const noexcept;
      vec2  operator+(const vec2 &rhs)     const noexcept;
      vec2  operator*(const float scalar)  const noexcept;
      float operator*(const vec2 &rhs)     const noexcept;
      vec2  operator/(const float rhs)     const;

      // assignment operators
      vec2& operator+=(const vec2 &rhs)    noexcept;
      vec2& operator+=(const float rhs)    noexcept;
      vec2& operator-=(const vec2 &rhs)    noexcept;
      vec2& operator-=(const float rhs)    noexcept;
      vec2& operator*=(const float scalar) noexcept;

      // comparison operators
      bool operator==(const vec2 &rhs) const noexcept;
      bool operator!=(const vec2 &rhs) const noexcept;

      friend class mat3;

    private:
      // if I want to do point2d in the same struct this makes it easy.
      //vec2(const float X, const float Y, const float W) noexcept;
      float x = 0.f;
      float y = 0.f;
    };
#pragma endregion


#pragma region vec4

    class vec4
    {
    public:
      // accessors
      inline const float  X() const noexcept;
      inline const float  Y() const noexcept;
      inline const float  Z() const noexcept;
      inline const float  W() const noexcept;

      // mutators
      inline       float& X()       noexcept;
      inline       float& Y()       noexcept;
      inline       float& Z()       noexcept;
      inline       float& W()       noexcept;


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
      mat3() noexcept;
      mat3(const vec2 &col1, const vec2 &col2, const vec2 &col3) noexcept;

      // operator overloads
      mat3 operator+(const mat3 &rhs) const noexcept;
      mat3 operator*(const mat3 &rhs) const noexcept;

      // transform a point
      vec2 operator*(const vec2 &rhs) const noexcept;

    private:
      float matrix[3][3];
    };

#pragma endregion

  }; // namespace math



}; // namespace AlJeEngine