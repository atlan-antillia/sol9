/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileFlagsAndAttributes.h
 *
 *****************************************************************************/


// 2012/10/30
// This class is for IShellItem and IShellItem2 interfaces.

#pragma once
#include <sol/Object.h>
#include <sol/ArgT.h>
#include <sol/StringBufferT.h>
#include <shobjidl.h>

namespace SOL {

class FileFlagsAndAttributes: public Object {

public:
  public:
  static _bstr_t toString(DWORD value)
  {
    ArgT<TCHAR> names[] = {

    {_T("ARCHIVE"), FILE_ATTRIBUTE_ARCHIVE},
    {_T("ENCRYPTED"), FILE_ATTRIBUTE_ENCRYPTED},  
    {_T("HIDDEN"), FILE_ATTRIBUTE_HIDDEN}, 
    {_T("NORMAL"), FILE_ATTRIBUTE_NORMAL}, 
    {_T("OFFLINE"), FILE_ATTRIBUTE_OFFLINE}, 
    {_T("READONLY"), FILE_ATTRIBUTE_READONLY}, 
    {_T("SYSTEM"), FILE_ATTRIBUTE_SYSTEM}, 
    {_T("TEMPORARY"), FILE_ATTRIBUTE_TEMPORARY}, 
    {_T("BACKUP_SEMANTICS"), FILE_FLAG_BACKUP_SEMANTICS},  
    {_T("DELETE_ON_CLOSE"), FILE_FLAG_DELETE_ON_CLOSE}, 
    {_T("NO_BUFFERING"), FILE_FLAG_NO_BUFFERING}, 
    {_T("OPEN_NO_RECALL"), FILE_FLAG_OPEN_NO_RECALL}, 
    {_T("OPEN_REPARSE_POINT"), FILE_FLAG_OPEN_REPARSE_POINT},  
    {_T("OVERLAPPED"), FILE_FLAG_OVERLAPPED}, 
    {_T("POSIX_SEMANTICS"), FILE_FLAG_POSIX_SEMANTICS}, 
    {_T("RANDOM_ACCESS"), FILE_FLAG_RANDOM_ACCESS}, 
    //{_T("SESSION_AWARE"), FILE_FLAG_SESSION_AWARE}, 
    {_T("FLAG_SEQUENTIAL_SCAN"), FILE_FLAG_SEQUENTIAL_SCAN}, 
    {_T("WRITE_THROUGH"), FILE_FLAG_WRITE_THROUGH}, 
    {_T("ANONYMOUS"), SECURITY_ANONYMOUS},
    {_T("CONTEXT_TRACKING"), SECURITY_CONTEXT_TRACKING}, 
    {_T("DELEGATION"), SECURITY_DELEGATION},
    {_T("EFFECTIVE_ONLY"), SECURITY_EFFECTIVE_ONLY},  
    {_T("IDENTIFICATION"), SECURITY_IDENTIFICATION},
    {_T("IMPERSONATION"), SECURITY_IMPERSONATION},
    };
 
    StringBufferT<TCHAR> buffer;
    int n = 0;
    for (int i = 0; i<CountOf(names); i++) {
      if (value & names[i].value) {
        if (n > 0) {
          buffer.append(_T("|"));
        }
        buffer.append(names[i].name);
        n++;
      }
    }
    return _bstr_t((const TCHAR*)buffer);
  }
};

}
