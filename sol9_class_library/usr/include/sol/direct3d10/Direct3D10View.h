/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Direct3D10View.h
 *
 *****************************************************************************/

#pragma once

#include <sol/direct3d10/Direct3D10DeviceChild.h>
 
namespace SOL {

class Direct3D10View : public Direct3D10DeviceChild {
public:
  Direct3D10View()
  :Direct3D10DeviceChild()
  {
  }
  
  ~Direct3D10View()
  {
  }
  
  operator ID3D10View*()
  {
    return getView();
  }

  ID3D10View* getView()
  {
    ID3D10View* view = (ID3D10View* )getIUnknown();
    if (view) {
      return view;
    } else {
      throw IException("I3D10View is NULL.")
    }
  }
  
  void  getResource( 
            __out  ID3D10Resource **ppResource)
  {        
    ID3D10View* view = getView();
    view -> GetResource( 
            ppResource);
  }
  
};
}