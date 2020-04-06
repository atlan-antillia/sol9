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
 *  Path.h
 *
 *****************************************************************************/

// 2012/05/02

#pragma once

#include <sol\Object.h>
#include <Shlwapi.h>
#include <sol/String.h>

#pragma comment(lib, "Shlwapi.lib")


namespace SOL {

class Path :public Object {
private:
  String path;

public:
  Path(const TCHAR* name)
  :path(name)
  {
    if (name == NULL) {
      throw Exception(0, _T("Exception: Name parameter is NULL."));
    }
  }

public:
  // Get the full path name for a file. The file does not need to exist.   
  String getFullPathName()
  {
    TCHAR  buffer[4096]; 
     TCHAR* pPart = NULL;

    if (GetFullPathName((const TCHAR*)path, CountOf(buffer), buffer, &pPart)) {
      return String(buffer); 
    } else {
      throw Exception(0, _T("Exception: Failed to get a fullpath for '%s'"), (const TCHAR*)path);
    }
  }

public:
  String canonicalize()
  {
    TCHAR inFolder[MAX_PATH];
    if (PathCanonicalize(inFolder, (const TCHAR*)path) ) {
      return String(inFolder);

    } else {
      throw Exception(0, _T("Invalid name: '%s' wasn't canonicalized."), (const TCHAR*)path);
    }
  }

public:
  // Confirm whether the file of 'path' exists. 
  BOOL exists()
  {
    return PathFileExists((const TCHAR*)path);
  }

public:
  // Confirm that a file of 'name' exists and is directory. The file name need to end with '\\'. 
  BOOL isDirectory()
  {
    BOOL rc = FALSE;
    const TCHAR* name = (const TCHAR*)path;


    if (!PathIsDirectory(name) ) {
      throw Exception(0, _T("Invalid folderName: '%s' isn't directory,"), name);
    }

    String folder = name;
    if (!folder.endsWith(_T("\\")) ) {
      throw Exception(0, _T("Invalid folderName: '%s' doesn't end with '\\'"), name);
    }

    return (rc = TRUE);
  }

public:
  BOOL isDirectoryEmpty()
  {
    return PathIsDirectoryEmpty((const TCHAR*)path);
  }

  BOOL isHTMLFile()
  {
    return PathIsHTMLFile((const TCHAR*)path);
  }
};


}
