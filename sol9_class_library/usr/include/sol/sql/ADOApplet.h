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
 *  ADOApplet.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/20

// SQL Client Application base class on ADO with the SQL Native Client.
// Each ADO based application can be dervied from this base class
// by implementing a virtual run() method in each subclass.

// Assumes that environment of SQL Server 2008 and SQLClient1.0 

// 2009/05/25
// Modified to allow argc >=2 in contructor ADOApplet(int argc, const char** argv), 
// but anyway argv[1] should be a file name of Connection.properties

#include <sol/sql/ADOConnection.h>
#include <sol/sql/ADOField.h>
#include <sol/sql/ADORecord.h>
#include <sol/sql/ADOParameter.h>
#include <sol/sql/ADOParameters.h>
#include <sol/sql/ADOField.h>
#include <sol/sql/ADOFields.h>
#include <sol/sql/ADORecordset.h>
#include <sol/sql/ADOCommand.h>
#include <sol/sql/ADOStream.h>

// This should be included here to show CredentialsDialog
#include <sol/CredentialsDialog.h>

namespace SOL {

class ADOApplet: public Object{

private:
  String propertiesFile;

private:
  ADOConnectionProperties properties;

private:
  ADOConnection connection;

public:
  /**
   * Constructor
   * 1 Call OleInitialize()
   * 2 Parser argc and argv parameters and extract a filePath.
   * 3 Create an instance of ADOConenciton.
   * 4 Open a connection to a db using a file name of filePath(connection,properites file.
   *
   * @param argc A count of arguments from a commandline .
   * @param argv An Array of strings of parameters from a commandline
   *
   */
  ADOApplet(int argc, const TCHAR** argv)
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw Exception(hr, "%s: %s\n", "OleInitialize", __FUNCTION__);
    }
    connection.createInstance();

    const TCHAR* filePath = NULL;
    //if (argc == 2) {
    //2009/05/25
    if (argc >= 2) {
      filePath = argv[1];
    }
    propertiesFile = filePath;
  }

public:
  /**
   * Construction
   * Create an instance of ADOConenciton.
   * Open a connection to a db using a file name of filePath(connection,properites file.
   *
   * @param filePath  A file path to a connection.properties file.
   *
   */
  ADOApplet(const TCHAR* filePath)
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw Exception(hr, "%s: %s\n", "OleInitialize", __FUNCTION__);
    }
    connection.createInstance();

    propertiesFile = filePath;
  }

public:
  ADOApplet()
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw Exception(hr, "%s: %s\n", "OleInitialize", __FUNCTION__);
    }
    connection.createInstance();
  }

public:
  ~ADOApplet()
  {
    connection.close();

    OleUninitialize();
  }

public:
  virtual void start() 
  {
    try {
      openConnection();
      
      //Call virtual main procedure.
      run();
      
      closeConnection();

    } catch(HRESULT hr){
      printf("Exception hr=%x\n", hr);
    } catch( _com_error &e)  {
      COMError error(e);
      error.dump();
    } catch(Exception& ex){
      ex.dump();
    } catch(...) {
      printf("Exception:Unknown\n");
    }
  }

private:
  bool loadPropertiesFile(const TCHAR* propertiesFile)
  {
    bool rc = false;
    TCHAR filePath[1024];
    memset(filePath, (TCHAR)0, CountOf(filePath));

    const TCHAR* DEFAULT_PROPERTIES_FILE_NAME = _T("Connection.properties"); 
    if (propertiesFile == NULL) {
      TCHAR module[_MAX_PATH];
      memset(module, (TCHAR)0, CountOf(module));
      GetModuleFileName(NULL, module, _MAX_PATH);
      TCHAR* dot = strrchr(module, '.');
      if (dot) {
        *dot = '\0';  //NULL terminated hered
      }
      _stprintf_s(filePath, CountOf(filePath), _T("%s.%s"), module, DEFAULT_PROPERTIES_FILE_NAME);
      if (GetFileAttributes(filePath) == 0xffffffff) {
        throw Exception(E_INVALIDARG, "%s: %s: %s",  filePath, "File not found", __FUNCTION__); 
      }
    } else {
      _stprintf_s(filePath, CountOf(filePath), _T("%s"), propertiesFile);
    }
    if (GetFileAttributes(filePath) == 0xffffffff) {
      throw Exception(E_INVALIDARG, "%s:%s: %s",  filePath, "File not found", __FUNCTION__); 
    } else {
      rc = properties.load(filePath);
    }
    return rc;
  }

public:
  HRESULT openConnection()
  {
    const TCHAR* filePath = (const TCHAR*)propertiesFile;
    //printf("openConnection Connection.properties file=%s\n", filePath);

    loadPropertiesFile(filePath);
  
    String constring;
    properties.getString(constring);  
    _bstr_t connectionString = (const TCHAR*)constring;
    connection.putConnectionString(connectionString);
  
    String isecurity = "";
    String userID   = "";
    String password = "";

    if (properties.getIntegratedSecurity(isecurity) == false) {
      properties.getUserID(userID);
      properties.getPassword(password);
      CredentialsDialog credentialsDialog;
      if (credentialsDialog.show(userID, password) != NO_ERROR) {
        throw Exception(E_FAIL, "Login cancelled; %s", __FUNCTION__);  
      }
    } 
    //printf("Try to open a db with a connectionString:%s\n",
    //  (const TCHAR*)connection.getConnectionString());
    HRESULT hr = connection.open("", (const TCHAR*)userID, (const TCHAR*)password);
    //printf("OK opened a db\n");
    return hr;
  }


public:
  // This is a virtual fuction. 
  //You have to re-define this method on your own subclass.
  virtual void run()
  {
    // Implement on each subclass
  }

public:
  void closeConnection()
  {
    connection.close();
  }


public:
  ADOConnection& getConnection() 
  {
    return connection;
  }

public:
  bool getErrors(ADOErrors& errors)
  {
    return connection.getErrors(errors);
  }
};

}
