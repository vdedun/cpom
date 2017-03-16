#ifndef __FLOAT3_H__
#define __FLOAT3_H__

#include <cmath>
#include <iostream>
#include <limits>

namespace cpom
{

/// Type holding a three dimensional coordinate and associated basic operators.
struct Float3
{
    float x;
    float y;
    float z;

    /// Construct a Float3 with x=y=z=n.
    constexpr Float3(float n=0.0f)
    : x(n),
      y(n),
      z(n)
    { }

    /// Construct a Float3 by setting each x,y,z component.
    constexpr Float3(float x, float y, float z)
    : x(x),
      y(y),
      z(z)
    { }

    /// Construct a Float3 from a float[3].
    constexpr Float3(float f[3])
    : x(f[0]),
      y(f[1]),
      z(f[2])
    { }

    /// Fuzzy component-wise comparison to another Float3 with tolerance epsilon.
    bool equalsTo(const Float3 &rhs,
                  const float epsilon=std::numeric_limits<float>::epsilon()) const
    {
        return (*this - rhs).length() < epsilon;
    }

    /// Component-wise equality operator.
    constexpr bool operator==(const Float3 &rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    /// Component-wise inequality operator.
    constexpr bool operator!=(const Float3 &rhs) const
    {
        return !(*this == rhs);
    }

    /// Component-wise addition operator.
    constexpr Float3 operator+(const Float3 &rhs) const
    {
        return Float3(x + rhs.x,
                      y + rhs.y,
                      z + rhs.z);
    }

    /// Component-wise addition operator with a scalar.
    constexpr Float3 operator+(const float rhs) const
    {
        return Float3(x + rhs,
                      y + rhs,
                      z + rhs);
    }

    /// Component-wise subtraction operator.
    constexpr Float3 operator-(const Float3 &rhs) const
    {
        return Float3(x - rhs.x,
                      y - rhs.y,
                      z - rhs.z);
    }

    /// Component-wise subtraction operator with a scalar.
    constexpr Float3 operator-(const float rhs) const
    {
        return Float3(x - rhs,
                      y - rhs,
                      z - rhs);
    }

    /// Component-wise multiplication operator.
    constexpr Float3 operator*(const Float3 &rhs) const
    {
        return Float3(x * rhs.x,
                      y * rhs.y,
                      z * rhs.z);
    }

    /// Component-wise multiplication operator with a scalar.
    constexpr Float3 operator*(const float rhs) const
    {
        return Float3(x * rhs,
                      y * rhs,
                      z * rhs);
    }

    /// Component-wise division operator.
    constexpr Float3 operator/(const Float3 &rhs) const
    {
        return Float3(x / rhs.x,
                      y / rhs.y,
                      z / rhs.z);
    }

    /// Component-wise division operator with a scalar.
    constexpr Float3 operator/(const float rhs) const
    {
        return Float3(x / rhs,
                      y / rhs,
                      z / rhs);
    }

    /// Dot product with another Float3.
    constexpr float dot(const Float3 &rhs) const
    {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }

    /// Return a Float3 with the absolute value of components
    inline Float3 abs() const
    {
        return Float3( std::abs(x), std::abs(y), std::abs(z) );
    }

    /// Square of length of vector x,y,z.
    inline float sqrLength() const
    {
        return this->dot(*this);
    }

    /// Length of vector x,y,z.
    inline float length() const
    {
        return std::sqrt( sqrLength() );
    }

    /// Returns true if any of x,y,z is NaN.
    inline bool hasNan() const
    {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }
};

/// Insertion operator for Float3.
inline std::ostream &operator<<(std::ostream &output, const Float3 &f)
{ 
    output << f.x << "," << f.y << "," << f.z;
    return output;
}

using Point = Float3;

} //namespace cpom

#endif // __FLOAT3_H__

