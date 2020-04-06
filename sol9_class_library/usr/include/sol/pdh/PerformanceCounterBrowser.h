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
 *  PerformanceCounterBrowser.h
 *
 *****************************************************************************/

// SOL9
// 2009/09/30

#pragma once
#include <sol/Object.h>
#include <sol/String.h>

#include <pdh.h>  // DWORD,PDH_FMT_LONG‘¼
#include <pdhmsg.h>  // PDH_MORE_DATA
//#include <stdio.h>

#pragma comment( lib, "pdh.lib" )

namespace SOL {

class PerformanceCounterBrowser :public Object {

private:
  HWND hOwner;
  
private:
  PDH_BROWSE_DLG_CONFIG config;

private:
  TCHAR counterPath[1024];

public:
  PerformanceCounterBrowser()
  :hOwner(NULL)
  {
    memset(counterPath, (TCHAR)0, CountOf(counterPath));
  }

public:
  Boolean create(HWND hparent, const TCHAR* title, DWORD level=PERF_DETAIL_WIZARD)
  {
    Boolean rc = True;
    memset(counterPath, (TCHAR)0, CountOf(counterPath));

    memset(&config, 0, sizeof(config));

    hOwner = hparent;
    if (title) {
      config.szDialogBoxCaption = (TCHAR*)title; 
    }
    config.hWndOwner = hOwner;
    config.bIncludeInstanceIndex    = TRUE;//FALSE;
    config.bSingleCounterPerAdd     = TRUE;
    config.bSingleCounterPerDialog  = TRUE;
    config.bLocalCountersOnly       = TRUE;
    config.bWildCardInstances       = TRUE;
    config.bHideDetailBox           = TRUE;

    config.bInitializePath          = FALSE;
    config.bDisableMachineSelection = FALSE;
    config.bIncludeCostlyObjects    = FALSE;
    config.bShowObjectBrowser       = FALSE;

    config.szDataSource             = NULL;
    config.szReturnPathBuffer       = counterPath;
    config.cchReturnPathLength      = CountOf(counterPath);
    config.pCallBack                = NULL;
    config.dwCallBackArg            = 0;
    config.CallBackStatus           = ERROR_SUCCESS;
    config.dwDefaultDetailLevel     = level;

    return rc;
  }


public:
  DWORD select(__out String& path)
  {
    path = "";
    memset(counterPath, (TCHAR)0, CountOf(counterPath));

    config.szReturnPathBuffer = counterPath;  
    config.cchReturnPathLength = CountOf(counterPath);

    PDH_STATUS status = PdhBrowseCounters(&config);
    
    if (status == ERROR_SUCCESS) {
      path = counterPath;
    }
    
    return status;
  }

public:
  bool getCounterPath(__out String& path)
  {
    bool rc = false;
    path = "";
    if (strlen(counterPath)>0) {
      path = counterPath;
      rc = true;
    }
    return rc;
  }

// Setter
public:
  void setIncludeInstanceIndex(BOOL value)
  {
    config.bIncludeInstanceIndex    = value;
  }

public:
  void setSingleCounterPerAdd(BOOL value)
  {
    config.bSingleCounterPerAdd     = value;
  }

public:
  void setSingleCounterPerDialog(BOOL value)
  {
    config.bSingleCounterPerDialog  = value;
  }

public:
  void setLocalCountersOnly(BOOL value)
  {
    config.bLocalCountersOnly       = value;
  }

public:
  void setWildCardInstances(BOOL value)
  {

    config.bWildCardInstances       = value;
  }

public:
  void setHideDetailBox(BOOL value)
  {
    config.bHideDetailBox           = value;
  }

public:
  void setInitializePath(BOOL value)
  {
    config.bInitializePath          = FALSE;
  }

public:
  void setDisableMachineSelection(BOOL value)
  {
    config.bDisableMachineSelection = FALSE;
  }
public:
  void setIncludeCostlyObjects(BOOL value)
  {
    config.bIncludeCostlyObjects    = value;
  }

public:
  void setShowObjectBrowser(BOOL value)
  {
    config.bShowObjectBrowser       = value;
  }

public:
  void setDefaultDetailLevel(DWORD level)
  {
    config.dwDefaultDetailLevel     = level;
  }

// getter
public:
  BOOL getIncludeInstanceIndex()
  {
    return config.bIncludeInstanceIndex;
  }

public:
  BOOL getSingleCounterPerAdd()
  {
    return config.bSingleCounterPerAdd ;
  }

public:
  BOOL getSingleCounterPerDialog()
  {
    return config.bSingleCounterPerDialog;
  }

public:
  BOOL setLocalCountersOnly()
  {
    return config.bLocalCountersOnly;
  }

public:
  BOOL getWildCardInstances()
  {
    return config.bWildCardInstances;
  }

public:
  BOOL getHideDetailBox()
  {
    return config.bHideDetailBox;
  }

public:
  BOOL getInitializePath()
  {
    return config.bInitializePath;
  }

public:
  BOOL getDisableMachineSelection()
  {
    return config.bDisableMachineSelection;
  }

public:
  BOOL getIncludeCostlyObjects()
  {
    return config.bIncludeCostlyObjects;
  }

public:
  BOOL getShowObjectBrowser()
  {
    return config.bShowObjectBrowser;
  }

public:
  BOOL getDefaultDetailLevel()
  {
    return config.dwDefaultDetailLevel;
  }

};

}
