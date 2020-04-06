/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SafeArray.h
 *
 *****************************************************************************/

// SOL9
// 2012/10/22

#pragma once

#include <sol\Object.h>
#include <sol\Exception.h>


namespace SOL {

class SafeArray: public Object {
private:
  VARTYPE    varType;  //Used in create method.
  SAFEARRAY* array;

public:
  SafeArray(SAFEARRAY* ar=NULL)
  :array(ar),
  varType(0)
  {
  }

public:
  ~SafeArray()
  {
    clear();
  }

private:
  void clear()
  {
    if (array) {
      SafeArrayDestroy(array);
      array = NULL;
    }
  }

public:
  bool create(VARTYPE vt, unsigned int dims, SAFEARRAYBOUND* bound)
  {
    bool rc = false;
    if (array) {
      throw Exception(0, "SafeArray is already created");
    }

    SAFEARRAY* sa = SafeArrayCreate(vt, dims, bound);
    if (sa) {
      varType = vt;
      array = sa;
      rc = true;
    } else {
      throw Exception(0, "Failed to create SafeArray");
    }
    return rc;
  }

public:
  bool create(VARTYPE vt, long lLbound, unsigned int cElements)
  {
    bool rc = false;
    if (array) {
      throw Exception(0, "SafeArray is already created");
    }

    SAFEARRAY* sa = SafeArrayCreateVector(vt, lLbound, cElements);
    if (sa) {
      varType = vt;
      array = sa;
      rc = true;
    } else {
      throw Exception(0, "Failed to create SafeArray");
    }
    return rc;
  }

public:
  operator SAFEARRAY*()
  {
    return getArray();
  }


public:
  SAFEARRAY* getArray()
  {
    if (array == NULL) {
      throw Exception(0, "SAFEARRAY is NULL");
    } 
    return array;
  }

public:
  VARTYPE getType()
  {
    return varType;
  }

public:
  long getLBound()
  {
    SAFEARRAY* array = getArray();
    long value = 0;
    SafeArrayGetLBound(array, 1, &value); 
    return value;
  }

public:
  long getUBound()
  {
    SAFEARRAY* array = getArray();
    long value = 0;
    SafeArrayGetUBound(array, 1, &value); 
    return value;
  }

public:
  HRESULT accessData(void HUGEP** ppvData)
  {
    SAFEARRAY* array = getArray();
    HRESULT hr = SafeArrayAccessData(array, ppvData); 
    if (FAILED(hr)) {
      throw hr;
    } else {
      return hr;
    }
  }

public:
  HRESULT unaccessData()
  {
    SAFEARRAY* array = getArray();
    HRESULT hr = SafeArrayUnaccessData(array); 
    if (FAILED(hr)) {
      throw hr;
    } else {
      return hr;
    }
  }
public:
  _bstr_t getString(long index)
  {
    SAFEARRAY* array = getArray();

    wchar_t* string = NULL;

    HRESULT hr = SafeArrayGetElement(array, &index, &string);

    if (FAILED(hr)) {
      throw hr;
    }
    else {
      return _bstr_t(string, false);
    }
  }

public:
  _variant_t getElement(long index)
  {
    SAFEARRAY* array = getArray();
        
    VARIANT var;
    VariantInit(&var);

    HRESULT hr = SafeArrayGetElement(array, &index, &var);

    if (FAILED(hr)) {
      throw hr;
    }
    return _variant_t(var, false);
  }


public:
  HRESULT putElement(long* indices, void* pv)
  {
    SAFEARRAY* array = getArray();

    HRESULT hr = SafeArrayPutElement(array, indices, pv);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getDim()
  {
    SAFEARRAY* array = getArray();

    HRESULT hr = SafeArrayGetDim(array);
    return hr;
  }

public:
  HRESULT redim(SAFEARRAYBOUND* psaboundNew)
  {
    SAFEARRAY* array = getArray();
    HRESULT hr = SafeArrayRedim(array, psaboundNew);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT lock()
  {
    SAFEARRAY* array = getArray();

    HRESULT hr = SafeArrayLock(array);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT unlock()
  {
    SAFEARRAY* array = getArray();

    HRESULT hr = SafeArrayUnlock(array);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  SAFEARRAY* copy()
  {
    SAFEARRAY* array = getArray();
    SAFEARRAY* psaOut = NULL;
    HRESULT hr = SafeArrayCopy(array, &psaOut); 
    if (FAILED(hr)) {
      throw hr;
    }
    return psaOut;
  }
  
  //Returns the size (in bytes) of the elements of a safearray.
public:
  UINT getElementSize()
  {
    SAFEARRAY* array = getArray();
    return SafeArrayGetElemsize(array); 
  }

};

}

