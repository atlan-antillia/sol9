/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DnsRecordT.h
 *
 *****************************************************************************/

// SOL9
// 2011/1/2
// 2011/1/14 Modified data member to be a pointer to T.

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/net/IPv4Address.h>
#include <sol/net/IPv6Address.h>
#include <sol/ArgT.h>
#include <sol/dns/DnsData.h>

/*
typedef struct _DnsRecordFlags {
  DWORD Section  :2;
  DWORD Delete  :1;
  DWORD CharSet  :2;
  DWORD Unused  :3;
  DWORD Reserved  :24;
} DNS_RECORD_FLAGS;
*/

namespace SOL {

template <class T> class DnsRecordT :public DnsObject {

private:
  StringT<TCHAR>   name;

  WORD  type;

  DWORD  ttl;

  DNS_RECORD_FLAGS  flags;

  WORD    dataLength;

  T*    data;

public:
  /**
   * Constructor
   */
  DnsRecordT()
  :name(_T("")),
  type(0),
  dataLength(0),
  data(NULL)
  {
    memset(&flags, 0, sizeof(flags));
  }

public:
  ~DnsRecordT()
  {
    clear();
  }


public:
  void clear()
  {
    if (data) {
      delete [] (BYTE*)data;
      data = NULL;
    }
  }


public:
  // 2011/1/14 Modifed to use a dataLength parameter.
  void copy(const TCHAR* pName, WORD wType, DWORD dwTtl, DNS_RECORD_FLAGS& sFlags, WORD wDataLength, T& t)
  {
    name = pName;
    type = wType;
    ttl  = dwTtl;
    memcpy(&flags, &sFlags, sizeof(flags));
    dataLength = wDataLength;

    if (dataLength>0) {
      data = (T*)new BYTE[dataLength];
      memcpy(data, &t, dataLength);
    }
  }


public:
  const TCHAR* getName()
  {
    return (const TCHAR*)name;
  }

public:
  WORD getType()
  {
    return type;
  }

public:
  DNS_RECORD_FLAGS& getFlags()
  {
    return flags;
  }

public:
  T& getData()
  {
    return *data;
  }

public:
  operator const T*() const 
  {
    return data;
  }

public:
  const TCHAR* getFlagsSection(int sec)
  {
    const ArgT<TCHAR> names[]={
      {_T("Question"),   DNSREC_QUESTION},
      {_T("Answer"),     DNSREC_ANSWER},
      {_T("Authority"),  DNSREC_AUTHORITY},
      {_T("Additional"), DNSREC_ADDITIONAL}
    };
    const TCHAR* name=NULL;
    for (int i=0; i<CountOf(names); i++) {
      if ((int)names[i].value == sec) {
        name=names[i].name;
        break;
      }
    }
    return name;
  }

public:
  const TCHAR* getFlagsCharSet(int sec)
  {
    const ArgT<TCHAR> names[]={
      {_T("Unknown"), DnsCharSetUnknown},
      {_T("Unicode"), DnsCharSetUnicode},
      {_T("Utf8"),    DnsCharSetUtf8},
      {_T("Ansi"),    DnsCharSetAnsi}
    };
    const TCHAR* name=NULL;
    for (int i=0; i<CountOf(names); i++) {
      if ((int)names[i].value == sec) {
        name=names[i].name;
        break;
      }
    }
    return name;
  }

public:
  void display()
  {
    _tprintf(_T("Name=%s\n"), (const TCHAR*)name);
    const TCHAR* sec = getFlagsSection(flags.Section);
    if (sec) {
      _tprintf(_T("Section=%s\n"), sec);
    }
    const TCHAR* charset = getFlagsCharSet(flags.CharSet);
    if (charset) {
      _tprintf(_T("CharSet=%s\n"), charset);
    }
    _tprintf(_T("Ttl=%d(seconds)\n"), ttl);
    _tprintf(_T("dataLength=%d\n"), dataLength);
    
    DnsData dnsData;
    dnsData.display(*data);
    _tprintf(_T("\n"));

  }
};

}
