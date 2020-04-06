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
 *  MediaPlayer.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed a WMPPlayer control 
(an OLE object) into your own window.
*/

// SOL9
// 2011/02/21
// 2011/12/12 Updated

#pragma once

#include <sol\Object.h>
#include <exdisp.h>
#include <sol\StringConverter.h>
#include <sol\String.h>
#include <sol\ole\IMediaPlayer.h>
#include <sol\ole\OleSite.h>

#include <sol\ole\OleInPlaceFrame.h>

#include <sol\ole\MediaEvents.h>
#include <sol/Stdio.h>

namespace SOL {

/**
 * Implementation of IMediaPlayer
 */
class MediaPlayer : public IMediaPlayer {

public:
  COleSite  oleSite;
  MediaEvents mediaEvents;
  IOleObject* oleObject;

  COleInPlaceFrame frame;

public:
  /**
   *
   */
  MediaPlayer()
    :oleObject(NULL)
  {
    oleSite.host  = this;
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name, args);
    createWebControl();

    return rc;
  }

public:
  /**
   *
   */
  ~MediaPlayer()
  {
    destroyWebControl();
  }

private:
  void createWebControl(void)
  {
    HRESULT hr = CoCreateInstance( __uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER, 
        IID_IOleObject, 
        (void **)&oleObject);
      
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    HWND hwnd = getWindow();

    oleObject->SetHostNames(L"WMP Host", L"WMP View");
    OleSetContainedObject(oleObject, TRUE);

    hr = oleObject-> SetClientSite(&oleSite);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
            
    RECT r;      
    GetClientRect(hwnd, &r);
    hr = oleObject->DoVerb(
        //OLEIVERB_INPLACEACTIVATE,
        OLEIVERB_SHOW, 
        NULL, (IOleClientSite*) &oleSite, -1, 
        hwnd, 
        &r);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    IWMPPlayer4* pPlayer = NULL;
    hr = oleObject->QueryInterface(__uuidof(IWMPPlayer4), 
        (void**)&pPlayer);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    hr = mediaEvents.Advise(oleObject, __uuidof(IWMPEvents));
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    IWMPSettings *pSettings=NULL;

    hr = pPlayer->QueryInterface(__uuidof(IWMPSettings), (void **)&pSettings);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    pPlayer->put_uiMode(_bstr_t("full"));
      
    pPlayer->put_enabled(VARIANT_TRUE);
    pSettings->put_enableErrorDialogs(VARIANT_TRUE);
    pPlayer->Release();
    pSettings->Release();
    
  }

public:
  //2011/12/12
  IWMPSettings* getSettings()
  {
    IWMPPlayer4* pPlayer = NULL;
    HRESULT hr = oleObject->QueryInterface(__uuidof(IWMPPlayer4), (void**)&pPlayer);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    IWMPSettings *pSettings=NULL;

    hr = pPlayer->QueryInterface(__uuidof(IWMPSettings), (void **)&pSettings);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pSettings;
  }

public:
  //2011/12/12
  IWMPControls* getControls()
  {
    IWMPPlayer4* pPlayer = NULL;
    HRESULT hr = oleObject->QueryInterface(__uuidof(IWMPPlayer4), (void**)&pPlayer);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    IWMPControls *pControls = NULL;

    hr = pPlayer->QueryInterface(__uuidof(IWMPControls), (void **)&pControls);
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return pControls;
  }            

public:
  HRESULT  QueryInterface(REFIID riid, void ** ppvObject)
  {
    if(ppvObject == NULL) {
      return E_INVALIDARG;
    }

    *ppvObject = NULL;
      
    if(riid == IID_IUnknown) {
        *ppvObject = this;
    } else if(riid == IID_IOleClientSite) {
        *ppvObject = &oleSite;
    } else if(riid == __uuidof(IWMPEvents)) {
        *ppvObject = &mediaEvents;
    }

    if(*ppvObject == NULL) {
      return E_NOINTERFACE;
    }
      //AddRef();
    return S_OK;
  }

public:
  void play(const TCHAR* url) 
  {
    IWMPPlayer4* pPlayer = NULL;
    if (oleObject ==NULL) {
      return;
    }
    HRESULT hr = oleObject->QueryInterface(__uuidof(IWMPPlayer4), (void**)&pPlayer);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    IWMPControls *pControls = NULL;

    hr = pPlayer->QueryInterface(__uuidof(IWMPControls), (void **)&pControls);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    pControls->stop();
            
    pPlayer->put_enabled(VARIANT_TRUE);
    pPlayer->put_URL(_bstr_t(url));  
    pControls->play();

    pControls->Release();
    pPlayer->Release();
  }

private:
  void destroyWebControl()
  {
    HRESULT hr = mediaEvents.Unadvise(oleObject, __uuidof(IWMPEvents));

    IWMPPlayer4* pPlayer =NULL;
    hr =  oleObject->QueryInterface(__uuidof(IWMPPlayer4), (void**)&pPlayer);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    pPlayer->Release();    
    oleObject->Close(OLECLOSE_NOSAVE);
    oleObject->Release();
  }

public:
  virtual IOleInPlaceFrame* getInPlaceFrame() 
  { 
    return &frame;
  }

public:
  virtual IOleObject* getOleObject() 
  { 
    return oleObject; 
  };

};

}
