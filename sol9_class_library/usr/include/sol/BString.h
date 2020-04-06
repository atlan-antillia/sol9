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
 *  BString.h
 *
 *****************************************************************************/

#pragma once

// 2010/04/02 Added some operator+() methods.
// 2012/03/07 Updated Constructor to allow a shallowCopy

#include <sol/StringConverter.h>

namespace SOL {

class BString :public Object {

private:
  BSTR bstring;

public:
  BString()
  :bstring(NULL)
  {
  }

public:
  BString(const char* cstring)
  :bstring(NULL)
  {
    if (cstring) {
      StringConverter converter;
      this->bstring = converter.toBSTR(cstring);
    } else {
      ;//Igonre
    }
  }

public:
  BString(const BString& string)
  :bstring(NULL)
  {
    const wchar_t* wstring = (const wchar_t*)string;
    if (wstring) {
      this->bstring = SysAllocString(wstring);
    } else {
      ;//Ignore
    }
  }

public:
  BString(const wchar_t* wstring)
  :bstring(NULL)
  {
    if (wstring) {
      this->bstring = SysAllocString(wstring);
    } else {
      ;//Ignore
    }
  }


public:
  BString(const BSTR& string, bool deepCopy=true)
  :bstring(NULL)
  {
    if (string) {
      if (deepCopy) {
        this->bstring = SysAllocString(string);
      } else {
        shallowCopy(string);
      }
    } else {
      ;//Ignore
    }
  }

public:
  ~BString()
  {
    clear();
  }

public:
  operator const wchar_t*() const{
    return (const wchar_t*)this->bstring;
  }

public:
  BString& operator=(const char* cstring)
  { 
    if (cstring) {
      StringConverter converter;
      this->bstring = converter.toBSTR(cstring);
    } else {
      this->bstring = NULL;
    }
    return *this;
  }

public:
  BString& operator=(const wchar_t* wstring)
  { 
    if (wstring) {
      this->bstring = SysAllocString(wstring);
    } else {
      this->bstring = NULL;
    }    
    return *this;
  }


public:
  operator wchar_t*() const
  {
    return (wchar_t*)this->bstring;
  }

public:
  operator const BSTR() const
  {
    return this->bstring;
  }

public:
  operator BSTR()
  {
    return this->bstring;
  }

public:
  bool operator==(const wchar_t* string)
  {
    bool rc = false;
    if (this->bstring == NULL && string ==NULL) {
      rc = true;
    }

    if (this->bstring != NULL && string != NULL) {
      if(wcscmp(this->bstring, string) == 0) {
        rc = true;
      }
    }
    return rc;
  }

public:
  bool equals(const wchar_t* string)
  {
    bool rc = false;
    if (this->bstring == NULL && string ==NULL) {
      rc = true;
    }

    if (this->bstring != NULL && string != NULL) {
      if(wcscmp(this->bstring, string) == 0) {
        rc = true;
      }
    }
    return rc;
  }

public:
  bool operator==(BString& string)
  {
    bool rc = false;
    const wchar_t* str = (const wchar_t*)string;
    if (this->bstring == NULL && str ==NULL) {
      rc = true;
    }

    if (this->bstring != NULL && str != NULL) {
      if(strcmp(this->bstring, str) == 0) {
        rc = true;
      }
    }
    return rc;
  }


public:
  void clear()
  {
    if (bstring) {
      SysFreeString(bstring);
      bstring = NULL;
    }
  }

public:
  void shallowCopy(BSTR bstrAllocated)
  {
    if (this->bstring != bstrAllocated) {
      clear();
    }
    this->bstring = bstrAllocated;
  }

public:
  void print()
  {
    printf("%S\n", bstring);
  }

//2010/04/02
public:
  BString& operator+(const char* cstring)
  {
    BSTR string = NULL;
    if (cstring) {
      StringConverter converter;
      string = converter.toBSTR(cstring);
    }
    append(string);
    SysFreeString(string);

    return *this;
  }
public:
  BString& operator+(const wchar_t* wstring)
  {
    BSTR string = NULL;
    if (wstring) {
      string = SysAllocStringLen(wstring, wcslen(wstring));
    }
    append(string);
    SysFreeString(string);

    return *this;
  }


public:
  BString& operator+(BSTR string)
  {
    append(string);
    return *this;
  }


public:
  BSTR append(BSTR string)
  {
    if (string ==NULL) {
      return this->bstring;
    }
    
    int olen = 0;
    if (this->bstring) {
      olen = SysStringLen(this->bstring);
    }
    int len  = SysStringLen(string);

    BSTR constring = SysAllocStringLen(NULL, olen + len);
    
    wmemcpy(constring, this->bstring, olen);
    wmemcpy(constring + olen, string, len);

    if (this->bstring) {
      SysFreeString(this->bstring);
    }

    this->bstring = constring;
    return this->bstring;
  }

public:
  int getLength() const
  {
    long len = 0;
    if (this->bstring) {
      len = SysStringLen(this->bstring);
    }
    return len;
  }
};

}

