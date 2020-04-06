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
 *  WbemNoticationQueryApplet.h
 *
 *****************************************************************************/

// SOL9
// 2010/02/24
// 2012/03/09 Updated.
// 2012/10/12 Updated.

#pragma once

#include <sol/wmi/WbemQueryApplet.h>


namespace SOL {

/**
 * Thread for WbemServices::ExecNotificationQuery method call.
 * This is a semi-ascyncronus query.
 */
class WbemNotificationQueryApplet: public WbemQueryApplet {

public:  
  /**
   * Constructor
   */
  WbemNotificationQueryApplet()
  :WbemQueryApplet()
  {
  }


public:
  //Please redefine this method in your own sublcass to inherit this class.
  
  virtual void display(WbemClassObjectEnumerator& enumerator)
  {
    WbemQueryProperties properties = getQueryProperties();

    _bstr_t reportFile = properties.getReportFile();

    FileWriter writer(reportFile);

    _bstr_t query = properties.getQuery();

    writer.write(L"[WbemQuery result for \"%s\"]\n", (const wchar_t*)query);

    LocalDateTime ldt;
    StringT<wchar_t> now;
    writer.write(L"(Generated on %s)\n", ldt.nowToSeconds(now));
    
    int i = 0;
    bool looping = true;
    while (looping) {
      ULONG iret = 0;
      try {
        WbemClassObject object = enumerator.next(100, 1, &iret);
        if (iret == 0) {
          continue;
        }
        
        _bstr_t text = object.getObjectText(0);

        printf("\n\nObjectText No:%d %S\n", i, (const wchar_t*)text);
        
        writer.write(L"\n\nObjectText No:%d %s\n", i, (const wchar_t*)text);
        
      } catch (HRESULT hr) {
        WbemErrors errors;
        printf("WbemNotificationQueryApplet::display Exception HRESULT=%x description%s\n",
          hr, errors.getName(hr));
        //break;

      } catch (Exception ex) {
        ex.printf();
        WbemErrors errors;
        HRESULT hr = ex.getHRESULT();
        printf("WbemNotificationQueryApplet::Exception:HRESULT=%08x %s", hr, errors.getName(hr));
        //break;
      } catch (...) {
        printf("WbemNotificationQueryApplet::display Unknown Exception \n");
        //break;
      }   
    }
  }


public:
  /**
   * Thread procedure to watch an instance creation of Win32_Process.
   */
  virtual void run()
  {
    MultiThreadedModel   multiThreaded;

    try {
      printf("1 Locator\n");
      WbemLocator locator;
        
      WbemQueryProperties& properties = getQueryProperties();

      _bstr_t server = properties.getServer();
      _bstr_t nspace = properties.getNamespace();
      _bstr_t query  = properties.getQuery();


      printf("2 ConnectServer\n");
      _bstr_t networkPath = L"";
      if (server.length()>0) {
        networkPath = L"\\\\";
        networkPath = networkPath + server;
        networkPath = networkPath + _bstr_t("\\");
        networkPath = networkPath + nspace;
      } else {
        networkPath = (BSTR)nspace;
      }
      //2012/10/12 Modified to use (const BSTR)(const wchar_t*).
      
      WbemServices services = locator.connectServer((const BSTR)(const wchar_t*)networkPath);

      printf("3 ExecNotificationQuery '%S'\n", (BSTR)query);
        
      WbemClassObjectEnumerator enumerator =  services.execNotificationQuery((BSTR)query);

      printf("4 Display\n");

      display(enumerator);

    } catch (HRESULT hr) {
      WbemErrors errors;
      printf("WbemNotificationQueryApplet,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (...) {
      printf("WbemNotificationQueryApplet,Unknown Exception\n");
    }
  }

};

}
