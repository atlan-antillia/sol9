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
 *  WFileFinder.h
 *
 *****************************************************************************/

// SOL9 2.0
// 2012/12/07

#pragma once

#include <sol\Object.h>
#include <sol\WString.h>
#include <sol\WFileFindData.h>

typedef WIN32_FIND_DATAW WFindData;

namespace SOL {

class WFileFinder :public Object{
private:
  HANDLE hf;
  WString  name;

public:
  WFileFinder(const wchar_t* dir)
  :name(dir)
  {
    hf   = INVALID_HANDLE_VALUE;
  }

public:
  ~WFileFinder() 
  {
    if (hf != INVALID_HANDLE_VALUE) {
      ::FindClose(hf);  
    }
  }
  
public:
  BOOL getFirst(__out WIN32_FIND_DATAW& fdata) 
  {
    BOOL rc = FALSE;

    if (hf != INVALID_HANDLE_VALUE) {
      ::FindClose(hf);
    }

    memset(&fdata, 0, sizeof(fdata));

    hf = ::FindFirstFileW((const wchar_t*)name, &fdata);
    if (hf != INVALID_HANDLE_VALUE) {
      rc = TRUE;
    }
    return rc;
  }

public:
  WFileFindData getFirst() 
  {
    WIN32_FIND_DATAW fdata;

    if (hf != INVALID_HANDLE_VALUE) {
      ::FindClose(hf);
    }

    memset(&fdata, 0, sizeof(fdata));

    hf = ::FindFirstFileW((const wchar_t*)name, &fdata);
    if (hf == INVALID_HANDLE_VALUE) {
      throw -1;
    } else {
      return WFileFindData(fdata);
    }
  }

public:
  BOOL getNext(__out WIN32_FIND_DATAW& fdata) 
  {
    BOOL rc = FALSE;
    if (hf == INVALID_HANDLE_VALUE) {
      return rc;
    }
    memset(&fdata, 0, sizeof(fdata));

    rc = ::FindNextFileW(hf, &fdata);
    if (rc == FALSE) {
      ::FindClose(hf);
      hf = INVALID_HANDLE_VALUE;
    }
    return rc;
  }


public:
  WFileFindData getNext() 
  {
    WIN32_FIND_DATAW fdata;

    if (hf == INVALID_HANDLE_VALUE) {
      throw -1;
    }
    memset(&fdata, 0, sizeof(fdata));

    BOOL rc = ::FindNextFileW(hf, &fdata);
    if (rc == FALSE) {
      ::FindClose(hf);
      throw -1;
    }
    return WFileFindData(fdata);
  }

};

}


