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
 *  SAXXMLAttributes.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/03
// 2015/12/19 Modified SAXXMLAttributes constructor.

#pragma once

#include <sol/xml/XMLObject.h>

// Simple C++ wrapper class to IMXAttributes COM interface.
// IMXAttribues is a list of 'writable'XML attributes.

namespace SOL {

class SAXXMLAttributes :public XMLObject {
private:
  MSXML2::IMXAttributesPtr mxAttributes;

public:
  SAXXMLAttributes()
    :mxAttributes(NULL)
  {
#ifdef XML4    
    mxAttributes.CreateInstance(__uuidof(SAXAttributes)); 
#endif

#ifdef XML6    
    mxAttributes.CreateInstance(__uuidof(SAXAttributes60)); //2015/12/19
#endif
  }

public:
  ~SAXXMLAttributes()
  {
    mxAttributes = NULL;
  }

public:
  IMXAttributesPtr getAttributesPtr()
  {
    return mxAttributes;
  }

public:
  HRESULT addAttribute(__in const _bstr_t name, 
      __in const _bstr_t value)
  {
    return getAttributesPtr()->addAttribute(
      _bstr_t(""), 
      _bstr_t(""), 
      name, 
      _bstr_t(""), 
      value);
  }


  HRESULT addAttribute(
    __in const _bstr_t uri,
    __in const _bstr_t localName,
    __in const _bstr_t qName,
    __in const _bstr_t type,
    __in const _bstr_t value)
  {
    return getAttributesPtr()->addAttribute(
      uri,
      localName,
      qName,
      type,
      value);
  }

  HRESULT addAttributeFromIndex(
    __in const _variant_t & varAtts,
    __in int index)
  {
    return mxAttributes->addAttributeFromIndex(
      varAtts,
      index);
  }

  HRESULT clear()
  {
    return getAttributesPtr()->clear();
  }

  HRESULT removeAttribute(
    int index)
  {
    return getAttributesPtr()->removeAttribute(
      index);
  }

  HRESULT setAttribute(
    __in int index,
    _bstr_t uri,
    _bstr_t localName,
    _bstr_t qName,
    _bstr_t type,
    _bstr_t value)
  {
    return getAttributesPtr()->setAttribute(
      index,
      uri,
      localName,
      qName,
      type,
      value);
  }

  HRESULT setAttributes(
    const _variant_t & varAtts)
  {
    return getAttributesPtr()->setAttributes(
        varAtts);
  }

  HRESULT setLocalName(
    __in int index,
    __in _bstr_t localName)
  {
    return getAttributesPtr()->setLocalName(
      index,
      localName);
  }

  HRESULT setQName(
    __in int index,
    __in _bstr_t qName)
  {
    return getAttributesPtr()->setQName(
      index,
      qName);
  }

  HRESULT setType(
    __in int index,
    __in _bstr_t type)
  {
    return getAttributesPtr()->setType(
      index,
      type);
  }

  HRESULT setURI(
    __in int index,
    __in _bstr_t uri)
  {
    return getAttributesPtr()->setURI(
      index,
      uri);
  }

  HRESULT setValue(
    __in int index,
    __in _bstr_t value)
  {
    return getAttributesPtr()->setValue(
      index,
      value);
  }

public:
  ISAXAttributesPtr getAttributes()
  {
    ISAXAttributesPtr attributes = mxAttributes;
    return attributes;
  }

public:
  operator ISAXAttributes*()
  {
    ISAXAttributesPtr attributes = mxAttributes;
    return(ISAXAttributes*)attributes;
  }
};

}
