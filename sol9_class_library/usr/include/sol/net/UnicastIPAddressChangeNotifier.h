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
 *  UnicastIPAddressChangeNotifier.h
 *
 *****************************************************************************/

// 2009/09/04

#pragma once

#include <sol/Object.h>
#include <sol/Thread.h>

#include <sol/net/UnicastIPAddressTable.h>

#include <sol\LocalDateTime.h>

#define WM_CHANGE_NOTIFER_CLOSED   (WM_USER + 2013)

namespace SOL {

class UnicastIPAddressChangeNotifier :public Thread {
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

public:
  UnicastIPAddressChangeNotifier(HWND hwnd = NULL, bool delInstance=false, ADDRESS_FAMILY f=AF_UNSPEC)
  :hNotification(NULL),
  hwndNotified(hwnd),
  deleteInstance(delInstance),
  family(f),
  termEvent(NULL),
  looping(false)
  {
    termEvent = CreateEvent(0, FALSE, FALSE, 0);
  }


public:
  ~UnicastIPAddressChangeNotifier()
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
  static void WINAPI changed(void* callerContext,
    PMIB_UNICASTIPADDRESS_ROW row, MIB_NOTIFICATION_TYPE type)
  {
    UnicastIPAddressChangeNotifier* notifier = (UnicastIPAddressChangeNotifier*)callerContext;
    if (notifier) {
      notifier->changed(row, type);
    }
  }

/*
When the callback function is received when a change occurs and the Row parameter is not NULL,
the pointer to the MIB_UNICASTIPADDRESS_ROW structure passed in the Row parameter contains
incomplete data. The information returned in the MIB_UNICASTIPADDRESS_ROW structure is only
enough information that an application can call the GetUnicastIpAddressEntry function to 
query complete information on the IP address that changed. 
When the callback function is received, an application should allocate a MIB_UNICASTIPADDRESS_ROW
structure and initialize it with the Address,
InterfaceLuid and InterfaceIndex members in the MIB_UNICASTIPADDRESS_ROW structure pointed to by
the Row parameter received. From Microsoft document.
*/

public:
  virtual void changed(PMIB_UNICASTIPADDRESS_ROW row, MIB_NOTIFICATION_TYPE type)
  {
    if (row) {
      MIB_UNICASTIPADDRESS_ROW row2;
      memset(&row2, 0, sizeof(row2));
      memcpy(&row2, row, sizeof(row2));
      int r = GetUnicastIpAddressEntry(&row2);

      if (r == NO_ERROR) {

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
*/

public:
  virtual void display(const char* name, MIB_UNICASTIPADDRESS_ROW& row)
  {
    //IPForwardTable table;
    UnicastIPAddressTable table;

    table.display(row);
  }

public:
  void run()
  {
    HANDLE waitEvents[1];
    waitEvents[0] = this->termEvent;

    this->looping = true;
  
    hNotification = NULL;

    if (NotifyUnicastIpAddressChange(family,
      (PUNICAST_IPADDRESS_CHANGE_CALLBACK )
      changed,
      this,   //__in     PVOID CallerContext,
        FALSE,  //__in     BOOLEAN InitialNotification,
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
        PostMessage(hwndNotified, WM_CHANGE_NOTIFER_CLOSED, 0, 0);
      }
    }

    if (deleteInstance) {
      delete this;
    }
  }
};

}


