/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  WbemQueryApplet.h
 *
 *****************************************************************************/

// SOL9

// 2010/02/24
// 2012/03/09 Updated.
// 2012/10/12 Updated.

#pragma once

#include <sol/Locale.h>
#include <sol/Exception.h>
#include <sol/Thread.h>

#include <sol/com/ApartmentThreadedModel.h>
#include <sol/com/MultiThreadedModel.h>
#include <sol/wmi/WbemQueryProperties.h>
#include <sol/wmi/WbemQueryPropertiesLoader.h>
//2010/05/08
#include <sol/wmi/WbemClassObject.h>

#include <sol/wmi/WbemLocator.h>
#include <sol/wmi/WbemServices.h>
#include <sol/wmi/WbemClassObjectEnumerator.h>

#include <sol/LocalDateTime.h>
#include <sol/wmi/WbemErrors.h>


namespace SOL {

/**
 * Thread for WbemServices::ExecQuery method call
 */
class WbemQueryApplet: public Thread {

private:
  WbemQueryProperties properties;

public:  
  /**
   * Constructor
   */
  WbemQueryApplet()
  {
    WbemQueryPropertiesLoader loader;
    loader.load(properties);
  }


public:
  //Redefine this method in your own sublcass to inherit this class.
  virtual void display(WbemClassObjectEnumerator& enumerator)
  {    
    _bstr_t reportFile = properties.getReportFile();

    FileWriter writer(reportFile);

    _bstr_t query = properties.getQuery();

    writer.writeln(L"[WbemQuery result for \"%s\"]", (const wchar_t*)query);

    LocalDateTime ldt;
    StringT<wchar_t> now;
    writer.writeln(L"(Generated on %s)", ldt.nowToSeconds(now));
    
    int i = 0;
    bool looping = true;
    while (looping) {
      try {
        //2012/10/13 WbemClassObject object = enumerator.next(0, 1, &iret);
        WbemClassObject object = enumerator.next();
        _bstr_t text = object.getObjectText(0);
        printf("\n\nObjectText No:%d %S\n", i, (const wchar_t*)text);
        writer.writeln(L"\r\n\r\nObjectText No:%d %s", i++, (const wchar_t*)text);

      } catch (HRESULT ) {
        break;
      } catch (Exception ) {
        break;   
      } catch (...) {
        break;
      }   
    }
  }

public:
  WbemQueryProperties& getQueryProperties()
  {
    return properties;
  }

public:
  /**
   * Thread procedure to watch an instance creation of Win32_Process.
   */
  virtual void run()
  {
    MultiThreadedModel   multiThreaded;
      
    try {
      WbemLocator locator;

      _bstr_t server = properties.getServer();
      _bstr_t nspace = properties.getNamespace();
      _bstr_t query  = properties.getQuery();

      _bstr_t networkPath = L"";
      if (server.length()>0) {
        networkPath = _bstr_t(L"\\\\");
        networkPath += server;
        networkPath +=  _bstr_t("\\");
        networkPath +=  nspace;
      } else {
        networkPath = nspace;
      }

      try {
        printf("NetworkPath='%S'\n", (const wchar_t*)networkPath);
        WbemServices services = locator.connectServer(networkPath);
        
        printf("Query='%S'\n", (const wchar_t*)query);
        WbemClassObjectEnumerator enumerator = services.execQuery((BSTR)query);

        display(enumerator);
      } catch (...) {

      }
    } catch (HRESULT hr) {
      WbemErrors errors;
      printf("WbemQueryApplet,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (Exception& ex) {
      ex.printf();
    } catch (...) {
      printf("WbemQueryApplet,Unknown Exception\n");
    }
  }

};

}
