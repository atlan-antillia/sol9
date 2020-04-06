/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ComException.h
 *
 *****************************************************************************/

// 2017/01/29

#pragma once
#include <sol/Exception.h>

namespace SOL {

class ComException :public Exception {
public:
  ComException(HRESULT hr)
  :Exception((int)0)
  {
    setHRESULT(hr);
    _com_error err(hr);
#ifdef UNICODE
    const wchar_t*  errMessage = err.ErrorMessage();
    const char* msg = toMBString(errMessage);
    setErrorMessage(msg);
#else
    const char*  errMessage = err.ErrorMessage();
    setErrorMessage(errMessage);
#endif
    
  }
  
public:
  ComException(HRESULT hr,  const wchar_t* format,...)
  :Exception((int)0)
  {
    setHRESULT(hr);
    wchar_t wmessage[MAX_MESSAGE];
    memset(wmessage, (wchar_t)0, MAX_MESSAGE);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(wmessage, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
    
    const char* msg = toMBString(wmessage);
    setErrorMessage(msg);
  }

public:
  ComException(HRESULT hr,  const char* format,...)
  :Exception((int)0)
  {
    setHRESULT(hr);

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(this->message, MAX_MESSAGE, _TRUNCATE, format, pos);
    va_end(pos);
  }

//2017/01/23
  virtual void  display(const char* filename, int line, const char* function ) 
  {
    char text[MAX_MESSAGE];
    _snprintf_s(text, sizeof(text), _TRUNCATE, "Caught at %s(%d) %s \r\n\r\n HRESULT(0x%llx) %s",
        filename, line,  function, 
      getHRESULT(), getErrorMessage());
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
    _snprintf_s(text, sizeof(text), _TRUNCATE, "Caught at %s(%d) %s \r\n\r\n HRESULT(0x%llx) %s",
      filename, line,  function, 
      getHRESULT(), getErrorMessage() );
#ifdef WIN32 
    MessageBoxA(NULL, text, "Exception", MB_OK|MB_ICONERROR);
#else
    ::printf("Exception: %s\n", (const char*)text);
#endif
    delete [] filename;
    delete [] function;
  }
};
  
}

