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
 *  EnumNetConnection.h
 *
 *****************************************************************************/

//2012/09/11

#pragma once

#include <sol/com/ComIDispatch.h>
#include <netfw.h>

/*
//Usage:
{
  ApartmentThreadedModel model;
  NetFwMgr mgr;
  NetFwPolicy  policy = mgr.getLocalPolicy();
}
*/

namespace SOL {

class NetFwPolicy: public ComIDispatch {

public:
  NetFwPolicy(INetFwPolicy* pPolicy=NULL)
    :ComIDispatch(pPolicy)
  {
  }

private:
  INetFwPolicy* getPolicy()
  {
    return (INetFwPolicy*) getIDispatch();
  }

public:
  HRESULT getCurrentProfile( 
            /* [retval][out] */ INetFwProfile **profile)
  {
    HRESULT hr = getPolicy() -> get_CurrentProfile( 
        profile);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  INetFwProfile* getCurrentProfile()
  {
    INetFwProfile* pProfile = NULL;
    HRESULT hr = getPolicy() -> get_CurrentProfile( 
        &pProfile);
    if (FAILED(hr)) {
      throw hr;
    }
    return pProfile;
  }

public:
/*
NET_FW_PROFILE_TYPE profileType. Specify one of the following values:  
  NET_FW_PROFILE_DOMAIN,
  NET_FW_PROFILE_STANDARD,
  NET_FW_PROFILE_CURRENT,
*/
  HRESULT getProfileByType(
            /* [in] */ NET_FW_PROFILE_TYPE profileType,
            /* [retval][out] */ INetFwProfile **profile)
  {
    HRESULT hr = getPolicy() -> GetProfileByType( 
          profileType,
          profile);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        
public:
  INetFwProfile* getDomainProfile()
  {
    return getProfileByType(NET_FW_PROFILE_DOMAIN);
  }

public:
  INetFwProfile* getStandardProfile()
  {
    return getProfileByType(NET_FW_PROFILE_STANDARD);
  }

public:
  INetFwProfile* getProfileByType( 
            /* [in] */ NET_FW_PROFILE_TYPE profileType)
  {
    INetFwProfile* pProfile = NULL;
    HRESULT hr = getPolicy() -> GetProfileByType( 
          profileType,
          &pProfile);
    if (FAILED(hr)) {
      throw hr;
    }
    return pProfile;
  }    
};

}
