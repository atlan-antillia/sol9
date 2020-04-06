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
 *  WMPErrorItem.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/21

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/wmp/WMPErrorItem.h>


namespace SOL {


class WMPErrorItem :public WMPObject {

private:
  IWMPErrorItemPtr item;

public:
  WMPErrorItem(IWMPErrorItemPtr ptr)
  :item(ptr)
  {
    if(ptr == NULL) {
      throw NullPointerException("IWMPErrorItemPtr is NULL", 0);
    }
  }

public:
  ~WMPErrorItem()
  {
    item = NULL;
  }

  long getErrorCode()
  {
    return item->GeterrorCode();
  }

  _bstr_t getErrorDescription()
  {
    return item->GeterrorDescription();
  }

  _variant_t getErrorContext()
  {
    return item->GeterrorContext();
  }

  long getRemedy()
  {
    return item->Getremedy();
  }

  _bstr_t getCustomUrl()
  {
    return item->GetcustomUrl();
  }

public:
  void show()
  {
    _tprintf(_T("<ErrorItem>\n"));
    _tprintf(_T("<ErrorCode>%x</ErrorCode>\n"), getErrorCode());
    _tprintf(_T("<ErrorDescription>%s</ErrorDescription>\n"),(const TCHAR*)getErrorDescription());

    try {
      _tprintf(_T("<Remedy>%x</Remedy>\n"), getRemedy());
    } catch (...) {
      //printf("Failed to getRemedy()\n");
    }
    try {
      _tprintf(_T("<CustomUrl>%s</CustomUrl>\n"),(const TCHAR*)getCustomUrl());
    } catch (...) {
      //printf("Faiied to getCustomUrl()\n");
    }
    _tprintf(_T("</ErrorItem>\n"));
  }

public:
  void write(Writer& writer)
  {
    writer.writeln(L"<ErrorItem>");
    writer.writeln(L"<ErrorCode>%x</ErrorCode>", getErrorCode());
    writer.writeln(L"<ErrorDescription>%s</ErrorDescription>",(const wchar_t*)getErrorDescription());

    try {
      writer.writeln(L"<Remedy>%x</Remedy>", getRemedy());
    } catch (...) {
      //printf("Failed to getRemedy()\n");
    }
    try {
      writer.writeln(L"<CustomUrl>%s</CustomUrl>",(const wchar_t*)getCustomUrl());
    } catch (...) {
      //printf("Faiied to getCustomUrl()\n");
    }
    writer.writeln(L"</ErrorItem>");
  }

};

}
