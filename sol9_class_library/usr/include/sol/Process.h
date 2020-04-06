/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Process.h
 *
 *****************************************************************************/

// SOL++2000
// 2012/06/25 Updated

#pragma once

#include <sol\Object.h>
#include <sol\Exception.h>
#include <sol\Pipe.h>

/*
typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;       //A handle to the newly created process. 
                         // The handle is used to specify the process in all functions that perform operations on the process object.
  HANDLE hThread;        //A handle to the primary thread of the newly created process. 
                         //The handle is used to specify the thread in all functions that perform operations on the thread object.
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;
From http://msdn.microsoft.com/en-us/library/windows/desktop/ms684873(v=vs.85).aspx
*/

namespace SOL {

class Process :public Object {
private:
  STARTUPINFO         startupInfo;
  PROCESS_INFORMATION  processInfo;
  SECURITY_ATTRIBUTES  securityAttributes;
  
public:
  Process(const TCHAR* cmd, DWORD flag = DETACHED_PROCESS) 
  {
    memset(&securityAttributes, 0, sizeof(SECURITY_ATTRIBUTES));
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = TRUE;

    memset(&startupInfo, 0, sizeof(STARTUPINFO));
    startupInfo.cb       = sizeof(STARTUPINFO);
    TCHAR command[MAX_PATH];
    wsprintf(command, _T("%s"), cmd);
    BOOL rc = CreateProcess(NULL,      // pointer to name of executable module 
          command,      // pointer to command line string

          &securityAttributes,  // pointer to process security attributes

          NULL,          // pointer to thread security attributes 
          TRUE,          // inheritance flag 

          flag,          // creation flags 
          NULL,          // pointer to new environment block 

          NULL,          // pointer to current directory name 
          &startupInfo,      // pointer to STARTUPINFO 
          &processInfo);       // pointer to PROCESS_INFORMATION  

    if (rc == False) {
      memset(&processInfo, 0, sizeof(processInfo));
      throw Exception(0, _T("Exception: Faield to CreateProcess %s\n"), cmd);
    }
  }

public:
  Process(const TCHAR* cmd, Pipe& pipe, DWORD flag = DETACHED_PROCESS) 
  {
    memset(&securityAttributes, 0, sizeof(SECURITY_ATTRIBUTES));
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = TRUE;

    memset(&startupInfo, 0, sizeof(STARTUPINFO));
    startupInfo.cb       = sizeof(STARTUPINFO);

    startupInfo.dwFlags     = STARTF_USESTDHANDLES;
    startupInfo.hStdOutput = pipe.getWriterHandle();
    startupInfo.hStdInput  = pipe.getReaderHandle();

    TCHAR command[MAX_PATH];
    wsprintf(command, _T("%s"), cmd);

    BOOL rc = CreateProcess(NULL,      // pointer to name of executable module 
          command,      // pointer to command line string

          &securityAttributes,  // pointer to process security attributes

          NULL,          // pointer to thread security attributes 
          TRUE,          // inheritance flag 

          flag,          // creation flags 
          NULL,          // pointer to new environment block 

          NULL,          // pointer to current directory name 
          &startupInfo,      // pointer to STARTUPINFO 
          &processInfo);       // pointer to PROCESS_INFORMATION  

    if (rc == False) {
      memset(&processInfo, 0, sizeof(processInfo));
      throw Exception(0, _T("Exception: Faield to CreateProcess %s\n"), cmd);
    }
  }

public:
  Process(const TCHAR* cmd, Pipe* pipe, DWORD flag = DETACHED_PROCESS) 
  {
    memset(&securityAttributes, 0, sizeof(SECURITY_ATTRIBUTES));
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = TRUE;

    memset(&startupInfo, 0, sizeof(STARTUPINFO));
    startupInfo.cb       = sizeof(STARTUPINFO);
    if (pipe) {
      startupInfo.dwFlags     = STARTF_USESTDHANDLES;
      startupInfo.hStdOutput = pipe -> getWriterHandle();
      startupInfo.hStdInput  = pipe -> getReaderHandle();
    }

    TCHAR command[MAX_PATH];
    wsprintf(command, _T("%s"), cmd);

    BOOL rc = CreateProcess(NULL,      // pointer to name of executable module 
          command,      // pointer to command line string

          &securityAttributes,  // pointer to process security attributes

          NULL,          // pointer to thread security attributes 
          TRUE,          // inheritance flag 

          flag,          // creation flags 
          NULL,          // pointer to new environment block 

          NULL,          // pointer to current directory name 
          &startupInfo,      // pointer to STARTUPINFO 
          &processInfo);       // pointer to PROCESS_INFORMATION  

    if (rc == False) {
      memset(&processInfo, 0, sizeof(processInfo));
      throw Exception(0, _T("Exception: Faield to CreateProcess %s\n"), cmd);
    }
  }


public:
  Boolean  destroy(int code=0)
  {
    Boolean rc = False;
    if (processInfo.hProcess) {
      rc = ::TerminateProcess(processInfo.hProcess, code);
    }
    return rc;
  }

public:
  HANDLE getProcessHandle() 
  {
    return processInfo.hProcess; 
  }

public:
  HANDLE getThreadHandle() 
  {
    return processInfo.hThread; 
  }

public:
  //Suspend the primary thread
  Boolean  suspend()
  {
    Boolean rc = False;
    if (processInfo.hThread) {
      rc = ::SuspendThread(processInfo.hThread);
    }
    return rc;
  }

public:
  //Resume the primary thread
  Boolean  resume()
  {
    Boolean rc = False;
    if (processInfo.hThread) {
      rc = ::ResumeThread(processInfo.hThread);
    }
    return rc;
  }

public:
  void wait(int interval=INFINITE) 
  {
    if (processInfo.hProcess) {
      WaitForSingleObject(processInfo.hProcess, interval);
    }
  }


};

}

