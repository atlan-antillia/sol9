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
 *  FileAttributes.h
 *
 *****************************************************************************/

// SOL9
// 2008/09/15

#pragma once

#include <sol/Object.h>
#include <sol/String.h>
#include <sol/StringBuffer.h>
#include <sol/Arg.h>
#include <shlwapi.h>    //shlwapi.lib
#include <psapi.h>      //psapi.lib

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "psapi.lib")

namespace SOL {

class FileAttributes :public Object {

/*
typedef struct _WIN32_FIND_DATA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    TCHAR cFileName[MAX_PATH];
    TCHAR cAlternateFileName[14];
} WIN32_FIND_DATA,  *PWIN32_FIND_DATA,  *LPWIN32_FIND_DATA;

*/
private:
  String filePath;

private:
  String fileType;

private:
  String ownerName;

private:
  String ownerDomain;

private:
  WIN32_FIND_DATA findData;


  //2009/10/18
public:
  FileAttributes()
  :filePath(_T("")),
  fileType(_T("")),
  ownerName(_T("")),
  ownerDomain(_T(""))
  {
  }

public:
  FileAttributes(__in const TCHAR* fileName)
  :filePath(fileName),
  fileType(_T("")),
  ownerName(_T("")),
  ownerDomain(_T(""))
  {
    memset(&findData, 0, sizeof(findData));

    if (fileName && exists(fileName)) {
      ;//OK

    } else {
      throw ERROR_INVALID_PARAMETER;
    }

    if (!find(fileName)) {
      throw ERROR_ACCESS_DENIED;
    }
  
    getFileType(fileName, fileType);
  
    //bool rc = 
    getFileOwner(fileName, ownerName, ownerDomain);
    //This may return false, but we ignore return value rc
  }


private:
  bool find(__in const TCHAR* fileName)
  {
    memset(&findData, 0, sizeof(findData));

    bool rc = false;
    HANDLE fFile= FindFirstFile(fileName, &findData);

    if(fFile != INVALID_HANDLE_VALUE) {

      if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        //_tprintf("FileName %s\n", findData.cFileName);
        rc = true;
      }

      FindClose(fFile);

    }
    return rc;
  }

private:
  bool getFileOwner(__in const TCHAR* fileName,
    __out String& owner, __out String& domain)
  {
    bool rc = false;


    DWORD dwSize = 0;
    GetFileSecurity(filePath, OWNER_SECURITY_INFORMATION, NULL, dwSize, &dwSize);

    PSECURITY_DESCRIPTOR psd = (PSECURITY_DESCRIPTOR)new char[dwSize];

    if (GetFileSecurity(filePath, OWNER_SECURITY_INFORMATION, psd, dwSize, &dwSize)) {
    
      PSID sid = NULL;
  
      BOOL ownerDefaulted;

      if (GetSecurityDescriptorOwner(psd, &sid, &ownerDefaulted)) {

        TCHAR accountName[MAX_PATH];
        TCHAR domainName[MAX_PATH];
        DWORD accountLen = CountOf(accountName);
        DWORD domainLen = CountOf(domainName);

        SID_NAME_USE snu;

        if (LookupAccountSid(NULL, sid, accountName, &accountLen, domainName, &domainLen, &snu)) {
          owner  = accountName;
          domain = domainName;
          rc = true;
        }
      }
    }

    delete [] (char*)psd;
    return rc;
  }


public:
  bool exists(__in const TCHAR* fileName) 
  {
    bool rc = false;
    if (GetFileAttributes(fileName) != 0xffffffff) {
      rc = true;
    }
    return rc;
  }


private:
  int getFileType(__in const TCHAR* filePath, __out String& string)
  {
    int rc = 0;

    SHFILEINFO fileInfo;

    memset(&fileInfo, 0, sizeof(fileInfo));

    if (filePath) {
    
      int rc = SHGetFileInfo(filePath, 0, &fileInfo, sizeof(SHFILEINFO),
                SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES);
      if (rc) {
        string = fileInfo.szTypeName;
      }
    }
    return rc;
  }


public:
  bool getFileKBSize(__out String& string)
  {
    bool rc = true;

    __int64 fileSizeHigh = findData.nFileSizeHigh;

    __int64 fileSizeLow  = findData.nFileSizeLow;

    __int64 fileSize = fileSizeHigh<<32 | fileSizeLow;

    TCHAR buffer[128];

    memset(buffer, (TCHAR)0, CountOf(buffer));

    StrFormatKBSize(fileSize, buffer, CountOf(buffer));
    string = buffer;

    return rc;
  }


public:
  bool getCreationTime(__out String& string)
  {
    string = _T("");
    return fileTimeToString(findData.ftCreationTime, string);
  }

public:
  bool getLastAccessTime(__out String& string)
  {
    string = _T("");
    return fileTimeToString(findData.ftLastAccessTime, string);
  }

public:
  bool getLastModifiedTime(__out String& string)
  {
    string = _T("");
    return fileTimeToString(findData.ftLastWriteTime, string);
  }

private:
  bool fileTimeToString(__in FILETIME ftFileTime, __out String& string)
  {
    bool rc = false;

    FILETIME ftLocalFileTime;
    SYSTEMTIME stFileTime;
    TCHAR fileTime[256];
    
    FileTimeToLocalFileTime(&ftFileTime , &ftLocalFileTime);
    FileTimeToSystemTime(&ftLocalFileTime , &stFileTime);

    _stprintf_s(fileTime, CountOf(fileTime), _T("%04d/%02d/%02d %02d:%02d:%02d") ,
      stFileTime.wYear , stFileTime.wMonth ,
      stFileTime.wDay , stFileTime.wHour ,
      stFileTime.wMinute , stFileTime.wSecond);

    string = fileTime;
    rc = true;

    return rc;
  }

public:
  bool getFileName(__out String& string)
  {
    bool rc = true;
    string = _T("");
    string = findData.cFileName;

    return rc;
  }

public:
  bool getOwnerName(__out String& string)
  {
    bool rc = true;
    string = "";
    string = (const TCHAR*)ownerName;

    return rc;
  }

public:
  bool getOwnerDomain(__out String& string)
  {
    bool rc = true;
    string = "";
    string = (const TCHAR*)ownerDomain;
  
    return rc;
  }

public:
  bool getFileType(__out String& string)
  {
    bool rc = true;
    string = "";
    string = (const TCHAR*)fileType;
    return rc;
  }

public:
  int getAttributes(__out String& string)
  {
  
    static const Arg types[] = {
    {_T("ARCHIVE"),    FILE_ATTRIBUTE_ARCHIVE},
    {_T("COMPRESSED"), FILE_ATTRIBUTE_COMPRESSED},
    {_T("DIRECTORY"),  FILE_ATTRIBUTE_DIRECTORY},

    {_T("ENCRYPTED"),  FILE_ATTRIBUTE_ENCRYPTED},
    {_T("HIDDEN"),     FILE_ATTRIBUTE_HIDDEN},
    {_T("NORMAL"),     FILE_ATTRIBUTE_NORMAL},
    {_T("OFFLINE"),    FILE_ATTRIBUTE_OFFLINE},
    {_T("READONLY"),   FILE_ATTRIBUTE_READONLY},
    {_T("REPARSE_POINT"), FILE_ATTRIBUTE_REPARSE_POINT},
    {_T("SPARSE_FILE"), FILE_ATTRIBUTE_SPARSE_FILE},
    {_T("SYSTEM"),     FILE_ATTRIBUTE_SYSTEM},
    {_T("TEMPORARY"),  FILE_ATTRIBUTE_TEMPORARY},
    };

    StringBuffer buffer;
    int count = XtNumber(types);
    int n = 0;    
    for (int i =0; i<count; i++) {
      if (types[i].value & findData.dwFileAttributes) {
        if (n >0) {
          buffer.append(_T(" | "));
        }
        buffer.append(types[i].name);
        n++;
      }
    }
    string = (const TCHAR*)buffer;

    return n;
  }

public:
  void display()
  {
    String name;
    getFileName(name);
    _tprintf(_T("FileName : %s\n"), (const TCHAR*)name);

    String fileSize;
    getFileKBSize(fileSize);
    _tprintf(_T("FileSize : %s\n"), (const TCHAR*)fileSize);

    String creationTime;
    getCreationTime(creationTime);
    _tprintf(_T("CreationTime : %s\n"),(const TCHAR*)creationTime);

    String lastAccessTime;
    getLastAccessTime(lastAccessTime);
    _tprintf(_T("LastAccessTime : %s\n"), (const TCHAR*)lastAccessTime);

    String lastModified;
    getLastModifiedTime(lastModified);
    _tprintf(_T("LastModified : %s\n"), (const TCHAR*)lastModified);

    String fileType;
    getFileType(fileType);
    _tprintf(_T("FileType : %s\n"), (const TCHAR*)fileType);

    String attributes;
    getAttributes(attributes);
    _tprintf(_T("Attributes : %s\n"), (const TCHAR*)attributes);

    String owner;
    getOwnerName(owner);
    _tprintf(_T("FileOwner : %s\n"), (const TCHAR*)owner);

    String domain;
    getOwnerDomain(domain);
    _tprintf(_T("OwnerDomain : %s\n"), (const TCHAR*)domain);

  }
};

}
