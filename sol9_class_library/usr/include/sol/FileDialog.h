/******************************************************************************
 *
 * Copyright (c) 1999-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileDialog.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/22

#pragma once

#include <sol/Application.h>
#include <sol/StringT.h>
#include <sol/CommonDialog.h>
#include <direct.h>

namespace SOL {

class FileDialog :public CommonDialog {
private:
  DWORD  flags;
  TCHAR   directory[_MAX_PATH];
  TCHAR  filename[_MAX_PATH];
  TCHAR  fileTitle[_MAX_PATH];
//  BOOL  fileSave;
  int    accessMode;
  OPENFILENAME ofn;

public:
  static const int OPEN = 0;
  static const int SAVE = 1;

  
public:
  /**
   * Constructor
   */
    
  FileDialog(): CommonDialog() 
  {
    filename[0]  = ZERO;
    fileTitle[0] = ZERO;
    directory[0] = ZERO;
    memset(&ofn, 0, sizeof(OPENFILENAME));
  }

public:
  /**
   * Constructor
   */
  FileDialog(View* parent, const TCHAR* caption, Args& args)
  :CommonDialog()
  {
    create(parent, caption, args);
  }


public:
  virtual Boolean create(View* parent, const TCHAR* caption, Args& args)
  {
    Boolean rc = CommonDialog::create(parent, &ofn);

    filename[0]  = ZERO;
    fileTitle[0] = ZERO;
    directory[0] = ZERO;

    memset(&ofn, 0, sizeof(OPENFILENAME));
    _getcwd(directory, _MAX_PATH);
  
    ofn.lpstrInitialDir= directory; 
    ofn.lStructSize    = sizeof(OPENFILENAME);
    ofn.lpstrFilter    = _T("All files (*.*) \0 *.*\0");
    ofn.nFilterIndex   = 1;
    ofn.lpstrFile      = filename;
    ofn.nMaxFile       = _MAX_PATH;
    ofn.lpstrFileTitle = fileTitle;
    ofn.nMaxFileTitle  = _MAX_PATH;
    ofn.lpstrTitle     = caption;
    ofn.lpstrDefExt    = (TCHAR*)args.get(XmNextension);
    if(parent) {
      ofn.hwndOwner  = parent->getWindow();
    }
    ofn.hInstance      = GetModuleHandle(NULL);
    //applet.getInstance();//Application::getInstance();
    
    //2009/11/04
    ofn.lCustData  =     (long)this;
    
    flags = NULL;

    // FileOpen in default.
    accessMode = OPEN;

    setValues(args);
    return rc;
  }

public:
  ~FileDialog() 
  {
  }


public:
  int open()
  {
    filename[0]  = ZERO;
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    return ::GetOpenFileName(&ofn);
  }
public:
  int openAllFiles()
  {
    _T("All files (*.*) \0 *.*\0");
    filename[0]  = ZERO;
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    return ::GetOpenFileName(&ofn);
  }

  int openImageFiles()
  {
    const TCHAR* filter = getImageFilesFilter();
    filename[0]  = ZERO;
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    ofn.lpstrFilter = filter;
    return ::GetOpenFileName(&ofn);
  }

public:
  int save()
  {
    //2012/06/12/filename[0]  = ZERO;
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_OVERWRITEPROMPT;
    return ::GetSaveFileName(&ofn);
  }
  
public:
  int saveAllFiles()
  {
    const TCHAR* filter = getAllFilesFilter();
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_OVERWRITEPROMPT;
    ofn.lpstrFilter = filter;    
    return ::GetSaveFileName(&ofn);
  }

public:
  int saveImageFiles()
  {
    const TCHAR* filter = getImageFilesFilter();
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_OVERWRITEPROMPT;
    ofn.lpstrFilter = filter;    
    return ::GetSaveFileName(&ofn);
  }

public:
  //2017/07/25
  int saveVideoFiles()
  {
    const TCHAR* filter = getVideoFilesFilter();
    fileTitle[0] = ZERO;
    ofn.Flags = flags|OFN_OVERWRITEPROMPT;
    ofn.lpstrFilter = filter;    
    return ::GetSaveFileName(&ofn);
  }
  
public:
  void getValues(Args& args)
  {
    LONG_PTR* val = NULL;
    int num   = args.getCount();
    Arg* arg  = args.getArgList();

    for(int i = 0; i<num; i++) {
      const TCHAR* name = arg[i].name;
      //<modified date="2000.01.09">
      val = (LONG_PTR*)arg[i].value;
      //</modified>

      if (name == XmNflags) {
        *val = (LONG_PTR)flags;
        continue;
      }
      if (name == XmNdirectory) {
        *val = (LONG_PTR)directory;
        continue;
      }
      if (name == XmNfilter) {
        *val = (LONG_PTR)ofn.lpstrFilter;
        continue;
      }
      if (name == XmNfileName) {
        *val = (LONG_PTR)filename;
        continue;
      }
      if (name == XmNfileTitle) {
        *val = (LONG_PTR)fileTitle;
        continue;
      }
    }
  }

public:
  void setValues(Args& args)
  {
    LONG_PTR val;
    if (args.get(XmNaccessMode, &val)) {
      accessMode = (int)val;
    }

    if (args.get(XmNflags, &val)) {
      flags = (DWORD)val;
    }
    if (args.get(XmNhook, &val)) {
      flags |= OFN_ENABLEHOOK;
      //2009/11/01
      ofn.lpfnHook = (LPOFNHOOKPROC)hookProc;
    }
    if (args.get(XmNfileName, &val)) {
      //2008/09/13 sizeof._MAX_PATH
      strcpy_s(filename, _MAX_PATH, (TCHAR*)val);
    }
    if (args.get(XmNdirectory, &val)) {
      //2008/09/13 sizeof._MAX_PATH
      strcpy_s(directory, _MAX_PATH, (TCHAR*)val);
      ofn.lpstrInitialDir= directory; 

    }
    if (args.get(XmNfilter, &val)) {
      ofn.lpstrFilter = (TCHAR*)val;
    }
    if (args.get(XmNfilterIndex, &val)) {
      ofn.nFilterIndex = (int)val;
    }

    if (args.get(XmNdialogTitle, &val)) {
      ofn.lpstrTitle  = (TCHAR*)val;
    }
    if (args.get(XmNtemplateName, &val)) {
      flags |= OFN_ENABLETEMPLATE;
      ofn.lpTemplateName  = (TCHAR*)val;
    }
  }

public:
  // Modal
  void popup(Action& action)
  {
    int result = NULL;
    if(accessMode == SAVE) {
      result = save();
    }
    else {
      result = open();
    }
  
    action.setResult(result);
  }

public:
  void setCaption(const TCHAR* caption)
  {
    ofn.lpstrTitle = (TCHAR*)caption;
  }

public:
  TCHAR*  getFileName() {
      return filename;
  }

public:
  TCHAR*  getFileTitle() {
      return fileTitle;
  }
  
  
  //2017/03/25
  static const TCHAR* getImageFilesFilter()
  {
    static const TCHAR* filters =
    _T("All Files    (*.*)\0*.*\0")
    _T("PNG files   (*.png)\0*.png\0")
    _T("Bitmap files (*.bmp;*.dib)\0*.bmp;*.dib\0")
    _T("JPEG files   (*.jpeg;*.jpg;*.jpe)\0*.jpeg;*.jpg;*.jpe\0")
    _T("TIFF Files   (*.tiff;*.tif)\0*.tiff;*.tif\0";)
    return filters;
  }
  
  static const TCHAR* getVideoFilesFilter()
  {
     static const TCHAR* filters = 
    _T("All Files   (*.*)\0*.*\0")
    _T("AVI files   (*.avi)\0*.avi\0")
    _T("MOV files   (*.mov)\0*.mov\0")
    _T("MP4 files   (*.mp4)\0*.mp4\0")
    _T("WMV Files   (*.wmv)\0*.wmv\0";)
    return filters;
  }
    
  static bool isImageFileName(const TCHAR* filename)
  {
    const TCHAR* extensions[] = {
      _T(".png"),
      _T(".bmp"),
      _T(".dib"),
      _T(".jpeg"),
      _T(".jpg"),
      _T(".jpe"),
      _T(".tiff"),
      _T(".tif")
    };
    bool rc = false;
    for (int i = 0; i<CountOf(extensions); i++) {
      if (StringT<TCHAR>::endsWithIgnoreCase(filename, extensions[i]) ) {
        //Printf(_T("%s %s"), filename, extensions[i]);
        rc = true;
        break;
      }
    }
    return rc;
  }

  static bool isVideoFileName(const TCHAR* filename)
  {
    static const TCHAR* extensions[] = {
      _T(".avi"),
      _T(".mov"),
      _T(".mp4"),
      _T(".wmv")
    };
    bool rc = false;
    for (int i = 0; i<CountOf(extensions); i++) {
      if (StringT<TCHAR>::endsWithIgnoreCase(filename, extensions[i]) ) {
        //Printf(_T("%s %s"), filename, extensions[i]);
        rc = true;
        break;
      }
    }
    return rc;
  }

  static const TCHAR* getAllFilesFilter()
  {
    static const TCHAR* filter = _T("All files (*.*) \0 *.*\0");
    return filter;
  }
};

}


