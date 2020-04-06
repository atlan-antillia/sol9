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
 *  ADOConnectionProperties.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/14
// 2009/06/05 Modified some initial values of properties in initialize() method.
// 2009/06/05 Added some methods to get property.


#pragma once

#include <sol/LinkedList.h>
#include <sol/String.h>

#include <sol/StringBuffer.h>
#include <sol/StringBufferT.h>

#include <sol/Property.h>
#include <sol/StringT.h>
#include <sol/StringConverter.h>


namespace SOL {

class ADOConnectionProperties :public Object {

private:
  LinkedList properties;

public:
  /**
   * Constructor
   */
  ADOConnectionProperties()
  {
    initialize();
  }

public:
  /**
   * Load properties from a connection.properites file of parameter filePath.
   *
   * The connection.properties takes the following format of multi-lines of pairs of name and value.

    ; Connectionstring for ADO with the SQL Native Client
    ; This is a comment line, because it begins with ';'.

    name1=value1
    name2=value2
    ;...
   */
  
  //2105/12/21 int -> bool
  bool load(const TCHAR* filePath)

  {
    if (filePath == NULL) {
      throw E_POINTER;
    }
    bool rc = false;
    if (GetFileAttributes(filePath) !=0xffffffff) {

      FILE* fp = NULL;
      errno_t err = fopen_s(&fp, filePath, _T("r"));
      if (err == 0 && fp) {
        char line[1024];
        while(fgets(line, sizeof(line), fp)) {
          int slen = strlen(line);
          if (slen <=1 ) {
            continue;
          }
          //2009/06/09
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
            } else {
              //printf("...Ignored a comment or empty line=[%s]\n", line);
            }
            delete [] tname;
            rc = true;
          }
        }
        fclose(fp);
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
    //printf("putProperty %s=%s\n", name, value);

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
    //ADO for SQL Native Client 
    //-------------------------
    properties.add(new Property("Application Name", ""));
     properties.add(new Property("Auto Translate", ""));
     properties.add(new Property("AutoTranslate", ""));
     properties.add(new Property("Connect Timeout", ""));
     properties.add(new Property("Current Language",  ""));
     properties.add(new Property("Data Source", ""));
    //2009/06/05
     //properties.add(new Property("DataTypeCompatibility", "80"));
     properties.add(new Property("DataTypeCompatibility", ""));

    properties.add(new Property("Failover Partner", ""));
     properties.add(new Property("Failover Partner SPN", ""));
    properties.add(new Property("Initial Catalog", ""));
    properties.add(new Property("Initial File Name", ""));
    properties.add(new Property("Integrated Security", ""));  //SSPI
    //2009/06/05
    //properties.add(new Property("MARS Connection", "true")); 
    properties.add(new Property("MARS Connection", "")); 

    properties.add(new Property("Network Address", ""));
    properties.add(new Property("Network Library", "")); 
     properties.add(new Property("Packet Size", ""));  //default 4096  
    properties.add(new Property("Password", ""));
      properties.add(new Property("Persist Security Info", ""));
     properties.add(new Property("Provider",  "SQLNCLI10"));  //SQL Native Client
     properties.add(new Property("Server SPN", ""));
     properties.add(new Property("Trust Server Certificate", ""));  //default false
     properties.add(new Property("Use Encryption for Data", ""));  //default false
     properties.add(new Property("User ID", ""));
     properties.add(new Property("Workstation ID", ""));

    //Keywords for IDBInitialize::Initialize, which are not recommended to use in general. 
    //--------------------------------
    properties.add(new Property("Addr", ""));  
    properties.add(new Property("Address", "")); 
    properties.add(new Property("APP", ""));  
    properties.add(new Property("AttachDBFileName", "")); 
    properties.add(new Property("Database", "")); 
    properties.add(new Property("Encrypt", "")); 
    properties.add(new Property("FailoverPartner", "")); 
    properties.add(new Property("FailoverPartnerSPN", "")); 
    properties.add(new Property("Language", "")); 
    properties.add(new Property("MarsConn", "")); 
    properties.add(new Property("Net", "")); 
    properties.add(new Property("Network", "")); 
    properties.add(new Property("PacketSize", ""));  
    properties.add(new Property("PersistSensitive", ""));
     properties.add(new Property("PWD", "")); 
     properties.add(new Property("Server", "")); 
     properties.add(new Property("ServerSPN", "")); 
     properties.add(new Property("Timeout", "")); 
     properties.add(new Property("Trusted_Connection", "")); 
     properties.add(new Property("TrustServerCertificate", ""));
    properties.add(new Property("UID", "")); 
    properties.add(new Property("UseProcForPrepare", "")); 
     properties.add(new Property("WSID", "")); 

    //2009/06/06
    // Password property for AceOleDB or JetOleDB
    //properties.add(new Property("Jet OLEDB:Database Password", ""));

  }

public:
  /**
   * Return a connection string of the following format:
   *
   *  "name1=value;name2=value2;...nameN=valueN"
   */
  int getString(__out String& connectionString)
  {
    StringBufferT<char> sbuffer;
    int rc = getString(sbuffer);

    connectionString = (const char*)sbuffer;
    return rc;
  }

public:
  /**
   * Return a connection string of the following format:
   *
   *  "name1=value;name2=value2;...nameN=valueN"
   */
  int getString(__out StringT<char>& connectionString)
  {
    StringBufferT<char> sbuffer;
    int rc = getString(sbuffer);

    connectionString = (const char*)sbuffer;
    return rc;
  }

private:
  int getString(StringBufferT<char>& sbuffer)
  {
    const static char* SOL9_PROPERTY_PREFIXE = "X_";
    const int PREFIX_LEN = strlen(SOL9_PROPERTY_PREFIXE);

    int rc = 0;

    ListEntry* ptr = properties.getEntry();
    while (ptr) {
      Property* prop = (Property*)ptr->getObject();
      if (prop) {
        const char* name = prop->getName();
        const char* value = prop->getValue();
        if (name && value && strlen(name)>0 && strlen(value)>0) {
          //2009/06/08 If name were not "X_...", then added it to stringbuffer
          if (_strnicmp(name,  SOL9_PROPERTY_PREFIXE, PREFIX_LEN) !=0) {
            char aProperty[1024];
            int len = strlen(name) + strlen(value) + strlen("=;") + 1;
            if (len < sizeof(aProperty)) {
              sprintf_s(aProperty, CountOf(aProperty), "%s=%s;", name, value);
              sbuffer.append(aProperty);
              rc++;
            }
          }
        }
      }
      ptr = ptr->getNext();
    }
    return rc;
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
  int getValueLength(const char* name)
  {
    int rc = -1;  //Non existent
    //Initial value = NULL;
    //const char* value = NULL;  

    ListEntry* ptr = properties.getEntry();
    while (ptr) {
      Property* prop = (Property*)ptr->getObject();
      if (prop) {
        const char* n = prop->getName();
        const char* v = prop->getValue();
        if (n != NULL && _strcmpi(name, n) == 0 &&
          v != NULL) {
            rc = strlen(v);
            break;
        }
      }
      ptr = ptr->getNext();
    }
    return rc;
  }

public:
  bool getIntegratedSecurity(__out String& value)
  {
    return getValue("Integrated Security", value);
  }

public:
  bool getIntegratedSecurity(__out StringT<char>& value)
  {
    return getValue("Integrated Security", value);
  }

public:
  bool getUserID(__out String& value)
  {
    bool rc = false;
    const char* val = getValue("User ID");
    if (val) {
      value = val;
      rc = true;
    } else {
      val = getValue("UID");
      value = val;
      rc = true;
    }
    return rc;
  }

public:
  bool getUserID(__out StringT<char>& value)
  {
    bool rc = false;
    const char* val = getValue("User ID");
    if (val) {
      value = val;
      rc = true;
    } else {
      val = getValue("UID");
      value = val;
      rc = true;
    }
    return rc;
  }

public:
  bool getPassword(__out String& value)
  {
    bool rc = false;
    const char* val = getValue("Password");
    if (val) {
      value = val;
      rc = true;
    } else {
      val = getValue("PWD");
      value = val;
      rc = true;
    }
    return rc;
  }

public:
  bool getPassword(__out StringT<char>& value)
  {
    bool rc = false;
    const char* val = getValue("Password");
    if (val) {
      value = val;
      rc = true;
    } else {
      val = getValue("PWD");
      value = val;
      rc = true;
    }
    return rc;
  }

public:
  //2009/06/05
  bool getInitialCatalog(__out String& value)
  {
    return getValue("Initial Catalog", value);
  }

public:
  //2009/06/05
  bool getInitialCatalog(__out StringT<char>& value)
  {
    return getValue("Initial Catalog", value);
  }


public:
  //2009/06/05
  bool getDataSource(__out String& value)
  {
    return getValue("Data Source", value);
  }

public:
  //2009/06/05
  bool getDataSource(__out StringT<char>& value)
  {
    return getValue("Data Source", value);
  }


public:
  //2009/06/05
  bool getProvider(__out String& value)
  {
    return getValue("Provider", value);
  }

public:
  //2009/06/05
  bool getProvider(__out StringT<char>& value)
  {
    return getValue("Provider", value);
  }

public:
  bool isProviderSQLNativeClient()
  {
    bool rc = false;
    String provider = "";
    if (getProvider(provider)) {
      if (provider.startsWithIgnoreCase(_T("SQLNCLI"))) {
        rc = true;
      }
    }
    return rc;
  }

public:
  bool isProviderJetOleDB()
  {
    bool rc = false;
    String provider = "";
    if (getProvider(provider)) {
      if (provider.startsWithIgnoreCase(_T("Microsoft.JET.OLEDB."))) {
        rc = true;
      }
    }
    return rc;
  }

public:
  // Return a password for AceOleDB or JetOleDB provider
  // 2009/06/05
  bool getJetOleDBPassword(__out String& value)
  {
    return getValue("Jet OLEDB:Database Password", value);
  }

public:
  // Return a password for AceOleDB or JetOleDB provider
  // 2009/06/05
  bool getJetOleDBPassword(__out StringT<char>& value)
  {
    return getValue("Jet OLEDB:Database Password", value);
  }

public:
  // Return a password for AceOleDB or JetOleDB provider
  // 2009/06/05
  int getJetOleDBPasswordLength()
  {
    return getValueLength("Jet OLEDB:Database Password");
  }

public:
  bool isProviderAceOleDB()
  {
    bool rc = false;
    String provider = "";
    if (getProvider(provider)) {
      if (provider.startsWithIgnoreCase(_T("Microsoft.ACE.OLEDB."))) {
        rc = true;
      }
    }
    return rc;
  }

public:
  void dump()
  {
    ListEntry* ptr = properties.getEntry();
    while (ptr) {
      Property* prop = (Property*)ptr->getObject();
      if (prop) {
        const char* name = prop->getName();
        const char* value = prop->getValue();
        
        printf("Property %s=%s\n", name, value);
      }
      ptr = ptr->getNext();
    }
  }
};

}
