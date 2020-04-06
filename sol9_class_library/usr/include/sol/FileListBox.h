/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileListBox.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol\String.h>
#include <sol\ListBox.h>
#include <sol\Directory.h>


namespace SOL {

class FileListBox :public ListBox {
private:

  String  directory;
  String  fileSpec;

  long  attribute;


public:
  FileListBox(): ListBox() { }

public:
  //2012/06/22
  FileListBox(View* parent, const TCHAR* label, Args& args)
  :ListBox()
  {
    create(parent, label, args);
  }

public:
  ~FileListBox()
  {
  }


public:
  virtual Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    Boolean rc = ListBox::create(parent, label, 
      args.set(XmNstyle, (LONG_PTR)LBS_STANDARD));

    // Setting default values.
    Directory dir;
    dir.getCwd(directory);//, _MAX_PATH);
    //strcpy_s(fileSpec, _MAX_FNAME, "*.*");
    fileSpec = _T("*.*");

    attribute = FILE_ATTRIBUTE_ARCHIVE|
    FILE_ATTRIBUTE_DIRECTORY|
    FILE_ATTRIBUTE_HIDDEN|   
    FILE_ATTRIBUTE_NORMAL|  
    FILE_ATTRIBUTE_READONLY| 
    FILE_ATTRIBUTE_SYSTEM;

    return rc;
  }


public:
  void setup(const TCHAR* dir, const TCHAR* spec, int attr)
  {
       TCHAR pathspec[_MAX_PATH];

    setDirectory(dir);
    setFileSpec(spec);
    setAttribute(attr);

    if(dir[strlen(dir)-1] == '\\') {
      _stprintf_s(pathspec, _MAX_PATH, _T("%s%s"), dir, spec);
    }
    else {
      _stprintf_s(pathspec, _MAX_PATH, _T("%s\\%s"), dir, spec);
    }
    findFiles(attribute, pathspec);
  }


public:
  void update()
  {
       TCHAR pathspec[_MAX_PATH];
    _stprintf_s(pathspec, _MAX_PATH, 
      _T("%s\\%s"), (const TCHAR*)directory,
      (const TCHAR*)fileSpec);

    resetContent();

    findFiles(attribute, pathspec);
  }

public:
  // Give a TCHAR array for fileName.
  // For example:TCHAR fileName[_MAX_PATH];
  void getFileName(String&  fileName)
  {
    fileName = "";
    TCHAR buffer[_MAX_PATH];
    memset(buffer, (TCHAR)0, _MAX_PATH);
    int indx = getCurSel();
    if(indx != LB_ERR) {
      getText(indx, buffer);
      fileName = buffer;
    }
  }
public:
  // Give a TCHAR array for pathName.
  // For example:TCHAR pathName[_MAX_PATH];
  void FileListBox::getPathName(String& pathName)
  {
    TCHAR name[_MAX_PATH];
    memset(name, (TCHAR)0, _MAX_PATH);
    int indx = getCurSel();
    if(indx != LB_ERR) {
      getText(indx, name);
  

      TCHAR fullPath[_MAX_PATH];
      _stprintf_s(fullPath, _MAX_PATH, _T("%s\\%s"), 
        (const TCHAR*)directory, name);

      pathName = fullPath;
    }
  }

public:
  TCHAR* getPathName()
  {
    int indx = getCurSel();
    TCHAR* pathName = NULL;
    if(indx != LB_ERR) {
      const TCHAR* cdir = (const TCHAR*)directory;
      int len = getTextLen(indx);
      TCHAR* item = new TCHAR[len+1];
      getText(indx, item);
      int slen = strlen(cdir)+strlen(item)+2;
      pathName = new TCHAR[slen];
      _stprintf_s(pathName, slen, _T("%s\\%s"), cdir, item);     
      delete [] item;
    }
    return pathName;
  }

  void   getDirectory(String& dir) {
      dir = directory;
  }


  void   getFileSpec(String& spec) {
    spec = this->fileSpec;
  }

  void   setAttribute(long  attr) {
      this->attribute = attr;
  }

  void   setDirectory(const TCHAR*  dir) {
      this->directory = dir;
  }

  void setFileSpec(const TCHAR* string) {
    this->fileSpec = string;
  }

};

}

