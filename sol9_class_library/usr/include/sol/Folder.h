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
 *  Folder.h
 *
 *****************************************************************************/

// SOL9
//
//  Folder.h
// FilePath splitter and directory(folder) creator
// 2008/09/29 Fixed bugs in splitPath method and exists method.
// 2012/04/28 sizeof -> CountOf

#pragma once

#include <sol\Object.h>
#include <sol\Exception.h>
#include <sol/String.h>
#include <sol/WString.h>

#include <sol/StringT.h>
#include <sol\StringConverter.h>


/** 
 */
namespace SOL {

class Folder :public Object {

private:

  wchar_t directory[_MAX_PATH];

  wchar_t fileName[_MAX_PATH];

  /** fileName only without dotExtension */
  wchar_t name[_MAX_PATH];
  
  wchar_t extension[_MAX_PATH];

public:
  /**
   * Split filePath into directory and filename.
   * @param filePath  This takes a file path string like:"c:\work\doc\some.txt"
   */
  Folder(const char* filePath)
  {
    StringConverter converter;
    wchar_t* wfilePath = converter.toWideChar(filePath);

    directory[0] = ZERO;
    fileName [0] = ZERO;
    name[0]     = ZERO;
    extension[0] = ZERO;

    bool rc = splitPath(wfilePath);

    delete [] wfilePath;

    if (rc ==false) {
      throw (int)E_FAIL;
    }
  }

public:
  /**
   * Split filePath into directory and filename.
   * @param filePath  This takes a file path string like:"c:\work\doc\some.txt"
   */
  Folder(const wchar_t* filePath)
  {
    directory[0] = ZERO;
    fileName [0] = ZERO;
    name[0]     = ZERO;
    extension[0] = ZERO;
    
    wchar_t wfilePath[_MAX_PATH];
    wcscpy_s(wfilePath, CountOf(wfilePath), filePath);
    int rc = splitPath(wfilePath);

    if (rc == false) {
      printf("Failed to split\n");
      throw (int)E_FAIL;
    }
  }

public:
  void display()
  {
    wprintf(L"Direcotry=%s, fileName=%s, name=%s, extension=%s\n",
    directory,
    fileName,
    name,
    extension);

  }

public:
  /**
   */
  bool splitPath(wchar_t* path) {
    bool rc = false;
  
    wchar_t* delim = wcsrchr(path, (wchar_t)'\\');
    if (delim) {
      *delim = ZERO;  //
      ++delim;

      wcscpy_s(this->directory, CountOf(this->directory), path); //2012/06/21
      wcscpy_s(this->fileName, CountOf(this->fileName), delim); //2012/06/21

      wchar_t* dot = wcsrchr(delim, (wchar_t)'.');
      if (dot) {
        *dot = ZERO;
    
        dot++;
        wcscpy_s(this->extension, CountOf(this->extension), dot);
      }
      //2012/04/28 sizeof -> CountOf
      wcscpy_s(this->name, CountOf(this->name), delim);

      rc = true;
    } else {
      //<added date="2008/09/29">
      //2012/04/28 sizeof -> CountOf
      wcscpy_s(this->fileName, CountOf(this->fileName), path);

      wchar_t* dot = wcsrchr(path, (wchar_t)'.');
      if (dot) {
        *dot = ZERO;
        dot++;
        wcscpy_s(this->extension, CountOf(this->extension), dot);

      }
      wcscpy_s(this->name, CountOf(this->name), path);
      //</added>
      rc = true;
      
    }
    return rc;
  }


public:  
  /**
   */
  bool  createFolder(SECURITY_ATTRIBUTES* attr=NULL) {
    bool rc = false;

    if (directory[0] == (wchar_t)'\0' || 
      wcscmp(directory, L".") == 0 ||
          wcscmp(directory, L"..") == 0) {
      return rc;
    }
    
    if (GetFileAttributesW(directory) != 0xffffffff) {
      //printf("Folder#make,1,already exists %s\n", directory);
      return true;
    }

    wchar_t dir[_MAX_PATH];
    wcscpy_s(dir, CountOf(dir), directory); //2012/06/21

    wchar_t* ptr = dir;
    
    while(ptr) {
      //Find delimiter '\\' from the beginning of the dir.
      ptr = wcschr(ptr, (wchar_t)'\\');
      if(ptr) { 
        *ptr = (wchar_t)'\0';
        if (GetFileAttributesW(dir) == 0xffffffff) {
          if (CreateDirectoryW(dir, attr)) {
            //printf("Folder#make,2, created a directory%s\n", dir);

            rc = true;
          } else {
            //printf("Folder#make,3,Failed to create a directory%s\n", dir);
            rc = false;
            break;
          }
        }
        *ptr = '\\';

      } else {
        if (GetFileAttributesW(dir) == 0xffffffff) {
          if (CreateDirectoryW(dir, attr)) {
            //printf("Folder#make,4,Created a directory %s\n", dir);
            rc = true;
          } else {
            //printf("Folder#make,5, Failed to create a directory3 %s\n", dir);
            rc = false;
          }
        } else {
          rc = true;
        }
        break;
      }
      ptr++;
    }

    return rc;
  }
  

public:  
  /**
   */
  bool exists() {
    bool rc = true;
    //2008/09/29: Added wcslen(direcotry)>0 
    if (wcslen(directory)>0 && GetFileAttributesW(directory) == 0xFFFFFFFF) {
      rc = false;  
    } 
    return rc;

  }

public:
  wchar_t* getDirectory()
  {
    return this->directory;
  }

public:
  wchar_t* getFileName()
  {
    return this->fileName;
  }


public:
  wchar_t* getExtension()
  {
    return this->extension;
  }

public:
  void  getDirectory(String& dir) {
#ifdef UNICODE
    dir = this->directory;
#else
    StringConverter converter;
    char* mbstring = converter.toMultiByte(this->directory);
    dir.shallowCopy(mbstring);
#endif
  }

public:
  void  getFileName(String& fname) {
#ifdef UNICODE
    fname = this->fileName;
#else
    StringConverter converter;
    char* mbstring = converter.toMultiByte(this->fileName);
    fname.shallowCopy(mbstring);
#endif

  }  

public:
  /**
   * Return file name only without extension
   */
  void getName(String& string) {
#ifdef UNICODE
    string = this -> name;
#else
    StringConverter converter;
    char* mbstring = converter.toMultiByte(this->name);
    string.shallowCopy(mbstring);
#endif

  }
};

}

