/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  TrackBar.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Primitive.h>

namespace SOL {

class TrackBar :public Primitive {
public:
  TrackBar(): Primitive() { }

public:
  //2012/06/25
  TrackBar(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    return Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
        .set(XmNclassName, (LONG_PTR)TRACKBAR_CLASS));

  }

  int    getPos() {
      return send(TBM_GETPOS, 0, 0L);
  }
  int    getRangeMin() {
      return send(TBM_GETRANGEMIN, 0, 0L);
  }
  int    getRangeMax() {
      return send(TBM_GETRANGEMAX, 0, 0L);
  }
  int    getTic() {
      return send(TBM_GETTIC, 0, 0L);
  }
  void   setTic() {
      send(TBM_SETTIC, 0, 0L);
  }
  void   setPos(int pos) {
      send(TBM_SETPOS, TRUE, pos);
  }
  void   setRange(int min, int max) {
      send(TBM_SETRANGE, TRUE, MAKELPARAM(min, max));
  }
  void  SetRangeMin(int min) {
      send(TBM_SETRANGEMIN, min, 0L);
  }
  void   setRangeMax(int max) {
      send( TBM_SETRANGEMAX, max, 0L);
  }
  void   clearTics() {
      send(TBM_CLEARTICS, 0, 0L);
  }
  void  setSel(int val) {
      send(TBM_SETSEL, 0, 0L);
  } 
  void   setSelStart(int start)  {
      send(TBM_SETSELSTART, start, 0L);
  }
  void   setSelEnd(int end) {
      send( TBM_SETSELEND, end, 0L);
  }
  LONG   getPTics() {
      return send(TBM_GETPTICS, 0, 0L);
  }
  int    getTicPos() {
      return send(TBM_GETTICPOS, 0, 0L);
  }
  int    getNumTics() {
      return send(TBM_GETNUMTICS, 0, 0L);
  }
  int   getSelStart() {
      return send(TBM_GETSELSTART, 0, 0L);
  }
  int   getSelEnd() {
      return send(TBM_GETSELEND, 0, 0L);
  }
  void   clearSel() {
      send(TBM_CLEARSEL, 0, 0L);
  }
  void   setTicFreq(int freq) {
      send(TBM_SETTICFREQ, 0, 0L);
  }
  void   setPageSize(int pageSize) {
      send(TBM_SETPAGESIZE, pageSize, 0L);
  }
  int   getPageSize() {
      return  send(TBM_GETPAGESIZE, 0, 0L);
  }
  void   setLineSize(int lineSize) {
      send(TBM_SETLINESIZE, lineSize, 0L);
  }
  int     getLineSize() {
      return send(TBM_GETLINESIZE, 0, 0L);
  }
  int     getThumbRect() {
      return send(TBM_GETTHUMBRECT, 0, 0L);
  }
  RECT*   getChannelRect() {
      return (RECT*)send(TBM_GETCHANNELRECT, 0, 0L);
  }
  void    setThumbLength(int length) {
      send(TBM_SETTHUMBLENGTH, length, 0L);
  }
  int    getThumbLength() {
      return send(TBM_GETTHUMBLENGTH, 0, 0L);
  }
};

}

