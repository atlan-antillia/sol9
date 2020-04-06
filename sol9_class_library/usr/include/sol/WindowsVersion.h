/******************************************************************************
 *
 * Copyright (c) 1999-2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WindowsVersion.h
 *
 *****************************************************************************/

// 2011/09/04 Modified a member function isVista and added a new meber function isWindows7.
// 2015/12/20 Updated.
// 2015/12/27
 
#pragma once

#include <sol\Object.h>
//#include <io.h>


namespace SOL {

class WindowsVersion :public Object {
private:
  OSVERSIONINFOEX versionInfo;

public:
  /**
   * Constructor
   */
  WindowsVersion() {
    memset(&versionInfo, 0, sizeof(OSVERSIONINFOEX));
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
  }

public:
  /**
   */
  bool getVersion(DWORD& dwPlatformId, 
      DWORD& dwMajorVersion, 
      DWORD& dwMinorVersion) {

    bool rc = false;

    memset(&versionInfo, 0, sizeof(OSVERSIONINFOEX));
  
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (GetVersionEx((OSVERSIONINFO*)&versionInfo) == 0) {

      versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx((OSVERSIONINFO*)&versionInfo);
    }

    dwPlatformId   = versionInfo.dwPlatformId;
    dwMajorVersion = versionInfo.dwMajorVersion;
    dwMinorVersion = versionInfo.dwMinorVersion;

    rc = true;

    return rc;
  }

public:
  /**
   */
  bool isVista() {
    bool rc = false;

    DWORD dwPlatformId; 
    DWORD dwMajorVersion; 
    DWORD dwMinorVersion;
    
    getVersion(dwPlatformId, 
        dwMajorVersion, 
        dwMinorVersion);
    if (dwPlatformId == VER_PLATFORM_WIN32_NT &&
        dwMajorVersion == 6 &&
        dwMinorVersion == 0) {
      rc = true;
    }

    return rc;
  }


    
  bool isWindows7() {
    bool rc = false;

    DWORD dwPlatformId; 
    DWORD dwMajorVersion; 
    DWORD dwMinorVersion;
    
    getVersion(dwPlatformId, 
        dwMajorVersion, 
        dwMinorVersion);
    if (dwPlatformId == VER_PLATFORM_WIN32_NT &&
        dwMajorVersion == 6 &&
        dwMinorVersion == 1) {
      rc = true;
    }

    return rc;
  }

  bool isWindows8() {
    bool rc = false;

    DWORD dwPlatformId; 
    DWORD dwMajorVersion; 
    DWORD dwMinorVersion;
    
    getVersion(dwPlatformId, 
        dwMajorVersion, 
        dwMinorVersion);
    if (dwPlatformId == VER_PLATFORM_WIN32_NT &&
        dwMajorVersion == 6 &&
        dwMinorVersion == 2) {
      rc = true;
    }

    return rc;
  }

  bool isWindows81() {
    bool rc = false;

    DWORD dwPlatformId; 
    DWORD dwMajorVersion; 
    DWORD dwMinorVersion;
    
    getVersion(dwPlatformId, 
        dwMajorVersion, 
        dwMinorVersion);
    if (dwPlatformId == VER_PLATFORM_WIN32_NT &&
        dwMajorVersion == 6 &&
        dwMinorVersion == 3) {
      rc = true;
    }
    return rc;
  }
  

  bool isWindows10() {
    bool rc = false;

    DWORD dwPlatformId; 
    DWORD dwMajorVersion; 
    DWORD dwMinorVersion;
    
    getVersion(dwPlatformId, 
        dwMajorVersion, 
        dwMinorVersion);
    if (dwPlatformId == VER_PLATFORM_WIN32_NT &&
        dwMajorVersion == 6 &&
        dwMinorVersion == 4) {
      rc = true;
    }
    return rc;
  }
};

}

