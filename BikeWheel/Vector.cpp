#include "Vector.h"

template<typename T>
Vector<T>::Vector() : x(0), y(0), z(0) {};

template<typename T>
Vector<T>& Vector<T>::operator += (const Vector<T>& vect) {
    x += vect.x;
    y += vect.y;
    z += vect.z;
}