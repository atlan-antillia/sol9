/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SAXContentHandlerImpl.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/WString.h>
#include <sol/xml/SAXLocator.h>

//Implementation class ISAXContentHandler COM interface.
//But, this is used to be a C++ class not COM object.
//Therefore we create an instance of this class by ordinary C++ constructor,
// not using ::CoCreateInstance API.

namespace SOL {

class SAXContentHandlerImpl :public ISAXContentHandler
{

public:
  SAXContentHandlerImpl()
  {
  }

private:
  //Unused. 
  long __stdcall QueryInterface(const struct _GUID &,void ** )   
  { 
    return 0;
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
  HRESULT __stdcall raw_putDocumentLocator(
    __in struct MSXML2::ISAXLocator * pLocator) 
  {
    putDocumentLocator( pLocator);
    return S_OK;
  }

  HRESULT __stdcall raw_startDocument() 
  {
    startDocument();
    return S_OK;
  }

  HRESULT __stdcall raw_endDocument() 
  {
    endDocument();
    return S_OK;
  }

  HRESULT __stdcall raw_startPrefixMapping(
    __in unsigned short * pwchPrefix,
    __in int cchPrefix,
    __in unsigned short * pwchUri,
    __in int cchUri)
  {
    WString pref(pwchPrefix, cchPrefix);
    WString uri(pwchUri, cchUri);
    startPrefixMapping(
      _bstr_t((const wchar_t*)pref),
      _bstr_t((const wchar_t*)uri));
    return S_OK;
  }

  HRESULT __stdcall raw_endPrefixMapping(
    /*[in]*/ unsigned short * pwchPrefix,
    /*[in]*/ int cchPrefix)
  {
    WString pref(pwchPrefix, cchPrefix);
    endPrefixMapping(_bstr_t((const wchar_t*)pref));
    return S_OK;
  }

  HRESULT __stdcall raw_startElement(
    __in unsigned short * pwchNamespaceUri,
    __in int cchNamespaceUri,
    __in unsigned short * pwchLocalName,
    __in int cchLocalName,
    __in unsigned short * pwchQName,
    __in int cchQName,
    __in struct MSXML2::ISAXAttributes * pAttributes)
  {
    WString uri(pwchNamespaceUri, cchNamespaceUri);
    WString localName(pwchLocalName, cchLocalName);
    WString qName(pwchQName, cchQName);
      
    startElement(_bstr_t((const wchar_t*)uri),
      _bstr_t((const wchar_t*)localName),
      _bstr_t((const wchar_t*)qName),
      pAttributes);
    return S_OK;
  }

  HRESULT __stdcall raw_endElement(
    __in unsigned short * pwchNamespaceUri,
    __in int cchNamespaceUri,
    __in unsigned short * pwchLocalName,
    __in int cchLocalName,
    __in unsigned short * pwchQName,
    __in int cchQName)
  {
    WString uri(pwchNamespaceUri, cchNamespaceUri);
    WString localName(pwchLocalName, cchLocalName);
    WString qName(pwchQName, cchQName);

    endElement(_bstr_t((const wchar_t*)uri),
      _bstr_t((const wchar_t*)localName),
      _bstr_t((const wchar_t*)qName) );
    return S_OK;
  }

  HRESULT __stdcall raw_characters(
    __in unsigned short * pwchChars,
    __in int cchChars)
  {
    WString chars(pwchChars, cchChars);

    characters(_bstr_t((const wchar_t*)chars) );
    return S_OK;
  }

  HRESULT __stdcall raw_ignorableWhitespace(
    __in unsigned short* pwchChars,
    __in int cchChars)
  {
    WString chars(pwchChars, cchChars);

    ignorableWhitespace(_bstr_t((const wchar_t*)chars));
    return S_OK;
  }

  HRESULT __stdcall raw_processingInstruction(
    __in unsigned short* pwchTarget,
    __in int cchTarget,
    __in unsigned short* pwchData,
    __in int cchData)
  {
    WString target(pwchTarget, cchTarget);
    WString data(pwchData, cchData);

    processingInstruction(_bstr_t((const wchar_t*)target), _bstr_t((const wchar_t*)data));
    return S_OK;
  }

  HRESULT __stdcall raw_skippedEntity(
    __in unsigned short * pwchName,
    __in int cchName)
  {
    WString name(pwchName, cchName);
    skippedEntity(_bstr_t((const wchar_t*)name));
    return S_OK;
  }

  //Pleae redefine the following methods in your own ContentHandler class derived from this class.
public:
  virtual void putDocumentLocator(
    __in MSXML2::ISAXLocator* /*pLocator*/) 
  {
  }

  virtual void startDocument() 
  {
  }

  virtual void endDocument() 
  {
  }

  virtual void startPrefixMapping(
    __in const _bstr_t /*prefix*/,
    __in const _bstr_t /*uri*/)
  {
  }

  virtual void endPrefixMapping(
    __in const _bstr_t /*prefix*/)
  {
  }

  virtual void startElement(
    __in const _bstr_t /*uri*/,
    __in const _bstr_t /*localName*/,
    __in const _bstr_t /*qName*/,
    __in struct MSXML2::ISAXAttributes* /*pAttributes*/)
  {
  }

  virtual void endElement(
    __in const _bstr_t /*uri*/,
    __in const _bstr_t /*localName*/,
    __in const _bstr_t /*qName*/)
  {
  }

  virtual void characters(
    __in const _bstr_t /*chars*/)
  {
  }

  virtual void ignorableWhitespace(
    __in const _bstr_t  /*chars*/)
  {
  }

  virtual void processingInstruction(
    __in const _bstr_t /*target*/,
    __in const _bstr_t /*data*/)
  {
  }

  virtual void skippedEntity(
    __in const _bstr_t  /*name*/)
  {
  }
};

}
