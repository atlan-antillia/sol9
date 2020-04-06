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
 *  NetFwPolicy2.h
 *
 *****************************************************************************/

//2012/09/14

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwRules.h>
#include <sol/Writer.h>


/**
Usage:
{
  ApartmentThreadedModel model;
  NetFwPolicy2 policy2;
  NetFwRules rules = policy2.getRules();
  NetFwServiceRestriction restriction = policy2.getServiceRestriction();
}
*/

namespace SOL {

class NetFwPolicy2: public ComIDispatch {
  
public:
  NetFwPolicy2()
    :ComIDispatch()
  {
    createInstance();
  }

public:
  HRESULT createInstance()
  {
    INetFwPolicy2* pPolicy2 = NULL;

    HRESULT hr = CoCreateInstance(
        __uuidof(::NetFwPolicy2), 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        __uuidof(INetFwPolicy2), 
        (void**)&pPolicy2);
    if (SUCCEEDED(hr)) {
      set(pPolicy2);
    } else {
      throw hr;
    }
    return hr;
  }


private:
  INetFwPolicy2* getPolicy2()
  {
    return (INetFwPolicy2*) getIDispatch(); 
  }

public:    
  HRESULT getCurrentProfileTypes( 
            /* [retval][out] */ long *profileTypesBitmask)
  {
    HRESULT hr = getPolicy2() -> get_CurrentProfileTypes( 
        profileTypesBitmask);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:    
  long getCurrentProfileTypes()
  {
    long profileTypesBitmask=0;
    HRESULT hr = getPolicy2() -> get_CurrentProfileTypes( 
        &profileTypesBitmask);
    if (FAILED(hr)) {
      throw hr;
    }
    return profileTypesBitmask;
  }
    
public:
  HRESULT getFirewallEnabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getPolicy2() -> get_FirewallEnabled( 
          profileType,
          enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
       
/*
typedef enum NET_FW_PROFILE_TYPE2_ { 
  NET_FW_PROFILE2_DOMAIN    = 0x0001,
  NET_FW_PROFILE2_PRIVATE   = 0x0002,
  NET_FW_PROFILE2_PUBLIC    = 0x0004,
  NET_FW_PROFILE2_ALL       = 0x7FFFFFFF 
} NET_FW_PROFILE_TYPE2;
*/
public:
  bool getFirewallEnabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPolicy2() -> get_FirewallEnabled( 
          profileType,
          &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }


public:
  HRESULT putFirewallEnabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ VARIANT_BOOL enabled)
  {
    HRESULT hr = getPolicy2() -> put_FirewallEnabled( 
          profileType,
          enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT putFirewallEnabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ bool enabled)
  {
    HRESULT hr = getPolicy2() -> put_FirewallEnabled( 
          profileType,
          toVariantBool(enabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getExcludedInterfaces( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ VARIANT *interfaces)
  {
    HRESULT hr = getPolicy2() -> get_ExcludedInterfaces( 
          profileType,
          interfaces);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  _variant_t getExcludedInterfaces( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getPolicy2() -> get_ExcludedInterfaces( 
          profileType,
          &var);
    if (FAILED(hr)) {
      throw hr;
    }
    return _variant_t(var, false);
  }

public:
  HRESULT putExcludedInterfaces( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ VARIANT interfaces)
  {
    HRESULT hr = getPolicy2() -> put_ExcludedInterfaces( 
        profileType,
        interfaces);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getBlockAllInboundTraffic( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ VARIANT_BOOL *block)
  {
    HRESULT hr = getPolicy2() -> get_BlockAllInboundTraffic( 
        profileType,
        block);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  bool getBlockAllInboundTraffic( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPolicy2() -> get_BlockAllInboundTraffic( 
        profileType,
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putBlockAllInboundTraffic( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ VARIANT_BOOL block)
  {
    HRESULT hr = getPolicy2() -> put_BlockAllInboundTraffic( 
          profileType,
          block);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT putBlockAllInboundTraffic( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ bool block)
  {
    HRESULT hr = getPolicy2() -> put_BlockAllInboundTraffic( 
          profileType,
          toVariantBool(block) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getNotificationsDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ VARIANT_BOOL *disabled)
  {
    HRESULT hr = getPolicy2() -> get_NotificationsDisabled( 
          profileType,
          disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getNotificationsDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPolicy2() -> get_NotificationsDisabled( 
          profileType,
          &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putNotificationsDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ VARIANT_BOOL disabled)
  {
    HRESULT hr = getPolicy2() -> put_NotificationsDisabled( 
          profileType,
          disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT putNotificationsDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ bool disabled)
  {
    HRESULT hr = getPolicy2() -> put_NotificationsDisabled( 
          profileType,
          toVariantBool(disabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getUnicastResponsesToMulticastBroadcastDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ VARIANT_BOOL *disabled)
  {
    HRESULT hr = getPolicy2() -> get_UnicastResponsesToMulticastBroadcastDisabled( 
          profileType,
          disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getUnicastResponsesToMulticastBroadcastDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPolicy2() -> get_UnicastResponsesToMulticastBroadcastDisabled( 
          profileType,
          &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putUnicastResponsesToMulticastBroadcastDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ VARIANT_BOOL disabled)
  {
    HRESULT hr = getPolicy2() -> put_UnicastResponsesToMulticastBroadcastDisabled( 
          profileType,
          disabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putUnicastResponsesToMulticastBroadcastDisabled( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ bool disabled)
  {
    HRESULT hr = getPolicy2() -> put_UnicastResponsesToMulticastBroadcastDisabled( 
          profileType,
          toVariantBool(disabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getRules( 
            /* [retval][out] */ INetFwRules **rules)
  {
    HRESULT hr = getPolicy2() -> get_Rules( 
          rules);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwRules* getRules()
  {
    INetFwRules* pRules = NULL;
    HRESULT hr = getPolicy2() -> get_Rules( 
          &pRules);
    if (FAILED(hr)) {
      throw hr;
    }
    return pRules;
  }

public:
  HRESULT getServiceRestriction( 
            /* [retval][out] */ INetFwServiceRestriction **serviceRestriction)
  {
    HRESULT hr = getPolicy2() -> get_ServiceRestriction( 
        serviceRestriction);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwServiceRestriction* getServiceRestriction()
  {
    INetFwServiceRestriction* pServiceRestriction = NULL;
    HRESULT hr = getPolicy2() -> get_ServiceRestriction( 
        &pServiceRestriction);
    if (FAILED(hr)) {
      throw hr;
    }
    return pServiceRestriction;
  }

public:
  HRESULT enableRuleGroup( 
            /* [in] */ long profileTypesBitmask,
            /* [in] */ BSTR group,
            /* [in] */ VARIANT_BOOL enable)
  {
    HRESULT hr = getPolicy2() -> EnableRuleGroup( 
          profileTypesBitmask,
          group,
          enable);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  HRESULT enableRuleGroup( 
            /* [in] */ long profileTypesBitmask,
            /* [in] */ BSTR group,
            /* [in] */ bool enable)
  {
    HRESULT hr = getPolicy2() -> EnableRuleGroup( 
          profileTypesBitmask,
          group,
          toVariantBool(enable) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  HRESULT isRuleGroupEnabled( 
            /* [in] */ long profileTypesBitmask,
            /* [in] */ BSTR group,
            /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getPolicy2() -> IsRuleGroupEnabled( 
          profileTypesBitmask,
          group,
          enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  bool isRuleGroupEnabled( 
            /* [in] */ long profileTypesBitmask,
            /* [in] */ BSTR group)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPolicy2() -> IsRuleGroupEnabled( 
          profileTypesBitmask,
          group,
          &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT restoreLocalFirewallDefaults()
  {
    HRESULT hr = getPolicy2() -> RestoreLocalFirewallDefaults();
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getDefaultInboundAction( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ NET_FW_ACTION *action)
  {
    HRESULT hr = getPolicy2() -> get_DefaultInboundAction( 
          profileType,
          action);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  NET_FW_ACTION getDefaultInboundAction( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    NET_FW_ACTION action;
    HRESULT hr = getPolicy2() -> get_DefaultInboundAction( 
          profileType,
          &action);
    if (FAILED(hr)) {
      throw hr;
    }
    return action;
  }


public:
  HRESULT putDefaultInboundAction( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ NET_FW_ACTION action)
  {
    HRESULT hr = getPolicy2() -> put_DefaultInboundAction( 
          profileType,
          action);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getDefaultOutboundAction( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [retval][out] */ NET_FW_ACTION *action)
  {
    HRESULT hr = getPolicy2() -> get_DefaultOutboundAction( 
            profileType,
            action);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  NET_FW_ACTION getDefaultOutboundAction( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType)
  {
    NET_FW_ACTION action;
    HRESULT hr = getPolicy2() -> get_DefaultOutboundAction( 
            profileType,
            &action);
    if (FAILED(hr)) {
      throw hr;
    }
    return action;
  }

public:
  HRESULT putDefaultOutboundAction( 
            /* [in] */ NET_FW_PROFILE_TYPE2 profileType,
            /* [in] */ NET_FW_ACTION action)
  {
    HRESULT hr = getPolicy2() -> put_DefaultOutboundAction( 
          profileType,
          action);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  HRESULT getIsRuleGroupCurrentlyEnabled( 
            /* [in] */ BSTR group,
           /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getPolicy2() -> get_IsRuleGroupCurrentlyEnabled( 
          group,
          enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  bool getIsRuleGroupCurrentlyEnabled( 
            /* [in] */ BSTR group)
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getPolicy2() -> get_IsRuleGroupCurrentlyEnabled( 
          group,
          &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT getLocalPolicyModifyState( 
            /* [retval][out] */ NET_FW_MODIFY_STATE *modifyState)
  {
    HRESULT hr = getPolicy2() -> get_LocalPolicyModifyState( 
          modifyState);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  NET_FW_MODIFY_STATE getLocalPolicyModifyState()
  {
    NET_FW_MODIFY_STATE modifyState;
    HRESULT hr = getPolicy2() -> get_LocalPolicyModifyState( 
          &modifyState);
    if (FAILED(hr)) {
      throw hr;
    }
    return modifyState;
  }    

public:
  virtual void displayProfile(HWND hwnd=NULL)
  {
    NetFwName name;
    _tprintf(_T("<Profile>\n"));

    NET_FW_MODIFY_STATE st = getLocalPolicyModifyState();
    _tprintf(_T("<PolicyModifyState>%s</PolicyModifyState>\n"), (const TCHAR*)name.toString(st)) ;

    NET_FW_PROFILE_TYPE2 types = (NET_FW_PROFILE_TYPE2)getCurrentProfileTypes();
    _tprintf(_T("<ProfileTypes>%s</ProfileTypes>\n"), (const TCHAR*)name.toStrings(types)) ;

    displayProfile(NET_FW_PROFILE2_DOMAIN);
    displayProfile(NET_FW_PROFILE2_PRIVATE);
    displayProfile(NET_FW_PROFILE2_PUBLIC);

    _tprintf(_T("</Profile>\n"));
  }

public:
  virtual void writeProfile(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<Profile>\n");

    NET_FW_MODIFY_STATE st = getLocalPolicyModifyState();
    writer.write(L"<PolicyModifyState>%s</PolicyModifyState>\n", 
      (const wchar_t*)_bstr_t(name.toString(st)) );

    NET_FW_PROFILE_TYPE2 types = (NET_FW_PROFILE_TYPE2)getCurrentProfileTypes();
    writer.write(L"<ProfileTypes>%s</ProfileTypes>\n", 
      (const wchar_t*)_bstr_t(name.toStrings(types)) );

    writeProfile(writer, NET_FW_PROFILE2_DOMAIN);
    writeProfile(writer, NET_FW_PROFILE2_PRIVATE);
    writeProfile(writer, NET_FW_PROFILE2_PUBLIC);

    writer.write(L"</Profile>\n");
  }

public:
  virtual void displayInterfaces(NET_FW_PROFILE_TYPE2 type, _variant_t var)
  {
    NetFwName name;
    _tprintf(_T("<%s>\n"), (const TCHAR*)name.toString(type));
    //if (var.vt == VT_EMPTY ||var.vt == VT_NULL) {
    //  _tprintf(_T("(null)\n"));
    //}

    if (var.vt & VT_ARRAY) {
      SAFEARRAY *pSa = var.parray;
      if (pSa) {
        if (var.vt & VT_VARIANT) {
          for(long i= pSa->rgsabound->lLbound; i < (long)pSa->rgsabound->cElements; i++) {
            _variant_t v;  
            if (SUCCEEDED(SafeArrayGetElement(pSa, &i, &v)) ) {
              if (v.vt & VT_BSTR) {
                _bstr_t name(v.bstrVal, false);
                //2012/09/26
                _tprintf(_T("<Interface>%s</Interface>\n"),(const TCHAR*)name);
              }
            }
          }
        }
      }
    }
    _tprintf(_T("</%s>\n"), (const TCHAR*)name.toString(type));
    
  }

public:
  virtual void writeInterfaces(Writer& writer, NET_FW_PROFILE_TYPE2 type, _variant_t var)
  {
    NetFwName name;
    writer.write(L"<%s>\n", (const wchar_t*)_bstr_t(name.toString(type)) );
    //if (var.vt == VT_EMPTY ||var.vt == VT_NULL) {
    //  _tprintf(_T("(null)\n"));
    //}

    if (var.vt & VT_ARRAY) {
      SAFEARRAY *pSa = var.parray;
      if (pSa) {
        if (var.vt & VT_VARIANT) {
          for(long i= pSa->rgsabound->lLbound; i < (long)pSa->rgsabound->cElements; i++) {
            _variant_t v;  
            if (SUCCEEDED(SafeArrayGetElement(pSa, &i, &v)) ) {
              if (v.vt & VT_BSTR) {
                _bstr_t name(v.bstrVal, false);
                //2012/09/26
                writer.write(L"<Interface>%s</Interface>\n", (const wchar_t*)name);
              }
            }
          }
        }
      }
    }
    writer.write(L"</%s>\n", (const wchar_t*)_bstr_t(name.toString(type)) );
    
  }

public:
  virtual void displayExcludedInterfaces(HWND hwnd=NULL)
  {
    _tprintf(_T("<ExcludedInterfaces>\n"));
  
    _variant_t var1 = getExcludedInterfaces(NET_FW_PROFILE2_DOMAIN);
    displayInterfaces(NET_FW_PROFILE2_DOMAIN, var1);


    _variant_t var2 = getExcludedInterfaces(NET_FW_PROFILE2_PRIVATE);
    displayInterfaces(NET_FW_PROFILE2_PRIVATE, var2);

    _variant_t var3 = getExcludedInterfaces(NET_FW_PROFILE2_PUBLIC);
    displayInterfaces(NET_FW_PROFILE2_PUBLIC, var3);


    _tprintf(_T("</ExcludedInterfaces>\n"));
  }

public:
  virtual void writeExcludedInterfaces(Writer& writer)
  {
    writer.write(L"<ExcludedInterfaces>\n");
  
    _variant_t var1 = getExcludedInterfaces(NET_FW_PROFILE2_DOMAIN);
    writeInterfaces(writer, NET_FW_PROFILE2_DOMAIN, var1);

    _variant_t var2 = getExcludedInterfaces(NET_FW_PROFILE2_PRIVATE);
    writeInterfaces(writer, NET_FW_PROFILE2_PRIVATE, var2);

    _variant_t var3 = getExcludedInterfaces(NET_FW_PROFILE2_PUBLIC);
    writeInterfaces(writer, NET_FW_PROFILE2_PUBLIC, var3);


    writer.write(L"</ExcludedInterfaces>\n");
  }

public:
  void displayProfile(NET_FW_PROFILE_TYPE2 type)
  {
    NetFwName name;
    _tprintf(_T("<%s>\n"), (const TCHAR*)name.toString(type));
    
    _tprintf(_T("<FirewallEnabled>%s</FirewallEnabled>\n"),
      name.toString(getFirewallEnabled(type)) );

    _tprintf(_T("<BlockAllInboundTraffic>%s</BlockAllInboundTraffic>\n"),
      name.toString(getBlockAllInboundTraffic(type)) );

    _tprintf(_T("<NotificationsDisabled>%s</NotificationsDisabled>\n"),
      name.toString(getNotificationsDisabled(type)) );

    _tprintf(_T("<UnicastResponsesToMulticastBroadcastDisabled>%s</UnicastResponsesToMulticastBroadcastDisabled>\n"),
      name.toString(getUnicastResponsesToMulticastBroadcastDisabled(type)) );

    NET_FW_ACTION a = getDefaultInboundAction(type);
    _tprintf(_T("<DefaultInboundAction>%s</DefaultInboundAction>\n"),
      name.toString(a) );

    _tprintf(_T("</%s>\n"), (const TCHAR*)name.toString(type) );
  }

public:
  void writeProfile(Writer& writer, NET_FW_PROFILE_TYPE2 type)
  {
    NetFwName name;
    writer.write(L"<%s>\n", (const wchar_t*)_bstr_t(name.toString(type)) );
    
    writer.write(L"<FirewallEnabled>%s</FirewallEnabled>\n",
      (const wchar_t*)_bstr_t(name.toString(getFirewallEnabled(type)) ) );

    writer.write(L"<BlockAllInboundTraffic>%s</BlockAllInboundTraffic>\n",
      (const wchar_t*)_bstr_t(name.toString(getBlockAllInboundTraffic(type)) ) );

    writer.write(L"<NotificationsDisabled>%s</NotificationsDisabled>\n",
      (const wchar_t*)_bstr_t(name.toString(getNotificationsDisabled(type)) ) );

    writer.write(L"<UnicastResponsesToMulticastBroadcastDisabled>%s</UnicastResponsesToMulticastBroadcastDisabled>\n",
      (const wchar_t*)_bstr_t(name.toString(getUnicastResponsesToMulticastBroadcastDisabled(type)) ) );

    NET_FW_ACTION a = getDefaultInboundAction(type);
    writer.write(L"<DefaultInboundAction>%s</DefaultInboundAction>\n",
      (const wchar_t*)_bstr_t(name.toString(a) ) );

    writer.write(L"</%s>\n", (const wchar_t*)_bstr_t(name.toString(type) ) );
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("<Policy2>\n"));

    NetFwRules rules = getRules();
    rules.display(hwnd);

    _tprintf(_T("</Policy2>\n"));
  }

public:
  virtual void write(Writer& writer)
  {
    writer.write(L"<Policy2>\n");
    //1 Write profile
    writeProfile(writer);

    //2 Write rules
    NetFwRules rules = getRules();
    rules.write(writer);

    //3 Write excludedInterfaces
    writeExcludedInterfaces(writer);
    writer.write(L"</Policy2>\n");
  }

};
    
}
