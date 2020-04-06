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
 *  ProcessInformation.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/12

#pragma once

#include <sol/Object.h>
#include <sol/String.h>
#include <sol/StringBuffer.h>
#include <sol/Arg.h>
//#include <psapi.h>
//#include <sddl.h>

#include <sol/ProcessUser.h>
#include <sol/ProcessOwner.h>
#include <sol/ProcessGroups.h>

namespace SOL {

class ProcessInformation :public Object {


private:
  DWORD processID;


  PROCESS_MEMORY_COUNTERS pmc;

  String baseName;

  String moduleName;

  ProcessUser tokenUser;
  ProcessOwner tokenOwner;
  ProcessGroups tokenGroups;


public:
  ProcessInformation(DWORD pid, const TCHAR* name=_T(""))
  :processID(pid),
  baseName(name),
  moduleName(_T(""))
  {
    memset(&pmc, 0, sizeof(pmc));

    getInformation();
  }

public:
  ~ProcessInformation()
  {
    clear();
  }

private:
  void clear()
  {
    memset(&pmc, 0, sizeof(pmc));

    baseName = "";
    moduleName = "";

  }

public:
  bool getInformation() 
  {
    bool rc = false;

    clear();
    
    //processID = pid;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, processID );
    if (hProcess == NULL) {
      _tprintf(_T("Failed to OpenProcess\n"));
      return rc;
    }
    
    if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
      _tprintf(_T("Failed to GetProcessMemory\n"));

      return rc;
    }

    HMODULE hMod = NULL;
        
    DWORD cbNeeded = 0;

    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), 
      &cbNeeded)) {

      TCHAR name[1024];
      memset(name, (TCHAR)0, CountOf(name));
      if (GetModuleBaseName( hProcess, hMod, name, CountOf(name))) {
        if (strlen(name)>0) {
          baseName = name;
        }
      } else {
        _tprintf(_T("Failed to GetModuleBaseName\n"));
      }

      memset(name, (TCHAR)0, CountOf(name));
      
      if (GetModuleFileNameEx(hProcess, hMod, name, CountOf(name))) {
        if (strlen(name)>0) {
          moduleName = name;
        }
      } else {
        _tprintf(_T("Failed to GetModuleFileName\n"));
      }
    }

    HANDLE hToken = NULL;
    if (OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)) {
      tokenUser.getInformation(hToken);  

      tokenOwner.getInformation(hToken);        

      tokenGroups.getInformation(hToken);        

      CloseHandle(hToken);

    } else {
      _tprintf(_T("Failed to OpenProcessToken\n"));
    }

      CloseHandle(hProcess);
    hProcess = NULL;

    return rc;
  }



public:
  void display()
  {
    _tprintf(_T("PID : %d\n"), processID);
    _tprintf(_T("BaseName : %s\n"), (const TCHAR*)baseName);
    _tprintf(_T("ModuleName : %s\n"), (const TCHAR*)moduleName);



    _tprintf(_T("PageFaultCount: 0X%08X\n"), pmc.PageFaultCount );
    _tprintf(_T("PeakWorkingSetSize: 0X%08X\n"), pmc.PeakWorkingSetSize );
    _tprintf(_T("WorkingSetSize: 0X%08X\n"), pmc.WorkingSetSize );
    _tprintf(_T("QuotaPeakPagedPoolUsage: 0X%08X\n"), pmc.QuotaPeakPagedPoolUsage );
        _tprintf(_T("QuotaPagedPoolUsage: 0X%08X\n"), pmc.QuotaPagedPoolUsage );
    _tprintf(_T("QuotaPeakNonPagedPoolUsage: 0X%08X\n"), pmc.QuotaPeakNonPagedPoolUsage );
    _tprintf(_T("QuotaNonPagedPoolUsage: 0X%08X\n"), pmc.QuotaNonPagedPoolUsage );
    _tprintf(_T("PagefileUsage: 0X%08X\n"), pmc.PagefileUsage ); 
    _tprintf(_T("PeakPagefileUsage: 0X%08X\n"), 
                  pmc.PeakPagefileUsage );  

    tokenUser.display();
    tokenOwner.display();
    tokenGroups.display();
  }

};

}
