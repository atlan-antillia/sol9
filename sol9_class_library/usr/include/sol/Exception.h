/******************************************************************************
 *
 * Copyright (c) 1999-2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Exception.h
 *
 *****************************************************************************/

// SOL9
//2016/12/06 Updated

//2017/01/23 Added WException, TException, caught macros and new display methpds.

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <windows.h>
#include <tchar.h>

namespace SOL {

class Exception {
protected:
  char*   message;
  int     errorCode;
  HRESULT hresult;
  static const int MAX_MESSAGE = 1024*2;

public:
  Exception(int error=0)
  :message(NULL),
  errorCode(error),
  hresult((HRESULT)0)
  {
    this ->message = new char[MAX_MESSAGE];
    memset(this->message, 0, MAX_MESSAGE);
  }

public:
  Exception(const char* msg, int error=0)
  :message(NULL),
  errorCode(error),
  hresult((HRESULT)0)
  {     
    if (msg) {
      size_t slen = strlen(msg) +1;
      this->message = new char[slen];
      strcpy_s(this->message, slen, msg);
    }  
  }

public:
  Exception(const wchar_t* msg, int error=0)
  :message(NULL),
  errorCode(error),
  hresult((HRESULT)0)
  { 
    if (msg) {
      this->message = toMBString(msg);
    }  
  }


public:
  Exception(int error, const char* format,...)
  :message(NULL),
  errorCode(error),
  hresult((HRESULT)0)
  {
    this ->message = new char[MAX_MESSAGE];
    memset(this->message, 0, MAX_MESSAGE);
    
    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(this->message, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
    //this->message[MAX_MESSAGE-1] = NULL;
  }

public:
  Exception(DWORD error, const char* format,...)
  :message(NULL),
  errorCode(error),
  hresult((HRESULT)0)
  {
    this ->message = new char[MAX_MESSAGE];
    memset(this->message, 0, MAX_MESSAGE);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(this->message, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
  }

public:
  Exception(int error, const wchar_t* format,...)
  :message(NULL),
  errorCode(error),
  hresult((HRESULT)0)
  {
    wchar_t wmessage[MAX_MESSAGE];
    memset(wmessage, (wchar_t)0, MAX_MESSAGE);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(wmessage, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
    this->message = toMBString(wmessage);
  }

public:
  Exception(DWORD error, const wchar_t* format,...)
    :message(NULL),
    errorCode(error),
    hresult((HRESULT)0)
  {
    wchar_t wmessage[MAX_MESSAGE];
    memset(wmessage, (wchar_t)0, MAX_MESSAGE);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(wmessage, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
    this->message = toMBString(wmessage);
  }

public:
  Exception(HRESULT herror, const wchar_t* format,...)
    :message(NULL),
    errorCode(0),
    hresult(herror)
  {
    wchar_t wmessage[MAX_MESSAGE];
    memset(wmessage, (wchar_t)0, MAX_MESSAGE);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(wmessage, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
    this->message = toMBString(wmessage);
  }

public:
  char* toMBString(const wchar_t* wcstring) 
  {
    char* mbstring = NULL;

    if (wcstring == NULL) {
      return mbstring;
    }
    
    int cb = WideCharToMultiByte(CP_ACP, 0, wcstring, -1, NULL, 0, NULL, NULL);
    
    if (cb > 0) {
      mbstring = new char[cb];
      mbstring[0] = ZERO;
      WideCharToMultiByte(CP_ACP, 0, wcstring, -1, mbstring, cb, NULL, NULL);
    }
    return mbstring;
  }

public:
  Exception(HRESULT hr, const char* format,...)
    :message(NULL),
    errorCode(0),
    hresult(hr)
  {
    this ->message = new char[MAX_MESSAGE];
    memset(this->message, 0, MAX_MESSAGE);
    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(this->message, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
  }

public:
  ~Exception() { 
    if (message) {
      delete [] message;
      message = NULL;
    }
  }
  
protected:
  //2008/07/11
  void formatMessage(const char* format, va_list pos)
  {
    if (this->message) {
      delete[] this->message;
    }
    this->message = new char[MAX_MESSAGE];
    memset(this->message, 0, MAX_MESSAGE);
    _vsnprintf_s(this->message, MAX_MESSAGE, _TRUNCATE, format, pos);
  }


public:
  const char* getString() 
  {
    return (const char*)message; 
  }

public:
  const char* getErrorMessage() 
  {
    return (const char*)message; 
  }
  
protected:
  void setErrorMessage(const wchar_t* wmessage) 
  {
    if (wmessage) {
      if (this->message) {
        delete [] this->message;
      }
      this -> message = toMBString(wmessage);
    } 
  }

protected:
  void setErrorMessage(const char* msg) 
  {
    if (msg) {
      if (this->message) {
        delete [] this->message;
      }
      size_t slen = strlen(msg) +1;
      this->message = new char[slen];
      strcpy_s(this->message, slen, msg);
    }; 
  }

public:
  int    getErrorCode() 
  { 
    return errorCode; 
  }

public:
  HRESULT    getHRESULT() 
  { 
    return hresult; 
  }

public:
  void   setErrorCode(int err) 
  { 
    errorCode = err; 
  }

protected:
  void setHRESULT(HRESULT hr)
  {
    this->hresult = hr;
  }

public:
  virtual void  printf() 
  {
    ::printf("Exception{\nMessage:%s\nErrorNo:0x%08X\nHRESULT:0x%08X\n}\n", 
        (const char*)message, 
        errorCode,
        hresult);
  }

  virtual void  display() 
  {
  //2015/09/25
#ifdef WIN32 
    MessageBoxA(NULL, (const char*)message, "Exception", MB_OK|MB_ICONERROR);

#else
    ::printf("Exception: %s\n", (const char*)message);
#endif
  }

//2017/01/23
  virtual void  display(const char* filename, int line, const char* function ) 
  {
    char text[MAX_MESSAGE];
    _snprintf_s(text, sizeof(text), _TRUNCATE,  "Caught at %s(%d) %s \r\n\r\nThrowed at %s",
        filename, line,  function, (const char*)message);
#ifdef WIN32 
    MessageBoxA(NULL, text, "Exception", MB_OK|MB_ICONERROR);
#else
    ::printf("Exception: %s\n", (const char*)text);
#endif
  }

//2017/01/23
  virtual void  display(const wchar_t* wfilename, int line, const wchar_t* wfunction ) 
  {
    char text[MAX_MESSAGE];
    const char* filename = toMBString(wfilename);
    const char* function = toMBString(wfunction);
    _snprintf_s(text, sizeof(text), _TRUNCATE, "Caught at %s(%d) %s \r\n\r\nThrowed at %s",
      filename, line,  function, (const char*)message);
#ifdef WIN32 
    MessageBoxA(NULL, text, "Exception", MB_OK|MB_ICONERROR);
#else
    ::printf("Exception: %s\n", (const char*)text);
#endif
    delete [] filename;
    delete [] function;
  }

  virtual void  show() 
  {
    display();
  }

public:
  //2011/01/30 Added virtual
  virtual void  dump() 
  {
    ::printf("Exception{\nMessage:%s\nErrorNo:0x%08X\nHRESULT:0x%08X\n}\n", 
        (const char*)message, 
        errorCode,
        hresult);
  }
};

//2016/01/13 Inline Exception 
#define IException(format, ...) Exception(0, "%s (%d) %s: " format, __FILE__, __LINE__,   __FUNCTION__ , __VA_ARGS__);

//2017/01/24   
#define WException(format, ...) Exception(0, L"%s (%d) %s: " format, __FILEW__, __LINE__,   __FUNCTIONW__ , __VA_ARGS__);

#ifdef UNICODE
#define TException(format, ...) Exception(0, L"%s (%d) %s: " format, __FILEW__, __LINE__,   __FUNCTIONW__ , __VA_ARGS__);
#else 
#define TException(format, ...) Exception(0, "%s (%d) %s: " format, __FILE__, __LINE__,   __FUNCTION__ , __VA_ARGS__);
#endif
  
#ifdef UNICODE
#define caught(ex) ex.display(__FILEW__, __LINE__,  __FUNCTIONW__);
#else
#define caught(ex) ex.display(__FILE__, __LINE__,  __FUNCTION__);  
#endif

}

