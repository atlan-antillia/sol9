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
 *  DropFiles.h
 *
 *****************************************************************************/

// SOL++2000
// 2012/06/22

#pragma once
#include <sol\Event.h>
#include <sol\StringList.h>

#include <shellapi.h>
#include <shlobj.h>


namespace SOL {

class DropFiles :public Object {
private:
  BOOL  dropped;
  HDROP  hdrop;
  int    num;
private:
  HDROP build(StringList* stringList, POINT pt, BOOL ncFlag,
           BOOL wcFlag=FALSE)
  {
    HDROP hdrop = NULL;
    if(stringList) {
      ListEntry* ptr = stringList->getEntry();    
      int buffLen = 0;
      while(ptr) {
        String* string = (String*)ptr->getObject();
        if(string) {
          buffLen = buffLen + string->getLength() + 1;
        }
        ptr = ptr ->getNext();
      }
    
      int  size = sizeof(DROPFILES) + buffLen+1;
  
      hdrop = (HDROP)::GlobalAlloc(GHND, size);
      if(hdrop) {
        DROPFILES* dropFiles = (DROPFILES*)::GlobalLock(hdrop);    
        int   offset = sizeof(DROPFILES);
        dropFiles->pFiles = offset;
        dropFiles->pt  = pt;
        dropFiles->fNC = ncFlag;  // True, if pt is in screen coords.
#ifdef UNICODE
        dropFiles->fWide = TRUE;  // True, if wide TCHAR switching
#else
        dropFiles->fWide = FALSE;  // True, if wide TCHAR switching

#endif
        TCHAR* buffer = (TCHAR*)dropFiles + offset;

        ptr = stringList->getEntry();
        int pos = 0;
        while(ptr) {
          String* string = (String*)ptr->getObject();
          if(string) {

            strcpy_s(buffer, string->getLength(), string->getContents());
            
            pos = string->getLength() + 1;
            buffer = buffer + pos;
          }
          ptr = ptr ->getNext();
        }
        ::GlobalUnlock(hdrop);
        num = ::DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
      }
    }
    return hdrop;
  }

public:

  DropFiles(HDROP drop) 
  {
    num      = 0;
    hdrop    = drop;
    dropped  = TRUE;
    num      = ::DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
  }

public:
  DropFiles(const TCHAR* fileName, POINT pt, BOOL ncFlag,
           BOOL wcFlag)
  {
    num = 0;
    dropped = FALSE;
    hdrop = NULL;

    if(fileName) {
      StringList stringList;
      stringList.addLast(fileName);
      hdrop   = build(&stringList, pt, ncFlag, wcFlag);
    }
  }

public:
  DropFiles(StringList* stringList, POINT pt, BOOL ncFlag,
           BOOL wcFlag = FALSE)
  {
    num     = 0;
    dropped = FALSE;
    hdrop   = build(stringList, pt, ncFlag, wcFlag);
  }




public:
  ~DropFiles()
  {
    if(hdrop && dropped) {
      ::DragFinish(hdrop);
    }
  }

public:
  int  queryFile(int indx, TCHAR* fileName, int size)
  {
    int length = 0;
    if(indx >= 0 && indx < num) {
      length = ::DragQueryFile(hdrop, indx, fileName, size);
    }
    return length;
  }

public:
  int  queryFileNameLength(int indx)
  {
    int length = 0;
    if(indx >= 0 && indx < num) {
      length = ::DragQueryFile(hdrop, indx, NULL, 0);
    }
    return length;
  }

public:
  void queryPoint(POINT* pt)
  {
    pt->x = 0;
    pt->y = 0;
    if(hdrop) {
      ::DragQueryPoint(hdrop, pt);
    }
  }

  int   queryCount() {
      return num;
  }

  HDROP   getDropHandle() {
      return hdrop;
  }
  //2012/06/22
  operator HDROP(){
    return hdrop;
  }
};

}


