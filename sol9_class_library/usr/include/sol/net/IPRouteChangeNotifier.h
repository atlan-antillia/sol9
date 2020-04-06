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
 *  IPRouteChangeNotifier.h
 *
 *****************************************************************************/

// 2009/09/04 Modified close method to call
//       CancelMibChangeNotify2(hNotification); 
// 2009/09/26 Added initialNotification parameter to Constructors.

#pragma once

#include <sol/Object.h>
#include <sol/Thread.h>

#include <sol/net/IPForwardTable.h>

#include <sol\LocalDateTime.h>

#define WM_IPROUTE_CHANGE_NOTIFER_CLOSED   (WM_USER + 2011)

namespace SOL {

class IPRouteChangeNotifier :public Thread {
private:
  HANDLE termEvent;

private:
  bool looping;

private:
  HANDLE hNotification;

private:
  HWND  hwndNotified;

private:
  bool deleteInstance;

private:
  ADDRESS_FAMILY family;

private:
  BOOL initialNotification;

public:
  IPRouteChangeNotifier(HWND hwnd = NULL, bool delInstance=false, 
    ADDRESS_FAMILY f=AF_UNSPEC, BOOL notify=FALSE)
  :hNotification(NULL),
  hwndNotified(hwnd),
  deleteInstance(delInstance),
  family(f),
  termEvent(NULL),
  looping(false),
  initialNotification(notify)
  {
    termEvent = CreateEvent(0, FALSE, FALSE, 0);
  }


public:
  ~IPRouteChangeNotifier()
  {
    close();
  }

public:
  void close()
  {
    if (termEvent) {
      CloseHandle(termEvent);
      termEvent = NULL;
    }

    if (hNotification) {
      //2009/09/04 CloseHandle(hNotification);
      CancelMibChangeNotify2(hNotification); 
      hNotification = NULL;
    }
  }

public:
  // Set termEvent to stop the run method loop.
  HANDLE getStopEvent() 
  {
    return termEvent;
  }

private:
  static void WINAPI routeChanged(void* callerContext,
    PMIB_IPFORWARD_ROW2 row, MIB_NOTIFICATION_TYPE type)
  {
    //printf("RouteChanged\n");
    IPRouteChangeNotifier* notifier = (IPRouteChangeNotifier*)callerContext;
    if (notifier) {
      notifier->routeChanged(row, type);
    }
  }

/*
The information returned in the MIB_IPFORWARD_ROW2 structure is only enough information 
that an application can call the GetIpForwardEntry2 function to query complete information 
on the IP route that changed. When the callback function is received, an application 
should allocate a MIB_IPFORWARD_ROW2 structure and initialize it with the 
  DestinationPrefix, 
  NextHop, 
  InterfaceLuid 
  and InterfaceIndex 
members in the MIB_IPFORWARD_ROW2 structure pointed to by the Row parameter received. 
A pointer to this newly initialized MIB_IPFORWARD_ROW2 structure should be passed 
to the GetIpForwardEntry2 function to retrieve complete information on the IP route 
that was changed. From Microsoft document.
*/

public:
  virtual void routeChanged(PMIB_IPFORWARD_ROW2 row, MIB_NOTIFICATION_TYPE type)
  {
    if (row) {
      MIB_IPFORWARD_ROW2 row2;
      memset(&row2, 0, sizeof(row2));
      memcpy(&row2, row, sizeof(row2));
      int r = GetIpForwardEntry2(&row2);
      //int r = GetIpForwardEntry2(row);

      if (r == NO_ERROR) {
        //printf("OK GetIpForwardEntry2 %d\n", r);
        const char* name = getNotificationType(type);
              
        LocalDateTime ldt;
        StringT<char> localTime;
        ldt.nowToSeconds(localTime);
        printf("<%s Notification : %s>\n", (const char*)localTime, name);

        display(name, row2);
        printf("\n");
      } else { 
        //Ignore other cases for r.
      }
    }
  }

public:
  const char* getNotificationType(int value)
  {
     static const ArgT<char> types[] = {
    {"ParameterNotification", MibParameterNotification},
    {"AddInstance",           MibAddInstance},
    {"DeleteInstance",        MibDeleteInstance},
    {"InitialNotification",   MibInitialNotification},

    };
    
    int count = XtNumber(types);
    const char* name = "";
    for (int i = 0; i<count; i++) {
      if ((int)types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }
  

/*
typedef struct _MIB_IPFORWARD_ROW2 {
  NET_LUID          InterfaceLuid;
  NET_IFINDEX       InterfaceIndex;
  IP_ADDRESS_PREFIX DestinationPrefix;
  SOCKADDR_INET      NextHop;
  UCHAR             SitePrefixLength;
  ULONG             ValidLifetime;
  ULONG             PreferredLifetime;
  ULONG             Metric;
  NL_ROUTE_PROTOCOL Protocol;
  BOOLEAN           Loopback;
  BOOLEAN           AutoconfigureAddress;
  BOOLEAN           Publish;
  BOOLEAN           Immortal;
  ULONG             Age;
  NL_ROUTE_ORIGIN   Origin;
}MIB_IPFORWARD_ROW2, *PMIB_IPFORWARD_ROW2;
*/

public:
  virtual void display(const char* name, MIB_IPFORWARD_ROW2& row)
  {
    IPForwardTable table;

    table.display(row);
  }

public:
  void run()
  {
    HANDLE waitEvents[1];
    waitEvents[0] = this->termEvent;

    this->looping = true;
  
    hNotification = NULL;

    if (NotifyRouteChange2(family,
      (PIPFORWARD_CHANGE_CALLBACK)
        routeChanged,
        this,   //__in     PVOID CallerContext,
      (BOOLEAN)initialNotification,  //2009/10/05 FALSE,  //__in     BOOLEAN InitialNotification,
        &hNotification) == NO_ERROR) {
      while (looping) {
      
        int r = WaitForMultipleObjects(1, waitEvents, FALSE, INFINITE); 
        if (r == WAIT_OBJECT_0 ) {
          printf("\nTerminateEvent has been set, so break this thread loop\n");
          break;
        }      
      }
    }

    if (hwndNotified) {
      if (IsWindow(hwndNotified)) {
        PostMessage(hwndNotified, WM_IPROUTE_CHANGE_NOTIFER_CLOSED, 0, 0);
      }
    }

    if (deleteInstance) {
      delete this;
    }
  }
};

}


