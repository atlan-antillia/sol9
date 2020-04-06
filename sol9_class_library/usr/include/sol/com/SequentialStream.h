/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SequentialStream.h
 *
 *****************************************************************************/

// SOL9
// 2012/08/08

#pragma once

#include <sol/com/ComIUnknown.h>


namespace SOL {

class  SequentialStream : public ComIUnknown {

public:
  SequentialStream(IUnknown* pUnknown=NULL)
  :ComIUnknown(pUnknown)
  {

  }

public:
  operator ISequentialStream*() {
    return getSequentialStream();
  }

public:
  ISequentialStream* getSequentialStream()
  {
    IUnknown* pUnknown = getIUnknown();
    if (pUnknown == NULL) {
      throw Exception(0, "ISequentialStream pointer is NULL");
    }
    return (ISequentialStream*)pUnknown;
  }

public:
       
  virtual HRESULT read( 
    __in void *pv,
    __in ULONG cb,
    __out ULONG *pcbRead)
  {
    HRESULT hr = getSequentialStream()->Read( 
      pv,
      cb,
                pcbRead);
    if (FAILED(hr)) {
      throw Exception(hr, "SequentialStream::read failed");
    }
    return hr;
  }

public:        
        virtual HRESULT write( 
    __in const void *pv,
    __in ULONG cb,
    __out ULONG *pcbWritten)
  {
    HRESULT hr = getSequentialStream() -> Write( 
      pv,
      cb,
      pcbWritten);
    if (FAILED(hr)) {
      throw Exception(hr, "SequentialStream::write failed");
    }
    return hr;

  }
        
};

}
