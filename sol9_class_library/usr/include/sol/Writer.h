/******************************************************************************
 *
 * Copyright (c) 2009-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Writer.h
 *
 *****************************************************************************/

// SOL9

#pragma once

#include <sol/Object.h>
#include <sol/StringT.h>
#include <sol/StringConverter.h>
#include <sol/Folder.h>


namespace SOL {

class Writer :public Object {

private:
  wchar_t* buffer;

private:
  // 2012/01/20 Buffer size 100KB for wchar_t* buffer;
  static const int BUFFER_SIZE = 1024*100;


public:
  /**
   + Constructor
   *
   * reportFileName FilePathname to save a text string.
   *              If this parameter NULL, simply display text on the console.
   */
  Writer()
    :buffer(NULL)
  {
    buffer = new wchar_t[BUFFER_SIZE+1];
  }

public:
  ~Writer()
  {
    if (buffer) {
      delete [] buffer;
      buffer = NULL;
    }
  }

public:
  //2012/01/22
  virtual int write(unsigned char* bytes, size_t len)
  {
    int rc = 0;
    if (bytes && len>0) {
      //If reportFile were NULL, simply write a string to a console stdio.
      //rc = printf("%S", string);
      fwrite(bytes, 1, len, stdout);
    }
    return rc;
  }

protected:
  //Write NULL-terminated string to a file or somewhere defined in each subclass. 
  //Implement this method in each subclass inheritting this base class.
  virtual int writeString(const wchar_t* string) 
  {
    int rc = 0;
    //This base Writer class writeString method writes a string of argument to a console stdout.
    if (string) {
      rc = printf("%S", string);
    }
    return rc;
  }

public:
  virtual int write(const wchar_t* format,...)
  {
    int rc = 0;
    if (buffer) {
      va_list pos;
      va_start(pos, format);

      _vsnwprintf_s(buffer, BUFFER_SIZE, _TRUNCATE, format, pos);
      va_end(pos);
      
      rc = writeString(buffer);
    }

    return rc;
  }

public:
  //2012/01/22
  virtual int writeln(const wchar_t* format,...)
  {
    int rc = 0;
    if (buffer) {
      va_list pos;
      va_start(pos, format);

      _vsnwprintf_s(buffer, BUFFER_SIZE-2, _TRUNCATE, format, pos);
      va_end(pos);
      //Append a new-line string "\r\n" for binary-mode to the buffer not "\n".
      //strcat(buffer, L"\r\n");
      strcat_s(buffer, BUFFER_SIZE-2, L"\r\n");

      rc = writeString(buffer);
    }

    return rc;
  }

public:
  // 2012/03/08
  virtual int newLine()
  {
    return writeString(L"\r\n");
  }

};

}
