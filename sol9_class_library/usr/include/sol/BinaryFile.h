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
 *  BinaryFile.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.07.09 Modified;
// 2009/10/18 Modified the parameter 'char* buffer' for methods to 'unsigned char* buffer'.

#pragma once

#include <sol\File.h>

namespace SOL {

class BinaryFile :public File {
  
public:
  BinaryFile() { }

  unsigned long   read(__out char* buffer, __in unsigned long size) {
      return File::read(buffer, size);
  }

  unsigned long   write(__out char* buffer, __in unsigned long size) {
      return File::write(buffer, size);
  }

  unsigned long   read(__in long offset, __out char* buffer, __in unsigned long size) {
      seek(offset, FILE_BEGIN);
      return File::read(buffer, size);
  }

  unsigned long   write(__in long offset, __out char* buffer, __in unsigned long size) {
      seek(offset, FILE_BEGIN);
      return File::write(buffer, size);
  }

// unsigned char buffer
  unsigned long   read(__out unsigned char* buffer, __in unsigned long size) {
      return File::read(buffer, size);
  }

  unsigned long   write(__out unsigned char* buffer, __in unsigned long size) {
      return File::write(buffer, size);
  }

  unsigned long   read(__in long offset, __out unsigned char* buffer, __in unsigned long size) {
      seek(offset, FILE_BEGIN);
      return File::read(buffer, size);
  }

  unsigned long   write(__in long offset, __out unsigned char* buffer, __in unsigned long size) {
      seek(offset, FILE_BEGIN);
      return File::write(buffer, size);
  }


};

}


