/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  SpecialFolder.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.07.06
// 2012/06/25

#pragma once

#include <sol\Object.h>

#include <sol\String.h>


namespace SOL {

class SpecialFolder :public Object {

public:
  SpecialFolder() { }

  String  getALTStartup(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_ALTSTARTUP, flag);
    return String(path);
  }

  String  getAppData(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_APPDATA, flag);
    return String(path);
  }

  String  getBitBucket(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    path[0] = '\0';
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_BITBUCKET, flag);
    return String(path);
  }

  String  getCommonALTStartup(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COMMON_ALTSTARTUP, flag);
    return String(path);
  }

  String  getCommonDesktopDirectory(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COMMON_DESKTOPDIRECTORY, flag);
    return String(path);
  }

  String  getCommonFavorites(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COMMON_FAVORITES, flag);
    return String(path);
  }

  String  getCommonPrograms(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COMMON_PROGRAMS, flag);
    return String(path);
  }

  String  getCommonStartMenu(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COMMON_STARTMENU, flag);
    return String(path);
  }

  String  getCommonStartup(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COMMON_STARTUP, flag);
    return String(path);
  }

  String  getCookies(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_COOKIES, flag);
    return String(path);
  }

  String  getDesktopDirectory(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_DESKTOPDIRECTORY, flag);
    return String(path);
  }

  String  getFavorites(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_FAVORITES, flag);
    return String(path);
  }

  String  getHistory(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_HISTORY, flag);
    return String(path);
  }

  String  getInternetCache(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_INTERNET_CACHE, flag);
    return String(path);
  }

  String  getNetHood(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_NETHOOD, flag);
    return String(path);
  }
  
  String  getPersonal(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_PERSONAL, flag);
    return String(path);
  }

  String  getPrintHood(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_PRINTHOOD, flag);
    return String(path);
  }

  String  getPrograms(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_PROGRAMS, flag);
    return String(path);
  }

  String  getRecent(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_RECENT, flag);
    return String(path);
  }

  String  getSendTo(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_SENDTO, flag);
    return String(path);
  }

  String  getStartMenu(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_STARTMENU, flag);
    return String(path);
  }

  String  getStartup(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_STARTUP, flag);
    return String(path);
  }

  String  getTemplates(HWND owner = NULL, BOOL flag=FALSE) {
    TCHAR path[MAX_PATH] = {'\0'};
    //HRESULT hr = 
    SHGetSpecialFolderPath(owner, path, CSIDL_TEMPLATES, flag);
    return String(path);
  }

public:
  void display()
  {
    _tprintf(_T("ALTStartup: %s\n"),(const TCHAR*)getALTStartup());

    _tprintf(_T("AppData: %s\n"),(const TCHAR*)getAppData());
    
    _tprintf(_T("BitBucket: %s\n"),(const TCHAR*)getBitBucket());
    
    _tprintf(_T("CommonALTStartup: %s\n"),(const TCHAR*)getCommonALTStartup());
    
    _tprintf(_T("CommonDesktopDirectory: %s\n"),(const TCHAR*)getCommonDesktopDirectory());
    
    _tprintf(_T("CommonFavorites: %s\n"),(const TCHAR*)getCommonFavorites());
    
    _tprintf(_T("CommonPrograms: %s\n"),(const TCHAR*)getCommonPrograms());
    
    _tprintf(_T("CommonStartMenu: %s\n"),(const TCHAR*)getCommonStartMenu());
    
    _tprintf(_T("CommonStartup: %s\n"),(const TCHAR*)getCommonStartup());
    
    _tprintf(_T("Cookies: %s\n"),(const TCHAR*)getCookies());
    
    _tprintf(_T("DesktopDirectory: %s\n"),(const TCHAR*)getDesktopDirectory());
    
    _tprintf(_T("Favorites: %s\n"),(const TCHAR*)getFavorites());
    
    _tprintf(_T("History: %s\n"),(const TCHAR*)getHistory());
    
    _tprintf(_T("InternetCache: %s\n"),(const TCHAR*)getInternetCache());
    
    _tprintf(_T("NetHood: %s\n"),(const TCHAR*)getNetHood());
  
    _tprintf(_T("Personal: %s\n"),(const TCHAR*)getPersonal());

    _tprintf(_T("PrintHood: %s\n"),(const TCHAR*)getPrintHood());
    
    _tprintf(_T("Programs: %s\n"),(const TCHAR*)getPrograms());
    
    _tprintf(_T("Recent: %s\n"),(const TCHAR*)getRecent());
    
    _tprintf(_T("SendTo: %s\n"),(const TCHAR*)getSendTo());
    
    _tprintf(_T("StartMenu: %s\n"),(const TCHAR*)getStartMenu());

    _tprintf(_T("ALTStartup: %s\n"),(const TCHAR*)getStartup());
    
    _tprintf(_T("getTemplates: %s\n"),(const TCHAR*)getTemplates());
  }

};

}



