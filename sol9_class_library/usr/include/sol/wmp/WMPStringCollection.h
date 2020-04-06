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
 *  WMPStringCollection.h
 *
 *****************************************************************************/


// SOL9
// 2011/12/21

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/HTMLEncoder.h>

namespace SOL {

class WMPStringCollection :public WMPObject {

private:
  IWMPStringCollection2Ptr collection;

public:
  WMPStringCollection(IWMPStringCollection2Ptr ptr)
    :collection(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPStringCollectionPtr is NULL", 0);
    }
  }

public:
  ~WMPStringCollection()
  {
    collection = NULL;
  }

public:
  long getCount()
  {
    return collection->Getcount();
  }

  _bstr_t item(long lIndex)
  {
    return collection->Item(lIndex);
  }

  //<IWMPStringCollection2>
  VARIANT_BOOL isIdentical(struct IWMPStringCollection2 * pIWMPStringCollection2)
  {
    return collection->isIdentical(pIWMPStringCollection2);

  }
    
    
  _bstr_t getItemInfo(long lCollectionIndex, _bstr_t bstrItemName)
  {
    return collection->getItemInfo(lCollectionIndex, bstrItemName);
  }

  long getAttributeCountByType(long lCollectionIndex, _bstr_t bstrType, _bstr_t bstrLanguage)
  {
    return collection->getAttributeCountByType(lCollectionIndex, bstrType, bstrLanguage);
  }

  _variant_t getItemInfoByType(long lCollectionIndex, _bstr_t bstrType,
    _bstr_t bstrLanguage, long lAttributeIndex)
  {
    return collection->getItemInfoByType(lCollectionIndex, bstrType,
        bstrLanguage, lAttributeIndex);
  }
  //</IWMPStringCollection2>

public:
  void show(_bstr_t attribute, _bstr_t mediaType)
  {
    long count = getCount();
    _tprintf(_T("<StringCollection Attribute=\"%s\" MediaType=\"%s\" >\n"),
      (const TCHAR*)attribute, (const TCHAR*)mediaType);
    for (long i = 0; i<count; i++) {
      _bstr_t name = item(i);
      _bstr_t bname;
      HTMLEncoder encoder;
      encoder.encode(name, bname);
      _tprintf(_T("<Item Name=\"%s\" />\n"), (const TCHAR*)bname);
    }
    _tprintf(_T("</StringCollection>\n"));
  }

public:
  //2012/01/22
  void write(_bstr_t attribute, _bstr_t mediaType, Writer& writer)
  {
    long count = getCount();
    writer.writeln(L"<StringCollection Attribute=\"%s\" MediaType=\"%s\" >",
      (const wchar_t*)attribute, (const wchar_t*)mediaType);

    for (long i = 0; i<count; i++) {
      _bstr_t name = item(i);
      _bstr_t bname;
      HTMLEncoder encoder;
      encoder.encode(name, bname);
      writer.writeln(L"<Item Name=\"%s\" />", (const wchar_t*)bname);
    }
    writer.writeln(L"</StringCollection>");

  }
};

}

