
/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IHTMLView.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed a IE browser control 
(an OLE object) into your own window.
Basically, this is based on a C++ example written by Chris Becke.
For C version, see http://www.codeproject.com/com/cwebpage.asp.
*/

// SOL9
// 2008/08/11

#pragma once

#include <sol\Object.h>
#include <sol\Composite.h>

//
// IHTMLView.h

namespace SOL {

/**
 * Abstract class with pure virtual functions.
 */
class IHTMLView :public Composite {

public:
  IHTMLView() {}

public:
  ~IHTMLView() { }

public:

  virtual  void createWebControl(void)    = 0;

  virtual  void destroyWebControl(void)  = 0;

  virtual  void navigate(const TCHAR* url) = 0;  

  virtual IOleInPlaceFrame* getInPlaceFrame() = 0;
  
  virtual IOleObject* getOleObject() = 0;

  //2008/08/11
  virtual HRESULT execWB(OLECMDID cmdID, OLECMDEXECOPT option, VARIANT* pvaIn, VARIANT* pvalOut) = 0;

  virtual void zoom(int level) = 0;

};

}
