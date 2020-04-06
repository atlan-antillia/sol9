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
 *  SWbemQueryApplet.h
 *
 *****************************************************************************/

// SOL9

// 2009/12/21 Modified to use SOL::ReportWriter class to save a query result.
// 2009/12/22 Modified to show an error name for an IException caught by catch caluse.
// 2012/03/08 Updated.

#pragma once

#include <sol/Locale.h>
#include <sol/Exception.h>
#include <sol/Thread.h>
#include <sol/com/ApartmentThreadedModel.h>
#include <sol/com/MultiThreadedModel.h>
#include <sol/wmi/SWbemQueryProperties.h>
#include <sol/wmi/SWbemQueryPropertiesLoader.h>

#include <sol/wmi/SWbemLocator.h>
#include <sol/wmi/SWbemServices.h>
#include <sol/wmi/SWbemObjectSet.h>

//2003/12/22
#include <sol/LocalDateTime.h>
#include <sol/wmi/WbemErrors.h>


namespace SOL {

/**
 * Thread for SWbemServices::ExecQuery method call
 */
class SWbemQueryApplet: public Thread {

private:
  SWbemQueryProperties properties;


public:  
  /**
   * Constructor
   */
  SWbemQueryApplet()
  {
    SWbemQueryPropertiesLoader loader;
    loader.load(properties);
  }


public:
  //Redefine this method in your own sublcass to inherit this class.

  virtual void display(SWbemObjectSet& objectSet)
  {
    long count = objectSet.getCount();
    
    _bstr_t reportFile = properties.getReportFile();
        //2015/07/15
    FileWriter writer((const wchar_t*)reportFile);

    _bstr_t query = properties.getQuery();

    writer.writeln(L"[SWbemQuery result for \"%s\"]", (const wchar_t*)query);

    LocalDateTime ldt;
    StringT<wchar_t> now;
    writer.writeln(L"(Generated on %s)", ldt.nowToSeconds(now));

    for (long i = 0; i<count; i++) {
      try {
        SWbemObject object = objectSet.itemIndex(i);

        _bstr_t text = object.getObjectText(0);
        //printf("\n\nObjectText No:%d %S\n", i, (const wchar_t*)text);
        
        writer.writeln(L"\r\n\r\nObjectText No:%d %s", i, (const wchar_t*)text);
              
      } catch (...) {

      }   
    }
  }

public:
  SWbemQueryProperties& getQueryProperties()
  {
    return properties;
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
  
      SWbemLocator locator;

      _bstr_t server = properties.getServer();
      _bstr_t nspace = properties.getNamespace();
      _bstr_t query  = properties.getQuery();

      SWbemServices services = locator.connectServer((BSTR)server, (BSTR)nspace);
        

      SWbemObjectSet objectSet = services.execQuery((BSTR)query);

      display(objectSet);

    } catch (HRESULT hr) {
      WbemErrors errors;
      printf("SWbemQueryApplet,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (...) {
      printf("SWbemQueryApplet,Unknown Exception\n");
    }
  }

};

}
