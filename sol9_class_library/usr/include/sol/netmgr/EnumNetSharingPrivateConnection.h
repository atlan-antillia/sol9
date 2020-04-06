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
 *  EnumNetSharingPrivateConnection.h
 *
 *****************************************************************************/

//2012/08/29

#pragma once

#include <sol/com/EnumVariant.h>
#include <netcon.h>
#include <sol/netcon/NetConnection.h>

namespace SOL {

class EnumNetSharingPrivateConnection: public EnumVariant {

public:    
  EnumNetSharingPrivateConnection(IEnumVARIANT* pVar)
    :EnumVariant(pVar)
  {
  }

public:
  INetConnection* nextConnection()
  {
    INetConnection* pCon = NULL;
    IUnknown* pUnk = EnumVariant::nextIUnknown();
    
    HRESUL hr = pUnk -> QueryInterface (__uuidof(INetConnection),
                  (void**)&pCon);
    pUnk -> Release();
    if (FAILED(hr)) {
      throw hr;
    }
    return pCon;
  }

public:

  IEnumNetSharingPrivateConnection* clone()
  {
      return (IEnumNetSharingPrivateConnection*) EnumVariant::clone();
  }    

public:
  virtual void display(HWND hwnd=NULL)
  {
    while (true) {
      try {
        NetConnection connection = nextConnection();
        connection.display();
      } catch (...) {
        break;
      }

    }
  }

};

}
    
