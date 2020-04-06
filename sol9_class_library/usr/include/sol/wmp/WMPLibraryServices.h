/******************************************************************************
 *
 * Copyright(c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  WMPLibraryServices.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>

namespace SOL {

class WMPLibraryServices :public WMPObject {

private:
  IWMPLibraryServicesPtr services;

public:
  WMPLibraryServices()
  :services(NULL)
  {
  }

public:
  WMPLibraryServices(IWMPLibraryServicesPtr ptr)
  :services(ptr)
  {
    if(ptr == NULL) {
      throw NullPointerException("IWMPLibraryServicesPtr is NULL", 0);
    }
  }

public:
  ~WMPLibraryServices()
  {
    services = NULL;
  }

public:
  void set(IWMPLibraryServices* serv)
  {
    services = serv;
  }

/*
enum WMPLibraryType
{
    wmpltUnknown = 0,
    wmpltAll = 1,
    wmpltLocal = 2,
    wmpltRemote = 3,
    wmpltDisc = 4,
    wmpltPortableDevice = 5
};
*/
public:
  
  long getCountByType(enum WMPLibraryType wmplt)
  {    
    return services->getCountByType(wmplt);
  }

public:  
  long getAllLibraryCount()
  {    
    return services->getCountByType(wmpltAll);
  }

public:  
  long getLocalLibraryCount()
  {    
    return services->getCountByType(wmpltLocal);
  }

public:  
  long getRemoteLibraryCount()
  {    
    return services->getCountByType(wmpltRemote);
  }

public:  
  long getPortableDeviceLibraryCount()
  {    
    return services->getCountByType(wmpltPortableDevice);
  }

public:  
  long getDiscLibraryCount()
  {    
    return services->getCountByType(wmpltDisc);
  }

public:

  IWMPLibraryPtr getLibraryByType(enum WMPLibraryType wmplt,long lIndex)
  {
    return services->getLibraryByType(wmplt,
      lIndex);
  }

public:
  IWMPLibraryPtr getAllLibrary(long lIndex = 0)
  {
    return services->getLibraryByType( wmpltAll,
      lIndex);
  }
public:
  IWMPLibraryPtr getLocalLibrary(long lIndex = 0)
  {
    return services->getLibraryByType(wmpltLocal,
      lIndex);
  }

public:
  IWMPLibraryPtr getDiscLibrary(long lIndex = 0)
  {
    return services->getLibraryByType(wmpltDisc,
      lIndex);
  }

public:
  IWMPLibraryPtr getPortableDeviceLibrary(long lIndex = 0)
  {
    return services->getLibraryByType(wmpltPortableDevice,
      lIndex);
  }
};


}
