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
 *  PerformanceCounterInfo.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/25

#pragma once
#include <sol/ArgT.h>
#include <sol/ArgListT.h>
#include <sol/String.h>
#include <sol/pdh/PdhObject.h>
//#include <sol/pdh/PerformanceCounter.h>

namespace SOL {

class PerformanceCounterInfo: public PdhObject {

private:
  HCOUNTER hCounter;

private:
  PPDH_COUNTER_INFO pInfo;

public:
  /**
   * Constructor
   */
  PerformanceCounterInfo(HCOUNTER hc)
  :hCounter(hc),
  pInfo(NULL)
  {
    if (hCounter == NULL) {
      throw ERROR_INVALID_PARAMETER;
    }

    DWORD dwSize = 0;

    PDH_STATUS status = PdhGetCounterInfo(
      hCounter,
      TRUE,
      &dwSize,
      NULL);

    pInfo = (PPDH_COUNTER_INFO)new char[dwSize];
  
    status = PdhGetCounterInfo(
      hCounter,
      TRUE,
      &dwSize,
      pInfo);

    if (status != ERROR_SUCCESS) {
      throw (int)status;
    }
  }

public:
  /**
   * Destructor
    */
  ~PerformanceCounterInfo()
  {
    if (pInfo) {
      delete [] (char*)pInfo;
      pInfo = NULL;
    }
  }

public:
  bool getVersion(__out DWORD& version)
  {
    bool rc = false;
    if (pInfo) {
      version = pInfo->CVersion;
      rc = true;
    }
    return rc;
  }

public:
  bool getStatus(__out DWORD& status)
  { 
    bool rc = false;
    if (pInfo) {
      status = pInfo->CStatus;
      rc = true;
    }
    return rc;
  }


public:
  bool getScale(__out DWORD& scale)
  {
    bool rc = false;
    if (pInfo) {
      scale = pInfo->lScale;
      rc = true;
    }
    return rc;
  }

public:
  bool getDefaultScale(__out DWORD& dscale)
  {
    bool rc = false;
    if (pInfo) {
      dscale = pInfo->lDefaultScale;
      rc = true;
    }

    return rc;
  }

public:
  bool getFullPath(__out String& path)
  {
    bool rc = false;
    if (pInfo) {
      path = pInfo->szFullPath;
      rc = true;
    }
    return rc;
  }

public:
  bool getExplainText(__out String& text)
  {
    bool rc = false;
    if (pInfo) {
      //2009/09/26
      text = "";
      if (pInfo->szExplainText) {
        text = pInfo->szExplainText;
      }
      rc = true;
    }
    return rc;
  }

public:
  /**
  Returned size is one of the following:
    PERF_SIZE_DWORD
    PERF_SIZE_LARGE
    PERF_SIZE_ZERO
    PERF_SIZE_VARIABLE_LEN
  */
  bool getDataSize(__out DWORD& size, __out String& name)
  {
    static const ArgT<char> types[] = {
      {"SIZE_DWORD", PERF_SIZE_DWORD},
      {"SIZE_LARGE", PERF_SIZE_LARGE},
      {"SIZE_ZERO", PERF_SIZE_ZERO},
      {"SIZE_VARIABLE_LEN", PERF_SIZE_VARIABLE_LEN},
    };

    bool rc = false;
    if (pInfo) {
      size = pInfo->dwType & 0x00000300;
      ArgListT<char> list(types, XtNumber(types));
      name = list.getName(size);
      rc = true;
    }

    return rc;
  }

public:
  /*
    Returned format is one of the following:
    PERF_NUMBER_HEX
    PERF_NUMBER_DECIMAL
    PERF_NUMBER_DEC_1000
    PERF_COUNTER_VALUE
    PERF_COUNTER_RATE
    PERF_COUNTER_FRACTION
    PERF_COUNTER_BASE
    PERF_COUNTER_ELAPSED
    PERF_COUNTER_QUEUELEN
    PERF_COUNTER_HISTOGRAM
    PERF_TEXT_UNICODE
    PERF_TEXT_ASCII
   */
  bool getFormatType(__out DWORD& format, __out String& name)
  {
    static const ArgT<char> types[] = {
  
    {"NUMBER_HEX", PERF_NUMBER_HEX},
    {"NUMBER_DECIMAL", PERF_NUMBER_DECIMAL},
    {"NUMBER_DEC_1000", PERF_NUMBER_DEC_1000},
    {"COUNTER_VALUE", PERF_COUNTER_VALUE},
    {"COUNTER_RATE", PERF_COUNTER_RATE},
    {"COUNTER_FRACTION", PERF_COUNTER_FRACTION},
    {"COUNTER_BASE", PERF_COUNTER_BASE},
    {"COUNTER_ELAPSED", PERF_COUNTER_ELAPSED},
    {"COUNTER_QUEUELEN", PERF_COUNTER_QUEUELEN},
    {"COUNTER_HISTOGRAM", PERF_COUNTER_HISTOGRAM},
    {"TEXT_UNICODE", PERF_TEXT_UNICODE},
    {"TEXT_ASCII", PERF_TEXT_ASCII},
    };

    bool rc = false;
    if (pInfo) {
      format = pInfo->dwType & 0x000f0000;
      ArgListT<char> list(types, XtNumber(types));
      name = list.getName(format);

      rc = true;
    }

    return rc;    
  }

public:
  /*
  Returned type is one of the following:
    PERF_TYPE_NUMBER 
    PERF_TYPE_COUNTER
    PERF_TYPE_TEXT
    PERF_TYPE_ZERO.

  */
  bool getDataType(__out DWORD& type, __out String& name) 
  {
    static const ArgT<char> types [] = {
    {"TYPE_NUMBER", PERF_TYPE_NUMBER}, 
    {"TYPE_COUNTER", PERF_TYPE_COUNTER},
    {"TYPE_TEXT", PERF_TYPE_TEXT},
    {"TYPE_ZERO", PERF_TYPE_ZERO},
    };

    bool rc = false;

    if (pInfo) {
      type = pInfo->dwType & 0x00000c00;

      ArgListT<char> list(types, XtNumber(types));
      name = list.getName(type);
      rc = true;
    }
    return rc;

  }

public:
  /*
  Returned type is one of the following:
    PERF_TIMER_TICK,
    PERF_TIMER_100NS,
    PERF_OBJECT_TIMER.
  */
  bool getTimerType(__out DWORD& type, __out String& name) 
  {
    static const ArgT<char> types [] = {
    {"TIMER_TICK", PERF_TIMER_TICK},
    {"TIMER_100NS", PERF_TIMER_100NS},
    {"OBJECT_TIMER", PERF_OBJECT_TIMER},
    };

    bool rc = false;

    if (pInfo) {

      type = pInfo->dwType & 0x00030000;

      ArgListT<char> list(types, XtNumber(types));
      name = list.getName(type);
      rc = true;
    }
    return rc;

  }

public:
  bool getDisplayType(__out DWORD& type, __out String& name)
  {

    static const ArgT<char> types[] = {
    {"DISPLAY_NO_SUFFIX", PERF_DISPLAY_NO_SUFFIX},
    {"DISPLAY_PER_SEC", PERF_DISPLAY_PER_SEC},
    {"DISPLAY_PERCENT", PERF_DISPLAY_PERCENT},
    {"DISPLAY_SECONDS", PERF_DISPLAY_SECONDS},
    {"DISPLAY_NOSHOW", PERF_DISPLAY_NOSHOW},

    };

    bool rc = false;

    if (pInfo) {

      type = pInfo->dwType & 0xf0000000;
      ArgListT<char> list(types, XtNumber(types));
      name = list.getName(type);
      rc = true;
    }
    return rc;
  }

public:
  bool isDeltaCounter(__out bool& value, __out String& name)
  {
    bool rc = false;
    if (pInfo) {
      value = false;
      name = "false";
      if (pInfo->dwType & PERF_DELTA_COUNTER) {
        value = true;
        name = "true";
      }
      rc = true;
    }
    return rc;
  }

public:
  bool isDeltaBase(__out bool& value, __out String& name)
  {
    bool rc = false;
    if (pInfo) {
      name = "false";
      value = false;
      if (pInfo->dwType & PERF_DELTA_BASE) {
        value = true;
        name = "true";
      }
      rc = true;      
    }
    return rc;
  }

public:
  bool isInverseCounter(__out bool& value, __out String& name)
  {
    bool rc = false;
    if (pInfo) {
      name = "false";
      value = false;
      if (pInfo->dwType & PERF_INVERSE_COUNTER) {
        value = true;
        name = "true";
      }
      rc = true;
    }
    return rc;
  }

public:
  bool isMultiCounter(__out bool& value, __out String& name)
  {
    bool rc = false;

    if (pInfo) {
      value = false;
      name = "false";
      
      if (pInfo->dwType & PERF_MULTI_COUNTER) {
        value = true;
        name = "true";
      }
      rc = true;

    }
    return rc;
  }

public:
  void display()
  {
    if (pInfo) {
      String fullPath;
      getFullPath(fullPath);
      _tprintf(_T("FullPath: %s\n"), (const TCHAR*)fullPath);

      DWORD version;
      getVersion(version);
      _tprintf(_T("Version: 0x%08x\n"), version);

      DWORD status;
      getStatus(status);
      _tprintf(_T("Status: 0x%08x\n"), status);

      DWORD scale;
      getScale(scale);
      _tprintf(_T("Scale: %d\n"), scale);

      DWORD dscale;
      getDefaultScale(dscale);
      _tprintf(_T("DefaultScale: %d\n"), dscale);
  

      String dataSize;
      DWORD  size;
      getDataSize(size, dataSize);
      _tprintf(_T("DataSize: %s\n"), (const TCHAR*)dataSize);

      String dataType;
      DWORD  value;
      getDataType(value, dataType);
      _tprintf(_T("DataType: %s\n"), (const TCHAR*)dataType);

      String formatType;
      DWORD  format;
      getFormatType(format, formatType);
      _tprintf(_T("FormatType: %s\n"), (const TCHAR*)formatType);


      String timerType;
      DWORD  timer;
      getTimerType(timer, timerType);
      _tprintf(_T("TimerType: %s\n"), (const TCHAR*)timerType);

      String displayType;
      DWORD  disp;
      getDisplayType(disp, displayType);
      _tprintf(_T("DisplayType: %s\n"), (const TCHAR*)displayType);

      String deltaCounterFlag;
      bool  deltaCounter;
      isDeltaCounter(deltaCounter, deltaCounterFlag);
      _tprintf(_T("IsDeltaCounter: %s\n"), (const TCHAR*)deltaCounterFlag);

      String deltaBaseFlag;
      bool  deltaBase;
      isDeltaBase(deltaBase, deltaBaseFlag);

      _tprintf(_T("IsDetaBase: %s\n"), (const TCHAR*)deltaBaseFlag);

      String inverseCounterFlag;
      bool  inverseCounter;
      isInverseCounter(inverseCounter, inverseCounterFlag);

      _tprintf(_T("IsInverseCounter: %s\n"), (const TCHAR*)inverseCounterFlag);

      String multiCounterFlag;
      bool  multiCounter;
      isMultiCounter(multiCounter, multiCounterFlag);

      _tprintf(_T("IsMultiCounter: %s\n"), (const TCHAR*)multiCounterFlag);

      String text;
      getExplainText(text);

      _tprintf(_T("ExplainText: %s\n"), (const TCHAR*)text);
    }
  }
};

}
