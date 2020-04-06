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
 *  LogFile.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <io.h>
#include <sol\File.h>

#include <sol\String.h>


namespace SOL {

class LogFile :public File {
private:
  String fileName;
    TCHAR*  buffer;
  
  size_t BUFFER_SIZE;

public:
  LogFile(const TCHAR* filename, unsigned int buffSize=1024) 
  {
    fileName = filename;
    if (buffSize<= SIZE_1KB) {
      buffSize = SIZE_1KB;
    }
    this->BUFFER_SIZE = buffSize;
    buffer    = new TCHAR[buffSize];

  }

public:
  ~LogFile() 
  {
    delete [] buffer;
  }

public:
  int printf(TCHAR* format,...) 
  {
    va_list pos;
    va_start(pos, format);
    //vsprintf_s(this->buffer, this->BUFFER_SIZE, format, pos);
    _vsnprintf_s(this->buffer, this->BUFFER_SIZE, _TRUNCATE, format, pos);
    va_end(pos);
          
    int len = 0;
   
    BOOL rc = create(fileName,  
               GENERIC_READ|GENERIC_WRITE,  // access mode 
               FILE_SHARE_READ|FILE_SHARE_WRITE,// share mode 
               NULL,            // security descriptor 
               OPEN_ALWAYS,          // how to create 
               FILE_ATTRIBUTE_NORMAL,    // file attributes 
               NULL);            // attributes to copy  
    if (rc) {
      // Move write-position to the end of this file.
      seek(0, FILE_END);    
            len = write(buffer, strlen(buffer));
            close();
    }
    return len;
  }

/*
  LogFile(const TCHAR* filename, unsigned int buffSize = 1024);

  ~LogFile();
 
  int printf(TCHAR* format,...);
  */
};

}


