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
 *  ADOXProperties.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/04

#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXProperty.h>

namespace SOL {

class ADOXProperties :public ADOCollection {

public:
  ADOXProperties()
  {
  }


public:
  ~ADOXProperties()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Properties));
  }


public:
  void set(__in ADOX::PropertiesPtr pPs) 
  {
    setObject((IDispatchPtr)pPs);
  }

public:
  ADOX::PropertiesPtr getPropertiesPtr() 
  {
    return (ADOX::PropertiesPtr)getObject();
  }

public:
  bool getItem(__in const _variant_t& index, 
      __out ADOXProperty& prop)
  {
    bool rc = false;
    ADOX::PropertyPtr pProp = getItem(index);
    if (pProp) {
      prop.set(pProp);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s %s", "E_FAIL", __FUNCTION__);
    }
    return rc;
  }

public:
  ADOX::PropertyPtr getItem(__in const _variant_t& index)
  {
    return getPropertiesPtr()->GetItem(index);
  }

public:
  long getCount()
  {
    return getPropertiesPtr()->GetCount();
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getPropertiesPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getPropertiesPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Properties>\n");
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXProperty prop;
      getItem(_variant_t(i), prop);
      prop.dump();
    }
    printf("</Properties>\n");

  }

};

}
