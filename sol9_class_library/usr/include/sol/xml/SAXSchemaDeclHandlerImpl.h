/******************************************************************************
 *
 * Copyright(c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  SAXSchemaDeclHandlerImpl.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/WString.h>

//Implementation class ISAXSchemaDeclHandler COM interface.
//But, this is used to be a C++ class not COM object.
//Therefore we create an instance of this class by ordinary C++ constructor,
// not using ::CoCreateInstance API.

namespace SOL {
//Implementation IDispatch interface.

class SAXSchemaDeclHandlerImpl : public IMXSchemaDeclHandler
{
private:
  long refCount;

public:
  SAXSchemaDeclHandlerImpl()
    :refCount(0)
  {
  }

public:
  ~SAXSchemaDeclHandlerImpl()
  {
  }

private:
  long __stdcall QueryInterface(const struct _GUID & riid, void **ppvObject)   
  {
    //printf("QueryInterface\n");
    HRESULT hr = S_OK;
    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, __uuidof(MSXML2::IMXSchemaDeclHandler) ) ) {
      *ppvObject = reinterpret_cast<MSXML2::IMXSchemaDeclHandler*>(this) ;
    }
    else {
      *ppvObject = NULL;
      hr = E_NOINTERFACE;
    }
    return hr;
  }

  unsigned long __stdcall AddRef(void) 
  { 
    return 0;
  }

  unsigned long __stdcall Release(void) 
  { 
    return 0;
  }

  HRESULT __stdcall GetTypeInfo(
      __in UINT   /*iTInfo*/,
      __in LCID   /*lcid*/,
      __out  ITypeInfo** /*ppTInfo*/)
  {
    return E_NOTIMPL;//E_NOINTERFACE;
  }

  HRESULT __stdcall GetTypeInfoCount(__out UINT* /*pctinfo*/)
  {
    return E_NOTIMPL;//E_NOINTERFACE;
  }


  HRESULT __stdcall GetIDsOfNames(
      __in REFIID    /*riid*/,
      __in LPOLESTR* /*rgszNames*/,
      __in UINT     /*cNames*/,
      __in LCID     /*lcid */,
      __out DISPID* /*rgDispId*/) 
  { 
    return E_NOTIMPL;//E_NOINTERFACE; 
  }

  HRESULT __stdcall Invoke(
      __in DISPID  /*dispIdMember*/,
      __in REFIID  /*riid*/,
      __in LCID    /*lcid*/,
      __in WORD    /*wFlags*/,
      __in DISPPARAMS* /*pDispParams*/,
      __out VARIANT*   /*pVarResult */, 
      __out EXCEPINFO* /*pExcepInfo */,
      __out UINT*      /*puArgErr*/) 
  {
    return E_NOTIMPL;//E_NOINTERFACE; 
  }

private:
  HRESULT __stdcall raw_schemaElementDecl(
    __in struct MSXML2::ISchemaElement * oSchemaElement)
  {
    schemaElementDecl(oSchemaElement);
    return S_OK;
  }

  //Please redefine this method in your own specific class dervide from this class.
public:
  virtual void schemaElementDecl(
    __in struct MSXML2::ISchemaElement* /*oSchemaElement*/)
  {
  }
};

}
