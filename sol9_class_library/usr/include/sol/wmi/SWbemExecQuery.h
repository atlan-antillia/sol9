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
 *  SWbemExecQuery.h
 *
 *****************************************************************************/

// SOL9

// 2012/10/12 Updated.

#pragma once

#include <sol/Locale.h>
#include <sol/Exception.h>
#include <sol/com/ApartmentThreadedModel.h>
#include <sol/com/MultiThreadedModel.h>
#include <sol/wmi/SWbemQueryProperties.h>
#include <sol/wmi/SWbemQueryPropertiesLoader.h>

#include <sol/wmi/SWbemLocator.h>
#include <sol/wmi/SWbemServices.h>
#include <sol/wmi/SWbemObjectSet.h>

#include <sol/LocalDateTime.h>
#include <sol/wmi/WbemErrors.h>

#include <sol/Writer.h>


namespace SOL {

class SWbemExecQuery: public Object {

private:
  _bstr_t server;
  _bstr_t nspace;
  _bstr_t query;

  _bstr_t xmlFileName;

  //Writer& writer;
  Writer writer;

public:  
  /**
   * Constructor
   */
  SWbemExecQuery(const TCHAR* _server, const TCHAR* _nspace, const TCHAR* _query,
     Writer& _writer)
  :server(_server),
   nspace(_nspace),
   query(_query),
   writer(_writer)
  {

  }

public:
  virtual void display(SWbemObjectSet& objectSet)
  {
    long count = objectSet.getCount();

    writer.writeln(L"<Result count='%d'>\n", count);

    LocalDateTime ldt;
    StringT<wchar_t> now;


    for (long i = 0; i<count; i++) {
      try {
        SWbemObject object = objectSet.itemIndex(i);
        writer.writeln(L"<Object>");
          
        SWbemPropertySet propSet = object.getProperties();
        propSet.write(writer);
      
        SWbemObjectPath path = object.getPath();
        path.write(writer);
    
        SWbemSecurity security = object.getSecurity();
        security.write(writer);
        writer.writeln(L"</Object>");
  
      } catch (...) {

      }   
    }
    writer.writeln(L"</Result>\n");

  }


public:
  /**
   */
  virtual void start()
  {
    try {

      SWbemLocator locator;
    
      //writer.writeln(L"<Namespace>%s</Namespace>\n", (const wchar_t*)nspace);


      SWbemServices services = locator.connectServer(server, nspace);
        
      //writer.writeln(L"<Query>%s</Query>\n", (const wchar_t*)query);
      
      SWbemObjectSet objectSet = services.execQuery(query);

      display(objectSet);

    } catch (HRESULT hr) {
      WbemErrors errors;
      printf("SWbemExecQuery,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (...) {
      printf("SWbemExecQuery,Unknown Exception\n");
    }
  }

};

}
