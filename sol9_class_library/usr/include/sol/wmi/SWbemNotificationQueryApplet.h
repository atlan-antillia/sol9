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
 *  SWbemNoticationQueryApplet.h
 *
 *****************************************************************************/

// 2012/03/08 Updated

// SOL9

// 2009/12/21 Modified to use SOL::ReportWriter class to save a query result.
// 2009/12/22 Modified to show an error name for an IException caught by catch caluse.

#pragma once

#include <sol/wmi/SWbemQueryApplet.h>

#include <sol/wmi/SWbemEventSource.h>
#include <sol/wmi/SWbemObjectPath.h>

namespace SOL {

/**
 * Thread for SWbemServices::ExecNotificationQuery method call.
 * This is a semi-ascyncronus query.
 */
class SWbemNotificationQueryApplet: public SWbemQueryApplet {

public:  
  /**
   * Constructor
   */
  SWbemNotificationQueryApplet()
  :SWbemQueryApplet()
  {
  }


public:
  //Please redefine this method in your own sublcass to inherit this class.

  virtual void display(SWbemEventSource& source)
  {
    //2009/12/21

    SWbemQueryProperties& properties = getQueryProperties();
    _bstr_t reportFile = properties.getReportFile();
    _bstr_t query       = properties.getQuery();

    FileWriter writer(reportFile);
      
    writer.writeln(L"[SWbemNoticaitionQuery result for \"%s\"]", (const wchar_t*)query);
    LocalDateTime ldt;
    StringT<wchar_t> now;
    writer.writeln(L"(Generated on %s)", ldt.nowToSeconds(now));

    bool looping = true;
    while (looping) { 
      try {

        int nextEventInterval = properties.getNextEvent();

        SWbemObject object   = source.nextEvent(nextEventInterval);
  
        _bstr_t text = object.getObjectText(0);
        printf("\n\nNotified ObjectText:%S\n", (const wchar_t*)text);

        writer.writeln(L"\n\nNotified ObjectText:%s", (const wchar_t*)text);
        
      } catch (...) {

      }   
    }
  }

public:
  /**
   * Thread procedure to watch an instance creation of Win32_Process.
   */
  virtual void run()
  {
    ApartmentThreadedModel apartmentThreaded;

    //MultiThreadedModel   multiThreaded;

    try {
      printf("1 Locator\n");
      SWbemLocator locator;
        
      SWbemQueryProperties& properties = getQueryProperties();

      _bstr_t server = properties.getServer();
      _bstr_t nspace = properties.getNamespace();
      _bstr_t query  = properties.getQuery();

      printf("2 ConnectServer\n");

      SWbemServices services = locator.connectServer((BSTR)server, (BSTR)nspace);

      printf("3 ExecQery\n");
        
      SWbemEventSource eventSource  = services.execNotificationQuery((BSTR)query);

      printf("4 Display\n");

      display(eventSource);

    } catch (HRESULT hr) {
      WbemErrors errors;
      printf("SWbemNotificationQueryApplet,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (...) {
      printf("SWbemNotificationQueryApplet,Unknown Exception\n");
    }
  }

};

}
