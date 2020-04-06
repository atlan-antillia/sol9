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
 *  ExcelWorkBooks.h
 *
 *****************************************************************************/

//2010/05/05

#pragma once

#include <sol/office/ExcelWorkBook.h>

namespace SOL {

class ExcelWorkBooks :public Object {

private:
  Excel::WorkbooksPtr workBooks;

public:
  ExcelWorkBooks(Excel::WorkbooksPtr books)
    :workBooks(books)
  {
  }

public:
  ~ExcelWorkBooks()
  {
    workBooks = NULL;
  }

public:    

  Excel::_ApplicationPtr getApplication ( )
  {
    return workBooks->GetApplication ( );
  }
    
  enum Excel::XlCreator getCreator ( )
  {
    return workBooks->GetCreator ( );
  }
    
  IDispatchPtr getParent ( )
  {
    return workBooks->GetParent ( );
  }
    
  Excel::_WorkbookPtr add (
          const _variant_t & vtemplate = vtMissing,
          long lcid = 0 )
  {
    return workBooks->Add (
            vtemplate,
            lcid );
  }
    
  HRESULT close (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = workBooks->Close (
            lcid )) ) {
      throw hr;
    } 
    return hr;
  }
    
  long getCount ( )
  {
    return workBooks->GetCount ( );
  }
    
  Excel::_WorkbookPtr GetItem (
          const _variant_t & index )
  {
    return workBooks->GetItem (
            index );
  }
    
  IUnknownPtr getNewEnum ( )
  {
    return workBooks->Get_NewEnum ( );
  }
    
  Excel::_WorkbookPtr open (
          _bstr_t filename,
          const _variant_t & updateLinks = vtMissing,
          const _variant_t & readOnly = vtMissing,
          const _variant_t & format = vtMissing,
          const _variant_t & password = vtMissing,
          const _variant_t & writeResPassword = vtMissing,
          const _variant_t & ignoreReadOnlyRecommended = vtMissing,
          const _variant_t & origin = vtMissing,
          const _variant_t & delimiter = vtMissing,
          const _variant_t & editable = vtMissing,
          const _variant_t & notify = vtMissing,
          const _variant_t & converter = vtMissing,
          const _variant_t & addToMru = vtMissing,
          long lcid = 0 )
  {
    return workBooks->_Open (
            filename,
            updateLinks,
            readOnly,
            format,
            password,
            writeResPassword,
            ignoreReadOnlyRecommended,
            origin,
            delimiter,
            editable,
            notify,
            converter,
            addToMru,
            lcid );
  }
    
  HRESULT __openText (
          _bstr_t filename,
          const _variant_t & origin,
          const _variant_t & startRow,
          const _variant_t & dataType,
          enum Excel::XlTextQualifier textQualifier,
          const _variant_t & consecutiveDelimiter = vtMissing,
          const _variant_t & tab = vtMissing,
          const _variant_t & semicolon = vtMissing,
          const _variant_t & comma = vtMissing,
          const _variant_t & space = vtMissing,
          const _variant_t & other = vtMissing,
          const _variant_t & otherChar = vtMissing,
          const _variant_t & fieldInfo = vtMissing,
          const _variant_t & textVisualLayout = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = workBooks->__OpenText (
            filename,
            origin,
            startRow,
            dataType,
            textQualifier,
            consecutiveDelimiter,
            tab,
            semicolon,
            comma,
            space,
            other,
            otherChar,
            fieldInfo,
            textVisualLayout,
            lcid )) ) {
      throw hr;
    } 
    return hr;
  }
    
  Excel::_WorkbookPtr getDefault (
          const _variant_t & index )
  {
    return workBooks->Get_Default (
            index );
  }
    
  HRESULT _openText (
          _bstr_t filename,
          const _variant_t & origin,
          const _variant_t & startRow,
          const _variant_t & dataType,
          enum Excel::XlTextQualifier textQualifier,
          const _variant_t & consecutiveDelimiter = vtMissing,
          const _variant_t & tab = vtMissing,
          const _variant_t & semicolon = vtMissing,
          const _variant_t & comma = vtMissing,
          const _variant_t & space = vtMissing,
          const _variant_t & other = vtMissing,
          const _variant_t & otherChar = vtMissing,
          const _variant_t & fieldInfo = vtMissing,
           const _variant_t & textVisualLayout = vtMissing,
          const _variant_t & decimalSeparator = vtMissing,
          const _variant_t & thousandsSeparator = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = workBooks->_OpenText (
            filename,
            origin,
            startRow,
            dataType,
            textQualifier,
            consecutiveDelimiter,
            tab,
            semicolon,
            comma,
            space,
            other,
            otherChar,
            fieldInfo,
             textVisualLayout,
            decimalSeparator,
            thousandsSeparator,
            lcid )) ) {
      throw hr;
    } 
    return hr;
  }
    
  Excel::_WorkbookPtr open (
          _bstr_t filename,
          const _variant_t & updateLinks = vtMissing,
          const _variant_t & readOnly = vtMissing,
          const _variant_t & format = vtMissing,
          const _variant_t & password = vtMissing,
          const _variant_t & writeResPassword = vtMissing,
          const _variant_t & ignoreReadOnlyRecommended = vtMissing,
          const _variant_t & origin = vtMissing,
          const _variant_t & delimiter = vtMissing,
          const _variant_t & editable = vtMissing,
          const _variant_t & notify = vtMissing,
          const _variant_t & converter = vtMissing,
          const _variant_t & addToMru = vtMissing,
          const _variant_t & local = vtMissing,
          const _variant_t & corruptLoad = vtMissing,
          long lcid = 0 )
  {
    return workBooks->Open (
            filename,
            updateLinks,
            readOnly,
            format,
            password,
            writeResPassword,
            ignoreReadOnlyRecommended,
            origin,
            delimiter,
            editable,
            notify,
            converter,
            addToMru,
            local,
            corruptLoad,
            lcid );
  }
    
  HRESULT openText (
          _bstr_t filename,
          const _variant_t & origin,
          const _variant_t & startRow,
          const _variant_t & dataType,
          enum Excel::XlTextQualifier textQualifier,
          const _variant_t & consecutiveDelimiter = vtMissing,
          const _variant_t & tab = vtMissing,
          const _variant_t & semicolon = vtMissing,
          const _variant_t & comma = vtMissing,
          const _variant_t & space = vtMissing,
          const _variant_t & other = vtMissing,
          const _variant_t & otherChar = vtMissing,
          const _variant_t & fieldInfo = vtMissing,
          const _variant_t & textVisualLayout = vtMissing,
          const _variant_t & decimalSeparator = vtMissing,
          const _variant_t & thousandsSeparator = vtMissing,
          const _variant_t & trailingMinusNumbers = vtMissing,
          const _variant_t & local = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = workBooks->OpenText (
            filename,
            origin,
            startRow,
            dataType,
            textQualifier,
            consecutiveDelimiter,
            tab,
            semicolon,
            comma,
            space,
            other,
            otherChar,
            fieldInfo,
            textVisualLayout,
            decimalSeparator,
            thousandsSeparator,
            trailingMinusNumbers,
            local,
            lcid )) ) {
      throw hr;
    } 
    return hr;
  }
    
  Excel::_WorkbookPtr openDatabase (
          _bstr_t filename,
          const _variant_t & commandText = vtMissing,
          const _variant_t & commandType = vtMissing,
          const _variant_t & backgroundQuery = vtMissing,
          const _variant_t & importDataAs = vtMissing )
  {
    return workBooks->OpenDatabase (
            filename,
            commandText,
            commandType,
            backgroundQuery,
            importDataAs );
  }
    
  HRESULT checkOut (
          _bstr_t filename )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = workBooks->CheckOut (
            filename )) ) {
      throw hr;
    } 
    return hr;
  }
    
  VARIANT_BOOL canCheckOut (
          _bstr_t filename )
  {
    return workBooks->CanCheckOut (
            filename );
  }
    
  Excel::_WorkbookPtr _openXML (
          _bstr_t filename,
          const _variant_t & stylesheets = vtMissing )
  {
    return workBooks->_OpenXML (
            filename,
            stylesheets );
  }
    
  Excel::_WorkbookPtr openXML (
          _bstr_t filename,
          const _variant_t & stylesheets = vtMissing,
          const _variant_t & loadOption = vtMissing )
  {
    return workBooks->OpenXML (
            filename,
            stylesheets,
            loadOption );
  }
};

}
