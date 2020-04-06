
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
 *  WMPMetadataPicture.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/HTMLEncoder.h>
// 2012/01/08
#include <sol/wininet/UrlCacheEntry.h>

namespace SOL {

class WMPMetadataPicture :public WMPObject
{
private:
  IWMPMetadataPicturePtr picture;

public:
  WMPMetadataPicture(IWMPMetadataPicturePtr ptr)
  :picture(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPMetadataPicturePtr is NULL", 0);
    }
  }

public:
  ~WMPMetadataPicture()
  {
    picture = NULL;
  }

public:

  _bstr_t getMimeType ( )
  {
    return picture->GetmimeType ( );
  }

  _bstr_t getPictureType ( )
  {
    return picture->GetpictureType ( );
  }

  _bstr_t getDescription ( )
  {
    return picture->GetDescription ( );
  }

  _bstr_t getURL ( )
  {
    return picture-> GetURL ( );
  }

public:
  virtual void showProperties(HWND hwnd=NULL) 
  {
    _tprintf(_T("<MetadataPicture>\n"));
    _bstr_t mimeType = getMimeType();
    _bstr_t pictType = getPictureType();
    _bstr_t desc     = getDescription();
    _bstr_t url      = getURL();
    _bstr_t bmimeType, bpictType, bdesc, burl;

    HTMLEncoder encoder;
    encoder.encode(mimeType, bmimeType);
    encoder.encode(pictType, bpictType);
    encoder.encode(desc, bdesc);
    encoder.encode(url, burl);
    _tprintf(_T("<MimeType>%s</MimeType>\n"), (const TCHAR*)bmimeType);
    _tprintf(_T("<PictureType>%s</PictureType>\n"), (const TCHAR*)bpictType);
    _tprintf(_T("<Description>%s</Description>\n"), (const TCHAR*)bdesc);
    _tprintf(_T("<URL>%s</URL>\n"), (const TCHAR*)burl);
    try {
      _bstr_t localFile;
      UrlCacheEntry entry = url;
      entry.getLocalFileName(localFile);
      _bstr_t blocalFile;
      encoder.encode(localFile, blocalFile);
      _tprintf(_T("<LocalFileName>%s</LocalFileName>\n"), (const TCHAR*)blocalFile);

    } catch (...) {

    }
    _tprintf(_T("</MetadataPicture>\n"));
  }

public:
  //2012/01/22
  virtual void writeProperties(Writer& writer) 
  {
    writer.writeln(L"<MetadataPicture>");
    _bstr_t mimeType = getMimeType();
    _bstr_t pictType = getPictureType();
    _bstr_t desc     = getDescription();
    _bstr_t url      = getURL();
    _bstr_t bmimeType, bpictType, bdesc, burl;

    HTMLEncoder encoder;
    encoder.encode(mimeType, bmimeType);
    encoder.encode(pictType, bpictType);
    encoder.encode(desc, bdesc);
    encoder.encode(url, burl);
    writer.writeln(L"<MimeType>%s</MimeType>", (const wchar_t*)bmimeType);
    writer.writeln(L"<PictureType>%s</PictureType>", (const wchar_t*)bpictType);
    writer.writeln(L"<Description>%s</Description>", (const wchar_t*)bdesc);
    writer.writeln(L"<URL>%s</URL>", (const wchar_t*)burl);
    try {
      _bstr_t localFile;
      UrlCacheEntry entry = url;
      entry.getLocalFileName(localFile);
      _bstr_t blocalFile;
      encoder.encode(localFile, blocalFile);
      writer.writeln(L"<LocalFileName>%s</LocalFileName>", (const wchar_t*)blocalFile);

    } catch (...) {

    }
    writer.writeln(L"</MetadataPicture>");
  }

};

}
