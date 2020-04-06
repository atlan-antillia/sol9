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
 *  ToolHelp.h
 *
 *****************************************************************************/

// SOL++2000
// 2009/09/10 Modified intialize method not to check Windows NT.
// 2009/10/15 Modified to use the prototype declaration of APIs in tlhelp32.h
#pragma once

#include <sol\Object.h>
#include <sol\LinkedList.h>
#include <psapi.h>
#include <process.h>
#include <tlhelp32.h>
#include <sol\ProcessInfo.h>
#include <sol/String.h>

namespace SOL {

class ToolHelp :public Object {


private:
  BOOL isWindowsNT() 
  {
    BOOL rc = FALSE;

    OSVERSIONINFO ver;
    memset(&ver, 0, sizeof(ver));
    ver.dwOSVersionInfoSize = sizeof(ver);

    GetVersionEx(&ver);

    if (ver.dwPlatformId ==VER_PLATFORM_WIN32_WINDOWS) {
      rc = FALSE;
    }

    if (ver.dwPlatformId == VER_PLATFORM_WIN32_NT) {
      rc = TRUE;
    }
    return rc;
  }



protected:
  BOOL getModuleEntry(DWORD processId, 
            DWORD dwModuleId, LPMODULEENTRY32 lpme32)
  {
    MODULEENTRY32  me32;
    BOOL  result = FALSE;

    memset(&me32, 0, sizeof(me32));
    me32.dwSize = sizeof(me32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    if(hSnapshot == INVALID_HANDLE_VALUE){
      return result;
    }

    if(Module32First(hSnapshot, &me32)){
      do{
        if(dwModuleId == me32.th32ModuleID){
          CopyMemory(lpme32, &me32, sizeof(me32));
          result = TRUE;
          break;
        }
      }while(Module32Next(hSnapshot, &me32));
    }  
  
    CloseHandle(hSnapshot);
    
    return result;
  }

protected:
  BOOL getHeapSize(DWORD processID,
               DWORD* size)
  {
    BOOL rc = FALSE;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    //HANDLE hSnapshot = createToolHelp(TH32CS_SNAPALL, processID);

    if(hSnapshot == INVALID_HANDLE_VALUE){
      return rc;
    }

    rc = TRUE;

    HEAPLIST32 hlist;
    memset(&hlist, 0, sizeof(hlist));
    hlist.dwSize = sizeof(hlist);
    DWORD heapID = 0;

    if (Heap32ListFirst(hSnapshot, &hlist)){
      do{
        if(processID == hlist.th32ProcessID){
          heapID = hlist.th32HeapID;
          break;
        }
      }while(Heap32ListNext(hSnapshot, &hlist));
    }  
    CloseHandle(hSnapshot);

    *size = 0;
    HEAPENTRY32 hentry;
    memset(&hentry, 0, sizeof(hentry));
    hentry.dwSize = sizeof(hentry);
    hentry.dwFlags = (LF32_FIXED|LF32_FREE|LF32_MOVEABLE);
    if (Heap32First(&hentry, processID, heapID )){
      do{
        *size += hentry.dwBlockSize;  
      } while(Heap32Next(&hentry));
    }    
    return rc;
  }
///////////////////////////////////////////////////////////
public:

  ToolHelp()
  {
  }

public:
  ~ToolHelp()
  {
  }


public:
  void getProcessList(LinkedList& list)
  {
    PROCESSENTRY32  pe32;
    //pe32.cntThreads

    memset(&pe32, 0, sizeof(pe32));
    pe32.dwSize = sizeof(pe32);

    HANDLE hsnpProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    if(hsnpProcess == INVALID_HANDLE_VALUE){
      return;
    }

    if (Process32First(hsnpProcess, &pe32)) {
      do{
        //::CharUpper(pe32.szExeFile);
        TCHAR* name = pe32.szExeFile;
        TCHAR* delim = strrchr(name, (TCHAR)'\\');
        if (delim) {
          name = ++delim;
        }

        list.add(new ProcessInfo(pe32.th32ProcessID,
                    name,
                    pe32.th32ParentProcessID,
                    pe32.cntThreads));
      } while(Process32Next(hsnpProcess, &pe32));

      CloseHandle(hsnpProcess);

    }
  }

protected:
  bool getModuleFileName(DWORD processID, String& name)
  {
    bool rc = false;
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, processID);
    if (hProcess== NULL) {
      return rc;
    }

    HMODULE hMod = NULL;
    DWORD cbNeeded = 0; 

    
    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), 
                 &cbNeeded)) {
      TCHAR fileName[1024];

        
      if (GetModuleFileNameEx(hProcess, hMod, fileName, 
          CountOf(fileName)) ) {
          name = fileName;
          rc = true;
      }
            
    }
    return rc;
  }

protected:
  void displayModules(DWORD processID)
  {
      //printf( "\nProcess ID: %u\n", processID );
    
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, processID );
    if (hProcess== NULL) {
      return;
    }

    HMODULE hMods[1024];  
    DWORD cbNeeded  = 0;
    
    if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
      int count = cbNeeded /sizeof(HMODULE);
      for (int i = 0; i < count; i++) {
        TCHAR name[MAX_PATH];

        if (GetModuleFileNameEx(hProcess, hMods[i], name, CountOf(name))) {
          //printf(_T("  %s\n"), name);
        }
      }
    }
    CloseHandle(hProcess);
  }


public:
  void displayProcesses()
  {
    PROCESSENTRY32  pe32;

    memset(&pe32, 0, sizeof(pe32));
    pe32.dwSize = sizeof(pe32);

    HANDLE hsnpProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    if(hsnpProcess == INVALID_HANDLE_VALUE){
      return;
    }

    if (Process32First(hsnpProcess, &pe32)) {
      do{

        String fileName="";
        getModuleFileName(pe32.th32ProcessID, fileName);
        if (fileName.getLength()>0) {
          
          _tprintf(_T("PID=%lu Name=%s Threads=%lu ParentPID=%lu \n"),
            pe32.th32ProcessID,
            (const TCHAR*)fileName,
            pe32.cntThreads,
            pe32.th32ParentProcessID);
        } else {
          
          _tprintf(_T("PID=%lu Name=%s  Threads=%lu ParentPID=%lu \n"),
            pe32.th32ProcessID,
            pe32.szExeFile,
            pe32.cntThreads,
            pe32.th32ParentProcessID);
        }
        //displayModules(pe32.th32ProcessID);

      } while(Process32Next(hsnpProcess, &pe32));

      CloseHandle(hsnpProcess);

    }
  }


public:
  void displayProcessesWithModules()
  {
    PROCESSENTRY32  pe32;

    memset(&pe32, 0, sizeof(pe32));
    pe32.dwSize = sizeof(pe32);

    HANDLE hsnpProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    if(hsnpProcess == INVALID_HANDLE_VALUE){
      return;
    }

    if (Process32First(hsnpProcess, &pe32)) {
      do{
        
        _tprintf(_T("-------------------------------------------\n"));
        String fileName="";
        getModuleFileName(pe32.th32ProcessID, fileName);
        if (fileName.getLength()>0) {
          
          _tprintf(_T("PID=%lu Name=%s Threads=%lu ParentPID=%lu \n"),
            pe32.th32ProcessID,
            (const TCHAR*)fileName,
            pe32.cntThreads,
            pe32.th32ParentProcessID);
        } else {
          _tprintf(_T("PID=%lu Name=%s  Threads=%lu ParentPID=%lu \n"),
            pe32.th32ProcessID,
            pe32.szExeFile,
            pe32.cntThreads,
            pe32.th32ParentProcessID);
        }
        displayModules(pe32.th32ProcessID);
        
      } while(Process32Next(hsnpProcess, &pe32));

      CloseHandle(hsnpProcess);

    }
  }
};

}

