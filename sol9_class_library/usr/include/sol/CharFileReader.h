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
 *  CharFileReader.h
 *
 *****************************************************************************/

//2016/02/27
//2016/07/10 Modified to specify share mode in opeReadOnly.
#pragma once

#include <sol/File.h>

namespace SOL {

class CharFileReader :public File {
private:
  char*  data;
  size_t size;
  
public:
  CharFileReader(const TCHAR* fileName, bool nullTerminated=true)
  :File(),
  data(NULL),
  size(0)
  {
    //Set sharemode
    if (openReadOnly(fileName, FILE_SHARE_READ | FILE_SHARE_WRITE) == FALSE) {
      String name(fileName);
      throw IException("Failed to open a file. %s", (const char*)name.getCharString());
    }
    
    size = fileLength();
    if (nullTerminated) {
      data = new char[size+1];
    } else {
      data = new char[size];
    }
        
    memset(data, 0, size);
  
    size_t remain = size;
    char* ptr = data;
    while (remain > 0) {
      size_t len = read(ptr, remain);
      remain -= len;
      ptr += len;
    }
    if (nullTerminated) {
      data[size] = ZERO;
    }
    close();
  }
  

public:
  ~CharFileReader()
  {
    
    delete[] data;
    data = NULL;
  }  
public:
  const char* getData() const
  {
    return data;
  }
  
  const size_t getDataSize() const
  {
    return size;
  }
};

} 
   