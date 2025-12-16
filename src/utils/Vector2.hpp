/**
 * @file Vector2.hpp
 * @author Joachim Perrin (joachimperrin1@gmail.com)
 * @author Dilhan Emir (dilhan77120@gmail.com)
 * @brief This file contains the definition of the Vector2 class, which is a class that represents a 2D vector.
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include <iostream>

/**
 * @brief The Vector2 class is a class that represents a 2D vector.
 *
 */
class Vector2
{
public:
    Vector2();
    Vector2(float x, float y);

    Vector2 &add(const Vector2 &vec);
    Vector2 &subtract(const Vector2 &vec);
    Vector2 &multiply(const Vector2 &vec);
    Vector2 &divide(const Vector2 &vec);
    float magnitude() const;
    Vector2 Normalized() const;
    Vector2 Project(const Vector2 vec, const Vector2 onto) const;
    Vector2 Normal() const;
    Vector2 Reflect(const Vector2 v, const Vector2 r);

    friend Vector2 operator+(const Vector2 &vec1, const Vector2 &vec2);
    friend Vector2 operator+(const Vector2 &vec, float scalar);
    friend Vector2 operator+(float scalar, const Vector2 &vec);
    friend Vector2 operator+(const Vector2 &vec, int scalar);
    friend Vector2 operator+(int scalar, const Vector2 &vec);

    friend Vector2 operator-(const Vector2 &vec1, const Vector2 &vec2);
    friend Vector2 operator-(const Vector2 &vec, float scalar);
    friend Vector2 operator-(float scalar, const Vector2 &vec);
    friend Vector2 operator-(const Vector2 &vec, int scalar);
    friend Vector2 operator-(int scalar, const Vector2 &vec);

    friend Vector2 operator*(const Vector2 &vec1, const Vector2 &vec2);
    friend Vector2 operator*(const Vector2 &vec, float scalar);
    friend Vector2 operator*(float scalar, const Vector2 &vec);
    friend Vector2 operator*(const Vector2 &vec, int scalar);
    friend Vector2 operator*(int scalar, const Vector2 &vec);

    friend Vector2 operator/(const Vector2 &vec1, const Vector2 &vec2);
    friend Vector2 operator/(const Vector2 &vec, float scalar);
    friend Vector2 operator/(float scalar, const Vector2 &vec);
    friend Vector2 operator/(const Vector2 &vec, int scalar);
    friend Vector2 operator/(int scalar, const Vector2 &vec);

    Vector2 &operator+=(const Vector2 &vec);
    Vector2 &operator-=(const Vector2 &vec);
    Vector2 &operator*=(const Vector2 &vec);
    Vector2 &operator/=(const Vector2 &vec);
    Vector2 &operator*=(float scalar);

    friend bool operator==(const Vector2 &vec1, const Vector2 &vec2);
    friend bool operator!=(const Vector2 &vec1, const Vector2 &vec2);

    Vector2 &zero();
    friend std::ostream &operator<<(std::ostream &stream, const Vector2 &vec);
    float x;
    float y;
};

#endif
