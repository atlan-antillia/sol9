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
 *  FileVersion.h
 *
 *****************************************************************************/

// SOL9
// 2008/12/16
// 2009/05/30
// 2009/10/05 Added a new method hasVersionInfo().

#pragma once
 
#include <sol\Object.h>
#include <sol\String.h>
#include <sol\StringT.h>

#include <sol\StringConverter.h>
#include <sol/FileWriter.h>
#include <sol/HTMLEncoder.h>

namespace SOL
{

typedef struct
{
    WORD wLanguage;
    WORD wCodePage;
} LANGANDCODEPAGE, *LPLANGANDCODEPAGE;


class FileVersion :public Object {

private:
  char* verInfo;

private:
  LPLANGANDCODEPAGE langCode;

private:
  UINT lcCount;

private:
  UINT unLen;

private:
  String filePath;

  String program;

  String comments;

  String companyName;

  String fileDescription;

  String fileVersion;

  String internalName;

  String legalCopyRight;

  String legalTrademarks;

  String originalFilename;

  String productName;

  String productVersion;

  String privateBuild;

  String specialBuild;

public:
  /**
   * Constructor
   */
  FileVersion(const TCHAR* path=NULL)
    :verInfo(NULL),
    langCode(NULL),
    unLen(0),
    lcCount(0),
    program(_T(""))

  {
    if (path ) {
      filePath = path;
    } else {
      TCHAR fileName[_MAX_PATH];
      memset(fileName, (TCHAR)0, CountOf(fileName));
      GetModuleFileName(NULL, fileName, _MAX_PATH);
      filePath = fileName;    
    }

    TCHAR drive[MAX_PATH];
    memset(drive, (TCHAR)0, CountOf(drive));

    TCHAR folder[MAX_PATH];
    memset(folder, (TCHAR)0, CountOf(folder));

    TCHAR name[MAX_PATH];
    memset(name, (TCHAR)0, CountOf(name));

    TCHAR extension[MAX_PATH];
    memset(extension, (TCHAR)0, CountOf(extension));

    _splitpath_s((const TCHAR*)filePath, drive, CountOf(drive),
      folder, CountOf(folder), name, CountOf(name),
      extension, CountOf(extension));
    this->program = name;
  
    DWORD dwSize = GetFileVersionInfoSize((const TCHAR*)filePath, NULL);

    if ( dwSize <= 0) {  
      return;
    }

    verInfo = new char[dwSize];
    memset(verInfo, 0x0, dwSize);

    if (GetFileVersionInfo((const TCHAR*)filePath, 0, dwSize, verInfo) == FALSE){  
      delete [] verInfo;
      verInfo = NULL;
      return;
    } 

    UINT unLen;
    if (VerQueryValue(verInfo, _T("\\VarFileInfo\\Translation"), 
      (LPVOID*)&langCode, &unLen) == FALSE) {

      delete [] verInfo;
      verInfo = NULL;
      return;
    } 

    this->lcCount = unLen / sizeof(LANGANDCODEPAGE);

    comments = _T("");
    companyName = _T("");
    fileDescription = _T("");
    fileVersion = _T("");
    internalName = _T("");
    legalCopyRight = _T("");
    legalTrademarks = _T("");
    originalFilename = _T("");
    productName = _T("");
    productVersion = _T("");
    privateBuild = _T("");
    specialBuild = _T("");
  
    getValue(_T("Comments"), comments);

    getValue(_T("CompanyName"), companyName);

    getValue(_T("FileDescription"), fileDescription);

    getValue(_T("FileVersion"), fileVersion);

    getValue(_T("InternalName"), internalName);

    getValue(_T("LegalCopyRight"), legalCopyRight);

    getValue(_T("LegalTrademarks"), legalTrademarks);
    
    getValue(_T("OriginalFilename"), originalFilename);

    getValue(_T("ProductName"), productName);

    getValue(_T("ProductVersion"), productVersion);

    getValue(_T("PrivateBuild"), privateBuild);

    getValue(_T("SpecialBuild"), privateBuild);

  }

public:
  /**
   * Destructor
   */
  ~FileVersion() {
    if (verInfo) {
      delete [] verInfo;
      verInfo = NULL;
      langCode = NULL;
      unLen = 0;
      lcCount = 0;
    }
  }  

public:
  //2009/10/05
  bool hasVersionInfo()
  {
    bool rc = false;
    if (verInfo) {
      rc = true;
    }
    return rc;
  }

public:
  const TCHAR* getProgramName() {
    return (const TCHAR*)program;
  }


private:
  bool getValue(const TCHAR* keyword, String& val) {
    bool rc = false;
    char* value = NULL;
    TCHAR query[1024];
    UINT unLen = 0;

    for (uint i = 0; i<lcCount; i++) {
      _stprintf_s(query, CountOf(query),
              _T("\\StringFileInfo\\%04x%04x\\%s"), 
        langCode[i].wLanguage, langCode[i].wCodePage, keyword);
      //_tprintf(_T("Query %s\n"), query);

      if (verInfo) {  
            VerQueryValue(verInfo, query, 
          (LPVOID*)&value, &unLen); 
        if (unLen > 0) {
          StringConverter converter;
          StringT<TCHAR> tstring;
          converter.convert(value, tstring);
          val = (const TCHAR*)value;
          rc = true;
          break;
        }
      }
    }
    return rc;
  }

public:
  const TCHAR*  getComments() { return (const TCHAR*)comments; }

  const TCHAR*  getCompanyName() { return (const TCHAR*)companyName; }

  const TCHAR*  getFileDescription() { return (const TCHAR*)fileDescription; }

  const TCHAR*  getFileVersion() { return (const TCHAR*)fileVersion; }

  const TCHAR*  getInternalName() { return (const TCHAR*)internalName; }

  const TCHAR*  getLegalCopyRight() { return (const TCHAR*)legalCopyRight; }

  const TCHAR*  getLegalTrademarks() { return (const TCHAR*)legalTrademarks; }
    
  const TCHAR*  getOriginalFilename() { return (const TCHAR*)originalFilename; }

  const TCHAR*  getProductName() { return (const TCHAR*)productName; }

  const TCHAR*  getProductVersion() { return (const TCHAR*)productVersion; }

  const TCHAR*  getPrivateBuild() { return (const TCHAR*)privateBuild; }

  const TCHAR*  getSpecialBuild() { return (const TCHAR*)privateBuild; }


public:
  void write(Writer& writer)
  {
    _bstr_t comments = getComments();
    _bstr_t companyName = getCompanyName();
    _bstr_t desc = getFileDescription();
    _bstr_t version = getFileVersion();
    _bstr_t internalName = getInternalName();
    _bstr_t legalCopyRight = getLegalCopyRight();
    _bstr_t legalTradeMark = getLegalTrademarks();
    _bstr_t originalFileName = getOriginalFilename();
    _bstr_t productName = getProductName();
    _bstr_t productVersion = getProductVersion();
    _bstr_t privateBuild = getPrivateBuild();
    _bstr_t specialBuild = getSpecialBuild();

    /*HTMLEncoder encoder;
    _bstr_t encDesc;
    encoder.encode(desc, encDesc);
    */

    writer.writeln(L"<FileVersion>");
    writer.writeln(L"<Comment>%s</Comment>", (const wchar_t*)comments);
    writer.writeln(L"<CompanyName>%s</CompanyName>", (const wchar_t*)companyName);
    writer.writeln(L"<FileDescription>%s</FileDescription>", (const wchar_t*)desc);
    writer.writeln(L"<FileVersion>%s</FileVersion>", (const wchar_t*)version);
    writer.writeln(L"<InternalName>%s</InternalName>", (const wchar_t*)internalName);
    writer.writeln(L"<LegalCopyRight>%s</LegalCopyRight>", (const wchar_t*)legalCopyRight);
    writer.writeln(L"<LegalTradeMark>%s</LegalTradeMark>", (const wchar_t*)legalTradeMark);
    writer.writeln(L"<OriginalFileName>%s</OriginalFileName>", (const wchar_t*)originalFileName);
    writer.writeln(L"<ProductName>%s</ProductName>", (const wchar_t*)productName);
    writer.writeln(L"<ProductVersion>%s</ProductVersion>", (const wchar_t*)productVersion);
    writer.writeln(L"<PrivateBuild>%s</PrivateBuild>", (const wchar_t*)privateBuild);
    writer.writeln(L"<SpecialBuild>%s</SpecialBuild>", (const wchar_t*)specialBuild);

    writer.writeln(L"</FileVersion>");

  }

};

}

  
