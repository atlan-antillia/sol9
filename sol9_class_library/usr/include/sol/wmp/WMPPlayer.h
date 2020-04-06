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
 *  WMPPlayer.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>

namespace SOL {

class WMPPlayer :public WMPObject {

private:
  IWMPPlayer4Ptr player;

public:
  WMPPlayer()
  :player(NULL)
  {
    IWMPPlayer4* pPlayer;
    HRESULT hr = CoCreateInstance( __uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER, 
      __uuidof(IWMPPlayer4), (void **)&pPlayer);
    if(FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    player = pPlayer;
  }


public:
  ~WMPPlayer()
  {
    player = NULL;  
  }



public:    
  IWMPLibraryServicesPtr getLibraryServices()
  { 
    IWMPLibraryServices* services = NULL;
    HRESULT hr = player->QueryInterface(__uuidof(IWMPLibraryServices),(void **)&services);
    if(FAILED(hr)) {
      printf("Failed to queryinterface for IWMPLibraryServices\n");
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    IWMPLibraryServicesPtr ptr = services;
    return ptr;
  }


//<IWMPCore>
    HRESULT close()
  {
    return player->close();
  }

    _bstr_t getURL()
  {
    return player->GetURL();
  }
    
  void putURL(
        _bstr_t pbstrURL)
  {
    player->PutURL(pbstrURL);
  }
    
  enum WMPOpenState getOpenState()
  {
    return player->GetopenState();
  }
    
  enum WMPPlayState getPlayState()
  {
    return player->GetplayState();
  }
    
  IWMPControlsPtr getControls()
  {
    return player->Getcontrols();
  }
    
  IWMPSettingsPtr getSettings()
  {
    return player->Getsettings();
  }
    
  IWMPMediaPtr getCurrentMedia()
  {
    return player->GetcurrentMedia();
  }
    
  void putCurrentMedia(
        struct IWMPMedia * ppMedia)
  {
    player->PutcurrentMedia(
        ppMedia);
  }
    
  
  IWMPMediaCollectionPtr getMediaCollection()
  {
    return player-> GetmediaCollection();
  }
    
  IWMPPlaylistCollectionPtr getPlaylistCollection()
  {
    return player->GetplaylistCollection();
  }

    _bstr_t getVersionInfo()
  {
    return player-> GetversionInfo();
  }
    
  HRESULT launchURL(
        _bstr_t bstrURL)
  {
    return player->launchURL(bstrURL);
  }
    
  IWMPNetworkPtr getNetwork()
  {
    return player->Getnetwork();
  }
    
  
  IWMPPlaylistPtr getCurrentPlaylist()
  {
    return player->GetcurrentPlaylist();
  }
    
  void putCurrentPlaylist(
        struct IWMPPlaylist * ppPL)
  {
    return player->PutcurrentPlaylist(
        ppPL);
  }
    
  IWMPCdromCollectionPtr getCdromCollection()
  {
    return player->GetcdromCollection();
  }
    
  IWMPClosedCaptionPtr getClosedCaption()
  {
    return player->GetclosedCaption();
  }
    
  VARIANT_BOOL getIsOnline()
  {
    return player->GetisOnline();
  }
    
  IWMPErrorPtr getError()
  {
    return player->GetError();
  }
    
  _bstr_t getStatus()
  {
    return player->Getstatus();
  }

//</IWMPCore>

//<IWMPCore2>
    IWMPDVDPtr getDVD()
  {
    return player->Getdvd();
  }

//<IWMPCore3>
    IWMPPlaylistPtr newPlaylist(
        _bstr_t bstrName,
        _bstr_t bstrURL)
  {
    return player->newPlaylist(
      bstrName,
      bstrURL);
  }

    IWMPMediaPtr newMedia(
        _bstr_t bstrURL)
  {
    return player->newMedia(
      bstrURL);
  }

//</IWMPCore3>

//<IWMPPlayer4>
    VARIANT_BOOL getEnabled()
  {
    return player->Getenabled();
  }

  void putEnabled(
        VARIANT_BOOL pbEnabled)
  {
    return player->Putenabled(pbEnabled);
  }

  VARIANT_BOOL getFullScreen()
  {
    return player->GetfullScreen();
  }

  void putFullScreen(
        VARIANT_BOOL pbFullScreen)
  {
    return player->PutfullScreen(
      pbFullScreen);
  }

  VARIANT_BOOL getEnableContextMenu()
  {
    return player->GetenableContextMenu();
  }

  void putEnableContextMenu(
        VARIANT_BOOL pbEnableContextMenu)
  {
    return player->PutenableContextMenu(pbEnableContextMenu);
  }

  void putUiMode(
        _bstr_t pbstrMode)
  {
    return player->PutuiMode(pbstrMode);
  }

  _bstr_t getUiMode()
  {
    return player->GetuiMode();
  }

  VARIANT_BOOL getStretchToFit()
  {
    return player-> GetstretchToFit();
  }

  void putStretchToFit(
        VARIANT_BOOL pbEnabled)
  {
    return player->PutstretchToFit(pbEnabled);
  }

  VARIANT_BOOL getWindowlessVideo()
  {
    return player->GetwindowlessVideo();
  }

  void putWindowlessVideo(
        VARIANT_BOOL pbEnabled)
  {
    return player->PutwindowlessVideo(pbEnabled);
  }

  VARIANT_BOOL getIsRemote()
  {
    return player->GetisRemote();

  }

    IWMPPlayerApplicationPtr getPlayerApplication()
  {
    return player->GetplayerApplication();
  }

  HRESULT openPlayer(
        _bstr_t bstrURL)
  {
    return player->openPlayer(bstrURL);
  }

//</IWMPPlayer4>

};

}
