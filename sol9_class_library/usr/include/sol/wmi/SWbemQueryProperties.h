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
 *  SWbemQueryProperties.h
 *
 *****************************************************************************/

// 2012/03/08 Updated
// SOL9

#pragma once

#include <sol/LinkedList.h>

#include <sol/String.h>

#include <sol/StringBuffer.h>
#include <sol/StringBufferT.h>

#include <sol/Property.h>
#include <sol/StringT.h>
#include <sol/StringConverter.h>


namespace SOL {

class SWbemQueryProperties :public Object {

private:
  LinkedList properties;

public:
  /**
   * Constructor
   */
  SWbemQueryProperties()
  {
    initialize();
  }

public:
  /**
   * Load properties from a query.properites file of parameter filePath.
   *
   * The query.properties takes the following format of multi-lines of pairs of name and value.

    ; This is a comment line, because it begins with ';'.

    name1=value1
    name2=value2
    ;...
   */
  bool load(const TCHAR* filePath)
  {
    if (filePath == NULL) {
      throw E_POINTER;
    }
    bool rc = false;

    if (GetFileAttributes(filePath) !=0xffffffff) {

      FILE* fp = NULL;
      errno_t err = fopen_s(&fp, filePath, _T("r"));
      if (err == 0 && fp !=NULL) {
        char line[1024];
        while(fgets(line, sizeof(line), fp)) {
          int slen = strlen(line);
          if (slen <=1 ) {
            continue;
          }
          if (line[slen-1] == '\n') {
            line[slen-1] = '\0';
          }
          char* eq = strchr(line, '=');
          char* name = line;
          char* value = "";
          if (eq) {
            *eq++ = '\0';
            value = eq;
          }

          char* tname = StringT<char>::trim(name);
  
          //If tname startsWith a char ';', it's a comment line, and ignore it.

          if (tname != NULL) {
            // Ignore the line beginning with ';'
            if (strlen(tname)>0 && tname[0] != ';') {                      
              char* tvalue = StringT<char>::trim(value);
              if (tvalue!=NULL) {
                putProperty(tname, tvalue);
                delete [] tvalue;
              }
            }
            delete [] tname;
          }
        }
        fclose(fp);
        rc = true;
      }            
    }
    return rc;
  }

public:
  bool putProperty(__in const char* name, __in const String& string)
  {
    bool rc = false;
      
    StringT<char> tstring;

    if (string.getString(tstring)) {
      rc = putProperty(name, (const char*)tstring);
    }

    return rc;
  }

public:
  bool putProperty(__in const char* name, __in const StringT<char>& string)
  {  
    return  putProperty(name, (const char*)string);
  }


public:
  bool putProperty(const char* name, const char* value)
  {

    bool rc = false;
    if (name == NULL || value == NULL) {
      return rc;
    }

    //properties 
    ListEntry* ptr = properties.getEntry();
    while (ptr) {
      Property* prop = (Property*)ptr->getObject();
      if (prop) {
        const char* pname = prop->getName();
        if (_strcmpi(pname, name) == 0) {
          prop->setValue(value);
          //printf("OK, Found an entry, update Property %s=%s\n", name, value);
          rc = true;
          break;
        }    
      }
      ptr = ptr->getNext();
    }
    //If not found existing initialized list
    if (rc == false) {
      properties.add(new Property(name, value));
    }
    return rc;
  }

private:
  void initialize()
  {  
    properties.add(new Property("Server", "."));    //Optional: Default "."
    properties.add(new Property("Namespace", ""));    //Required: Example "root\cimv2"
    properties.add(new Property("Query", ""));      //Required: Example "select * from WM_Process"
    properties.add(new Property("NextEvent", "10"));      //Required only for NotificationQueryApplet
                              //This specifies an interval parameter for SWbemEventSource NextEvent method iin milliseconds.

    
    properties.add(new Property("ReporFile", ""));    //Optional: Specifiy a file path name to save a query result.
    
   }


public:
  bool getValue(__in const char* name, __out String& value)
  {
    bool rc = false;
    const char* v = getValue(name);
    if (v) {
      value = v;
      rc = true;
    }
    return rc;
  }

public:
  bool getValue(__in const char* name, __out StringT<char>& value)
  {
    bool rc = false;
    const char* v = getValue(name);
    if (v) {
      value = v;
      rc = true;
    }
    return rc;
  }

public:
  const char* getValue(__in const char* name)
  {
    //Initial value = NULL;
    const char* value = NULL;  

    ListEntry* ptr = properties.getEntry();
    while (ptr) {
      Property* prop = (Property*)ptr->getObject();
      if (prop) {
        const char* n = prop->getName();
        const char* v = prop->getValue();
        if (n != NULL && _strcmpi(name, n) == 0 &&
          v != NULL && strlen(v)>0) {

          //If name found and v is not empty(strlen(v>0)
          //then, set value=v and break;
          value = v;
          break;
        }
      }
      ptr = ptr->getNext();
    }
    return value;
  }

public:
  bool getServer(__out String& value)
  {
    return getValue("Server", value);
  }

public:
  _bstr_t getServer()
  {
    BSTR  server = NULL;
    StringT<char> value;

    if (getValue("Server", value)) {
      StringConverter converter;
      server = converter.toBSTR(value);
    } else {
      server = SysAllocString(L".");
    }
    return _bstr_t(server, false);
  }

public:
  bool getNamespace(__out String& value)
  {
    return getValue("Namespace", value);
  }


public:
  _bstr_t getNamespace()
  {
    BSTR nameSpace = NULL;
    StringT<char> value;

    if (getValue("Namespace", value)) {
      StringConverter converter;
      nameSpace = converter.toBSTR(value);
    } else {
      printf("Not specified Namespace property in Query.properites file\n");
    }
    return _bstr_t(nameSpace, false);
  }


public:
  
  bool getQuery(__out String& value)
  {
    return getValue("Query", value);
  }

public:
  _bstr_t getQuery()
  {
    BSTR query = NULL;
    StringT<char> value;

    if (getValue("Query", value)) {
      StringConverter converter;
      query = converter.toBSTR(value);
    } else {
      printf("Not specified Query property in Query.properites file\n");

    }
    return _bstr_t(query, false);
  }
public:
  int getNextEvent()
  {
    int interval = 1;
    StringT<char> value;

    if (getValue("NextEvent", value)) {
      interval = atoi(value);
      if (interval <1) {
        interval = 1;
      }
    } else {
      //printf("Not specified Next property in Query.properites file\n");
    }
    return interval;
  }

public:
  //2009/12/21
  _bstr_t getReportFile()
  {
    BSTR  file = NULL;
    StringT<char> value;

    if (getValue("ReportFile", value)) {
      StringConverter converter;
      file = converter.toBSTR(value);
    } else {
      file = NULL;
    }
    return _bstr_t(file, false);
  }

};

}
