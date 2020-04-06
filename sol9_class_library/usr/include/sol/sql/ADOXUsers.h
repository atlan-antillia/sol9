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
 *  ADOXUsers.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/02
#pragma once

#include <sol/sql/ADOCollection.h>
#include <sol/sql/ADOXUser.h>

namespace SOL {

class ADOXUsers :public ADOCollection {

public:
  ADOXUsers()
  {
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADOX::Users));
  }

public:
  void set(__in ADOX::UsersPtr pF) 
  {
    setObject((IDispatchPtr)pF);  
  }

public:
  ADOX::UsersPtr getUsersPtr()
  {
    return (ADOX::UsersPtr)getObject();
  }

public:
  bool getItem(__in const _variant_t& item,
      __out ADOXUser& user)
  {
    bool rc = false;
    ADOX::_UserPtr ptr = getItem(item);
    if (ptr) {
      user.set(ptr);
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s", __FUNCTION__);      
    }
    return rc;
  }

public:
  ADOX::_UserPtr getItem(__in const _variant_t& item)
  {
    return getUsersPtr()->GetItem(item);
  }

public:
  HRESULT append(
    __in const _variant_t& item,
    __in _bstr_t password)
  {
    return getUsersPtr()->Append(
        item,
            password);
  }

public:

  HRESULT remove(
    __in const _variant_t& item)
  {
    return getUsersPtr()->Delete(item);
  }


void dump(ADOX::_Collection *pColl)
{
    IEnumVARIANT *pEnum;
    ULONG lFetched;
    VARIANT var;
    pColl->raw__NewEnum((IUnknown**)&pEnum);// get enumerator object
  int c= 0;
    for ( ; ; )
    {
  printf("%d \n", c++);
    //clear variable which will contain collection item object
        VariantInit(&var);
        // Next method returns IDispatch encapsulated into VARIANT variable
        // if VARIANT type is VT_EMPTY then collection is empty
        pEnum->Next(1, &var, &lFetched);
        if (var.vt== VT_EMPTY) {
    printf("VT_EMPTY %d\n", var.vt);
    break;
  }
        if (var.vt== VT_DISPATCH)
        {
    printf("VT_DISPATCH\n");
            DISPID dspId;
            HRESULT hr;
            OLECHAR *propertyName = L"Name";
            // Since we work with IDispatch interface we need to know DISP_ID 
            //of "Name" property
            hr = var.pdispVal->GetIDsOfNames(IID_NULL, &propertyName, 1, 
                LOCALE_SYSTEM_DEFAULT, &dspId);
            if (SUCCEEDED(hr))
            {
                VARIANT vVal;
                // clear variable which will contain property value
                VariantInit(&vVal);
                DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
                // get property value
                hr = var.pdispVal->Invoke(dspId, IID_NULL, LOCALE_USER_DEFAULT, 
                     DISPATCH_PROPERTYGET,&dispparamsNoArgs, &vVal, NULL, NULL);
                if (SUCCEEDED(hr) && VT_BSTR == vVal.vt)
                {
                    //char ascName[256];
                    //memset(ascName, 0, 256);
                    // convert UNICODE string to ASCII string
                    //WideCharToMultiByte(CP_ACP, 0, vVal.bstrVal, -1, ascName, 256, NULL, NULL);
                   // MessageBox(NULL, ascName, "Name", 0);
      printf("%S\n",  vVal.bstrVal);

                }
            }
            // release collection item object
            var.pdispVal->Release();
        }
        // clear object container variable
        VariantClear(&var);
    }
    // release resources
    pEnum->Release();
    VariantClear(&var);
}

public:
  long getCount()
  {
    long rc = 0;
    //try {    
      rc = getUsersPtr()->GetCount();
    //} catch (_com_error& ex) {
    //  COMError e(ex);
      //e.dump();
    //}
    return rc;
  }

public:
  HRESULT refresh()
  {
    HRESULT hr = getUsersPtr()->Refresh();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    };
    return hr;
  }

public:
  IUnknownPtr newEnum() 
  {
    return   getUsersPtr()->_NewEnum();
  }

public:
  void dump()
  {
    printf("<Users>\n");
    
    long c = getCount();
    for (long i = 0; i<c; i++) {
      ADOXUser user;
      getItem(_variant_t(i), user);
      user.dump();
    }
    printf("</Users>\n");
  }

};

}
