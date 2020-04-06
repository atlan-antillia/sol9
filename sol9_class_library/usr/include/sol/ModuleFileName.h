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
 *  ModuleFileName.h
 *
 *****************************************************************************/
//2017/01/27 Modified to use _tmemset instead of memset.

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

namespace SOL {

class ModuleFileName :public Object {

private:
  TCHAR path[_MAX_PATH];
  TCHAR drive[_MAX_DRIVE];
  TCHAR dir[_MAX_DIR];
  TCHAR fileName[_MAX_FNAME];
  TCHAR ext[_MAX_EXT];
  TCHAR appName[_MAX_FNAME];
public:
  //2017/01/27
  ModuleFileName(const TCHAR* fullpath)
  {
    _tmemset(path,     (TCHAR)0, CountOf(path)); 
    _tmemset(drive,    (TCHAR)0, CountOf(drive));
    _tmemset(dir,      (TCHAR)0, CountOf(dir));
    _tmemset(fileName, (TCHAR)0, CountOf(fileName));
    _tmemset(ext,      (TCHAR)0, CountOf(ext));
    _tmemset(appName,  (TCHAR)0, CountOf(appName));

    if (fullpath == nullptr) {
      throw IException("Invalid parameter");
    }
    if (_tcslen(fullpath) >(MAX_PATH-1)) {
      throw IException("Invalid parameter");
    }

    _tcscpy_s(path, CountOf(path), fullpath);
    
    errno_t err = _tsplitpath_s(path,
                 drive, CountOf(drive),
                 dir,   CountOf(dir),
                 fileName,CountOf(fileName),
                  ext, CountOf(ext)); 
    if (err != NO_ERROR) {
      throw IException("Failed to _tsplitpath_s"); 
    }
    _stprintf_s(appName, CountOf(appName), _T("%s%s"), fileName, ext);
  }

public:
  ModuleFileName(HMODULE hModule = NULL)
  {
    _tmemset(path,    (TCHAR)0, CountOf(path));
    _tmemset(drive,   (TCHAR)0, CountOf(drive));
    _tmemset(dir,     (TCHAR)0, CountOf(dir));
    _tmemset(fileName,(TCHAR)0, CountOf(fileName));
    _tmemset(ext,     (TCHAR)0, CountOf(ext));
    _tmemset(appName, (TCHAR)0, CountOf(appName));
	
    DWORD rc = GetModuleFileName(hModule, path, CountOf(path));
    if(rc == 0) {
      throw IException("Failed to GetModuleFileName");
    }
    errno_t err = _tsplitpath_s(path,
                 drive, CountOf(drive),
                 dir,   CountOf(dir),
                 fileName,CountOf(fileName),
                  ext, CountOf(ext)); 
    if (err != NO_ERROR) {
      throw IException("Failed to _tsplitpath_s"); 
    }
    _stprintf_s(appName, CountOf(appName), _T("%s%s"), fileName, ext);
  }

public:
  const TCHAR* getDrive() const
  {
    return drive;
  }
  
  const TCHAR* getDir() const
  {
    return dir;
  }

  const TCHAR* getDirectory() const
  {
    return dir;
  }

  const TCHAR* getFileName() const
  {
    return fileName;
  }

  const TCHAR* getAppName() const
  {
    return appName;
  }

  const TCHAR* getExt() const 
  {
    return ext;
  }
};

}

