/******************************************************************************
 *
 * Copyright (c) 1999-2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IPv4AddressInfo.h
 *
 *****************************************************************************/


// SOL9
// 2010/11/20

#pragma once

#include <sol/net/AddressInfo.h>


namespace SOL {

class IPv4AddressInfo :public AddressInfo {

public:
  IPv4AddressInfo(__in const ADDRINFOT* ptr=NULL)
    :AddressInfo(ptr)
  {
  }

public:
  ~IPv4AddressInfo()
  {
  }


public:
  /**
   * Get a copy of IPv4 sockaddr_in.  
   */
  void getSockAddr(__out sockaddr_in& addr) 
  {
    const sockaddr* address = AddressInfo::getSockAddr();
    if (address) {
      memcpy(&addr, address, sizeof(addr));
    }
  }
};

}

