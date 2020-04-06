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
 *  WMPMetadataText.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/HTMLEncoder.h>

namespace SOL {

class WMPMetadataText :public WMPObject 
{
private:
  IWMPMetadataTextPtr text;

public:
  WMPMetadataText(IWMPMetadataTextPtr ptr)
  :text(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPMetadataTextPtr is NULL", 0);
    }
  }

public:
  ~WMPMetadataText()
  {
    text = NULL;
  }

  _bstr_t getDescription ( )
  {
    return text ->GetDescription ( );
  }

  _bstr_t getText ( )
  {
    return text ->Gettext ( );
  }

public:
  virtual void showProperties(HWND hwnd=NULL) 
  {
    _tprintf(_T("<MetadataText>\n"));
    _bstr_t desc = getDescription();
    _bstr_t txt =  getText();
    _bstr_t bdesc;
    _bstr_t btxt;
    HTMLEncoder encoder;
    encoder.encode(desc, bdesc);
    encoder.encode(txt, btxt);
    _tprintf(_T("<Description>%s</Description>\n"), (const TCHAR*)bdesc);
    _tprintf(_T("<Text>%s</Text>\n"), (const TCHAR*)btxt);

    _tprintf(_T("</MetadataText>\n"));
  }
public:
  virtual void writeProperties(Writer& writer) 
  {
    writer.writeln(L"<MetadataText>");
    _bstr_t desc = getDescription();
    _bstr_t txt =  getText();
    _bstr_t bdesc;
    _bstr_t btxt;
    HTMLEncoder encoder;
    encoder.encode(desc, bdesc);
    encoder.encode(txt, btxt);
    writer.writeln(L"<Description>%s</Description>", (const wchar_t*)bdesc);
    writer.writeln(L"<Text>%s</Text>", (const wchar_t*)btxt);

    writer.writeln(L"</MetadataText>");
  }
};

}
