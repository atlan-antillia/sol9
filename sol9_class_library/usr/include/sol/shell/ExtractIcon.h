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
 *  ExtractIcon.h
 *
 *****************************************************************************/


// 2012/11/30

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shlobj.h>

namespace SOL {

class ExtractIcon :public ComIUnknown {

public:
  ExtractIcon(IExtractIcon* pExtractor)
  :ComIUnknown(pExtractor)
  {
  }
  
public:
  IExtractIcon* getExtractor()
  {  
    return (IExtractIcon*)getIUnknown();
  }

public:
  HRESULT getIconLocation(
      UINT   uFlags,
      LPTSTR  szIconFile,
      UINT   cchMax,
      __out int   *piIndex,
      __out UINT  *pwFlags)
  {
    IExtractIcon* pExtractor = getExtractor();
    HRESULT hr = pExtractor -> GetIconLocation(
        uFlags,
        szIconFile,
        cchMax,
        piIndex,
        pwFlags);
    if (FAILED(hr)) {
      throw hr;
    }  
    return hr;
  }
  


public:
  HRESULT extract(
        LPTSTR  pszFile,
        UINT    nIconIndex,
        __out_opt HICON   *phiconLarge,
        __out_opt HICON   *phiconSmall,
        UINT    nIconSize)
  {
    IExtractIcon* pExtractor = getExtractor();
    HRESULT hr = pExtractor -> Extract(
      pszFile,
      nIconIndex,
      phiconLarge,
      phiconSmall,
      nIconSize);
    if (FAILED(hr)) {
      throw hr;
    }  
    return hr;
  }

};

}
