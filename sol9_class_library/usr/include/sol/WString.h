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
 *  WString.h
 *
 *****************************************************************************/

// SOL++2000/SOL9
// 2009/06/20 String class for wchar_t
// 2011/01/31 Added a Contructor and deepCopy methods.
// 2012/03/07 Updated Constructor to allow a shallowCopy
// 2012/04/10 Added 'contains' and 'split' methods.

#pragma once
#include <sol\Object.h>
#include <sol\OutOfMemoryException.h>
#include <sol\NullPointerException.h>
#include <sol\OutOfRangeException.h>
#include <sol\InvalidArgumentException.h>
#include <wchar.h>
#include <sol\StringConverter.h>
#include <sol\SmartPtrs.h>

namespace SOL {

class WString :public Object {
private:
  size_t    length;
  wchar_t*  text;
  
private:
  bool copy(const wchar_t* string)
  {
    bool rc = false;
    if (string != NULL) {
      size_t len = wcslen(string);

      wchar_t* temp = new wchar_t[len+1];
      if(temp) {
        wcscpy_s(temp, len+1, string);
        if(this->text != string && this->text !=NULL) {
          //_soltrace("WString::copy,1,delete text\n");
          delete [] this->text;
        }
        this->text = temp;
        this->length = len;
        rc = true;
      } else {
        //Memory allocation error.
      }
    }
    return rc;
  }

public:
  /**
   */
  WString()
    :length(0),
    text(NULL)
  {
    //_soltrace("WString::WString()\n");
  }

public:
  //2012/03/10 Added the second parameter.
  WString(const wchar_t* string, bool deepCopy=true)
  :length(0),
  text(NULL) 
  {   
    if (string) {
      if (deepCopy) {
        if (copy(string) == false) {
          throw OutOfMemoryException("WString::WString,1,Failed to create a string");
        }
      } else {
        shallowCopy((wchar_t*)string);
      }
    }
  }

public:
  //2012/06/08 
  WString(const char* mbstring)
  :length(0),
  text(NULL) 
  {   
    if (mbstring) {
      StringConverter converter;
      wchar_t* string = converter.toWideChar(mbstring);
      shallowCopy((wchar_t*)string);
    }
  }

public:
  // 2011/01/31 Added new constructor.
  // The first array parameter can be an array of non-NULL terminated usigned short.
  // The second len parameter specifies a length of the array of the array parameter.
  WString(unsigned short* array, int len)
  :length(0),
  text(NULL) 
  {
    // Create an NULL-termiinated wchar_t string of length len.
    deepCopy(array, len);
  }


  // 1999.09.03 Added
public:
  WString(const WString* string)
  :length(0),
  text(NULL) 
  {   
    if (string) {
      const wchar_t*  str = string->getContents();
      if (str == NULL) {
        return;
      }
      else {
        if (copy(str) == false) {
          throw OutOfMemoryException("WString::WString,2,Failed to create a string");
        }
      }
    }
  }


public:
  WString(const WString& string)
  :length(0),
  text(NULL)
  {
    //this->length = string.getLength();
    //this->text = NULL;
    const wchar_t* str = string.getContents();
    if (str == NULL) {
      return;
    } else {
      if (copy(str) == false) {
        throw OutOfMemoryException("Failed to create a string");
      }
    }
  }


public:
  ~WString() { 
    clear();
  }

private:
  // 2009/04/09 Modiffied to call SecureZeroMemory
  void clear() { 
    if (this->text) {
      //2009/04/09
      SecureZeroMemory(this->text, this->length);
      delete [] this->text;
    }
    this->text =NULL;
    this->length = 0;
  }

public:
  // 2009/04/09 Call SecureZeroMemory() and  delete the memory area
  void secureClear() { 
    if (this->text) {
      SecureZeroMemory(this->text, this->length);
      delete [] this->text;
    }
    this->text =NULL;
    this->length = 0;
  }

public:
  wchar_t*   getContents() const { 
    return this->text; 
  }

public:
  size_t     getLength() const  { 
    return this->length; 
  }

public:
  //2017/04/25
  bool isEmpty() {
    bool rc = false;
    if (this->length == 0 || this->text ==NULL) {
      rc = true;
    }
    return rc;
  }


public:
  operator wchar_t*() const{
    return this->text;
  }

public:
  operator const wchar_t*() const{
    return this->text;
  }

public:
  WString& operator=(const wchar_t* string)
  { 
    _soltrace("WString::operator=(const wchar_t*)\n");
    if (string != NULL) {
      if(copy(string) == false) {
        throw OutOfMemoryException("Failed to substitue a string");
      }
    }
    return *this;
  }

public:
  WString& operator=(const char* mbstring)
  { 
    _soltrace("WString::operator=(const wchar_t*)\n");
    if (mbstring != NULL) {
      StringConverter converter;
      SmartPtrs<wchar_t> string = converter.toWideChar(mbstring);
      
      if(copy((wchar_t*)string) == false) {
        
        throw OutOfMemoryException("Failed to substitue a string");
      }
    }
    return *this;
  }

public:
  // string can be non-NULL terminated string.
  void deepCopy(unsigned short* string, int len)
  {
    deepCopy((wchar_t*)(void*)string, len);
  }

public:
  //2011/01/28
  // The string parameter can be non-NULL terminated.
  void deepCopy(wchar_t* string, size_t len)
  {
    if (string != NULL && len>0) {
      if (this->text != string) {
        clear();
      }
     // int len = length;

      wchar_t* temp = new wchar_t[len+1];
      wmemcpy(temp, string, len);
      temp[len] = NULL;  //Put a NULL char at this len position to make a NULL terminated string
      this->text = temp;
      this->length = len;
    } else {
      clear();

      this->text   = NULL;//string;
      this->length = 0;
    }
  }

public:
  void shallowCopy(wchar_t* string)
  { 
    // Accept a string of NULL
    _soltrace("WString::shallowCopy(const wchar_t*)\n");
    if (string) {
      if (this->text != string) {
        clear();
      }
      this->text   = string;
      this->length = wcslen(string);
    }
    else {
      clear();

      this->text   = string;  //NULL
      this->length = 0;
      //throw InvalidArgumentException("WString::shallowCopy,InvalidArgument");
    }    
  }

public:
  WString& operator=(const WString& string)
  {        
    _soltrace("WString::operator=(const WString&)\n");

    //this->length = string.getLength();
    wchar_t* str = string.getContents();
    if (str) {
      if (copy(str) == false) {
        throw OutOfMemoryException("Failed to substitue a string");
      }
    } else {
      //str = NULL;
      clear();

      this->text = str;
      this->length = 0;
    }
    return *this;
  }

public:
  int operator==(const wchar_t* string)
  {
    int rc = 0;
    if (this->text == NULL && string ==NULL) {
      rc = 1;
    }

    //2008/07/08
    if (this->text != NULL && string != NULL) {
      if(wcscmp(this->text, string) == 0) {
        rc = 1;
      }
    }
    return rc;
  }


  //int operator==(WString& string)
public:
  int operator==(WString& string)
  {
    int rc = 0;
    const wchar_t* str = (const wchar_t*)string;
    if (this->text == NULL && str ==NULL) {
      rc = 1;
    }

    if (this->text != NULL && str != NULL) {
      if(wcscmp(this->text, str) == 0) {
        rc = 1;
      }
    }
    return rc;
  }

public:
  WString& operator+(const wchar_t* string)
  {
    if(string == NULL) {
      return *this;
    }

    this->length += wcslen(string);
    wchar_t* temp = new wchar_t[this->length+1];
    swprintf_s(temp, this->length+1, L"%s%s", this->text, string);
  
    if(this->text != string) {
      delete [] text;
    }
    text = temp;
    return *this;
  }

public:
  int compare(Object* object)
  {
    int rc = 0;
    if (object==NULL) {
      return rc;
    }

    WString* string = (WString*)object;
    const wchar_t* p1 = this->text;

    const wchar_t* p2 = (const wchar_t*)(*string);
    if (p1 == NULL && p2 == NULL) {
      rc = 1;
    }
    if (p1 != NULL && p2 != NULL) {
      rc = wcscmp(p1, p2);
    }
    return rc;
  }

  //2012/04/20
public:
  float toFloat()
  {
    float f = 0.0f;
    if (this->text) {
      f = (float)_wtof(this->text);
    }
    return f;
  }

  //2012/04/20
public:
  double toDouble()
  {
    double f = 0.0f;
    if (this->text) {
      f = _wtof(this->text);
    }
    return f;
  }

public:
  //2012/04/20
  int toInteger()
  {
    int f = 0;
    if (this->text) {
      f = _wtoi(this->text);
    }
    return f;
  }

public:
  //2012/04/20
  bool contains(const wchar_t* string)  
  {
    bool rc = false;
    if (find(string)) {
      rc = true;
    }
    return rc;
  }


public:
  const wchar_t* find(const wchar_t* string)  
  {
    const wchar_t* ptr = NULL;
    if (this->text && string) {
      ptr = wcsstr(this->text, string);
    }
    return ptr;
  }

public:
  //2012/04/20
  int split(__in const wchar_t ch, __out WString& string1, __out WString& string2)  
  {
    int rc = 0;

    if (this->text) {
      wchar_t* ptr = (wchar_t*)strchr(this->text, ch);
      if (ptr) {
        size_t len1 = (size_t)(ptr - text);
        if (len1 > 0) {
          string1.deepCopy(text, len1);
          rc++;
        }
      
        size_t len2 = this->length - len1-1;
        if (len2 > 0) {
          string2.deepCopy(++ptr, len2);
          rc++;
        }
      }
    }
    return rc;
  }


public:
  //2012/04/20
  bool containsIgnoreCase(const wchar_t* string)  
  {
    bool rc = false;
    if (findIgnoreCase(string)) {
      rc = true;
    }
    return rc;
  }

public:
  const wchar_t* findIgnoreCase(const wchar_t* string)
  {
    const wchar_t* found = NULL;
    if (this->text && string) {
      const wchar_t* ptr = this->text;
      size_t count = wcslen(string);
      for (size_t i = 0; i<this->length; i++) {
        if (_wcsnicmp(ptr, string, count) == 0) {
          found = ptr;
          break;
        }
        ptr++;
      }
    }
    return found;
  }

public:
  int replace(wchar_t oc, wchar_t nc)
  {
    int  n = 0;
    if (this->text) {
      for (size_t i = 0; i<this->length; i++) {
        if (text[i] == oc) {
          text[i] = nc;
          n++;
        }
      }
    }
    return n;
  }

//<added date="2000/11/10">
public:
  WString& operator+(wchar_t ch)
  {
    wchar_t string[80];
    swprintf_s(string, CountOf(string), L"%c", ch);
    return WString::operator+(string);
  }

public:
  WString& operator+(int num)
  {
    wchar_t string[80];
    swprintf_s(string, CountOf(string), L"%d", num);
    return WString::operator+(string);
  }

public:
  bool equals(const wchar_t* str) {
    bool rc = false;
    if(this->text != NULL && str != NULL) {
        if(wcscmp(this->text, str) == 0) {
             rc = true;
      }
    }
    return rc;
  }

public:
  bool equals(const WString& str) {
    return equals((const wchar_t*)str);
  }

public:
  bool equalsIgnoreCase(const wchar_t* str) {
    bool rc = false;

    if(this->text != NULL && str != NULL) {
        if(_wcsicmp(this->text, str) == 0) {
             rc = true;
      }
    }
    return rc;
  }

public:
  bool equalsIgnoreCase(const WString& str) {
    return equalsIgnoreCase((const wchar_t*)str);
  }

public:
  WString& operator+(float num)
  {
    wchar_t string[80];
    swprintf_s(string, CountOf(string), L"%f", num);
    return WString::operator+(string);
  }

public:
  void trim()
  {
    wchar_t* rt = WString::trim(this->text);

    if (rt) {
      clear();
      //Shallow copy
      this->text = rt;
      this->length = wcslen(rt);
    }
  }

public:
  void trimOnNewLine() {
    if (this->text) {
      wchar_t* ptr = wcsstr(this->text, L"\r\n");
      if (ptr) {
        //Terminate this text on this ptr position by putting '\0';
        *ptr = '\0';
        this->length = wcslen(this->text);
      }
    }
  }


public:
  /**
   */  
  bool   startsWith(const wchar_t* start) {
    return WString::startsWith(this->text, start);
  }

public:
  /**
   */  
  bool   startsWithIgnoreCase(const wchar_t* start) {
    return WString::startsWithIgnoreCase(this->text, start);
  }

public:
  /**
   */  
  bool   endsWith(const wchar_t* end) {
    return WString::endsWith(this->text, end);
  }

public:
  /**
   */  
  bool   endsWithIgnoreCase(const wchar_t* end) {
    return WString::endsWithIgnoreCase(this->text, end);
  }

public:
  const wchar_t* findLast(const wchar_t* string)
  {
    const wchar_t* ptr = NULL;

    if (this->text && string) {
      size_t tlen = wcslen(text);
      size_t slen = wcslen(string);
      if (tlen < slen) {
        return ptr;
      } else {
        for(size_t i = tlen - slen; i>=0; i--) {
          int n= wcsncmp(this->text + i, string, slen);
          if (n == 0) {
            ptr = this->text + i;
            break;
          }
        }
      }  
    }
    return ptr;
  }

public:
  wchar_t&    operator[](size_t n) 
  {
    if (this->text == NULL) {
      throw NullPointerException("WString::operator[] - Text is NULL");
    }
    if (n <=0 || n>this->length) {
      throw OutOfRangeException("WString::operator[] - Index is out of range");
    }
    
    //
    return text[n]; 
  }

  void display()
  {
    printf("%S\n", this->text);
  }

//////////////////////////////////////////////////////////////////////
///
public:
  static wchar_t* trim(wchar_t* string) {
    if (string == NULL) {
      return string;
    }
    
    size_t slen = wcslen(string)+1;

    wchar_t* temp = new wchar_t[slen];
    wcscpy_s(temp, slen, string);
    wchar_t* p = temp;

    while (*p == ' ' || *p == '\t' || *p =='\r' || *p=='\n') {
      p++;
    }

    wchar_t* t = p + wcslen(p) -1;
    while (*t == ' ' || *t == '\t' || *t =='\r' || *t=='\n') {
      if (p == t) break;
      *t = '\0';
      t--;
    }

    size_t plen = wcslen(p)+1;
    wchar_t* rt = new wchar_t[plen];
    wcscpy_s(rt, plen, p);

    delete [] temp;

    return rt;
  }



public:
  /**
   * 
   * @param string  
   * @param start
   * @return bool
   *
   */  
  static bool  startsWith(const wchar_t* string, const wchar_t* start) {
    bool rc = false;
    if (string != NULL && start != NULL) {
      if (wcsncmp(string, start, wcslen(start)) ==0) {
        rc = true;
      }
    }
    return rc;
  }

public:
  /**
   * 
   * @param string
   * @param start
   * @return bool
   */  
  static bool  startsWithIgnoreCase(const wchar_t* string, const wchar_t* start) {
    bool rc = false;
    if (string != NULL && start != NULL) {
  
      if (_wcsnicmp(string, start, wcslen(start)) ==0) {
        rc = true;
      }
    }
    return rc;
  }


public:
  /**
   * 
   * @param string
   * @param end
   * @return bool
   */  

  static bool endsWith(const wchar_t* string, const wchar_t* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = wcslen(string);
      size_t slen = wcslen(end);
      if (tlen >= slen) {
        if (wcsncmp(string+tlen-slen, end, slen) ==0) {
          rc = true;
        }
      }
    }
    return rc;
  }

public:
  /**
   * 
   * @param string
   * @param end  
   * @return bool
   */  
  static bool endsWithIgnoreCase(const wchar_t* string, const wchar_t* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = wcslen(string);
      size_t slen = wcslen(end);
      if (tlen >= slen) {
        if (_wcsnicmp(string+tlen-slen, end, slen) ==0) {
          rc = true;
        }
      }
    }
    return rc;
  }



};

}

