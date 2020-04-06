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
 *  NetFwIcmpSettings.h
 *
 *****************************************************************************/

//2012/09/14

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>
#include <sol/Writer.h>

namespace SOL {

class NetFwIcmpSettings: public ComIDispatch {
    
public:
  NetFwIcmpSettings(INetFwIcmpSettings* pSettings)
    :ComIDispatch(pSettings)
  {
  }

private:
  INetFwIcmpSettings* getSettings()
  {
    return (INetFwIcmpSettings*) getIDispatch();
  }

public:
  HRESULT getAllowOutboundDestinationUnreachable( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowOutboundDestinationUnreachable( 
          allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowOutboundDestinationUnreachable()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowOutboundDestinationUnreachable( 
          &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public:
  HRESULT putAllowOutboundDestinationUnreachable( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundDestinationUnreachable( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putAllowOutboundDestinationUnreachable( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundDestinationUnreachable( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getAllowRedirect( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowRedirect( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  bool getAllowRedirect()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowRedirect( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public:
  HRESULT putAllowRedirect( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowRedirect( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putAllowRedirect( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowRedirect( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowInboundEchoRequest( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowInboundEchoRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowInboundEchoRequest( 
            /* [retval][out] */ )
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowInboundEchoRequest( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public:
  HRESULT putAllowInboundEchoRequest( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundEchoRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putAllowInboundEchoRequest( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundEchoRequest( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowOutboundTimeExceeded( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowOutboundTimeExceeded( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowOutboundTimeExceeded( 
            /* [retval][out] */ )
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowOutboundTimeExceeded( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public:
  HRESULT putAllowOutboundTimeExceeded( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundTimeExceeded( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putAllowOutboundTimeExceeded( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundTimeExceeded( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowOutboundParameterProblem( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowOutboundParameterProblem( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowOutboundParameterProblem( 
            /* [retval][out] */ )
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowOutboundParameterProblem( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public: 
  HRESULT putAllowOutboundParameterProblem( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundParameterProblem( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public: 
  HRESULT putAllowOutboundParameterProblem( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundParameterProblem( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowOutboundSourceQuench( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowOutboundSourceQuench( 
          allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowOutboundSourceQuench()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowOutboundSourceQuench( 
          &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public: 
  HRESULT putAllowOutboundSourceQuench( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundSourceQuench( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public: 
  HRESULT putAllowOutboundSourceQuench( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundSourceQuench( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowInboundRouterRequest( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowInboundRouterRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowInboundRouterRequest()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowInboundRouterRequest( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public:
  HRESULT putAllowInboundRouterRequest( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundRouterRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putAllowInboundRouterRequest( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundRouterRequest( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowInboundTimestampRequest( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowInboundTimestampRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowInboundTimestampRequest()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowInboundTimestampRequest( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public: 
  HRESULT putAllowInboundTimestampRequest( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundTimestampRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public: 
  HRESULT putAllowInboundTimestampRequest( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundTimestampRequest( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public: 
  HRESULT getAllowInboundMaskRequest( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowInboundMaskRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public: 
  bool getAllowInboundMaskRequest()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowInboundMaskRequest( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public:
  HRESULT putAllowInboundMaskRequest( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundMaskRequest( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putAllowInboundMaskRequest( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowInboundMaskRequest( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getAllowOutboundPacketTooBig( 
            /* [retval][out] */ VARIANT_BOOL *allow)
  {
    HRESULT hr = getSettings() -> get_AllowOutboundPacketTooBig( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getAllowOutboundPacketTooBig()
  {
    VARIANT_BOOL allow;
    HRESULT hr = getSettings() -> get_AllowOutboundPacketTooBig( 
        &allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(allow);
  }

public: 
  HRESULT putAllowOutboundPacketTooBig( 
            /* [in] */ VARIANT_BOOL allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundPacketTooBig( 
        allow);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public: 
  HRESULT putAllowOutboundPacketTooBig( 
            /* [in] */ bool allow)
  {
    HRESULT hr = getSettings() -> put_AllowOutboundPacketTooBig( 
        toVariantBool(allow) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
    
public:
  virtual void display(HWND hwnd=NULL)
  {
    NetFwName name;

    _tprintf(_T("<IcmpSettings>\n"));

    _tprintf(_T("<AllowOutboundDestinationUnreachable>%s</AllowOutboundDestinationUnreachable>\n"), name.toString(getAllowOutboundDestinationUnreachable()) );

    _tprintf(_T("<AllowRedirect>%s</AllowRedirect>\n"), name.toString(getAllowRedirect()) );

    _tprintf(_T("<AllowInboundEchoRequest>%s</AllowInboundEchoRequest>\n"), name.toString(getAllowInboundEchoRequest()) ); 

    _tprintf(_T("<AllowOutboundTimeExceeded>%s</AllowOutboundTimeExceeded>\n"), name.toString(getAllowOutboundTimeExceeded()) ); 

    _tprintf(_T("<AllowOutboundParameterProblem>%s</AllowOutboundParameterProblem>\n"), name.toString(getAllowOutboundParameterProblem()) ); 

    _tprintf(_T("<AllowOutboundSourceQuench>%s</AllowOutboundSourceQuench>\n"), name.toString(getAllowOutboundSourceQuench()) );

    _tprintf(_T("<AllowInboundRouterRequest>%s</AllowInboundRouterRequest>\n"), name.toString(getAllowInboundRouterRequest()) );

    _tprintf(_T("<AllowInboundTimestampRequest>%s</AllowInboundTimestampRequest>\n"), name.toString(getAllowInboundTimestampRequest()) );

    _tprintf(_T("<AllowInboundMaskRequest>%s</AllowInboundMaskRequest>\n"), name.toString(getAllowInboundMaskRequest()) );

    _tprintf(_T("<AllowOutboundPacketTooBig>%s</AllowOutboundPacketTooBig>\n"), name.toString(getAllowOutboundPacketTooBig()) );

    _tprintf(_T("</IcmpSettings>\n"));
  }

public:
  virtual void write(Writer& writer)
  {
    NetFwName name;

    writer.write(L"<IcmpSettings>\n");

    writer.write(L"<AllowOutboundDestinationUnreachable>%s</AllowOutboundDestinationUnreachable>\n",
      (const wchar_t*)_bstr_t(name.toString(getAllowOutboundDestinationUnreachable()) ) );

    writer.write(L"<AllowRedirect>%s</AllowRedirect>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowRedirect()) ) );

    writer.write(L"<AllowInboundEchoRequest>%s</AllowInboundEchoRequest>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowInboundEchoRequest()) ) ); 

    writer.write(L"<AllowOutboundTimeExceeded>%s</AllowOutboundTimeExceeded>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowOutboundTimeExceeded()) ) ); 

    writer.write(L"<AllowOutboundParameterProblem>%s</AllowOutboundParameterProblem>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowOutboundParameterProblem()) ) ); 

    writer.write(L"<AllowOutboundSourceQuench>%s</AllowOutboundSourceQuench>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowOutboundSourceQuench()) ) );

    writer.write(L"<AllowInboundRouterRequest>%s</AllowInboundRouterRequest>\n",
      (const wchar_t*)_bstr_t(name.toString(getAllowInboundRouterRequest()) ) );

    writer.write(L"<AllowInboundTimestampRequest>%s</AllowInboundTimestampRequest>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowInboundTimestampRequest()) ) );

    writer.write(L"<AllowInboundMaskRequest>%s</AllowInboundMaskRequest>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowInboundMaskRequest()) ) );

    writer.write(L"<AllowOutboundPacketTooBig>%s</AllowOutboundPacketTooBig>\n", 
      (const wchar_t*)_bstr_t(name.toString(getAllowOutboundPacketTooBig()) ) );

    writer.write(L"</IcmpSettings>\n");
  }
};
    
}
