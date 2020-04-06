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
 *  ArgList.h
 *
 *****************************************************************************/


// SOL9
// 2009/09/25

#pragma once

#include <sol/String.h>
#include <sol/pdh/PdhObject.h>


namespace SOL {

class PerformanceCounterPath :public PdhObject {

private:

  PDH_COUNTER_PATH_ELEMENTS elements;

public:
  PerformanceCounterPath()
  {
    clear();
  }

public:
  void clear()
  {
    memset(&elements, 0, sizeof(elements));
  }


public:
  PDH_STATUS make(__out String& path,
      __in const TCHAR* machineName, 
      __in const TCHAR* objectName,
      __in const TCHAR* counterName,
      __in const TCHAR* instanceName = NULL,
      __in const int  instanceIndex = -1)
  {    
    clear();

    elements.szMachineName    = (TCHAR*)machineName;

        elements.szObjectName     = (TCHAR*)objectName;
    elements.szCounterName    = (TCHAR*)counterName;

        
    elements.dwInstanceIndex  = instanceIndex;

    elements.szInstanceName   = (TCHAR*)instanceName;

    TCHAR buffer[1024];
    memset(buffer, (TCHAR)0, CountOf(buffer));    

    DWORD dwSize = CountOf(buffer);

    PDH_STATUS status = PdhMakeCounterPath(&elements, buffer,
                                           &dwSize, 0);
    if (status == ERROR_SUCCESS) {
      path = buffer;
    } else {
      throw (int)status;
    }

    return status;
  }

};

}
