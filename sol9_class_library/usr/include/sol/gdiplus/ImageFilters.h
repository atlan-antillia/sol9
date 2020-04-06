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
 *  ImageFilters.h
 *
 *****************************************************************************/

// SOL9
// 2012/04/20

#pragma once

#include <sol\Object.h>
#include <sol\WString.h>
#include <gdiplus.h>

namespace SOL {

class ImageFilters :public Object {

private:
  struct NamedFilter{
    const wchar_t* name;
    const Gdiplus::ColorMatrix* matrix;
  };

public:
  ImageFilters()
  {
  }


public:
  bool getColorMatrix(__in const wchar_t* name, __out Gdiplus::ColorMatrix& matrix)
  {
    bool rc = false;

    if (name == NULL) {
      return rc;
    }

    //ColorMatrix filters.
    static const Gdiplus::ColorMatrix filters[]  = {
      //Gray : NTSC.
      {0.299f, 0.299f, 0.299f, 0, 0,
       0.587f, 0.587f, 0.587f, 0, 0,
       0.114f, 0.114f, 0.114f, 0, 0,
            0,      0,      0, 1, 0,
            0,      0,      0, 0, 1},

      //Lightgray
      {0.5f, 0.5f, 0.5f, 0, 0,
       0.5f, 0.5f, 0.5f, 0, 0,
       0.5f, 0.5f, 0.5f, 0, 0,
          0,    0,    0, 1, 0,
          0,    0,    0, 0, 1 },

      //Sepia : See http://msdn.microsoft.com/ja-jp/magazine/cc163866(en-us).aspx
      {0.393f, 0.349f, 0.272f, 0, 0,
       0.769f, 0.686f, 0.534f, 0, 0,
       0.189f, 0.168f, 0.131f, 0, 0,
            0,      0,      0, 1, 0,
            0,      0,      0, 0, 1},

      //Negative
      {-1,  0,  0, 0, 0,
        0, -1,  0, 0, 0, 
        0,  0, -1, 0, 0,
        0,  0,  0, 1, 0,
        1,  1,  1, 0, 1},
    };

    //Named ColorMatrix filters.
    static const NamedFilter namedFilters[] = {
      {L"Gray",      &filters[0]},
      {L"LightGray", &filters[1]},
      {L"Sepia",     &filters[2]},
      {L"Negative",  &filters[3]},
    };

    //Alpha ColorMatrix filter with a float parameter
    WString wstring = name;
    if (wstring.startsWithIgnoreCase(L"Alpha:")) {
      WString alpha, value;
      if (wstring.split(':', alpha, value) == 2) {
        float f = value.toFloat();

        const Gdiplus::ColorMatrix filter = 
        {1, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 
         0, 0, 1, 0, 0,
         0, 0, 0, f, 0,
         0, 0, 0, 0, 1};
        memcpy(&matrix, &filter, sizeof(matrix));
        rc = true;
      }
    }
    //Contrast(or Brightness) ColorMatrix filter with a float scale
    else if (wstring.startsWithIgnoreCase(L"Contrast:")) {
      WString contrast, scale;
      if (wstring.split(':', contrast, scale) == 2) {
        float f = scale.toFloat();
        //See also http://www.bobpowell.net/image_contrast.htm
        const Gdiplus::ColorMatrix filter = 
        {f, 0, 0, 0, 0,
         0, f, 0, 0, 0, 
         0, 0, f, 0, 0,
         0, 0, 0, 1, 0,
         0, 0, 0, 0, 1};
        memcpy(&matrix, &filter, sizeof(matrix));
        rc = true;
      }
    } else {
      //Find a matching ColorMatrix filter for name from namedFilters for 'Gray'. 'LightGray', 'Sepia', 'Negative'.
      for (int i = 0; i<CountOf(namedFilters); i++) {
        if (name && _wcsicmp(name, namedFilters[i].name) == 0) {
          //Found a filter.
          memcpy(&matrix, namedFilters[i].matrix, sizeof(matrix));
          rc = true;
          break;
        }
      }
    } 
    if (rc == false) {
      throw Exception(0, _T("Exception: Invalid filterName:%s"), (const TCHAR*)_bstr_t(name));
    }
    return rc;
  }
};

}
