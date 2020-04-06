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
 *  Wchardef.h
 *
 *****************************************************************************/

//2015/12/11

//SOL9 2.0

#pragma once
//2015/08/22
#define _CRT_NON_CONFORMING_SWPRINTFS 1
#define  _CRT_SECURE_NO_WARNINGS      1

//#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <direct.h>
#include <memory.h>
#include <wchar.h>

//namespace SOL {

// strdup
inline wchar_t* new_strdup(const wchar_t *strSource ) 
{
  if (!strSource) {
    throw -1;
  }
  size_t size = wcslen(strSource)+1;
  //wchar_t* string = new wchar_t[wcslen(strSource)+1];
  wchar_t* string = new wchar_t[size];
  
  //wcscpy(string, strSource);
  wcscpy_s(string, size, strSource);

  return string;
}

// strdup
inline wchar_t* _strdup(const wchar_t *strSource ) 
{
  return _wcsdup( strSource);
}

// strdup
//2011/1/17
inline wchar_t* strdup(const wchar_t *strSource ) 
{
  return _wcsdup(strSource);
}



inline wchar_t* strtok(wchar_t* strToken, const wchar_t* strDelimit)
{
  wchar_t *context = NULL;
  //return wcstok(strToken, strDelimit);
  return wcstok_s(strToken, strDelimit, &context);
}

inline wchar_t *strtok_s(wchar_t *strToken,const wchar_t *strDelimit, wchar_t **context)
{
  return wcstok_s(strToken, strDelimit, context);
}


inline errno_t strcat_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource)
{
  return wcscat_s(strDestination, numberOfElements, strSource);
}
 
  
inline errno_t strncat_s(wchar_t *strDest, size_t numberOfElements, const wchar_t *strSource, size_t count) 
{
  return wcsncat_s(strDest, numberOfElements,strSource, count);

}



//strcmp
inline int strcmp(const wchar_t *string1, const wchar_t *string2) 
{
  return wcscmp(string1, string2);
}

inline int _stricmp(const wchar_t *string1,const wchar_t *string2)
{
  return _wcsicmp(string1,string2);
}

//stricmp_l
inline int _stricmp_l(const wchar_t *string1, const wchar_t *string2, _locale_t locale) 
{
  return _wcsicmp_l(string1, string2, locale);
}

//strncmp
inline int strncmp(const wchar_t *string1, const wchar_t *string2, size_t count) 
{
  return wcsncmp(string1, string2, count);
}

//strnicmp
inline int strnicmp(const wchar_t *string1, const wchar_t *string2, size_t count) 
{
  return _wcsnicmp(string1, string2, count);
}

//strspn
inline size_t strspn(const wchar_t *str,const wchar_t *strCharSet)
{
  return wcsspn(str,strCharSet);
}

//strncpy
/*
inline wchar_t* strncpy(wchar_t *a, const wchar_t *b, size_t count) 
{
  return wcsncpy(a, b, count);
}
*/
  
inline errno_t strcpy_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource )
{
  return wcscpy_s(strDestination, numberOfElements, strSource);
}


inline errno_t strncpy_s(wchar_t *strDest, size_t numberOfElements, const wchar_t *strSource, size_t count)
{
  return wcsncpy_s(strDest, numberOfElements, strSource, count);
}

// strtod
inline double strtod(const wchar_t *nptr,wchar_t **endptr)
{
  return wcstod(nptr,endptr);
}


// strtol
inline long strtol(const wchar_t *a, wchar_t **b, int c) 
{
  return wcstol(a, b, c);
}

inline long _strtol_l(const wchar_t *nptr, wchar_t **endptr,int base, _locale_t locale)
{
  return _wcstol_l(nptr, endptr, base, locale);
}

// strtoul
inline unsigned long strtoul(const wchar_t *nptr, wchar_t **endptr, int base)
{
  return wcstoul(nptr,endptr, base);
}

inline unsigned long _strtoul_l(const wchar_t *nptr,wchar_t **endptr,int base, _locale_t locale)
{
  return _wcstoul_l(nptr,endptr, base, locale);
}

//_strnicmp
inline int _strnicmp(const wchar_t *a, const wchar_t *b, size_t c) 
{
  return _wcsnicmp(a,b,c);
}


//strlen
inline size_t strlen(const wchar_t* string) 
{
  return wcslen(string);
}


//strnlen
inline size_t strnlen(const wchar_t *str, size_t numberOfElements)
{
  return wcsnlen(str, numberOfElements);
}

  
//strcpy 2012/07/11
inline errno_t strcpy(wchar_t *a, size_t size, const wchar_t *b) 
{
  return wcscpy_s(a, size, b);
}



inline errno_t _strnset_s(wchar_t *str, size_t numberOfElements,wchar_t c, size_t count)
{
  return _wcsnset_s(str, numberOfElements, c, count);
}



//atoi
inline int atoi(const wchar_t *a) 
{
  return _wtoi(a);
}

//itoa
//inline wchar_t* _itoa_s(int a, wchar_t *b, int c) 
inline errno_t _itoa_s(int a, wchar_t *b, size_t size, int c) 
{
  //return _itow(a, b, c);
  return _itow_s(a, b, size, c);
}

//stricmp
inline int stricmp(const wchar_t *a, const wchar_t *b) 
{
  return  _wcsicmp(a,b);
}

/*
inline unsigned long strtoul(const wchar_t *a,wchar_t **b,int c) 
{
  return wcstoul(a,b,c);
}

inline double strtod(const wchar_t *a, wchar_t **b) 
{
  return wcstod(a,b);
}
*/



// stricoll
inline int _stricoll(const wchar_t *string1, const wchar_t *string2) 
{
  return _wcsicoll(string1, string2);
}

// strcoll
inline int strcoll(const wchar_t *string1, const wchar_t *string2) {

  return wcscoll(string1, string2);
}

/*
inline int _strcoll_l(const wchar_t *string1, const wchar_t *string2, _locale_t locale) 
{
  return wcscoll_l(string1, string2, locale);

}
*/
//strnicoll
inline int _strnicoll(const wchar_t *string1, const wchar_t *string2, size_t count)
{
  return _wcsnicoll(string1, string2, count);
}

inline int _strnicoll_l(const wchar_t *string1, const wchar_t *string2, size_t count, _locale_t locale)
{
  return _wcsnicoll_l(string1, string2, count, locale);
}

//strchr
inline const wchar_t* strchr(const wchar_t *a, wchar_t b) 
{
  return wcschr(a,b);
}

//strstr
inline const wchar_t* strstr(const wchar_t *a, const wchar_t *b) 
{
  return wcsstr(a,b);
}


//strrchr
inline wchar_t *strrchr(wchar_t *str, wchar_t c)
{ 
  return wcsrchr(str, c); 
}

inline const wchar_t *strrchr(const wchar_t *str, wchar_t c)
{
  return wcsrchr(str, c); 
}

  
inline errno_t _strupr_s(wchar_t *str, size_t numberOfElements)
{
  return _wcsupr_s(str,numberOfElements);
}

inline errno_t _strupr_s_l(wchar_t* str, size_t numberOfElements, _locale_t locale)
{
  return _wcsupr_s_l(str, numberOfElements, locale);
}



inline errno_t strlwr_s(wchar_t *string, size_t size) 
{
  return _wcslwr_s(string, size);
}
  
inline errno_t _strlwr_s_l(wchar_t * str, size_t size, _locale_t locale)
{
  return _wcslwr_s_l(str, size, locale);
}

//strftime
inline size_t strftime(wchar_t *strDest, size_t maxsize, const wchar_t *format, const struct tm *timeptr) 
{
  return wcsftime(strDest, maxsize, format, timeptr);
}

inline size_t _strftime_l(wchar_t *strDest, size_t maxsize,const wchar_t *format, const struct tm *timeptr, _locale_t locale)
{
  return _wcsftime_l(strDest, maxsize, format,timeptr, locale);
}


inline errno_t _strtime_s(wchar_t *buffer,size_t numberOfElements)
{
  return _wstrtime_s(buffer,numberOfElements);
}

//asctime_s for wchar_t*
//2010/12/18
inline errno_t asctime_s(wchar_t* buffer, size_t numberOfElements, const struct tm *_tm)
{
  return _wasctime_s(buffer, numberOfElements, _tm);
}




//strpbrk
inline const wchar_t* strpbrk(const wchar_t *a, const wchar_t *b) 
{
  return wcspbrk(a,b);
}


//strrev
inline wchar_t* _strrev(wchar_t *str)
{
  return _wcsrev(str);
}

//strxfrm
inline size_t strxfrm(wchar_t *strDest, const wchar_t *strSource, size_t count)
{
  return wcsxfrm(strDest, strSource, count);
}


//inline int _vsnprintf(wchar_t *a, size_t b, const wchar_t *c, va_list d) 
inline int _vsnprintf_s(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format, va_list argptr )
{
  return _vsnwprintf_s(buffer, sizeOfBuffer, count, format, argptr);
}

  

inline errno_t _splitpath_s(
   const wchar_t * path, wchar_t * drive, size_t driveNumberOfElements, wchar_t * dir, size_t dirNumberOfElements,
  wchar_t * fname, size_t nameNumberOfElements, wchar_t * ext,  size_t extNumberOfElements)
{
  return _wsplitpath_s(path, drive, driveNumberOfElements, dir, dirNumberOfElements, 
    fname, nameNumberOfElements, ext, extNumberOfElements);
}

//_makepath_s
inline errno_t _makepath_s(wchar_t *path, size_t sizeInCharacters, const wchar_t *drive, const wchar_t *dir, 
      const wchar_t *fname, const wchar_t *ext)
{
  return _wmakepath_s(path, sizeInCharacters, drive, dir, fname, ext);
}

/*
char *_getcwd(char *buffer, int maxlen);
*/

//2009/10/07
inline wchar_t *_getcwd(wchar_t *buffer,int maxlen) {

  return _wgetcwd(buffer, maxlen);
}

/*int _mkdir(const char *dirname);
*/

inline int _mkdir(const wchar_t *dirname) 
{
  return _wmkdir(dirname);
}

/*
int _rmdir( const char *dirname );
*/
//2009/10/07
inline int _rmdir(const wchar_t *dirname)
{
  return _wrmdir(dirname);
}


/*
errno_t _mktemp_s(
   char *template,
   size_t sizeInChars
);
*/
inline errno_t _mktemp_s(wchar_t *stemplate, size_t sizeInChars)
{
  return _wmktemp_s(stemplate, sizeInChars);
}


/*
char *_fullpath( char *absPath,const char *relPath,size_t maxLength);
*/

//2009/10/07
inline wchar_t *_fullpath(wchar_t *absPath, const wchar_t *relPath, size_t maxLength) 
{
  return _wfullpath(absPath, relPath, maxLength);
}

///////////////////////////////////////////////
//FILE related inline functions
inline FILE* fopen(const wchar_t *filename, const wchar_t *mode) 
{
  FILE* fp = NULL;
  
  _wfopen_s(&fp, filename, mode);
  return fp; //2012/07/11
}

  
//2009/10/07
inline errno_t fopen_s(FILE** pFile, const wchar_t *filename, const wchar_t *mode) 
{
  return _wfopen_s(pFile, filename, mode);
}

/*
FILE *freopen(const char *filename, const char *mode, FILE *stream); 
}
*/

inline FILE *freopen(const wchar_t *filename, const wchar_t *mode, FILE *stream)
{
  FILE* fp = NULL;
  _wfreopen_s(&fp, filename, mode, stream);
  return fp; //2012/07/11
  //return _wfreopen(filename, mode, stream);
}

/*
errno_t freopen( FILE** pFile, const char *path, const char *mode, FILE *stream );
*/
//2009/10/07
inline errno_t freopen_s(FILE** pFile, const wchar_t *path, const wchar_t *mode, FILE *stream) 
{
  return _wfreopen_s(pFile, path, mode, stream);
}

/*
FILE *_fsopen( const char *filename,const char *mode,int shflag );
*/

//2009/10/07
inline FILE *_fsopen(const wchar_t *filename, const wchar_t *mode, int shflag) 
{
  return _wfsopen(filename, mode, shflag);
}

inline int fputs(const wchar_t *string, FILE *fp) 
{
  return fputws(string, fp);
}

//2009/10/07
inline int _fputchar(wchar_t c) 
{
  return _fputwchar(c);
}

inline int vfprintf(FILE* fp, const wchar_t *format, va_list argptr)
{
  return vfwprintf(fp, format, argptr);
}

inline int _vfprintf_l(FILE* fp, const wchar_t *format, _locale_t locale,va_list argptr)
{
  return  _vfwprintf_l(fp, format, locale, argptr);
}


inline int vfprintf_s(FILE *fp, const wchar_t *format, va_list argptr) 
{
  return vfwprintf_s(fp, format, argptr);
}

inline int _vfprintf_s_l(FILE *fp, const wchar_t *format, _locale_t locale, va_list argptr) 
{
  return _vfwprintf_s_l(fp, format, locale, argptr);
}

/*
int memcmp( const void *buf1, const void *buf2, size_t count);
*/
//2009/10/07
inline int memcmp(const wchar_t * buf1,const wchar_t * buf2, size_t count)
{
  return wmemcmp(buf1, buf2, count);
}

/*
void *memset(void *dest,int c,size_t count );
*/
inline wchar_t *memset(wchar_t *dest, wchar_t c, size_t count)
{
  return wmemset(dest, c, count);
}


//2009/10/07
inline wchar_t *memchr(wchar_t * buf, wchar_t c,size_t count) 
{
  return wmemchr(buf, c, count);
}

//2009/10/07
inline const wchar_t *memchr(const wchar_t * buf, wchar_t c, size_t count) 
{
  return wmemchr(buf, c,count);
}

/*
void *memcpy(void *dest,const void *src,size_t count );
*/

inline wchar_t *memcpy(wchar_t *dest, const wchar_t *src, size_t count) 
{
  return wmemcpy(dest, src, count);
}

/*
errno_t memcpy_s(void *dest, size_t numberOfElements, const void *src, size_t count );
*/
inline errno_t memcpy_s(wchar_t *dest, size_t numberOfElements, const wchar_t *src, size_t count)
{
  return wmemcpy_s(dest, numberOfElements, src, count);
}

//};


//using namespace SOL;
