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
 *  SWbemQueryThread.h
 *
 *****************************************************************************/

// SOL9
// 2015/12/14


#pragma once

#include <sol/Locale.h>
#include <sol/BString.h>
#include <sol/Exception.h>
#include <sol/Thread.h>
#include <sol/StringListT.h>
#include <sol/com/ApartmentThreadedModel.h>
#include <sol/com/MultiThreadedModel.h>
#include <sol/wmi/SWbemQueryProperties.h>
#include <sol/wmi/SWbemQueryPropertiesLoader.h>

#include <sol/wmi/SWbemLocator.h>
#include <sol/wmi/SWbemServices.h>
#include <sol/wmi/SWbemObjectSet.h>

#include <sol/LocalDateTime.h>

#include <sol/wmi/WbemErrors.h>
#include <sol/StringTokenizerT.h>
#include <sol/WcharProperty.h>


namespace SOL {

/**
 * Thread for SWbemServices::ExecQuery method call
 */
class SWbemQueryThread: public Thread {
private:
 
  BString server;
  BString nspace;
  BString query; 

  long count;
  StringListT<wchar_t> textList;
  
public:  
  /**
   * Constructor
   * For example, the parameters take the following strings:
   * serverName = ".",
   * nameSpace  = "root\\cimv2",
   * queryString = "select * from Win32_OperationSystem".
   */
  SWbemQueryThread(const char* serverName, const char* nameSpace, const char* queryString )
  :server(serverName),
  nspace(nameSpace),
  query(queryString)  
  {
  }

  /*
   Constructor 
 
   For example, the queryTemplate and target parameters take the following strings:
   queryTemplate = "select %s from Win32_OperationSystem",
   target        = "Caption" or "*".
  */
  SWbemQueryThread(const char* serverName, const char* nameSpace, const char* queryTemplate, const char* target )
  :server(""),
  nspace(""),
  query("")  
  {
    if (serverName == NULL || nameSpace == NULL || queryTemplate == NULL || target == NULL) {
      throw IException("Invalid argument."); 
    }
    server = serverName;
    nspace = nameSpace;
    if (strstr(queryTemplate, "%s") ) {
      const int bsize = strlen(queryTemplate) + strlen(target) + 1;
      char* buffer = new char[bsize];
      sprintf_s(buffer, bsize, queryTemplate, target);
      query = buffer;
      delete [] buffer;
    } else {
      throw IException("Invalid queryTemplate");
    }
  }

  SWbemQueryThread(const wchar_t* serverName, const wchar_t* nameSpace, const wchar_t* queryString )
  :server(serverName),
  nspace(nameSpace),
  query(queryString)  
  {
  }

public:
  long getObjectSetCount()
  {
    return count;
  }
 
  const wchar_t* getObjectText(int index = 0)
  {
    StringT<wchar_t>* text = textList.getNth(index);
    return (const wchar_t*)(*text);
  }
  
  void getObjectText(int index, StringT<wchar_t>& value)
  {
    static const wchar_t WZERO = '\0';
    static const wchar_t WLPAREN = '{';
    static const wchar_t WRPAREN = '}';
    
    int lenNewline = wcslen(L"\r\n");
    
    StringT<wchar_t>* text = textList.getNth(index);
    
    const wchar_t* string = new_strdup((const wchar_t*)(*text));

    const wchar_t* lp = wcschr (string, WLPAREN);
    const wchar_t* rp = wcsrchr(string, WRPAREN);
    
    value = L"";
    
    if (lp && rp) {
      lp += lenNewline;  
      rp -= lenNewline;  
      wchar_t* tail = (wchar_t*)rp;
      *tail = WZERO;
      value = lp;
    }
    delete string;
  }

  void dump()
  {
    for (long i = 0; i<count; i++) {
      printf("%S\n", getObjectText(i));  
    }
  }
  
  void display()
  {
    for (long i = 0; i< getObjectSetCount(); i++) {
      StringT<wchar_t> name;
      // Get a list of Name="Value" pair.
      getObjectText(i, name);
      //printf("%S\n", (const wchar_t*)name);
      StringTokenizerT<wchar_t> tokenizer((const wchar_t*)name);
      tokenizer.clearSeparator();
      tokenizer.addSeparator((wchar_t)'\n');
      while(tokenizer.hasMoreToken()) {
        StringT<wchar_t> line;
        //Get a line ended with a newline from the object text 'name'.
        tokenizer.getToken(line);
        if (line.getLength() > 1) {
          // Split the property of the format 'name=value' to name and value by using WcharProperty.
          WcharProperty property(line);
          property.dump();
        }
      }
    }
  }
  
public:
  //
  virtual void run()
  {
    ApartmentThreadedModel apartmentThreaded;

    try {
      SWbemLocator locator;
      SWbemServices services  = locator.connectServer((BSTR)server, (BSTR)nspace);

      SWbemObjectSet objectSet = services.execQuery((BSTR)query);

      count = objectSet.getCount();

      _bstr_t text = L"";
      for (long i = 0; i<count; i++) {
        SWbemObject object = objectSet.itemIndex(i);
        _bstr_t text = object.getObjectText(0);
        textList.addLast(new StringT<wchar_t>((const wchar_t*)text));
      }    
    } catch (HRESULT hr) {
      WbemErrors errors;
      throw IException("SWbemQueryThread,Exception:HRESULT=%08x %s", hr, errors.getName(hr));
    } catch (...) {
      throw IException("SWbemQueryThread,Unknown Exception\n");
    }
  }

};

}
