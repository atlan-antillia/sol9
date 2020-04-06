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
 *  Clipboard.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>
#include <sol\View.h>


namespace SOL {

class Clipboard :public Object {
  View*  owner;
  BOOL  status;
  public:
  Clipboard(View* owner1) {
    owner = owner1;
    status = ::OpenClipboard(owner.getWindow());
  }
  BOOL  close() {
      return ::CloseClipboard();
  }
  int  countFormats() {
      return ::CountClipboardFormats();
  }
  BOOL  empty() {
      return ::EmptyClipboard();
  }
  HANDLE  getData(UINT format) {
      return ::GetClipboardData(format);
  }
  int    getFormatName(UINT format, String buff, int max) {
      return ::GetClipboardFormatName(format, buff, max);
  }
  View*  getOwner() {
      return owner;
  }
  void  set(UINT format, HANDLE hdata) {
      ::SetClipboardData(format, hdata);
  }
};

}


