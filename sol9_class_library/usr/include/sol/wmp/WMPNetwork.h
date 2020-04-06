/******************************************************************************
 *
 * Copyright(c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WMPNetwork.h
 *
 *****************************************************************************/


// SOL9
// 2011/12/12

#pragma once

#include <sol/wmp/WMPObject.h>

namespace SOL {

class WMPNetwork :public WMPObject {

private:
  IWMPNetworkPtr network;

public:
  WMPNetwork(IWMPNetworkPtr ptr)
  :network(ptr)
  {
    if(ptr == NULL) {
      throw NullPointerException("IWMPNetworkPtr is NULL", 0);
    }
  }

public:
  ~WMPNetwork()
  {
    network = NULL;
  }

public:
  long getBandWidth()
  {
    return network->GetbandWidth();
  }

  long getRecoveredPackets()
  {
    return network->GetrecoveredPackets();
  }

  _bstr_t getSourceProtocol()
  {
    return network->GetsourceProtocol();
  }

  long getReceivedPackets()
  {
    return network->GetreceivedPackets();
  }

  long getLostPackets()
  {
    return network->GetlostPackets();
  }

  long getReceptionQuality()
  {
    return network->GetreceptionQuality();
  }

  long getBufferingCount()
  {
    return network->GetbufferingCount();
  }

  long getBufferingProgress()
  {
    return network->GetbufferingProgress();
  }

  long getBufferingTime()
  {
    return network->GetbufferingTime();
  }

  void putBufferingTime(long plBufferingTime)
  {
    network->PutbufferingTime(plBufferingTime);
  }

  long getFrameRate()
  {
    return network->GetframeRate();
  }

  long getMaxBitRate()
  {
    return network->GetmaxBitRate();
  }

  long getBitRate()
  {
    return network->GetbitRate();
  }

/*
The getProxySettings returns the following values:
0: A proxy server is not being used.
1: The proxy settings for the current browser are being used (only valid for HTTP).
2: The manually specified proxy settings are being used.
3: The proxy settings are being auto-detected
*/
  long getProxySettings(_bstr_t bstrProtocol)
  {
    return network->getProxySettings(bstrProtocol);
  }

  HRESULT setProxySettings(_bstr_t bstrProtocol, long lProxySetting)
  {
    return network->setProxySettings(bstrProtocol, lProxySetting);
  }

  _bstr_t getProxyName(_bstr_t bstrProtocol)
  {
    return network->getProxyName(bstrProtocol);
  }

  HRESULT setProxyName(_bstr_t bstrProtocol, _bstr_t bstrProxyName)
  {
    return network->setProxyName(bstrProtocol, bstrProxyName);
  }

  long getProxyPort(_bstr_t bstrProtocol)
  {
    return network->getProxyPort(bstrProtocol);
  }

  HRESULT setProxyPort(_bstr_t bstrProtocol, long lProxyPort)
  {
    return network->setProxyPort(bstrProtocol, lProxyPort);
  }

  _bstr_t getProxyExceptionList(_bstr_t bstrProtocol)
  {
    return network->getProxyExceptionList(bstrProtocol);
  }

  HRESULT setProxyExceptionList(_bstr_t bstrProtocol, _bstr_t pbstrExceptionList)
  {
    return network->setProxyExceptionList(bstrProtocol, pbstrExceptionList);
  }

  VARIANT_BOOL getProxyBypassForLocal(_bstr_t bstrProtocol)
  {
    return network->getProxyBypassForLocal(bstrProtocol);
  }

  const TCHAR* getProxyBypassFlagForLocal(_bstr_t bstrProtocol)
  {
    const TCHAR* flag = _T("false");
    if (network->getProxyBypassForLocal(bstrProtocol) == VARIANT_TRUE) {
      flag = _T("true");
    }
    return flag;
  }

  HRESULT setProxyBypassForLocal(_bstr_t bstrProtocol, VARIANT_BOOL fBypassForLocal)
  {
    return network->setProxyBypassForLocal(bstrProtocol, fBypassForLocal);
  }

  long getmaxBandwidth()
  {
    return network->GetmaxBandwidth();
  }

  void putMaxBandwidth(long lMaxBandwidth)
  {
    network->PutmaxBandwidth(lMaxBandwidth);
  }

  long getDownloadProgress()
  {
    return network->GetdownloadProgress();
  }

  long getEncodedFrameRate()
  {
    return network->GetencodedFrameRate();
  }

  long getFramesSkipped()
  {
    return network->GetframesSkipped();
  }

//
public:
  virtual void showProperties(HWND hwnd = NULL)
  {
    _tprintf(_T("<WMPNetwork>\n"));
    _tprintf(_T("<BandWidth>%ld</BandWidth>\n"),  getBandWidth() );
    _tprintf(_T("<ReceivedPackets>%ld</ReceivedPackets>\n"), getRecoveredPackets() );
    _tprintf(_T("<LostPackets>%ld</LostPackets>\n"), getLostPackets() );
    _tprintf(_T("<ReceptionQuality>%ld</ReceptionQuality>\n"), getReceptionQuality() );
    _tprintf(_T("<BufferingCount>%ld</BufferingCount>\n"), getBufferingCount() );
    _tprintf(_T("<BufferingProgress>%ld</BufferingProgress>\n"), getBufferingProgress() );
    _tprintf(_T("<BufferingTime>%ld</BufferingTime>\n"), getBufferingTime() );

    try {
      _tprintf(_T("<FrameRate>%ld</FrameRate>\n"), getFrameRate() );
    } catch (...) {
    }
    try {
      _tprintf(_T("<MaxBitRate>%ld</MaxBitRate>\n"), getMaxBitRate() );
    } catch (...) {
    }
    try {
      _tprintf(_T("<BitRate>%ld</BitRate>\n"), getBitRate() );
    } catch (...) {
    }

    _bstr_t bstrProtocol[2] = {_bstr_t("HTTP"), _bstr_t("MMS") };
    for (int i = 0; i< CountOf(bstrProtocol); i++) {
      try {
        if (getProxySettings(bstrProtocol[i]) != 0) {
          _tprintf(_T("<Proxy>\n"));
          _tprintf(_T("<Protocol>%s</Protocol>\n"), (const TCHAR*)bstrProtocol[i]); 
          
          _tprintf(_T("<ProxyName>%s</ProxyName>\n"),  
              (const TCHAR*) getProxyName(bstrProtocol[i]) );
          _tprintf(_T("<ProxyPort>%d</ProxyPort>\n"), 
              (const TCHAR*)getProxyPort(bstrProtocol[i]) );
          _tprintf(_T("<ProxyException>%s</ProxyException>\n"), 
              (const TCHAR*)getProxyExceptionList(bstrProtocol[i]) );
          _tprintf(_T("<ProxyBypassForLocal>%s</ProxyBypassForLocal>\n"), 
              (const TCHAR*)getProxyBypassFlagForLocal(bstrProtocol[i]) );
          _tprintf(_T("</Proxy>\n"));

        } else {
          //_tprintf(_T("No proxySettings for %s\n"), (const TCHAR*)bstrProtocol[i]);
        }
      } catch (...) {
      }
    }
    try {
      _tprintf(_T("<MaxBandWidth>%ld</MaxBandWidth>\n"), getmaxBandwidth() );
    } catch (...) {
    }
    try {
      _tprintf(_T("<DownloadProgress>%ld</DownloadProgress>\n"), getDownloadProgress() );
    } catch (...) {
    }
    try {
      _tprintf(_T("<EncodedFrameRate>%ld</EncodedFrameRate>\n"), getEncodedFrameRate() );
    } catch (...) {
    }
    try {
      _tprintf(_T("<FrameSkipped>%ld</FrameSkipped>\n"), getFramesSkipped() );
    } catch (...) {
    }
    _tprintf(_T("</WMPNetwork>\n"));
  }

public:
  virtual void writeProperties(Writer& writer)
  {
    writer.writeln(L"<WMPNetwork>");
    writer.writeln(L"<BandWidth>%ld</BandWidth>",  getBandWidth() );
    writer.writeln(L"<ReceivedPackets>%ld</ReceivedPackets>", getRecoveredPackets() );
    writer.writeln(L"<LostPackets>%ld</LostPackets>", getLostPackets() );
    writer.writeln(L"<ReceptionQuality>%ld</ReceptionQuality>", getReceptionQuality() );
    writer.writeln(L"<BufferingCount>%ld</BufferingCount>", getBufferingCount() );
    writer.writeln(L"<BufferingProgress>%ld</BufferingProgress>", getBufferingProgress() );
    writer.writeln(L"<BufferingTime>%ld</BufferingTime>", getBufferingTime() );

    try {
      writer.writeln(L"<FrameRate>%ld</FrameRate>", getFrameRate() );
    } catch (...) {
    }
    try {
      writer.writeln(L"<MaxBitRate>%ld</MaxBitRate>", getMaxBitRate() );
    } catch (...) {
    }
    try {
      writer.writeln(L"<BitRate>%ld</BitRate>", getBitRate() );
    } catch (...) {
    }

    _bstr_t bstrProtocol[2] = {_bstr_t("HTTP"), _bstr_t("MMS") };
    for (int i = 0; i< CountOf(bstrProtocol); i++) {
      try {
        if (getProxySettings(bstrProtocol[i]) != 0) {
          writer.writeln(L"<Proxy>");
          writer.writeln(L"<Protocol>%s</Protocol>", (const wchar_t*)bstrProtocol[i]); 
          
          writer.writeln(L"<ProxyName>%s</ProxyName>",  
              (const wchar_t*) getProxyName(bstrProtocol[i]) );
          writer.writeln(L"<ProxyPort>%d</ProxyPort>", 
              (const wchar_t*)getProxyPort(bstrProtocol[i]) );
          writer.writeln(L"<ProxyException>%s</ProxyException>", 
              (const wchar_t*)getProxyExceptionList(bstrProtocol[i]) );
          writer.writeln(L"<ProxyBypassForLocal>%s</ProxyBypassForLocal>", 
              (const wchar_t*)getProxyBypassFlagForLocal(bstrProtocol[i]) );
          writer.writeln(L"</Proxy>");
        } else {
          //_tprintf(_T("No proxySettings for %s\n"), (const TCHAR*)bstrProtocol[i]);
        }
      } catch (...) {
      }
    }
    try {
      writer.writeln(L"<MaxBandWidth>%ld</MaxBandWidth>", getmaxBandwidth() );
    } catch (...) {
    }
    try {
      writer.writeln(L"<DownloadProgress>%ld</DownloadProgress>", getDownloadProgress() );
    } catch (...) {
    }
    try {
      writer.writeln(L"<EncodedFrameRate>%ld</EncodedFrameRate>", getEncodedFrameRate() );
    } catch (...) {
    }
    try {
      writer.writeln(L"<FrameSkipped>%ld</FrameSkipped>", getFramesSkipped() );
    } catch (...) {
    }
    writer.writeln(L"</WMPNetwork>");
  }

};

}
