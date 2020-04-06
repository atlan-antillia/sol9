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
 *  DiskSpace.h  
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Object.h>
#include <sol/StringConverter.h>
#include <sol/StringT.h>

//A function pointer to GetDiskFreeSpaceExA
typedef  BOOL (WINAPI *DiskFreeSpaceProc)(LPCSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER );

namespace SOL {

class DiskSpace :public Object {
private:
  DiskFreeSpaceProc diskSpaceProc;
  HINSTANCE  lib;  

public:
  DiskSpace() 
  {
    diskSpaceProc = NULL;
    lib = LoadLibrary(_T("kernel32.dll") );

    OSVERSIONINFO verInfo;
    verInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&verInfo);

    
    if(verInfo.dwMajorVersion>4  || 
      (verInfo.dwMajorVersion==4 && LOWORD(verInfo.dwBuildNumber)>=1000 ) ){
      diskSpaceProc =(DiskFreeSpaceProc)GetProcAddress(lib, "GetDiskFreeSpaceExA");
    }
  }

public:
  ~DiskSpace()
  {
    FreeLibrary(lib);
  }

public:
  Boolean get(const TCHAR* path, double& free, double& total)
  {

    Boolean rc = True;
    free  = 0.0;
    total = 0.0;

    // If GetDiskFreeSpaceEx procedure exists, use it.
    if(diskSpaceProc){
      ULARGE_INTEGER fba,tb,fb;
      StringT<char> cpath;
      StringConverter converter;
      converter.convert(path, cpath);

      if((*diskSpaceProc)((const char*)cpath, &fba, &tb, &fb)) {
        fba.QuadPart = Int64ShrlMod32(fba.QuadPart,20); 
                tb.QuadPart = Int64ShrlMod32(tb.QuadPart,20); 
                fb.QuadPart = Int64ShrlMod32(fb.QuadPart,20); 
        free  = (double)fba.u.LowPart;
        total = (double)tb.u.LowPart;
      } else {
        // Disk access error.
        //Printf("Failed to access disk %s\r\n", path);
        rc = False;
      }
    } else {
      
      DWORD  sectorsPerCluster = 0; 
      DWORD  bytesPerSector    = 0;
      DWORD  freeClusters      = 0;
      DWORD  clusters          = 0;
    
      if (::GetDiskFreeSpace(path, &sectorsPerCluster, 
        &bytesPerSector, &freeClusters, &clusters)) {
      //<modified date="2000.02.18">
        double size = (double)sectorsPerCluster *
               (double)bytesPerSector *
               (double)clusters/1024.0;

        double freeSize = (double)sectorsPerCluster *
               (double)bytesPerSector *
               (double)freeClusters/1024.0;
        total = (double)size/1024.0;
        free  = (double)freeSize/1024.0;
      //</modified>
      } else {
        rc = False;
        // Disk access error.
        //Printf("Failed to access disk %s\r\n", path);
      }
    }
    return rc;
  }

};

}



