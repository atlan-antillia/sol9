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
 *  PerformanceCounter.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/25

#pragma once

#include <sol/pdh/PdhObject.h>
#include <sol/pdh/PerformanceCounterInfo.h>


namespace SOL {

class PerformanceCounter :public PdhObject {

private:
  HCOUNTER hCounter;

public:
  PerformanceCounter()
  :hCounter(NULL)
  {
  }

public:
  ~PerformanceCounter()
  {
    if (hCounter) {
      PdhRemoveCounter(hCounter);
      hCounter = NULL;
    }
  }

public:
  void setCounter(HCOUNTER hc) {
    hCounter = hc;
  }

public:
  HCOUNTER getCounter() {
    return hCounter;
  }

public:
  operator HCOUNTER() const{
    return hCounter;
  }


public:

  PDH_STATUS getFormattedValue(__out String& string)
  {
/*
typedef struct _PDH_FMT_COUNTERVALUE {
  DWORD CStatus;
  union {
    LONG longValue;
    double doubleValue;
    LONGLONG largeValue;
    LPCSTR AnsiStringValue;    //not supported (From MSDN)
    LPCWSTR WideStringValue;  //not supported (From MSDN)
  } ;
}PDH_FMT_COUNTERVALUE, *PPDH_FMT_COUNTERVALUE;
*/
    string = "";

    PDH_FMT_COUNTERVALUE value;

    memset(&value, 0, sizeof(value));
    PerformanceCounterInfo info(getCounter());

    String sizeName;
    DWORD size;
    info.getDataSize(size, sizeName);

    DWORD sizeType = PDH_FMT_LONG;

    if (size == PERF_SIZE_DWORD){
      sizeType = PDH_FMT_LONG;
    }
    if (size == PERF_SIZE_LARGE){
      sizeType = PDH_FMT_LARGE;
    }

    char buffer[MAX_PATH];
    memset(buffer, 0, sizeof(buffer));
    PDH_STATUS   status = PdhGetFormattedCounterValue(hCounter, sizeType, 
              //PDH_FMT_LONG, 
              //PDH_FMT_LARGE,
              //|PDH_FMT_NOSCALE, 
                  NULL, &value);
    if (status == ERROR_SUCCESS) {
      if (sizeType == PDH_FMT_LONG) {
        sprintf_s(buffer, CountOf(buffer), "%lu", value.longValue);
      }
      if (sizeType == PDH_FMT_LARGE) {
        sprintf_s(buffer, CountOf(buffer), "%I64d", value.largeValue);
      }
      string = buffer;

    } else {
      throw (int)status;
    }

    return status;
  }

public:

  PDH_STATUS getFormattedValue(__out PDH_FMT_COUNTERVALUE& value,
          __in DWORD type=PDH_FMT_LONG)
  {
    memset(&value, 0, sizeof(value));

    PDH_STATUS   status = PdhGetFormattedCounterValue(hCounter, type, 
                  NULL, &value);
    if (status != ERROR_SUCCESS) {
      throw (int)status;
    }

    return status;
  }
};

}
