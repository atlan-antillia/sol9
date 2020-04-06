/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  IPAddressChangeNotifier.h
 *
 *****************************************************************************/

#pragma once

// SOL9
// 2008/10/10
//

#include <sol\WSAInitializer.h>
#include <sol\Thread.h>

#include <sol\net\NetworkInterfaceInfo.h>
#include <sol\StringBuffer.h>

#include <process.h>


#define WM_IPADDRESS_CHANGE  (WM_USER + 2009)

namespace SOL {

/**
 * IPAddressChangeNotifier thread class is to detect change of IPAddress and post a message 
 * WM_IADDRESS_CHANGE to a thread or window specified by Constructor.
 * The WPARAM parameter associated with the message will be TRUE or FALSE
 * which means the status of connected to the Internet or disconnected from Internet respectively.
 *
 * In this class Windows API NotifyAddrChange is used to detect an IPAddress change 
 * with non-blocking mode.
 */

class IPAddressChangeNotifier :public Thread {

private:
  NetworkInterfaceInfo info;

private:
  HANDLE termEvent;

private:
  bool looping;

private:
  DWORD threadIdNotified;

private:
  HWND  hwndNotified;

private:
  UINT  notifyMessage;

private:
  BOOL  connected;


public:
  /**
   * Constructor
   * @param threadId  Thread ID to receive a windows message to notify IP AddressChanged
   *          (connected or disconnected to/from Internet). 
   */
  IPAddressChangeNotifier(DWORD threadId, UINT message=WM_IPADDRESS_CHANGE)
  :Thread(),
   looping(false),

   threadIdNotified(threadId),
   hwndNotified(NULL),
   notifyMessage(message),
   termEvent(NULL),
   connected(FALSE)
  {
    termEvent = CreateEvent(0,FALSE,FALSE,0);  
  }


public:
  /**
   * Constructor
   * @param hwnd  Window handle to receive a windows message to notify IP AddressChanged
   *          (connected or disconnected to/from Internet). 
   */
  IPAddressChangeNotifier(HWND hwnd, UINT message=WM_IPADDRESS_CHANGE)
  :Thread(),
   looping(false),
   threadIdNotified(0),
   hwndNotified(hwnd),
   notifyMessage(message),
   termEvent(NULL),
   connected(FALSE)
  {
    termEvent = CreateEvent(0,FALSE,FALSE,0);  
  }

public:
  ~IPAddressChangeNotifier() {
    close();
  }


private:
  bool close()
  {
    bool rc = false;
    if (termEvent) {
      CloseHandle(termEvent);
      termEvent = NULL;
    }
    return rc;
  }

public:
  // Set termEvent to stop the run method loop.
  void stop() {
    SetEvent(termEvent);
    looping  = false;
  }


private:

  /**
   * At the first time, post a notifyMessage with a parameter of current status of connected or disconnected to/from
   * Internet to threaIdNotified or hwndNotified
   *
   */
  virtual void notifyFirstTime()
  {
    BOOL status = FALSE;
    info.listup();
    
    if (info.isConnectedToInternet()) {
      status = TRUE;    
    }

    if (threadIdNotified>0) {
      PostThreadMessage(threadIdNotified, notifyMessage, status, 0);
    }
    if (hwndNotified !=NULL) {
      PostMessage(hwndNotified, notifyMessage, status, 0);
    }
    this->connected = status;
  }

private:

  /**
   * IPAddress has been changed, so post a notifyMessage to threaIdNotified or hwndNotified
   *
   */
  virtual void notify()
  {
    BOOL status = FALSE;
    info.listup();
    
    if (info.isConnectedToInternet()) {
      status = TRUE;    
    }

    if (threadIdNotified>0 && (status != this->connected)) {
      PostThreadMessage(threadIdNotified, notifyMessage, status, 0);
    }
    if (hwndNotified !=NULL && (status != this->connected)) {
      PostMessage(hwndNotified, notifyMessage, status, 0);
    }
    this->connected = status;
  }


public:
  /**
   * Thread procedure to get notification of IPAddress changes of NeworkInterface. 
   */
  void run()
  {
    notifyFirstTime();

    OVERLAPPED ovl;
    memset(&ovl, 0, sizeof(ovl));
    ovl.hEvent   = CreateEvent(NULL, FALSE, FALSE, NULL);

    HANDLE waitEvents[2];
    waitEvents[0] = this->termEvent;
    waitEvents[1] = ovl.hEvent;

    HANDLE hFile = NULL;

    this->looping = true;

    while (looping) {
      //printf("Waiting NotifyAddrChange.No blocking here\n");

      DWORD rc = NotifyAddrChange(&hFile, &ovl);
      if (rc != NO_ERROR) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
          printf("NotifyAddrChange error...%d\n", WSAGetLastError());
          break;
        }
      }
    
      //printf("Call Wait \n");
      
      int r = WaitForMultipleObjects(2, waitEvents, FALSE, INFINITE); 
      if (r == WAIT_OBJECT_0 ) {
        //If termEvent set to terminate this thread, 
        //then, we break this while loppStopped 
        printf("\nTerminateEvent has been set, so break this thread loop\n");
        break;
      }
      /**
      if (r == WAIT_OBJECT_0 +1) {
        notify();
      }
      */
      
      DWORD dwBytes = 0;
      //printf("Call GetOverlapped \n");
      BOOL b = GetOverlappedResult(hFile, &ovl, &dwBytes, TRUE); 
      if (b == TRUE) {
        notify();
      }
    }
    CloseHandle(ovl.hEvent);
  }

};

}
