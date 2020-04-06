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
 *  VideoInputDeviceEnumerator.h
 *
 *****************************************************************************/

// To use this class, you have to call com initializeer, for example, CoInitializeEx(NULL, COINIT_MULTITHREADED);

#pragma once

#include <dshow.h>

#include <sol/com/ComPtr.h>
#include <sol/WString.h>
#include <sol/LinkedList.h>


#pragma comment(lib, "strmiids")

namespace SOL {
  
class VideoInputDeviceEnumerator {
private:
  
public:
  VideoInputDeviceEnumerator()
  {
  }

  ~VideoInputDeviceEnumerator()
  {
  }
  
  
  //Get a list of WString of a friendly names of a video-device.
  int enumerate(LinkedList& friendlyNames)
  {
    ComPtr<ICreateDevEnum> pDevEnum;

    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,  
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
    
    if (FAILED(hr))  {
      throw IException("Failed to create instance of SystemDeviceEnum.");
    }

    int count = 0;
    ComPtr<IEnumMoniker> pEnum;
    
    hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
    if (FAILED(hr)) {
        throw IException("Failed to create class enumerator");
    }

    IMoniker* pMoniker = NULL;

    while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
      ComPtr<IPropertyBag> pPropBag = NULL;
      HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
      if (FAILED(hr)) {
         pMoniker->Release();
         continue;  
      } 

      VARIANT var;
      VariantInit(&var);

      hr = pPropBag->Read(L"Description", &var, 0);
      if (FAILED(hr)){
        hr = pPropBag->Read(L"FriendlyName", &var, 0);
      }
      if (SUCCEEDED(hr)) {
        printf("%S\n", var.bstrVal);
        WString* wstring = new WString(var.bstrVal);
        friendlyNames.add(wstring);
        VariantClear(&var); 
        count++;
      }
      pMoniker->Release();
    }
    
    return count;
  }
};

}

