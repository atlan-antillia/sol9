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
 *  SWbemBaseObject.h
 *
 *****************************************************************************/


#pragma once

#define _WIN32_DCOM

#include <sol/Object.h>
#include <sol/com/ComObject.h>
#include <sol/BString.h>
#include <sol/com/EnumVariant.h>
//2009/12/22

#include <sol/LocalDateTime.h>
#include <sol/wmi/WbemErrors.h>

#include <wbemidl.h>
#include <wbemdisp.h>

#pragma comment(lib, "wbemuuid.lib")

namespace SOL {

class SWbemBaseObject :public ComObject {
  

public:
  SWbemBaseObject(IDispatch* pDispatch=NULL)
    :ComObject(pDispatch)
  {
  }

public:
  ~SWbemBaseObject()
  {
  }

public:
  virtual void display()
  {
    printf("SWbemBaseObject::display\n");
  }

};


}
