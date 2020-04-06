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
 *  OpenGLPalette.h
 *
 *****************************************************************************/

// 2015/07/22

#pragma once

#include <sol/opengl/OpenGLObject.h>
#include <sol/ClientDC.h>

namespace SOL {

class OpenGLPalette :public OpenGLObject {
protected:
  HPALETTE hPalette;

public:
  OpenGLPalette(ClientDC* clientDC)
  :hPalette(NULL)
  {
    if (clientDC == NULL) {
      throw IException("Invalid argument: ClientDC is NULL");    
    }
    HDC hDC = clientDC -> get(); 
    createPalette(hDC);
  }

  // See http://www.cs.rit.edu/~ncs/Courses/570/UserGuide/OpenGLonWin-11.html
  virtual void createPalette(HDC hDC)
  {
    if (hDC == NULL) {
      throw IException("Invalid argumet: HDC is NULL");
    }
    
    int pixelFormat = GetPixelFormat(hDC);
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    DescribePixelFormat(hDC, pixelFormat, sizeof(pfd), &pfd);

    int paletteSize = 0;

    if (pfd.dwFlags & PFD_NEED_PALETTE) {
        paletteSize = 1 << pfd.cColorBits;
    } else {
        return;
    }
    char* pbuffer = new char[sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY) ]; 
    LOGPALETTE* pPal = (LOGPALETTE*)pbuffer;
        
    pPal->palVersion = 0x300;
    pPal->palNumEntries = paletteSize;

    //  RGB color palette 
    int redMask = (1 << pfd.cRedBits) - 1;
    int greenMask = (1 << pfd.cGreenBits) - 1;
    int blueMask = (1 << pfd.cBlueBits) - 1;
  
    for (int i=0; i<paletteSize; ++i) {
      pPal->palPalEntry[i].peRed =
                    (((i >> pfd.cRedShift) & redMask) * 255) / redMask;
      pPal->palPalEntry[i].peGreen =
                    (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
      pPal->palPalEntry[i].peBlue =
                    (((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
      pPal->palPalEntry[i].peFlags = 0;
    }
  
    hPalette = CreatePalette(pPal);
    delete [] pbuffer;

    if (hPalette) {
      SelectPalette(hDC, hPalette, FALSE);
      RealizePalette(hDC);
    } else {
      throw IException("Failed to CreatePalette");
    }
  }

  ~OpenGLPalette()
  {
    if (hPalette) {
      DeleteObject(hPalette);
      hPalette = NULL;
    }
  }
};
}
