/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  TextField.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2009/07/06 Modified to initialize member variables enterCallback(NULL) and
//    keyInCallback(NULL) in constructors.
// 2012/06/25

#pragma once

#include <sol\Text.h>
#include <sol\CallbackEntry.h>
#include <sol\Font.h>
#include <sol\ClientDC.h>

namespace SOL {

class TextField :public Text {
private:
  static const int  ENTER = 13;

private:
  static const long STYLE = WS_BORDER|ES_LEFT|ES_AUTOHSCROLL;


private:
  int    dataType;
  CallbackEntry* enterCallback;
  CallbackEntry* keyInCallback;

public:
  enum {T_STRING, T_INTEGER, T_BOOLEAN};

public:
  TextField()
  :Text(),
    enterCallback(NULL),
    keyInCallback(NULL)
  { 
  }
  TextField(View* parent, HWND hwnd)
  :Text(parent, hwnd),
    enterCallback(NULL),
    keyInCallback(NULL)
  {
  }

public:
  //2012/06/25
  TextField(View* parent, const TCHAR* name, Args& args)
  :Text()
  {
    create(parent, name, args);
  }

public:
  ~TextField() 
  { 
    delete enterCallback; 
    delete keyInCallback;
  }


public:
  void addCallback(const TCHAR* name, Object* object,
    Callback proc, void* data)
  {
    if(name == XmNactivateCallback) {
      if(enterCallback) {
        delete enterCallback;
      }
      enterCallback = new CallbackEntry(name, NULL, object,
        proc, data);
    }
    if(name == XmNkeyInCallback) {
      if(keyInCallback) {
        delete keyInCallback;
      }    
      keyInCallback = new CallbackEntry(name, NULL, object,
        proc, data);
    }
  }


public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Text::create(parent, name, 
      args.set(XmNstyle, (LONG_PTR)STYLE));

    enterCallback = NULL;
    keyInCallback = NULL;

    limitText(LINE_LENGTH);
    replaceWindowProc();
    addEventHandler(WM_CHAR, this,
          (Handler)&TextField::charIn, NULL);
    addEventHandler(WM_COMMAND, this,
         (Handler)&TextField::charIn, NULL);

    resize(name);    // Added
    dataType = T_STRING;
    setValues(args);

    return rc;
  }

public:

  long charIn(Event& event)
  {
    TCHAR line[LINE_LENGTH];
    WORD word = event.getWParam();
    if(keyInCallback) {
      Action action(NULL, event);
      keyInCallback -> call(action); 
    }

    if(dataType == T_BOOLEAN) {
      if((word >= '0' && word <='1') || 
        (word == VK_BACK)) {
        return defaultProc(event);
      }
      if(word != ENTER)
      return 0L;
    }
    if(dataType == T_INTEGER) {
      if((word >= '0' && word <='9') || 
        (word == VK_BACK)) {
        return defaultProc(event);
      }
      if(word != ENTER)
      return 0L;
    }

    if(word == ENTER) {
      if(enterCallback) {
            ::GetWindowText(getWindow(), line, LINE_LENGTH);
        Action action(NULL, event);
            enterCallback -> setData(line);
            enterCallback -> call(action);
      }
      return 0L;
    }

    return defaultProc(event);
  }

public:
  void getPreferredSize(Dimension& d)
  {
    ClientDC cdc(this);
    HFONT hfont = NULL;
    Font* font = getFont();
    if (font) {
      hfont = (HFONT)cdc.select(font);
    }
//  SIZE size;
    int h = cdc.getTextHeight();
    int x, y, ww, hh;

    getGeometry(x, y, ww, hh);
    reshape(x, y, ww, h+8);
    if (hfont) cdc.select(hfont);
  
    d.set(ww, h+8);
  }

public:
  void getValues(Args& args)
  {
    Text::getValues(args);

    LONG_PTR* val = (LONG_PTR*)args.get(XmNdataType);
    if(val) {
      *val = dataType;
    }
  }

public:
  void setValues(Args& args)
  {
    Text::setValues(args);

    LONG_PTR  val;
    if (args.get(XmNdataType, &val)) {
      dataType = val;
      // Limit text length.
      if(dataType == T_STRING) {
        limitText(LINE_LENGTH);
      }
      if(dataType == T_BOOLEAN) {
        limitText(1);
      }
      if(dataType == T_INTEGER) {
        limitText(6);
      }
    }
  }


  int    getDataType() { return dataType; }
};

}


