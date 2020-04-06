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
 *  ShareInfo.h
 *
 *****************************************************************************/

#pragma once

#include <sol/nm/NetInfo.h>

namespace SOL {

class ShareInfo: public NetInfo {

public:
  /**
   * Constructor
   */
  ShareInfo(int lv=0)
  :NetInfo(lv)
  {
  }

public:
  /**
   * Destructor
   */
  ~ShareInfo()
  {
  }

protected:
  const wchar_t* getType(DWORD value)
  {
    static const ArgT<wchar_t> types[] = {
      {L"Disk drive", STYPE_DISKTREE}, 
      {L"Print queue ", STYPE_PRINTQ},   
      {L"Communication device", STYPE_DEVICE},     
      {L"Interprocess Communication (IPC)", STYPE_IPC}, 
    };
    const wchar_t* name = L"";
    int count =  XtNumber(types);
    for(int i = 0; i<count; i++) {
      if (types[i].value == value) {
        name = types[i].name;
      }
    }
    return name;
  }

protected:
  const wchar_t* getPermission(DWORD value, __out StringBufferT<wchar_t>& buffer)
  {
    static const ArgT<wchar_t> types[] = {
      {L"ACCESS_READ", ACCESS_READ}, 
          //Permission to read data from a resource and, by default, to execute the resource. 
 
      {L"ACCESS_WRITE", ACCESS_WRITE}, 
         //Permission to write data to the resource. 
 
      {L"ACCESS_CREATE", ACCESS_CREATE}, 
         //Permission to create an instance of the resource (such as a file); data can be written to the resource as the resource is created. 
 
      {L"ACCESS_EXEC", ACCESS_EXEC}, 
         //Permission to execute the resource. 
 
      {L"ACCESS_DELETE", ACCESS_DELETE}, 
         //Permission to delete the resource. 
 
      {L"ACCESS_ATRIB", ACCESS_ATRIB}, 
         //Permission to modify the resource's attributes (such as the date and time when a file was last modified). 
 
      {L"ACCESS_PERM", ACCESS_PERM}, 
         //Permission to modify the permissions (read, write, create, execute, and delete) assigned to a resource for a user or application. 
 
      {L"ACCESS_ALL", ACCESS_ALL}, 
         //Permission to read, write, create, execute, and delete resources, and to modify their attributes and permissions. 
     };

    int count = XtNumber(types);
    int matched = 0;
    for (int i = 0; i<count; i++) {
      if (types[i].value & value) {
        if (matched>0) {
          buffer.append(L" | ");
        }
        buffer.append(types[i].name);
        matched++;
      }
    }
    return (const wchar_t*)buffer;

  }
};

}
