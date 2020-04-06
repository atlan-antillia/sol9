#include <sol\Object.h>


namespace SOL {

class Module :public Object {

private:
  HMODULE hModule;

public:
  Module(__in const wchar_t* path, 
    __in DWORD dwFlags=LOAD_LIBRARY_AS_DATAFILE|LOAD_WITH_ALTERED_SEARCH_PATH)
  :hModule(NULL)
  {  
  
    if ((
      hModule = LoadLibraryExW(path, NULL, dwFlags) 
      //hModule = GetModuleHandleW(path)
      ) == NULL) {
        MessageBox(NULL, _T("Module"), NULL, MB_OK);
      throw E_FATAL;
    }
  }

public:
  ~Module()
  {
    if (hModule) {
      FreeLibrary(hModule);
      hModule = NULL;
    }    
  }

public:
  HMODULE getModule()
  {
    if (hModule == NULL) {
      throw E_FATAL;
    }
    return hModule;
  }

public:
  FARPROC getProcAddress(const char* name)
  {
    FARPROC proc = GetProcAddress(getModule(), name);
    if (proc == NULL) {
      throw E_FATAL;
    }
    return proc;
  }

public:
  HICON loadIcon(int idIcon)
  {
    HICON hIcon = (HICON)LoadImage(getModule(), MAKEINTRESOURCE(idIcon), IMAGE_ICON, 0, 0, LR_SHARED); 
    if (hIcon == NULL) {
      throw E_FATAL;
    }
    return hIcon;
  }

public:
  _bstr_t loadString(int resourceId)
  {
    wchar_t buf[1024];
  
    if (LoadStringW(getModule(), resourceId, buf, CountOf(buf)) ) {
      return _bstr_t(buf);
    } else {
      throw E_FATAL;
    }

  }

};

}
