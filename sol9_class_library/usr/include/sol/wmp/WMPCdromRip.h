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
 *  WMPCdromRip.h
 *
 *****************************************************************************/


// SOL9
// 2011/12/12

#pragma once

#include <sol/wmp/WMPObject.h>


namespace SOL {

class WMPCdromRip :public WMPObject {
private:
  IWMPCdromRipPtr cdromRip;
 
public:
  WMPCdromRip(IWMPCdromRipPtr ptr)
  :cdromRip(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("IWMPCdromRipPtr is NULL", 0);
    }
  }

/*
enum WMPRipState
{
    wmprsUnknown = 0,
    wmprsRipping = 1,
    wmprsStopped = 2
};
*/

public:
  enum WMPRipState getRipState()
  {
    return cdromRip->GetripState();
  }

  long getRipProgress()
  {
    return cdromRip->GetripProgress();
  }


  HRESULT startRip()
  {
    return cdromRip->startRip();
  }


  HRESULT stopRip()
  {
    return cdromRip->stopRip();
  }


};

}
