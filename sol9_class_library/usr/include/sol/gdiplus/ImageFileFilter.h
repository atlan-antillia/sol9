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
 *  ImageFilters.h
 *
 *****************************************************************************/

// SOL9
// 2012/05/20

#pragma once

#include <sol\Object.h>
#include <sol\WString.h>
//#include <gdiplus.h>

namespace SOL {

class ImageFileFilter :public Object {
public:
  /*
  enum Alignment{
    Center = 0,
    LeftTop = 1,
    LeftBottom = 2,
    RightTop = 3,
    RightBottom = 4,
  };
  */
private:
  WString fileName;
  WString filterName;  //Specify a string such as "alpha:0.70"
  WString resize;  //"50%", "100,*", "*,300", "200,300"

  //int    sizePercentage;
  
  //Alignment alignment;
  WString   alignment;

public:
  ImageFileFilter(const TCHAR* file, const TCHAR* filter, const TCHAR* size, const TCHAR* align)
    :fileName(file),
    filterName(filter),
    resize(size),
    alignment(align)
  {
  }

public:
  const wchar_t* getFileName()
  {
    return (const wchar_t*)fileName;
  }

public:
  const wchar_t* getFilterName()
  {
    return (const wchar_t*)filterName;
  }

public:
  const wchar_t* getSize()
  {
    return (const wchar_t*)resize;
  }

public:
  const wchar_t* getAlignment()
  {
    return (const wchar_t*)alignment;
  }

public:
  void setFileName(const TCHAR* file)
  {
    fileName = file;
  }

public:
  void setFilterName(const TCHAR* filter)
  {
    filterName = filter;
  }

public:
  void setSize(const TCHAR* size)
  {
    resize = size;
  }

public:
  void setAlignment(const TCHAR* align)
  {
    alignment = align;
  }

};

}
