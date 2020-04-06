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
 *  Action.h
 *
 *****************************************************************************/

// 2017/09/10 Updated.

#pragma once

#include <sol\Event.h>

/**
 * Action class.
 */
namespace SOL {

class Action : public Object {
  void*   data;
  void*   value;
  Event   event;      //2012/09/24
  long    result;       // return-value of callback

public:
  Action()
    :data(NULL),
    value(NULL),
    result(0)
  {
  }

public:
  Action(void* value1, Event& event1)
    :data(NULL),
    value(value1),
    event(event1),
    result(0) 
  {
    //
  }

  void*   getData() { return data; }
  void*   getValue() { return value; }
  Event&  getEvent() { return event; }
  long    getResult() { return result; }
  void    setData(void* data1) { data = data1; }
  void    setResult(long val) { result = val; }
  
  //2012/06/14
  LPARAM  getLParam() { return event.getLParam(); }

  //2012/06/14
  WPARAM  getWParam() { return event.getWParam(); }

  //2017/09/10
  int getIntValue() 
  {
    return to_integer(value);
  }

  //2017/09/10
  int getIntData()
  {
    return to_integer(data);
  }
};

}


