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
 *  ADOXViews.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXView.h>

namespace SOL {

class ADOXViews :public ADOCollection {

public:
  ADOXViews()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Views));
  }

public:
  void set(__in ADOX::ViewsPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }
public:
  ADOX::ViewsPtr getViewsPtr() 
  {
    return (ADOX::ViewsPtr)getObject();  
  }

public:
   bool getItem(
    __in const _variant_t& item,
    __out ADOXView& view)
  {
    bool rc = false;
    ADOX::ViewPtr ptr = getItem(item);
    if (ptr) {
      view.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::ViewPtr getItem(
    __in const _variant_t& item)
  {
    return getViewsPtr()->GetItem(item);

  }

public:
  HRESULT append(
    __in _bstr_t name,
    __in IDispatch* command)
  {
    return getViewsPtr()->Append(
      name,
      command);
  }

public:
  HRESULT remove(
    __in const _variant_t& item)
  {
    return getViewsPtr()->Delete(item);
  }

public:
  long getCount()
  {
    return getViewsPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getViewsPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getViewsPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Views>\n");
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXView view;
      getItem(_variant_t(i), view);
      view.dump();
    }
    printf("</Views>\n");

  }
};

}
