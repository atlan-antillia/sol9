/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Object.h
 *
 *****************************************************************************/

// SOL9 
// 2017/07/30 Updated 

// 2015/12/19
#pragma warning(disable: 4100)
#pragma warning(disable: 4456) //2017/01/25
#pragma warning(disable: 4458) //2017/01/25
#pragma warning(disable: 4477) //2017/01/25
#pragma warning(disable: 4819) //2017/03/10
#pragma warning(disable: 4311) //2017/03/10
#pragma warning(disable: 4312) //2017/03/10
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4302)

#pragma once

//To avoid compilatiion errors, you may need the following line.
#define STRSAFE_LIB

#define STRICT_TYPED_ITEMIDS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <io.h>
#include <time.h>


#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <exdisp.h>
#include <mshtml.h>

#include <commctrl.h>
#include <objbase.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <comdef.h>
#include <shellapi.h>
#include <process.h>

#include <locale.h>

#include <sol/Wchardef.h>

#include <sol\auxdef.h>

#include <sol/TypeConverter.h>

#ifdef _SOL32_DISABLE_WARNING
#pragma warning(disable:4996)
#endif

#include <sol/Wchardef.h>

#ifdef _DEBUG
#define _soltrace  printf
#else
#define _soltrace
#endif

#include <assert.h>
#include <sys/stat.h>
#include <errno.h>

//2016/12/05
#include <sol/Exception.h>
#include <sol/UnknownException.h>

#include <sol/SmartPtr.h>

namespace SOL {
/**
 * Class Object. The base class of SOL7 class library.
 */
class Object {
  int id;

public:
  /**
   * Constructor
   */
  Object() { id = 0; }

  /**
   * Destructor
   */
  virtual ~Object() { }

  /**
   * Virtual compare method.
   */
  virtual int   compare(Object* ) { return 0; }

  /**
   * Virutal dump method.
   */
  virtual void  dump() { }

  /**
   * Return id member of this object.
   */
  int    getId() { return id; }  

  /**
   * Set val to the member id of this object
   */
  void  setId(int val) { id = val; }

  /**
   * Virtual toString method.
   */
  //2012/02/25
  virtual _bstr_t toString() { return _bstr_t("Object"); }

  virtual void display() { }

};

}

using namespace SOL;

