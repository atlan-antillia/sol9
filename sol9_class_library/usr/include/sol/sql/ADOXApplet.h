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
 *  ADOXApplet.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/05

// SQL Client Application base class on ADOX with the SQL Native Client, OLEDB and so on.
// Each ADOX based application can be dervied from this base class
// by implementing a virtual run() method in each subclass.

// Assumes that environment of SQL Server 2008 and SQLClient1.0 or Access2007 

#include <sol/sql/ADOApplet.h>
#include <sol/sql/ADOXCatalog.h>

// This should be included here to show CredentialsDialog
#include <sol/CredentialsDialog.h>

namespace SOL {

class ADOXApplet: public Object{

private:
  String propertiesFile;

private:
  ADOConnectionProperties properties;

private:
  ADOXCatalog catalog;

public:
  /**
   * Constructor
   * 1 Call OleInitialize()
   * 2 Parser argc and argv parameters and extract a filePath.
   * 3 Create an instance of ADOXCatalog.
   *
   * @param argc A count of arguments from a commandline .
   * @param argv An Array of strings of parameters from a commandline
   *
   */
  ADOXApplet(int argc, const TCHAR** argv)
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw Exception(hr, "%s: %s\n", "OleInitialize", __FUNCTION__);
    }
    catalog.createInstance();

    const TCHAR* filePath = NULL;

    if (argc >= 2) {
      filePath = argv[1];
    }
    propertiesFile = filePath;
  }

public:
  /**
   * Construction
   * Create an instance of ADOXCatalog.
   *
   * @param filePath  A file path to a connection.properties file.
   *
   */
  ADOXApplet(const TCHAR* filePath)
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw Exception(hr, "%s: %s\n", "OleInitialize", __FUNCTION__);
    }
    catalog.createInstance();

    propertiesFile = filePath;
  }

public:
  ADOXApplet()
  {
    HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) {
      throw Exception(hr, "%s: %s\n", "OleInitialize", __FUNCTION__);
    }
    catalog.createInstance();
  }

public:
  ~ADOXApplet()
  {
    catalog.close();

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
  /*
   * Connect or create a connection to a catalog using a file name of 
   * filePath(connection,properites file.
   */
  HRESULT openConnection()
  {
    static const char* JET_OLEDB_PASSWORD = "Jet OLEDB:Database Password";

    const TCHAR* filePath = (const TCHAR*)propertiesFile;
    //_tprintf(_T("openConnection Connection.properties file=%s\n"), filePath);

    loadPropertiesFile(filePath);
    //properties.dump();

    StringT<char> constring;
    properties.getString(constring);  
    _bstr_t connectionString = (const char*)constring;
    //printf("ConnectionString =%S\n", (const wchar_t*)connectionString);
    String provider = "";
    bool nativeClient = properties.isProviderSQLNativeClient();
    bool jetOleDB     = properties.isProviderJetOleDB();
    bool aceOleDB     = properties.isProviderAceOleDB();

    String jetOleDBPassword = "";
    properties.getJetOleDBPassword(jetOleDBPassword);
    int jetOleDBPasswordLen = properties.getJetOleDBPasswordLength();
    String isecurity = "";
    String userID   = "";
    String password = "";
        
    properties.getUserID(userID);
    properties.getPassword(password);

    //2009/06/05
    if (properties.getIntegratedSecurity(isecurity) == false) {
      //Need password
      
      if ((jetOleDB || aceOleDB) ) {
        if (jetOleDBPasswordLen>0) {
          connectionString = connectionString + _bstr_t(JET_OLEDB_PASSWORD)+ _bstr_t("=") + 
            _bstr_t((const TCHAR*)jetOleDBPassword);
        } 
        if (jetOleDBPasswordLen==0){
          //Prompt password
          CredentialsDialog credentialsDialog;
          if (credentialsDialog.show(userID, password) != NO_ERROR) {
            throw Exception(E_FAIL, "Login cancelled; %s", __FUNCTION__);  
          }
          properties.putProperty(JET_OLEDB_PASSWORD, password);
          String nconstring;
          properties.getString(nconstring);  
          connectionString = (const TCHAR*)nconstring;
          //printf("Connstring=%s\n", (const char*)connectionString);
        }
        else {
          ;//printf("Do not do nothing\n");
        }
      } else {
        //In case of SQLNCLI1.0        
        CredentialsDialog credentialsDialog;
        if (credentialsDialog.show(userID, password) != NO_ERROR) {
          throw Exception(E_FAIL, "Login cancelled; %s", __FUNCTION__);  
        }
        if (nativeClient) {
          connectionString = connectionString + _bstr_t("User ID=") + _bstr_t((const TCHAR*)userID) + _bstr_t(";");
          connectionString = connectionString + _bstr_t("Password=") + _bstr_t((const TCHAR*)password);
        }
      }
    }
    
  //  printf("Try to open(connect or create) a catalog with a connectionString:%s\n",
  //    (const char*)connectionString);
      
    HRESULT hr = catalog.open(connectionString);

  //  printf("OK opened a catalog\n");
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
    catalog.close();
  }


public:
  ADOXCatalog& getCatalog() 
  {
    return catalog;
  }

public:
  ADOConnectionProperties& getConnectionProperties()
  {
    return properties;
  }

public:
  bool getConnectionProerty(const char* name, String& value)
  {
    return properties.getValue(name, value);
  }

public:
  bool getXMLEncoding(String& value)
  {
    //default encoding
    value = "UTF-8";
    return properties.getValue("X_XML_ENCODING", value);
  }

public:
  bool getInitialCatalog(String& initialCatalog)
  {
    return properties.getInitialCatalog(initialCatalog);
  }

public:
  // dump some importantant connection properties
  void showConnectionProperties()
  {
    String provider = "";
    properties.getProvider(provider);
    _tprintf(_T("Provider =\"%s\"\n"), (const TCHAR*)provider);

    String integratedSecurity = "";
    properties.getIntegratedSecurity(integratedSecurity);
    _tprintf(_T("Integrated Security =\"%s\"\n"), (const TCHAR*)integratedSecurity);

    String initialCatalog = "";
    properties.getInitialCatalog(initialCatalog);
    _tprintf(_T("Initial catalog =\"%s\"\n"), (const TCHAR*)initialCatalog);

    String dataSource = "";
    properties.getDataSource(dataSource);
    _tprintf(_T("Data Source =\"%s\"\n"), (const TCHAR*)dataSource);
  }
};

}
