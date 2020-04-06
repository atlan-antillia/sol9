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
 *  Directory.h
 *
 *****************************************************************************/

// SOL++2000
// 2008/07/10 Modified make method to use wchar_t.

#pragma once

#include <sol\Object.h>
#include <sol\String.h>
#include <sol\StringConverter.h>

#include <io.h>
#include <direct.h>


namespace SOL {

class Directory :public Object {

public:
  Directory() { }

public:
  BOOL  changeDir(const TCHAR* name) {
    return ::SetCurrentDirectory(name);
  }

public:
  DWORD  getCwd(String& dir) {
    TCHAR buff[_MAX_PATH];
    DWORD rc =::GetCurrentDirectory(CountOf(buff), buff);
    dir = buff;
    return rc;
  }

public:
  BOOL  make(const TCHAR* name, SECURITY_ATTRIBUTES* attr=NULL) {
    BOOL rc = FALSE;

    if (name == NULL) {
      return rc;
    }

    if (name[0] == '\0' || 
      strcmp(name, _T(".")) == 0 ||
        strcmp(name, _T("..")) == 0) {
      return rc;
    }
    if (GetFileAttributes(name) != 0xffffffff) {
      //Already exists
      return rc;
    }

    StringConverter converter;
    wchar_t* dir = converter.toWideChar(name);
    wchar_t* ptr = dir;
    
    const wchar_t DELIM = '\\';

    while(ptr) {
      //Find the DELIM
      ptr = wcschr(ptr, DELIM);
      if(ptr) { 
        //NULL-terminate
        *ptr = ZERO;
        if (GetFileAttributesW(dir) == 0xffffffff) {
          //If dir doesn't exist, create it
          rc = CreateDirectoryW(dir, attr);
          if (rc == FALSE) {
            //If failed, break this loop
            break;
          }
        }  
        *ptr = DELIM;

      } else {
        // Not found DELIM
        if (GetFileAttributesW(dir) == 0xffffffff) {
          // If dir doesn't exist, create it 
          rc = CreateDirectoryW(dir, attr);
        } else {
          rc = TRUE;
        }
        break;
      }
      ptr++;
    }

    delete [] dir;

    return rc;
  }

public:
  virtual int remove(const TCHAR* name) {
    return ::RemoveDirectory(name);
  }

public:
  BOOL  exists(const TCHAR* dir) {
    BOOL rc = FALSE;
  
    if (dir != NULL && GetFileAttributes(dir) != 0xffffffff) {
      rc = TRUE;
    }
    return rc;
  }
};

}



