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
 *  IPInterfaceChangeNotifier.h
 *
 *****************************************************************************/


// SOL9
// 2009/08/29
//
// 2009/09/26 Added initialNotification parameter to Constructors.
#pragma once

//#include <sol\WSAInitializer.h>
#include <sol\Thread.h>

#include <sol\net\IPInterfaceTable.h>
#include <sol\StringBuffer.h>
#include <sol\LocalDateTime.h>
#include <process.h>


#define WM_IPINTERFACE_CHANGE_NOTIFER_CLOSED   (WM_USER + 2012)

namespace SOL {


class IPInterfaceChangeNotifier :public Thread {

private:
  HANDLE termEvent;

private:
  bool looping;

private:
  HANDLE hNotification;
  
private:
  DWORD threadIdNotified;

private:
  HWND  hwndNotified;

private:
  bool deleteInstance;

private:
  ADDRESS_FAMILY family;

  //2009/09/26
private:
  BOOL initialNotification;

public:
  /**
   * Constructor
   * @param threadId  Thread ID to receive a windows message to notify IPInterfaceChanged event.
   * @param initialNotify Initial Notification.  
   */
  IPInterfaceChangeNotifier(DWORD threadId, bool delInstance=false, 
    ADDRESS_FAMILY f=AF_UNSPEC, BOOL notify=FALSE) 
  :Thread(),
   looping(false),
   hNotification(NULL),
   threadIdNotified(threadId),
   hwndNotified(NULL),
   termEvent(NULL),
   deleteInstance(delInstance),
   family(f),
   initialNotification(notify)
  {
    termEvent = CreateEvent(0, FALSE, FALSE, 0);
  }


public:
  /**
   * Constructor
   * @param hwnd  Window handle to receive a windows message to notify IPInterfaceChanged event.
   * @param initialNotify Initial Notification.  
   */
  IPInterfaceChangeNotifier(HWND hwnd, bool delInstance=false, 
    ADDRESS_FAMILY f=AF_UNSPEC, BOOL notify=FALSE)
  :Thread(),
   looping(false),
   hNotification(NULL),
   threadIdNotified(0),
   hwndNotified(hwnd),
   termEvent(NULL),
   deleteInstance(delInstance),
   family(f),
    initialNotification(notify)
  {
    termEvent = CreateEvent(0, FALSE, FALSE, 0);  
  }


public:
  ~IPInterfaceChangeNotifier() 
  {
    close();
  }


private:
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
  void stop() 
  {
    SetEvent(termEvent);
    looping  = false;
  }

public:
  // Set termEvent to stop the run method loop.
  HANDLE getStopEvent() 
  {
    return termEvent;
  }

private:
  //Static Callback function for NotifyIpInterfaceChange API.

  static void WINAPI InterfaceChangeCallback(PVOID callerContext,
      PMIB_IPINTERFACE_ROW row,
      MIB_NOTIFICATION_TYPE notificationType)
  {
    IPInterfaceChangeNotifier* notifier = (IPInterfaceChangeNotifier*)callerContext;

    if (notifier) {
      //Call an instance method of class IPInterfaceChangeNotifier.
      notifier ->interfaceChanged(row, notificationType);
    }
  }


public:
  const char* getFamily(int family)
  {
    const char* name = "";

    if (family == AF_INET) {
      name = "IPv4";  
    }
    if (family == AF_INET6) {
      name = "IPv6";
    }
    return name;
  }

public:
  const char* getNotificationType(int type)
  {
    static const char* names[] = {
    "ParameterNotification",
    "AddInstance",
    "DeleteInstance",
    "InitialNotification" 
    };

    const char* name = "";
    if (type >=0 && type < XtNumber(names)) {
      name = names[type];
    }
    return name;
  }

public:
  /*
  When the callback function is received when a change occurs and the Row parameter is not NULL, 
  the pointer to the MIB_IPINTERFACE_ROW structure passed in the Row parameter contains incomplete data. 
  The information returned in the MIB_IPINTERFACE_ROW structure is only enough information that 
  an application can call the GetIpInterfaceEntry function to query complete information on the 
  IP interface that changed.  This comes from Microsoft's document. 
   */
  virtual void interfaceChanged(
      PMIB_IPINTERFACE_ROW row,
      MIB_NOTIFICATION_TYPE notificationType)
  {
    const char* family = "Unknown";
    if (row) {
      //Is row is not NULL?
      family = getFamily(row->Family);

      const char* notification = getNotificationType(notificationType);

      LocalDateTime ldt;
      StringT<char> localTime;
      ldt.nowToSeconds(localTime);
      printf("<%s %sNotification : %s>\n", (const char*)localTime,  family, notification);

      //We have to get complete information for row of MIB_IPINTERFACE_ROW  
      GetIpInterfaceEntry(row);

      display(notification, *row);

      printf("\n");
    }
  }

public:
  // This is a virtual display member function.
  // If needed to display a row data in a window, please redfine this method 
  //in your subclass which inherits this class.
  virtual void display(const char* notification, 
        MIB_IPINTERFACE_ROW& row)
  {
    IPInterfaceTable ipIfTable;

    //Display row data on the command prompt window by using printf.
    ipIfTable.display(row);
  }


public:
  /**
   * Thread procedure to get notification of IPInterfaceChanges. 
   */
  void run()
  {
    HANDLE waitEvents[1];
    waitEvents[0] = this->termEvent;

    this->looping = true;
  
    hNotification = NULL;

    //Path this pointer for the third parameter as a callerContext. 
    //
    if (NotifyIpInterfaceChange(family, 
      (PIPINTERFACE_CHANGE_CALLBACK)InterfaceChangeCallback, 
      this, 
      (BOOLEAN)initialNotification, //FALSE, 2009/09/26 
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
        PostMessage(hwndNotified, WM_IPINTERFACE_CHANGE_NOTIFER_CLOSED, 0, 0);
      }
    }

    if (deleteInstance) {
      delete this;
    }
  }

};

}
