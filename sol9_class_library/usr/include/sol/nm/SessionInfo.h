/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SessionInfo.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/NetInfo.h>

namespace SOL {

class SessionInfo: public NetInfo {

public:
  /**
   * Constructor
   */
  SessionInfo(int lv=0)
  :NetInfo(lv)
  {
  }

public:
  /**
   * Destructor
   */
  ~SessionInfo()
  {
  }

public:
  const wchar_t* getUserFlags(DWORD flag) 
  {
    static const ArgT<wchar_t> types[] = {
      {L"GUEST", SESS_GUEST},       //The user using a guest account. 
      {L"NOENCRYPTION", SESS_NOENCRYPTION},  //The session without using password encryption.
    };
    int count = XtNumber(types);
    const wchar_t* name = L"";
    for (int i = 0; i<count; i++) {
      if (types[i].value == flag) {
        name = types[i].name;
      }
    }
    return name;
  }
};

}
