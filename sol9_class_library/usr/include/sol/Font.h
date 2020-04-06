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
 *  Font.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/05/31

#pragma once

#include <sol\Args.h>

#include <sol\GdiObject.h>
#include <sol\ClientDC.h>

namespace SOL {

class Font :public GdiObject {
private:
  LOGFONT lf;
  
private:

  HFONT  create(Arg* arg, int num)
  {
    memset(&lf, 0, sizeof(LOGFONT));

    lf.lfPitchAndFamily =VARIABLE_PITCH|FF_ROMAN;

    //lf.lfPitchAndFamily = DEFAULT_PITCH|FF_MODERN;//FF_DONTCARE;
    //lf.lfPitchAndFamily = FF_DONTCARE;

    //OUT_STROKE_PRECIS 
    /*
    Ouput precisiion
    OUT_STRING_PRECIS = 1;
    OUT_CHARACTER_PRECIS = 2;
    OUT_STROKE_PRECIS = 3;
    OUT_TT_PRECIS = 4;
    OUT_DEVICE_PRECIS = 5;
    OUT_RASTER_PRECIS = 6;
    OUT_TT_ONLY_PRECIS = 7;
    OUT_OUTLINE_PRECIS = 8;
    OUT_SCREEN_OUTLINE_PRECIS = 9; 
    */
    //lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    lf.lfOutPrecision   = OUT_STROKE_PRECIS;

    /*
    Clip precision

    CLIP_DEFAULT_PRECIS = 0;
    CLIP_CHARACTER_PRECIS = 1;
    CLIP_STROKE_PRECIS = 2;
    CLIP_MASK = 15;
    CLIP_LH_ANGLES = (1 shl 4);
    CLIP_TT_ALWAYS = (2 shl 4);
    CLIP_EMBEDDED  = (8 shl 4);
    */

    //lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfClipPrecision  = CLIP_STROKE_PRECIS;
    /*
    Font Quality
    DEFAULT_QUALITY = 0;
    DRAFT_QUALITY = 1;  
    PROOF_QUALITY = 2;
    NONANTIALIASED_QUALITY = 3;
    ANTIALIASED_QUALITY = 4;
    */
    //lf.lfQuality      = DEFAULT_QUALITY;
    lf.lfQuality      = DRAFT_QUALITY;

    //2008/06/26 Modified to use DEFAULT_CHARSSET
    /*
    ANSI_CHARSET = 0;
    DEFAULT_CHARSET = 1;
    SYMBOL_CHARSET = 2;
    SHIFTJIS_CHARSET = $80;
    HANGEUL_CHARSET = 129;
    GB2312_CHARSET = 134;
    CHINESEBIG5_CHARSET = 136;
    OEM_CHARSET = 255;
    JOHAB_CHARSET = 130;
    HEBREW_CHARSET = 177;
    ARABIC_CHARSET = 178;
    GREEK_CHARSET = 161;
    TURKISH_CHARSET = 162;
    VIETNAMESE_CHARSET = 163; 
    THAI_CHARSET = 222;
    EASTEUROPE_CHARSET = 238;
    RUSSIAN_CHARSET = 204;

    MAC_CHARSET = 77;
    BALTIC_CHARSET = 186;
    */

    lf.lfCharSet        = DEFAULT_CHARSET;

    /*
    Font Weights
    FW_DONTCARE = 0;
    FW_THIN = 100;
    FW_EXTRALIGHT = 200;
    FW_LIGHT = 300;
    FW_NORMAL = 400;
    FW_MEDIUM = 500;
    FW_SEMIBOLD = 600;
    FW_BOLD = 700;
    FW_EXTRABOLD = 800;
    FW_HEAVY = 900;
    FW_ULTRALIGHT = FW_EXTRALIGHT;
    FW_REGULAR = FW_NORMAL;
    FW_DEMIBOLD = FW_SEMIBOLD;
    FW_ULTRABOLD = FW_EXTRABOLD;
    FW_BLACK = FW_HEAVY;
    */

    lf.lfWeight      = FW_REGULAR;

    for(int i = 0; i<num; i++) {
      if(arg[i].name == XmNwidth) {
        lf.lfWidth = (int)arg[i].value; 
        continue; 
      }
      if(arg[i].name == XmNheight) {
        lf.lfHeight = (int)arg[i].value; 
        continue;
      }

      //2008/07/02
      if(arg[i].name == XmNpointSize) {
        int size = (int)arg[i].value;
        HDC hDC = GetDC(NULL);
        DWORD h = GetDeviceCaps(hDC, LOGPIXELSY);
        int nHeight = -MulDiv(size, h, 72);
        ReleaseDC(NULL, hDC);
      
        lf.lfHeight = nHeight; 
        continue;
      }

      if(arg[i].name == XmNweight) {
        lf.lfWeight = (int)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNorientation) {
        lf.lfOrientation = (int)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNescapement) {
        lf.lfEscapement = (int)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNitalic) {
        lf.lfItalic = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNunderline) {
        lf.lfUnderline = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNstrikeout) {
        lf.lfStrikeOut = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNcharSet) {
        lf.lfCharSet = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNoutputPrecision) {
        lf.lfOutPrecision = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNclipPrecision) {
        lf.lfClipPrecision = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNquality) {
        lf.lfQuality = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNpitchAndFamily) {
        lf.lfPitchAndFamily = (BYTE)arg[i].value; 
        continue;
      }
      if(arg[i].name == XmNfaceName){
         strcpy_s(lf.lfFaceName, 
            CountOf(lf.lfFaceName), 
            (const TCHAR*)(LPSTR)arg[i].value);
        continue;
      }
    }
    return  ::CreateFontIndirect(&lf);
  }


public:
  Font()
  :GdiObject(NULL)
  {
  }


public:
  Font(Args& args)
  :GdiObject((HANDLE)create(args.getArgList(), args.getCount()))
  {
  }

public:
  Font(LOGFONT* logFont)
  :GdiObject((HANDLE)::CreateFontIndirect(logFont))
  {
    lf = *logFont;
  }

public:
  Font(Arg* arg, int num)
  :GdiObject((HANDLE)create(arg, num))
  {
  }

public:
  Boolean create(Args& args)
  {
    Boolean rc = False;
    HANDLE hfont = (HANDLE)create(args.getArgList(), args.getCount());
    if (hfont) {
      setHandle(hfont);
      rc = True;
    }
    return rc;
  }

public:
  Boolean create(LOGFONT* logFont)
  {
    Boolean rc = False;

    HANDLE hfont = (HANDLE)::CreateFontIndirect(logFont);

    if (hfont) {
      setHandle(hfont);
      rc = True;
    }
    return rc;
  }

public:
  ~Font()
  {
    HFONT hfont = (HFONT)get();
    if(hfont) {
      ::DeleteObject(hfont);
    }
  }


  HFONT  getFont() {
      return (HFONT)get();
  }

  LOGFONT* getLogFont() { 
    return &lf;
  }

public:
// 2012/05/31
  operator HFONT() {
    return (HFONT)get();
  }
};

}


