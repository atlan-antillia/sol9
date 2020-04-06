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
 *  NetFwRule.h
 *
 *****************************************************************************/

//2012/09/14
//2012/09/23 Updated

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>
#include <sol/netfw/NetFwName.h>
#include <sol/Writer.h>

/** Usage:
{
  ApartmentThreadedModel model;
  NetFwPolicy2  policy2;
  NetFwRules rules = policy2.getRules();
  NetFwRule  rule = rules.item(L"RuleName");
}
*/


namespace SOL {

class NetFwRule: public ComIDispatch {

public:
  NetFwRule(INetFwRule* pRule=NULL)
    :ComIDispatch(pRule)
  {
    if (pRule == NULL) {
      createInstance();
    }
  }

public:
  HRESULT createInstance()
  {
    INetFwRule* pRule = NULL;
    HRESULT hr = CoCreateInstance(
        __uuidof(::NetFwRule),
        NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwRule),
        (void**)&pRule);
    if (SUCCEEDED(hr)) {
      set(pRule);
    } else {
      throw hr;
    }
    return hr;
  }

private:
  INetFwRule* getRule()
  {
    return (INetFwRule*) getIDispatch();
  }

public:
  operator INetFwRule*()
  {
    return (INetFwRule*) getIDispatch();
  }

public:
  HRESULT getName( 
            /* [retval][out] */ BSTR *name)
  {
    HRESULT hr = getRule() -> get_Name( 
        name);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getName()
  {
    BSTR name = NULL;
    HRESULT hr = getRule() -> get_Name( 
        &name);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(name, false);
  }

public:
  HRESULT putName( 
            /* [in] */ BSTR name)
  {
    HRESULT hr = getRule() -> put_Name( 
        name);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getDescription( 
            /* [retval][out] */ BSTR *desc)
  {
    HRESULT hr = getRule() -> get_Description( 
        desc);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  _bstr_t getDescription()
  {
    BSTR desc = NULL;
    HRESULT hr = getRule() -> get_Description( 
        &desc);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(desc, false);
  }

public:        
  HRESULT putDescription( 
            /* [in] */ BSTR desc)
  {
    HRESULT hr = getRule() -> put_Description( 
        desc);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getApplicationName( 
            /* [retval][out] */ BSTR *imageFileName)
  {
    HRESULT hr = getRule() -> get_ApplicationName( 
        imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  _bstr_t getApplicationName()
  {
    BSTR imageFileName = NULL;
    HRESULT hr = getRule() -> get_ApplicationName( 
        &imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(imageFileName, false);
  }

public:        
  HRESULT putApplicationName( 
            /* [in] */ BSTR imageFileName)
  {
    HRESULT hr = getRule() -> put_ApplicationName( 
        imageFileName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getServiceName( 
            /* [retval][out] */ BSTR *serviceName)
  {
    HRESULT hr = getRule() -> get_ServiceName( 
        serviceName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  _bstr_t getServiceName()
  {
    BSTR serviceName = NULL;
    HRESULT hr = getRule() -> get_ServiceName( 
        &serviceName);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(serviceName, false);
  }

public:        
  HRESULT putServiceName( 
            /* [in] */ BSTR serviceName)
  {
    HRESULT hr = getRule() -> put_ServiceName( 
        serviceName);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getProtocol( 
            /* [retval][out] */ LONG *protocol)
  {
    HRESULT hr = getRule() -> get_Protocol( 
        protocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  LONG getProtocol()
  {
    LONG protocol = 0;
    HRESULT hr = getRule() -> get_Protocol( 
        &protocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return protocol;
  }

public:        
  HRESULT putProtocol( 
            /* [in] */ LONG protocol)
  {
    HRESULT hr = getRule() -> put_Protocol( 
        protocol);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getLocalPorts( 
            /* [retval][out] */ BSTR *portNumbers)
  {
    HRESULT hr = getRule() -> get_LocalPorts( 
        portNumbers);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  _bstr_t getLocalPorts()
  {
    BSTR portNumbers = NULL;
    HRESULT hr = getRule() -> get_LocalPorts( 
        &portNumbers);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(portNumbers, false);
  }

public:        
  HRESULT putLocalPorts( 
            /* [in] */ BSTR portNumbers)
  {
    HRESULT hr = getRule() -> put_LocalPorts( 
        portNumbers);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getRemotePorts( 
            /* [retval][out] */ BSTR *portNumbers)
  {
    HRESULT hr = getRule() -> get_RemotePorts( 
        portNumbers);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getRemotePorts()
  {
    BSTR portNumbers = NULL;
    HRESULT hr = getRule() -> get_RemotePorts( 
        &portNumbers);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(portNumbers, false);
  }

public:        
  HRESULT putRemotePorts( 
            /* [in] */ BSTR portNumbers)
  {
    HRESULT hr = getRule() -> put_RemotePorts( 
        portNumbers);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getLocalAddresses( 
            /* [retval][out] */ BSTR *localAddrs)
  {
    HRESULT hr = getRule() -> get_LocalAddresses( 
        localAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getLocalAddresses()
  {
    BSTR localAddrs = NULL;
    HRESULT hr = getRule() -> get_LocalAddresses( 
        &localAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(localAddrs, false);
  }

public:        
  HRESULT putLocalAddresses( 
            /* [in] */ BSTR localAddrs)
  {
    HRESULT hr = getRule() -> put_LocalAddresses( 
        localAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getRemoteAddresses( 
            /* [retval][out] */ BSTR *remoteAddrs)
  {
    HRESULT hr = getRule() -> get_RemoteAddresses( 
          remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getRemoteAddresses()
  {
    BSTR remoteAddrs = NULL;
    HRESULT hr = getRule() -> get_RemoteAddresses( 
          &remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(remoteAddrs, false);
  }

public:        
  HRESULT putRemoteAddresses( 
            /* [in] */ BSTR remoteAddrs)
  {
    HRESULT hr = getRule() -> put_RemoteAddresses( 
        remoteAddrs);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getIcmpTypesAndCodes( 
            /* [retval][out] */ BSTR *icmpTypesAndCodes)
  {
    HRESULT hr = getRule() -> get_IcmpTypesAndCodes( 
        icmpTypesAndCodes);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getIcmpTypesAndCodes( 
            /* [retval][out] */ )
  {
    BSTR icmpTypesAndCodes = NULL;
    HRESULT hr = getRule() -> get_IcmpTypesAndCodes( 
        &icmpTypesAndCodes);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(icmpTypesAndCodes, false);
  }

public:        
  HRESULT putIcmpTypesAndCodes( 
            /* [in] */ BSTR icmpTypesAndCodes)
  {
    HRESULT hr = getRule() -> put_IcmpTypesAndCodes( 
        icmpTypesAndCodes);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getDirection( 
            /* [retval][out] */ NET_FW_RULE_DIRECTION *dir)
  {
    HRESULT hr = getRule() -> get_Direction( 
        dir);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  NET_FW_RULE_DIRECTION getDirection()
  {
    NET_FW_RULE_DIRECTION dir;
    HRESULT hr = getRule() -> get_Direction( 
        &dir);
    if (FAILED(hr)) {
      throw hr;
    }
    return dir;
  }

public:        
  HRESULT putDirection( 
            /* [in] */ NET_FW_RULE_DIRECTION dir)
  {
    HRESULT hr = getRule() -> put_Direction( 
        dir);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getInterfaces( 
            /* [retval][out] */ VARIANT *interfaces)
  {
    HRESULT hr = getRule() -> get_Interfaces( 
        interfaces);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  _variant_t getInterfaces()
  {
    VARIANT var;
    VariantInit(&var);
    HRESULT hr = getRule() -> get_Interfaces( 
        &var);
    if (FAILED(hr)) {
      throw hr;
    }
    return _variant_t(var, false);
  }


public:        
  HRESULT putInterfaces( 
            /* [in] */ VARIANT interfaces)
  {
    HRESULT hr = getRule() -> put_Interfaces( 
        interfaces);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getInterfaceTypes( 
            /* [retval][out] */ BSTR *interfaceTypes)
  {
    HRESULT hr = getRule() -> get_InterfaceTypes( 
        interfaceTypes);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getInterfaceTypes()
  {
    BSTR interfaceTypes = NULL;
    HRESULT hr = getRule() -> get_InterfaceTypes( 
        &interfaceTypes);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(interfaceTypes, false);
  }

public:        
  HRESULT putInterfaceTypes( 
            /* [in] */ BSTR interfaceTypes)
  {
    HRESULT hr = getRule() -> put_InterfaceTypes( 
        interfaceTypes);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getEnabled( 
            /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getRule() -> get_Enabled( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  bool getEnabled()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getRule() -> get_Enabled( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:
  HRESULT putEnabled( 
            /* [in] */ VARIANT_BOOL enabled)
  {
    HRESULT hr = getRule() -> put_Enabled( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT putEnabled( 
            /* [in] */ bool enabled)
  {
    HRESULT hr = getRule() -> put_Enabled( 
        toVariantBool(enabled));
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getGrouping( 
            /* [retval][out] */ BSTR *context)
  {
    HRESULT hr = getRule() -> get_Grouping( 
        context);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  _bstr_t getGrouping()
  {
     BSTR context = NULL;
    HRESULT hr = getRule() -> get_Grouping( 
        &context);
    if (FAILED(hr)) {
      throw hr;
    }
    return _bstr_t(context, false);
  }

public:        
  HRESULT putGrouping( 
            /* [in] */ BSTR context)
  {
    HRESULT hr = getRule() -> put_Grouping(
        context);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getProfiles( 
            /* [retval][out] */ long *profileTypesBitmask)
  {
    HRESULT hr = getRule() -> get_Profiles( 
        profileTypesBitmask);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  long getProfiles()
  {
    long profileTypesBitmask;
    HRESULT hr = getRule() -> get_Profiles( 
        &profileTypesBitmask);
    if (FAILED(hr)) {
      throw hr;
    }
    return profileTypesBitmask;
  }

public:        
  HRESULT putProfiles( 
            /* [in] */ long profileTypesBitmask)
  {
    HRESULT hr = getRule() -> put_Profiles( 
        profileTypesBitmask);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getEdgeTraversal( 
            /* [retval][out] */ VARIANT_BOOL *enabled)
  {
    HRESULT hr = getRule() -> get_EdgeTraversal( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  bool getEdgeTraversal()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = getRule() -> get_EdgeTraversal( 
        &vbool);
    if (FAILED(hr)) {
      throw hr;
    }
    return toBool(vbool);
  }

public:        
  HRESULT putEdgeTraversal( 
            /* [in] */ VARIANT_BOOL enabled)
  {
    HRESULT hr = getRule() -> put_EdgeTraversal( 
        enabled);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT putEdgeTraversal( 
            /* [in] */ bool enabled)
  {
    HRESULT hr = getRule() -> put_EdgeTraversal( 
        toVariantBool(enabled) );
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:        
  HRESULT getAction( 
            /* [retval][out] */ NET_FW_ACTION *action)
  {
    HRESULT hr = getRule() -> get_Action( 
        action);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  NET_FW_ACTION getAction()
  {
    NET_FW_ACTION action;
    HRESULT hr = getRule() -> get_Action( 
        &action);
    if (FAILED(hr)) {
      throw hr;
    }
    return action;
  }

public:        
  HRESULT putAction( 
            /* [in] */ NET_FW_ACTION action)
  {
    HRESULT hr = getRule() -> put_Action( 
        action);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  virtual void displayInterfaces(HWND hwnd=NULL)
  {
    _tprintf(_T("<Intefaces>\n"));
    _variant_t var = getInterfaces();
    //if (var.vt == VT_EMPTY || var.vt == VT_NULL) {
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
                //2012/09/23
                _bstr_t name(v.bstrVal);//, false);
                _tprintf(_T("<Interface>%s</Interface>\n"),(const TCHAR*)name);
              } else {
                ;// Probably, you have to convert v to BSTR 
              }
            }
          }
        }
      }
    }
    else {
      //_tprintf(_T("variant.vt=%d\n"), var.vt);
    }
    _tprintf(_T("</Intefaces>\n"));
  }

public:
  virtual void writeInterfaces(Writer& writer)
  {
    writer.write(L"<Intefaces>\n");
    _variant_t var = getInterfaces();
    //if (var.vt == VT_EMPTY || var.vt == VT_NULL) {
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
                //2012/09/23
                _bstr_t name(v.bstrVal);//, false);
                writer.write(L"<Interface>%s</Interface>\n", (const TCHAR*)name);
              } else {
                ;// Probably, you have to convert v to BSTR 
              }
            }
          }
        }
      }
    }
    else {
      //_tprintf(_T("variant.vt=%d\n"), var.vt);
    }
    writer.write(L"</Intefaces>\n");
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    NetFwName name;
    _tprintf(_T("<Rule>\n"));

    _tprintf(_T("<Name>%s</Name>\n"), (const TCHAR*)getName() );
    _tprintf(_T("<Description>%s</Description>\n"), (const TCHAR*)getDescription() );
    _tprintf(_T("<ApplicationName>%s</ApplicationName>\n"), (const TCHAR*)getApplicationName() );
    _tprintf(_T("<ServiceName>%s</ServiceName>\n"), (const TCHAR*)getServiceName() );
    NET_FW_IP_PROTOCOL protocol = (NET_FW_IP_PROTOCOL)getProtocol();
    _tprintf(_T("<Protocol>%s</Protocol>\n"), (const TCHAR*)name.toString(protocol) );
    _tprintf(_T("<LocalPorts>%s</LocalPorts>\n"), (const TCHAR*)getLocalPorts() );
    _tprintf(_T("<RemotePorts>%s</RemotePorts>\n"), (const TCHAR*)getRemotePorts() );
    _tprintf(_T("<LocalAddresses>%s</LocalAddresses>\n"), (const TCHAR*)getLocalAddresses() );
    _tprintf(_T("<RemoteAddresses>%s</RemoteAddresses>\n"), (const TCHAR*)getRemoteAddresses() );
    _tprintf(_T("<IcmpTypesAndCodes>%s</IcmpTypesAndCodes>\n"), (const TCHAR*)getIcmpTypesAndCodes() );
    NET_FW_RULE_DIRECTION dir = getDirection();
    _tprintf(_T("<Direction>%s</Direction>\n"), (const TCHAR*)name.toString(dir) );
    _tprintf(_T("<InterfaceTypes>%s</InterfaceTypes>\n"), (const TCHAR*)getInterfaceTypes() );
    _tprintf(_T("<Enabled>%s</Enabled>\n"), name.toString(getEnabled()) );
    _tprintf(_T("<Grouping>%s</Grouping>\n"), (const TCHAR*)getGrouping() );
    NET_FW_PROFILE_TYPE2 type = (NET_FW_PROFILE_TYPE2)getProfiles() ;

    _tprintf(_T("<Profiles>%s</Profiles>\n"), (const TCHAR*)name.toStrings(type) );
  
    _tprintf(_T("<EdgeTraversal>%s</EdgeTraversal>\n"), (const TCHAR*)name.toString(getEdgeTraversal()) );
    NET_FW_ACTION action = getAction();
    _tprintf(_T("<Action>%s</Action>\n"), (const TCHAR*)name.toString(action) );
    displayInterfaces(hwnd);
    _tprintf(_T("</Rule>\n"));

  }

public:
  virtual void write(Writer& writer)
  {
    NetFwName name;
    writer.write(L"<Rule>\n");

    writer.write(L"<Name>%s</Name>\n", 
      (const wchar_t*)_bstr_t(getName() ) );
    writer.write(L"<Description>%s</Description>\n", 
      (const wchar_t*)_bstr_t(getDescription() ) );
    writer.write(L"<ApplicationName>%s</ApplicationName>\n", 
      (const wchar_t*)_bstr_t(getApplicationName() ) );
    writer.write(L"<ServiceName>%s</ServiceName>\n", 
      (const wchar_t*)_bstr_t(getServiceName() ) );
    NET_FW_IP_PROTOCOL protocol = (NET_FW_IP_PROTOCOL)getProtocol();
    writer.write(L"<Protocol>%s</Protocol>\n", 
      (const wchar_t*)_bstr_t(name.toString(protocol) ) );
    writer.write(L"<LocalPorts>%s</LocalPorts>\n", 
      (const wchar_t*)_bstr_t(getLocalPorts() ) );
    writer.write(L"<RemotePorts>%s</RemotePorts>\n", 
      (const wchar_t*)_bstr_t(getRemotePorts() ) );
    writer.write(L"<LocalAddresses>%s</LocalAddresses>\n", 
      (const wchar_t*)_bstr_t(getLocalAddresses() ) );
    writer.write(L"<RemoteAddresses>%s</RemoteAddresses>\n", 
      (const wchar_t*)_bstr_t(getRemoteAddresses() ) );
    writer.write(L"<IcmpTypesAndCodes>%s</IcmpTypesAndCodes>\n", 
      (const wchar_t*)_bstr_t(getIcmpTypesAndCodes() ) );
    NET_FW_RULE_DIRECTION dir = getDirection();
    writer.write(L"<Direction>%s</Direction>\n", 
      (const wchar_t*)_bstr_t(name.toString(dir) ) );
    writer.write(L"<InterfaceTypes>%s</InterfaceTypes>\n", 
      (const wchar_t*)_bstr_t(getInterfaceTypes() ) );
    writer.write(L"<Enabled>%s</Enabled>\n", 
      (const wchar_t*)_bstr_t(name.toString(getEnabled()) ) );
    writer.write(L"<Grouping>%s</Grouping>\n", 
      (const wchar_t*)_bstr_t(getGrouping() ) );

    NET_FW_PROFILE_TYPE2 type = (NET_FW_PROFILE_TYPE2)getProfiles() ;
    writer.write(L"<Profiles>%s</Profiles>\n", 
      (const wchar_t*)_bstr_t(name.toStrings(type) ) );
  
    writer.write(L"<EdgeTraversal>%s</EdgeTraversal>\n", 
      (const wchar_t*)_bstr_t(name.toString(getEdgeTraversal()) ) );

    NET_FW_ACTION action = getAction();
    writer.write(L"<Action>%s</Action>\n", 
      (const wchar_t*)_bstr_t(name.toString(action) ) );

    writeInterfaces(writer);

    writer.write(L"</Rule>\n");

  }

};


}

    
