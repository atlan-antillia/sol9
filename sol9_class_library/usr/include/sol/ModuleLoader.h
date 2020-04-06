/******************************************************************************
 *
 * Copyright (c) 1999-2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ModuleLoder.h
 *
 *****************************************************************************/

// SOL9


#pragma once

#include <sol/Object.h>
#include <sol/String.h>

namespace SOL {

class ModuleLoader :public Object {

private:
  HMODULE hModule;

public:
  ModuleLoader()
  :hModule(NULL)
  {

  }

public:
  ~ModuleLoader()
  {
    clear();
  }


public:

  bool load(__in const char* argv,
    __in DWORD dwFlags=LOAD_LIBRARY_AS_DATAFILE|LOAD_WITH_ALTERED_SEARCH_PATH)
  {  
    bool rc = false;
    clear();
  
    if ((hModule = LoadLibraryExA(argv, NULL, dwFlags) )) { //2012/06/23
      rc = true;
    } else {
      rc = false;
    }
    return rc;
  }

public:

  bool load(__in const wchar_t* argv, 
    __in DWORD dwFlags=LOAD_LIBRARY_AS_DATAFILE|LOAD_WITH_ALTERED_SEARCH_PATH)
  {  
    bool rc = false;
    clear();
  
    if ((hModule = LoadLibraryExW(argv, NULL, dwFlags) )) {
      rc = true;
    } else {
      rc = false;
    }
    return rc;
  }

public:
  //2012/12/07
  HMODULE load(__in const wchar_t* argv, 
    __in DWORD dwFlags=LOAD_LIBRARY_AS_DATAFILE|LOAD_WITH_ALTERED_SEARCH_PATH)
  {  
    HMODULE hM = NULL;

    bool rc = false;
    clear();
  
    if ((hM = LoadLibraryExW(argv, NULL, dwFlags) )) {
      rc = true;
    } else {
      throw -1;
    }
    return hM;
  }

public:
  void clear()
  {
    if (hModule) {
      FreeLibrary(hModule);
      hModule = NULL;
    }    
  }

public:
  HMODULE getHModule() {
    return hModule;
  }
};

}


