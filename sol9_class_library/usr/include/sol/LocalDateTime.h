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
 *  LocalDateTime.h
 *
 *****************************************************************************/

// SOL9 2009/08/29
// 2009/12/21 Modified
// 2012/06/25 Updated

#pragma once

#include <sol\Object.h>
#include <sol/String.h>
#include <sol/StringT.h>
//#include <sol/StringConverter.h>

namespace SOL {

/*
 Get a localTime by using API GetLocalTime and return a string expression of a format  
 "YYYY/MM/DD HH:MM:SS" or "YYYY/MM/DD HH:MM:SS:ss"
*/

class LocalDateTime :public Object {

public:
  LocalDateTime()
  {
  }

public:
  //2012/06/25
  String nowToSeconds() {
    TCHAR buff[128];
    memset(buff, (TCHAR)0, CountOf(buff));
    nowToSeconds(buff, CountOf(buff));
    return String(buff);
  }

public:
  //2012/06/25
  const TCHAR* nowToSeconds(__out String& dateTime) {
    char buff[128];
    memset(buff, (char)0, CountOf(buff));
    nowToSeconds(buff, CountOf(buff));
    dateTime = buff;
    return (const TCHAR*)dateTime;
  }

public:
  //2012/06/25
  const char* nowToSeconds(__out StringT<char>& dateTime) {
    char buff[128];
    memset(buff, (char)0, CountOf(buff));
    nowToSeconds(buff, CountOf(buff));
    dateTime = buff;
    return (const char*)dateTime;
  }

public:
  //2009/12/21
  const wchar_t* nowToSeconds(__out StringT<wchar_t>& dateTime) {
    //2012/06/25
    wchar_t buff[128];
    memset(buff, (wchar_t)0, CountOf(buff));
    nowToSeconds(buff, CountOf(buff));

    dateTime = buff;
    return (const wchar_t*)dateTime;
  }

public:
  /**
     */
  void nowToSeconds(__inout char* buff, int size) 
  {
    SYSTEMTIME systime;
    if (buff && size > 0) {
      GetLocalTime(&systime);
      sprintf_s(buff, size, 
        "%04d/%02d/%02d %02d:%02d:%02d",
        systime.wYear,
        systime.wMonth,
        systime.wDay,
        systime.wHour,
        systime.wMinute,
      systime.wSecond);
    } else {
      throw IException("Invalid argument");
    }
  }    

public:
  //2012/06/25
  void nowToSeconds(__inout wchar_t* buff, int size) 
  {
    SYSTEMTIME systime;
    if (buff && size >0) {
      GetLocalTime(&systime);
      swprintf_s(buff, size, 
        L"%04d/%02d/%02d %02d:%02d:%02d",
        systime.wYear,
        systime.wMonth,
        systime.wDay,
        systime.wHour,
        systime.wMinute,
      systime.wSecond);
    } else {
      throw IException ("Invalid argument");
    }
  }    

public:
  //2012/06/25
  String nowToMilliseconds()
  {
    TCHAR buff[128];
    memset(buff, (TCHAR)0, CountOf(buff));
    nowToMilliseconds(buff, CountOf(buff));  
    return String(buff);
  }

public:
  //2012/06/25
  const TCHAR* nowToMilliseconds(__out String& dateTime) {
    TCHAR buff[128];
    memset(buff, (TCHAR)0, CountOf(buff));
    nowToMilliseconds(buff, CountOf(buff));
    dateTime = buff;
    return (const TCHAR*)dateTime;
  }

public:
  //2012/06/25  
  const char* nowToMilliseconds(__out StringT<char>& dateTime) {
    char buff[128];
    memset(buff, (char)0, CountOf(buff));

    nowToMilliseconds(buff, CountOf(buff));
    dateTime = buff;    
    return (const char*)dateTime;
  }


public:
  /**
     */
  void nowToMilliseconds(char* buff, int size) 
  {
    SYSTEMTIME systime;

    GetLocalTime(&systime);
  
    sprintf_s(buff, size,
    "%04d-%02d-%02d %02d:%02d:%02d:%03d",
    systime.wYear,
    systime.wMonth,
    systime.wDay,
    systime.wHour,
    systime.wMinute,
    systime.wSecond,
    systime.wMilliseconds);

  }


public:
  //2012/06/25
  const wchar_t* nowToMilliseconds(__out StringT<wchar_t>& dateTime) 
  {
    //2012/06/25
    wchar_t buff[128];
    memset(buff, (wchar_t)0, CountOf(buff));
    nowToMilliseconds(buff, CountOf(buff));

    dateTime = buff;
    return (const wchar_t*)dateTime;
  }

public:
  //2012/06/25
  void nowToMilliseconds(wchar_t* buff, int size) 
  {
    SYSTEMTIME systime;

    GetLocalTime(&systime);
  
    swprintf_s(buff, size,
    L"%04d-%02d-%02d %02d:%02d:%02d:%03d",
    systime.wYear,
    systime.wMonth,
    systime.wDay,
    systime.wHour,
    systime.wMinute,
    systime.wSecond,
    systime.wMilliseconds);

  }    

};


}


