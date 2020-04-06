/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  MessageFont.h
 *
 *****************************************************************************/

// SOL9
// 2008/08/13
#pragma once

#include <sol\Font.h>


namespace SOL {

/**
 * MessageFont class
 */
class MessageFont :public Font {
private:
  LOGFONT lf;

public:
  /**
   * Constructor
   */
  MessageFont()
  :Font() {
    memset(&lf, 0, sizeof(lf));
    getMessageFont(lf);    
  }

public:
  ~MessageFont() {
  }


public:

  Boolean   create(int pointSize) {
    //this -> pointSize = pointSize;

    HDC hdc = GetDC(NULL);
    int height = -MulDiv(pointSize,GetDeviceCaps(hdc,LOGPIXELSY),72);
    ReleaseDC(NULL, hdc);

    lf.lfHeight = height;

    return Font::create(&lf);
  }

public:

  Boolean   create() {
    return Font::create(&lf);
  }

private:
  BOOL getMessageFont(LOGFONT& lf) {
    
    NONCLIENTMETRICS ncm;
    memset(&ncm, 0, sizeof(ncm)); 
    ncm.cbSize = sizeof(ncm); 

    BOOL rc = SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0); 
    if (rc) {
      lf = ncm.lfMessageFont; 
    }
    return rc;
  }

public:
  LOGFONT& getLogMessageFont() {
    return lf;
  }
};

}
