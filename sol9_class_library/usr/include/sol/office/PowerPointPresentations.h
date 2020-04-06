/******************************************************************************
 *
 * Copyright (c) 2010 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  PowerPointPresentations.h
 *
 *****************************************************************************/

//2010/05/05

#pragma once

#include <sol/office/PowerPointPresentation.h>

namespace SOL {

class PowerPointPresentations :public Object {


private:
  PowerPoint::PresentationsPtr presentations;


public:
  PowerPointPresentations(PowerPoint::PresentationsPtr pres)
  :presentations(pres) 
  {

  }

public:
  ~PowerPointPresentations() 
  {
    presentations = NULL;
  }


public:
    
  PowerPoint::_ApplicationPtr getApplication ( )
  {
    return presentations->GetApplication ( );
  }
    
  IDispatchPtr getParent ( )
  {
    return presentations->GetParent ( );
  }
    
  PowerPoint::_PresentationPtr item (
          const _variant_t & index )
  {
    return presentations->Item (
            index );
  }
    
  PowerPoint::_PresentationPtr add (
          enum Office::MsoTriState withWindow )
  {
    return presentations->Add (
            withWindow );
  }
    
  PowerPoint::_PresentationPtr OpenOld (
          _bstr_t fileName,
          enum Office::MsoTriState readOnly,
          enum Office::MsoTriState untitled,
          enum Office::MsoTriState withWindow )
  {
    return presentations->OpenOld (
            fileName,
            readOnly,
            untitled,
            withWindow );
  }
    
  PowerPoint::_PresentationPtr Open (
          _bstr_t fileName,
          enum Office::MsoTriState readOnly,
          enum Office::MsoTriState untitled,
          enum Office::MsoTriState withWindow )
  {
    return presentations->Open (
            fileName,
            readOnly,
            untitled,
            withWindow );

  }
    
  HRESULT checkOut (
          _bstr_t fileName )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = presentations->CheckOut (
            fileName )) ) {
      throw hr;
    }
    return hr;
  }

  VARIANT_BOOL canCheckOut (
          _bstr_t fileName )
  {
    return presentations->CanCheckOut (
            fileName );
  }
    
  PowerPoint::_PresentationPtr open2007 (
          _bstr_t fileName,
          enum Office::MsoTriState readOnly,
          enum Office::MsoTriState untitled,
          enum Office::MsoTriState withWindow,
          enum Office::MsoTriState openAndRepair )
  {
    return presentations->Open2007 (
            fileName,
            readOnly,
            untitled,
            withWindow,
            openAndRepair );
  }

};

}
