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
 *  WbemServiceSink.h
 *
 *****************************************************************************/


#pragma once

#include <sol\wmi\WbemObjectSink.h>

namespace SOL {

class WbemServiceSink : public WbemObjectSink
{

public:
  WbemServiceSink()
  {
  }

public:
   ~WbemServiceSink() {
   }

public:
  /**
   * Show some typical properties of Win32_Service WbemClassObject.
   *
   * For full properties of Win32_Service, see the below comment.
   */
    virtual HRESULT ShowObject(VARIANT& vTargetInst)
  {
    try {
      _variant_t vInst(vTargetInst);  
      IWbemClassObjectPtr pServiceObj(vInst);
          
      VARIANT vVar;
      VariantInit(&vVar);
      if (SUCCEEDED(pServiceObj->Get(L"Name", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("Name: %s\n"), (const TCHAR*)string);
      }  
      VariantClear(&vVar);

      if (SUCCEEDED(pServiceObj->Get(L"DisplayName", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("DisplayName: %s\n"), (const TCHAR*)string);
      }
      VariantClear(&vVar);

      if (SUCCEEDED(pServiceObj->Get(L"PathName", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("PathName: %s\n"), (const TCHAR*)string);
      }  
      VariantClear(&vVar);

    
      VariantInit(&vVar);
      if (SUCCEEDED(pServiceObj->Get(L"StartMode", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;

        _tprintf(_T("StartMode: %s\n"), (const TCHAR*)string);
      }
      VariantClear(&vVar);

      VariantInit(&vVar);
      if (SUCCEEDED(pServiceObj->Get(L"State", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("State: %s\n"), (const TCHAR*)string);
      }

      VariantClear(&vVar);
      VariantInit(&vVar);
      if (SUCCEEDED(pServiceObj->Get(L"Status", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("Status: %s\n"), (const TCHAR*)string);
      }
      VariantClear(&vVar);

      VariantInit(&vVar);
      if (SUCCEEDED(pServiceObj->Get(L"Description", 0, &vVar, 0, 0))) {
        _variant_t var(vVar);
        _bstr_t string = (_bstr_t)var;
        _tprintf(_T("Description: %s\n"), (const TCHAR*)string);
      }
      VariantClear(&vVar);

      _tprintf(_T("\n"));

    } catch(_com_error ) {

    }

    return WBEM_S_NO_ERROR;
  }

};

}

/*
class Win32_Service : Win32_BaseService
{
  boolean  AcceptPause;
  boolean  AcceptStop;
  string   Caption;
  uint32   CheckPoint;
  string   CreationClassName;
  string   Description;
  boolean  DesktopInteract;
  string   DisplayName;
  string   ErrorControl;
  uint32   ExitCode;
  datetime InstallDate;
  string   Name;
  string   PathName;
  uint32   ProcessId;
  uint32   ServiceSpecificExitCode;
  string   ServiceType;
  boolean  Started;
  string   StartMode;
  string   StartName;
  string   State;
  string   Status;
  string   SystemCreationClassName;
  string   SystemName;
  uint32   TagId;
  uint32   WaitHint;
};

*/
