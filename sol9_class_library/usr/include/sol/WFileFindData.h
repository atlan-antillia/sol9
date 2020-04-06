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
 *  WFileFindData.h
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

class WFileFindData :public Object {
private:
  WIN32_FIND_DATAW data;
  
private:
  WString toString(SYSTEMTIME& time) 
  {
    wchar_t buffer[128];
    swprintf(buffer, CountOf(buffer), L"%.4u/%.2u/%.2u %.2u:%.2u", 
          time.wYear, time.wMonth, time.wDay,
              time.wHour, time.wMinute);
    return WString(buffer);
  }

public:
  /**
   *
   */
  WFileFindData(WIN32_FIND_DATAW& fdata) {
    memcpy(&data, &fdata, sizeof(fdata));
  }    

public:
  /**
   *
   */
  WFileFindData(const wchar_t* filePath) {
    memset(&data, 0, sizeof(WIN32_FIND_DATA));
    //data.dwFileAttributes  = FILE_ATTRIBUTE_NORMAL;

    HANDLE hf = ::FindFirstFileW(filePath, &data);

    if (hf != INVALID_HANDLE_VALUE) {
      FindClose(hf);
    } else {
      throw Exception(GetLastError(),
        L"FileFindData#FileFindData,1,Failed,filePath=\"%s\"", filePath);
    }
  }    

public:
  /**
   * Get LocalSystemTime of CreationTime
   */
  //LocalFileTime->SystemTime
  SYSTEMTIME getCreationTime() 
  {
    SYSTEMTIME time;
    FILETIME ltime;
    ::FileTimeToLocalFileTime(&(data.ftCreationTime), &ltime);
    ::FileTimeToSystemTime(&ltime, &time);
    return time;
  }

public:
  WString creationTimeToString() 
  {  
    SYSTEMTIME time = getCreationTime();
    return toString(time);
  }

public:
  /**
   * Get LocalSystemTime of LastAccessTime
   */
  //LocalFileTime->SystemTime

  SYSTEMTIME getLastAccessTime() 
  {
    SYSTEMTIME time;
    FILETIME ltime;

    ::FileTimeToLocalFileTime(&(data.ftLastAccessTime), &ltime);
    ::FileTimeToSystemTime(&ltime, &time);
    return time;
  }

public:
  WString lastAccessTimeToString() 
  {
    SYSTEMTIME time = getLastAccessTime();
    return toString(time);
  }

public:
  /**
   * Get LocalSystemTime of LastWriteTime
   */
  //LocalFileTime->SystemTime

  SYSTEMTIME getLastWriteTime() 
  {
    SYSTEMTIME time;
    FILETIME ltime;
    ::FileTimeToLocalFileTime(&(data.ftLastWriteTime), &ltime);
    ::FileTimeToSystemTime(&ltime, &time);
    return time;
  }

public:
  WString lastWriteTimeToString() 
  {
    SYSTEMTIME time = getLastWriteTime();
    return toString(time);
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
  DWORD getFileSizeLow() {
    return (DWORD)data.nFileSizeLow;
  }

public:
  //2012/12/07
  void getFileName(WString& name) {
    name = data.cFileName;
  }

public:
  //2012/12/07
  _bstr_t getFileName() {
    return _bstr_t(data.cFileName);
  }

public:
  //2012/12/07
  void getAlternateFileName(WString& name) 
  {
    name = data.cAlternateFileName;
  }

public:
  //2012/12/07
  _bstr_t getAlternateFileName() 
  {
    return _bstr_t(data.cAlternateFileName);
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
