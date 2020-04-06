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
 *  WMPPlaylist.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/HTMLEncoder.h>

namespace SOL {

class WMPPlaylist :public WMPObject {

private:
  IWMPPlaylistPtr list;
 
public:
  WMPPlaylist(IWMPPlaylistPtr ptr)
  :list(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPPlaylistPtr is NULL", 0);
    }

  }

public:
  ~WMPPlaylist()
  {
    list = NULL;
  }

public:
  long getCount()
  {
    return list->Getcount();
  }

  _bstr_t getName()
  {
    return list->Getname();
  }

  void putName(_bstr_t pbstrName)
  {
    list->Putname(pbstrName);
  }

  long getAttributeCount()
  {
    return list->GetattributeCount();
  }
    
  _bstr_t getAttributeName(long lIndex)
  {
    return list->GetattributeName(lIndex);
  }
    
  IWMPMediaPtr getItem(long lIndex)
  {
    return list->GetItem(lIndex);
  }
    
  _bstr_t getItemInfo(_bstr_t bstrName)
  {
    return list->getItemInfo(bstrName);
  }

  HRESULT setItemInfo(_bstr_t bstrName, _bstr_t bstrValue)
  {
    return list->setItemInfo(bstrName, bstrValue);
  }

  VARIANT_BOOL getIsIdentical(
    struct IWMPPlaylist * pIWMPPlaylist)
  {
    return list->GetisIdentical(
      pIWMPPlaylist);
  }
    
  HRESULT clear()
  {
    return list->clear();
  }
    
  HRESULT insertItem(long lIndex, struct IWMPMedia * pIWMPMedia)
  {
    return list->insertItem(lIndex, pIWMPMedia);
  }
    
  HRESULT appendItem(struct IWMPMedia * pIWMPMedia)
  {
    return list->appendItem(
      pIWMPMedia);
  }

  HRESULT removeItem(
    struct IWMPMedia * pIWMPMedia)
  {
    return list->removeItem(
      pIWMPMedia);
  }
    
  HRESULT moveItem(
    long lIndexOld,
    long lIndexNew)
  {
    return list->moveItem(lIndexOld, lIndexNew);
  }

    //
public:
  void showProperties(HWND hwnd=NULL)
  {
    _tprintf(_T("<Playlist>\n"));
    _tprintf(_T("<Count>%d</Count>\n"), getCount());
    _tprintf(_T("<Name>%s</Name>\n"), (const TCHAR*)getName());
    long count = getAttributeCount();
    _tprintf(_T("<AttributeCount>%d</AttributeCount>\n"), count);

    _tprintf(_T("<Attributes>\n"));
    for (long i = 0; i<count; i++) {    
      _bstr_t name  = getAttributeName(i);
      _bstr_t value = getItemInfo(name);
      _bstr_t bname;
      _bstr_t bvalue;

      HTMLEncoder encoder;
      encoder.encode(name, bname);
      encoder.encode(value, bvalue);

      _tprintf(_T("<Attribute Name=\"%s\" Value=\"%s\" />\n"), 
        (const TCHAR*)bname, (const TCHAR*)bvalue);
    }
    _tprintf(_T("</Attributes>\n"));
    _tprintf(_T("</Playlist>\n"));
  }

public:
  void writeProperties(Writer& writer)
  {
    writer.writeln(L"<Playlist>");
    writer.writeln(L"<Count>%d</Count>", getCount());
    writer.writeln(L"<Name>%s</Name>", (const wchar_t*)getName());
    long count = getAttributeCount();
    writer.writeln(L"<AttributeCount>%d</AttributeCount>", count);

    writer.writeln(L"<Attributes>");
    for (long i = 0; i<count; i++) {    
      _bstr_t name  = getAttributeName(i);
      _bstr_t value = getItemInfo(name);
      _bstr_t bname;
      _bstr_t bvalue;

      HTMLEncoder encoder;
      encoder.encode(name, bname);
      encoder.encode(value, bvalue);

      writer.writeln(L"<Attribute Name=\"%s\" Value=\"%s\" />", 
        (const wchar_t*)bname, (const wchar_t*)bvalue);
    }
    writer.writeln(L"</Attributes>");
    writer.writeln(L"</Playlist>");
  }

};

}
