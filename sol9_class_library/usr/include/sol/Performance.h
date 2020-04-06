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
 *  Performance.h
 *
 *****************************************************************************/

// SOL++2000

#pragma once

#include <sol\Object.h>
#include <sol\LinkedList.h>
#include <sol\LogFile.h>
#include <sol\ProcessInfo.h>
#include <sol\StringT.h>
#include <sol\StringConverter.h>

typedef PERF_DATA_BLOCK        PerfDataBlock;
typedef PERF_OBJECT_TYPE      PerfObject;
typedef PERF_COUNTER_DEFINITION    PerfCounter;
typedef PERF_INSTANCE_DEFINITION  PerfInstance;
typedef PERF_COUNTER_BLOCK      PerfCounterBlock;

#define PEF_DATASIZE    (1024*10)

#define NAME_COUNTERS    _T("Counters")
#define NAME_PROCESS    _T("Process")
#define NAME_PROCESSID    _T("ID Process")
#define NAME_WORKING_SET  _T("Working Set")

namespace SOL {

#define NAME_PEFLIB    _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\009")

class Performance :public Object {

private:
  DWORD getIndex(const TCHAR* title)
  {
    DWORD  index = -1;
    HKEY  hkey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, NAME_PEFLIB, 0, KEY_READ, &hkey) 
      != ERROR_SUCCESS){
      return index;
    }

    HANDLE hHeap = GetProcessHeap();

    DWORD  size = 0;

    if (RegQueryValueEx(hkey, NAME_COUNTERS, NULL, NULL, NULL, &size)
      != ERROR_SUCCESS){
      return index;
    }

    TCHAR* buffer = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, size);

    if (RegQueryValueEx(hkey, NAME_COUNTERS, NULL, NULL, (LPBYTE)buffer, &size)
      != ERROR_SUCCESS){
      HeapFree(hHeap, 0, buffer);
      return index;
    }

    TCHAR* lpsz = (TCHAR*)buffer;
    int   len = 0;

    while((len = strlen(lpsz))){
      index = (DWORD)atoi(lpsz);
      lpsz += (len + 1);
      StringT<TCHAR> tname;
      StringConverter converter;
      converter.convert(lpsz, tname);

      if(strcmp(title, lpsz  //(const TCHAR*)tname
              ) == 0){
        break;
      }
      lpsz += (strlen(lpsz) + 1);
    }
  
    RegCloseKey(hkey);
    HeapFree(hHeap, 0, buffer);

    return index;
  }



  PerfDataBlock* getDataBlock()
  {
    HANDLE hHeap = GetProcessHeap();

    DWORD  size = PEF_DATASIZE;  
    LRESULT rc = 0;

    DWORD id = getIndex(NAME_PROCESS);
    TCHAR index[MAX_PATH];
    _stprintf_s(index, CountOf(index), _T("%d"), id);

    PPERF_DATA_BLOCK  pdb = NULL;

    do{
      pdb = (PerfDataBlock*)HeapAlloc(hHeap, 0, size);
      if(pdb == NULL){
        return NULL;
      }

      rc = RegQueryValueEx(HKEY_PERFORMANCE_DATA, index, 
          NULL, NULL, (LPBYTE)pdb, &size);

      if (rc == ERROR_MORE_DATA) {
        HeapFree(hHeap, 0, pdb);
        size += 1024;
        continue;
      }

    } while (rc == ERROR_MORE_DATA);

    return pdb;
  }


  DWORD indexOffset(PerfDataBlock* pdb, const TCHAR* name)
  {
    PerfObject* pot = getObjectType(pdb);
    PerfCounter* pcd = firstCounter(pdb);

    DWORD index = getIndex(name);

    DWORD offset = 0;

    for(int n = 0; n < (int)pot->NumCounters; n++){
      if (pcd->CounterNameTitleIndex == index){
        offset = pcd->CounterOffset;
        break;
      }
      pcd = nextCounter(pcd);
    }

    return offset;
  }


  PerfInstance* findNthInstance(PerfDataBlock* pdb, 
                          int index)
  {
    PerfInstance* pid = firstInstance(pdb);

    PerfInstance* nth = NULL;
    int n = 0;
    while (pid) {
      if (n == index) {
        nth = pid;
        break;
      }
      pid = nextInstance(pid);
      n++;
    }
    return nth;
  }


  PerfObject* getObjectType(PerfDataBlock* pdb){
    return (PerfObject*)((LPBYTE)pdb + pdb->HeaderLength);
  }

  PerfCounter*  firstCounter(PerfDataBlock* pdb) {
    PerfObject* pot = getObjectType(pdb);
    return (PerfCounter*)((LPBYTE)pot + pot->HeaderLength);
  }

  PerfCounter* nextCounter(PerfCounter* pcd) {
    return (PerfCounter*)((LPBYTE)pcd + pcd->ByteLength);
  }

  PerfInstance*  firstInstance(PerfDataBlock* pdb) {
    PerfObject*  pot = getObjectType(pdb);
    return (PerfInstance*)((PBYTE)pot + pot->DefinitionLength);
  }

  PerfInstance*  nextInstance(PerfInstance* pid) {
    PerfCounterBlock*  pcb= (PerfCounterBlock*)((LPBYTE)pid + pid->ByteLength);
    return (PerfInstance*)((LPBYTE)pcb + pcb->ByteLength);
  }

  PerfCounterBlock*  firstCounterBlock(PerfDataBlock* pdb) {
    PerfInstance* pid = firstInstance(pdb);
    return (PerfCounterBlock*)((LPBYTE)pid + pid->ByteLength);
  }

  PerfCounterBlock*   nextCounterBlock(PerfCounterBlock* pcb){
    PPERF_INSTANCE_DEFINITION  pid= (PerfInstance*)((LPBYTE)pcb + 
                pcb->ByteLength);
    return (PerfCounterBlock*)((LPBYTE)pid + pid->ByteLength);
  }

  DWORD  getLongValue(PerfCounterBlock* pcb, DWORD offset) {
    return *((DWORD *)((PBYTE)pcb + offset));
  }

  void  getProcessName(PerfInstance* pid, char* name, 
        DWORD size) {
      WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK,
        (LPWSTR)((LPBYTE)pid + pid->NameOffset),
        -1, name, size, NULL, NULL);
  }

  void  getProcessName(PerfInstance* pid, wchar_t* name, 
        DWORD size) {
        strcpy_s(name, size, (LPWSTR)((LPBYTE)pid + pid->NameOffset));
  
      /*WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK,
        (LPWSTR)((LPBYTE)pid + pid->NameOffset),
        -1, name, size, NULL, NULL);
        */
  }

public:
  Performance() {}
  ~Performance() {}

public:
  void getProcessList(LinkedList& list)
  {
    PPERF_DATA_BLOCK  pdb = getDataBlock();
    if (pdb == NULL){
      return;
    }

    DWORD pidOffset = indexOffset(pdb, NAME_PROCESSID);
    DWORD wsOffset  = indexOffset(pdb, NAME_WORKING_SET);

    PPERF_OBJECT_TYPE         pot = getObjectType(pdb);
    PPERF_INSTANCE_DEFINITION pid = firstInstance(pdb);
    PPERF_COUNTER_BLOCK       pcb = firstCounterBlock(pdb);

    for(int n = 1; n < (int)pot->NumInstances; n++){
      DWORD id       = getLongValue(pcb, pidOffset);
      DWORD workSet  = getLongValue(pcb, wsOffset);

      TCHAR name[_MAX_PATH];
      getProcessName(pid, name, CountOf(name));

      list.add(new ProcessInfo(id, name));
      pid = nextInstance(pid);
      pcb = nextCounterBlock(pcb);
    }

    HeapFree(GetProcessHeap(), 0, pdb);
  }

public:
  BOOL dumpTitleIndex()
  {
    BOOL  rc = FALSE;
    HKEY  hkey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, NAME_PEFLIB, 0, KEY_READ, &hkey) 
      != ERROR_SUCCESS){
      return rc;
    }

    HANDLE hHeap = GetProcessHeap();

    DWORD  size = 0;

    if (RegQueryValueEx(hkey, NAME_COUNTERS, NULL, NULL, NULL, &size)
      != ERROR_SUCCESS){
      return rc;
    }

    TCHAR* buffer = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, size);

    if (RegQueryValueEx(hkey, NAME_COUNTERS, NULL, NULL, (LPBYTE)buffer, &size)
      != ERROR_SUCCESS){
      HeapFree(hHeap, 0, buffer);
      return rc;
    }

    TCHAR* lpsz = buffer;
    int   len = 0;
    LogFile logFile(_T("titleindex.txt"));
    while((len = strlen(lpsz))){
      TCHAR  name[MAX_PATH];
      //2009/06/17 sizeof(MAX_PATH) -> sizeof(name)
      strcpy_s(name, CountOf(name), lpsz);
      lpsz += (len + 1);
      logFile.printf(_T("%s=[%s]\r\n"), name, lpsz);
  
      lpsz += (strlen(lpsz) + 1);
    }
    rc = TRUE;

    RegCloseKey(hkey);
    HeapFree(hHeap, 0, buffer);

    return rc;
  }


public:
  void dump()
  {
    BOOL  rc = FALSE;
    HKEY  hkey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, NAME_PEFLIB, 0, KEY_READ, &hkey) 
      != ERROR_SUCCESS){
      return;// rc;
    }

    HANDLE hHeap = GetProcessHeap();

    DWORD  size = 0;

    if (RegQueryValueEx(hkey, NAME_COUNTERS, NULL, NULL, NULL, &size)
      != ERROR_SUCCESS){
      return;// rc;
    }

    TCHAR* buffer = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, size);

    if (RegQueryValueEx(hkey, NAME_COUNTERS, NULL, NULL, (LPBYTE)buffer, &size)
      != ERROR_SUCCESS){
      HeapFree(hHeap, 0, buffer);
      return;// rc;
    }

    TCHAR* lpsz = buffer;
    int   len = 0;
    //printf("titleindex.txt");
    while((len = strlen(lpsz))){
      TCHAR  name[MAX_PATH];
      //2009/06/17 sizeof(MAX_PATH) -> sizeof(name)
      strcpy_s(name, CountOf(name), lpsz);
      lpsz += (len + 1);
      printf("%s=[%s]\r\n", name, lpsz);
  
      lpsz += (strlen(lpsz) + 1);
    }
    rc = TRUE;

    RegCloseKey(hkey);
    HeapFree(hHeap, 0, buffer);

  }


};

}

