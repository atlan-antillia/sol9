/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  MediaControlView.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.01.09 Modified the constructor to call setValues method.
// 2000.02.18
#pragma once

#include <sol\Primitive.h>
#include <vfw.h>


namespace SOL {

class MediaControlView :public Primitive {

public:
  MediaControlView(): Primitive() 
  { 
  }

public:
  //2012/06/23
  MediaControlView(View* parent, const TCHAR* name, Args& args)
     :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
              args.set(XmNexStyle, WS_EX_TOPMOST)
              .set(XmNpredefined, true)
              .set(XmNclassName,  MCIWND_WINDOW_CLASS));

    setValues(args);

    return rc;
  }

  Boolean  canPlay() {
    return (Boolean)MCIWndCanPlay(getWindow());
  }

  Boolean   canRecord() {
    return (Boolean)MCIWndCanRecord(getWindow());
  }
  Boolean  canSave() {
    return (Boolean)MCIWndCanSave(getWindow());
  }
  Boolean  canWindow() {
    return (Boolean)MCIWndCanWindow(getWindow());
  }

  Boolean  canEject() {
    return (Boolean)MCIWndCanEject(getWindow());
  }

  Boolean  canConfig() {
    return (Boolean)MCIWndCanConfig(getWindow());
  }

  Boolean  paletteKick() {
    return (Boolean)MCIWndPaletteKick(getWindow());
  }

  long   save(const TCHAR* file) {
    return (LONG)MCIWndSM(getWindow(), MCI_SAVE, 0, (LPARAM)(LPVOID)(file));
  }

  void   saveDialog() {
    MCIWndSave(getWindow(), -1);
  }

  long   clear(TCHAR* lp) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_NEW, 0, (LPARAM)(LPVOID)(lp));
  }

  long   record() {
    return (LONG)MCIWndSM(getWindow(), MCI_RECORD, 0, 0);
  }
  long   open(TCHAR* sz, int f) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_OPEN, 
        (WPARAM)(UINT)(f),(LPARAM)(LPVOID)(sz));
  }

  long   openDialog() {
    return MCIWndOpen(getWindow(), -1, 0);
  }
  long   close() {
    return (LONG)MCIWndSM(getWindow(), MCI_CLOSE, 0, 0);
  }
  long   play() {
    return (LONG)MCIWndSM(getWindow(), MCI_PLAY, 0, 0);
  }
  long   stop() {
    return (LONG)MCIWndSM(getWindow(), MCI_STOP, 0, 0);
  }
  long   pause() {
    return (LONG)MCIWndSM(getWindow(), MCI_PAUSE, 0, 0);
  }

  long   resume() {
    return (LONG)MCIWndSM(getWindow(), MCI_RESUME, 0, 0);
  }

  long   seek(long lPos) {
    return (LONG)MCIWndSM(getWindow(), MCI_SEEK, 0, (LPARAM)(LONG)(lPos));
  }

  long   eject() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_EJECT, 0, 0);
  }

  long   home() {
    return MCIWndSeek(getWindow(), MCIWND_START);
  }

  long   end() {
    return MCIWndSeek(getWindow(), MCIWND_END);
  }

  long   getSource(LPRECT prc) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GET_SOURCE, 0, (LPARAM)(LPRECT)(prc));
  }
  long   putSource(LPRECT prc) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_PUT_SOURCE, 0, (LPARAM)(LPRECT)(prc));
  }

  long   getDest(LPRECT prc) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GET_DEST, 0, (LPARAM)(LPRECT)(prc));
  }
  long   putDest(LPRECT prc) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_PUT_DEST, 0, (LPARAM)(LPRECT)(prc));
  }
  long  playReverse() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_PLAYREVERSE, 0, 0);
  }
  long  playFrom(LONG lPos) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_PLAYFROM, 0, (LPARAM)(LONG)(lPos));
  }

  long  playTo(LONG lPos) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_PLAYTO,   0, (LPARAM)(LONG)(lPos));
  }

  long  playFromTo(LONG lStart, LONG lEnd) {
        MCIWndSeek(getWindow(), lStart);
    return   MCIWndPlayTo(getWindow(), lEnd);
  }

  long  getDeviceID() {
    return (UINT)MCIWndSM(getWindow(), MCIWNDM_GETDEVICEID, 0, 0);
  }

  long  getAlias() {
    return (UINT)MCIWndSM(getWindow(), MCIWNDM_GETALIAS, 0, 0);
  }

  long  getMode(LPTSTR lp, UINT len) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETMODE, (WPARAM)(UINT)(len), (LPARAM)(LPTSTR)(lp));
  }

  long  getPosition() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETPOSITION, 0, 0);
  }

  long  getPositionString(LPARAM lp, UINT len) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETPOSITION, (WPARAM)(UINT)(len), (LPARAM)(LPTSTR)(lp));
  }
  long  getStart() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETSTART, 0, 0);
  }

  long  getLength() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETLENGTH, 0, 0);
  }

  long  getEnd() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETEND, 0, 0);
  }
  long  step(int n) {
    return (LONG)MCIWndSM(getWindow(), MCI_STEP, 0,(LPARAM)(long)(n));
  }
  void  destroy() {
    (VOID)MCIWndSM(getWindow(), WM_CLOSE, 0, 0);
  }
  void  zoom(int iZoom) {
    (VOID)MCIWndSM(getWindow(), MCIWNDM_SETZOOM, 0, (LPARAM)(UINT)(iZoom));
  }
  UINT   getZoom() {
    return (UINT)MCIWndSM(getWindow(), MCIWNDM_GETZOOM, 0, 0);
  }

  long  setVolume(int iVol) {
     return (LONG)MCIWndSM(getWindow(), MCIWNDM_SETVOLUME, 0, (LPARAM)(UINT)(iVol));
  }
  long  getVolume() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETVOLUME, 0, 0);
  }

  long  setSpeed(int iSpeed) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_SETSPEED, 0, (LPARAM)(UINT)(iSpeed));
  }

  long  getSpeed() {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETSPEED, 0, 0);
  }

  long  setTimeFormat(const TCHAR* lp) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_SETTIMEFORMAT, 0, (LPARAM)(LPTSTR)(lp));
  }

  long  getTimeFormat(TCHAR* lp, int len) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETTIMEFORMAT, (WPARAM)(UINT)(len), (LPARAM)(LPTSTR)(lp));
  }

  void  validateMedia() {
       (VOID)MCIWndSM(getWindow(), MCIWNDM_VALIDATEMEDIA, 0, 0);
  }

  void  setRepeat(Boolean f) {
      (void)MCIWndSM(getWindow(), MCIWNDM_SETREPEAT, 0, (LPARAM)(Boolean)(f));
  }

  Boolean  getRepeat() {
    return (Boolean)MCIWndSM(getWindow(), MCIWNDM_GETREPEAT, 0, 0);
  }

  long  useFrames() {
    return setTimeFormat(TEXT("frames"));
  }
  long  useTime() {
    return setTimeFormat(TEXT("ms"));
  }

  void  setActiveTimer(UINT active) {
      (VOID)MCIWndSM(getWindow(), MCIWNDM_SETACTIVETIMER, (WPARAM)(UINT)(active), 0L);
  }

  void  setInactiveTimer(UINT inactive)  {
    (VOID)MCIWndSM(getWindow(), MCIWNDM_SETINACTIVETIMER, (WPARAM)(UINT)(inactive), 0L);
  }
  void  setTimers(UINT active, UINT inactive) {
      (VOID)MCIWndSM(getWindow(), MCIWNDM_SETTIMERS,(WPARAM)(UINT)(active), (LPARAM)(UINT)(inactive));
  }
  UINT  getActiveTimer() {
    return (UINT)MCIWndSM(getWindow(), MCIWNDM_GETACTIVETIMER,  0, 0L);
  }
  UINT  getInactiveTimer() {
    return (UINT)MCIWndSM(getWindow(), MCIWNDM_GETINACTIVETIMER, 0, 0L);
  }

  long  realize(Boolean fBkgnd) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_REALIZE,(WPARAM)(Boolean)(fBkgnd),0);
  }

  long  sendString(const TCHAR* sz) {
    return  (LONG)MCIWndSM(getWindow(), MCIWNDM_SENDSTRING, 0, (LPARAM)(LPTSTR)(sz));
  }

  long  returnString(TCHAR* lp, int len) {
    return  (LONG)MCIWndSM(getWindow(), MCIWNDM_RETURNSTRING, (WPARAM)(UINT)(len), (LPARAM)(LPVOID)(lp));
  }
  long  getError(TCHAR* lp, int len) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETERROR, (WPARAM)(UINT)(len), (LPARAM)(LPVOID)(lp));
  }

  void  activate(Boolean f) {
       (void)MCIWndSM(getWindow(), WM_ACTIVATE, (WPARAM)(Boolean)(f), 0);
  }

  HPALETTE  getPalette() {
    return  (HPALETTE)MCIWndSM(getWindow(), MCIWNDM_GETPALETTE, 0, 0);
  }

  long  setPalette(HPALETTE hpal) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_SETPALETTE, (WPARAM)(HPALETTE)(hpal), 0);
  }

  long  getFileName(TCHAR* lp, int len) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETFILENAME, (WPARAM)(UINT)(len), (LPARAM)(LPVOID)(lp));
  }

  long  getDevice(TCHAR* lp, int len)  {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_GETDEVICE, (WPARAM)(UINT)(len), (LPARAM)(LPVOID)(lp));
  }

  UINT  getStyles() {
    return (UINT)MCIWndSM(getWindow(), MCIWNDM_GETSTYLES, 0, 0L);
  }

  long  changeStyles(UINT mask, long value) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_CHANGESTYLES, (WPARAM)(UINT)(mask), (LPARAM)(LONG)(value));
  }

  long  openInterface(LPUNKNOWN pUnk) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_OPENINTERFACE, 0, (LPARAM)(LPUNKNOWN)(pUnk));
  }

  long  setOwner(HWND hwndP) {
    return (LONG)MCIWndSM(getWindow(), MCIWNDM_SETOWNER, (WPARAM)(hwndP), 0);
  }
};

}


