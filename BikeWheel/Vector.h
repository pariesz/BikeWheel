#pragma once
#include "arduino.h"

template <typename T>
struct Vector3 {
    T x, y, z;
    
    Vector3<T>() : x(0), y(0), z(0) {};
    Vector3<T>(T x, T y, T z) : x(x), y(y), z(z) {};
};

template <typename T>
struct Vector2 {
    T x, y;

    Vector2<T>() : x(0), y(0) {};
    Vector2<T>(T x, T y) : x(x), y(y) {};
};

