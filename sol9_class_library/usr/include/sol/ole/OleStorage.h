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
 *  OleStorage.h
 *
 *****************************************************************************/

/**
This is a simple Win32 C++ class (not MFC and WTL) to embed a IE browser control 
(an OLE object) into your own window.
Basically, this is based on a C++ example written by Chris Becke.
For C version, see http://www.codeproject.com/com/cwebpage.asp.
*/


// SOL9
// 2008/08/10

#pragma once

#include <sol\Object.h>
#include <exdisp.h>


namespace SOL {

/**
 * COleStorage
 */
class COleStorage: public IStorage
{
// IUnknown 
public:

  STDMETHODIMP QueryInterface(REFIID riid,void ** ppvObject){
    return E_NOTIMPL;
  }

  STDMETHODIMP_(ULONG) AddRef(void) {
    return 1;
  }

  STDMETHODIMP_(ULONG) Release(void) {
    return 1;
  }


  // IStorage
  STDMETHODIMP CreateStream(const WCHAR * pwcsName,DWORD grfMode,DWORD reserved1,DWORD reserved2,IStream ** ppstm){
    return E_NOTIMPL;
  }

  STDMETHODIMP OpenStream(const WCHAR * pwcsName,void * reserved1,DWORD grfMode,DWORD reserved2,IStream ** ppstm) {
    return E_NOTIMPL;
  }

  STDMETHODIMP CreateStorage(const WCHAR * pwcsName,DWORD grfMode,DWORD reserved1,DWORD reserved2,IStorage ** ppstg) {
    return E_NOTIMPL;
  }

  STDMETHODIMP OpenStorage(const WCHAR * pwcsName,IStorage * pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage ** ppstg){
    return E_NOTIMPL;
  }

  STDMETHODIMP CopyTo(DWORD ciidExclude,IID const * rgiidExclude,SNB snbExclude,IStorage * pstgDest){
    return E_NOTIMPL;
  }

  STDMETHODIMP MoveElementTo(const OLECHAR * pwcsName,IStorage * pstgDest,const OLECHAR* pwcsNewName,DWORD grfFlags){
    return E_NOTIMPL;
  }

  STDMETHODIMP Commit(DWORD grfCommitFlags){
    return E_NOTIMPL;
  }

  STDMETHODIMP Revert(void) {
    return E_NOTIMPL;
  }

  STDMETHODIMP EnumElements(DWORD reserved1,void * reserved2,DWORD reserved3,IEnumSTATSTG ** ppenum){
    return E_NOTIMPL;
  }

  STDMETHODIMP DestroyElement(const OLECHAR * pwcsName){
    return E_NOTIMPL;
  }

  STDMETHODIMP RenameElement(const WCHAR * pwcsOldName,const WCHAR * pwcsNewName){
    return E_NOTIMPL;
  }

  STDMETHODIMP SetElementTimes(const WCHAR * pwcsName,FILETIME const * pctime,FILETIME const * patime,FILETIME const * pmtime){
    return E_NOTIMPL;
  }

  STDMETHODIMP SetClass(REFCLSID clsid) {
    return S_OK;
  }

  STDMETHODIMP SetStateBits(DWORD grfStateBits,DWORD grfMask)
  {
    return E_NOTIMPL;
  }

  STDMETHODIMP Stat(STATSTG * pstatstg,DWORD grfStatFlag)
  {
    return E_NOTIMPL;
  }  
};

}
