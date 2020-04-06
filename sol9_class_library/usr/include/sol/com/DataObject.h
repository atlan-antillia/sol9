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
 *  DataObject.h
 *
 *****************************************************************************/


// 2012/10/30

#pragma once
#include <sol/com/ComIUnknown.h>
#include <objidl.h>

namespace SOL {

class DataObject: public ComIUnknown {
    
public:
  DataObject(IDataObject* pData)
  :ComIUnknown(pData)
  {
  }

public:
  IDataObject* getObject()
  {
    return (IDataObject*)getIUnknown();
  }


public:
  HRESULT getData( 
            /* [in] */ FORMATETC *pformatetcIn,
            /* [out] */ STGMEDIUM *pmedium)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> GetData( 
            pformatetcIn,
            pmedium);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  STGMEDIUM getData( 
            /* [in] */ FORMATETC *pformatetcIn)
  {
    STGMEDIUM medium;
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> GetData( 
            pformatetcIn,
            &medium);
    if (FAILED(hr)) {
      throw hr;
    }
    return medium;
  }

  virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [unique][in] */ FORMATETC *pformatetcIn,
            /* [out] */ STGMEDIUM *pmedium) = 0;
        

public:
  HRESULT getDataHere( 
            /* [in] */ FORMATETC *pformatetc,
            /* [out][in] */ STGMEDIUM *pmedium)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> GetDataHere( 
            pformatetc,
            pmedium);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
  
public:
  STGMEDIUM getDataHere( 
            /* [in] */ FORMATETC *pformatetc)
  {
    STGMEDIUM medium;
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> GetDataHere( 
            pformatetc,
            &medium);
    if (FAILED(hr)) {
      throw hr;
    }
    return medium;
  }
  
        
public:
  HRESULT  queryGetData( 
            /* [in] */ FORMATETC *pformatetc)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> QueryGetData( 
            pformatetc);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  HRESULT getCanonicalFormatEtc( 
            /* [in] */ FORMATETC *pformatectIn,
            /* [out] */ FORMATETC *pformatetcOut)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> GetCanonicalFormatEtc( 
            pformatectIn,
            pformatetcOut);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  FORMATETC getCanonicalFormatEtc( 
            /* [in] */ FORMATETC *pformatectIn)
  {
    FORMATETC formatetcOut;
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> GetCanonicalFormatEtc( 
            pformatectIn,
            &formatetcOut);
    if (FAILED(hr)) {
      throw hr;
    }
    return formatetcOut;
  }


public:
  HRESULT setData( 
            /* [in] */ FORMATETC *pformatetc,
            /* [in] */ STGMEDIUM *pmedium,
            /* [in] */ BOOL fRelease)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> SetData( 
            pformatetc,
            pmedium,
            fRelease);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
  virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetData( 
            /* [unique][in] */ FORMATETC *pformatetc,
            /* [unique][in] */ STGMEDIUM *pmedium,
            /* [in] */ BOOL fRelease) = 0;
        
public:
  HRESULT  enumFormatEtc( 
            /* [in] */ DWORD dwDirection,
            /* [out] */ IEnumFORMATETC **ppenumFormatEtc)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject ->  EnumFormatEtc( 
            dwDirection,
            ppenumFormatEtc);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }


public:
  IEnumFORMATETC* enumFormatEtc( 
            /* [in] */ DWORD dwDirection)
  {
    IEnumFORMATETC* pFormatEtc = NULL;
    IDataObject* pObject = getObject();
    HRESULT hr = pObject ->  EnumFormatEtc( 
            dwDirection,
            &pFormatEtc);
    if (FAILED(hr)) {
      throw hr;
    }
    return pFormatEtc;
  }
        
public:
  HRESULT dAdvise( 
            /* [in] */ FORMATETC *pformatetc,
            /* [in] */ DWORD advf,
            /* [in] */ IAdviseSink *pAdvSink,
            /* [out] */ DWORD *pdwConnection)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> DAdvise( 
            pformatetc,
            advf,
            pAdvSink,
          pdwConnection);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }

public:
  DWORD dAdvise( 
            /* [in] */ FORMATETC *pformatetc,
            /* [in] */ DWORD advf,
            /* [in] */ IAdviseSink *pAdvSink)
  {
    DWORD dwConnection = 0;
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> DAdvise( 
            pformatetc,
            advf,
            pAdvSink,
          &dwConnection);
    if (FAILED(hr)) {
      throw hr;
    }
    return dwConnection;
  }

        
public:
  HRESULT DUnadvise( 
            /* [in] */ DWORD dwConnection)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> DUnadvise(dwConnection);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
        virtual HRESULT STDMETHODCALLTYPE DUnadvise( 
            /* [in] */ DWORD dwConnection) = 0;
        
public:
  HRESULT enumDAdvise( 
            /* [out] */ IEnumSTATDATA **ppenumAdvise)
  {
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> EnumDAdvise( 
            ppenumAdvise);
    if (FAILED(hr)) {
      throw hr;
    }
    return hr;
  }
     
public:
  IEnumSTATDATA* enumDAdvise()
  {
    IEnumSTATDATA* pData = NULL;
    IDataObject* pObject = getObject();
    HRESULT hr = pObject -> EnumDAdvise( 
            &pData);
    if (FAILED(hr)) {
      throw hr;
    }
    return pData;
  }  
    
};

}

