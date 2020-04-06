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
 *  ShellItem.h
 *
 *****************************************************************************/


// 2012/10/30
// This class is for IShellItem and IShellItem2 interfaces.

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>

namespace SOL {

class NameSpaceTreeControlEvents: public INameSpaceTreeControlEvents {
    
private:
  HWND hwndEventListener;

public:
  /**
   * Constructor
   */
  NameSpaceTreeControlEvents()
  {
  }

public:
  virtual ~NameSpaceTreeControlEvents()
  {
  }

public:
  ULONG STDMETHODCALLTYPE AddRef()
  {
    return 1;
  }

public:
  ULONG STDMETHODCALLTYPE Release()
  {
    return 1;
  }

public:
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
      /* [in */REFIID riid, 
      /* [out */void** ppv)
  {
    if(riid == IID_IUnknown || 
      riid == __uuidof(INameSpaceTreeControlEvents)) {
      *ppv = static_cast<INameSpaceTreeControlEvents *>(this);
    } else {
      return E_NOINTERFACE;
    }  
    return S_OK;
  }

public:
  virtual HRESULT STDMETHODCALLTYPE OnItemClick( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCEHITTEST nstceHitTest,
            /* [in] */ NSTCECLICKTYPE nstceClickType)
  {
    HRESULT hr = S_OK;
    return hr;
  }

public:
  virtual HRESULT STDMETHODCALLTYPE OnPropertyItemCommit( 
            /* [in] */  IShellItem *psi)
  {
    return S_FALSE;;
  }

        
public:
  virtual HRESULT STDMETHODCALLTYPE OnItemStateChanging( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCITEMSTATE nstcisMask,
            /* [in] */ NSTCITEMSTATE nstcisState)
  {
    return S_OK;
  }
        
  virtual HRESULT STDMETHODCALLTYPE OnItemStateChanged( 
            /* [in] */ IShellItem *psi,
            /* [in] */ NSTCITEMSTATE nstcisMask,
            /* [in] */ NSTCITEMSTATE nstcisState)
  {
    return S_OK;
  }
        
  virtual HRESULT STDMETHODCALLTYPE OnSelectionChanged( 
            /* [in] */ IShellItemArray *psiaSelection)
  {
    return S_OK;
  }
        
  virtual HRESULT STDMETHODCALLTYPE OnKeyboardInput( 
            /* [in] */ UINT uMsg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam)
  {
    return S_FALSE;  
  }
        

  virtual HRESULT STDMETHODCALLTYPE OnBeforeExpand( 
            /* [in] */ IShellItem *psi)
  {
    return S_OK;
  }
        
  virtual HRESULT STDMETHODCALLTYPE OnAfterExpand( 
            /* [in] */ IShellItem *psi)
  {
    return S_OK;
  }
        
  virtual HRESULT STDMETHODCALLTYPE OnBeginLabelEdit( 
            /* [in] */ IShellItem *psi)
  {
    return S_OK;
  }
        
  virtual HRESULT STDMETHODCALLTYPE OnEndLabelEdit( 
            /* [in] */ IShellItem *psi) 
  {
    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE OnGetToolTip( 
            /* [in] */ IShellItem *psi,
            /* [out] */ LPWSTR pszTip,
            /* [in] */ int cchTip)
  {
    return E_NOTIMPL;
  }
        

  virtual HRESULT STDMETHODCALLTYPE OnBeforeItemDelete( 
            /* [in] */ IShellItem *psi)
  {
    return E_NOTIMPL;
  }
        

  virtual HRESULT STDMETHODCALLTYPE OnItemAdded( 
            /* [in] */ IShellItem *psi,
            /* [in] */ BOOL fIsRoot)
  {
    return E_NOTIMPL;
  }
        

  virtual HRESULT STDMETHODCALLTYPE OnItemDeleted( 
            /* [in] */ IShellItem *psi,
            /* [in] */ BOOL fIsRoot)
  {
    return E_NOTIMPL;
  }
        

  virtual HRESULT STDMETHODCALLTYPE OnBeforeContextMenu( 
            /* [in] */ IShellItem *psi,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    *ppv = NULL;
    return E_NOTIMPL;
  }        

  virtual HRESULT STDMETHODCALLTYPE OnAfterContextMenu( 
            /* [in] */ IShellItem *psi,
            /* [in] */ IContextMenu *pcmIn,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppv)
  {
    *ppv = NULL;
    return E_NOTIMPL;
  }
        

  virtual HRESULT STDMETHODCALLTYPE OnBeforeStateImageChange( 
            /* [in] */ IShellItem *psi)
  {
    return S_OK;
  }

        

  virtual HRESULT STDMETHODCALLTYPE OnGetDefaultIconIndex( 
            /* [in] */ IShellItem *psi,
            /* [out] */ int *piDefaultIcon,
            /* [out] */ int *piOpenIcon)
  {
    return E_NOTIMPL;
  }
        
};
 
}
   
