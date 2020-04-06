/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WICMetadataQueryReader.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>

namespace SOL {

class WICMetadataQueryReader: public ComIUnknown
{
public:
  WICMetadataQueryReader()
  :ComIUnknown()
  {
  }
  
public:
  WICMetadataQueryReader(IWICBitmapDecoder* decoder)
  :ComIUnknown()
  {  
    IWICMetadataQueryReader* reader = NULL;
  	HRESULT hr = decoder -> GetMetadataQueryReader(
            &reader);
    if (SUCCEEDED(hr)) {
      set(reader);
    } else {
      throw IException("Failed to GetMetadataQueryReader. HRESULT(0x%lx)", hr);  
    }
  }
  
	
  ~WICMetadataQueryReader()
  {
  }

  operator IWICMetadataQueryReader*()
  {
    return getReader();
  }
  
  IWICMetadataQueryReader* getReader()
  {
    IWICMetadataQueryReader* reader = (IWICMetadataQueryReader*)getIUnknown();
    if (reader) {
      return reader;
    } else {
      throw IException("IWICMetadataQueryReader is NULL.");
    }
  }

  void getContainerFormat( 
            __out GUID *pguidContainerFormat)
  {
    IWICMetadataQueryReader* reader = getReader();
    HRESULT hr = reader -> GetContainerFormat( 
            pguidContainerFormat);
    if (FAILED(hr)) {
      throw IException("Failed to GetContainerFormat. HRESULT(0x%lx)", hr);
    }
  }
  
  void getLocation( 
            __in UINT cchMaxLength,
            __in WCHAR *wzNamespace,
            __out UINT *pcchActualLength)
  {
    IWICMetadataQueryReader* reader = getReader();
    HRESULT hr = reader -> GetLocation( 
            cchMaxLength,
            wzNamespace,
            pcchActualLength);
    if (FAILED(hr)) {
      throw IException("Failed to GetLocation. HRESULT(0x%lx)", hr);
    }
  }
        
  void getMetadataByName( 
            __in LPCWSTR wzName,
            __in PROPVARIANT *pvarValue)
  {
    IWICMetadataQueryReader* reader = getReader();
    HRESULT hr = reader -> GetMetadataByName( 
            wzName,
            pvarValue);
    if (FAILED(hr)) {
      throw IException("Failed to GetMetadataByName. HRESULT(0x%lx)", hr);
    }
  }
        
  void getEnumerator( 
            __out IEnumString **ppIEnumString)
  {
    IWICMetadataQueryReader* reader = getReader();
    HRESULT hr = reader -> GetEnumerator( 
            ppIEnumString);
    if (FAILED(hr)) {
      throw IException("Failed to GetEnumerator. HRESULT(0x%lx)", hr);
    }
  }
};
    
}

