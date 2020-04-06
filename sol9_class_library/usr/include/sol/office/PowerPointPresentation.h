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
 *  PowerPointPresentation.h
 *
 *****************************************************************************/

//2010/04/01
//2010/05/05

#pragma once

#include <sol/office/PowerPointApplet.h>

namespace SOL {

class PowerPointPresentation :public Object {
private:
  PowerPoint::_PresentationPtr presentation;

public:
  PowerPointPresentation(PowerPoint::_PresentationPtr presen)
  :presentation(presen)
  {

  }

public:
  ~PowerPointPresentation()
  {
    presentation = NULL;
  }
/*
public:
  HRESULT close()
  {
    HRESULT hr = presentation->Close();
    presentation = NULL;
    return hr;
  }

public:
  HRESULT save()
  {
    return presentation->Save();
  }
*/
public:    
/*
  HRESULT saveAs (
        _bstr_t fileName,
    enum PowerPoint::PpSaveAsFileType fileFormat,
    enum Office::MsoTriState embedTrueTypeFonts=Office::msoTrue)
  {
    
    return presentation->SaveAs (
          fileName,
          fileFormat,
          embedTrueTypeFonts );

  }

public:
   HRESULT printOut(
        int from,
        int to,
        _bstr_t printToFile,
        int copies,
        enum Office::MsoTriState collate)
   {
     return presentation->PrintOut (
           from,
          to,
          printToFile,
          copies,
          collate );
   }
*/

public:    
  PowerPoint::_ApplicationPtr getApplication ( )
  {
    return presentation->GetApplication ( );
  }    

  IDispatchPtr getParent ( )
  {
    return presentation->GetParent ( );
  }    
    
  PowerPoint::_MasterPtr getSlideMaster ( )
  {
    return presentation->GetSlideMaster ( );
  }    
    
  PowerPoint::_MasterPtr getTitleMaster ( )
  {
    return presentation->GetTitleMaster ( );
  }    
    
  enum Office::MsoTriState getHasTitleMaster ( )
  {
    return presentation->GetHasTitleMaster ( );
  }    
    
  PowerPoint::_MasterPtr addTitleMaster ( )
  {
    return presentation->AddTitleMaster ( );
  }    
    
  HRESULT applyTemplate (
          _bstr_t fileName )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->ApplyTemplate (
            fileName ))) {
      throw hr;
    }
    return hr;
  }    
    
  _bstr_t getTemplateName ( )
  {
    return presentation->GetTemplateName ( );
  }    
    
  PowerPoint::_MasterPtr getNotesMaster ( )
  {
    return presentation->GetNotesMaster ( );
  }    
    
  PowerPoint::_MasterPtr getHandoutMaster ( )
  {
    return presentation->GetHandoutMaster ( );
  }    
    
  PowerPoint::SlidesPtr getSlides ( )
  {
    return presentation->GetSlides ( );
  }    
    
  PowerPoint::PageSetupPtr getPageSetup ( )
  {
    return presentation->GetPageSetup ( );
  }    
    
  PowerPoint::ColorSchemesPtr getColorSchemes ( )
  {
    return presentation->GetColorSchemes ( );
  }    
    
  PowerPoint::ExtraColorsPtr getExtraColors ( )
  {
    return presentation->GetExtraColors ( );
  }    
    
  PowerPoint::SlideShowSettingsPtr getSlideShowSettings ( )
  {
    return presentation->GetSlideShowSettings ( );
  }    
    
  PowerPoint::FontsPtr getFonts ( )
  {
    return presentation->GetFonts ( );
  }    
    
  PowerPoint::DocumentWindowsPtr getWindows ( )
  {
    return presentation->GetWindows ( );
  }    
    
  PowerPoint::TagsPtr getTags ( )
  {
    return presentation->GetTags ( );
  }    
    
  PowerPoint::ShapePtr getDefaultShape ( )
  {
    return presentation->GetDefaultShape ( );
  }    
    
  IDispatchPtr getBuiltInDocumentProperties ( )
  {
    return presentation->GetBuiltInDocumentProperties ( );
  }    
    
  IDispatchPtr getCustomDocumentProperties ( )
  {
    return presentation->GetCustomDocumentProperties ( );
  }    
    
  VBIDE::_VBProjectPtr getVBProject ( )
  {
    return presentation->GetVBProject ( );
  }    

      enum Office::MsoTriState getReadOnly ( )
  {
    return presentation->GetReadOnly ( );
  }    
    
  _bstr_t getFullName ( )
  {
    return presentation->GetFullName ( );
  }    
    
  _bstr_t getName ( )
  {
    return presentation->GetName ( );
  }    
    
  _bstr_t getPath ( )
  {
    return presentation->GetPath ( );
  }    
    
  enum Office::MsoTriState getSaved ( )
  {
    return presentation->GetSaved ( );
  }    
    
  void putSaved (
          enum Office::MsoTriState Saved )
  {
    presentation->PutSaved (
            Saved );
  }    
    
  enum PowerPoint::PpDirection getLayoutDirection ( )
  {
    return presentation->GetLayoutDirection ( );
  }    


      
  void putLayoutDirection (
            enum PowerPoint::PpDirection layoutDirection )
  {
    presentation->PutLayoutDirection (
            layoutDirection );
  }    
    
  PowerPoint::DocumentWindowPtr newWindow ( )
  {
    return presentation->NewWindow ( );
  }    
    
  HRESULT followHyperlink (
          _bstr_t address,
          _bstr_t subAddress,
          VARIANT_BOOL newWindow,
          VARIANT_BOOL addHistory,
          _bstr_t extraInfo,
          enum Office::MsoExtraInfoMethod method,
          _bstr_t headerInfo )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->FollowHyperlink (
            address,
            subAddress,
            newWindow,
            addHistory,
            extraInfo,
            method,
            headerInfo ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT addToFavorites ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->AddToFavorites ( ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT unused ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->Unused ( ))) {
      throw hr;
    }
    return hr;
  }    
    
  PowerPoint::PrintOptionsPtr getPrintOptions ( )
  {
    return presentation->GetPrintOptions ( );
  }    
    
  HRESULT printOut (
          int from,
          int to,
          _bstr_t printToFile,
          int copies,
          enum Office::MsoTriState collate )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->PrintOut (
            from,
            to,
            printToFile,
            copies,
            collate ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT save ( )
  {
    return presentation->Save ( );
  }    
    
/*
enum PpSaveAsFileType
{
    ppSaveAsPresentation = 1,
    ppSaveAsPowerPoint7 = 2,
    ppSaveAsPowerPoint4 = 3,
    ppSaveAsPowerPoint3 = 4,
    ppSaveAsTemplate = 5,
    ppSaveAsRTF = 6,
    ppSaveAsShow = 7,
    ppSaveAsAddIn = 8,
    ppSaveAsPowerPoint4FarEast = 10,
    ppSaveAsDefault = 11,
    ppSaveAsHTML = 12,
    ppSaveAsHTMLv3 = 13,
    ppSaveAsHTMLDual = 14,
    ppSaveAsMetaFile = 15,
    ppSaveAsGIF = 16,
    ppSaveAsJPG = 17,
    ppSaveAsPNG = 18,
    ppSaveAsBMP = 19,
    ppSaveAsWebArchive = 20,
    ppSaveAsTIF = 21,
    ppSaveAsPresForReview = 22,
    ppSaveAsEMF = 23,
    ppSaveAsOpenXMLPresentation = 24,
    ppSaveAsOpenXMLPresentationMacroEnabled = 25,
    ppSaveAsOpenXMLTemplate = 26,
    ppSaveAsOpenXMLTemplateMacroEnabled = 27,
    ppSaveAsOpenXMLShow = 28,
    ppSaveAsOpenXMLShowMacroEnabled = 29,
    ppSaveAsOpenXMLAddin = 30,
    ppSaveAsOpenXMLTheme = 31,
    ppSaveAsPDF = 32,
    ppSaveAsXPS = 33,
    ppSaveAsXMLPresentation = 34,
    ppSaveAsOpenDocumentPresentation = 35,
    ppSaveAsExternalConverter = 36
};

*/

  HRESULT saveAs (
          _bstr_t fileName,
          enum PowerPoint::PpSaveAsFileType fileFormat,
          enum Office::MsoTriState embedTrueTypeFonts=Office::msoTrue )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->SaveAs (
            fileName,
            fileFormat,
            embedTrueTypeFonts ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT saveCopyAs (
          _bstr_t fileName,
          enum PowerPoint::PpSaveAsFileType fileFormat,
          enum Office::MsoTriState embedTrueTypeFonts )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->SaveCopyAs (
            fileName,
            fileFormat,
            embedTrueTypeFonts ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT doExport (
          _bstr_t path,
          _bstr_t filterName,
          int scaleWidth,
          int scaleHeight )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->Export (
            path,
            filterName,
            scaleWidth,
            scaleHeight ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT close ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->Close ( ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT setUndoText (
          _bstr_t text )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->SetUndoText (
            text ))) {
      throw hr;
    }
    return hr;
  }    
    
  IDispatchPtr getContainer ( )
  {
    return presentation->GetContainer ( );
  }    
    
  enum Office::MsoTriState getDisplayComments ( )
  {
    return presentation->GetDisplayComments ( );
  }    
    
  void putDisplayComments (
          enum Office::MsoTriState displayComments )
  {
    presentation->PutDisplayComments (
            displayComments );
  }    
    
  enum PowerPoint::PpFarEastLineBreakLevel getFarEastLineBreakLevel ( )
  {
    return presentation->GetFarEastLineBreakLevel ( );
  }    
    
  void putFarEastLineBreakLevel (
          enum PowerPoint::PpFarEastLineBreakLevel farEastLineBreakLevel )
  {
    presentation->PutFarEastLineBreakLevel (
            farEastLineBreakLevel );
  }    
    
  _bstr_t getNoLineBreakBefore ( )
  {
    return presentation->GetNoLineBreakBefore ( );
  }    
    
  void putNoLineBreakBefore (
          _bstr_t noLineBreakBefore )
  {
    presentation->PutNoLineBreakBefore (
            noLineBreakBefore );
  }    
    
  _bstr_t getNoLineBreakAfter ( )
  {
    return presentation->GetNoLineBreakAfter ( );
  }    
    
  void putNoLineBreakAfter (
          _bstr_t noLineBreakAfter )
  {
    presentation->PutNoLineBreakAfter (
            noLineBreakAfter );
  }    
    
  HRESULT updateLinks ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->UpdateLinks ( ))) {
      throw hr;
    }
    return hr;
  }    
    
  PowerPoint::SlideShowWindowPtr getSlideShowWindow ( )
  {
    return presentation->GetSlideShowWindow ( );
  }    
    
  enum Office::MsoFarEastLineBreakLanguageID getFarEastLineBreakLanguage ( )
  {
    return presentation->GetFarEastLineBreakLanguage ( );
  }    
    
  void putFarEastLineBreakLanguage (
          enum Office::MsoFarEastLineBreakLanguageID farEastLineBreakLanguage )
  {
    presentation->PutFarEastLineBreakLanguage (
            farEastLineBreakLanguage );
  }    
    
  HRESULT webPagePreview ( )    
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->WebPagePreview ( ))) {
      throw hr;
    }
    return hr;
  }    

  enum Office::MsoLanguageID getDefaultLanguageID ( )
  {
    return presentation->GetDefaultLanguageID ( );
  }    
    
  void putDefaultLanguageID (
          enum Office::MsoLanguageID defaultLanguageID )
  {
    presentation->PutDefaultLanguageID (
            defaultLanguageID );
  }    
    
  Office::_CommandBarsPtr getCommandBars ( )
  {
    return presentation->GetCommandBars ( );
  }    
    
  PowerPoint::PublishObjectsPtr getPublishObjects ( )
  {
    return presentation->GetPublishObjects ( );
  }    
    
  PowerPoint::WebOptionsPtr getWebOptions ( )
  {
    return presentation->GetWebOptions ( );
  }    
    
  Office::HTMLProjectPtr getHTMLProject ( )
  {
    return presentation->GetHTMLProject ( );
  }    
    
  HRESULT reloadAs (
          enum Office::MsoEncoding cp )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->ReloadAs (
            cp ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT makeIntoTemplate (
          enum Office::MsoTriState isDesignTemplate )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->MakeIntoTemplate (
            isDesignTemplate ))) {
      throw hr;
    }
    return hr;
  }    
    
  enum Office::MsoTriState getEnvelopeVisible ( )
  {
    return presentation->GetEnvelopeVisible ( );
  }    
    
  void putEnvelopeVisible (
          enum Office::MsoTriState envelopeVisible )
  {
    presentation->PutEnvelopeVisible (
            envelopeVisible );
  }    

      HRESULT sblt (
          _bstr_t s )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->sblt (
            s ))) {
      throw hr;
    }
    return hr;
  }    

      enum Office::MsoTriState getVBASigned ( )
  {
    return presentation->GetVBASigned ( );
  }    

     enum Office::MsoTriState getSnapToGrid ( )
  {
    return presentation->GetSnapToGrid ( );
  }    
    
  void putSnapToGrid (
          enum Office::MsoTriState snapToGrid )
  {
    presentation->PutSnapToGrid (
            snapToGrid );
  }    
    
  float getGridDistance ( )
  {
    return presentation->GetGridDistance ( );
  }    
    
  void putGridDistance (
          float gridDistance )
  {
    return presentation->PutGridDistance (
            gridDistance );
  }    
    
  PowerPoint::DesignsPtr getDesigns ( )
  {
    return presentation->GetDesigns ( );
  }    
    
  HRESULT merge (
          _bstr_t path )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->Merge (
            path ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT checkIn (
          VARIANT_BOOL saveChanges,
          const _variant_t & comments = vtMissing,
          const _variant_t & makePublic = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr =  presentation->CheckIn (
            saveChanges,
            comments,
            makePublic ))) {
      throw hr;
    }
    return hr;
  }    
    
  VARIANT_BOOL canCheckIn ( )
  {
    return presentation->CanCheckIn ( );
  }    
    
  Office::SignatureSetPtr getSignatures ( )
  {
    return presentation->GetSignatures ( );
  }    
    
  enum Office::MsoTriState getRemovePersonalInformation ( )
  {
    return presentation->GetRemovePersonalInformation ( );
  }    
    
  void putRemovePersonalInformation (
    enum Office::MsoTriState removePersonalInformation )
  {
    presentation->PutRemovePersonalInformation (
      removePersonalInformation );
  }    
    
  HRESULT sendForReview (
          _bstr_t recipients,
          _bstr_t subject,
          VARIANT_BOOL showMessage,
          const _variant_t & includeAttachment = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->SendForReview (
            recipients,
            subject,
            showMessage,
            includeAttachment ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT replyWithChanges (
          VARIANT_BOOL showMessage )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->ReplyWithChanges (
            showMessage ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT endReview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->EndReview ( ))) {
      throw hr;
    }
    return hr;
  }    
    
  enum PowerPoint::PpRevisionInfo getHasRevisionInfo ( )
  {
    return presentation->GetHasRevisionInfo ( );
  }    
    
  HRESULT addBaseline (
          _bstr_t fileName )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->AddBaseline (
            fileName ))) {
      throw hr;
    }
    return hr;
  }    
    
  HRESULT removeBaseline ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->RemoveBaseline ( ))) {
      throw hr;
    }
    return hr;
  }    

      _bstr_t getPasswordEncryptionProvider ( )
  {
    return presentation->GetPasswordEncryptionProvider ( );
  }    
    
  _bstr_t getPasswordEncryptionAlgorithm ( )
  {
    return presentation->GetPasswordEncryptionAlgorithm ( );
  }    
    
  int getPasswordEncryptionKeyLength ( )
  {
    return presentation->GetPasswordEncryptionKeyLength ( );
  }    
    
  VARIANT_BOOL getPasswordEncryptionFileProperties ( )
  {
    return presentation->GetPasswordEncryptionFileProperties ( );
  }    
   
   HRESULT setPasswordEncryptionOptions (
          _bstr_t passwordEncryptionProvider,
          _bstr_t passwordEncryptionAlgorithm,
          int passwordEncryptionKeyLength,
          VARIANT_BOOL passwordEncryptionFileProperties )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->SetPasswordEncryptionOptions (
            passwordEncryptionProvider,
            passwordEncryptionAlgorithm,
            passwordEncryptionKeyLength,
            passwordEncryptionFileProperties ))) {
      throw hr;
    }
    return hr;
  }    
    
  _bstr_t getPassword ( )
  {
    return presentation->GetPassword ( );
  }    
    
  void putPassword (
          _bstr_t Password )  
  {
    presentation->PutPassword (
            Password );
  }    

  _bstr_t getWritePassword ( )
  {
    return presentation->GetWritePassword ( );
  }    
    
  void putWritePassword (
          _bstr_t writePassword )
  {
    presentation->PutWritePassword (
            writePassword );
  }    
    
  Office::PermissionPtr getPermission ( )
  {
    return presentation->GetPermission ( );
  }    
    
  Office::SharedWorkspacePtr getSharedWorkspace ( )
  {
    return presentation->GetSharedWorkspace ( );
  }    
    
  Office::SyncPtr getSync ( )
  {
    return presentation->GetSync ( );
  }    
    
  HRESULT sendFaxOverInternet (
          _bstr_t recipients,
          _bstr_t subject,
          VARIANT_BOOL showMessage )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = presentation->SendFaxOverInternet (
            recipients,
            subject,
            showMessage ))) {
      throw hr;
    }
    return hr;
  }    
    
  Office::DocumentLibraryVersionsPtr getDocumentLibraryVersions ( )
  {
    return presentation->GetDocumentLibraryVersions ( );
  }    

   
};

}
