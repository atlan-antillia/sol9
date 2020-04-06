/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ADOObject.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/10
// 2009/06/02 Modified to support ADOX.

#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <comdef.h>
//2009/06/02
#import "C:\Program Files\Common Files\system\ado\msadox.dll"

#import "C:\program files\common files\system\ado\msado15.dll" rename("EOF", "adoEOF")

#include <sol/Object.h>
#include <sol/COMError.h>
#include <sol/ArgT.h>
#include <sol/COMTypeConverter.h>
#include <sol/Exception.h>
#include <sol/sql/ADOEnumNames.h>
//2009/06/05
#include <sol/sql/ADOXEnumNames.h>

namespace SOL {

class ADOObject :public Object {

private:
  IDispatchPtr pDispatch;

protected:
  /**
   * Constrctor
   */
  ADOObject()
  :pDispatch(NULL)
  {
  }

protected:
  /**
   * Constrctor
   */
  ADOObject(REFCLSID classId)
  :pDispatch(NULL)
  {
    createInstance(classId);
  }

protected:
  /**
   * Create an instance of COM class of classId.
   */
  HRESULT createInstance(REFCLSID classId) 
  {
    pDispatch = NULL;

        HRESULT hr = pDispatch.CreateInstance(classId);

    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  /**
   * Create an instance of COM class.This is really a virtual function.
   */
  virtual HRESULT createInstance() 
  {
        HRESULT hr = S_OK;
    
    return hr;
  }

public:
  /**
   * Destructor
   */
  ~ADOObject() 
  {
    clear();
  }

public:
  /**
   * Return a pointer to IDISPATCH.
   * Return the pDispatch member if it's not NULL, else throw E_POINTER
   *
   */
  IDispatchPtr getObject() 
  {
    if (pDispatch !=NULL) {
      return pDispatch;
    } else {
      throw Exception(E_POINTER, "%s: %s", "NULL pointer", __FUNCTION__);
    }
  }

public:
  void clear()
  {
    pDispatch = NULL;
  }

public:
  void setObject(IDispatchPtr ptr)
  {
    pDispatch = NULL;
    pDispatch = ptr;
  }

};

}
