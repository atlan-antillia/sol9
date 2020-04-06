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
 *  SAXAttributes.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once
#include <sol/xml/XMLObject.h>
#include <sol/WString.h>

// Simple C++ wrapper class to ISAXAttributes.
// SAXAttribute is a list of 'readonly' XMLf attributes

namespace SOL {

class SAXAttributes : public XMLObject {
private:
  MSXML2::ISAXAttributesPtr pAttributes;

public:
  SAXAttributes(MSXML2::ISAXAttributes* attr)
    :pAttributes(attr)
  {
  }

public:
  ~SAXAttributes()
  {
    pAttributes = NULL;
  }

public:
  MSXML2::ISAXAttributesPtr getAttributesPtr()
  {
    if (pAttributes == NULL) {
      throw Exception(E_FATAL, "Error: SAXAttributes is NULL");
    }
    return pAttributes;
  }
  int getLength()
  {
    return getAttributesPtr() -> getLength();
  }

  HRESULT getURI(
    __in int nIndex,
    __out _bstr_t& url)
  {
    unsigned short* pwchUrl = NULL;
    int    cchUrl = 0;
    HRESULT hr = getAttributesPtr() -> getURI(nIndex, &pwchUrl, &cchUrl);
    if(SUCCEEDED(hr)) {
      WString wurl(pwchUrl, cchUrl);
      url =(const wchar_t*)wurl;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getLocalName(
    __in int nIndex,
    __out _bstr_t& localName)
  {
    unsigned short* pwchLocalName = NULL;
    int    cchLocalName = 0;
    HRESULT hr = getAttributesPtr() -> getLocalName(nIndex, &pwchLocalName, &cchLocalName);
    if(SUCCEEDED(hr)) {
      WString wlocalName(pwchLocalName, cchLocalName);
      localName =(const wchar_t*)wlocalName;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getQName(
    __in int nIndex,
    __out _bstr_t& qName)
  {
    unsigned short* pwchQName = NULL;
    int    cchQName = 0;
    HRESULT hr = getAttributesPtr() -> getQName(nIndex, &pwchQName, &cchQName);
    if(SUCCEEDED(hr)) {
      WString wqName(pwchQName, cchQName);
      qName =(const wchar_t*)wqName;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getName(
    __in int nIndex,
    __out _bstr_t& url,
    __out _bstr_t& localName,
    __out _bstr_t& qName)
  {
    unsigned short* pwchUrl = NULL;
    int    cchUrl = 0;

    unsigned short* pwchLocalName = NULL;
    int    cchLocalName = 0;

    unsigned short* pwchQName = NULL;
    int    cchQName = 0;
    HRESULT hr = getAttributesPtr() -> getName(nIndex, 
        &pwchUrl, &cchUrl,
        &pwchLocalName, &cchLocalName, 
        &pwchQName, &cchQName);
    if(SUCCEEDED(hr)) {
      WString wurl(pwchUrl, cchUrl);
      WString wlocalName(pwchLocalName, cchLocalName);
      WString wqName(pwchQName, cchQName);
      url =(const wchar_t*)wurl;
      localName =(const wchar_t*)wlocalName;
      qName =(const wchar_t*)wqName;

    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  int getIndexFromName(
    __in const _bstr_t url,
    __in const _bstr_t localName)
  {
    return getAttributesPtr() -> getIndexFromName(toShort(url), url.length(),
      toShort(localName), localName.length());
  }


  int getIndexFromQName(__in const _bstr_t qName)
  {
    return getAttributesPtr() -> getIndexFromQName(toShort(qName), qName.length());
  }

  HRESULT getType(
    __in int nIndex,
    __out _bstr_t& type)
  {
    unsigned short* pwchType = NULL;
    int    cchType = 0;
    HRESULT hr = getAttributesPtr() -> getType(nIndex, &pwchType, &cchType);
    if(SUCCEEDED(hr)) {
      WString wtype(pwchType, cchType);
      type =(const wchar_t*)wtype;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getTypeFromName(
    __in const _bstr_t url,
    __in const _bstr_t localName,
    __out _bstr_t& type)
  {
    unsigned short* pwchType = NULL;
    int    cchType = 0;
    HRESULT hr = getAttributesPtr() -> getTypeFromName(toShort(url), url.length(),
        toShort(localName), localName.length(),
        &pwchType, &cchType);
    if(SUCCEEDED(hr)) {
      WString wtype(pwchType, cchType);
      type =(const wchar_t*)wtype;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getTypeFromQName(
    __in const _bstr_t qName,
    __out _bstr_t& type)
  {
    unsigned short* pwchType = NULL;
    int    cchType = 0;
    HRESULT hr = getAttributesPtr() -> getTypeFromQName(toShort(qName), qName.length(),
        &pwchType, &cchType);
    if(SUCCEEDED(hr)) {
      WString wtype(pwchType, cchType);
      type =(const wchar_t*)wtype;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getValue(
    __in int nIndex,
    __out _bstr_t& value)
  {
    unsigned short* pwchValue = NULL;
    int    cchValue = 0;
    HRESULT hr = getAttributesPtr() -> getValue(nIndex, &pwchValue, &cchValue);
    if(SUCCEEDED(hr)) {
      WString wvalue(pwchValue, cchValue);
      value =(const wchar_t*)wvalue;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getValueFromName(
    __in const _bstr_t url,
    __in const _bstr_t localName,
    __out _bstr_t& value)
  {
    unsigned short* pwchValue = NULL;
    int    cchValue = 0;
    HRESULT hr = getAttributesPtr() -> getValueFromName(toShort(url), url.length(),
        toShort(localName), localName.length(),
        &pwchValue, &cchValue);
    if(SUCCEEDED(hr)) {
      WString wvalue(pwchValue, cchValue);
      value =(const wchar_t*)wvalue;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

  HRESULT getValueFromQName(
    __in const _bstr_t qName,
    __out _bstr_t& value)
  {
    unsigned short* pwchValue = NULL;
    int    cchValue = 0;
    HRESULT hr = getAttributesPtr() -> getValueFromQName(toShort(qName), qName.length(),
      &pwchValue, &cchValue);
    if(SUCCEEDED(hr)) {
      WString wvalue(pwchValue, cchValue);
      value =(const wchar_t*)wvalue;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

public:
  virtual void display()
  {
    int len = getLength();
    if(len <1) {
      return;
    }

    for(int i = 0; i<len; i++) {
      try {
        _bstr_t qName= L"";
        _bstr_t value = L"";
        getQName(i, qName);

        getValue(i, value);
        printf(" %S=\"%S\"",(const wchar_t*)qName,(const wchar_t*)value);
      } catch(HRESULT hr) {
        printf("Exception SAXAttributes::display HRESULT=0x%08x\n", hr);
      } catch(...) {
        printf("Exception SAXAttributes::display\n");
      }
    }
  }
};

}
