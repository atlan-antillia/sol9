/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  PerformanceQuery.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/25

#pragma once

#include <sol/pdh/PdhObject.h>
#include <sol/pdh/PerformanceCounter.h>

namespace SOL {

class PerformanceQuery :public PdhObject {

private:
  HQUERY hQuery;

public:
  PerformanceQuery()
  :hQuery(NULL)
  {
    PDH_STATUS status = PdhOpenQuery(NULL, 0, &hQuery);
    if (status != ERROR_SUCCESS) {
      throw (int)status;
    }
  }

public:
  ~PerformanceQuery()
  {
    if (hQuery) {
      PdhCloseQuery(hQuery);
      hQuery = NULL;
    }
  }

public:
  PDH_STATUS addCounter(const TCHAR* path, PerformanceCounter& counter)
  {
    PDH_STATUS status = (PDH_STATUS)-1;;
    if (hQuery) {
      HCOUNTER hCounter;
      status = PdhAddCounter(hQuery, path, 0, &hCounter);
      if (status == ERROR_SUCCESS) {
        counter.setCounter(hCounter);
      } else {    
        throw (int)status;
      }
    }
    return status;
  }

public:
  PDH_STATUS collect()
  {
    PDH_STATUS status = (PDH_STATUS)-1;;
    if (hQuery) {
      status = PdhCollectQueryData(hQuery);
      if (status != ERROR_SUCCESS) {
        throw (int)status;
      }
    }
    return status;
  }

};

}
