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
 *  WbemProcessSink.h
 *
 *****************************************************************************/


#pragma once

#include <sol\wmi\WbemObjectSink.h>

namespace SOL {

class WbemProcessSink : public WbemObjectSink
{

public:
  WbemProcessSink()
  {
  }

public:
   ~WbemProcessSink() {
   }

public:
  // dateTime Format= YYYY/MM/DD HH:MM:SS
  void toDateTime(const TCHAR* date, TCHAR* dateTime) {

    memcpy(&dateTime[0], &date[0], 4);
    dateTime[4] = '/';
    memcpy(&dateTime[5], &date[4], 2);
    dateTime[7] = '/';
    memcpy(&dateTime[8], &date[6], 2);
    dateTime[10] = ' ';
    memcpy(&dateTime[11],&date[8], 2);
    dateTime[13] = ':';
    memcpy(&dateTime[14],&date[10], 2);
    dateTime[16] = ':';
    memcpy(&dateTime[17],&date[12], 2);
  }

public:
  /**
   * Show some typical properties of Win32_Process WbemClassObject.
   *
   * For full properties of Win32_Process, see the below comment.
   */
    virtual HRESULT ShowObject(VARIANT& vTargetInst)
  {
    try {
      _variant_t vInst(vTargetInst);  
      IWbemClassObjectPtr pProcessObj(vInst);
      BSTR bstr;
      pProcessObj->GetObjectText(0, &bstr);
      printf("ObjectText=%S\n", bstr);
      SysFreeString(bstr);

      VARIANT vVar;
      VariantInit(&vVar);
      if (SUCCEEDED(pProcessObj->Get(L"ExecutablePath", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("ExecutablePath: %s\n"), (const TCHAR*)string);
      }  

      VariantClear(&vVar);

      if (SUCCEEDED(pProcessObj->Get(L"Name", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("Name: %s\n"), (const TCHAR*)string);
      }  
      VariantClear(&vVar);

      if (SUCCEEDED(pProcessObj->Get(L"CommandLine", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("CommandLine: %s\n"), (const TCHAR*)string);
      }
      VariantClear(&vVar);

      if (SUCCEEDED(pProcessObj->Get(L"CreationDate", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
    
        TCHAR date[256];
        strcpy_s(date, CountOf(date), (const TCHAR*)string);    
        TCHAR dateTime[256];
        memset(dateTime, (TCHAR)0, CountOf(dateTime));
        toDateTime(date, dateTime);
        _tprintf(_T("CreationDate: %s \n"), dateTime);
      }  
      VariantClear(&vVar);


      if (SUCCEEDED(pProcessObj->Get(L"ProcessID", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _tprintf(_T("ProcessID: 0x%08x\n"), var.lVal);
      }
      VariantClear(&vVar);

      if (SUCCEEDED(pProcessObj->Get(L"ParentProcessID", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _tprintf(_T("ParentProcessID: 0x%08x\n"),var.lVal);
      }
      VariantClear(&vVar);

      _tprintf(_T("\n"));

    } catch(_com_error) {

    }

    return WBEM_S_NO_ERROR;
  }

};

}

/*
class Win32_Process : CIM_Process
{
  string   Caption;
  string   CommandLine;
  string   CreationClassName;
  datetime CreationDate;
  string   CSCreationClassName;
  string   CSName;
  string   Description;
  string   ExecutablePath;
  uint16   ExecutionState;
  string   Handle;
  uint32   HandleCount;
  datetime InstallDate;
  uint64   KernelModeTime;
  uint32   MaximumWorkingSetSize;
  uint32   MinimumWorkingSetSize;
  string   Name;
  string   OSCreationClassName;
  string   OSName;
  uint64   OtherOperationCount;
  uint64   OtherTransferCount;
  uint32   PageFaults;
  uint32   PageFileUsage;
  uint32   ParentProcessId;
  uint32   PeakPageFileUsage;
  uint64   PeakVirtualSize;
  uint32   PeakWorkingSetSize;
  uint32   Priority;
  uint64   PrivatePageCount;
  uint32   ProcessId;
  uint32   QuotaNonPagedPoolUsage;
  uint32   QuotaPagedPoolUsage;
  uint32   QuotaPeakNonPagedPoolUsage;
  uint32   QuotaPeakPagedPoolUsage;
  uint64   ReadOperationCount;
  uint64   ReadTransferCount;
  uint32   SessionId;
  string   Status;
  datetime TerminationDate;
  uint32   ThreadCount;
  uint64   UserModeTime;
  uint64   VirtualSize;
  string   WindowsVersion;
  uint64   WorkingSetSize;
  uint64   WriteOperationCount;
  uint64   WriteTransferCount;
};

*/
