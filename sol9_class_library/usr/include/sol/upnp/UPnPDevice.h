/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  UPnPDevice.h
 *
 *****************************************************************************/

// SOL9
// 2009/12/02
// 2012/03/07 Updated

#pragma once
#include <sol/upnp/UPnPObject.h>
#include <sol/upnp/UPnPServices.h>

namespace SOL {

class UPnPDevice :public UPnPObject {

public:
  UPnPDevice(IDispatch* pDev=NULL)
  :UPnPObject(pDev)
  {

  }

public:
  ~UPnPDevice()
  {
  }


public:
  IUPnPDevice* getDevice()
  {
    IUPnPDevice* pDevice = (IUPnPDevice*)getIDispatch();

    return pDevice;
  }


public:
  BString getUniqueDeviceName()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();
    HRESULT hr = pDevice->get_UniqueDeviceName(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }

public:
  BString getModelName()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_ModelName(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }

public:
  BString getDescription()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_Description(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }


public:
  BString getFriendlyName()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_FriendlyName(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }


public:
  BString getManufacturerURL()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_ManufacturerURL(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }

public:
  BString getType()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_Type(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }

public:
  BString getModelNumber()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_ModelNumber(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }

public:
  BString getModelURL()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_ModelURL(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }


public:
  BString getManufacturerName()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_ManufacturerName(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }


public:
  BString getSerialNumber()
  {
     BSTR name = NULL;
    IUPnPDevice* pDevice = getDevice();

    HRESULT hr = pDevice->get_SerialNumber(&name);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return BString(name, false);
  }



public:
  HRESULT getServices(UPnPServices& services)
  {
    HRESULT hr = E_FAIL;
    IUPnPServices* pServices;
    printf(".......Services\n");
    IUPnPDevice* pDevice = getDevice();
        
    if (SUCCEEDED(hr=pDevice->get_Services(&pServices))  )
    {  
      services.set(pServices);
      //services.display();
    }
    return hr;
  }                

public:
  IUPnPServices* getServices()
  {
    printf(".......Services\n");
    IUPnPDevice* pDevice = getDevice();
    IUPnPServices* pServices = NULL;
    HRESULT  hr = pDevice->get_Services(&pServices);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);

    return pServices;
  }    

public:
  IUPnPDevices* getChildren()
  {  
    IUPnPDevices* pChildren = NULL;

    IUPnPDevice* pDevice = getDevice();
    HRESULT  hr = pDevice->get_Children(&pChildren);
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);  

    return pChildren;
  }

public:
  bool hasChildren()
  {
    bool rc = false;
    IUPnPDevice* pDevice = getDevice();

    VARIANT_BOOL variant_bool = VARIANT_FALSE;
    if (SUCCEEDED(pDevice->get_HasChildren(&variant_bool))) {
      if (variant_bool == VARIANT_TRUE) {
          rc = true;
      }
    }
    return rc;
  }

public:
  virtual void display()
  {
    printf("UPnPDevice \n");

    
    wprintf(L"UniqueDeviceName: %s\n", (const wchar_t*)getUniqueDeviceName());
            
    wprintf(L"ModelName: %s\n", (const wchar_t*)getModelName());
        
    wprintf(L"Description: %s\n", (const wchar_t*)getDescription());

    wprintf(L"FriendlyName: %s\n", (const wchar_t*)getFriendlyName());
            
    wprintf(L"ManufacturerURL: %s\n", (const wchar_t*)getManufacturerURL());

    wprintf(L"ManufacturerName: %s\n", (const wchar_t*)getManufacturerName());
          
    wprintf(L"SerialNumber: %s\n", (const wchar_t*)getSerialNumber());


//    IUPnPServices* pServices;
    printf("Services\n");
    UPnPServices services;    
  //  if (SUCCEEDED(pDevice->get_Services(&pServices)) ){
    if (SUCCEEDED(getServices(services)) ){
      services.display();
    }
  }
};

}
