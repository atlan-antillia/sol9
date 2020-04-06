/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  StorageProperty.h
 *
 *****************************************************************************/

// SOL9

#pragma once
// 2010/05/30

#include <sol/Object.h>
#include <sol/StringConverter.h>


namespace SOL {
  
class StorageProperty :public Object {

private:
  IStorage      *pStorage;

  IPropertySetStorage *pPropSetStg;

public:
  /** 
   * Constructor
   */
  StorageProperty(const wchar_t* wcFilename)
    :pStorage(NULL),
    pPropSetStg(NULL)
  {     
    // Open the document as an OLE compound document.
    HRESULT hr = StgOpenStorage(wcFilename, NULL,
      STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0, &pStorage);

    if(FAILED(hr)) {
      throw hr;
    } else {
      hr = pStorage->QueryInterface(IID_IPropertySetStorage, (void **)&pPropSetStg);  
      if(FAILED(hr)) {
        throw hr;
      }
    }
  }

public:
  /**
   * Destructor
   */
  ~StorageProperty() {
    if (pPropSetStg != NULL) {
      pPropSetStg->Release();
      pPropSetStg = NULL;
    }
    if (pStorage != NULL) {
      pStorage->Release();
      pStorage = NULL;
    }
  }


public:
  HRESULT getTitle(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_TITLE, string);  
  }

  HRESULT getSubject(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_SUBJECT, string);      
  }
 
  HRESULT getKeywords(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_KEYWORDS, string);      
  }
  
  HRESULT getComments(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_COMMENTS, string);      
  }

  HRESULT getTemplate(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_TEMPLATE, string);      
  }

  HRESULT getRevisionNumber(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_REVNUMBER, string);      
  }

  HRESULT getAuthor(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_AUTHOR, string);      
  }

  HRESULT getLastAuthor(_bstr_t& string) {
    return getProperty(FMTID_SummaryInformation, PIDSI_LASTAUTHOR, string);      
  }

  HRESULT getEditTime(SYSTEMTIME& systemTime) {
    return getProperty(FMTID_SummaryInformation, PIDSI_EDITTIME, systemTime);      
  }

  HRESULT getCreatedDateTime(SYSTEMTIME& systemTime) {
    return getProperty(FMTID_SummaryInformation, PIDSI_CREATE_DTM, systemTime);      
  }

  HRESULT getLastSavedDateTime(SYSTEMTIME& systemTime) {
    return getProperty(FMTID_SummaryInformation, PIDSI_LASTSAVE_DTM, systemTime);      
  }

  HRESULT getPageCount(int& value) {
    return getProperty(FMTID_SummaryInformation, PIDSI_PAGECOUNT, value);      
  }

  HRESULT getWordCount(int& value) {
    return getProperty(FMTID_SummaryInformation, PIDSI_WORDCOUNT, value);      
  }

  HRESULT getCharCount(int& value) {
    return getProperty(FMTID_SummaryInformation, PIDSI_CHARCOUNT, value);      
  }

  HRESULT getAppName(_bstr_t& value) {
    return getProperty(FMTID_SummaryInformation, PIDSI_APPNAME, value);      
  }

  HRESULT getLineCount(int& value) {
    return getProperty(FMTID_DocSummaryInformation, PIDDSI_LINECOUNT, value);
  }

  HRESULT getParagraphCount(int& value) {
    return getProperty(FMTID_DocSummaryInformation, PIDDSI_PARCOUNT, value);

  }

  HRESULT getCompany(_bstr_t& value) {
    return getProperty(FMTID_DocSummaryInformation, PIDDSI_COMPANY, value);
  }

public:
  
  HRESULT getProperty(__in REFFMTID formatId, __in long propId, __out _bstr_t& string) {
    IPropertyStorage *pPropStg = NULL;
 
    HRESULT hr = this->pPropSetStg->Open(formatId,
      STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
  
    if(FAILED(hr)) {
      return hr;
    }
    PROPSPEC    pPropSpec[1];
    PROPVARIANT pPropVar[1]; 

    ZeroMemory(&pPropSpec[0], sizeof(PROPSPEC));
    pPropSpec[0].ulKind = PRSPEC_PROPID;
    pPropSpec[0].propid = propId;
    
    // Read properties.
    hr = pPropStg->ReadMultiple(1, pPropSpec, pPropVar);
    if (!FAILED(hr)) {  
      wchar_t* wstring = NULL;
      if (toString(pPropVar, &wstring)) {
        hr = S_OK;
        string = wstring;
        delete [] wstring;
      } else {
        hr = E_FAIL;
      }
    }
    pPropStg->Release();

    return hr;
  }

public:
  HRESULT getProperty(__in REFFMTID formatId, __in long propId, __out SYSTEMTIME& lst) {
    IPropertyStorage *pPropStg = NULL;
 
     HRESULT hr = this->pPropSetStg->Open(formatId, 
      STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
  
    if(FAILED(hr)) {
      return hr;
    }
    PROPSPEC    pPropSpec[1];
    PROPVARIANT pPropVar[1]; 

    ZeroMemory(&pPropSpec[0], sizeof(PROPSPEC));
    pPropSpec[0].ulKind = PRSPEC_PROPID;
    pPropSpec[0].propid = propId;
    
    // Read properties.
    hr = pPropStg->ReadMultiple(1, pPropSpec, pPropVar);
    if (!FAILED(hr)) {  
      if (toSystemTime(pPropVar, lst)) {
        hr = S_OK;
      } else {
        hr = E_FAIL;
      }
    }
    pPropStg->Release();

    return hr;
   }


public:
  HRESULT getProperty(__in REFFMTID formatId, __in long propId, __out int& value) {
    IPropertyStorage *pPropStg = NULL;
 
    HRESULT hr = this->pPropSetStg->Open(formatId,
      STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
  
    if(FAILED(hr)) {
      return hr;
    }
    PROPSPEC    pPropSpec[1];
    PROPVARIANT pPropVar[1]; 

    ZeroMemory(&pPropSpec[0], sizeof(PROPSPEC));
    pPropSpec[0].ulKind = PRSPEC_PROPID;
    pPropSpec[0].propid = propId;
    
    // Read properties.
    hr = pPropStg->ReadMultiple(1, pPropSpec, pPropVar);
    if (!FAILED(hr)) {  
      int x;
      if (toInteger(pPropVar, &x)) {
        value  =x;
        hr = S_OK;
      } else {
        hr = E_FAIL;
      }
    }
    pPropStg->Release();
    return hr;
   }


private:
  bool toSystemTime(PROPVARIANT *pPropVar, SYSTEMTIME& lst) {
    bool rc = false;
 
    switch(pPropVar->vt) {
 
    case VT_FILETIME:
    {
            FILETIME lft;
            FileTimeToLocalFileTime(&pPropVar->filetime, &lft);                
            FileTimeToSystemTime(&lft, &lst);
      
      rc = true;
     }
         break;

    default:
      rc = false;
    }
    return rc;
  }

private:
  bool toInteger(PROPVARIANT *pPropVar, int* value) {
    bool rc = true;
      
    switch(pPropVar->vt) {
    
    case VT_BOOL:     
      if (pPropVar->boolVal == TRUE) {
        *value = 1;
       } else {
        *value = 0;
       }
      rc = true;
           break;

      
    case VT_I2: // 2-byte signed int.
          *value = (int)pPropVar->iVal;
       rc = true;
       break;

        case VT_I4: // 4-byte signed int.
           *value = (int)pPropVar->lVal;
      rc = true;
          break;

      default:
      rc = false;
      break;
    }
    return rc;
  }

private:
  bool toString(PROPVARIANT *pPropVar, wchar_t** wstring) {
    bool rc = true;

    switch(pPropVar->vt) {

    case VT_BSTR: 
    {
      wchar_t* bstr = (wchar_t*)pPropVar->bstrVal;
      int len = SysStringLen(pPropVar->bstrVa);

      wchar_t* temp = new wchar_t[len + 1];
      if (temp) {
        wmemcpy(temp, bstr, len);
        temp[len] = '\0';
        *wstring = temp;
         rc = true;
      }
         }
         break;

      
    case VT_LPSTR: // Null-terminated string.
    {
      StringConverter converter;

      *wstring = conveter.toWideChar(pPropVar->pszVal);
      rc = true;
    }
    break;
      
    default:
      rc = false;
          break;
    }
      return rc;
  }

};

}
