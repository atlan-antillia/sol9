/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WCharModuleFileName.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

namespace SOL {

class WCharModuleFileName :public Object {

private:
  wchar_t path[_MAX_PATH];
  wchar_t drive[_MAX_DRIVE];
  wchar_t dir[_MAX_DIR];
  wchar_t fileName[_MAX_FNAME];
  wchar_t ext[_MAX_EXT];

public:
  WCharModuleFileName(HMODULE hModule = NULL)
  {
    memset(path, (wchar_t)0, CountOf(path)); 
    memset(drive,(wchar_t)0, CountOf(drive));
    memset(dir,  (wchar_t)0, CountOf(dir));
    memset(ext,  (wchar_t)0, CountOf(ext));
	
    DWORD rc = GetModuleFileNameW(hModule, path, CountOf(path));
    if(rc == 0) {
      throw IException("Failed to GetModuleFileName");
    }
    errno_t err = _wsplitpath_s(path,
                 drive, CountOf(drive),
                 dir,   CountOf(dir),
                 fileName,CountOf(fileName),
                  ext, CountOf(ext)); 
    if (err != NO_ERROR) {
      throw IException("Failed to _tsplitpath_s"); 
    }
  }
  
public:
  const wchar_t* getDrive() const
  {
    return drive;
  }
  
  const wchar_t* getDir() const
  {
    return dir;
  }
  
  const wchar_t* getFileName() const
  {
    return fileName;
  }

  const wchar_t* getExt() const 
  {
    return ext;
  }
};

}

