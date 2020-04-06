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
 *  FileStream.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\File.h>


namespace SOL {

class FileStream :public File {
private:
  long      offset;
  char*     buffer;
  size_t    buffsize;
  size_t    pos;
  size_t    charNum;

protected:
  FileStream(HANDLE handle)
    :File(handle) { 
  }

public:
  FileStream()
  {
    offset   = 0L;
    buffsize = 1024*32;  //2008/07/02
    buffer   = new char[buffsize];
    pos      = 0;
    charNum  = 0;
  }


public:
  FileStream(int bufferSize)
  {
    //2008/07/02
    if (bufferSize< SIZE_1KB) {
      bufferSize = SIZE_1KB;
    }

    offset   = 0L;
    buffsize = bufferSize;

    buffer   = new char[buffsize];
    pos      = 0;
    charNum  = 0;
  }


  ~FileStream()
  {
    if (buffer) {
      delete [] buffer;  // 
    }
    buffer = NULL;
  }

public:
  BOOL create(const TCHAR* fileName)
  {
    pos      = 0;
    charNum  = 0;
    offset   = 0L;
    return File::create(fileName);
  }

public:
  BOOL openReadOnly(const TCHAR* fileName)
  {
    pos     = 0;
    charNum = 0;
    offset  = 0L;
    return File::openReadOnly(fileName);
  }

public:
  BOOL openReadWrite(const TCHAR* fileName)
  {
    pos     = 0;
    charNum = 0;
    offset  = 0L;  
    return File::openReadWrite(fileName);
  }

public:
  BOOL openWriteOnly(const TCHAR* fileName)
  {
    pos     = 0;
    charNum = 0;
    offset  = 0L;  
    return File::openWriteOnly(fileName);
  }


public:
  int getLine(char* string, int num)
  {
    int ret = 0;
    if(pos >= charNum) {
      pos = 0;
      ret = readMultiLines();
    }
    if(ret == -1) {
      return FALSE;
    }

    size_t i = pos;
    size_t j = 0;

    while(i < charNum) {
      if(j == num) {
        break;
      }
      if(buffer[i] == 0xd && buffer[i+1] == 0xa) {
        pos = i+2;
        break;
      }
      string[j++] = buffer[i++];
    }
    string[j] = NULL;
    return TRUE;
  }

public:
  int putLine(const char* line)
  {
    int num = 0;

    if (line==NULL) {
      return num;
    }

    size_t len  = strlen(line);

    if(pos + len >= buffsize) {
      charNum = pos;
      num     = writeMultiLines();
      pos = 0;
    }
    size_t i = pos;
    size_t j = 0;
  
    while(j <= len) {
      if(line[j] == NULL) {
        pos     = i;
        charNum = pos;
        break;
      }
      buffer[i++] = line[j++];
    }
    return num;
  }


public:
  int putLineWithCR(const char* line)
  {
    if (line==NULL) {
      return 0;
    }

    int n = putLine(line);
    int m = putLine("\r\n");
    return n + m;
  }


public:
  int printFWithCR(char* format,...)  
  {
    const int BSIZE = 1024*8;
    //Allocate a temporary buff of size BSIZE.
    char* buff  = new char[BSIZE];
    va_list pos;
    va_start(pos, format);
    vsprintf_s(buff, BSIZE, format, pos);
    va_end(pos);
  
    int r =putLineWithCR(buff);

    delete [] buff;
    return r;
  }


public:
  void flush()
  {
    if(charNum >0)   {
      writeMultiLines();
    }
    pos     = 0;
    charNum = 0;

    offset = NULL;
    //File::flush();
  }

public:
  void close()
  {
    int mode = getMode();
    if((mode == OF_WRITE) || (mode == OF_CREATE)) {
      flush();
    }
    pos     = 0;  // 
    charNum = 0;  //
    offset  = 0L;  //

    File::close();
  }

///////////////////////////////////////////////////////
private:
  int readMultiLines()
  {
    if(seek(offset, 0) == -1L) {
      return -1;
    }
    charNum = read(buffer, buffsize);
    //if(charNum == -1) {
    if (charNum <= 0) { //2017/09/10
        return -1;
    }
    int next = getNextPosition();
    if(next == -1)  {
      return -1;
    }
    charNum = next;
    offset += next;

    return 1;
  }

private:
  size_t writeMultiLines()
  {
    if(seek(offset, 0) == -1L) {
      return -1;
    }
    size_t num = write(buffer, charNum);
    offset += charNum;

    return num;
  }

private:
  size_t getNextPosition()
  {
    size_t i = charNum - 1;

    while(i > 0) {
      if(buffer[i-1] == 0xd && buffer[i] == 0xa) {
        return i+1;
      }
      i--;
    }
    return -1;
  }

};

}


