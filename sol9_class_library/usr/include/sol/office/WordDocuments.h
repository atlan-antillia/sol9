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
 *  WordDocuments.h
 *
 *****************************************************************************/

//2010/05/05

#pragma once

#include <sol/office/WordDocument.h>

namespace SOL {

class WordDocuments :public Object {
private:
  Word::DocumentsPtr documents;

public:
  WordDocuments(Word::DocumentsPtr docs)
  :documents(docs)
  {
  }

public:
  ~WordDocuments()
  {
    documents = NULL;
  }

public:

  IUnknownPtr getNewEnum ( )
  {
    return documents->Get_NewEnum ( );
  }

  long getCount ( )
  {
    return documents->GetCount ( );
  }
    
  Word::_ApplicationPtr getApplication ( )
  {
    return documents->GetApplication ( );
  }
    
  long getCreator ( )
  {
    return documents->GetCreator ( );
  }
    
  IDispatchPtr getParent ( )
  {
    return documents->GetParent ( );
  }
    
  Word::_DocumentPtr item (
          VARIANT * index )
  {
    return documents->Item (
            index );
  }
    
  HRESULT close (
          VARIANT * saveChanges = &vtMissing,
          VARIANT * originalFormat = &vtMissing,
          VARIANT * routeDocument = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED (hr = documents->Close (
            saveChanges,
            originalFormat,
            routeDocument )) ) {
      throw hr;
    }
    return hr;
  }
    
  Word::_DocumentPtr addOld (
          VARIANT * vtemplate = &vtMissing,
          VARIANT * newTemplate = &vtMissing )
  {
    return documents->AddOld (
            vtemplate,
            newTemplate );
  }
    
  Word::_DocumentPtr openOld (
          VARIANT * fileName,
          VARIANT * confirmConversions = &vtMissing,
          VARIANT * readOnly = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * passwordDocument = &vtMissing,
          VARIANT * passwordTemplate = &vtMissing,
          VARIANT * revert = &vtMissing,
          VARIANT * writePasswordDocument = &vtMissing,
          VARIANT * writePasswordTemplate = &vtMissing,
          VARIANT * format = &vtMissing )
  {
    return documents->OpenOld (
            fileName,
            confirmConversions,
            readOnly,
            addToRecentFiles,
            passwordDocument,
            passwordTemplate,
            revert,
            writePasswordDocument,
            writePasswordTemplate,
            format );
  }
    
  HRESULT save (
          VARIANT * noPrompt = &vtMissing,
          VARIANT * originalFormat = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED (hr = documents->Save (
            noPrompt,
            originalFormat )) ) {
      throw hr;
    }
    return hr;
  }
    
  Word::_DocumentPtr add (
          VARIANT * vtemplate = &vtMissing,
          VARIANT * newTemplate = &vtMissing,
          VARIANT * documentType = &vtMissing,
          VARIANT * visible = &vtMissing )
  {
    return documents->Add (
            vtemplate,
            newTemplate,
            documentType,
            visible );
  }
    
  Word::_DocumentPtr open2000 (
          VARIANT * fileName,
           VARIANT * confirmConversions = &vtMissing,
          VARIANT * readOnly = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * passwordDocument = &vtMissing,
          VARIANT * passwordTemplate = &vtMissing,
          VARIANT * revert = &vtMissing,
          VARIANT * writePasswordDocument = &vtMissing,
          VARIANT * writePasswordTemplate = &vtMissing,
          VARIANT * format = &vtMissing,
          VARIANT * encoding = &vtMissing,
          VARIANT * visible = &vtMissing )
  {
    return documents->Open2000 (
            fileName,
             confirmConversions,
            readOnly,
            addToRecentFiles,
            passwordDocument,
            passwordTemplate,
            revert,
            writePasswordDocument,
            writePasswordTemplate,
            format,
            encoding,
            visible );
  }
    
  HRESULT checkOut (
          _bstr_t fileName )
  {
    HRESULT hr = S_OK;
    if (FAILED (hr = documents->CheckOut (
            fileName )) ) {
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL canCheckOut (
          _bstr_t fileName )
  {
    return documents->CanCheckOut (
            fileName );
  }
    
  Word::_DocumentPtr open2002 (
          VARIANT * fileName,
          VARIANT * confirmConversions = &vtMissing,
          VARIANT * readOnly = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * passwordDocument = &vtMissing,
          VARIANT * passwordTemplate = &vtMissing,
          VARIANT * revert = &vtMissing,
          VARIANT * writePasswordDocument = &vtMissing,
          VARIANT * writePasswordTemplate = &vtMissing,
          VARIANT * format = &vtMissing,
          VARIANT * encoding = &vtMissing,
          VARIANT * visible = &vtMissing,
          VARIANT * openAndRepair = &vtMissing,
          VARIANT * documentDirection = &vtMissing,
          VARIANT * noEncodingDialog = &vtMissing )
  {
    return documents->Open2002 (
            fileName,
            confirmConversions,
            readOnly,
            addToRecentFiles,
            passwordDocument,
            passwordTemplate,
            revert,
            writePasswordDocument,
            writePasswordTemplate,
            format,
            encoding,
            visible,
            openAndRepair,
            documentDirection,
            noEncodingDialog );
  }
    

  Word::_DocumentPtr open (
          VARIANT * fileName,
          VARIANT * confirmConversions = &vtMissing,
          VARIANT * readOnly = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * passwordDocument = &vtMissing,
          VARIANT * passwordTemplate = &vtMissing,
          VARIANT * revert = &vtMissing,
          VARIANT * writePasswordDocument = &vtMissing,
          VARIANT * writePasswordTemplate = &vtMissing,
          VARIANT * format = &vtMissing,
          VARIANT * encoding = &vtMissing,
          VARIANT * visible = &vtMissing,
          VARIANT * openAndRepair = &vtMissing,
          VARIANT * documentDirection = &vtMissing,
          VARIANT * noEncodingDialog = &vtMissing,
          VARIANT * xmlTransform = &vtMissing )
  {
    return documents->Open (
            fileName,
            confirmConversions,
            readOnly,
            addToRecentFiles,
            passwordDocument,
            passwordTemplate,
            revert,
            writePasswordDocument,
            writePasswordTemplate,
            format,
            encoding,
            visible,
            openAndRepair,
            documentDirection,
            noEncodingDialog,
            xmlTransform );
  }
    
  Word::_DocumentPtr OpenNoRepairDialog (
          VARIANT * fileName,
          VARIANT * confirmConversions = &vtMissing,
          VARIANT * readOnly = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * passwordDocument = &vtMissing,
          VARIANT * passwordTemplate = &vtMissing,
          VARIANT * revert = &vtMissing,
          VARIANT * writePasswordDocument = &vtMissing,
          VARIANT * writePasswordTemplate = &vtMissing,
          VARIANT * format = &vtMissing,
          VARIANT * encoding = &vtMissing,
          VARIANT * visible = &vtMissing,
          VARIANT * openAndRepair = &vtMissing,
          VARIANT * documentDirection = &vtMissing,
          VARIANT * noEncodingDialog = &vtMissing,
          VARIANT * xmlTransform = &vtMissing )
  {
    return documents->OpenNoRepairDialog (
            fileName,
            confirmConversions,
            readOnly,
            addToRecentFiles,
            passwordDocument,
            passwordTemplate,
            revert,
            writePasswordDocument,
            writePasswordTemplate,
            format,
            encoding,
            visible,
            openAndRepair,
            documentDirection,
            noEncodingDialog,
            xmlTransform );
  }
    
  Word::_DocumentPtr addBlogDocument (
          _bstr_t providerID,
          _bstr_t postURL,
          _bstr_t blogName,
          _bstr_t postID )
  {
    return documents->AddBlogDocument (
            providerID,
            postURL,
            blogName,
            postID );
  }

};

}
