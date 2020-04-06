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
 *  WbemNotificationQueryAsyncApplet.h
 *
 *****************************************************************************/

// SOL9
// 2010/02/24
// 2012/03/09 Updated.
// 2012/10/12 Updated.

#pragma once

#include <sol/wmi/WbemQueryApplet.h>
#include <sol/wmi/WbemObjectSink.h>


namespace SOL {

/**
 * Thread for WbemServices::ExecNotificationQuery method call.
 * This is a semi-ascyncronus query.
 */
class WbemNotificationQueryAsyncApplet: public WbemQueryApplet {

public:  
  /**
   * Constructor
   */
  WbemNotificationQueryAsyncApplet()
  :WbemQueryApplet()
  {
  }


public:
  /**
   * Thread procedure to watch an instance creation of Win32_Process.
   */
  virtual void run()
  {
    try {
      printf("1 Locator\n");
      WbemLocator locator;
        
      WbemQueryProperties& properties = getQueryProperties();

      _bstr_t server = properties.getServer();
      _bstr_t nspace = properties.getNamespace();
      _bstr_t query  = properties.getQuery();

      printf("2 ConnectServer\n");
      
      //_bstr_t 
      _bstr_t networkPath = L"";
      if (server.length()>0) {
        networkPath = L"\\\\";
        networkPath = networkPath + server;
        networkPath = networkPath + _bstr_t("\\");
        networkPath = networkPath + nspace;
      } else {
        networkPath = (BSTR)nspace;
      }
  
      WbemServices services = locator.connectServer((BSTR)networkPath);
      
      WbemObjectSink objectSink;
    
      printf("3 ExecNotificationQueryAsync\n");        
      
      HRESULT hr = S_OK;
      if (SUCCEEDED(hr = services.execNotificationQueryAsync((BSTR)query,
        &objectSink))) {

        bool looping = true;

        while(looping) {
          // The services->execNotificationQueryAsync(...) method will call the virtual 
          // WbemProcessSink::Indicate method when an event occurs
          Sleep(500);
        }
      }

    } catch (HRESULT hr) {
      WbemErrors errors;
      printf("WbemNotificationQueryAsyncApplet,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (Exception ex) {
      ex.printf();
      WbemErrors errors;
      HRESULT hr = ex.getHRESULT();
      printf("WbemNotificationQueryAsyncApplet,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (...) {
      printf("WbemNotificationQueryAsyncApplet,Unknown Exception\n");
    }
  }

};

}
