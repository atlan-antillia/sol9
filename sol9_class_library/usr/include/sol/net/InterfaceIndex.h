/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  InterfaceGuid.h
 *
 *****************************************************************************/

// SOL9
// 2011/1/1
#include <sol/Object.h>
#include <sol/StringT.h>

namespace SOL {

class InterfaceIndex :public Object {

private:
  NET_IFINDEX index

public:
  InterfaceIndex(__in const NET_IFINDEX id)
  :index(id)
  {
  }

public:
  
  NETIO_STATUS toLuid(__out NET_LUID *luid)
  {
    return toLuid(index, luid);
  } 

public:
  
  static NETIO_STATUS toLuid(__const NET_IFINDEX index, __out NET_LUID *luid)
  {
    //If sucess, this returns NO_ERROR
    return ConvertInterfaceIndexToLuid(index, luid);
  } 
};


}
