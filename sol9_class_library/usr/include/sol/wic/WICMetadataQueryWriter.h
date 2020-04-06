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
 *  WICMetadataQueryWriter.h
 *
 *****************************************************************************/


#pragma once

#include <sol/wic/WICImagingFactory.h>
#include <sol/wic/WICMetadataQueryReader.h>

namespace SOL {

class WICMetadataQueryWriter: public WICMetadataQueryReader
{

public:
  WICMetadataQueryWriter(IWICImagingFactory* factory, 
            __in  REFGUID guidMetadataFormat,
            __in const GUID *pguidVendor)
  :WICMetadataQueryReader()
  {
    IWICMetadataQueryWriter* writer = NULL;
    HRESULT hr = factory -> CreateQueryWriter( 
            guidMetadataFormat,
            pguidVendor,
            &writer);
    if (SUCCEEDED(hr)) {
      set(writer);
    } else  {
      throw IException("Failed to CreateQueryWriter. HRESUL(0x%lx)", hr);  
    }
  }
  
  WICMetadataQueryWriter(IWICImagingFactory* factory,
            __in IWICMetadataQueryReader *pIQueryReader,
            __in const GUID *pguidVendor)
  :WICMetadataQueryReader()
  {
    IWICMetadataQueryWriter* writer = NULL;
    HRESULT hr = factory -> CreateQueryWriterFromReader( 
            pIQueryReader,
            pguidVendor,
            &writer);
    if (SUCCEEDED(hr)) {
      set(writer);
    } else {
      throw IException("Failed to CreateQueryWriterFromReader. HRESUL(0x%lx)", hr);  
    }
  }
  
  ~WICMetadataQueryWriter()
  {
  }

  operator IWICMetadataQueryWriter*()
  {
    return getWriter();
  }

  IWICMetadataQueryWriter* getWriter()
  {
    IWICMetadataQueryWriter* writer = (IWICMetadataQueryWriter*)getIUnknown();
    if (writer) {
      return writer;
    } else {
      throw IException("IWICMetadataQueryWriter is NULL.");
    }
  }
  
  void  setMetadataByName( 
            __in  LPCWSTR wzName,
            __in  const PROPVARIANT *pvarValue)
  {
    IWICMetadataQueryWriter* writer = getWriter();
    HRESULT hr = writer -> SetMetadataByName( 
            wzName,
            pvarValue);
    if (FAILED(hr)) {
      throw IException("Failed to SetMetadataByName. HRESUL(0x%lx)", hr);
    }
  }
  
  void  removeMetadataByName( 
            __in  LPCWSTR wzName)
  {
    IWICMetadataQueryWriter* writer = getWriter();
    HRESULT hr = writer -> RemoveMetadataByName( 
            wzName);
    if (FAILED(hr)) {
      throw IException("Failed to RemoveMetadataByName. HRESUL(0x%lx)", hr);
    }
  }
};
    
}

