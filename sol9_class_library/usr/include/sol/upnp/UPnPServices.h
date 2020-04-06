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
 *  UPnPServices.h
 *
 *****************************************************************************/

// SOL9
// 2009/12/02
// 2012/03/07 Updated

#pragma once
#include <sol/upnp/UPnPService.h>
#include <sol/upnp/UPnPCollection.h>

namespace SOL {

class UPnPServices :public UPnPCollection {


public:
  UPnPServices(IDispatch* pServ=NULL)
  :UPnPCollection(pServ)
  {
  }

public:
  IUPnPServices* getServices() 
  {
    IUPnPServices* pServices = (IUPnPServices*)getIDispatch();
    if (pServices == NULL) throw NullPointerException("IUPnPServices is NULL");

    return pServices;
  }

public:
  long getCount()
  {
    IUPnPServices* pServices = getServices();
    long count = -1;
    HRESULT hr = pServices->get_Count(&count); 
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);  
    }
    return count;
  }

public:
  void display()
  {
    printf("UPnPServices Count = %d\n", getCount());

    //IUPnPServices* pDevices = getServices();
    
    //HRESULT hr = E_FAIL;
        
    try {
      EnumVariant enumVariant = getNewEnum();

      IDispatch* pDisp = NULL;
      while ((pDisp = enumVariant.next()) !=NULL) {
        try {
          ComObject dispService = pDisp;
        
          UPnPService service = dispService.queryInterface(IID_IUPnPService);
          service.display();

        } catch (...) {

        }
      }
    } catch (...) {

    }
  }
};

}
