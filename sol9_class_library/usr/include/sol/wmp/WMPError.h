/******************************************************************************
 *
 * Copyright(c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  WMPError.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/21

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/wmp/WMPErrorItem.h>


namespace SOL {


class WMPError :public WMPObject {

private:
  IWMPErrorPtr error;

public:
  WMPError(IWMPErrorPtr ptr)
  :error(ptr)
  {
    if(ptr == NULL) {
      throw NullPointerException("IWMPErrorPtr is NULL", 0);
    }
  }

public:
  ~WMPError()
  {
    error = NULL;
  }

  HRESULT clearErrorQueue ( )
  {
    return error->clearErrorQueue ( );
  }

  long getErrorCount ( )
  {
    return error->GeterrorCount ( );
  }

  IWMPErrorItemPtr getItem (long dwIndex )
  {
    return error->GetItem (dwIndex );
  }

  HRESULT webHelp ( )
  {
    return error->webHelp ( );
  }

public:
  void show(HWND hwnd=NULL)
  {
    _tprintf(_T("<Error>\n"));

    long count = getErrorCount();
    for (long i=0; i<count; i++) {
      WMPErrorItem item = getItem(i);
      item.show();
    }
    _tprintf(_T("</Error>\n"));
  }

  void write(Writer& writer)
  {
    writer.writeln(L"<Error>");

    long count = getErrorCount();
    for (long i=0; i<count; i++) {
      WMPErrorItem item = getItem(i);
      item.write(writer);
    }
    writer.writeln(L"</Error>");
  }
};

}
