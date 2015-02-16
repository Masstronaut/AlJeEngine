


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
    enum coordType
    {
      Vector2D,
      Point2D
    };

    class vec2
    {
    public:
      /*****************************************************************************/
      /***************************** Constructors **********************************/
      /*****************************************************************************/
      vec2() noexcept;
      vec2(const float X, const float Y, coordType = Vector2D) noexcept;

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


    private:
      // if I want to do point2d in the same struct this makes it easy.
      //vec2(const float X, const float Y, const float W) noexcept;
      float x = 0;
      float y = 0;
      float w = 0;



    };







  };



};