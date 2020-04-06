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
 *  FileTime.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once
#include <sol\Object.h>
#include <time.h>

#include <sol\String.h>

namespace SOL {

class FileTime :public Object {
private:
  int      timeZone;
  FILETIME    fileTime;

public:

  static const int LOCALTIME = 0;
  static const int GMT       = 1;

public:
  const wchar_t* toString(__out _bstr_t& string)
  {
    SYSTEMTIME stFileTime = getSystemTime();
    TCHAR buffer[256];
    
    _stprintf_s(buffer, sizeof(buffer)/sizeof(buffer[0]), _T("%04d/%02d/%02d %02d:%02d:%02d") ,
      stFileTime.wYear , stFileTime.wMonth ,
      stFileTime.wDay , stFileTime.wHour ,
      stFileTime.wMinute , stFileTime.wSecond);
    string = buffer;
    return (const wchar_t*)string;
  }

public:
  //2012/09/08
  _bstr_t toString()
  {
    SYSTEMTIME stFileTime = getSystemTime();
    TCHAR buffer[256];
    
    _stprintf_s(buffer, sizeof(buffer)/sizeof(buffer[0]), _T("%04d/%02d/%02d %02d:%02d:%02d") ,
      stFileTime.wYear , stFileTime.wMonth ,
      stFileTime.wDay , stFileTime.wHour ,
      stFileTime.wMinute , stFileTime.wSecond);
    return _bstr_t(buffer);
  }

public:
  FileTime(FILETIME ft, int zone=LOCALTIME)
  {
    fileTime = ft;
    timeZone = zone;
  }


public:
  FileTime(WORD wYear, WORD wMonth, WORD wDay,
       WORD wHour=0, WORD wMinute=0, WORD wSecond=0)
  {
    SYSTEMTIME systemTime;
    systemTime.wYear = wYear;
    systemTime.wMonth = wMonth;
    systemTime.wDay = wDay;
    systemTime.wHour = wHour;
    systemTime.wMinute = wMinute;
    systemTime.wSecond = wSecond;

    SystemTimeToFileTime(&systemTime,
        &fileTime);
  }

public:
  operator FILETIME() const{
    return this->fileTime;
  }

public:
  const FILETIME getFileTime()
  {
    return fileTime;
  }

public:
  SYSTEMTIME getSystemTime()
  {
    SYSTEMTIME sysTime;
    FILETIME lt;
    if (timeZone == LOCALTIME) {
      FileTimeToLocalFileTime(&fileTime, &lt);
      FileTimeToSystemTime(&lt, &sysTime);
    } else {
      FileTimeToSystemTime(&fileTime, &sysTime);
    }
    return sysTime;
  }


};

}

