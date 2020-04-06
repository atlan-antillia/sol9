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
 *  BinaryFileReader.h
 *
 *****************************************************************************/

#pragma once

#include <sol/BinaryFile.h>
#include <sol/Exception.h>

namespace SOL {

class BinaryFileReader : BinaryFile {
private:
  UINT8*  buffer;
  size_t size;
  
public:
  BinaryFileReader(const TCHAR* filename, int shareFlag= 0)
  :BinaryFile(),
  buffer(NULL),
  size(0)
  {
    if (openReadOnly(filename, shareFlag) ) {
      size   = (size_t)fileLength();
      printf("Size=%d\n", size);
      buffer  = new UINT8[size];
      UINT8* ptr = buffer;
      size_t remain = size;
      while (remain > 0) {
        size_t rlen = (size_t)read((char*)ptr, (long)remain);

        if (rlen > 0) {
         remain -= rlen;
         ptr    += rlen;
        } else {
          break;
        }
      }
      close();
    } else {
      throw IException(_T("Failed to openReadOnly. %s"), filename);
    }
  }
  
  
  ~BinaryFileReader()
  {
    delete buffer;
  }
  
  UINT8* getBuffer()
  {
    return buffer;
  }
   
  size_t getSize()
  {
    return size;
  }
  
  void write(const TCHAR* filename)
  {
    if (create(filename)) {
      UINT8* ptr = buffer;
      size_t remain = size;
      while (remain > 0) {
        size_t rlen = (size_t)BinaryFile::write((char*)ptr, (long)remain);

        if (rlen > 0) {
         remain -= rlen;
         ptr    += rlen;
        } else {
          break;
        }
      }
      close();
      
    } else {
      throw IException("Failed to openReadWrite");
    }
  }
  
};

}

