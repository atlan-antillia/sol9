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
 *  OfficeFileVerifier.h
 *
 *****************************************************************************/

// 2012/05/12
// 2012/05/20 Modified isOfficeFile method.

#pragma once

#include <sol/Object.h>
#include <sol/Path.h>
#include <sol/File.h>


namespace SOL {

class OfficeFileVerifier :public Object {

public:
  OfficeFileVerifier() 
  {
  }

public:
  ~OfficeFileVerifier() 
  {
  }


private:
  bool verifyFileHeader(const TCHAR* filename, const unsigned char* header, const int hsize)
  {
    bool rc = false;

    if (GetFileAttributes(filename) == 0xFFFFFFFF) {
      return rc;
    }

    HANDLE in = CreateFile(filename,  // Name of the file 
          GENERIC_READ,      // Access mode         
            TRUE,          // Share mode 
            NULL,          // Security descriptor 
            OPEN_EXISTING,      // How to create 
            FILE_ATTRIBUTE_READONLY,// File attributes 
            NULL);           // Attributes to copy

    if(in != INVALID_HANDLE_VALUE) {

      unsigned char* data = new unsigned char[hsize];
      unsigned long len = 0;
      if (ReadFile(in, data, hsize, (unsigned long*)&len, NULL)) {
        if(startsWith(data, header,  hsize)) {
          rc = true;
        } 
      }
      delete [] data;
      CloseHandle(in);          
    }
    return rc;
  }

public:
  bool isOfficeFile(const TCHAR* filename) 
  {
    bool rc = false;

    if (isOfficeFileExtension(filename)) {

      if (isOffice2007FileExtension(filename)) {
        //Verify ZIP header  
        rc = isZipHeader(filename);
        //2012/05/20
        if (!rc) {
          //If encrypted office file of office2010, it's a compound file.
          rc = isOfficeHeader(filename); 
        }
      } else {
        //Verify OFFICE header
        rc = isOfficeHeader(filename);
      }
    }
    return rc;
  }

public:
  bool isOfficeHeader(const TCHAR* filename) 
  {
    static const unsigned char OFFICE_HEADER[] = 
      {0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1,};
    return verifyFileHeader(filename, OFFICE_HEADER, CountOf(OFFICE_HEADER));
  }

public:
  bool isZipHeader(const TCHAR* filename) 
  {
    static const unsigned char ZIP_HEADER[] = 
      {0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x06, 0x00, 0x08, 0x00};

    return verifyFileHeader(filename, ZIP_HEADER, CountOf(ZIP_HEADER));
  }

public:
  bool isXPSFile(const TCHAR* filename) 
  {
    bool rc = isXPSFileExtension(filename);

    if (rc != true) {
      return rc;
    }

    return isZipHeader(filename);
  }

public:
  bool isOffice2007FileExtension(const TCHAR* filePath)
  {
    bool rc = false;

    TCHAR* EXTENSIONS[] ={
    _T(".docx"), _T(".docm"),
    _T(".pptx"), _T(".pptm"), _T(".ppsx"), _T(".ppsm"),
    _T(".xlsb"), _T(".xlsx"), _T(".xlsm"),
    _T(".xps")
    };

    for (int i = 0; i<CountOf(EXTENSIONS); i++) {
      if (endsWithIgnoreCase(filePath, EXTENSIONS[i])) {
        rc = true;
        break;
      }
    }
    return rc;    
  }

public:
  bool isOfficeFileExtension(const TCHAR* filePath)
  {
    bool rc = false;

    TCHAR* EXTENSIONS[] ={
    _T(".doc"), _T(".docx"), _T(".docm"),
    _T(".ppt"), _T(".pps"), _T(".pptx"), _T(".pptm"), _T(".ppsx"), _T(".ppsm"),
    _T(".xls"), _T(".xlsb"), _T(".xlsx"), _T(".xlsm"),
    _T(".xps")
    };

    for (int i = 0; i<CountOf(EXTENSIONS); i++) {
      if (endsWithIgnoreCase(filePath, EXTENSIONS[i])) {
        rc = true;
        break;
      }
    }

    return rc;    
  }

public:
  bool isOfficeFileExtensionWithoutXPS(const TCHAR* filePath)
  {
    bool rc = false;

    TCHAR* EXTENSIONS[] ={
    _T(".doc"), _T(".docx"), _T(".docm"),
    _T(".ppt"), _T(".pps"), _T(".pptx"), _T(".pptm"), _T(".ppsx"), _T(".ppsm"),
    _T(".xls"), _T(".xlsb"), _T(".xlsx"), _T(".xlsm"),
    //_T(".xps")
    };

    for (int i = 0; i<CountOf(EXTENSIONS); i++) {
      if (endsWithIgnoreCase(filePath, EXTENSIONS[i])) {
        rc = true;
        break;
      }
    }
    return rc;    
  }

public:
  bool isXPSFileExtension(const TCHAR* filePath)
  {
    bool rc = false;

    if (endsWithIgnoreCase(filePath, _T(".xps"))) {
      rc = true;  
    }
    return rc;    
  }

public:
  bool isWordFileExtension(const TCHAR* filePath)
  {
    bool rc = false;

    if (endsWithIgnoreCase(filePath, _T(".doc")) ||
      endsWithIgnoreCase(filePath, _T(".docx")) ||
      endsWithIgnoreCase(filePath, _T(".docm")) ) {
      rc = true;  
    }
    return rc;    
  }

public:
  bool isPowerPointFileExtension(const TCHAR* filePath)
  {
    bool rc = false;

    if (endsWithIgnoreCase(filePath, _T(".ppt")) ||
      endsWithIgnoreCase(filePath, _T(".pps")) ||
      endsWithIgnoreCase(filePath, _T(".pptx")) ||
      endsWithIgnoreCase(filePath, _T(".pptm")) ||
      endsWithIgnoreCase(filePath, _T(".ppsx")) ||
      endsWithIgnoreCase(filePath, _T(".ppsm"))  ) {
      rc = true;  
    }
    return rc;    
  }

public:
  bool isExcelFileExtension(const TCHAR* filePath)
  {
    bool rc = false;

    if (endsWithIgnoreCase(filePath, _T(".xls")) ||
      endsWithIgnoreCase(filePath, _T(".xlsb")) ||
      endsWithIgnoreCase(filePath, _T(".xlsx")) ||
      endsWithIgnoreCase(filePath, _T(".xlsm")) ) {
      rc = true;  
    }
    return rc;    
  }

public:
  static bool endsWithIgnoreCase(const TCHAR* string, const TCHAR* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = strlen(string);
      size_t slen = strlen(end);
      if (tlen >= slen) {
        if (_strnicmp(string+tlen-slen, end, slen) == 0) { //2015/12/30
          rc = true;
        }
      }
    }
    return rc;
  }

private:
   bool startsWith(const unsigned char* data, const unsigned char* header, int len) {
    bool rc = true;
    for (int i = 0; i<len; i++) {
      if (data[i] != header[i]) {
        rc = false;
        break;  
      }
    }
    return rc;
  }

};

}
