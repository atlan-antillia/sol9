/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  Vector.h
 *
 *****************************************************************************/

//2016/08/10

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

#include <math.h>

namespace SOL {
  
template <class T, size_t SIZE> class Vector {
private:
  T*  value;
  
public:
  Vector()
  :value(new T[SIZE])
  {
    for (int i = 0; i<SIZE; i++) {
      value[i] = (T)0;
    }    
  }

 
  Vector(const T* v, size_t size)
  :value(new T[SIZE])
  {
    set(v, size);
  }

  Vector(const Vector<T, SIZE>& vec)
  :value(new T[SIZE])
  {
    set(vec.getValue(), SIZE);
  }
 
  virtual ~Vector()
  {
    delete [] value;
    value = NULL;
  }

  const T* getValue() const
  {
    return value;
  }
  
  void set(const T* v, int size)
  {
    if (v && size == SIZE) {
      for (int i = 0; i<SIZE; i++) {
        value[i] = v[i];
      }
    } else {
      throw IException("Invalid parameter");
    }
  }
  
  void set(size_t i, const T& c)
  {
    if (i >= 0 && i < SIZE) {
      value[i] = c;
    } else {
      throw IException("Index:out of range, %d", i);
    }
  }


  T  get(size_t i) const
  {
    if (i >= 0 && i < SIZE) {
      return value[i];
    } else {
      throw IException("Index:out of range, %d", i);
    }
  }

  T&  operator[](size_t i) const
  {
    if (i >= 0 && i < SIZE) {
      return value[i];
    } else {
      throw IException("Index:out of range, %d", i);
    }
  }

  void normalize()
  {
    T sq = T(0);
    for (int i = 0; i<SIZE; i++) {
      sq += value[i]*value[i];
    }
    T length = (T)sqrt(sq);
 
    if (length != (T)0) {
      for (int i = 0; i<SIZE; i++) {
        value[i] /= length;
      }
    }
  }

  static T dotProduct(const Vector& v1, const Vector& v2)
  {
    T product = (T)0;
    for (int i = 0; i<SIZE; i++) {
      product += v1[i] * v2[i];
    }
    return product;
  }

  T dotProduct(const Vector& vec) const
  {
    return dotProduct(*this, vec);
  }
   
  Vector operator+(const Vector &vec) const
  {
    T v[SIZE];
    for(int i = 0; i<SIZE; i++) {
      v[i] = value[i] + vec[i];
    }
    return Vector<T, SIZE>(v, SIZE);
  }
 
  void operator+=(const Vector &vec)
  {
    for (int i = 0; i<SIZE; i++) {
      value[i] += vec[i];
    }
  }
 
  Vector operator-(const Vector &vec) const
  {
    T v[SIZE];
    for(int i = 0; i<SIZE; i++) {
      v[i] = value[i] - vec[i];
    }
    return Vector<T, SIZE>(v, SIZE);
  }

  void operator-=(const Vector &vec)
  {
    for (int i = 0; i<SIZE; i++) {
      value[i] -= vec[i];
    }
  }

  Vector operator*(const Vector& vec) const
  {
    T v[SIZE];
    for(int i = 0; i<SIZE; i++) {
      v[i] = value[i] * vec[i];
    }
    return Vector<T, SIZE>(v, SIZE);
  }

  Vector operator*(const T& c) const
  {
    T v[SIZE];
    for(int i = 0; i<SIZE; i++) {
      v[i] = value[i] * c;
    }
    return Vector<T, SIZE>(v, SIZE);
  }
 
  void operator*=(const T& c)
  {
    for (int i = 0; i<SIZE; i++) {
      value[i] *= c;
    }
  }
 
  Vector operator/(const T& c) const
  {
    if (c != (T)0) {
      T v[SIZE];
      for(int i = 0; i<SIZE; i++) {
        v[i] = value[i] /c;
      }
      return Vector<T>(v, SIZE);
    } else {
      throw IException("Invalid parameter."); 
    }
  }
 
  void operator/=(const T& c)
  {
    if (c != (T)0) {
      for (int i = 0; i<SIZE; i++) {
        value[i] /= c;
      }
    } else {
      throw IException("Invalid parameter");
    }
  }
};
 
}

