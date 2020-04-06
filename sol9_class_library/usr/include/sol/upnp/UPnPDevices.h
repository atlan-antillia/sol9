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
 *  UPnPDevices.h
 *
 *****************************************************************************/

// SOL9
// 2009/12/02
// 2012/03/07 Updated

#pragma once
#include <sol/upnp/UPnPCollection.h>
#include <sol/upnp/UPnPServices.h>
#include <sol/upnp/UPnPDevice.h>

namespace SOL {

class UPnPDevices :public UPnPCollection {

public:
  /**
   * Constructor
   */
  UPnPDevices(IDispatch* pDev=NULL)
  :UPnPCollection(pDev)
  {
  }


public:
  /**
   * Destructor
   */
  ~UPnPDevices()
  {
  }

public:
  IUPnPDevices* getDevices() 
  {
    IUPnPDevices* pDevices = (IUPnPDevices*)getIDispatch();
    return pDevices;
  }

public:
  /**
   * Extract a device specified by uniqueDevice name parameter from devices of IUPnPDevices (pDevices),
   * and return it.
   *
   */
  IUPnPDevice* getDeviceFromDeviceName(__in const wchar_t* name)
  {
    //HRESULT hr = E_FAIL;
    // Invalid arguments?
    if (name == NULL) {
      throw E_POINTER;
    }
      
    IUPnPDevice * pDevice = NULL;
      
    //IUPnPDevices* pDevices = getDevices();

    EnumVariant enumVariant = getNewEnum();

    IDispatch* pdispDevice = NULL;

    try {
      while ((pdispDevice = enumVariant.next()) !=NULL) {
        UPnPDevice dispDevice(pdispDevice);

        try {        
          pDevice = (IUPnPDevice*)dispDevice.queryInterface(IID_IUPnPDevice);

          UPnPDevice device = pDevice;          
              
          BString fname = device.getUniqueDeviceName();
          if (fname.equals(name)) {
            //OK! We found it, return pDevice breaking this loop.
            device.set(NULL); 
            break;
          }
          //If we had children of devices.      
          UPnPDevices subDevices = device.getChildren();

          // If this has children devices, do get a device of name from the children.  
          pDevice = subDevices.getDeviceFromDeviceName(name);
          
        } catch (...) {
        }
      }
    } catch (...) {

    }
            
    return pDevice;
  }

public:
  long getCount()
  {
    IUPnPDevices* pDevices = getDevices();
    long count = -1;
      HRESULT hr = pDevices->get_Count(&count);   
    if (FAILED(hr)) throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);  
    
    return count;
  }


public:
  virtual void display()
  {
    printf("UPnPDevices Count = %d\n", getCount());    
    //IUPnPDevices* pDevices = getDevices();
    //HRESULT hr = E_FAIL;

    try {
      EnumVariant enumVariant = getNewEnum();

      IDispatch * pDisp = NULL;

      while ((pDisp = enumVariant.next()) !=NULL ) {
        UPnPDevices devices = pDisp;    
                UPnPDevice upnDevice = devices.queryInterface(IID_IUPnPDevice);

        upnDevice.display();
                
        printf(".....Children\n");
        try {
          UPnPDevices subDevices = upnDevice.getChildren();
            //Display properties of children devices
          subDevices.display();

        } catch (...) {
          
        }
      }    
    } catch (...) {

    }
  }
};

}
//
