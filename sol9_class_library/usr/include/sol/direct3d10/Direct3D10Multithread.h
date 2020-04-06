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
 *  Direct3D10Multithread.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Exception.h>
#include <sol/com/ComIUnknown.h>
#include <d3d10_1.h>

namespace SOL {
  
class Direct3D10Multithread : public ComIUnknown {

public:
  Direct3D10Multithread()
  {
  }
  
  ~Direct3D10Multithread()
  {
  }

  operator ID3D10Multithread*()
  {
    return getMultithread();
  }

  ID3D10Multithread* getMultithread()
  {
    ID3D10Multithread* multithread = (ID3D10Multithread* )getIUnknown();
    if (multithread) {
      return multithread;
    } else {
      throw IException("D3D10Multithread is NULL.")
    }
  }

  void  enter()
  {
    ID3D10Multithread* multithread = getMultithread();
    multithread -> Enter();
  }       
  void  leave()
  {
    ID3D10Multithread* multithread = getMultithread();
    multithread -> Leave();
  }       
        
  BOOL  setMultithreadProtected( 
            __in  BOOL bMTProtect)
  {
    ID3D10Multithread* multithread = getMultithread();
    return multithread -> SetMultithreadProtected( 
            bMTProtect);
  }       
        
  BOOL getMultithreadProtected()
  {
    ID3D10Multithread* multithread = getMultithread();
    return multithread -> GetMultithreadProtected();
  }       
        
};
  
}

