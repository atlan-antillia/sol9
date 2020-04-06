/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  StreamFile.h
 *
 *****************************************************************************/

#pragma once

#include <sol/Object.h>
#include <sol/Exception.h>

namespace SOL {

class StreamFile :public Object { //TextFile {
private:
  FILE* fp;
    
public:
  StreamFile()
  :fp(NULL)
  {
  }
  
  bool open(const char* filepath, const char* rwmode, const char* encoding=NULL)
  {
    if (filepath == NULL) {
      throw IException("Invalid parameter: filepath is NULL.");  
    }
    if (rwmode == NULL) {
      throw IException("Invalid parameter: rwmode is NULL."); 
    }
    
    char mode[256];
    memset(mode, 0, sizeof(mode));
    
    if (encoding == NULL) {
      //ANSI encoding
      sprintf_s(mode, CountOf(mode), "%s", rwmode);
    } else if (strcmp(encoding, "UNICODE") == 0 ||
        strcmp(encoding, "UTF-8") == 0 ||
        strcmp(encoding, "UTF-16LE") == 0) {
      sprintf_s(mode, CountOf(mode), "%s, ccs=%s", rwmode, encodidng);
     } else {
      throw IException("Invalid encoding parameter.");
     }
      
      errno_t err = fopen_s(&fp, filepath, rwmode);
      if (err != 0 || fp == NULL) {
        throw IException("Failed to open: %s", filepath);      
      }
    
      errno_t err = fopen_s(&fp, filepath, mode);
      if (err != 0 || fp == NULL) {
        throw IException("Failed to open: %s", filepath);      
      }
  }

  bool open(const wchar_t* filepath, const wchar_t* rwmode, const wchar_t* encoding=NULL)
  {
    if (filepath == NULL) {
      throw IException("Invalid parameter: filepath is NULL.");  
    }
    if (rwmode == NULL) {
      throw IException("Invalid parameter: rwmode is NULL."); 
    }
    
    wchar_t mode[256];
    memset(mode, 0, size(mode));
    
    if (encoding == NULL) {
      //ANSI encoding
      swprintf_s(mode, CountOf(mode), L"%s", rwmode);
    } else if (wcscmp(encoding, L"UNICODE") == 0 ||
               wcscmp(encoding, L"UTF-8") == 0 ||
               wcscmp(encoding, L"UTF-16LE") == 0) {
      swprintf_s(mode, CountOf(mode), L"%s, ccs=%s", rwmode, encodidng);
     } else {
      throw IException("Invalid encoding parameter.");
     }
      
      errno_t err = _wfopen_s(&fp, filepath, rwmode);
      if (err != 0 || fp == NULL) {
        throw IException("Failed to open: %s", filepath);      
      }
    
      errno_t err = fopen_s(&fp, filepath, mode);
      if (err != 0 || fp == NULL) {
        throw IException("Failed to open: %s", filepath);      
      }
  }

public:
  ~StreamFile()
  {
    close();
  }
  
  void close()
  {
    if (fp) {
      fclose(fp);
      fp = NULL;
    }
  }

};


}
