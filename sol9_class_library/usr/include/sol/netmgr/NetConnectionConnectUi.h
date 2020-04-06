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
 *  NetConnectionConnectUi.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIUnknown.h>
#include <netcon.h>

namespace SOL {

class NetConnectionConnectUi: public ComIUnknown {

public:
  NetConnectionConnectUi(INetConnectionConnectUi* pUi=NULL)
  :ComIUnknown(pUi)
  {

  }

private:
  INetConnectionConnectUi* getConnectUi()
  {
    return (INetConnectionConnectUi*)getIUnknown();
  }

    
public:
  HRESULT setConnection( 
            /* [in] */ INetConnection __RPC_FAR *pCon)
  {
    HRESULT hr = getgetConnectUi() -> SetConnection( 
        pCon);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
       
  HRESULT connect( 
            /* [in] */ HWND hwndParent,
            /* [in] */ DWORD dwFlags)
  {
    HRESULT hr = getgetConnectUi() -> Connect( 
      hwndParent,
      dwFlags);

    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
        
  HRESULT disconnect( 
            /* [in] */ HWND hwndParent,
            /* [in] */ DWORD dwFlags)
  {
    HRESULT hr = getgetConnectUi() -> Disconnect( 
      hwndParent,
      dwFlags)ÅG
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }    
};
    
}

