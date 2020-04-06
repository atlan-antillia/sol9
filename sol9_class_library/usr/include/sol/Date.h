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
 *  Date.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once
#include <sol\Object.h>
#include <time.h>

#include <sol\String.h>

namespace SOL {

class Date :public Object {
private:
  int      timeZone;
  String    date;
  SYSTEMTIME  systemTime;

public:

  static const int LOCALTIME = 0;
  static const int GMT       = 1;

private:
  void toString(SYSTEMTIME& sysTime)
  {
    TCHAR* month[] = {
    _T("Jan"),  // 0
    _T("Feb"),  // 1
    _T("Mar"),  // 2
    _T("Apr"),  // 3
    _T("May"),  // 4
    _T("Jun"),  // 5
    _T("Jul"),  // 6
    _T("Aug"),  // 7
    _T("Sep"),  // 8
    _T("Oct"),  // 9
    _T("Nov"),  //10
    _T("Dec"),  //11
    };
  
    TCHAR* week[] = {
    _T("Sun"),  // 0
    _T("Mon"),  // 1
    _T("Tue"),  // 2
    _T("Wed"),  // 3
    _T("Thu"),  // 4
    _T("Fri"),  // 5
    _T("Sat"),  // 6
    };

    this->systemTime = sysTime;

    TCHAR buffer[80];
    if (timeZone == LOCALTIME) {
      _stprintf_s(buffer, CountOf(buffer), _T("%s, %02d %s %4d %02d:%02d:%02d"),
        week[sysTime.wDayOfWeek],
        sysTime.wDay,
        month[sysTime.wMonth-1],
        sysTime.wYear,
        sysTime.wHour,
        sysTime.wMinute,
        sysTime.wSecond);
    } else {
      _stprintf_s(buffer, CountOf(buffer), _T("%s, %02d %s %4d %02d:%02d:%02d GMT"),
        week[sysTime.wDayOfWeek],
        sysTime.wDay,
        month[sysTime.wMonth-1],
        sysTime.wYear,
        sysTime.wHour,
        sysTime.wMinute,
        sysTime.wSecond);
    }
    date = buffer;
  }

public:
  Date(int zone=LOCALTIME)
  {
    timeZone = zone;
    SYSTEMTIME sysTime;

    if (timeZone == LOCALTIME) {
      GetLocalTime(&sysTime);
    } else {
      GetSystemTime(&sysTime);
    }
    toString(sysTime);
  }


  Date(SYSTEMTIME& sysTime, int zone=LOCALTIME)
  {
    timeZone = zone;
    toString(sysTime);
  }

public:
  Date(FILETIME& ft, int zone=LOCALTIME)
  {
    timeZone = zone;
    SYSTEMTIME sysTime;
    FILETIME lt;
    if (timeZone == LOCALTIME) {
      FileTimeToLocalFileTime(&ft, &lt);
      FileTimeToSystemTime(&lt, &sysTime);
    } else {
      FileTimeToSystemTime(&ft, &sysTime);
    }
    toString(sysTime);
  }

public:
  const TCHAR* getDate() const { 
    return (const TCHAR*)date; 
  }

public:
  bool getDate(__out StringT<char>& string) const {
    bool rc = false;
    if (date.getLength()>0) {
#ifdef UNICODE
  StringConverter converter;
  converter.convert((const wchar_t*)date, string);
#else
  string = (const char*)date;
#endif
      rc = true;
    }
    return rc;
  }

public:
  SYSTEMTIME&  getSystemTime() { 
    return systemTime; 
  }

public:
  operator const TCHAR*() { 
    return (const TCHAR*)date; 
  }

};

}

