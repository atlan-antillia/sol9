/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenGLProfile.h
 *
 *****************************************************************************/

#pragma once

#include <sol/ModuleFileName.h>
#include <sol/opengl/OpenGLObject.h>
#include <sol/StringT.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>

namespace SOL {

class OpenGLProfile : public OpenGLObject {
private:
  char  defaultProfile[MAX_PATH];
  int   majorVersion; 
  int   minorVersion;
  
public:
  OpenGLProfile()
  :OpenGLObject(),
  majorVersion(INVALID_VALUE),
  minorVersion(INVALID_VALUE)
  {
    ModuleFileName moduleFileName;
    const char* drive = moduleFileName.getDrive();
    const char* dir   = moduleFileName.getDir();
    static const char* DEFAULT_PROFILE = "oglprofile.ogl";  
    //The DEFAULT_PROFILE should be in the current program (.exe) module folder.
    sprintf_s(defaultProfile, sizeof(defaultProfile),  "%s%s%s", drive, dir, DEFAULT_PROFILE);
    
  }
  
  bool exists()
  {
    //struct stat st;
    struct _stat64i32 st;
    //
    int r = _stat(defaultProfile, &st);
    if (r == -1 && errno == ENOENT) {
      return false;
    } else {
      return true;
    }
  }
  
  
  void read()
  {
    FILE* fp = _fsopen(defaultProfile, "r",  _SH_DENYNO);
    if (fp) {
      char line[1024];
      while(fgets(line, sizeof(line), fp)) {
        StringT<char> aline(line);
        aline.trim();
        if (aline.startsWith("//")) {
          //MessageBox(NULL, line, "Comment", MB_OK);
          continue;
        }
        const char* equal = strstr(line, "=");
        if (equal) {
          int tlen = strlen(line);
          line[tlen] = ZERO;
          line[(int)(equal-line)] = ZERO;
          StringT<char> name(line);
          StringT<char> value(equal+1);
          name.trim();
          value.trim();
          if (name == "majorVersion") {
            majorVersion = atoi((const char*)value);
          }
          if (name ==  "minorVersion") {
            minorVersion = atoi((const char*)value);
          }
        }
      }
      fclose(fp);    
    }
  }
  
  int getMajorVersion()
  {
    return majorVersion;
  }
  
  int getMinorVersion()
  {
    return minorVersion;
  }

};

}

      