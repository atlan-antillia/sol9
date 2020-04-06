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
 *  SocketStream.h
 *
 *****************************************************************************/

// SOL++2000
// 1999.08.10 Modified
#pragma once

#include <sol\Socket.h>
#include <sol/StringBufferT.h>
//#include <sol\StringBuffer.h>

#include <sol\InetAddress.h>
#include <sol/StringT.h>
#include <sol/StringBufferT.h>

/**
 * SocketStream class
 */
namespace SOL {

class SocketStream :public Socket {
  char  line[1024];
  int    startPos;
  int    contentSize;

  char*  buffer;

  static const int BUFFER_SIZE = 1024*8;

public:
  /**
   *
   */
  SocketStream() 
    :Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP),
    startPos(0),
    contentSize(0),
    buffer(new char[BUFFER_SIZE])
  {
  }
public:
  /**
   *
   */
  SocketStream(int domain, int protocol) 
    :Socket(domain, SOCK_STREAM, protocol),
    startPos(0),
    contentSize(0),
    buffer(new char[BUFFER_SIZE])
  {
  }

public:
  /**
   *
   */
  SocketStream(SOCKET soc) 
    :Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP),
    startPos(0),
    contentSize(0),
    buffer(new char[BUFFER_SIZE])
  {
    setSocket(soc);
  }

public:
  /**
   *
   */
  ~SocketStream() 
  {
    if (this->buffer) {
      delete [] this->buffer; //1999.08.22
      this->buffer = NULL;
    }
  }


public:
  /**
   *
   */
  SocketStream* accept(sockaddr* addr, int* size)
  {
    BOOL rc = FALSE;
    SOCKET soc = getSocket();
    SocketStream* stream = NULL;

    SOCKET newfd = ::accept(soc, addr, size);
        
    if(newfd != INVALID_SOCKET) {
      stream = new SocketStream(newfd);
    }

    if(stream == NULL) {
      throw InvalidSocketException("SocketStream::accept,1,Failed to accept a socket", 
        WSAGetLastError());  
    }

    return stream;
  }

public:
  /**
   *
   */
  SocketStream* accept(InetAddress& address) 
  {
    BOOL rc = FALSE;
    SOCKET soc = getSocket();
    SocketStream* stream = NULL;
    
    sockaddr_in* addr = address.getAddress();
    int size  = address.getSize();
        
    SOCKET newfd = ::accept(soc, (sockaddr*)addr, &size);
        
    if(newfd != INVALID_SOCKET) {
      stream = new SocketStream(newfd);
    }

    if(stream == NULL) {
      throw InvalidSocketException("StreamSocket,1,accept,Failed to accept a socket", 
        WSAGetLastError());  
    }

    return stream;
  }


public:
  /**
   *
   */
  SocketStream* accept(unsigned short port, unsigned long address) 
  {
    BOOL   rc = FALSE;
    SOCKET soc = getSocket();
    SocketStream* stream = NULL;

    sockaddr_in client;
    memset(&client, 0, sizeof(client));
    client.sin_family = getDomain();
    client.sin_port = htons(port);
    client.sin_addr.s_addr = htonl(address);
    int size = sizeof(client);
    SOCKET newfd = ::accept(soc, (sockaddr*)&client, &size);
        
    if(newfd != INVALID_SOCKET) {
      stream = new SocketStream(newfd);
    }
    
    if(stream == NULL) {
      throw InvalidSocketException("SocketStream::accpet,1,Failed to accept a socket", 
        WSAGetLastError());  
    }
    return stream;
  }


public:
  /**
   *
   */
  SOCKET create(int domain=AF_INET, int protocol=IPPROTO_TCP) 
  {
    return Socket::create(domain, SOCK_STREAM, protocol);
  }


public:
  /**
   *
   */
  int connect(unsigned short port, hostent* hostEntry) 
  {
    SOCKET soc = getSocket();

    sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = getDomain();
    server.sin_port   = htons(port);
    memcpy((char*)&server.sin_addr, 
                hostEntry->h_addr, hostEntry->h_length);
    return ::connect(soc, (sockaddr*)&server, sizeof(server));
    
  }

public:
  /**
   *
   */
  int connect(unsigned short port, unsigned long address) 
  {
    SOCKET soc  = getSocket();

    sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = getDomain();
    server.sin_port   = htons(port);
    server.sin_addr.s_addr = htonl(address);
    return ::connect(soc, (sockaddr*)&server, sizeof(server));
    }


public:
  /**
   *
   */
  int connect(sockaddr* addr, size_t size)  
  {
    SOCKET soc  = getSocket();
    return ::connect(soc, addr, size);
  }


// 1999.07.03
public:
  /**
   *
   */
  int connect(InetAddress& addr)
  {
    SOCKET soc  = getSocket();
    return ::connect(soc, (sockaddr*)addr.getAddress(), addr.getSize());
  }

public:
  /**
   *
   */
  int readLine(char* buffer, int max)
  {
    bool crFound = false;

    char ch[1];
    int len = 0;
    int i = 0;
  
    int RETRY_COUNT_MAX = 10;
    int retryCount = 0;

    SOCKET soc = getSocket();

    while (i< (max-1)) {
      if (isReadable(soc)==false) {
        continue;
      }
      //This is a very slow method. 
      len = SocketStream::recv(ch, sizeof(ch), 0);

      if (len == SOCKET_ERROR && WSAGetLastError() ==WSAEWOULDBLOCK) {
        //Printf("Socket#readLine,1,SOCKET_ERRO,WSAEWOULDBLOCK\r\n");

        if (retryCount < RETRY_COUNT_MAX) {
          //Do retry to read the socket.
          Sleep(10);
          retryCount++;
          continue;
        } else {
          //Printf("Socket#readLine,retry over\r\n");
          break;
        }
      }

      if (len <=0) {
        break;
      }

      buffer[i++] = ch[0];
      
      if (ch[0] == CHAR_CR) {
        crFound = true;
        continue;
      }

      if (crFound && ch[0]== CHAR_LF) {
        break;
      }

      retryCount = 0;
    }

    buffer[i]= '\0';
    //Printf("SocketStream#readLine,2,lenghth=%d line=%s \r\n", i, buffer);

    return i;
  }

public:
  int readLine(StringBufferT<char>& buffer)
  {
    bool crFound = false;
    char ch[1];
    int len = 0;

    SOCKET soc = getSocket();

    while (true) {
      //2008/07/11
      if (isReadable(soc)==false) {
        continue;
      }

      len = recv(ch, 1, 0);

      if (len <= 0) {
        break;
      }
      
      //2008/07/12

      //If ch is 0x0d, then set crFount=true and continue this reading loop,
      //Modified not to append this 0x0d to buffer. 
      if (ch[0] == 0xd) {
        crFound = true;
        continue;
      }
      //Found a newline(0x0d,0x0a), break this loop.
      if (crFound && ch[0]== 0xa) {
        break;
      }
      //Other cases, append ch to buffer
      buffer.append(ch[0]);

    }
    return buffer.getContentSize();
  }


public:
  int getLine(StringBuffer& buffer)
  {
    Boolean found = False;
    for(int i = startPos; i<contentSize; i++) {
      //If found a newline(0x0d, 0x0a) in line, then set startPos, and break 

      if (line[i] == 0xd || line[i] == 0xa) {
        startPos = i+1;
        found = True;
        //2008/07/11
        break;
      }
      //else, then apppend a character to the buffer 

      else {
        buffer.append(line[i]);
      }
    }

    //Found a newline(0x0d, 0x0a), then return 
    if (found) {
      return buffer.getContentSize();
    }

    SOCKET soc = getSocket();

    while (1) {
      startPos = 0;
      //2008/07/11
      if (isReadable(soc)==false) {
        continue;
      }

      contentSize = SocketStream::recv(line, 1024, 0);
      if (contentSize <=0) {
        // Reached to end of data.
        return  -1;
      }
      for(int i = startPos; i<contentSize; i++) {
        if (line[i] == 0xd || line[i] == 0xa) {
          startPos = i+1;
          found = True;
          break;
        } else {
          buffer.append(line[i]);
        }
      }

      if (found) {
        break;
      }
    }

    return buffer.getContentSize();
  }



public:
  int getPeerName(InetAddress& address)
  {
    sockaddr_in* addr = address.getAddress();
    return getPeerName(addr);
  }

public:
  int getPeerName(sockaddr_in* addr) 
  {
    memset(addr, 0, sizeof(sockaddr_in));
    SOCKET soc = getSocket();
    int addrlen = sizeof(sockaddr_in);
    return ::getpeername(soc, (sockaddr*)addr, &addrlen);
    
  }

public:

  int listen(int backlog) 
  {
    SOCKET soc = getSocket();
    
    return ::listen(soc, backlog);
  }

public:
  int select(HWND hwnd, unsigned int msg, long event)
  { 
    SOCKET soc = getSocket();
    return ::WSAAsyncSelect(soc, hwnd, msg, event);
  }

private:
  //
  bool isReadable(SOCKET fd, int timeout=100)
  {
    bool rc = false;

    fd_set  readFD, writeFD;
  
    timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_usec = timeout;
    
    FD_ZERO(&readFD);
    FD_ZERO(&writeFD);
  
    FD_SET(fd, &readFD);
    FD_SET(fd, &writeFD);

    if (::select(FD_SETSIZE, &readFD, &writeFD, 
        NULL,  &tv) != SOCKET_ERROR) {
  
      if (FD_ISSET(fd, &readFD)) {
        //OK. Readable
        rc = true;
      }
    } else {
      //SOCKET_ERROR
      if (WSAGetLastError()== WSAEWOULDBLOCK) {
        Sleep(2);
      }
    }
    return rc;
  }

private:
  //
  bool isWritable(SOCKET fd, int timeout=100)
  {
    bool rc = false;
  
    fd_set  readFD, writeFD;
    timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_usec = timeout;

    FD_ZERO(&readFD);
    FD_ZERO(&writeFD);

    FD_SET(fd, &readFD);
    FD_SET(fd, &writeFD);

    if (::select(FD_SETSIZE, &readFD, &writeFD, 
        NULL,  &tv) != SOCKET_ERROR) {

      if (FD_ISSET(fd, &writeFD)) {
        //OK. Writable
        rc = true;
      }
    } else {
      //SOCKET_ERROR
      if (WSAGetLastError() == WSAEWOULDBLOCK) {
        Sleep(2);
      }
    }
    return rc;
  }


// 1999.08.22 
public:
  int printf(const char* format,...)
  {
    va_list pos;
    va_start(pos, format);
    vsprintf_s(buffer, BUFFER_SIZE, format, pos);
    va_end(pos);

    return sendAll(buffer);
  }

public:
  int recv(char* buff, int len, int flag=0) 
  {
    SOCKET soc = getSocket();

    return ::recv(soc, buff, len, flag);
  }
    
public:
  int send(const char* buff, int len, int flag=0) 
  {
    SOCKET soc = getSocket();
    return ::send(soc, buff, len, flag);
  }

// 1999.06.12 to-arai
// 1999.08.16 Added a timeout argument. Specify the timeout in second.
public:
  int sendAll(const char* buff, int len, int flag=0, long timeout=30)
  {
    
    int sentBytes = 0;
    
    SOCKET soc = getSocket();

    const char* ptr = buff;
    int  orglen = len;
    time_t startTime = time(NULL);
    
    const int RETRY_COUNT_MAX = 10;
    int   retryCount = 0;

    while (len >0) {
      
      time_t currentTime = time(NULL);

      if ((currentTime - startTime) > timeout) {
        if (sentBytes < orglen) { 
          // timeout;
          break;
        }
        if (sentBytes == orglen) {
          break;
        }
      }

      //Check if fd is writable
      if (isWritable(soc) == false) {
        continue;
      }

      int size = ::send(soc, ptr, len, flag);
      
      if (size == SOCKET_ERROR && WSAGetLastError() ==WSAEWOULDBLOCK) {
        //Socket error has happened, and if it were caused by blocking,
        //retry to send the buff data.
        if (retryCount < RETRY_COUNT_MAX) {
          Sleep(10);
          retryCount++;
          continue;
        } else {
          break;
        }
      }

      if (size < 0 && len <=0) {  // 1999.08.14
        //Something send-error has happened!
        break;
      }
  
      if (size >0) {
        sentBytes += size;
        ptr += size;
        len -= size;
      }

      retryCount = 0;
    }
    return sentBytes;
  }

public:
  int sendAll(const char* string) 
  {
    int rc = 0;
    if (string) {
      rc = sendAll(string, strlen(string), 0);
    }
    return rc;
  }

public:    
  //2009/10/18 String -> StringT
  int sendAll(StringT<char>& string) 
  {
    const char* text = (const char*)string;
    int rc = 0;
    if (text) {
      rc = sendAll(text, strlen(text), 0);
    }
    return rc;
  }
  
public:
  int sendAll(StringBufferT<char>& buffer) 
  {
    const char* text = buffer.getBuffer();
    int rc = 0;
    if (text) {
      rc = sendAll(text, strlen(text), 0);
    }
    return rc;
  }

};

}

