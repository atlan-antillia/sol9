/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WindowsFirewall.h
 *
 *****************************************************************************/

// SOL9
// 2008/08/05

#pragma once

#include <sol\Object.h>

#include <netfw.h>

namespace SOL {

/**
 * WindowsFirewall setting class
 */

class WindowsFirewall: public Object {

private:
  INetFwMgr* fwMgr;

  INetFwProfile* fwProfile;
  INetFwPolicy* fwPolicy;

public:
  /**
   * Constructor            
   */

  WindowsFirewall()
   :fwProfile(NULL),
   fwMgr(NULL),
   fwPolicy(NULL)
  {
        
    HRESULT hr = CoInitializeEx(0,COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (hr != RPC_E_CHANGED_MODE && FAILED(hr)){
      printf("WindowsFirewall#WindowsFirewall,1,CoInitializeEx failed: 0x%08lx\n", hr);
      throw hr;
    }

    try {
      // Firewall settings manager.
      if (FAILED(hr = CoCreateInstance(__uuidof(NetFwMgr),
          NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwMgr),
          (void**)&fwMgr))) {
        printf("WindowsFirewall#WindowsFirewall,2,CoCreateInstance failed: 0x%08lx\n", hr);
        throw hr;
      }

      if (FAILED(hr =fwMgr->get_LocalPolicy(&fwPolicy))) {
        printf("WindowsFirewall#WindowsFirewall,3,get_LocalPolicy failed: 0x%08lx\n", hr);
        throw hr;
      }
      if (FAILED(hr = fwPolicy->get_CurrentProfile(&fwProfile))) {
        printf("WindowsFirewall#WindowsFirewall,4,get_CurrentProfile failed: 0x%08lx\n", hr);

        throw hr;
      }
    } catch (HRESULT hr) {
      printf("WindowsFirewall#WindowsFirewall,5,Caught Exception 0x%08lx\n", hr);
      clear();

      throw hr;
    }
  }  
  

private:
  void clear() {
    if (fwProfile) {
      fwProfile->Release();
      fwProfile = NULL;
    }
    if (fwPolicy) {
      fwPolicy->Release();
      fwPolicy = NULL;
    }
    if (fwMgr) {
      fwMgr->Release();
      fwMgr = NULL;
    }

    CoUninitialize();
  }


public:
  /**
   * Destructor
   */
  ~WindowsFirewall() {
    clear();
  }


public:
  HRESULT isFirewallEnabled(BOOL& enabled)
  {
    HRESULT hr = S_OK;

    enabled = FALSE;

    VARIANT_BOOL fwEnabled = VARIANT_FALSE;

    try {  
      if (FAILED (hr = fwProfile->get_FirewallEnabled(&fwEnabled))) {
        printf("WindowsFirewall#isFirewallEnabled,1,get_FirewallEnabled failed: 0x%08lx\n", hr);
        throw hr;
      }
      if (fwEnabled == VARIANT_TRUE){
        enabled = TRUE;  
      }
     } catch (HRESULT ) {

    }
    return hr;
   }


public:
  HRESULT isExceptionNotAllowed(BOOL& notAllowed)
  {
    //printf("WindowsFirewall#isFirewallOn,1,Start");

    HRESULT hr = S_OK;

    VARIANT_BOOL fwNotAllowed = VARIANT_FALSE;

    notAllowed = FALSE;

    try {  
      if (FAILED (hr = fwProfile->get_ExceptionsNotAllowed(&fwNotAllowed))) {
        printf("WindowsFirewall#isExceptionNotAllowed,1,get_ExceptionsNotAllowed failed: 0x%08lx\n", hr);
        throw hr;
      }
      if (fwNotAllowed == VARIANT_TRUE){
        notAllowed = TRUE;
      }
    } catch (HRESULT ) {

    } 
    return hr;
  }


public:
  HRESULT isPortEnabled(int port, bool tcp, BOOL& enabled)
  {
        enabled = FALSE;

    NET_FW_IP_PROTOCOL protocol = NET_FW_IP_PROTOCOL_UDP;
    if(tcp) {
      protocol = NET_FW_IP_PROTOCOL_TCP;
    }

    INetFwOpenPorts* fwOpenPorts = NULL;
    INetFwOpenPort* fwOpenPort = NULL;
    HRESULT hr = S_OK;
    
    try {
      if (FAILED(hr= fwProfile->get_GloballyOpenPorts(&fwOpenPorts))) {
        printf("WindowsFirewall#isPortEnabled,1,Failed in get_GloballyOpenPorts\n");
        throw hr;

      }    
      long count = 0;
      if (FAILED(hr = fwOpenPorts->get_Count(&count))) {
        printf("WindowsFirewall#isPortEnabled,2,Failed in get_Count\n");
        throw hr;
      }
      printf("Count=%d\n", count);
      //if (count>0) {
      if (FAILED(hr = fwOpenPorts->Item(port, protocol, &fwOpenPort))) {
        printf("WindowsFirewall#isPortEnabled,3,Failed in Item\n");
        throw hr;
      }

      VARIANT_BOOL fwEnabled = VARIANT_FALSE;  
      if (FAILED(hr = fwOpenPort->get_Enabled(&fwEnabled))) {
        printf("WindowsFirewall#isPortEnabled,4,get_Enabled\n");
        throw hr;
      }
      if (fwEnabled == VARIANT_TRUE) {
        enabled = TRUE;
      }
      //}
    } catch (HRESULT ) {
      ;//
    }
    
    if (fwOpenPort) 
      fwOpenPort->Release();
      
    if (fwOpenPorts)
      fwOpenPorts->Release();
  
    return hr;
  }

public:

  HRESULT setPortEnabled(int port, bool tcp, bool enable)
  {
    HRESULT hr = S_OK;


    NET_FW_IP_PROTOCOL protocol = NET_FW_IP_PROTOCOL_UDP;
    if(tcp) {
      protocol = NET_FW_IP_PROTOCOL_TCP;
    }

    INetFwOpenPort* fwOpenPort = NULL;
    INetFwOpenPorts* fwOpenPorts = NULL;

    try {
      if (FAILED(hr = fwProfile->get_GloballyOpenPorts(&fwOpenPorts))) {
        printf("WindowsFirewall#setPortEnabled,1,Failed in get_GloballyOpenPorts\n");

        throw hr;
      }
      long count = 0;
      if (FAILED(hr = fwOpenPorts->get_Count(&count))) {
        printf("WindowsFirewall#setPortEnabled,2,Failed in get_Count\n");
        throw hr;
      }
      printf("Count=%d\n", count);

      if (FAILED(hr = fwOpenPorts->Item(port, protocol, &fwOpenPort))) {
        printf("WindowsFirewall#setPortEnabled,3,Failed in Item\n");
        throw hr;
      }

      VARIANT_BOOL fwEnabled = VARIANT_FALSE;
      if (enable) {
        fwEnabled = VARIANT_TRUE;
      }
      if (FAILED (hr = fwOpenPort->put_Enabled(fwEnabled))) {
        printf("WindowsFirewall#sePortEnabled,4,put_Enabled\n");

        throw hr;
      }

    } catch (HRESULT ) {
      ;  
    }
  
    if (fwOpenPort)
      fwOpenPort->Release();

    if (fwOpenPorts) 
      fwOpenPorts->Release();

    return hr;
  }
};

}
