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
 *  SAXDeclHandlerImpl.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/WString.h>

//Implementation class ISAXDecltHandler COM interface.
//But, this is used to be a C++ class not COM object.
//Therefore we create an instance of this class by ordinary C++ constructor,
// not using ::CoCreateInstance API.

namespace SOL {

class SAXDeclHandlerImpl : public ISAXDeclHandler 
{
public:
  SAXDeclHandlerImpl()
  {
  }

private:
  //ISAXXMLReader::putProprty calls this method.
  //SAXDeclHandlerImpl is a C++ class but pretends to be a COM object by 
  //implementing QueryInterface method.
  long __stdcall QueryInterface(const struct _GUID & riid, void **ppObject)   
  {
    if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, __uuidof(MSXML2::ISAXDeclHandler))) {
      *ppObject = static_cast<MSXML2::ISAXDeclHandler*>(this);
    } else {
      *ppObject = NULL;
      return E_NOINTERFACE;
    }
    return S_OK;
  }

  unsigned long __stdcall AddRef(void) 
  { 
    return 0;
  }

  unsigned long __stdcall Release(void) 
  { 
    return 0;
  }

private:
  HRESULT __stdcall raw_elementDecl(
    __in unsigned short * pwchName,
    __in int cchName,
    __in unsigned short * pwchModel,
    __in int cchModel)
  {
    WString wname(pwchName, cchName);
    WString wmodel(pwchModel, cchModel);

    elementDecl(
      _bstr_t((const wchar_t*)wname),
      _bstr_t((const wchar_t*)wmodel));
    return S_OK;
  }

  HRESULT __stdcall raw_attributeDecl(
    __in unsigned short * pwchElementName,
    __in int cchElementName,
    __in unsigned short * pwchAttributeName,
    __in int cchAttributeName,
    __in unsigned short * pwchType,
    __in int cchType,
    __in unsigned short * pwchValueDefault,
    __in int cchValueDefault,
    __in unsigned short * pwchValue,
    __in int cchValue) 
  {
    WString welementName(pwchElementName, cchElementName);
    WString wattributeName(pwchAttributeName, cchAttributeName);
    WString wtype(pwchType, cchType);
    WString wvalueDecl(pwchValueDefault, cchValueDefault);
    WString wvalue(pwchValue, cchValue);

    attributeDecl(
      _bstr_t((const wchar_t*)welementName),
      _bstr_t((const wchar_t*)wattributeName),
      _bstr_t((const wchar_t*)wtype),
      _bstr_t((const wchar_t*)wvalueDecl),
      _bstr_t((const wchar_t*)wvalue));
    return S_OK;
  }

  HRESULT __stdcall raw_internalEntityDecl(
    __in unsigned short * pwchName,
    __in int cchName,
    __in unsigned short * pwchValue,
    __in int cchValue) 
  {
    WString wname(pwchName, cchName);
    WString wvalue(pwchValue, cchValue);

    internalEntityDecl(
      _bstr_t((const wchar_t*)wname),
      _bstr_t((const wchar_t*)wvalue)
      );
    return S_OK;
  }

  HRESULT __stdcall raw_externalEntityDecl(
    __in unsigned short * pwchName,
    __in int cchName,
    __in unsigned short * pwchPublicId,
    __in int cchPublicId,
    __in unsigned short * pwchSystemId,
    __in int cchSystemId) 
  {
    WString wname(pwchName, cchName);
    WString wpublicId(pwchPublicId, cchPublicId);
    WString wsystemId(pwchSystemId, cchSystemId);

    externalEntityDecl(
      _bstr_t((const wchar_t*)wname),
      _bstr_t((const wchar_t*)wpublicId),
      _bstr_t((const wchar_t*)wsystemId));
    return S_OK;
  }

public:
  virtual void elementDecl(
    __in const _bstr_t name,
    __in const _bstr_t model)
  {
  }

  virtual void attributeDecl(
    __in const _bstr_t elementName,
    __in const _bstr_t attributeName,
    __in const _bstr_t type,
    __in const _bstr_t valueDefault,
    __in const _bstr_t value)
  {
  }

  virtual void internalEntityDecl(
    __in const _bstr_t name,
    __in const _bstr_t value)
  {
  }

  virtual void externalEntityDecl(
    __in const _bstr_t name,
    __in const _bstr_t publicId,
    __in const _bstr_t systemId)
  {
  }

};

}

 
