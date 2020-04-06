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
 *  SAXDTDHandlerImpl.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/WString.h>

//Implementation class ISAXDTDHandler COM interface.
//But, this is used to be a C++ class not COM object.
//Therefore we create an instance of this class by ordinary C++ constructor,
// not using ::CoCreateInstance API.

namespace SOL {

class SAXDTDHandlerImpl : public ISAXDTDHandler
{
public:
  SAXDTDHandlerImpl()
  {
  }

private:
  long __stdcall QueryInterface(const struct _GUID & /*riid*/, void ** /*ppObject*/)   
  {
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
  virtual HRESULT __stdcall raw_notationDecl(
    __in  unsigned short * pwchName,
    __in int cchName,
    __in unsigned short * pwchPublicId,
    __in int cchPublicId,
    __in unsigned short * pwchSystemId,
    __in int cchSystemId)
  {
    WString wname(pwchName, cchName);
    WString wpublicId(pwchPublicId, cchPublicId);
    WString wsystemId(pwchSystemId, cchSystemId);

    notationDecl(
      _bstr_t((const wchar_t*)wname),
      _bstr_t((const wchar_t*)wpublicId),
      _bstr_t((const wchar_t*)wsystemId));

    return S_OK;
  }

  virtual HRESULT __stdcall raw_unparsedEntityDecl(
    __in unsigned short * pwchName,
    __in int cchName,
    __in unsigned short * pwchPublicId,
    __in int cchPublicId,
    __in unsigned short * pwchSystemId,
    __in int cchSystemId,
    __in unsigned short * pwchNotationName,
    __in int cchNotationName)
  {
    WString wname(pwchName, cchName);
    WString wpublicId(pwchPublicId, cchPublicId);
    WString wsystemId(pwchSystemId, cchSystemId);
    WString wnotationName(pwchNotationName, cchNotationName);

    unparsedEntityDecl(
      _bstr_t((const wchar_t*)wname),
      _bstr_t((const wchar_t*)wpublicId),
      _bstr_t((const wchar_t*)wsystemId),
      _bstr_t((const wchar_t*)wnotationName));
    return S_OK;
  }


public:
  virtual void notationDecl(
    __in const _bstr_t name,
    __in const _bstr_t publicId,
    __in const _bstr_t systemId)
  {
  }

public:
  virtual void unparsedEntityDecl(
    __in const _bstr_t name,
    __in const _bstr_t publicId,
    __in const _bstr_t systemId,
    __in const _bstr_t notationName)
  {
  }
};

}
