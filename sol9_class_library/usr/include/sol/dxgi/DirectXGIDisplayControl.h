/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DirectXGIDisplayControl.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/com/IUnknown.h>
#include <dxgi1_2.h>


namespace SOL {

class DirectXGIDisplayControl1 : public ComIUnknown {
    
public:
  DirectXGIDisplayControl1()
  :ComIUnknown()
  {
    IDXGIFactory1* factory1 = NULL;
    HRESULT hr = CreateDXGIFactory1( 
      0, 
      __uuidof(IDXGIFactory1),
      (void**)&factory1);
    if (SUCCEEDED(hr)) {
      set(factory1);
    } else {
      throw IException("Failed to CreateDXGIFactory1. HRESULT(%lf)", hr);
    }

  }
  
  operator IDXGIDisplayControl*()
  {
    return getDisplayControl1();
  }
  
  IDXGIDisplayControl* getDisplayControl1()
  {
    IDXGIDisplayControl* control1 = (IDXGIDisplayControl*)getIUnknown();
    if (control1) {
      return control1;
    } else {
      throw IException("IDXGIControl1 is NULL.");
    }
  }
  
  BOOL  isStereoEnabled()
  {
    IDXGIDisplayControl* control1 = getControl1();
    if (control1) {
      return control1 -> IsStereoEnabled();
    } else {
      throw IException("IDXGIFactory1 is NULL.");
    }
  }
        
  void  setStereoEnabled( 
            BOOL enabled) 
  {
    IDXGIDisplayControl* control1 = getControl1();
    if (control1) {
      control1 -> SetStereoEnabled( 
            enabled) ;
    } else {
      throw IException("IDXGIFactory1 is NULL.");
    }
  }
        
};
}    


