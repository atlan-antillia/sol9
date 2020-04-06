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
 *  MediaEventsListener.h
 *
 *****************************************************************************/


// SOL9
// 2011/12/20: MediaEvents Listener class derived from SOL::MediaEvents 

#pragma once

#include <sol/ole/MediaEvents.h>
#include <sol/ArgListT.h>

namespace SOL {

class MediaEventsListener :public MediaEvents {
  
private:
  DWORD threadId;

private:
  IWMPPlayer4* pPlayer;

public:
  //Constructor
  MediaEventsListener(DWORD thread)
  :pPlayer(NULL),
  threadId(thread)
  {
  }

public:
  IWMPPlayer4* getPlayer()
  {
    return pPlayer;
  }

public:
  void putPlayer(IWMPPlayer4* player)
  {
    pPlayer = player;
  }

public:
  const TCHAR* getOpenStateName(long NewState)
  {
    static const ArgT<TCHAR> states[] = {
      {_T("Undefined"),              wmposUndefined},
      {_T("PlaylistChanging"),       wmposPlaylistChanging},
      {_T("PlaylistLocating"),       wmposPlaylistLocating},
      {_T("PlaylistConnecting"),     wmposPlaylistConnecting},
      {_T("PlaylistLoading"),        wmposPlaylistLoading},
      {_T("PlaylistOpening"),        wmposPlaylistOpening},
      {_T("PlaylistOpenNoMedia"),    wmposPlaylistOpenNoMedia},
      {_T("PlaylistChanged"),        wmposPlaylistChanged},
      {_T("MediaChanging"),          wmposMediaChanging},
      {_T("MediaLocating"),          wmposMediaLocating},
      {_T("MediaConnecting"),        wmposMediaConnecting},
      {_T("MediaLoading"),           wmposMediaLoading},
      {_T("MediaConnecting"),        wmposMediaConnecting},
      {_T("MediaLoading"),           wmposMediaLoading},
      {_T("MediaOpening"),           wmposMediaOpening},
      {_T("MediaOpen"),              wmposMediaOpen},
      {_T("BeginCodecAcquisition"),  wmposBeginCodecAcquisition},
      {_T("EndCodecAcquisition"),    wmposEndCodecAcquisition},
      {_T("BeginIndividualization"), wmposBeginIndividualization},
      {_T("EndIndividualization"),   wmposEndIndividualization},
      {_T("MediaWaiting"),           wmposMediaWaiting},
      {_T("OpeningUnknownURL"), wmposOpeningUnknownURL},
    };
    ArgListT<TCHAR> argList(states, CountOf(states));
    return argList.getName(NewState);
  }

/*
enum WMPOpenState
{
  wmposUndefined = 0,
    wmposPlaylistChanging = 1,
    wmposPlaylistLocating = 2,
    wmposPlaylistConnecting = 3,
    wmposPlaylistLoading = 4,
    wmposPlaylistOpening = 5,
    wmposPlaylistOpenNoMedia = 6,
    wmposPlaylistChanged = 7,
    wmposMediaChanging = 8,
    wmposMediaLocating = 9,
    wmposMediaConnecting = 10,
    wmposMediaLoading = 11,
    wmposMediaOpening = 12,
    wmposMediaOpen = 13,
    wmposBeginCodecAcquisition = 14,
    wmposEndCodecAcquisition = 15,
    wmposBeginLicenseAcquisition = 16,
    wmposEndLicenseAcquisition = 17,
    wmposBeginIndividualization = 18,
    wmposEndIndividualization = 19,
    wmposMediaWaiting = 20,
    wmposOpeningUnknownURL = 21
};
*/



public:
  const TCHAR* getPlayStateName(long NewState)
  {
    static const ArgT<TCHAR> states[] = {
      {_T("Undefined"),     wmppsUndefined},
      {_T("Stopped"),     wmppsStopped}, 
      {_T("Paused"),       wmppsPaused}, 
      {_T("Playing"),     wmppsPlaying}, 
      {_T("ScanForward"),   wmppsScanForward}, 
      {_T("ScanReverse"),   wmppsScanReverse}, 
      {_T("Buffering"),     wmppsBuffering}, 
      {_T("Waiting"),     wmppsWaiting}, 
      {_T("MediaEnded"),     wmppsMediaEnded}, 
      {_T("Transitioning"),   wmppsTransitioning}, 
      {_T("Ready"),         wmppsReady},
      {_T("Reconnecting"),    wmppsReconnecting},
      {_T("Last"),            wmppsLast},
    };

    ArgListT<TCHAR> argList(states, CountOf(states));
    return argList.getName(NewState);
  }

public:
  void postThreadMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
  {
    PostThreadMessage(threadId, message, wParam, lParam);
  }

public:
  virtual void __stdcall PlayStateChange (__in long NewState)
  {
    //
    const TCHAR* name =getPlayStateName(NewState);
    _tprintf(_T("PlayStateChange NewState=%s (%d)\n"), name, NewState);
  }
};

}
