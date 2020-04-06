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
 *  FileWriter.h
 *
 *****************************************************************************/

// SOL9
// 2010/04/01 Modified to use DeleteFileW in constructor FileWriter.
// 2012/01/22 Modified to open a reportFile in the constructor FileWriter in append-binary mode.
#pragma once

#include <sol/Object.h>
#include <sol/StringT.h>
#include <sol/StringConverter.h>
#include <sol/Folder.h>

#include <sol/Writer.h>
#include <sol/SmartPtr.h>


namespace SOL {

class FileWriter :public Writer {

private:
  FILE* fp;

private:
  wchar_t* reportFile;

public:
  /**
   * Constructor
   *
   * reportFileName FilePathname to save a text string.
   *     If this parameter NULL, simply display a string on the console(stdout).
   */
  //2015/12/12
  FileWriter(const wchar_t* reportFileName)
    :Writer(),
    reportFile(NULL),
    fp(NULL)
  {
    openFile(reportFileName);
  }

public:
  //2015/12/12
  FileWriter(const char* fileName)
    :Writer(),
    reportFile(NULL),
    fp(NULL)
  {
    StringConverter converter;
    const wchar_t* reportFileName = converter.toWideChar(fileName);
    SmartPtr<const wchar_t> temp(reportFileName);
    
    openFile(reportFileName);
  }
public:
  //2015/07/15
  FileWriter(const _bstr_t& fileName)
    :Writer(),
    reportFile(NULL),
    fp(NULL)
  {
    const wchar_t* reportFileName = (const wchar_t*)(fileName);    
    openFile(reportFileName);
  }
  
  
  //2015/07/15
  void openFile(const wchar_t* reportFileName)
  {
    if (reportFileName) {
      size_t flen = wcslen(reportFileName);
      reportFile = new wchar_t[flen+1];        
      wcscpy_s(reportFile, flen+1, reportFileName);
      if (GetFileAttributesW(reportFile) != -1) {
        //If already exists, try to delete it.
        DeleteFileW(reportFile);  //2010/04/01 Modified to use DeleteFileW
        //Don't care success or failure of this deleteion operation.
      } else {
        //If not existent, check a folder and try to create it
        Folder folder(reportFile);
          
        if (folder.exists() == false) {
          if (folder.createFolder() == false) {
            wchar_t msg[1024];
            swprintf(msg, CountOf(msg), 
              L"Failed to create a folder \"%s\" for filePath:\"%s\"\n",
              folder.getDirectory(), reportFile);
            MessageBoxW(NULL, msg, L"FileWriter", MB_OK);
            delete [] reportFile;
            reportFile = NULL;
            return;
          } else {
            ;//OK probably created a new folder
          }
        } else {
          //MessageBoxW(NULL, folder.getDirectory(), L"FileWriter: folder already exists", MB_OK);
        }
      }
      fp = NULL;
      //2015/12/12 
      errno_t err =_wfopen_s(&fp, reportFile, L"ab");
      if (err !=0 || fp == NULL) {
        throw Exception(GetLastError(), L"Failed to open a file:%s",  reportFile);
      }
      else {
        //2012/01/22 
        //Write the BOM to the above opened file to mark to be UTF-16 file.
        unsigned char bom[2] = {0xff, 0xfe}; 
        writeBytes(bom, 2);
      }
    } else {
      ; //OK, display a string on the console.
    }
  }


public:
  ~FileWriter()
  {
    close();

    if (reportFile) {
      delete [] reportFile;
      reportFile = NULL;
    }
  }

public:
  void close()
  {
    if (fp) {
      fclose(fp);
      fp = NULL;
    }
  }

public:
  //2012/01/22 
  int writeBytes(unsigned char* bytes, size_t len)
  {
    int rc = 0;
    if (bytes && len>0) {
      if (fp) {
        rc = fwrite(bytes, sizeof(unsigned char), len, fp);
      } else {
        //If reportFile were NULL or failed to open the file, simply write a string to a console stdio.
        fwrite(bytes, sizeof(unsigned char), len, stdout);
      }
    }
    return rc;
  }


public:
  // string parameter is a null-terminated wchar_t string
  //
  int writeString(const wchar_t* string)
  {
    int rc = 0;
    if (string) {
      size_t slen = wcslen(string);
      if (fp) {
        //2012/01/22
        rc = fwrite(string, sizeof(wchar_t), slen, fp);
      } else {
        //If reportFile were NULL or failed to open the file, simply write a string to a console stdio.
        rc = fwrite(string, sizeof(wchar_t), slen, stdout);
      }
    }
    return rc;
  }
};

}
