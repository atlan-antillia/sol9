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
 *  PerformanceObject.h
 *
 *****************************************************************************/

// SOL9

#pragma once

#include <sol/pdh/PdhObject.h>

#include <winperf.h>
//#include <pdh.h>

//#pragma comment(lib, "pdh.lib")

namespace SOL {

class PerformanceObject :public PdhObject {
private:
  TCHAR* dataSource;
  TCHAR* machineName;
  DWORD detailLevel;

  TCHAR* objectNames;

public:
  /**
   * Constructor
   */
  PerformanceObject(const TCHAR* source = NULL, const TCHAR* machine=NULL,
    DWORD level = PERF_DETAIL_WIZARD )
  :dataSource(NULL),
  machineName(NULL),
  detailLevel(level),
  objectNames(NULL)
  {
    if (source) {
      size_t slen = strlen(source)+1;
      dataSource = new TCHAR[slen];
      strcpy_s(dataSource, slen, source);
    }
    if (machine) {
      size_t slen = strlen(machine)+1;
      machineName = new TCHAR[slen];
      strcpy_s(machineName, slen, machine);
    }

    enumObjects();
  }

public:
  /**
   * Destructor
   */
  ~PerformanceObject()
  {
    if (dataSource) {
      delete [] dataSource;
      dataSource = NULL;
    }
    if (machineName) {
      delete [] machineName;
      machineName = NULL;
    }
    clear();
  }


public:
  bool enumObjects()
  {  
    bool rc = false;

    clear();

    DWORD dwSize = 0;
    DWORD r = 0;

    if ((r = PdhEnumObjects(dataSource, machineName, NULL, &dwSize,
      detailLevel, TRUE)) != PDH_MORE_DATA) {
      throw (int)r;
    }

    objectNames = new TCHAR[dwSize];
    memset(objectNames, (TCHAR)0, dwSize);    
    if ((r = PdhEnumObjects(dataSource, machineName, objectNames, &dwSize,
      detailLevel, FALSE)) == ERROR_SUCCESS){
      rc = true;
    } else {
      throw (int)r;
    }
    return rc;
  }

public:
  void clear()
  {
    if (objectNames) {
      delete [] objectNames;
      objectNames = NULL;
    }
  }

protected:
  DWORD enumObjectItems(__in const TCHAR* objectName,
    __in TCHAR* counterNames, __in DWORD& counterNameLen,
    __in TCHAR* instanceNames, __in DWORD& instanceNameLen)
  {
    DWORD r = PdhEnumObjectItems(dataSource, machineName, objectName, 
      counterNames, &counterNameLen,
      instanceNames, &instanceNameLen, detailLevel, FALSE);
    if (r !=  ERROR_SUCCESS) {
      throw (int)r;
    }
    return r;
  }

protected:
  DWORD getObjectItemsSize(__in const TCHAR* objectName, 
      __out DWORD& dwCountersSize,
      __out DWORD& dwInstancesSize)
  {
    dwCountersSize  = 0;
    dwInstancesSize = 0;

    DWORD r = PdhEnumObjectItems(dataSource, machineName, objectName,
      NULL, &dwCountersSize, 
      NULL, &dwInstancesSize, 
      detailLevel, FALSE);
    if (r != PDH_MORE_DATA) {
      throw (int)r;
    }
    return r;
  }

private:
  void enumObjectItems(const TCHAR *objectName)
  {
    DWORD dwCountersSize  = 0;
    DWORD dwInstancesSize = 0;

    //DWORD r = 0;
    
    TCHAR* counters  = NULL;
    TCHAR* instances = NULL;

    try {
      getObjectItemsSize(objectName,
        dwCountersSize, 
        dwInstancesSize);

      if (dwCountersSize>0) {
        counters = new TCHAR[dwCountersSize];
        memset(counters, (TCHAR)0, dwCountersSize);
      }

      if (dwInstancesSize>0) {
        instances = new TCHAR[dwInstancesSize];
        memset(instances, (TCHAR)0, dwInstancesSize);
      }
        
      enumObjectItems(objectName, 
          counters, dwCountersSize,
          instances, dwInstancesSize);

      const TCHAR *p = NULL;
      if (instances) {
        int insCount = 0;
        for (p = instances; *p; p+= strlen(p)+1) {
          insCount++;
        }
        if (insCount>0) {
          _tprintf(_T("  Instance:\n"));
          for (p = instances; *p; p+= strlen(p)+1) {
            _tprintf(_T("    %s\n"), p);
          }
        }
      }

      if (counters) {
        int cntCount = 0;
        for (p = counters; *p; p+= strlen(p)+1) {
          cntCount++;
        }

        if (cntCount>0) {
          _tprintf(_T("  Counter:\n"));
          for (p = counters; *p; p+= strlen(p)+1) {
            _tprintf(_T("    %s\n"), p);
          }
        }
      }
    } catch (...) {
      
    }

    delete [] counters;
    delete [] instances;
  }

public:
  void display()
  {
    const TCHAR* p = NULL;
    for (p = objectNames; *p; p += strlen(p)+1) {
      _tprintf(_T("%s\n"), p);
      enumObjectItems((const TCHAR*)p);
      _tprintf(_T("\n"));
    }
  }

protected:
  TCHAR* getObjectNames()
  {
    return objectNames;
  }

protected:
  TCHAR* getDataSource() 
  { 
    return dataSource;
  }

protected:
  TCHAR* getMachineName() 
  { 
    return machineName;
  }

protected:
  DWORD getDetailLevel() 
  { 
    return   detailLevel;
  }
};

}
