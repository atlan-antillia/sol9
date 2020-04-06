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
 *  Auxdef.h
 *
 *****************************************************************************/

// SOL9
// 2010/04/08 Modified not to use null, Error and Success macros.

#pragma once

#include <math.h>

#ifndef Key
//typedef  unsigned long  Key;
typedef LONG_PTR Key;
#endif

#ifndef LONG_PTR
//typedef   unsigned long  LONG_PTR;
typedef   LONG_PTR  LONG_PTR;

#endif

#ifndef uint
typedef  unsigned int  uint;
#endif

//2008/07/03
#ifndef ushort
typedef  unsigned short  ushort;
#endif

#ifndef uchar
typedef  unsigned char  uchar;
#endif

#ifndef Boolean
typedef  int      Boolean;
#endif

//2010/04/08
//#define null    NULL

#define INVALID_VALUE (-1)

#define True    1
#define False    0
//2010/04/08
//#define Error       -1

//2-16/01/10 
//#define Zero        '\0'
#define ZERO        '\0'

//#define Success     0

#define XtNumber(a)  (int)( sizeof(a)/sizeof(a[0]) )
#define CountOf(a)   (int)( sizeof(a)/sizeof(a[0]) )
#define NumberOf(a)  (int)( sizeof(a)/sizeof(a[0]) )

#define LINE_LENGTH 256
#define MAX_LEN      256
#define RealX(x)   (x)*(LOWORD(GetDialogBaseUnits()))/4
#define RealY(y)   (y)*(HIWORD(GetDialogBaseUnits()))/8

#define  SIZE_1KB    1024

#define SIZE_128B    128

#define  CHAR_CR    0X0D
#define  CHAR_LF    0X0A

#define CHAR_DOT  '.'
#define CHAR_BSLASH  '\\'
#define CHAR_TAB  '\t'


//2009/10/13

#define NO_REDRAW      CS_DBLCLKS  
#define NO_REDRAW_NO_DBLCLICK  0

//2012/09/09
#define NOT_OK(hr) (hr!=S_OK)

//2012/12/10
//EXCEPTION FATAL
#define E_FATAL  -1
#define PATH_LEN  1024

#ifdef UNICODE
inline void _tmemset(wchar_t* ptr, wchar_t value, size_t count) {
  wmemset(ptr, value, count);
}
#else
inline void _tmemset(char* ptr, char value, size_t count) {
  memset(ptr, value, count);
}
#endif

//2015/07/22
//2015/10/01 Modified to use TCHAR instead of char
inline const TCHAR* appName(const TCHAR* fullpath)
{
  const TCHAR* name = _T("");
  if (fullpath) {
    const TCHAR* tmp = _tcsrchr(fullpath, TCHAR('\\'));
    if (tmp) {
      tmp++;
      name = tmp;
    }
  }
  return name;
}

inline const TCHAR* appDirectory(const TCHAR* fullpath, TCHAR* directory, size_t length)
{
 //const TCHAR* name = _T("");
  if (fullpath && directory && length >= _tcslen(fullpath)) {
    const TCHAR* start = fullpath;
    const TCHAR* tmp   = _tcsrchr(fullpath, TCHAR('\\'));
    if (tmp) {
      tmp++;
      size_t len = tmp - start;
      _tcsncpy_s(directory, length, fullpath, len);
      directory[len] = NULL;
    }
  }
  return directory;
}

#define MATH_PI   3.14159265f

inline float SIN(int degree)
{
  float radian = (float)degree * MATH_PI / 180.0f;
  return (float)sin(radian);
}
  
inline float COS(int degree)
{ 
  float radian = (float)degree * MATH_PI / 180.0f;
  return (float)cos(radian);
}

inline float SIN(float degree)
{
  float radian = degree * MATH_PI / 180.0f;
  return (float)sin(radian);
}
  
inline float COS(float degree)
{ 
  float radian = degree * MATH_PI / 180.0f;
  return (float)cos(radian);
}


