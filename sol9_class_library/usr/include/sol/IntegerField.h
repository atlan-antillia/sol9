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
 *  IntegerField.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/25

#pragma once

#include <sol\Text.h>


namespace SOL {

class IntegerField :public Text {
private:
  static  const long STYLE = (WS_BORDER|ES_LEFT|ES_AUTOHSCROLL);

private:
  CallbackEntry* entry;

protected:
  long charIn(Event& event)
  {
    TCHAR line[256];
    WORD word = event.getWParam();
    if(word >= '0' && word <='9') 
      return defaultProc(event);
    if(word == VK_BACK) 
      return defaultProc(event);
    if(word == VK_RETURN) {
      if(entry) {
        Text::getText(line, 255);
        Action action(NULL, event);
              entry -> setData(line);
              entry -> call(action);
      }
      return NULL;
    }
    return NULL;
  }

public:
  IntegerField():Text() { }

public:
  //2012/06/25
  IntegerField::IntegerField(View* parent, const TCHAR* name, Args& args)
  :Text()
  {
    create(parent, name, args);
  }


public:
  ~IntegerField() { 
    if(entry) delete entry; 
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Text::create(parent, name, 
      args.set(XmNstyle, (LONG_PTR)STYLE));

    entry = NULL;

    limitText(30);  //20->30
    replaceWindowProc();
    addEventHandler(WM_CHAR, this,
      (Handler)&IntegerField::charIn, NULL);
    addEventHandler(WM_COMMAND, this,
          (Handler)&IntegerField::charIn, NULL);

    resize(name);

    return rc;
  }

public:
  void addCallback(const TCHAR* name, Object* object,
    Callback proc, void* data)
  {
    if(entry) {
      delete entry;
    }
    entry = new CallbackEntry(name, NULL, object,
        proc, data);
  }


public:
  void setInteger(int num)
  {
    TCHAR buffer[80];
    _stprintf_s(buffer, CountOf(buffer), _T("%d"), num);
    Text::setText(buffer);
  }

public:
  void setLong(long num)
  {
    TCHAR buffer[80];
    _stprintf_s(buffer, CountOf(buffer), _T("%ld"), num);
    Text::setText(buffer);
  }


public:
  int getInteger()
  {
    TCHAR buffer[80];
    getText(buffer, CountOf(buffer));
    TCHAR* error = NULL;
    return strtol((const TCHAR*)buffer, &error, 10);
  }

public:
  long getLong()
  {
    TCHAR buffer[80];
    getText(buffer, CountOf(buffer));
    TCHAR* error = NULL;
    return strtol((const TCHAR*)buffer, &error, 10);

  }


};

}

