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
 *  NetSharingPortMappingProps.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netcon.h>


namespace SOL {

class NetSharingPortMappingProps : public ComIDispatch
{
public:
  NetSharingPortMappingProps(INetSharingPortMappingProps* pProps=NULL)
    :ComIDispatch(pProps)
  {
  }

private:
  INetSharingPortMappingProps* getProps()
  {
    return (INetSharingPortMappingProps*) getIDispatch();
  }

public:
  _bstr_t getName()
  {
    BSTR name = NULL;
    HRESULT hr = getProps() -> get_Name(&name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(bstr, false);
  }


  UCHAR getIPProtocol()
  {
    UCHAR protocol = 0;
    HRESULT hr = getProps() -> get_IPProtocol(&protocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return protocol;
  }
        

  long getExternalPort()
  {
    long port = 0;
    HRESULT hr = getProps() -> get_ExternalPort(&port);
    if (FAILED(hr)) {
      throw hr;
    }
    return port;
  }
        

  long getInternalPort()
  {
    long port = 0;
    HRESULT hr = getProps() -> get_InternalPort(&port);
    if (FAILED(hr)) {
      throw hr;
    }
    return port;
  }
        

  long getOptions()
  {
    long options = 0;
    HRESULT hr = getProps() -> get_Options(options);
    if (FAILED(hr)) {
      throw hr;
    }
    return options;
  }
        

  _bstr_t getTargetName()
  {
    BSTR name = NULL;
    HRESULT hr = getProps() -> get_TargetName(&name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }
        

  _bstr_t getTargetIPAddress()
  {
    BSTR address = NULL;
    HRESULT hr = getProps() -> get_TargetIPAddress(&address);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(address, false);
  }
        

  bool getEnabled()
  {
    VARIANT_BOOL vbool = VARIANT_FALSE;
    HRESULT hr = getProps() -> get_Enabled(&vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }
        
    
};
    
}
