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
 *  OfficeApplet.h
 *
 *****************************************************************************/

//2010/04/06
//2011/09/06 Updated for Office2010
//2015/12/30 Modified to be compile for Office 2013 for Desktop.

#pragma once

#include <sol/Object.h>


//2011/09/06
//2015/12/25
#ifndef WIN64
#ifdef OFFICE2013
#import "C:\Program Files (x86)\Common Files\Microsoft Shared\OFFICE15\MSO.DLL" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("SearchPath", "SeachPathXL")
  
#elif OFFICE2010
#import "C:\Program Files (x86)\Common Files\Microsoft Shared\OFFICE14\MSO.DLL" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("SearchPath", "SeachPathXL")

#else 
#import "C:\Program Files (x86)\Common Files\Microsoft Shared\OFFICE12\MSO.DLL" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("SearchPath", "SeachPathXL")

#endif

#else
#ifdef OFFICE2013
#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE15\MSO.DLL" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("SearchPath", "SeachPathXL")

#elif OFFICE2010
#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE14\MSO.DLL" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("SearchPath", "SeachPathXL")

#else 
#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("SearchPath", "SeachPathXL")
  
#endif

#endif

//2015/12/30
// 32bit Visual Basic for Application
#import "C:\Program Files (x86)\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" 

namespace SOL {

class OfficeApplet :public Object {

public:
  OfficeApplet()
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw hr;
    }
  }

public:
  ~OfficeApplet()
  {
    OleUninitialize();
  }

public:
  
  bool getActiveObject(const wchar_t* application, IDispatch** ppDisp) 
  { 
  
    _bstr_t name = application;
    printf( "OfficeApplication#getActiveObject,1,Start,Application=%s",
      (const char*)name);

    bool rc = false;
    CLSID clsid;
    CLSIDFromProgID(application, &clsid);

    IUnknown *pUnk = NULL;
    *ppDisp = NULL;

    HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);
    if(SUCCEEDED(hr)) {
      hr = pUnk->QueryInterface(IID_IDispatch, (void **)ppDisp);
      
      pUnk->Release();

      if (SUCCEEDED(hr)) {
        rc = true;
      } else {
        printf( "OfficeApplet#getActiveObject,1,Not found an interface for active Object for =%s\n",
        (const char*)name);
      }
    } else {
      printf( "OfficeApplet#getActiveObject,2,Failed to GetActiveObject for Application=%s\n",
        (const char*)name);
  
    }
    return rc;
  }

};

}


