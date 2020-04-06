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
 *  File.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.08.06 Modified the type of argument for get*Time methods
// to take a reference to FILETIME, not a pointer to FILETIME.
// 1999.08.10 Added a shareMode argument to openReadOnly method.

// 2000.07.09 Modified datatype for read/write methods.
#pragma once

#include <io.h>
#include <sol\Object.h>
//2008/07/09

#include <sol\InvalidHandleException.h>

#include <sol\String.h>
#include <sol\AlreadyOpenedException.h>


namespace SOL {

class File :public Object {
  UINT  mode;  
  HANDLE  fh;
  // 1999.03.09
  
  String name;

 protected:
    File(HANDLE handle) {
      fh = handle;
  }

public:
  File()
    :fh(INVALID_HANDLE_VALUE),
    mode(NULL)
  {
  }

public:
  ~File()
  {
    close();
  }

public:
  BOOL create(const TCHAR* filePath) 
  {
    isAlreadyOpened();

    BOOL rc = FALSE;

    if (filePath) {
      // If already opened, close it

      this->fh = ::CreateFile(filePath,  //  Name of the file 
          GENERIC_READ|GENERIC_WRITE,  // Access mode 
          0,              // Share mode 
          NULL,          // Security descriptor 
          CREATE_ALWAYS,      // How to create 
          FILE_ATTRIBUTE_NORMAL,  // File attributes 
          NULL);           // Attributes to copy  
      if(this->fh != INVALID_HANDLE_VALUE) {
        rc = TRUE;
        this->name = filePath;
        mode = OF_CREATE;

      } else {
        throw InvalidHandleException("Failed to create a file", GetLastError());

      }
    }
    return rc;
  }

public:
  BOOL create(const TCHAR* filePath, 
    DWORD access, 
    DWORD share,
      SECURITY_ATTRIBUTES*  securityAttrs, 
      DWORD  howToCreate,  
      DWORD  attrsAndFlags, 
      HANDLE  hTemplateFile)
  {
    isAlreadyOpened();

    BOOL rc = FALSE;

    if (filePath) {
      // If already opened, close it

      this->fh = ::CreateFile(filePath, 
        access, share,
          securityAttrs, 
          howToCreate,  
          attrsAndFlags, 
          hTemplateFile);

      if(this->fh != INVALID_HANDLE_VALUE){
        this->mode = OF_CREATE;
        this->name = filePath;

        rc = TRUE;
      } else {
        throw InvalidHandleException("Failed to create a file", GetLastError());
      }
    }
    return rc;
  }         
  
public:
  void isAlreadyOpened()
  {
    if(this->fh != INVALID_HANDLE_VALUE) {
      throw AlreadyOpenedException("FileAlreadyOpened");
    }    
  }

public:    
  virtual void close() 
  {
    if(this->fh != INVALID_HANDLE_VALUE) {
      ::FlushFileBuffers(this->fh);
      ::CloseHandle(this->fh);

      this->fh = INVALID_HANDLE_VALUE;
    }
  }

public:
  //2012/02/11
  bool isUnicodeFile(const TCHAR* filename)
  {
    bool rc = false;
    if (openReadOnly(filename)) {
      if (fileLength() >=2) {
        unsigned char buffer[2];
        read(buffer, sizeof(buffer));

        if (buffer[0] == 0xff && buffer[1] == 0xfe) {
          rc = true;
        }
      }
      close();
    }
    return rc;
  }

public:
  HANDLE getHandle() {
    //2009/10/18 Added NULL check for this->fh handle. 
    if (this->fh == INVALID_HANDLE_VALUE || this->fh == NULL) {
      throw InvalidHandleException("File::getHandle,1,InvalidFileHandle\n");
    }
    return this->fh;
  }

public:
  long fileLength() 
  {
    HANDLE h = getHandle();

    return (long)::GetFileSize(h, NULL);
  }
public:
  virtual void flush() 
  {
    HANDLE h = getHandle();
    ::FlushFileBuffers(h);
  }

public:
  BOOL isExistent(const TCHAR* fileName) 
  {
    // 2008/07/09
    BOOL rc = FALSE;
    if (fileName) {
      if (GetFileAttributes(fileName) != 0xffffffff) {
        rc = TRUE;
      }
    }
    return rc;
  }

public:
  BOOL openReadOnly(const TCHAR* filePath, int shareMode=0) 
  {
    isAlreadyOpened();

    BOOL rc = FALSE;
    if (filePath) {

      this->fh = ::CreateFile(filePath,    //  Name of the file 
          GENERIC_READ,      // Access mode 
          shareMode,        // Ahare mode 
          NULL,          // Security descriptor 
          OPEN_EXISTING,      // How to create 
          FILE_ATTRIBUTE_READONLY,  // File attributes 
          NULL);           // Attributes to copy

      if(this->fh != INVALID_HANDLE_VALUE) {
        this->mode = OF_READ;
        this->name = filePath;

        rc = TRUE;  

      } else {

      }
    }
    return rc;
  }

public:
  BOOL openReadWrite(const TCHAR* filePath, int shareMode=0) 
  {
    isAlreadyOpened();

    BOOL rc = FALSE;
    if (filePath) {

      this->fh = ::CreateFile(filePath,    //  name of the file 
          GENERIC_READ|GENERIC_WRITE,  // access mode 
          shareMode,            // share mode 
          NULL,          // security descriptor 
          OPEN_EXISTING,      // how to create 
          FILE_ATTRIBUTE_NORMAL,  // file attributes 
          NULL           // attributes to copy  
         );  
      if(this->fh != INVALID_HANDLE_VALUE) {
        this->mode = OF_READWRITE;
        this->name = filePath;

        rc = TRUE;
      }
    }
    return rc;
  }

public:
  BOOL openWriteOnly(const TCHAR* filePath, int shareMode=0) 
  {
    isAlreadyOpened();

    BOOL rc = FALSE;

    if (filePath) {  
      this->fh = ::CreateFile(name,    //  name of the file 
        GENERIC_WRITE,      // access mode 
        shareMode,            // share mode 
        NULL,          // security descriptor 
        OPEN_EXISTING,      // how to create 
        FILE_ATTRIBUTE_NORMAL,  // file attributes 
        NULL);           // attributes to copy  
      if (this->fh != INVALID_HANDLE_VALUE) {
        this->mode = OF_WRITE;
        this->name = filePath;

        rc = TRUE;
      }
    }
    return rc;
  }

public:
  BOOL remove(const TCHAR* filePath) 
  {
    BOOL rc = FALSE;

    if (filePath) {
      rc = ::DeleteFile(filePath);
    }
    return rc;
  }

public:
  // dir FILE_BEGIN/FILE_CURRENT/FILE_END
  long seek(long pos, int dir) 
  {
    HANDLE h = getHandle();
    return SetFilePointer(h, pos, NULL, dir);
  }

public:
  long seekBegin(long pos) 
  {
    return seek(pos, FILE_BEGIN);
  }

public:
  long seekCurrent(long pos) 
  {
    return seek(pos, FILE_CURRENT);
  }

public:
  long seekEnd(long pos) 
  {
    return seek(pos, FILE_END);
  }

public:
  unsigned long read(__out char* buffer, __in unsigned long size) 
  {
    HANDLE h = getHandle();
    unsigned long len = 0;

    ::ReadFile(h, buffer, size, (unsigned long*)&len, NULL);
    return len;
  }

public:
  unsigned long write(__in char* buffer, __in unsigned long size) 
  {
    HANDLE h = getHandle();
    unsigned long len = 0;
    ::WriteFile(h, buffer, size, (unsigned long*)&len, NULL);
    return len;
  }


public:
  //buffer is a Null-terminated string
  unsigned long write(__in char* buffer) 
  {
    size_t size = strlen(buffer);

    HANDLE h = getHandle();
    unsigned long len = 0;
    ::WriteFile(h, buffer, (DWORD)size, (unsigned long*)&len, NULL);
    return len;
  }

//2009/10/18
public:
  unsigned long read(__out unsigned char* buffer, __in unsigned long size) 
  {
    HANDLE h = getHandle();
    unsigned long len = 0;

    ::ReadFile(h, buffer, size, (unsigned long*)&len, NULL);
    return len;
  }
//2009/10/18

public:
  unsigned long write(__in unsigned char* buffer, __in unsigned long size) 
  {
    HANDLE h = getHandle();
    unsigned long len = 0;
    ::WriteFile(h, buffer, size, (unsigned long*)&len, NULL);
    return len;
  }

public:
  unsigned long write(wchar_t* buffer, unsigned long charLen) 
  {
    HANDLE h = getHandle();
    unsigned long len = 0;
    unsigned long bytesLen = charLen*2;

    ::WriteFile(h, buffer, bytesLen, (unsigned long*)&len, NULL);
    return len;
  }

public:
  //buffer is a Null-terminated string
  unsigned long write(const wchar_t* buffer) 
  {
    size_t charLen = wcslen(buffer);
    HANDLE h = getHandle();
    unsigned long len = 0;
    size_t bytesLen = charLen*2;

    ::WriteFile(h, buffer, (DWORD)bytesLen, (unsigned long*)&len, NULL);
    return len;
  }

public:
  BOOL getCreationTime(FILETIME& creation) 
  {
    HANDLE h = getHandle();
    FILETIME lastAccess;
    FILETIME lastWrite;
    return ::GetFileTime(h, &creation, &lastAccess, &lastWrite);
  }
public:
  BOOL getLastAccessTime(FILETIME& lastAccess) 
  {
    HANDLE h = getHandle();
    FILETIME creation;
    FILETIME lastWrite;
    return ::GetFileTime(h, &creation, &lastAccess, &lastWrite);
  }

public:

  BOOL getLastWriteTime(FILETIME& lastWrite) 
  {
    HANDLE h = getHandle();
    FILETIME creation;
    FILETIME lastAccess;
    return ::GetFileTime(h, &creation, &lastAccess, &lastWrite);
  }


public:
  DWORD  getAttributes(const TCHAR* name) {
      return ::GetFileAttributes(name);
  }

public:
  int  getMode() { 
    return mode; 
  }

public:
  BOOL  getFileInformation(BY_HANDLE_FILE_INFORMATION* info) {
    HANDLE h = getHandle();
    return ::GetFileInformationByHandle(h, info);
  }

public:
  DWORD  getType() { 
    HANDLE h = getHandle();
    return ::GetFileType(h); 
  }
  
public:
  BOOL  getTime(FILETIME& creation, 
      FILETIME& lastAccess, FILETIME& lastWrite) {

    HANDLE h = getHandle();
    return ::GetFileTime(h, &creation, &lastAccess, &lastWrite);
  }

public:
  BOOL  setTime(const FILETIME* creation, 
        const FILETIME* lastAccess, const FILETIME* lastWrite) {
    HANDLE h = getHandle();
    return ::SetFileTime(h, creation, lastAccess, lastWrite);
  }

public:
  void  setEnd() {
    HANDLE h = getHandle();

    ::SetEndOfFile(h);
  }
};

}



