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
 *  SolLibRegistry.h
 *
 *****************************************************************************/

#pragma once


#include <sol\CurrentUserRegistry.h>


#ifndef _SOL_LIB_REGISTRY_
#define _SOL_LIB_REGISTRY_

#define  _SOL_LIB_REGISTRY_DEFAULTFONT_KEY  "Software\\Antillia\\SolLib\\DefaultFont"

namespace SOL {

class SolLibRegistry :public CurrentUserRegistry {

public:
  /**
   */
  SolLibRegistry()
    :CurrentUserRegistry() {
        
  }

public:
  bool  getDefaultFontPoint(int& size) {
    bool rc = false;
    //size = 8;
    if (getInteger(_SOL_LIB_REGISTRY_DEFAULTFONT_KEY, "PointSize", size) ) {
      rc = true;
    }
    if (size == 0) {
      size = 9;
    }
    return rc;
  }

public:
  bool  getDefaultFontFaceName(String& name) {
    bool rc = false;
    name = "";
    
    if (getText(_SOL_LIB_REGISTRY_DEFAULTFONT_KEY, "FaceName", name) ) {
      rc = true;
    }
    return rc;
  }

};

}

#endif
