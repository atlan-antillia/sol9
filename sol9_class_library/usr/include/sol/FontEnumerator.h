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
 *  FontEnumerator.cpp
 *
 *****************************************************************************/

// SOL++2000
#pragma once


#include <sol/Object.h>

namespace SOL {

class FontEnumerator :public Object {

private:
  int num;

public:
  FontEnumerator() {
    this->num = 0;
  }

public:
  //
  //
  // return Number of enumerated fonts(this->num).

  int enumerate(const TCHAR* faceName=_T(""))
  {
        HDC hDC = GetDC(NULL);

    LOGFONT lf = { 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
             0, _T("") };

    strcpy_s(lf.lfFaceName, CountOf(lf.lfFaceName), faceName);

    this-> num=0;

    EnumFontFamiliesEx( hDC, &lf, (FONTENUMPROC)EnumFontFamiliesExProc, (LPARAM)this, 0 );

    //printf("Num=%d\n", num);

    ReleaseDC( NULL, hDC );
    return this->num;
    
  }

private:
  static int CALLBACK EnumFontFamiliesExProc( ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, 
        int FontType, LPARAM lParam)
  {
    FontEnumerator* fontEnum = (FontEnumerator*)lParam;

    fontEnum->increment();

    //Printf( "%s\n", lpelfe->elfFullName );
    return 1;
  }

public:
  void increment() {
    num++;
  }

public:
  int  getNumber() {
    return num;
  }
};

}


/*
 int main( int __argc, TCHAR** __argv )

{

  const char* faceName = "ÉÅÉCÉäÉI";

  FontEnumerator fontEnum;
  int n = fontEnum.enumerate(faceName);
  printf("Font=%s number =%d\n", faceName, n);
  return 0;
}

*/
