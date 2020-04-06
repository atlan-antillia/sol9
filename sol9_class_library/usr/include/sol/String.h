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
 *  String.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.09.03 Added a constructor to take a pointer to String.
// 2000/11/11
// 2008/07/07 Modified to define all methods in header file.

// 2009/04/09 Modified to call SecureZeroMemory in private clear() method which 
// can be called in Destructor.
// 2009/04/09 Added a method secureClear() to call SecureZeroMemory 
// and delete the memory area.
// 2009/04/10 Added a method bool isEmpty().

// 2009/10/08 Modified to use TCHAR instead of char.
// 2012/03/07 Updated Constructor to allow a shallowCopy
// 2012/04/10 Added 'contains' and 'split' methods.
// 2016/02/28 Added getCharString method.

#pragma once
#include <sol\Object.h>

#include <sol\OutOfMemoryException.h>
#include <sol\NullPointerException.h>
#include <sol\OutOfRangeException.h>
#include <sol\InvalidArgumentException.h>
#include <sol\StringConverter.h>
#include <sol/StringT.h>

namespace SOL {

class String :public Object {
private:
  size_t  length;
  TCHAR*  text;
  
private:
  bool copy(const TCHAR* string)
  {
    bool rc = false;
    if (string != NULL) {
      size_t len = strlen(string);

      TCHAR* temp = new TCHAR[len+1];
      if(temp) {
        strcpy_s(temp, len+1, string);
        if(this->text != string && this->text !=NULL) {
          //_soltrace("String::copy,1,delete text\n");
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
  String()
    :length(0),
    text(NULL)
  {
    //_soltrace("String::String()\n");
  }

public:
  //2012/03/07 
  String(const TCHAR* string, bool deepCopy=true)
  :length(0),
  text(NULL) 
  {   
    if (string) {
      if (deepCopy) {
        if (copy(string) == false) {
          throw OutOfMemoryException("String::String,1,Failed to create a string");
        }
      } else {
        shallowCopy((TCHAR*)string);
      }
    }
  }
public:
  // 2011/01/31 Added new constructor.
  // The first array parameter can be an array of non-NULL terminated TCHAR.
  // The second len parameter specifies a length of the array of the string parameter.
  String(TCHAR* array, int len)
  :length(0),
  text(NULL) 
  {
    // Create an NULL-termiinated TCHAR string of length len.
    deepCopy(array, len);
  }


#ifndef UNICODE 
public:
  String(const wchar_t* wstring, bool deepCopy=true)
  :length(0),
  text(NULL) 
  {   
    if (wstring) {
      StringConverter converter;
      StringT<char> cstring; 
      converter.toMultiByte(wstring, cstring);
      const char* str = (const char*)cstring; 
      if (deepCopy) {
        if (copy(str) == false) {
          throw OutOfMemoryException("String::String,1,Failed to create a string");
        }
      } else {
        shallowCopy((char*)str);
      }
    }
  }
#endif


#ifdef UNICODE
public:
 
  String(const char* string, bool deepCopy=true)
  :length(0),
  text(NULL) 
  {   
    if (string) {
      StringConverter converter;
      StringT<wchar_t> wstring;
      
      converter.toWideChar(string, wstring);
      const wchar_t* str = (const wchar_t*)wstring;
      if (deepCopy) {
        if (copy(str) == false) {
          throw OutOfMemoryException("String::String,1,Failed to create a string");
        }
      } else {
        shallowCopy((wchar_t*)str);
      }
    }
  }
#endif

// 1999.09.03 Added

public:
  String(const String* string)
  :length(0),
  text(NULL) 
  {   
    if (string) {
      const TCHAR*  str = string->getContents();
      if (str == NULL) {
        return;
      }
      else {
        if (copy(str) == false) {
          throw OutOfMemoryException("String::String,2,Failed to create a string");
        }
      }
    }
  }


public:
  String(const String& string)
  :length(0),
  text(NULL)
  {
    //this->length = string.getLength();
    //this->text = NULL;
    const TCHAR* str = (const TCHAR*)string;
    if (str == NULL) {
      return;
    } else {
      if (copy(str) == false) {
        throw OutOfMemoryException("Failed to create a string");
      }
    }
  }

public:
  String(const StringT<char>& string)
  :length(0),
  text(NULL)
  {
    //this->length = string.getLength();
    //this->text = NULL;
    const char* cstring  = (const char*)string;
    if (cstring == NULL) {
      return;
    }
    else {
#ifdef UNICODE
      StringConverter converter;

      StringT<wchar_t> wstring;
      converter.toWideChar(cstring, wstring);
      const wchar_t* str = (const wchar_t*)wstring;
#else 
      const char* str = cstring;
#endif
    
      if (copy(str) == false) {
        throw OutOfMemoryException("Failed to create a string");
      }
    }
  }


public:
  String(const StringT<wchar_t>& string)
  :length(0),
  text(NULL)
  {
    //this->length = string.getLength();
    //this->text = NULL;
    const wchar_t* wstring  = (const wchar_t*)string;
    if (wstring == NULL) {
      return;
    }
    else {
#ifdef UNICODE
      const wchar_t* str = wstring;

#else 
      StringConverter converter;

      StringT<char> cstring;
      converter.toMultiByte(wstring, cstring);
      const char* str = (const char*)cstring;

#endif
    
      if (copy(str) == false) {
        throw OutOfMemoryException("Failed to create a string");
      }
    }
  }

public:
  ~String() { 
    clear();
  }

  //2012/06/05
public:
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
  TCHAR*   getContents() const { 
    return this->text; 
  }

public:
  size_t     getLength() const  { 
    return this->length; 
  }

public:
  bool isEmpty() {
    //2017/04/25
    bool rc = false;
    if (this->length == 0 || this->text ==NULL) {
      rc = true;
    }
    return rc;
  }


public:
  operator TCHAR*() const{
    return this->text;
  }

public:
  operator const TCHAR*() const{
    return this->text;
  }

public:
  String& operator=(const TCHAR* string)
  { 
    _soltrace("String::operator=(const TCHAR*)\n");
    if (string != NULL) {
      if(copy(string) == false) {
        throw OutOfMemoryException("Failed to substitue a string");
      }
    }
    return *this;
  }

#ifdef UNICODE
public:
  String& operator=(const char* string)
  { 
    //_soltrace("String::operator=(const TCHAR*)\n");
    if (string != NULL) {
      StringConverter converter;
      StringT<wchar_t> wstring;
      converter.toWideChar(string, wstring);

      const wchar_t* str = (const wchar_t*)wstring;
      if(copy(str) == false) {
        throw OutOfMemoryException("Failed to substitue a string");
      }
    }
    return *this;
  }
#endif

#ifndef UNICODE
public:
  String& operator=(const wchar_t* wstring)
  { 
    //_soltrace("String::operator=(const TCHAR*)\n");
    if (wstring != NULL) {
      StringConverter converter;
      StringT<char> cstring;
      converter.toMultiByte(wstring, cstring);
      const char* str = (const char*)cstring;
      if(copy(str) == false) {
        throw OutOfMemoryException("Failed to substitue a string");
      }
    }
    return *this;
  }
#endif

public:
  //2011/01/28
  // The string parameter can be non-NULL terminated.
  void deepCopy(TCHAR* string, size_t slength)
  {
    if (string != NULL && slength>0) {
      if (this->text != string) {
        clear();
      }
      size_t len = slength;

      TCHAR* temp = new TCHAR[len+1];
      memcpy(temp, string, len);
      temp[len] = NULL;  //Put a NULL char at this len position to make a NULL terminated string
      this->text = temp;
      this->length = len;
    } else {
      clear();

      this->text   = NULL;
      this->length = 0;
    }
  }

public:
  void shallowCopy(TCHAR* string)
  { 
    // Accept a string of NULL
    _soltrace("String::shallowCopy(const TCHAR*)\n");
    if (string) {
      if (this->text != string) {
        clear();
      }
      this->text   = string;
      this->length = strlen(string);
    }
    else {
      clear();

      this->text   = string;  //NULL
      this->length = 0;
      //throw InvalidArgumentException("String::shallowCopy,InvalidArgument");
    }    
  }

public:
  String& operator=(const String& string)
  {        
    _soltrace("String::operator=(const String&)\n");

    //this->length = string.getLength();
    TCHAR* str = string.getContents();
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
  int operator==(const TCHAR* string)
  {
    int rc = 0;
    if (this->text == NULL && string ==NULL) {
      rc = 1;
    }

    //2008/07/08
    if (this->text != NULL && string != NULL) {
      if(strcmp(this->text, string) == 0) {
        rc = 1;
      }
    }
    return rc;
  }


  //int operator==(String& string)
public:
  int operator==(String& string)
  {
    int rc = 0;
    const TCHAR* str = (const TCHAR*)string;
    if (this->text == NULL && str ==NULL) {
      rc = 1;
    }

    if (this->text != NULL && str != NULL) {
      if(strcmp(this->text, str) == 0) {
        rc = 1;
      }
    }
    return rc;
  }

public:
  String& operator+(const TCHAR* string)
  {
    if(string == NULL) {
      return *this;
    }

    this->length += strlen(string);
    TCHAR* temp = new TCHAR[this->length+1];
    _stprintf_s(temp, this->length+1, _T("%s%s"), this->text, string);
    /*
    */
    if(this->text != string) {
      delete [] text;
    }
    text = temp;
    return *this;
  }

#ifdef UNICODE
public:
  String& operator+(const char* string)
  {
    if(string == NULL) {
      return *this;
    }
    StringConverter converter;
    wchar_t* wstring = converter.toWideChar(string);

    this->length += strlen(wstring);
    wchar_t* temp = new wchar_t[this->length+1];
    _stprintf_s(temp, this->length+1, _T("%s%s"), this->text, wstring);

    if(this->text != wstring) {
      delete [] text;
    }
    text = temp;

    delete [] wstring;

    return *this;
  }
#endif

#ifndef UNICODE
public:
  String& operator+(const wchar_t* wstring)
  {
    if(wstring == NULL) {
      return *this;
    }
    StringConverter converter;
    const char* cstring = converter.toMultiByte(wstring);

    this->length += strlen(cstring);
    char* temp = new char[this->length+1];
    sprintf_s(temp, this->length+1, "%s%s", this->text, cstring);

    if(this->text != temp) {
      delete [] text;
    }
    text = temp;

    delete [] cstring;

    return *this;
  }
#endif

public:
  int compare(Object* object)
  {
    int rc = 0;
    if (object==NULL) {
      return rc;
    }

    String* string = (String*)object;
    const TCHAR* p1 = this->text;

    const TCHAR* p2 = (const TCHAR*)(*string);
    if (p1 == NULL && p2 == NULL) {
      rc = 1;
    }
    if (p1 != NULL && p2 != NULL) {
      rc = strcmp(p1, p2);
    }
    return rc;
  }

  //2012/04/20
public:
  float toFloat()
  {
    float f = 0.0f;
    if (this->text) {
      f = (float)_ttof(this->text);
    }
    return f;
  }

  //2012/04/20
public:
  double toDouble()
  {
    double f = 0.0f;
    if (this->text) {
      f = _ttof(this->text);
    }
    return f;
  }

public:
  //2012/04/20
  int toInteger()
  {
    int f = 0;
    if (this->text) {
      f = _ttoi(this->text);
    }
    return f;
  }

public:
  //2012/04/10
  bool contains(const TCHAR* string)  
  {
    bool rc = false;
    if (find(string)) {
      rc = true;
    }
    return rc;
  }

public:
  const TCHAR* find(const TCHAR* string)  
  {
    const TCHAR* ptr = NULL;
    if (this->text && string) {
      ptr = strstr(this->text, string);
    }
    return ptr;
  }

public:
  int split(__in const TCHAR ch, __out String& string1, __out String& string2)  
  {
    int rc = 0;

    if (this->text) {
      TCHAR* ptr = (TCHAR*)strchr(this->text, ch);
      if (ptr) {
        size_t len1 = ptr - text;
        if (len1 > 0) {
          string1.deepCopy(text, len1);
          //_tprintf(_T("1=[%s]\n"), (const TCHAR*)string1);
          rc++;
        }
      
        size_t len2 = this->length - len1-1;
        if (len2 > 0) {
          string2.deepCopy(++ptr, len2);
          //_tprintf(_T("2=[%s]\n"), (const TCHAR*)string2);
          rc++;
        }
      }
    }
    return rc;
  }

public:
  int replace(TCHAR oc, TCHAR nc)
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
public:
  //2009/11/16
  bool removeBackSlash()
  {
    bool rc = false;
    if (this->text && this->length>0) {
      if (this->text[this->length-1] == '\\') {
        this->text[this->length-1] = '\0';
        this->length--;
        rc = true;
      }
    }
    return rc;
  }


//<added date="2000/11/10">
public:
  String& operator+(TCHAR ch)
  {
    TCHAR string[80];
    //sprintf_s(string, sizeof(string), "%c", ch);
    string[0] = ch;
    string[1] = (TCHAR)0;//ZERO;

    return String::operator+(string);
  }

public:
#ifdef UNICODE
  String& operator+(char ch)
  {
    TCHAR string[80];
    //sprintf_s(string, sizeof(string), "%c", ch);
    string[0] = (TCHAR)ch;
    string[1] = (TCHAR)0;//ZERO;

    return String::operator+(string);
  }
#endif

public:
  String& operator+(int num)
  {
    TCHAR string[80];
    _stprintf_s(string, CountOf(string), _T("%d"), num);

    return String::operator+(string);
  }

public:
  bool equals(const TCHAR* str) {
    bool rc = false;
    if(this->text != NULL && str != NULL) {
        if(strcmp(this->text, str) == 0) {
             rc = true;
      }
    }
    return rc;
  }

public:
  bool equals(const String& str) {
    return equals((const TCHAR*)str);
  }

public:
  bool equalsIgnoreCase(const TCHAR* str) const {
    bool rc = false;

    if(this->text != NULL && str != NULL) {
      //strcmpi -> stricmp
        if(_stricmp(this->text, str) == 0) {
             rc = true;
      }
    }
    return rc;
  }

public:
  bool equalsIgnoreCase(const String& str) const {
    return equalsIgnoreCase((const TCHAR*)str);
  }

public:
  String& operator+(float num)
  {
    TCHAR string[80];
    _stprintf_s(string, CountOf(string), _T("%f"), num);

    return String::operator+(string);
  }

public:
  void trim()
  {
    TCHAR* rt = String::trim(this->text);

    if (rt) {
      clear();
      //Shallow copy
      this->text = rt;
      this->length = strlen(rt);
    }
  }

public:
  void trimOnNewLine() {
    if (this->text) {
      TCHAR* ptr = (TCHAR*)strstr(this->text, _T("\r\n"));
      if (ptr) {
        //Terminate this text on this ptr position by putting '\0';
        *ptr = '\0';
        this->length = strlen(this->text);
      }
    }
  }


public:
  /**
   */  
  bool   startsWith(const TCHAR* start) {
    return String::startsWith(this->text, start);
  }

public:
  /**
   */  
  bool   startsWithIgnoreCase(const TCHAR* start) {
    return String::startsWithIgnoreCase(this->text, start);
  }

public:
  /**
   */  
  bool   endsWith(const TCHAR* end) {
    return String::endsWith(this->text, end);
  }

public:
  /**
   */  
  bool   endsWithIgnoreCase(const TCHAR* end) {
    return String::endsWithIgnoreCase(this->text, end);
  }

public:
  //2009/11/12
  const TCHAR* findLast(const TCHAR* string)
  {
    return String::findLast(this->text, string);
  }

public:
  //2009/11/12
  static const TCHAR* findLast(const TCHAR* text, const TCHAR* string)
  {
    const TCHAR* ptr = NULL;

    if (text && string) {
      size_t tlen = strlen(text);
      size_t slen = strlen(string);
      if (tlen < slen) {
        return ptr;
      } else {
        for(size_t i = tlen - slen; i>=0; i--) {
          int n= strncmp(text + i, string, slen);
          if (n == 0) {
            ptr = text + i;
            break;
          }
        }
      }  
    }
    return ptr;
  }

public:
  //2009/11/12
  const TCHAR* findFirst(const TCHAR* string) {
    return String::findFirst(this->text, string);    
  }

public:
  //2009/11/12
  static const TCHAR* findFirst(const TCHAR* text, const TCHAR* string) {
    const TCHAR* ptr = NULL;
    if (text && string) {
      ptr = strstr(text, string);
    }
    return ptr;
  }


public:
  TCHAR&    operator[](size_t n) 
  {
    if (this->text == NULL) {
      throw NullPointerException("String::operator[] - Text is NULL");
    }
    if (n <=0 || n>this->length) {
      throw OutOfRangeException("String::operator[] - Index is out of range");
    }
    
    return text[n]; 
  }


public:
  // If UNICODE environment, then this->text is wcstring.
  //  convert it to mbstring and return it to parameter string.
  // If not, then this->text is mbstring, and return it to parameter string. 
  // 2009/10/26 Addecd cnst
  bool getString(__out StringT<char>& tstring) const
  {
    bool rc = false;

    if (text == NULL) {
      return rc;      
    }
#ifdef UNICODE
    
    wchar_t* wcstring = text;
    
    int cb = WideCharToMultiByte(CP_ACP, 0, 
        wcstring, -1, NULL, 0, NULL, NULL);
    
    if (cb > 0) {
      char* mbstring = new char[cb];
      mbstring[0] = ZERO;
      WideCharToMultiByte(CP_ACP, 0, wcstring, -1, mbstring, cb, NULL, NULL);
      tstring.shallowCopy(mbstring);
      rc = true;
    }

#else 
    //2009/11/01
    tstring = (char*)text;
    rc = true;
#endif

    return rc;
  }

public:
  // If UNICODE environment, then this->text is wcstring.
  //  convert it to mbstring and return it to parameter string.
  // If not, then this->text is mbstring, and return it to parameter string. 
  // 2016/02/27 Addecd cnst
  StringT<char> getCharString() const
  {
    if (text == NULL) {
      return StringT<char>("");      
    }
#ifdef UNICODE
    
    wchar_t* wcstring = text;
    
    const int cb = WideCharToMultiByte(CP_ACP, 0, 
        wcstring, -1, NULL, 0, NULL, NULL);
    
    if (cb > 0) {
      char* mbstring = new char[cb];
      mbstring[0] = ZERO;
      WideCharToMultiByte(CP_ACP, 0, wcstring, -1, mbstring, cb, NULL, NULL);
      //Specify shallow copy flag to be false, because we allocae mbstring above,
      return StringT<char>((const char*)mbstring, false);
    }

#else 
    return StringT<char>((char*)text);
#endif
    return StringT<char>("");
  }

public:
  // If UNICODE environment, then this->text is wcstring.
  //  and return it to parameter string.
  // If not, then this->text is mbstring, and return convert it to
  // wcstring and return it to parameter string. 
  // 2009/10/26 Addecd cnst
  bool getString(__out StringT<wchar_t>& tstring) const
  {
    bool rc = false;

    if (text == NULL) {
      return rc;      
    }

#ifdef UNICODE
    tstring = text;
    rc = true;
#else 
    rc = true;
    char* mbstring = text;
    int cb = MultiByteToWideChar(CP_ACP, 0, mbstring, -1, NULL, 0); 
    if (cb >0) {
      wchar_t* wcstring = new wchar_t[cb];
      wcstring[0] = ZERO;
      MultiByteToWideChar(CP_ACP, 0, mbstring, -1, wcstring, cb);
      tstring.shallowCopy(wcstring);
      rc = true;
    }
#endif

    return rc;
  }


//////////////////////////////////////////////////////////////////
//Å@static methods

public:
  static char* trim(__in char* string) {
    if (string == NULL) {
      return NULL;
    }
    
    size_t slen = strlen(string)+1;

    char* temp = new char[slen];
    strcpy_s(temp, slen, string);
    char* p = temp;

    while (*p == ' ' || *p == '\t' || *p =='\r' || *p=='\n') {
      p++;
    }

    char* t = p + strlen(p) -1;
    while (*t == ' ' || *t == '\t' || *t =='\r' || *t=='\n') {
      if (p == t) break;
      *t = '\0';
      t--;
    }

    size_t plen = strlen(p)+1;
    char* rt = new char[plen];
    strcpy_s(rt, plen, p);

    delete [] temp;

    return rt;
  }

public:
  static wchar_t* trim(__in wchar_t* string) {
    if (string == NULL) {
      return NULL;
    }
    
    size_t slen = strlen(string)+1;

    wchar_t* temp = new wchar_t[slen];
    strcpy_s(temp, slen, string);
    wchar_t* p = temp;

    while (*p == ' ' || *p == '\t' || *p =='\r' || *p=='\n') {
      p++;
    }

    wchar_t* t = p + strlen(p) -1;
    while (*t == ' ' || *t == '\t' || *t =='\r' || *t=='\n') {
      if (p == t) break;
      *t = '\0';
      t--;
    }

    size_t plen = strlen(p)+1;
    wchar_t* rt = new wchar_t[plen];
    strcpy_s(rt, plen, p);

    delete [] temp;

    return rt;
  }

public:
  static bool trim(__in TCHAR* string, __out String& tstring) {
    bool rc = false;
    if (string == NULL) {
      return rc;
    }

    TCHAR* trimmed = trim(string);
    if (trimmed) {
      tstring = trimmed;
    }
    return rc;
  }
public:
  static bool trim(__in char* string, __out StringT<char>& tstring) {
    bool rc = false;
    if (string == NULL) {
      return rc;
    }

    char* trimmed = trim(string);
    if (trimmed) {
      tstring.shallowCopy(trimmed);
    }
    return rc;
  }

public:
  static bool trim(__in wchar_t* string, __out StringT<wchar_t>& tstring) {
    bool rc = false;
    if (string == NULL) {
      return rc;
    }

    wchar_t* trimmed = trim(string);
    if (trimmed) {
      tstring.shallowCopy(trimmed);
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
  static bool  startsWith(__in const char* string, __in const char* start) {
    bool rc = false;
    if (string != NULL && start != NULL) {
      if (strncmp(string, start, strlen(start)) ==0) {
        rc = true;
      }
    }
    return rc;
  }

public:
  static bool  startsWith(__in const wchar_t* string, __in const wchar_t* start) {
    bool rc = false;
    if (string != NULL && start != NULL) {
      if (strncmp(string, start, strlen(start)) ==0) {
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
  static bool  startsWithIgnoreCase(__in const char* string, __in const char* start) {
    bool rc = false;
    if (string != NULL && start != NULL) {
      if (_strnicmp(string, start, strlen(start)) ==0) {
        rc = true;
      }
    }
    return rc;
  }

public:
  static bool  startsWithIgnoreCase(__in const wchar_t* string, __in const wchar_t* start) {
    bool rc = false;
    if (string != NULL && start != NULL) {
  
      if (_strnicmp(string, start, strlen(start)) ==0) {
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
  static bool endsWith(__in const char* string, __in const char* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = strlen(string);
      size_t slen = strlen(end);
      if (tlen >= slen) {
        if (strncmp(string+tlen-slen, end, slen) ==0) {
          rc = true;
        }
      }
    }
    return rc;
  }

public:
  static bool endsWith(__in const wchar_t* string, __in const wchar_t* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = strlen(string);
      size_t slen = strlen(end);
      if (tlen >= slen) {
        if (strncmp(string+tlen-slen, end, slen) ==0) {
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
  static bool endsWithIgnoreCase(__in const char* string, __in const char* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = strlen(string);
      size_t slen = strlen(end);
      if (tlen >= slen) {
        if (_strnicmp(string+tlen-slen, end, slen) ==0) {
          rc = true;
        }
      }
    }
    return rc;
  }

public:
  static bool endsWithIgnoreCase(__in const wchar_t* string, __in const wchar_t* end) {
    bool rc = false;
    if (string != NULL && end != NULL) {
      size_t tlen = strlen(string);
      size_t slen = strlen(end);
      if (tlen >= slen) {
        if (_strnicmp(string+tlen-slen, end, slen) ==0) {
          rc = true;
        }
      }
    }
    return rc;
  }


};

}

