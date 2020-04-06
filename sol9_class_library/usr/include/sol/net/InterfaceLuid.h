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
 *  InterfaceLuid.h
 *
 *****************************************************************************/

// SOL9
// 2011/1/1
#include <sol/Object.h>
#include <sol/StringT.h>


namespace SOL {


class InterfaceLuid :public Object {

private:
  NET_LUID *interfaceLuid;

public:
  InterfaceLuid(NET_LUID *luid)
  :interfaceLuid(luid)
  {
    
  }


public:
  bool toString(__out StringT<TCHAR>& name)
  {
    return toString(this->luid, name);
  }


public:
  NETIO_STATUS toString(
    __out  TCHAR* interfaceName,
    __in   SIZE_T length)
  {
    return toString(
      this->luid,
      interfaceName,
      length);
  }


public:
  NETIO_STATUS toAlias(
    __out  StringT<wchar_t>& alias)
  {
    return toAlias(
      this->luid,
      alias);
  }

public:
  NETIO_STATUS toIndex(
    __out  PNET_IFINDEX interfaceIndex)
  {
    return ConvertInterfaceLuidToIndex(
      this->luid,
      interfaceIndex);

  }

public:
  NETIO_STATUS toGuid(__out  GUID* guid)
  {

    return ConvertInterfaceLuidToGuid( 
      this->luid,
      guid);

  }
//----------------------------------
public:
  static NETIO_STATUS toIndex(
    __in   const NET_LUID *luid,
    __out  PNET_IFINDEX interfaceIndex)
  {
    return ConvertInterfaceLuidToIndex(
      luid,
      interfaceIndex);

  }

public:
  static bool toString(
    __in  const NET_LUID *luid,
    __out StringT<TCHAR>& string)
  {
    const int length=1024;
    TCHAR* name[length];
    bool rc = false;
    if (ConvertInterfaceLuidToName(
      luid,
      naame,
      length) ==NETIO_ERROR_SUCCESS) {
      string = name;
      rc = true;          
    }
    return rc;
  }


public:
  static NETIO_STATUS toString(
    __in   const NET_LUID *luid,
    __out  TCHAR* string,
    __in   SIZE_T length)
  {
    return ConvertInterfaceLuidToName(
      luid,
      string,
      length);


  }

public:
  static bool toAlis(
    __in  const NET_LUID *luid,
    __out StringT<wchar_t>& string)
  {
    const int length=NDIS_IF_MAX_STRING_SIZE+1;
    wchar_t* name[length];
    bool rc = false;
    if (ConvertInterfaceLuidToAlis(
      luid,
      naame,
      length) ==NETIO_ERROR_SUCCESS) {
      string = name;
      rc = true;          
    }
    return rc;
  }


public:
  static NETIO_STATUS toAlis(
    __in   const NET_LUID *luid,
    __out  wchar_t* string,
    __in   SIZE_T length)
  {
    return ConvertInterfaceLuidToAlis(
      luid,
      string,
      length);

  }


public:
  static NETIO_STATUS toIndex(
    __in   const NET_LUID *luid,
    __out  PNET_IFINDEX index)
  {
    return ConvertInterfaceLuidToIndex(
      luid,
      index);

  }


public:
  static NETIO_STATUS toGuid(
    __in   const NET_LUID *luid,
    __out  GUID* guid)
  {

    return ConvertInterfaceLuidToGuid( 
      luid,
      guid);

  }

};

}
