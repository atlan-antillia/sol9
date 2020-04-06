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
 *  NetManager.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/10

#pragma once

#include <sol/Object.h>
#include <lm.h>
//2009/11/16
#include <sol/StringT.h>

//2009/11/14
#pragma comment(lib, "netapi32.lib")

namespace SOL {

class NetManager :public Object {
private:
  //const wchar_t* serverName;
  StringT<wchar_t> serverName;

public:
  /**
   * Constructor
   * @param server server name
   */
  NetManager(const wchar_t* server=NULL)
    :serverName(L"")
  {
    if (server) {
      serverName = server;
    }
  }  


public:
  ~NetManager()
  {

  }

public:
  const wchar_t* getServerName()
  {
    return (const wchar_t*)serverName;
  }

public:
  void setServerName(const wchar_t* name)
  {
    serverName = name;
  }

};

}
