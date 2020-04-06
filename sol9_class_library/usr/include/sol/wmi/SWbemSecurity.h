/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SWbemSecurity.h
 *
 *****************************************************************************/

// 2012/03/08 Updated. 

#pragma once

#include <sol/wmi/SWbemBaseObject.h>
#include <sol/wmi/SWbemPrivilegeSet.h>

namespace SOL {

class SWbemSecurity : public SWbemBaseObject {
    
public:
  SWbemSecurity(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemSecurity* get()
  {
    return (ISWbemSecurity*)getIDispatch();
  }

public:
  SWbemSecurity& operator=(ISWbemSecurity* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  WbemImpersonationLevelEnum getImpersonationLevel()
  {
    HRESULT hr = E_FAIL;
    ISWbemSecurity* security = get();
    WbemImpersonationLevelEnum iImpersonationLevel;

    hr = security -> get_ImpersonationLevel( 
      &iImpersonationLevel);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iImpersonationLevel;
  }        

public:
  HRESULT putImpersonationLevel( 
            __in WbemImpersonationLevelEnum iImpersonationLevel)
  {
    HRESULT hr = E_FAIL;
    ISWbemSecurity* security = get();

    hr = security -> put_ImpersonationLevel( 
      iImpersonationLevel);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  WbemAuthenticationLevelEnum getAuthenticationLevel()
  {
    HRESULT hr = E_FAIL;
    ISWbemSecurity* security = get();
    WbemAuthenticationLevelEnum iAuthenticationLevel;

    hr = security -> get_AuthenticationLevel( 
      &iAuthenticationLevel);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iAuthenticationLevel;
  }        


public:
/* 
WbemAuthenticationLevelEnum is the following:

  wbemAuthenticationLevelNone  
    Short name: None 
    Uses no authentication.
 
  wbemAuthenticationLevelConnect
    Short name: Connect 
    Authenticates the credentials of the client only when the client establishes a relationship with the server.
 
  wbemAuthenticationLevelCall
    Short name: Call 
    Authenticates only at the beginning of each call when the server receives the request.
 
  wbemAuthenticationLevelPkt
    Short name: Pkt 
    Authenticates that all data received is from the expected client.
 
  wbemAuthenticationLevelPktIntegrity
    Short name: PktIntegrity 
    Authenticates and verifies that none of the data transferred between client and server has been modified.
 
  wbemAuthenticationLevelPktPrivacy
    Short name: PktPrivacy 
    Authenticates all previous impersonation levels and encrypts the argument value of each remote procedure call.
*/

  HRESULT putAuthenticationLevel( 
            __in WbemAuthenticationLevelEnum iAuthenticationLevel)
  {
    HRESULT hr = E_FAIL;
    ISWbemSecurity* security = get();

    hr = security -> put_AuthenticationLevel( 
      iAuthenticationLevel);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  ISWbemPrivilegeSet* getPrivileges( 
      )
  {
    HRESULT hr = E_FAIL;
    ISWbemSecurity* security = get();
    ISWbemPrivilegeSet *objWbemPrivilegeSet = NULL;

    hr = security -> get_Privileges( 
        &objWbemPrivilegeSet);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return objWbemPrivilegeSet;
  }        

public:
  void write(Writer& writer)
  {
    writer.writeln(L"<Security>");
    WbemImpersonationLevelEnum impersonatioLevel = getImpersonationLevel();
    writer.writeln(L"<ImpersonationLevel>%d</ImpersonationLevel>", impersonatioLevel);
    WbemAuthenticationLevelEnum authLevel = getAuthenticationLevel();
    writer.writeln(L"<AuthenticationLevel>%d</AuthenticationLevel>", authLevel);

    try {
      SWbemPrivilegeSet set = getPrivileges();
      set.write(writer);
    } catch (...) {

    }
    writer.writeln(L"</Security>");

  }

};

}
