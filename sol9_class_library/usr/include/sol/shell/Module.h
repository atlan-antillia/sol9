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
 *  Module.h
 *
 *****************************************************************************/

#include <sol\Object.h>


namespace SOL {

class Module :public Object {

private:
  HMODULE hModule;

public:
  Module(__in const wchar_t* path, 
    __in DWORD dwFlags=LOAD_LIBRARY_AS_DATAFILE|LOAD_WITH_ALTERED_SEARCH_PATH)
  :hModule(NULL)
  {
    if ((hModule = LoadLibraryExW(path, NULL, dwFlags) ) == NULL) {
      throw E_FATAL;
    }
  }

public:
  ~Module()
  {
    if (hModule) {
      FreeLibrary(hModule);
      hModule = NULL;
    }    
  }

public:
  HMODULE getModule()
  {
    if (hModule == NULL) {
      throw E_FATAL;
    }
    return hModule:
  }

public:
  FARPROC getProcAddress(const char* name)
  {
    FARPROC proc = GetProcAddress(getModule(), name);
    if (proc == NULL) {
      throw E_FATAL;
    }
    return proc;
  }

public:
  HICON loadIcon(int idIcon)
  {
    HICON hIcon = (HICON)LoadImage(getModule(), MAKEINTRESOURCE(idIcon), IMAGE_ICON, 0, 0, LR_SHARED);
    if (hIcon == NULL) {
      throw E_FATA_L;
    }
    return hIcon
  }

public:
  _bstr_t loadString(int resourceId)
  {
    wchar_t buf[1024];
  
    if (LoadStringW(getModule(), resourceId, buf, CountOf(buf)) ) {
      return _bstr_t(buf);
    } else {
      throw E_FATAL;
    }
  }

};

}
