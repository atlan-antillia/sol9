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
 *  NetConnection.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/ComIUnknown.h>
#include <sol/Guid.h>
#include <netcon.h>
#include <sol/ArgT.h>
#include <sol/ArgListT.h>
#include <sol/StringBufferT.h>

namespace SOL {

class NetConnectionProperties: public Object{

private:
  NETCON_PROPERTIES* pProperties;

public:
  NetConnectionProperties(NETCON_PROPERTIES* pProp=NULL)
  :pProperties(pProp)
  {
  }

public:
  ~NetConnectionProperties()
  {
    clear();
  }

public:
  void clear()
  {
    if (pProperties) {
      CoTaskMemFree(pProperties->pszwName);
      CoTaskMemFree(pProperties->pszwDeviceName);
      
      CoTaskMemFree(pProperties);
      pProperties = NULL;
    }
  }

public:
  virtual void display(HWND hwnd=NULL)
  {
    _tprintf(_T("Guid = %s\n"), (const TCHAR*)getGuid() );
    _tprintf(_T("Name = %s\n"), (const TCHAR*)getName() );
    _tprintf(_T("DeviceName = %s\n"), (const TCHAR*)getDeviceName() );
    _tprintf(_T("Status = %s\n"), (const TCHAR*)getStatus() );
    _tprintf(_T("MediaType = %s\n"), (const TCHAR*)getMediaType() );
    _tprintf(_T("Character = %s\n"), (const TCHAR*)getCharacter() );
    _tprintf(_T("ThisClassId = %s\n"), (const TCHAR*)getThisClsId() );
    _tprintf(_T("UiClassId = %s\n"), (const TCHAR*)getUiClsId() );
    _tprintf(_T("\n"));
  }

public:
  GUID guid()
  {
    if (pProperties) {
      return pProperties->guidId;
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }


public:
  _bstr_t getGuid()
  {
    if (pProperties) {
      return Guid::toString(pProperties->guidId);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  _bstr_t getName()
  {
    if (pProperties) {
      return _bstr_t(pProperties->pszwName);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  _bstr_t getDeviceName()
  {
    if (pProperties) {
      return _bstr_t(pProperties->pszwDeviceName);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  NETCON_STATUS status()
  {
    if (pProperties) {
      return pProperties->Status;
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  NETCON_MEDIATYPE mediaType()
  {
    if (pProperties) {
      return pProperties->MediaType;
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  DWORD character()
  {
    if (pProperties) {
      return pProperties->dwCharacter;
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  GUID thisClsId()
  {
    if (pProperties) {
      return pProperties->clsidThisObject;
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  GUID uiClsId()
  {
    if (pProperties) {
      return pProperties->clsidUiObject;
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  const TCHAR* getStatus()
  {
    static ArgT<TCHAR> status[] = {
      {_T("DISCONNECTED"), NCS_DISCONNECTED},
      {_T("CONNECTING"), NCS_CONNECTING},
      {_T("CONNECTED"), NCS_CONNECTED},
      {_T("DISCONNECTING"), NCS_DISCONNECTING},
      {_T("HARDWARE_NOT_PRESENT"), NCS_HARDWARE_NOT_PRESENT},
      {_T("HARDWARE_DISABLED"), NCS_HARDWARE_DISABLED},
      {_T("HARDWARE_MALFUNCTION"), NCS_HARDWARE_MALFUNCTION},
      {_T("MEDIA_DISCONNECTED"), NCS_MEDIA_DISCONNECTED},
      {_T("AUTHENTICATING"), NCS_AUTHENTICATING},
      {_T("AUTHENTICATION_SUCCEEDED"), NCS_AUTHENTICATION_SUCCEEDED},
      {_T("NCS_AUTHENTICATION_FAILED"), NCS_AUTHENTICATION_FAILED},
      {_T("INVALID_ADDRESS"), NCS_INVALID_ADDRESS},
      {_T("CREDENTIALS_REQUIRED"), NCS_CREDENTIALS_REQUIRED} 
    };

    ArgListT<TCHAR> argList(status, CountOf(status));
    if (pProperties) {
      return argList.getName(pProperties->Status);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  const TCHAR* getMediaType()
  {
    static ArgT<TCHAR> type[] = {
      {_T("NONE"), NCM_NONE},
      {_T("DIRECT"), NCM_DIRECT},
      {_T("ISDN"), NCM_ISDN},
      {_T("LAN"), NCM_LAN},
      {_T("PHONE"), NCM_PHONE},
      {_T("TUNNEL"), NCM_TUNNEL},
      {_T("PPPOE"), NCM_PPPOE},
      {_T("BRIDGE"), NCM_BRIDGE},
      {_T("SHAREDACCESSHOST_LAN"), NCM_SHAREDACCESSHOST_LAN},
      {_T("SHAREDACCESSHOST_RAS"), NCM_SHAREDACCESSHOST_RAS} 
    };
      
    ArgListT<TCHAR> argList(type, CountOf(type));
    if (pProperties) {
      return argList.getName(pProperties->MediaType);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  _bstr_t getCharacter()
  {
    static ArgT<TCHAR> names[] = {
      {_T("NONE"), NCCF_NONE},
      {_T("ALL_USERS"), NCCF_ALL_USERS},
      {_T("ALLOW_DUPLICATION"), NCCF_ALLOW_DUPLICATION},
      {_T("ALLOW_REMOVAL"), NCCF_ALLOW_REMOVAL},
      {_T("ALLOW_RENAME"), NCCF_ALLOW_RENAME},
      {_T("INCOMING_ONLY"), NCCF_INCOMING_ONLY},
      {_T("OUTGOING_ONLY"), NCCF_OUTGOING_ONLY},
      {_T("BRANDED"), NCCF_BRANDED},
      {_T("SHARED"), NCCF_SHARED},
      {_T("BRIDGED"), NCCF_BRIDGED},
      {_T("FIREWALLED"), NCCF_FIREWALLED},
      {_T("DEFAULT"), NCCF_DEFAULT},
      {_T("HOMENET_CAPABLE"), NCCF_HOMENET_CAPABLE},
      {_T("SHARED_PRIVATE"), NCCF_SHARED_PRIVATE},
      {_T("QUARANTINED"), NCCF_QUARANTINED},
      {_T("RESERVED"), NCCF_RESERVED},
      {_T("BLUETOOTH_MASK"), NCCF_BLUETOOTH_MASK},
      {_T("LAN_MASK"), NCCF_LAN_MASK} 
    };

    if (pProperties) {
      StringBufferT<TCHAR> buffer;
      int count = 0;
      for (int i =0; i<CountOf(names); i++) {
        if (pProperties->dwCharacter & names[i].value) {
          if (count > 0) {
            buffer.append(_T("|"));
          }
          buffer.append(names[i].name);
          count++;
        }
      }
      return _bstr_t((const TCHAR*)buffer);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  _bstr_t getThisClsId()
  {
    if (pProperties) {
      return Guid::toString(pProperties->clsidThisObject);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }

public:
  _bstr_t getUiClsId()
  {
    if (pProperties) {
      return Guid::toString(pProperties->clsidUiObject);
    } else {
      throw Exception(0, "NETCON_PROPERTIES is NULL");
    }
  }
};

}


/*
typedef struct tagNETCON_PROPERTIES {
  GUID             guidId;
  LPWSTR           pszwName;
  LPWSTR           pszwDeviceName;
  NETCON_STATUS    Status;
  NETCON_MEDIATYPE MediaType;
  DWORD            dwCharacter;
  CLSID            clsidThisObject;
  CLSID            clsidUiObject;
} NETCON_PROPERTIES;

*/
