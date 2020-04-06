/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DropTarget.h
 *
 *****************************************************************************/

// SOL9 2008/12/11

#pragma once

#include <sol\Object.h>


//SOL9 specific user-defined message,which can be sent
// to the window of m_hReceiver, this will be a window
// of user's application.
// If m_hReciever is NULL, this message will be sent the drop target 
// of m_hTarget window.

#define WM_SOL_DROPFILES  (WM_USER+2011)

namespace SOL {

/**
 * class DropTarget.
 * Implementation of the IDropTarget interface
 */
class CDropTarget :public IDropTarget {

// Member variables
private:
  LONG  m_lRefCount;
  HWND  m_hTarget;
  HWND  m_hReceiver;
  bool    m_fAllowDrop;
  IDataObject *m_pDataObject;


public:
  // IUnknown implementation
  HRESULT __stdcall QueryInterface (REFIID iid, void ** ppvObject)
  {
    if(iid == IID_IDropTarget || iid == IID_IUnknown) {
      AddRef();
      *ppvObject = this;
  
      return S_OK;

    } else {
      *ppvObject = 0;
      return E_NOINTERFACE;
    }
  }

public:
  ULONG  __stdcall AddRef (void) 
  {
    return InterlockedIncrement(&m_lRefCount);
  }

public:
  ULONG  __stdcall Release (void) 
  {
    LONG count = InterlockedDecrement(&m_lRefCount);
    
    if(count == 0) {
      delete this;
      return 0;
    } else {
      return count;
    }
  }

public:
  // IDropTarget implementation
  HRESULT __stdcall DragEnter (IDataObject * pDataObject, DWORD grfKeyState, 
    POINTL pt, DWORD * pdwEffect)
  {
    // Check the dataobject
    m_fAllowDrop = QueryDataObject(pDataObject);
  
    if(m_fAllowDrop) {
      // Get the dropeffect based on keyboard state
      *pdwEffect = DropEffect(grfKeyState, pt, *pdwEffect);

      SetFocus(m_hTarget);

    } else {
      *pdwEffect = DROPEFFECT_NONE;
    }

    return S_OK;
  }


public:
  HRESULT __stdcall DragOver (DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
  {
    if(m_fAllowDrop) {
      *pdwEffect = DropEffect(grfKeyState, pt, *pdwEffect);

    } else {
      *pdwEffect = DROPEFFECT_NONE;
    }

    return S_OK;
  }

public:
  HRESULT __stdcall DragLeave (void)
  {
    m_fAllowDrop = false;

    return S_OK;
  }

public:
  HRESULT __stdcall Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
  {

    if(m_fAllowDrop) {
      DropData(m_hTarget, pDataObject);

      *pdwEffect = DropEffect(grfKeyState, pt, *pdwEffect);

    } else {
      *pdwEffect = DROPEFFECT_NONE;
    }
    return S_OK;
  }

//
// 
//
public:
  // Constructor
  CDropTarget(HWND hwnd) 
  {
    m_lRefCount  = 1;
    m_hTarget       = hwnd;
    m_hReceiver  = NULL;

    m_fAllowDrop = false;
    m_pDataObject = NULL;
  }

public:
  // Constructor
  CDropTarget() 
  {
    m_lRefCount  = 1;
    m_hTarget       = NULL;
    m_hReceiver  = NULL;
    m_fAllowDrop = false;
    m_pDataObject = NULL;
  }

public:
  //Destructor
  ~CDropTarget() 
  {
    //2009/11/01
    if (m_hTarget && IsWindow(m_hTarget)) {
      RevokeDragDrop(m_hTarget);
    
      // Remove the strong lock
      CoLockObjectExternal(this, FALSE, TRUE);
      Release();
    }
    // release our own reference
    m_hTarget = NULL;
  }

public:
  void setTarget(HWND hwnd) {
    if (hwnd) {
      DragAcceptFiles(hwnd, TRUE);
      m_hTarget = hwnd;
      RegisterDragDrop(hwnd, this);
      CoLockObjectExternal(this, TRUE, FALSE);
    }
  }
public:
  void setEventReceiver(HWND hwnd) {
    //2009/11/01
    if (hwnd) {
      DragAcceptFiles(hwnd, TRUE);
    }
    m_hReceiver = hwnd;
  }

public:
  //
  bool acceptDragFiles() {
    bool rc = false;
    LONG lExStyle = GetWindowLong(m_hTarget, GWL_EXSTYLE );
    //  WS_EX_TOOLWINDOW??
    if (lExStyle & WS_EX_ACCEPTFILES) {
      rc = true;
    }
    return rc;
  }

private:

  // Internal helper function
  DWORD DropEffect(DWORD grfKeyState, POINTL pt, DWORD dwAllowed)
  {
    DWORD dwEffect = 0;

    if(grfKeyState & MK_CONTROL) {
      dwEffect = dwAllowed & DROPEFFECT_COPY;
    }
    else if(grfKeyState & MK_SHIFT) {
      dwEffect = dwAllowed & DROPEFFECT_MOVE;
    }
  
    if(dwEffect == 0) {
      if(dwAllowed & DROPEFFECT_COPY) {
        dwEffect = DROPEFFECT_COPY;
      }
      if(dwAllowed & DROPEFFECT_MOVE) {
        dwEffect = DROPEFFECT_MOVE;
      }
    }
  
    return dwEffect;
  }


private:
  //
  // Dropping from an Explorer. We accept CF_HDROP only
  //
  bool  QueryDataObject(IDataObject *pDataObject)
  {

    FORMATETC fmtetc = { CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

    // does the data object support CF_HDROP using a HGLOBAL?
    return pDataObject->QueryGetData(&fmtetc) == S_OK ? true : false;
  }



private:
  //
  // After getting a handle for type CF_HDROP and PostMessage to
  // 
  void DropData(HWND hwnd, IDataObject *pDataObject)
  {
    //Construct a FORMATETC object
    FORMATETC fmtetc = { CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

    STGMEDIUM stgmed;

    // If the dataobject contains any HDROP stored as a HGLOBAL
    if(pDataObject->QueryGetData(&fmtetc) == S_OK)
    {

      // Found the data!
      if(pDataObject->GetData(&fmtetc, &stgmed) == S_OK)
      {        
        //Check copy key
        BOOL removeSourceFiles = FALSE;
        short x =GetKeyState(VK_CONTROL);
        if (x <0) {
          //If CONTROL key is being pressed, then do COPY
          removeSourceFiles = FALSE;
        } else {
          //MOVE
          //If CONTROL key is not being pressed, ignore the shif-key and, do move.
          removeSourceFiles = TRUE;
        }

        SetForegroundWindow(m_hTarget);
        //Lock the stgmed.hGlobal, and get HDROP object
        HDROP hdrop = (HDROP)GlobalLock(stgmed.hGlobal);
        HWND hTarget = m_hTarget;
        if (m_hReceiver) {
          hTarget = m_hReceiver;
        }

        //SendMessage SOL specific user-defined Windows message (WM_SOL_DROPFILES) to the hTarget window.
        SendMessage(hTarget, WM_SOL_DROPFILES,
            (WPARAM)hdrop, 
            (LPARAM)removeSourceFiles);

        //Now, we can GlobalUnlock the HDROP object
        GlobalUnlock(hdrop);

        // Release the data
        ReleaseStgMedium(&stgmed);
      }
    }
  }

};


}
