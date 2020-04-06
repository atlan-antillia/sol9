/******************************************************************************
 *
 * Copyright (c) 2008-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  HexView.h
 *
 *****************************************************************************/

// SOL9
// 2008/09/04
// 2008/12/16 Modfied addHexData method.
// 2012/06/22

#pragma once
#include <sol\ListView.h>
#include <sol\CourierFont.h>
#include <sol/StringT.h>
#include <sol/StringConverter.h>


namespace SOL {

/**
 * HexView class to display hex data into a listview.
 */
class HexView :public ListView {

private:
  CourierFont  courier;

public:
  HexView():ListView() { }


public:
  //2012/06/22
  HexView(View* parent, const TCHAR* name, Args& args)
    :ListView()
  {
    create(parent, name, args);
  }

public:
  /**
   * Create a listview and insert columns for hex view
   */
  Boolean create(View* parent, const TCHAR* name, Args& args) {
    Boolean rc = ListView::create(parent, name,   
        args.set(XmNstyle,  (LONG_PTR)LVS_REPORT));

    ListViewColumn items[] = {
      {_T("ADDRESS"),   LVCFMT_LEFT, 84},  //2009/11/06
      {_T("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"),   LVCFMT_LEFT, 360},
      {_T("0123456789ABCDEF"), LVCFMT_LEFT, 134},  //2009/11/06
    };
    
    courier.create(9);

    HFONT hf = courier.getFont();
    setColumn(items, sizeof(items)/sizeof(items[0]));
    send(WM_SETFONT, (WPARAM)hf, 1);

    setExtendedViewStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); 

    return rc;

  }

public:
  /**
   * Insert hex data into this listview. with a format of the columns.
   * 
   */

  void addHexData(int& id, unsigned char* buff, DWORD cbRead) {
    const int SIXTEEN = 16;
    int lineNum = cbRead/SIXTEEN;
    int lineRem = cbRead % SIXTEEN;
    if (lineRem>0) {
      lineNum++;
    }
    unsigned char* ptr = (unsigned char*)buff;
    char ascString[SIXTEEN+1];
        
    for(int i = 0; i<lineNum; i++) {
      memset(ascString, 0, SIXTEEN+1);

      const int slen = SIXTEEN*3 + 1;
      char hexString[slen];
      memset(hexString, 0, slen); 
      char* b = hexString;

      int lineLen = SIXTEEN;
      if (lineRem >0 && i== (lineNum-1)) {
        lineLen = lineRem;
      }
      for (int j = 0; j<lineLen; j++) {
        char c = *ptr;
        if (c == '\0') {
          c= '.';
        }
        ascString[j] = c;
        sprintf_s(b, CountOf(hexString), "%02X ", *ptr++);
        b += 3;
      }
      //2008/12/16
      const TCHAR* items[3];
      TCHAR address[32];
      _stprintf_s(address, CountOf(address), _T("0X%08X"), id*16);
      
      StringT<TCHAR> thex;
      StringT<TCHAR> tasc;
      StringConverter converter;
      converter.convert(hexString, thex);
      converter.convert(ascString, tasc);
      int n = 0;
      items[n++] = address;
      items[n++] = (const TCHAR*)thex;//hexString;
      items[n++] = (const TCHAR*)tasc;//ascString;

      insertLine(id++, items, n);
    }
  }
};

}
