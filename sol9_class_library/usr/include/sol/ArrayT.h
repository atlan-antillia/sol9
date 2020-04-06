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
 *  ArrayT.h
 *
 *****************************************************************************/

//2014/12/09 Modified the size of array to be automatically expanded.
//2016/08/10 Modified to use __compar_fn_t in sort method.
#pragma once

#include <sol/Object.h>
#include <sol/Sortable.h>
#include <sol/Exception.h>

typedef int (*__compar_fn_t) (const void *, const void *);

namespace SOL {
  
template <class T> class ArrayT :public Object, public Sortable {

private:
  size_t  capacity;
  size_t  size;
  T*      array;
 
private:
  bool copy(const ArrayT& arr)
  {
    const T* ar = arr.array;
    const size_t size = arr.size;

    assert(ar);
    assert(size>0);

    bool rc = false;
    T* temp = new T[size];
    if(temp) {
      for(size_t i = 0; i<size; i++) {
        temp[i] = ar[i];
      }

      if(this->array != ar && this->array !=NULL) {
        clear();
      }
      this->array = temp;
      this->size = size;
      this->capacity = size;
    	
      rc = true;
    } else {
      Exception("Failed to allocate a memory").display();
      assert(temp == NULL);
      //Memory allocation error.
    }
    return rc;
  }

  void clear()
  {
    if (this->array) {
      delete [] this->array;
    }
    this->array =NULL;

    this->size  = 0;
    this->capacity = 0;
  }

  static bool memcpy(T* dest, size_t dlen, T* src, size_t slen)
  //memcpy(T* dest, size_t dlen, T* src, size_t slen)
  {
    bool rc = true;
    if (dest && src && dlen >=slen && dlen >0) {
      for (size_t i = 0; i<slen; i++) {
        dest[i] = src[i];
      }
    } else {
      throw IException("Invalid argument");
    }
    return rc;
  }

  static bool memset(T* dest, T value, size_t len)
  {
    bool rc = true;
    if (dest && len >0) {
      for (size_t i = 0; i<len; i++) {
        dest[i] = value;
      }
    } else {
      throw IException("Invalid argument");
    }
    return rc;
  }

  //static comparison methods
protected:
  static  int compare(const T* a, const T* b)
  {
    if (*a == *b) {
      return 0;
    } else {
      if (*a < *b) {
        return -1;
      } else {
        return 1;
      }
    }
  }

protected:
  static  int _compare(const T* a, const T* b)
  {
    return -compare(a, b);
  }


protected:
  virtual void getFormat(char* format, size_t size, size_t v)
  {
    assert(format);
    assert(size>=128);
    _snprintf_s(format, size, _TRUNCATE , "%%0%dx ", v*2);
  }

private:
  //2014/12/09
  static  const int DEFAULT_SIZE   = 100;

  static  const int AUTO_INCREMENT = 100;

////////////////////////////////////////////////////////////////////////
public:
  /**
   * Constructor
   */
  ArrayT()
  :capacity(DEFAULT_SIZE),
  size(DEFAULT_SIZE),
  array(NULL)
  {
    array = new T[size]; //2015/05/13 
  }

  /**
   * Constructor
   */
  ArrayT(T* ar, size_t s)
  :capacity(s),
  size(s),
  array(NULL)
  {
    deepCopy(ar, size);
  }

  /**
   * Constructor
   */
  ArrayT(const ArrayT* arr)
  :size(0),
  array(NULL)
  {
    if (arr) {
      assert(arr);
      copy(*arr);
    }
  }

  /**
   * Constructor
   */
  ArrayT(const ArrayT& arr)
  :size(0),
  array(NULL)
  {
    copy(arr);
  }

  /**
   * Destructor
   */
  ~ArrayT()
  {
    clear();
  }
  
  const T*   getArray()
  {
    return this->array;
  }
  

//ISO C++ says that these are ambiguous,even though the worst conversion for the 
//first is better than the worst conversion for the second:
// 2014/12/11 commented out the following operator to avoid the above warning.
/*
  operator const T*() const
  {
    return this->array;
  }
*/
  const T* getData() const
  {
    return this->array;
  }

  size_t getSize() const
  {
    return this->size;
  }

  bool isEmpty()
  {
    bool rc = false
    if (this->size==0 || this->array ==NULL) {
      rc = true;
    }
    return rc;
  }

  void deepCopy(T* arr, size_t s)
  {
    assert(arr);
    assert(s > 0);
    if (this->array != arr) {
      clear();
    }
    this->size = s;
    this->capacity = s;
    this->array = new T[this->size];
    for(size_t i = 0; i<this->size; i++) {
      this->array[i] = arr[i];
    }
  }

  void shallowCopy(T* arr, size_t s)
  {
    assert(arr);
    assert(s>0);

    if (this->array != arr) {
      clear();
    }
    this->array   = arr;
    this->size = s;
  	this->capacity = s;
  }


  ArrayT& operator=(const ArrayT& array)
  {
    if (copy(array) == false) {
      throw IException("Failed to copy an array");
    }
    return *this;
  }

  bool operator==(const ArrayT& arr)
  {
     bool rc = false;

    if (this->array != NULL) {
      size_t s1 = this->size;
      const size_t s2 = arr.getSize();
      const T* data = (const T*)arr;
      if (s1 != s2) {
        return false;
      } else {
        rc = true;
        for(size_t i = 0; i<this->size; i++) {
          if ( this->array[i] != data[i]) {
            rc = false;
            break;
          }
        }
      }
    }
    return rc;
  }

  bool memcpy(size_t pos, const T* data, size_t len)
  {
    bool rc = true;
    if (pos >=0 && data != NULL && (pos + len)<=size) {
      for (size_t i = 0; i<len; i++) {
        array[pos + i] = data[i];
      }
    } else {
      throw IException("Invalid argument");
    }
    return rc;
  }

  bool resize(size_t len)
  {
    bool rc = false;
    if (len <= 0) {
      throw IException("Invalid argument");
    }
    size_t nlen =  len;
    T* temp = new T[nlen];

    if(temp) {
     	for (size_t i = 0; i<nlen; i++) {
     		temp[i] = (T)NULL;
    	}
      //memset(temp, (T)0, nlen);
      //memcpy(temp, nlen, this->array, this->size);
    	for (size_t n = 0; n< this->size; n++) {
    	  temp[n] = array[n];
    	}
    } else {
      return rc;
    }
    this -> size = nlen;
    this -> capacity = nlen;
  	
    delete [] this->array;
    this -> array = temp;
    rc = true;

    return rc;
  }

  T&  operator[](size_t pos)
  {
    if (pos>=0 && pos < size) {
      //2015/05/12
      if (array == NULL) {
        array = new T[size];
      }
      return array[pos];
     
    } else if (pos >= size) {
      //2014/12/09
      resize( pos + AUTO_INCREMENT);
      //size = pos;
    
      return array[pos];	
    } else {
      throw IException("Index:out of range, %d", pos);
    }
  }


  T&  at(size_t pos)
  {
    if (pos>=0 && pos < size) {
      //2015/05/12
      if (array == NULL) {
         array = new T[size]; 
      }
      return array[pos];
      
    } else if (pos >= size) {
      //2014/12/09
      resize( pos + AUTO_INCREMENT);
      //size = pos;
    	
      return array[pos];	
    } else {
      throw IException("Index:out of range, %d", pos);
    }
  }
	
  T  getNth(size_t pos)
  {
    T val = (T)0;
    if(pos>=0 && pos < size) {
      if (array == NULL) {
         array = new T[size];
      }
      val = array[pos];
    } else {

    	throw IException("Position: out of range, %d", pos);
    }
    return val;
  }

  void   setNth(size_t pos, T value)
  {
    if(pos>=0 && pos < size) {
      //2015/05/12
      if (array == NULL) {
        array = new T[size];
      }
      array[pos] = value;
    } else if (pos >= size) {
      //2014/12/09
      resize( pos + AUTO_INCREMENT);
      array[pos] = value;	
    } else {
      throw IException("Index:out of range, %d", pos);
    }
  }

  void sort(Sortable::SortDirection direction= ASCENDING)
  {
    if (direction == Sortable::ASCENDING) {
      ::qsort(array, size, sizeof(T), (__compar_fn_t) ArrayT<T>::compare) ;
    } else {
      ::qsort(array, size, sizeof(T), (__compar_fn_t) ArrayT<T>::_compare) ;
    }
  }

  void remove(int index)
  {
    if (index >= 0 && index <size) {
      for (int i = index; i<size-1; i++) {
        array[i] = array[i+1]; 
      }
    }
  }

};

}
