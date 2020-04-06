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
 *  WMPControls.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>

namespace SOL {

class WMPControls :public WMPObject
{
private:
  IWMPControls3Ptr controls;
 
public:
  WMPControls(IWMPControlsPtr ptr)
  :controls(ptr)
  {
    if(ptr == NULL) {
      throw NullPointerException("IWMPControlsPtr is NULL", 0);
    }
  }

public:
  ~WMPControls()
  {
    controls = NULL;
  }

   //

  VARIANT_BOOL getIsAvailable(_bstr_t bstrItem)
  {
    return controls->GetisAvailable(bstrItem);
  }

  HRESULT play()
  {
    return controls->play();
  }

  HRESULT stop()
  {
    return controls-> stop();
  }

  HRESULT pause()
  {
    return controls->pause();
  }

  HRESULT fastForward()
  {
    return controls->fastForward();
  }

  HRESULT fastReverse()
  {
    return controls->fastReverse();
  }

  double getCurrentPosition()
  {
    return controls->GetcurrentPosition();
  }

  void putCurrentPosition(double pdCurrentPosition)
  {
    controls->PutcurrentPosition(pdCurrentPosition);
  }

  _bstr_t getCurrentPositionString()
  {
    return controls->GetcurrentPositionString();
  }

  HRESULT next()
  {
    return controls->next();
  }

  HRESULT previous()
  {
    return controls-> previous();
  }

  IWMPMediaPtr getCurrentItem()
  {
    return controls->GetcurrentItem();
  }

  void putCurrentItem(struct IWMPMedia * ppIWMPMedia)
  {
    controls->PutcurrentItem(ppIWMPMedia);
  }

  long getCurrentMarker()
  {
    return controls->GetcurrentMarker();
  }

  void putCurrentMarker(long plMarker)
  {
    controls->PutcurrentMarker(plMarker);
  }

  HRESULT playItem(struct IWMPMedia * pIWMPMedia)
  {
    return controls->playItem(pIWMPMedia);
  }

//<IWMPControls2>
    HRESULT step(long lStep)
  {
    return controls->step(lStep);
  }

//
//<IWMPControls3>
  long getAudioLanguageCount()
  {
    return controls->GetaudioLanguageCount();
  }

  long getAudioLanguageID(
        long lIndex)
  {
    return controls->getAudioLanguageID(
      lIndex);
  }

    _bstr_t getAudioLanguageDescription(
        long lIndex)
  {
    return controls->getAudioLanguageDescription(
      lIndex);
  }

  long getCurrentAudioLanguage()
  {
    return controls->GetcurrentAudioLanguage();
  }

  void putCurrentAudioLanguage(
        long plLangID)
  {
    controls->PutcurrentAudioLanguage(
      plLangID);
  }

  long getCurrentAudioLanguageIndex()
  {
    return controls->GetcurrentAudioLanguageIndex();
  }

  void putCurrentAudioLanguageIndex(
        long plIndex)
  {
    controls->PutcurrentAudioLanguageIndex(
      plIndex);
  }

  _bstr_t getLanguageName(
        long lLangID)
  {
    return controls->getLanguageName(
      lLangID);
  }

  _bstr_t getCurrentPositionTimecode()
  {
    return controls->GetcurrentPositionTimecode();
  }

  void putCurrentPositionTimecode(
        _bstr_t bstrTimecode)
  {
    controls->PutcurrentPositionTimecode(
      bstrTimecode);
  }

//</IWMPControls3>

public:
  void showProperties(HWND hwnd=NULL)
  {

  }

};

}
