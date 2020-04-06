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
 *  SocketSelector.h
 *
 *****************************************************************************/

// SOL++2000

// 1999.08.04
#pragma once

#include <sol\Socket.h>

namespace SOL {

class SocketSelector :public Object {
private:
    fd_set  readFDSet;
    fd_set  writeFDSet;
    fd_set  IExceptionFDSet;
    timeval timeout;

public:
  SocketSelector() 
  {
    FD_ZERO(&readFDSet);
    FD_ZERO(&writeFDSet);
    FD_ZERO(&IExceptionFDSet);
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_usec = 100;
  }

public:
  void setTimeout(int sec, int usec ) 
  {
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
  }

public:
  void    clearAll()
  {
    FD_ZERO(&readFDSet);
    FD_ZERO(&writeFDSet);
    FD_ZERO(&IExceptionFDSet);
  }

public:
  void    setReadable(Socket* soc) 
  {
    if (soc) {
      FD_SET(soc->getSocket(), &readFDSet);
    }
  }

public:

  void    setWritable(Socket* soc) 
  {
    if (soc) {
      FD_SET(soc->getSocket(), &writeFDSet);
    }
  }

public:
  void    setException(Socket* soc) 
  {
    if (soc) {
      FD_SET(soc->getSocket(), &IExceptionFDSet);
    }
  }

public:
  int select() 
  {
    return ::select(FD_SETSIZE, &readFDSet, 
                &writeFDSet, &IExceptionFDSet,  &timeout);
  }

public:
  int isReadable(Socket* soc) 
  {
    int rc = SOCKET_ERROR;
    if (soc) {
      rc = FD_ISSET(soc->getSocket(), &(this->readFDSet));
    }
    return rc;
  }

public:
  int isWritable(Socket* soc) 
  {
    int rc = SOCKET_ERROR;
    if (soc) {
      rc = FD_ISSET(soc ->getSocket(), &(this->writeFDSet));
    }
    return rc;
  }

public:
  int isException(Socket* soc) 
  {
    int rc = SOCKET_ERROR;
    if (soc) {
      rc = FD_ISSET(soc ->getSocket(), &(this->IExceptionFDSet));
    }
    return rc;
  }

  ///////////////////////////////////
public:
    void    clearReadable() {
            FD_ZERO(&readFDSet);
    }

    void    clearWritable() {
            FD_ZERO(&writeFDSet);
    }

    void    clearException() {
            FD_ZERO(&IExceptionFDSet);
    }
};

}

