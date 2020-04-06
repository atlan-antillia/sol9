/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  NetConnectionProps.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netcon.h>

namespace SOL {

class NetConnectionProps : public ComIDispatch {
public:
  NetConnectionProps(INetConnectionProps* pProps)
    :ComIDispatch(pProps)
  {
  }

private:
  INetConnectionProps* getProps()
  {
    return (INetConnectionProps*) getIDispatch();
  }

public:
  HRESULT getGuid( 
            /* [retval][out] */ BSTR *pbstrGuid)
  {
    HRESULT hr = getProps() -> get_Guid( 
        pbstrGuid);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getGuid()
  {
    BSTR guid = NULL;
    HRESULT hr = getProps() -> get_Guid( 
        &guid);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(guid, false);
  }

public:
  HRESULT getName( 
            /* [retval][out] */ BSTR *pbstrName)
  {
    HRESULT hr = getProps() -> get_Name( 
        pbstrName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  _bstr_t getName()
  {
    BSTR name = NULL;
    HRESULT hr = getProps() -> get_Name( 
        &name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }        

public:
  HRESULT getDeviceName( 
            /* [retval][out] */ BSTR *pbstrDeviceName)
  {
    HRESULT hr = getProps() -> get_DeviceName( 
        pbstrDeviceName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  _bstr_t getDeviceName()
  {
    BSTR name = NULL;
    HRESULT hr = getProps() -> get_DeviceName( 
        &name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }        

public:
  HRESULT getStatus( 
            /* [retval][out] */ NETCON_STATUS *pStatus)
  {
    HRESULT hr = getProps() -> get_Status( 
        pStatus);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  NETCON_STATUS getStatus()
  {
    NETCON_STATUS status;
    HRESULT hr = getProps() -> get_Status( 
        &status);

    if (FAILED(hr)) {
      throw hr;
    }
    return status;
  }        

public:
  HRESULT getMediaType( 
            /* [retval][out] */ NETCON_MEDIATYPE *pMediaType)
   {
    HRESULT hr = getProps() -> get_MediaType( 
        pMediaType);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }       

public:
  NETCON_MEDIATYPE getMediaType()
   {
    NETCON_MEDIATYPE type;
    HRESULT hr = getProps() -> get_MediaType( 
        &type);
    if (FAILED(hr)) {
      throw hr;
    }
    return type;
  }       

public:
  HRESULT getCharacteristics( 
            /* [retval][out] */ DWORD *pdwFlags)
  {
    HRESULT hr = getProps() -> get_Characteristics( 
        pdwFlags);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }        

public:
  DWORD getCharacteristics()
  {
    DWORD flags = 0;
    HRESULT hr = getProps() -> get_Characteristics( 
        &flags);
    if (FAILED(hr)) {
      throw hr;
    }
    return flags;
  }        
    
};
    
}
