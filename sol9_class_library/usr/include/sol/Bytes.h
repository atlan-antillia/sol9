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
 *  Bytes.h
 *
 *****************************************************************************/

// SOL9 2009/02/17
// Renamed in the following way:
// ByteArray -> Bytes

// Array ->Bytes -> ByteArray(will be deprecated)
// 2017/01/25 Updated.

#pragma once

#include <sol\Array.h>
#include <sol\InvalidArgumentException.h>
#include <sol\OutOfRangeException.h>

/**
 * Bytes class
 */
namespace SOL {

class Bytes :public Array {
private:
  unsigned char*   bytes;

public:
  /**
   * Constructor
   */
  Bytes()
    :Array(0), bytes(NULL)
  {

  }

public:
  /**
   * Constructor
   */
  Bytes(uint size)
    :Array(size), bytes(NULL)
  {
    if (size <=0) {
      throw InvalidArgumentException("Bytes#Bytes: InvalidArgument");
    }

    bytes    = new unsigned char[size];
    memset(bytes, 0, size);
  }

public:
  /**
   * Constructor
   */
  Bytes(unsigned char* data, uint size)
    :Array(size), bytes(NULL)
  {
    if (data == NULL || size <=0) {
      throw InvalidArgumentException("Bytes#Bytes: InvalidArgument");
    }
    bytes    = new unsigned char[size];
    memcpy(bytes, data, size); 
  }

public:
  /**
   * Destructor
   */
  ~Bytes() 
  {
    clear();
  }

public:
  void  clear() 
  {
    if(bytes) {
      delete [] bytes;
    }
    setSize(0);
    bytes = NULL;
  }

public:
  void  set(const unsigned char* data, uint len) 
  {
    if (data !=NULL && len>0) {
      if (this->bytes != data) {
        delete [] bytes;
        bytes =NULL;
      }
      bytes = new unsigned char[len];
      memcpy(bytes, data, len);
      setSize(len);
    } else {
      throw InvalidArgumentException("Bytes#copy: InvalidArgument");
    }
  }

public:
  void  shallowCopy(unsigned char* data, uint len) 
  {
    if (data !=NULL && len>0) {
      if (this->bytes != data) {
        delete [] bytes;
        bytes =NULL;
      }
      this->bytes = data;
      setSize(len);
    } else {
      throw InvalidArgumentException("Bytes#copy: InvalidArgument");
    }
  }

public:
  // Simply set a Null pointer to the bytes member not to delete the bytes memory area. 
  void nullify()
  {
      this->bytes = NULL;
      setSize(0);
  }

public:
  void  copy(uint pos, const unsigned char* data, uint len) 
  {
    uint s = getSize();
    if (pos >=0 && data !=NULL && (pos + len)<=s) {
      unsigned char* ptr = (bytes + pos);
      memcpy(ptr, data, len);
    } else {
      throw InvalidArgumentException("Bytes#copy: InvalidArgument");
    }
  }

public:
  BOOL  expand(uint len) 
  {
    uint s = getSize();
    BOOL rc = FALSE;
    if (len<0) {
      throw InvalidArgumentException("Bytes#expand: InvalidArgument");
    }
    unsigned char* temp = new unsigned char[s+len];

    if(temp) {
      memset(temp, 0, s+len);
      memcpy(temp, bytes, s);
    } else {
      return rc;
    }

    s += len;
    setSize(s);

    delete [] bytes;
    bytes = temp;

    rc = TRUE;
    
    return rc;
  }

public:
  unsigned char*  getContents() 
  {
      return bytes;
  }

public:
  unsigned char    getNth(uint pos) {
    char val = NULL;
    
    if(pos>=0 && pos < getSize()) {
      val = bytes[pos];
    } else {
      throw OutOfRangeException("Bytes#getNth: Parameter is out of range");
    }
    return val;
  }

public:
  void  setNth(uint pos, unsigned char ch) 
  {
    if(pos>=0 && pos < getSize()) {
      bytes[pos] = ch;
    } else {
      throw OutOfRangeException("Bytes#setNth: Parameter is out of range");
    }
  }

public:
  const TCHAR* toString(__out _bstr_t& bstr)
  {
    if (isPrintable()) {
      size_t len = getSize();
      BYTE* b = new BYTE[len+1];
      memcpy(b, bytes, len);
      b[len] = ZERO;
      bstr = (char*)b;
      delete [] b;
      return (const TCHAR*)bstr;
    } else {
      return toHexString(bstr);
    }
  }

public:
  const TCHAR* toHexString(__out _bstr_t& bstr)
  {
    size_t len = getSize();
    size_t slen = len * 3 +1;
    TCHAR* string = new TCHAR[slen];
    TCHAR* ptr = string; 
    for (size_t i = 0; i<len; i++) {      
      _stprintf_s(ptr, slen, _T("%02x "), this->bytes[i]); 
      ptr  += 3;
      slen -= 3;
    }
    bstr = string;
    delete [] string;
    return (const TCHAR*)bstr;
  }

public:
  char* toStringWithSpace()
  {
    size_t len = getSize();
    size_t slen = len * 3 +1;
    char* string = new char[slen];
    memset(string, 0, slen);
    char* ptr = string; 
    for (size_t i = 0; i<len; i++) {
      //if (i >0 && (i %16) == 0) {
      //  printf("\n");
      //}
      
      sprintf_s(ptr, slen, "%02X ", this->bytes[i]); 
      ptr  += 3;
      slen -= 3;
    }
    return string;
  }

public:
  bool isPrintable()
  {
    bool rc = true;
    size_t len = getSize();
    for (size_t i = 0; i<len; i++) {
      if (bytes[i] == ZERO) {
        rc = false;
        break;
      }
    }
    return rc;
  }

public:
  void write()
  {
    _bstr_t string;
    toString(string);
    _tprintf(_T("%s\n"), (const TCHAR*)string);
  }

public:
  void dump()
  {
    size_t len = getSize();
    printf("Size = %d(Bytes)\n", len);
    for (size_t i = 0; i<len; i++) {
      if (i >0 && (i %16) == 0) {
        printf("\n");
      }
      printf("%02X ", this->bytes[i]); 
    }
    printf("\n");
  }

public:
  unsigned char* getData() {
    return this->bytes;
  }

public:
  //2009/03/17
  const unsigned char* getBytes() 
  {
    return this->bytes;
  }

};

}


