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
 *  URL.h
 *
 *****************************************************************************/

// SOL++2000

// 2009/10/16

#pragma once

#include <sol\Object.h>
//2009/10/16
#include <sol\StringT.h>
#include <sol\StringBufferT.h>

namespace SOL {

class URL :public Object {
private:
  StringT<char> protocol;
  StringT<char> host;
  StringT<char> path;
  unsigned short  port;
  StringT<char> fileName;    

public:
  URL(const char* proto1, const char* host1, const char* path1, 
      unsigned short port1 = 80)
    :protocol(proto1),
    host(host1), path(path1), port(port1) {

    }

public:
  URL(char* string)
  :port(80)
  {
    StringBufferT<char> strBuffer;
    strBuffer.append(string);

    const char* ptr = strBuffer.getBuffer();

    // get protocol
    char* p = (char*) strstr(ptr, "://");
    if (p) {   
      *p = ZERO;
      protocol = ptr;
      ptr = p + 3;
  
      p = (char*)strstr(ptr, ":");
      if (p) {
        *p = ZERO;
        host = ptr;
        char* por = ++p;
        char* sla = strstr(por, "/");
        if (sla) {
          *sla = ZERO;
          path = ++sla;
        }
        port = atoi(por);
      } else {
        // no port
        port = 80;
    
        // get path
        p = (char*)strstr(ptr, "/");
        if (p) {
          *p = ZERO;
          path = ++p;                      
        }
        host = ptr;
      }
    }
  }

public:  
  const char* getProtocol() { return (const char*)protocol; }

public:
  const char* getHost() { return (const char*)host; }

public:
  const char* getPath() { return (const char*)path; }

public:
  unsigned short getPort() { return port; }

public:
  const char* getFileName()
  {
    const char* host = getHost();
    const char* path = getPath();

    if (*host =='/') {
      host++;
    }

    //2001/03/11
    char buffer[1024];
    //

    if (strlen(host)) {
      sprintf_s(buffer, sizeof(buffer),"%s:/%s", host, path);
  
    } else {
      sprintf_s(buffer, sizeof(buffer), "%s", path);
    }
    int len = strlen(buffer);

    // 2001/03/11 
    //Checking a url parameter.
    char* q = strstr(buffer, "?");
    if (q) {
      *q = ZERO;
    }
    //

    char* ptr = buffer;
    for (int i = 0; i<len; i++) {
      if (*ptr == '|') *ptr = ':';
      if (*ptr == '/') *ptr = '\\';
      ptr++;
    }
    fileName = buffer;

    return (const char*)fileName;
  }


};

}


