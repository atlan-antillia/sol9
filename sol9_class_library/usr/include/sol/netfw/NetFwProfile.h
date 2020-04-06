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
 *  NetFwProfile.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>
#include <sol/netfw/NetFwRemoteAdminSettings.h>
#include <sol/netfw/NetFwIcmpSettings.h>
#include <sol/netfw/NetFwOpenPorts.h>
#include <sol/netfw/NetFwServices.h>
#include <sol/netfw/NetFwAuthorizedApplications.h>

#include <sol/Writer.h>

/**
//Usage:
{
  ApartmentThreadedModel model;
  NetFwMgr mgr;
  NetFwPolicy  policy = mgr.getLocalPolicy();
  NetFwProfile profile = policy.getCurrentProfile();
}
*/

namespace SOL {

class NetFwProfile: public ComIDispatch {

public:
  NetFwProfile(INetFwProfile* pProfile=NULL)
    :ComIDispatch(pProfile)
  {
  }

private:
  INetFwProfile* getProfile()
  {
    return (INetFwProfile*) getIDispatch();
  }

public:    
  HRESULT getType( 
            /* [retval][out] */ NET_FW_PROFILE_TYPE *type)
  {
    HRESULT hr = getProfile() -> get_Type( 
        type);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:    
  NET_FW_PROFILE_TYPE getType()
  {
    NET_FW_PROFILE_TYPE type;
    HRESULT hr = getProfile() -> get_Type( 
        &type);
    if (FAILED(hr)) {
      throw hr;
    }
    return type;
  }

public:
  HRESULT getFirewallEnabled( 
            /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getProfile() -> get_FirewallEnabled( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getFirewallEnabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getProfile() -> get_FirewallEnabled( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putFirewallEnabled( 
            /* [in] */ VARIANT_BOOL enabled)
  {
    HRESULT hr = getProfile() -> put_FirewallEnabled( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT putFirewallEnabled( 
            /* [in] */ bool enabled)
  {
    HRESULT hr = getProfile() -> put_FirewallEnabled( 
        toVariantBool(enabled));
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getExceptionsNotAllowed( 
            /* [retval][out] */ VARIANT_BOOL *notAllowed)
  {
    HRESULT hr = getProfile() -> get_ExceptionsNotAllowed( 
        notAllowed);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  bool getExceptionsNotAllowed()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getProfile() -> get_ExceptionsNotAllowed( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putExceptionsNotAllowed( 
            /* [in] */ VARIANT_BOOL notAllowed)
  {
    HRESULT hr = getProfile() -> put_ExceptionsNotAllowed( 
        notAllowed);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
  
public:
  HRESULT putExceptionsNotAllowed( 
            /* [in] */ bool notAllowed)
  {
    HRESULT hr = getProfile() -> put_ExceptionsNotAllowed( 
        toVariantBool(notAllowed) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT getNotificationsDisabled( 
            /* [retval][out] */ VARIANT_BOOL *disabled)
  {
    HRESULT hr = getProfile() -> get_NotificationsDisabled( 
        disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  bool getNotificationsDisabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getProfile() -> get_NotificationsDisabled( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }


public:
  HRESULT putNotificationsDisabled( 
            /* [in] */ VARIANT_BOOL disabled)
  {
    HRESULT hr = getProfile() -> put_NotificationsDisabled( 
        disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT putNotificationsDisabled( 
            /* [in] */ bool disabled)
  {
    HRESULT hr = getProfile() -> put_NotificationsDisabled( 
        toVariantBool(disabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getUnicastResponsesToMulticastBroadcastDisabled( 
            /* [retval][out] */ VARIANT_BOOL *disabled)
  {
    HRESULT hr = getProfile() -> get_UnicastResponsesToMulticastBroadcastDisabled( 
        disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  bool getUnicastResponsesToMulticastBroadcastDisabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getProfile() -> get_UnicastResponsesToMulticastBroadcastDisabled( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putUnicastResponsesToMulticastBroadcastDisabled( 
            /* [in] */ VARIANT_BOOL disabled)
  {
    HRESULT hr = getProfile() -> put_UnicastResponsesToMulticastBroadcastDisabled( 
          disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT putUnicastResponsesToMulticastBroadcastDisabled( 
            /* [in] */ bool disabled)
  {
    HRESULT hr = getProfile() -> put_UnicastResponsesToMulticastBroadcastDisabled( 
          toVariantBool(disabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getRemoteAdminSettings( 
            /* [retval][out] */ INetFwRemoteAdminSettings **remoteAdminSettings)
  {
    HRESULT hr = getProfile() -> get_RemoteAdminSettings( 
        remoteAdminSettings);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
  
public:
  INetFwRemoteAdminSettings* getRemoteAdminSettings()
  {
    INetFwRemoteAdminSettings* pRemoteAdminSettings = NULL;
    HRESULT hr = getProfile() -> get_RemoteAdminSettings( 
        &pRemoteAdminSettings);
    if (FAILED(hr)) {
      throw hr;
    }
    return pRemoteAdminSettings;
  }


public:
  HRESULT getIcmpSettings( 
            /* [retval][out] */ INetFwIcmpSettings **icmpSettings)
  {
    HRESULT hr = getProfile() -> get_IcmpSettings( 
        icmpSettings);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwIcmpSettings* getIcmpSettings()
  {
    INetFwIcmpSettings* pIcmpSettings = NULL;
    HRESULT hr = getProfile() -> get_IcmpSettings( 
        &pIcmpSettings);
    if (FAILED(hr)) {
      throw hr;
    }
    return pIcmpSettings;
  }

public:
  HRESULT getGloballyOpenPorts( 
            /* [retval][out] */ INetFwOpenPorts **openPorts)
  {
    HRESULT hr = getProfile() -> get_GloballyOpenPorts( 
        openPorts);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        

public:
  INetFwOpenPorts* getGloballyOpenPorts()
  {
    INetFwOpenPorts* pOpenPorts = NULL;
    HRESULT hr = getProfile() -> get_GloballyOpenPorts( 
        &pOpenPorts);
    if (FAILED(hr)) {
      throw hr;
    }
    return pOpenPorts;
  }

public:
  HRESULT getServices( 
            /* [retval][out] */ INetFwServices **services)
  {
    HRESULT hr = getProfile() -> get_Services( 
        services);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwServices* getServices()
  {
    INetFwServices* pServices = NULL;
    HRESULT hr = getProfile() -> get_Services( 
        &pServices);
    if (FAILED(hr)) {
      throw hr;
    }
    return pServices;
  }

public:
  HRESULT getAuthorizedApplications( 
            /* [retval][out] */ INetFwAuthorizedApplications **apps)
  {
    HRESULT hr = getProfile() -> get_AuthorizedApplications( 
        apps);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwAuthorizedApplications* getAuthorizedApplications()
  {
    INetFwAuthorizedApplications* pApps = NULL;
    HRESULT hr = getProfile() -> get_AuthorizedApplications( 
        &pApps);
    if (FAILED(hr)) {
      throw hr;
    }
    return pApps;
  }
        

public:    
  virtual void display(HWND hwnd=NULL)
  {
    NetFwName name;
    _tprintf(_T("<Profile>\n"));

    NET_FW_PROFILE_TYPE type = getType();
    _tprintf(_T("<Type>%s</Type>\n"),  
        name.toString(type)); 
    _tprintf(_T("<FirewallEnabled>%s</FirewallEnabled>\n"), //2012/09/26 
        name.toString(getFirewallEnabled()) );

    _tprintf(_T("<ExceptionsNotAllowed>%s</ExceptionsNotAllowed>\n"), 
        name.toString(getExceptionsNotAllowed()) );
    _tprintf(_T("<NotificationsDisabled>%s</NotificationsDisabled>\n"), 
        name.toString(getNotificationsDisabled()) );
    _tprintf(_T("<UnicastResponsesToMulticastBroadcastDisabled>%s</UnicastResponsesToMulticastBroadcastDisabled>\n"), 
        name.toString(getUnicastResponsesToMulticastBroadcastDisabled()) );

    NetFwRemoteAdminSettings adminSettings = getRemoteAdminSettings();
    adminSettings.display(hwnd); 
    
    NetFwIcmpSettings icmpSettings = getIcmpSettings();
    icmpSettings.display(hwnd);

    NetFwOpenPorts openPorts = getGloballyOpenPorts();
    openPorts.display(hwnd);

    NetFwServices services = getServices();
    services.display(hwnd);
    
    NetFwAuthorizedApplications authorizedApplications = getAuthorizedApplications();
    authorizedApplications.display(hwnd);
    _tprintf(_T("</Profile>\n"));
  }

public:    
  virtual void write(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<Profile>\n");

    NET_FW_PROFILE_TYPE type = getType();
    writer.write(L"<Type>%s</Type>\n",  
        (const wchar_t*)_bstr_t(name.toString(type)) ); 
    
  
    writer.write(L"<FirewallEnabled>%s</FirewallEnabled>\n", 
        (const wchar_t*)_bstr_t(name.toString(getFirewallEnabled()) ) );
    
    writer.write(L"<ExceptionsNotAllowed>%s</ExceptionsNotAllowed>\n", 
        (const wchar_t*)_bstr_t(name.toString(getExceptionsNotAllowed()) ) );
    writer.write(L"<NotificationsDisabled>%s</NotificationsDisabled>\n", 
        (const wchar_t*)_bstr_t(name.toString(getNotificationsDisabled()) ) );
    writer.write(L"<UnicastResponsesToMulticastBroadcastDisabled>%s</UnicastResponsesToMulticastBroadcastDisabled>\n", 
        (const wchar_t*)_bstr_t(name.toString(getUnicastResponsesToMulticastBroadcastDisabled()) ) );
      
    
    NetFwRemoteAdminSettings adminSettings = getRemoteAdminSettings();
    adminSettings.write(writer); 
    
    NetFwIcmpSettings icmpSettings = getIcmpSettings();
    icmpSettings.write(writer);

    NetFwOpenPorts openPorts = getGloballyOpenPorts();
    openPorts.write(writer);

    NetFwServices services = getServices();
    services.write(writer);
    
    NetFwAuthorizedApplications authorizedApplications = getAuthorizedApplications();
    authorizedApplications.write(writer);
    
    writer.write(L"</Profile>\n");
  }

};
 
}
