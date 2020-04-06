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
 *  WMPMedia.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07
// 2012/01/05 Updated

#pragma once

#include <sol/wmp/WMPObject.h>
#include <sol/HTMLEncoder.h>

//2012/01/05
#include <sol/wmp/WMPMetadataPicture.h>
#include <sol/wmp/WMPMetadataText.h>

#include <sol/Writer.h>

namespace SOL {

class WMPMedia :public WMPObject {

private:
  IWMPMedia3Ptr media;

public:
  WMPMedia(IWMPMediaPtr ptr)
  :media(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPMediaPtr is NULL", 0);
    }
  }

public:
  ~WMPMedia()
  {
    media = NULL;  
  }

public:
  IWMPMediaPtr getMedia()
  {
    return media;
  }


  VARIANT_BOOL getIsIdentical(struct IWMPMedia * pIWMPMedia)
  {
    return media->GetisIdentical(pIWMPMedia);
  }

  _bstr_t getSourceURL()
  {
    return media->GetsourceURL();
  }


  _bstr_t getName()
  {
    return media->Getname();
  }


  void putName(_bstr_t pbstrName)
  {
    media->Putname(pbstrName);
  }


  long getImageSourceWidth()
  {
    return media->GetimageSourceWidth();
  }

  
  long getImageSourceHeight()
  {
    return media->GetimageSourceHeight();
  }

  
  long getMarkerCount()
  {
    return media->GetmarkerCount();
  }


  double getMarkerTime(long markerNum)
  {
    return media->getMarkerTime(markerNum);
  }

  
  _bstr_t getMarkerName(long markerNum)
  {
    return media->getMarkerName(markerNum);
  }

  
  double getDuration()
  {
    return media->Getduration();
  }

  
  _bstr_t getDurationString()
  {
    return media->GetdurationString();
  }

  
  long getAttributeCount()
  {
    return media->GetattributeCount();
  }

  
  _bstr_t getAttributeName(long lIndex)
  {
    return media->getAttributeName(lIndex);
  }


  _bstr_t getItemInfo(_bstr_t bstrItemName)
  {
    return media->getItemInfo(bstrItemName);
  }

  //2011/12/23
  //This returns a string "True" or "False" for Cdrom, but returns an empty string "" for other media.
  _bstr_t isSelectedForRip()
  {
    return media->getItemInfo(_bstr_t("SelectedForRip"));
  }

  //2011/12/29
  HRESULT selectForRip(bool flag)
  {
    _bstr_t bflag = "False";
    if (flag) {
      bflag = "True";
    }
    return media->setItemInfo(_bstr_t("SelectedForRip"), bflag);
  }

  HRESULT setItemInfo(_bstr_t bstrItemName, _bstr_t bstrVal)
  {
    return media->setItemInfo(bstrItemName, bstrVal);
  }


  _bstr_t getItemInfoByAtom(long lAtom)
  {
    return media->getItemInfoByAtom(lAtom);
  }



  VARIANT_BOOL isMemberOf(struct IWMPPlaylist * pPlaylist)
  {
    return media->isMemberOf(pPlaylist);

  }

  VARIANT_BOOL isReadOnlyItem(_bstr_t bstrItemName)
  {
    return media->isReadOnlyItem(bstrItemName);
  }

//<IWMPMedia2>
  IWMPErrorItemPtr getError ( )
  {
    return media->GetError ( );
  }
//</IWMPMedia2>


//<IWMPMedia3>
  long getAttributeCountByType (
        _bstr_t bstrType,
        _bstr_t bstrLanguage )
  {
    return media->getAttributeCountByType (
      bstrType,
      bstrLanguage );
  }

  _variant_t getItemInfoByType (
        _bstr_t bstrType,
        _bstr_t bstrLanguage,
        long lIndex )
  {
    return media->getItemInfoByType (
      bstrType,
      bstrLanguage,
      lIndex );
  }
//</IWMPMedia3>

//2012/01/04
public:
  IWMPMetadataPicturePtr getMetadataPicture()
  {
    IWMPMetadataPicturePtr picture = NULL;
    _bstr_t type = "WM/Picture";
    _bstr_t lang = "";
    long count = getAttributeCountByType(type, lang);

    for (long n = 0; n<count; n++) {
      _variant_t var = getItemInfoByType (type, lang, n);
      if (var.vt == VT_DISPATCH) {
        IWMPMetadataPicture* ipicture = NULL;

        if (SUCCEEDED(var.pdispVal->QueryInterface(
              __uuidof(IWMPMetadataPicture), (void**)&ipicture)) ) {
          picture = ipicture;
            break;
        }
      }
    }
    return picture;
  }

//2012/01/04
public:
  IWMPMetadataTextPtr getMetadataText()
  {
    IWMPMetadataTextPtr text = NULL;
    _bstr_t type = "WM/Text";
    _bstr_t lang = "";
    long count = getAttributeCountByType(type, lang);

    for (long n = 0; n<count; n++) {
      _variant_t var = getItemInfoByType (type, lang, n);
      if (var.vt == VT_DISPATCH) {
        IWMPMetadataText* itext = NULL;

        if (SUCCEEDED(var.pdispVal->QueryInterface(
              __uuidof(IWMPMetadataText), (void**)&itext)) ) {
          text = itext;
          break;
        }
      }
    }
    return text;
  }


public:
  virtual void showProperties(HWND hwnd=NULL)
  {
    HTMLEncoder encoder;
    _bstr_t url;
    encoder.encode((const wchar_t*)getSourceURL(), url);
    _tprintf(_T("<Media>\n"));    

    _tprintf(_T("<Name>%s</Name>\n"), (const TCHAR*)getName());    
    _tprintf(_T("<SourceURL>%s</SourceURL>\n"), (const TCHAR*)url);      
    _tprintf(_T("<ImageSourceWidth>%d</ImageSourceWidth>\n"), getImageSourceWidth());    
    _tprintf(_T("<ImageSourceHeight>%d</ImageSourceHeight>\n"), getImageSourceHeight());    

    long mc = getMarkerCount();    
    _tprintf(_T("<Marker Count=\"%d\">\n"), mc);    

    for (long i = 0; i<mc; i++) {
      //double mtime = getMarkerTime(i);
      _tprintf(_T("<MarkerTime>%f</MarkerTime>\n<MarkerName>%s</MarkerName>\n"),
          media->getMarkerTime(i),
        (const TCHAR*)getMarkerName(i)
        );
    }
    _tprintf(_T("</Marker>\n"));    
    _tprintf(_T("<Duration>%f</Duration>\n"),  getDuration());
    _tprintf(_T("<DurationString>%s</DurationString>\n"), (const TCHAR*) getDurationString());
    _tprintf(_T("<SelectedForRip>%s</SelectedForRip>\n"), (const TCHAR*)isSelectedForRip());

    long count = getAttributeCount();
    _tprintf(_T("<Attributes Count=\"%d\">\n"), count);    
    
    for (long n = 0; n<count; n++) {
      _bstr_t name = getAttributeName(n);
      _bstr_t value = getItemInfo(name);      

      _bstr_t isReadOnly = "";
      if (isReadOnlyItem(name) == VARIANT_TRUE) {
        isReadOnly = "ReadOnly=\"True\"";
      }
      _bstr_t bname;
      _bstr_t bvalue;
      encoder.encode((const wchar_t*)name, bname);
      encoder.encode((const wchar_t*)value, bvalue);
      
      _tprintf(_T("<Attribute Name=\"%s\" Value=\"%s\" %s/>\n"),
        (const TCHAR*)bname,
        (const TCHAR*)bvalue,
        (const TCHAR*)isReadOnly);
    }
    _tprintf(_T("</Attributes>\n"));

    //2012/01/05
    try {
      WMPMetadataPicture picture = getMetadataPicture();
      picture.showProperties();
    } catch (...) {
    }
    try {
      WMPMetadataText text = getMetadataText();
      text.showProperties();
    } catch (...) {
    }
    _tprintf(_T("</Media>\n"));    
  } 

public:
  //2012/01/22
  virtual void writeProperties(Writer& writer)
  {
    HTMLEncoder encoder;
    _bstr_t url;
    encoder.encode((const wchar_t*)getSourceURL(), url);
    writer.writeln(L"<Media>");    

    writer.writeln(L"<Name>%s</Name>", (const wchar_t*)getName());    
    writer.writeln(L"<SourceURL>%s</SourceURL>", (const wchar_t*)url);      
    writer.writeln(L"<ImageSourceWidth>%d</ImageSourceWidth>", getImageSourceWidth());    
    writer.writeln(L"<ImageSourceHeight>%d</ImageSourceHeight>", getImageSourceHeight());    

    long mc = getMarkerCount();    
    writer.writeln(L"<Marker Count=\"%d\">", mc);    

    for (long i = 0; i<mc; i++) {
      //double mtime = getMarkerTime(i);
      writer.writeln(L"<MarkerTime>%f</MarkerTime>\r\n<MarkerName>%s</MarkerName>",
          media->getMarkerTime(i),
        (const wchar_t*)getMarkerName(i)
        );
    }
    writer.writeln(L"</Marker>");    

    writer.writeln(L"<Duration>%f</Duration>",  getDuration());
    writer.writeln(L"<DurationString>%s</DurationString>", (const wchar_t*) getDurationString());
  
    writer.writeln(L"<SelectedForRip>%s</SelectedForRip>", (const wchar_t*)isSelectedForRip());

    long count = getAttributeCount();
    writer.writeln(L"<Attributes Count=\"%d\">", count);    
    
    for (long n = 0; n<count; n++) {
      _bstr_t name = getAttributeName(n);
      _bstr_t value = getItemInfo(name);      

      _bstr_t isReadOnly = "";
      if (isReadOnlyItem(name) == VARIANT_TRUE) {
        isReadOnly = "ReadOnly=\"True\"";
      }
      _bstr_t bname;
      _bstr_t bvalue;
      encoder.encode((const wchar_t*)name, bname);
      encoder.encode((const wchar_t*)value, bvalue);
      
      writer.writeln(L"<Attribute Name=\"%s\" Value=\"%s\" %s/>",
        (const wchar_t*)bname,
        (const wchar_t*)bvalue,
        (const wchar_t*)isReadOnly);
    }
    writer.writeln(L"</Attributes>");

    //2012/01/05
    try {
      WMPMetadataPicture picture = getMetadataPicture();
      picture.writeProperties(writer);
    } catch (...) {
    }

    try {
      WMPMetadataText text = getMetadataText();
      text.writeProperties(writer);
    } catch (...) {
    }

    writer.writeln(L"</Media>");    
  } 
};

}
