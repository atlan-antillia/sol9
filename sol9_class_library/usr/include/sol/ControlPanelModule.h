/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ControlPanelModule.h
 *
 *****************************************************************************/


#include <sol\Module.h>
#include <cpl.h>

namespace SOL {

/*
typedef struct tagCPLINFO
{
    int         idIcon;
    int         idName;
    int         idInfo;
    LONG_PTR    lData;
} CPLINFO, *LPCPLINFO;
 */


class ControlPanelModule :public Module {

typedef LONG (APIENTRY *CPLAPPLET)(HWND, UINT, LPARAM, LPARAM);

private:

  CPLAPPLET cplApplet;
  HWND     hOwner;
  CPLINFO   cplInfo;

public:
  ControlPanelModule(__in const wchar_t* path)
    :Module(path, 0),
    cplApplet(NULL),
    hOwner(NULL)
  {  
    cplApplet = (CPLAPPLET)getProcAddress("CPlApplet");
    
    memset(&cplInfo, 0, sizeof(cplInfo));
  }

public:
  bool initialize(HWND hwnd)
  {
    bool rc = true;
    hOwner = hwnd;
    try {
      if (cplApplet(hOwner, CPL_INIT, 0, 0) == 0) {
      //MessageBox(NULL, _T("Error1"), NULL, MB_OK);
        throw E_FATAL;
      }

      cplApplet(hOwner, CPL_GETCOUNT, 0, 0);

      cplApplet(hOwner, CPL_INQUIRE,  0, (LPARAM)&cplInfo);
      //MessageBox(NULL, _T("Error3"), NULL, MB_OK);

      //throw E_FATAL;
    
    } catch (...) {
    }

    return rc;
  }

public:
  ~ControlPanelModule()
  {
    if (cplApplet) {
      cplApplet(hOwner, CPL_EXIT, 0, 0);
    }    
  }


public:
  HICON getIcon()
  {
    return loadIcon(cplInfo.idIcon);
  }

public:
  _bstr_t getName()
  {
    return loadString(cplInfo.idName);
  }

public:
  _bstr_t getInfo()
  {
    return loadString(cplInfo.idInfo);
  }

public:
  LONG_PTR getData()
  {
    return cplInfo.lData;
  }

};

}
