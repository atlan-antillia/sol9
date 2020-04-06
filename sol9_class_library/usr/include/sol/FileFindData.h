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
 *  FileFindData.h
 *
 *****************************************************************************/

// SOL++2000

#pragma once

#include <sol\Object.h>
#include <sol\Exception.h>
#include <sol\String.h>
#include <sol/StringT.h>

/*
typedef struct _WIN32_FIND_DATA {  
DWORD dwFileAttributes;  
FILETIME ftCreationTime;  
FILETIME ftLastAccessTime;  
FILETIME ftLastWriteTime;  
DWORD nFileSizeHigh;  
DWORD nFileSizeLow;  
DWORD dwReserved0;  
DWORD dwReserved1;  
TCHAR cFileName[MAX_PATH];  
TCHAR cAlternateFileName[14];
} WIN32_FIND_DATA, 
*/

namespace SOL {

class FileFindData :public Object {
private:
  WIN32_FIND_DATA data;
  
private:
  bool toString(SYSTEMTIME& time, String& dateTime) 
  {
    TCHAR buffer[128];
    _stprintf_s(buffer, CountOf(buffer), _T("%.4u/%.2u/%.2u %.2u:%.2u"), 
          time.wYear, time.wMonth, time.wDay,
              time.wHour, time.wMinute);
    dateTime = buffer;
    return true;
  }

public:
  /**
   *
   */
  FileFindData(WIN32_FIND_DATA& fdata) {
    memcpy(&data, &fdata, sizeof(fdata));
  }    

public:
  /**
   *
   */
  FileFindData(const TCHAR* filePath) {
    memset(&data, 0, sizeof(WIN32_FIND_DATA));
    //data.dwFileAttributes  = FILE_ATTRIBUTE_NORMAL;

    HANDLE hf = ::FindFirstFile(filePath, &data);

    if (hf != INVALID_HANDLE_VALUE) {
      FindClose(hf);
    } else {
      throw Exception(GetLastError(),
        _T("FileFindData#FileFindData,1,Failed,filePath=\"%s\""), filePath);
    }
  }    

public:
  /**
   * Get LocalSystemTime of CreationTime
   */
  //LocalFileTime->SystemTime
  void getCreationTime(SYSTEMTIME& time) {
    FILETIME ltime;
    ::FileTimeToLocalFileTime(&(data.ftCreationTime), &ltime);
    ::FileTimeToSystemTime(&ltime, &time);
  }

public:
  void getCreationTime(String& dateTime) {  
    SYSTEMTIME time;
    getCreationTime(time);
    toString(time, dateTime);
  }

public:
  /**
   * Get LocalSystemTime of LastAccessTime
   */
  //LocalFileTime->SystemTime

  void getLastAccessTime(SYSTEMTIME& time) {
    FILETIME ltime;
    ::FileTimeToLocalFileTime(&(data.ftLastAccessTime), &ltime);
    ::FileTimeToSystemTime(&ltime, &time);
  }

public:
  void getLastAccessTime(String& dateTime) {
    SYSTEMTIME time;
    getLastAccessTime(time);
    toString(time, dateTime);
  }

public:
  /**
   * Get LocalSystemTime of LastWriteTime
   */
  //LocalFileTime->SystemTime

  void getLastWriteTime(SYSTEMTIME& time) {
    FILETIME ltime;
    ::FileTimeToLocalFileTime(&(data.ftLastWriteTime), &ltime);
    ::FileTimeToSystemTime(&ltime, &time);
  }

public:
  void getLastWriteTime(String& dateTime) {
    SYSTEMTIME time;
    getLastWriteTime(time);
    toString(time, dateTime);
  }


public:
  DWORD getFileAttributes() {
    return data.dwFileAttributes;
  }

public:
  //2015/12/12
  ULONGLONG  getFileSize() {   
    ULARGE_INTEGER size;
    size.HighPart = data.nFileSizeHigh;
    size.LowPart  = data.nFileSizeLow;
    return size.QuadPart;
  }
  
  //2015/12/12
  void getFileSize(StringT<char>& string)
  {
    ULONGLONG size = getFileSize();
    char buff[20];
    sprintf_s(buff, CountOf(buff), "%I64d", size);
    string = buff;
  }
  
public:
  void getFileName(String& name) {
    name = (const TCHAR*)data.cFileName;
  }

public:
  void getAlternateFileName(String& name) {
    name = (const TCHAR*)data.cAlternateFileName;
  }
public:
  bool isDirectory() {
    bool rc = false;
    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      rc = true;
    }
    return rc;
  }
};

}
