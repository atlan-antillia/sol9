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
 *  NetFwName.h
 *
 *****************************************************************************/

//2012/09/15

#pragma once

#include <sol/Object.h>
#include <sol/ArgT.h>
#include <sol/ArgListT.h>
#include <sol/StringBufferT.h>

//#include <Icftypes.h>
#include <netfw.h>

namespace SOL {

class NetFwName: public Object {

public:
  NetFwName()

  {
  }

/* Windows8 
public:
  const TCHAR* toString(NET_FW_AUTHENTICATE_TYPE type)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("AUTHENTICATE_NONE"), NET_FW_AUTHENTICATE_NONE},
      {_T("AUTHENTICATE_NO_ENCAPSULATION"), NET_FW_AUTHENTICATE_NO_ENCAPSULATION},
      {_T("AUTHENTICATE_WITH_INTEGRITY"), NET_FW_AUTHENTICATE_WITH_INTEGRITY},
      {_T("AUTHENTICATE_AND_NEGOTIATE_ENCRYPTION"), NET_FW_AUTHENTICATE_AND_NEGOTIATE_ENCRYPTION},
      {_T("AUTHENTICATE_AND_ENCRYPT"), NET_FW_AUTHENTICATE_AND_ENCRYPT},  
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(type);
  }
*/
public:
  const TCHAR* toString(NET_FW_EDGE_TRAVERSAL_TYPE type)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("DENY"), NET_FW_EDGE_TRAVERSAL_TYPE_DENY},
      {_T("ALLOW"), NET_FW_EDGE_TRAVERSAL_TYPE_ALLOW},
      {_T("DEFER_TO_APP"), NET_FW_EDGE_TRAVERSAL_TYPE_DEFER_TO_APP},
      {_T("DEFER_TO_USER"), NET_FW_EDGE_TRAVERSAL_TYPE_DEFER_TO_USER} 
    };
    
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(type);

  }

public:
  const TCHAR* toString(NET_FW_MODIFY_STATE state)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("OK"), NET_FW_MODIFY_STATE_OK},
      {_T("GP_OVERRIDE"), NET_FW_MODIFY_STATE_GP_OVERRIDE},
      {_T("INBOUND_BLOCKED"), NET_FW_MODIFY_STATE_INBOUND_BLOCKED},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(state);
  }
public:
  _bstr_t toString(NET_FW_PROFILE_TYPE2 type)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("DOMAIN"), NET_FW_PROFILE2_DOMAIN},
      {_T("PRIVATE"), NET_FW_PROFILE2_PRIVATE},
      {_T("PUBLIC"), NET_FW_PROFILE2_PUBLIC},
      {_T("ALL"), NET_FW_PROFILE2_ALL} 
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(type);
  }

public:
  _bstr_t toStrings(NET_FW_PROFILE_TYPE2 types)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("DOMAIN"), NET_FW_PROFILE2_DOMAIN},
      {_T("PRIVATE"), NET_FW_PROFILE2_PRIVATE},
      {_T("PUBLIC"), NET_FW_PROFILE2_PUBLIC},
      //{_T("ALL"), NET_FW_PROFILE2_ALL} 
    };
    StringBufferT<TCHAR> buffer;
    int count = 0;
    for (int i = 0; i<CountOf(names); i++) {
      if (types & names[i].value) {
        if (count>0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        count++;
      }
    }
    return _bstr_t((const TCHAR*)buffer);
  }

public:
  const TCHAR* toString(NET_FW_RULE_CATEGORY cat)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("BOOT"), NET_FW_RULE_CATEGORY_BOOT},
      {_T("STEALTH"), NET_FW_RULE_CATEGORY_STEALTH},
      {_T("FIREWALL"), NET_FW_RULE_CATEGORY_FIREWALL},
      {_T("CONSEC"), NET_FW_RULE_CATEGORY_CONSEC},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(cat);
  }

public:
  const TCHAR* toString(NET_FW_IP_VERSION version)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("V4"), NET_FW_IP_VERSION_V4},
      {_T("V6"), NET_FW_IP_VERSION_V6},
      {_T("ANY"), NET_FW_IP_VERSION_ANY},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(version);
  }

public:
  const TCHAR* toString(NET_FW_PROFILE_TYPE type)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("DOMAIN"), NET_FW_PROFILE_DOMAIN},
      {_T("STANDARD"), NET_FW_PROFILE_STANDARD},
      {_T("CURRENT"), NET_FW_PROFILE_CURRENT},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(type);
  }

public:        
  const TCHAR* toString(NET_FW_RULE_DIRECTION dir)
  {
    //2012/09/26
    static const ArgT<TCHAR> names[] = {
      {_T("IN"), NET_FW_RULE_DIR_IN},
      {_T("OUT"), NET_FW_RULE_DIR_OUT},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(dir);
  }

public:        
  const TCHAR* toString(NET_FW_ACTION action)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("BLOCK"), NET_FW_ACTION_BLOCK},
      {_T("ALLOW"), NET_FW_ACTION_ALLOW},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(action);    
  }

public:
  const TCHAR* toString(NET_FW_IP_PROTOCOL protocol)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("TCP"), NET_FW_IP_PROTOCOL_TCP},
      {_T("UDP"), NET_FW_IP_PROTOCOL_UDP},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(protocol);
  }

public:        
  const TCHAR* toString(NET_FW_SCOPE value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("ALL"), NET_FW_SCOPE_ALL},
      {_T("LOCAL_SUBNET"), NET_FW_SCOPE_LOCAL_SUBNET},
      {_T("CUSTOM"), NET_FW_SCOPE_CUSTOM},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(value);    
  }

public:        
  const TCHAR* toString(NET_FW_SERVICE_TYPE type)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("FILE_AND_PRINT"), NET_FW_SERVICE_FILE_AND_PRINT},
      {_T("UPNP"), NET_FW_SERVICE_UPNP},
      {_T("REMOTE_DESKTOP"), NET_FW_SERVICE_REMOTE_DESKTOP},
      {_T("NONE"), NET_FW_SERVICE_NONE},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(type);    
  }

public:        
  const TCHAR* toString(bool value)
  {
    static const ArgT<TCHAR> names[] = {
      {_T("false"), false},
      {_T("true"), true},
    };
    ArgListT<TCHAR> argList(names, CountOf(names));
    return argList.getName(value);    
  }
};
 
}
