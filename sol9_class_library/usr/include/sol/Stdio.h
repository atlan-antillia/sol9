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
 *  Stdio.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\CriticalSection.h>
#include <richedit.h>
/*
void Printf(char* format,...);

// <added date="2000.05.03" author="to-arai" />
void print(char* format,...);
void println(char* format,...);

// <added date="2009/10/10" author="to-arai" />

void Printf(wchar_t* format,...);
void print(wchar_t* format,...);
void println(wchar_t* format,...);
*/

void Printf(TCHAR* format,...)
{
  static CriticalSection cs;

  cs.enter();

  TCHAR buffer[1024];
  memset(buffer, (TCHAR)0, CountOf(buffer));

  va_list pos;
  va_start(pos, format);
  _vsnprintf_s(buffer, CountOf(buffer), _TRUNCATE,  format, pos);
  va_end(pos);

  HWND root = ::GetDesktopWindow();
  HWND hwnd = (HWND)::GetProp(root, _T("SCROLLED_TEXT"));

  if(hwnd && ::IsWindow(hwnd) && ::IsWindowVisible(hwnd) ) {
    unsigned int len = (unsigned int)::SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0L);
    unsigned int max = (int)::SendMessage(hwnd, EM_GETLIMITTEXT, 0,0);

    if((len + strlen(buffer))>= max) {
      int visibleLine =(int)::SendMessageA(hwnd, 
                  EM_GETFIRSTVISIBLELINE, 0, 0);
      unsigned int charPos =(unsigned int)::SendMessageA(hwnd, 
            EM_LINEINDEX, visibleLine,0);
      ::SendMessage(hwnd, EM_SETSEL, 0, charPos);

      ::SendMessage(hwnd, WM_CLEAR, 0, 0);
      len = (int)::SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0L);
    }

    ::SendMessage(hwnd, EM_SETSEL, len, len);
    ::SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)buffer);
    ::SendMessage(hwnd, WM_SETREDRAW, 1, 0L);
  }

  cs.leave();
}


void print(TCHAR* format,...)
{
  static CriticalSection ex;

  ex.enter();

  TCHAR buffer[1024];
    memset(buffer, (TCHAR)0, CountOf(buffer));

  va_list pos;
  va_start(pos, format);
  _vsnprintf_s(buffer, CountOf(buffer), _TRUNCATE, format, pos);
  va_end(pos);

  HWND root = ::GetDesktopWindow();
  HWND hwnd = (HWND)::GetProp(root, _T("SOL_TRACER"));

  if(hwnd && ::IsWindow(hwnd) && ::IsWindowVisible(hwnd) ) {
    COPYDATASTRUCT cp;
    memset(&cp, 0, sizeof(cp));
    cp.cbData = (DWORD)strlen(buffer)+1; //2009/11/14
    cp.lpData = buffer;
    ::SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cp);
  }

  ex.leave();
}

void println(TCHAR* format,...)
{
  static CriticalSection ex;

  ex.enter();

  TCHAR buffer[1024];
    memset(buffer, (TCHAR)0, CountOf(buffer));

  va_list pos;
  va_start(pos, format);
  _vsnprintf_s(buffer, CountOf(buffer), _TRUNCATE, format, pos);
  va_end(pos);
  size_t rest = CountOf(buffer)- strlen(buffer);
  strcat_s(buffer, rest, _T("\r\n"));

  HWND root = ::GetDesktopWindow();
  HWND hwnd = (HWND)::GetProp(root, _T("SOL_TRACER"));

  if(hwnd && ::IsWindow(hwnd) && ::IsWindowVisible(hwnd) ) {
    COPYDATASTRUCT cp;
    memset(&cp, 0, sizeof(cp));
    cp.cbData = (DWORD)strlen(buffer)+1;  //2009/11/14 
    cp.lpData = buffer;
    ::SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cp);
  }

  ex.leave();
}
//</added>

