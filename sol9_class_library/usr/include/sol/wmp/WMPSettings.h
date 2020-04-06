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
 *  WMPSettings.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>

namespace SOL {

class WMPSettings :public WMPObject
{
private:
  IWMPSettings2Ptr settings;
    //

public:
  WMPSettings(IWMPSettingsPtr ptr)
  :settings(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPSettingsPtr is NULL", 0);
    }
  }

public:
  ~WMPSettings()
  {
    settings = NULL;
  }

public:
  // IWMPSettings
  VARIANT_BOOL getIsAvailable(_bstr_t bstrItem)
  {
    return settings->GetisAvailable(bstrItem);
  }

  VARIANT_BOOL getAutoStart()
  {
    return settings->GetautoStart();
  }

  void putAutoStart(VARIANT_BOOL pfAutoStart)
  {
    return settings->PutautoStart(pfAutoStart);
  }

  _bstr_t getBaseURL()
  {
    return settings->GetbaseURL();
  }

  void putBaseURL(_bstr_t pbstrBaseURL)
  {
    return settings->PutbaseURL(pbstrBaseURL);
  }

  _bstr_t getDefaultFrame()
  {
    return settings->GetdefaultFrame();
  }

  void putDefaultFrame(_bstr_t pbstrDefaultFrame)
  {
    return settings->PutdefaultFrame(
            pbstrDefaultFrame);
  }

  VARIANT_BOOL getInvokeURLs()
  {
    return settings->GetinvokeURLs();
  }

  void putInvokeURLs(VARIANT_BOOL pfInvokeURLs)
  {
    return settings->PutinvokeURLs(pfInvokeURLs);
  }
  
  VARIANT_BOOL getMute()
  {
    return settings->Getmute();
  }

  void putMute(VARIANT_BOOL pfMute)
  {
    return settings->Putmute(pfMute);
  }

  long getPlayCount()
  {
    return settings->GetplayCount();
  }

  void putPlayCount(long plCount)
  {
    return settings->PutplayCount(plCount);
  }

  double getRate()
  {
    return settings->Getrate();
  }

  void putRate(double pdRate)
  {
    return settings->Putrate(pdRate);
  }

  long getBalance()
  {
    return settings->Getbalance();
  }

  void putBalance(long plBalance)
  {
    return settings->Putbalance(plBalance);
  }

  long getVolume()
  {
    return settings->Getvolume();
  }

  void putVolume(long plVolume)
  {
    return settings->Putvolume(plVolume);
  }

  VARIANT_BOOL getMode(_bstr_t bstrMode)
  {
    return settings->getMode(bstrMode);
  }

  HRESULT setMode(
    _bstr_t bstrMode,
    VARIANT_BOOL varfMode)
  {
    return settings->setMode(bstrMode, varfMode);
  }

/*
mode: 
 autoRewind
 loop
 showFrame
 shuffle
*/
  VARIANT_BOOL getEnableErrorDialogs()
  {
    return settings->GetenableErrorDialogs();
  }

  void putEnableErrorDialogs(VARIANT_BOOL pfEnableErrorDialogs)
  {
    return settings->PutenableErrorDialogs(pfEnableErrorDialogs);
  }

  //IWMPSettings2
  long getDefaultAudioLanguage ( )
  {
    return settings->GetdefaultAudioLanguage ( );
  }

    _bstr_t getMediaAccessRights ( )
  {
    return settings->GetmediaAccessRights ( );
  }

   // desiredAccess = "none", "read", "full"
  VARIANT_BOOL requestMediaAccessRights (
        _bstr_t bstrDesiredAccess )
  {
    return settings->requestMediaAccessRights (bstrDesiredAccess );
  }

private:
  const TCHAR* getBoolName(VARIANT_BOOL flag)
  {
    static const TCHAR* name = _T("false");
    if (flag == VARIANT_TRUE) {
      name = _T("true");
    }
    return name;
  }
private:
  const wchar_t* getBoolean(VARIANT_BOOL flag)
  {
    static const wchar_t* name = L"false";
    if (flag == VARIANT_TRUE) {
      name = L"true";
    }
    return name;
  }

public:
  void showProperties(HWND hwnd=NULL) 
  {
    _tprintf(_T("<Settings>\n") );

    _tprintf(_T("<AutoStart>%s</AutoStart>\n"), getBoolName(getAutoStart()) );
    _tprintf(_T("<BaseURL>%s</BaseURL>\n"), (const TCHAR*)getBaseURL() );
    _tprintf(_T("<DefaultFrame>%s</DefaultFrame>\n"),  (const TCHAR*)getDefaultFrame() );
    _tprintf(_T("<InvokeURLs>%s</InvokeURLs>\n"), getBoolName(getInvokeURLs()) );
    _tprintf(_T("<Mute>%s</Mute>\n"), getBoolName(getMute()) );
    _tprintf(_T("<Rate>%f</Rate>\n"), getRate() );
    _tprintf(_T("<Balance>%ld</Balance>\n"), getBalance() );
    _tprintf(_T("<EnableErrorDialogs>%s</EnableErrorDialogs>\n"), getBoolName(getEnableErrorDialogs()) );
    _tprintf(_T("<Volume>%ld</Volume>\n"),  getVolume() );

    _tprintf(_T("<AutoRewind>%s</AutoRewind>\n"), getBoolName(getMode(_bstr_t("autoRewind"))) );
    _tprintf(_T("<Loop>%s</Loop>\n"), getBoolName(getMode(_bstr_t("loop"))) );
    _tprintf(_T("<ShowFrame>%s</ShowFrame>\n"), getBoolName(getMode(_bstr_t("showFrame"))) );
    _tprintf(_T("<Shuffle>%s</Shuffle>\n"), getBoolName(getMode(_bstr_t("shuffle"))) );

    _tprintf(_T("<DefaultAudioLanguage>%ld</DefaultAudioLanguage>\n"), getDefaultAudioLanguage() );
    _tprintf(_T("<MediaAccessRights>%s</MediaAccessRights>\n"),  (const TCHAR*)getMediaAccessRights() );
    _tprintf(_T("</Settings>\n") );

  }
public:
  void writeProperties(Writer& writer) 
  {
    writer.writeln(L"<Settings>");

    writer.writeln(L"<AutoStart>%s</AutoStart>", getBoolean(getAutoStart()) );
    writer.writeln(L"<BaseURL>%s</BaseURL>", (const wchar_t*)getBaseURL() );
    writer.writeln(L"<DefaultFrame>%s</DefaultFrame>",  (const wchar_t*)getDefaultFrame() );
    writer.writeln(L"<InvokeURLs>%s</InvokeURLs>", getBoolean(getInvokeURLs()) );
    writer.writeln(L"<Mute>%s</Mute>", getBoolean(getMute()) );
    writer.writeln(L"<Rate>%f</Rate>", getRate() );
    writer.writeln(L"<Balance>%ld</Balance>", getBalance() );
    writer.writeln(L"<EnableErrorDialogs>%s</EnableErrorDialogs>", getBoolean(getEnableErrorDialogs()) );
    writer.writeln(L"<Volume>%ld</Volume>",  getVolume() );

    writer.writeln(L"<AutoRewind>%s</AutoRewind>", getBoolean(getMode(_bstr_t("autoRewind"))) );
    writer.writeln(L"<Loop>%s</Loop>", getBoolean(getMode(_bstr_t("loop"))) );
    writer.writeln(L"<ShowFrame>%s</ShowFrame>", getBoolean(getMode(_bstr_t("showFrame"))) );
    writer.writeln(L"<Shuffle>%s</Shuffle>", getBoolean(getMode(_bstr_t("shuffle"))) );

    writer.writeln(L"<DefaultAudioLanguage>%ld</DefaultAudioLanguage>", getDefaultAudioLanguage() );
    writer.writeln(L"<MediaAccessRights>%s</MediaAccessRights>",  (const wchar_t*)getMediaAccessRights() );
    writer.writeln(L"</Settings>");
  }

};

}
