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
 *  ExcelPublisher.h
 *
 *****************************************************************************/

// class ExcelPublish can publish a MS-Excel xlsfile as a file of format of 
// 'html', 'mhtml', 'txt', 'csv', or 'ods'.

//2012/05/11
//2012/05/11 The docFile and saveFile parameters to publish method can take a full or relative path.

#include <sol/office/ExcelApplet.h>
#include <sol/office/ExcelWorkBook.h>
#include <sol/office/OfficeFileVerifier.h>

#include <sol/BString.h>
#include <sol/ArgT.h>
#include <sol/Path.h>

namespace SOL {

class ExcelPublisher :public ExcelApplet {

public:
  ExcelPublisher()
  {
    putShowWindowsInTaskbar(VARIANT_FALSE);


    putDisplayAlerts(0, VARIANT_FALSE);
    putScreenUpdating(0, VARIANT_FALSE);
  
    putVisible(0, VARIANT_FALSE);
  }

private:
  bool verifySaveFormat(const TCHAR* saveFormat,
    Excel::XlFileFormat& xformat, StringT<TCHAR>& extension)
  {
    bool rc = false;
    static ArgT<TCHAR> names[] =
    {
      {_T(".html"),    (LONG_PTR)Excel::xlHtml},
      {_T(".mhtml"),   (LONG_PTR)Excel::xlWebArchive},
      {_T(".txt"),     (LONG_PTR)Excel::xlCurrentPlatformText},
      {_T(".csv"),     (LONG_PTR)Excel::xlCSV},
      {_T(".ods"),     (LONG_PTR)Excel::xlOpenDocumentSpreadsheet},
    };

    for (int i = 0; i< CountOf(names); i++) {
      StringT<TCHAR> name = names[i].name;
      if (name.endsWithIgnoreCase(saveFormat)) {
        xformat = (Excel::XlFileFormat)names[i].value;
        extension = names[i].name;
        rc = true;
        break;
      }
    }
    if (!rc) {
      throw Exception(0, _T("Unsupported saveformat %s"), saveFormat);
    }

    return rc;
  }

public:
  bool publish(const TCHAR* docFile, const TCHAR* saveFormat)
  {
    bool rc = false;
    if (docFile == NULL || saveFormat == NULL) {
      throw Exception(0, _T("Exception: Invalid parameter to publish method")); 
    }

    OfficeFileVerifier verifier;
    if ( !(verifier.isExcelFileExtension(docFile) &&
         verifier.isOfficeFile(docFile)) ) {
      throw Exception(0, _T("Exception: Invalid Office file '%s'"), docFile ); 
    }

    try {
      StringT<TCHAR> extension;
      Excel::XlFileFormat xformat;

      verifySaveFormat(saveFormat, xformat, extension);

      Path docPath = docFile;
      String docFullPath = docPath.getFullPathName();

      BString docname = (const TCHAR*)docFullPath;

      ExcelWorkBook book = open((BSTR)docname, false);

      printf("Opened a document %S\n", (BSTR)docname);

      try {
        BString filename = docname + (const TCHAR*)extension;  
        _variant_t newfilename = (BSTR)filename;
        _variant_t format = (short)xformat;

        book.saveAs(newfilename, format);
        printf("Saved As %S\n", (BSTR)filename);

        book.close();
        printf("Closed a document\n");
        rc = true;
      } catch (...) {
        book.close();
        printf("Closed a document\n");
      }

    } catch (HRESULT hr) {
      printf("Exception %x\n", hr);
    } catch (Exception& ex) {
      ex.printf();
    } catch (...) {
      printf("Unknown Exception \n");
    }
    return rc;
  }

public:
  bool publish(const TCHAR* docFile, const TCHAR* saveFile, const TCHAR* saveFormat)
  {
    bool rc = false;
    if (docFile == NULL || saveFile == NULL || saveFormat == NULL) {
      throw Exception(0, _T("Exception: Invalid parameter to publish method")); 
    }

    OfficeFileVerifier verifier;
    if ( !(verifier.isExcelFileExtension(docFile) &&
         verifier.isOfficeFile(docFile)) ) {
      throw Exception(0, _T("Exception: Invalid Office file '%s'"), docFile ); 
    }

    try {

      StringT<TCHAR> extension;
      Excel::XlFileFormat xformat;

      verifySaveFormat(saveFormat, xformat, extension);

      Path docPath = docFile;
      String docFullPath = docPath.getFullPathName();

      Path savePath = saveFile;
      String saveFullPath = savePath.getFullPathName();

      BString docname  = (const TCHAR*)docFullPath;
      BString savename = (const TCHAR*)saveFullPath;

      ExcelWorkBook book = open((BSTR)docname, false);

      printf("Opened a document %S\n", (BSTR)docname);

      try {
        BString filename = savename;// + (const TCHAR*)extension;  
        _variant_t newfilename = (BSTR)filename;
        _variant_t format = (short)xformat;

        //HRESULT hr = 
        book.saveAs(newfilename, format);
        printf("Saved As %S\n", (BSTR)filename);

        book.close();
        printf("Closed a document\n");

        rc = true;
      } catch (...) {
        book.close();
        printf("Closed a document\n");
      }
    } catch (HRESULT hr) {
      printf("Exception %x\n", hr);
    } catch (Exception& ex) {
      ex.printf();
    } catch (...) {
      printf("Unknown Exception \n");
    }
    return rc;
  }

};

}

