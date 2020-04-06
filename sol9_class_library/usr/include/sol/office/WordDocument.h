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
 *  WordDocument.h
 *
 *****************************************************************************/

//2010/04/08
//2010/05/05 Added a lot of public methods.

#pragma once

#include <sol/office/WordApplet.h>

namespace SOL {

class WordDocument :public Object {

private:
  Word::_DocumentPtr document;

public:
  WordDocument(Word::_DocumentPtr doc)
    :document(doc)
  {
  }

public:
  ~WordDocument()
  {
    document = NULL;
  }

public:
    
  _bstr_t getName ( )
  {
    return document->GetName ( );
  }

    
  Word::_ApplicationPtr getApplication ( )
  {
    return document->GetApplication ( );
  }

      long getCreator ( )
  {
    return document->GetCreator ( );
  }

      IDispatchPtr GetParent ( )
  {
    return document->GetParent ( );
  }

    
  IDispatchPtr GetBuiltInDocumentProperties ( )
  {
    return document->GetBuiltInDocumentProperties ( );
  }

    
  IDispatchPtr getCustomDocumentProperties ( )
   {
    return document->GetCustomDocumentProperties ( );
  }

     _bstr_t getPath ( )
      {
    document->GetPath ( );
  }

  Word::BookmarksPtr getBookmarks ( )
  {
    return document->GetBookmarks ( );
  }

    
  Word::TablesPtr getTables ( )
  {
    return document->GetTables ( );
  }

    
  Word::FootnotesPtr getFootnotes ( )
  {
    return document->GetFootnotes ( );
  }

   
 
  Word::EndnotesPtr getEndnotes ( )
  {
    return document->GetEndnotes ( );
  }

    
  Word::CommentsPtr getComments ( )
  {
    return document->GetComments ( );
  }

    
  enum Word::WdDocumentType getType ( )
  {
    return document->GetType ( );
  }

    
  VARIANT_BOOL getAutoHyphenation ( )
  {
    return document->GetAutoHyphenation ( );
  }

    
  void putAutoHyphenation (
          VARIANT_BOOL prop )
  {
    document->PutAutoHyphenation (
            prop );
  }

    
  VARIANT_BOOL getHyphenateCaps ( )
  {
    return document->GetHyphenateCaps ( );
  }

      void putHyphenateCaps (
          VARIANT_BOOL prop )
  {
    document->PutHyphenateCaps (
      prop );
  }

    
  long getHyphenationZone ( )
  {
    return document->GetHyphenationZone ( );
  }

    
  void putHyphenationZone (
          long prop )
  {
    document->PutHyphenationZone (
            prop );
  }

    
  long getConsecutiveHyphensLimit ( )
  {
    return document->GetConsecutiveHyphensLimit ( );
  }

    
  void PutConsecutiveHyphensLimit (
          long prop )
  {
    document->PutConsecutiveHyphensLimit (
            prop );
  }

    
  Word::SectionsPtr getSections ( )
  {
    return document->GetSections ( );
  }

    
  Word::ParagraphsPtr getParagraphs ( )
  {
    return document->GetParagraphs ( );
  }

    
  Word::WordsPtr getWords ( )
  {
    return document->GetWords ( );
  }

    
  Word::SentencesPtr getSentences ( )
  {
    return document->GetSentences ( );
  }

    
  Word::CharactersPtr getCharacters ( )
  {
    return document->GetCharacters ( );
  }

    
  Word::FieldsPtr getFields ( )
  {
    return document->GetFields ( );
  }

    
  Word::FormFieldsPtr getFormFields ( )
  {
    return document->GetFormFields ( );
  }

    
  Word::StylesPtr getStyles ( )
  {
    return document->GetStyles ( );
  }

    
  Word::FramesPtr getFrames ( )
  {
    return document->GetFrames ( );
  }

    
  Word::TablesOfFiguresPtr getTablesOfFigures ( )
  {
    return document->GetTablesOfFigures ( );
  }

    
  Word::VariablesPtr getVariables ( )
  {
    return document->GetVariables ( );
  }

    
  Word::MailMergePtr getMailMerge ( )
  {
    return document->GetMailMerge ( );
  }

    
  Word::EnvelopePtr getEnvelope ( )
  {
    return document->GetEnvelope ( );
  }

    
  _bstr_t getFullName ( )
  {
    return document->GetFullName ( );
  }

    
  Word::RevisionsPtr getRevisions ( )
  {
    return document->GetRevisions ( );
  }

    
  Word::TablesOfContentsPtr getTablesOfContents ( )
  {
    return document->GetTablesOfContents ( );
  }

    
  Word::TablesOfAuthoritiesPtr getTablesOfAuthorities ( )
  {
    return document->GetTablesOfAuthorities ( );
  }

    
  Word::PageSetupPtr getPageSetup ( )
  {
    return document->GetPageSetup ( );
  }

    
  void putPageSetup (
  struct Word::PageSetup * prop )
  {
    document->PutPageSetup (
            prop );
  }

    
  Word::WindowsPtr getWindows ( )
  {
    return document->GetWindows ( );
  }

    
  VARIANT_BOOL getHasRoutingSlip ( )
  {
    return document->GetHasRoutingSlip ( );
  }

      void putHasRoutingSlip (
          VARIANT_BOOL prop )
  {
    document->PutHasRoutingSlip (
            prop );
  }

    
  Word::RoutingSlipPtr getRoutingSlip ( )
  {
    return document->GetRoutingSlip ( );
  }

    
  VARIANT_BOOL getRouted ( )
  {
    return document->GetRouted ( );
  }

    
  Word::TablesOfAuthoritiesCategoriesPtr getTablesOfAuthoritiesCategories ( )
  {
    return document-> GetTablesOfAuthoritiesCategories ( );
  }

    
  Word::IndexesPtr getIndexes ( )
  {
    return document->GetIndexes ( );
  }

    
  VARIANT_BOOL getSaved ( )
  {
    return document->GetSaved ( );
  }

    
  void putSaved (
          VARIANT_BOOL prop )
  {
    document->PutSaved (
            prop );
  }

    
  Word::RangePtr getContent ( )
  {
    return document->GetContent ( );
  }

    
  Word::WindowPtr getActiveWindow ( )
  {
    return document->GetActiveWindow ( );
  }

    
  enum Word::WdDocumentKind getKind ( )
  {
    return document->GetKind ( );
  }

    
  void putKind (
          enum Word::WdDocumentKind prop )
  {
    document->PutKind (
             prop );
  }

    
  VARIANT_BOOL getReadOnly ( )
  {
    return document-> GetReadOnly ( );
  }

  Word::SubdocumentsPtr getSubdocuments ( )
  {
    return document->GetSubdocuments ( );
  }

    
  VARIANT_BOOL getIsMasterDocument ( )
  {
    return document->GetIsMasterDocument ( );
  }

    
  float getDefaultTabStop ( )
  {
    return document->GetDefaultTabStop ( );
  }

    
  void putDefaultTabStop (
          float prop )
  {
    document->PutDefaultTabStop (
            prop );
  }

    
  VARIANT_BOOL getEmbedTrueTypeFonts ( )
  {
    return document->GetEmbedTrueTypeFonts ( );
  }

    
  void putEmbedTrueTypeFonts (
          VARIANT_BOOL prop )
  {
    document->PutEmbedTrueTypeFonts (
            prop );
  }

    
  VARIANT_BOOL getSaveFormsData ( )
  {
    return document->GetSaveFormsData ( );
  }

    
  void putSaveFormsData (
          VARIANT_BOOL prop )
  {
    document-> PutSaveFormsData (
            prop );
  }

    
  VARIANT_BOOL getReadOnlyRecommended ( )
  {
    return document->GetReadOnlyRecommended ( );
  }

    
  void putReadOnlyRecommended (
          VARIANT_BOOL prop )
  {
    document->PutReadOnlyRecommended (
              prop );
  }

    
  VARIANT_BOOL getSaveSubsetFonts ( )
  {
    return document->GetSaveSubsetFonts ( );
  }

  void putSaveSubsetFonts (
          VARIANT_BOOL prop )
  {
    document->PutSaveSubsetFonts (
            prop );
  }

  VARIANT_BOOL getCompatibility (
          enum Word::WdCompatibility Type )
  {
    return document->GetCompatibility (
            Type );
  }

    
  void putCompatibility (
           enum Word::WdCompatibility Type,
          VARIANT_BOOL prop )
  {
    document->PutCompatibility (
             Type,
            prop );
  }

    
  Word::StoryRangesPtr getStoryRanges ( )
  {
    return document->GetStoryRanges ( );
  }

    
  Office::_CommandBarsPtr getCommandBars ( )
  {
    return document->GetCommandBars ( );
  }

  VARIANT_BOOL getIsSubdocument ( )
  {
    return document->GetIsSubdocument ( );
  }

    
  long getSaveFormat ( )
  {
    return document->GetSaveFormat ( );
  }

    
  enum Word::WdProtectionType getProtectionType ( )
  {
    return document->GetProtectionType ( );
  }

    
  Word::HyperlinksPtr getHyperlinks ( )
  {
    return document->GetHyperlinks ( );
  }

    
  Word::ShapesPtr getShapes ( )
  {
    return document->GetShapes ( );
  }

    
  Word::ListTemplatesPtr getListTemplates ( )
  {
    return document->GetListTemplates ( );
  }

    
  Word::ListsPtr getLists ( )
  {
    return document->GetLists ( );
  }

    
  VARIANT_BOOL getUpdateStylesOnOpen ( )
  {
    return document->GetUpdateStylesOnOpen ( );
  }
    
  void putUpdateStylesOnOpen (
          VARIANT_BOOL prop )
  {
    document->PutUpdateStylesOnOpen (
            prop );
  }

    
  _variant_t getAttachedTemplate ( )
  {
    return document->GetAttachedTemplate ( );
  }

    
  void putAttachedTemplate (
          VARIANT * prop )
  {
    document->PutAttachedTemplate (
              prop );
  }

    
  Word::InlineShapesPtr getInlineShapes ( )
  {
    return document->GetInlineShapes ( );
  }

    
  Word::ShapePtr getBackground ( )
  {
    return document->GetBackground ( );
  }

    
  void putBackground (
  struct Word::Shape * prop )
  {
    document->PutBackground (
            prop );
  }

    
  VARIANT_BOOL getGrammarChecked ( )
  {
    return document->GetGrammarChecked ( );
  }

    
  void putGrammarChecked (
          VARIANT_BOOL prop )
  {
    document->PutGrammarChecked (
            prop );
  }

    
  VARIANT_BOOL getSpellingChecked ( )
  {
    return document->GetSpellingChecked ( );
  }

    
  void putSpellingChecked (
          VARIANT_BOOL prop )
  {
    document->PutSpellingChecked (
            prop );
  }

    
  VARIANT_BOOL getShowGrammaticalErrors ( )
  {
    return document->GetShowGrammaticalErrors ( );
  }

    
  void putShowGrammaticalErrors (
          VARIANT_BOOL prop )
  {
    document->PutShowGrammaticalErrors (
            prop );
  }

    
  VARIANT_BOOL getShowSpellingErrors ( )
  {
    return document->GetShowSpellingErrors ( );
  }

    
  void putShowSpellingErrors (
          VARIANT_BOOL prop )
  {
    document->PutShowSpellingErrors (
            prop );
  }

  Word::VersionsPtr getVersions ( )
  {
    return document->GetVersions ( );
  }


  VARIANT_BOOL getShowSummary ( )
  {
    return document->GetShowSummary ( );
  }

    
  void putShowSummary (
          VARIANT_BOOL prop )
  {
    document->PutShowSummary (
            prop );
  }

    
  enum Word::WdSummaryMode getSummaryViewMode ( )
  {
    return document->GetSummaryViewMode ( );
  }

    
  void putSummaryViewMode (
          enum Word::WdSummaryMode prop )
  {
    document->PutSummaryViewMode (
      prop );
  }

    
  long getSummaryLength ( )
  {
    return document->GetSummaryLength ( );
  }

    
  void putSummaryLength (
          long prop )
  {
    document->PutSummaryLength (
            prop );
  }

    
  VARIANT_BOOL getPrintFractionalWidths ( )
  {
    return document->GetPrintFractionalWidths ( );
  }

    
  void putPrintFractionalWidths (
          VARIANT_BOOL prop )
  {
    document-> PutPrintFractionalWidths (
            prop );
  }

    
  VARIANT_BOOL getPrintPostScriptOverText ( )
  {
    return document->GetPrintPostScriptOverText ( );
  }

    
  void putPrintPostScriptOverText (
          VARIANT_BOOL prop )
  {
    document->PutPrintPostScriptOverText (
            prop );
  }

    
  IDispatchPtr getContainer ( )
  {
    return document->GetContainer ( );
  }

    
  VARIANT_BOOL getPrintFormsData ( )
  {
    return document->GetPrintFormsData ( );
  }

    
  void putPrintFormsData (
          VARIANT_BOOL prop )
  {
    document->PutPrintFormsData (
            prop );
  }

    
  Word::ListParagraphsPtr getListParagraphs ( )
  {
    return document->GetListParagraphs ( );
  }

    
  void putPassword (
          _bstr_t _arg1 )
  {
    document->PutPassword (
            _arg1 );
  }

    
  void putWritePassword (
          _bstr_t _arg1 )
  {
    document-> PutWritePassword (
            _arg1 );
  }

    
  VARIANT_BOOL getHasPassword ( )
  {
    return document->GetHasPassword ( );
  }

    
  VARIANT_BOOL getWriteReserved ( )
  {
    return document->GetWriteReserved ( );
  }

    
  _bstr_t getActiveWritingStyle (
          VARIANT * languageID )
  {
    return document->GetActiveWritingStyle (
            languageID );
  }

    
  void putActiveWritingStyle (
          VARIANT * languageID,
          _bstr_t prop )
  {
    document->PutActiveWritingStyle (
            languageID,
            prop );
  }

    
  VARIANT_BOOL getUserControl ( )
  {
    return document->GetUserControl ( );
  }

    
  void putUserControl (
          VARIANT_BOOL prop )
  {
    document->PutUserControl (
            prop );
  }

    
  VARIANT_BOOL getHasMailer ( )
  {
    return document->GetHasMailer ( );
  }

  void putHasMailer (
          VARIANT_BOOL prop )
  {
    document->PutHasMailer (
              prop );
  }

    
  Word::MailerPtr getMailer ( )
  {
    return document->GetMailer ( );
  }

    
  Word::ReadabilityStatisticsPtr getReadabilityStatistics ( )
  {
    return document->GetReadabilityStatistics ( );
  }

    
  Word::ProofreadingErrorsPtr getGrammaticalErrors ( )
  {
    return document->GetGrammaticalErrors ( );
  }

    
  Word::ProofreadingErrorsPtr getSpellingErrors ( )
  {
    return document->GetSpellingErrors ( );
  }

    
  VBIDE::_VBProjectPtr getVBProject ( )
  {
    return document->GetVBProject ( );
  }

    
  VARIANT_BOOL getFormsDesign ( )
  {
    return document->GetFormsDesign ( );
  }

    
  _bstr_t get_CodeName ( )
  {
    return document->Get_CodeName ( );
  }

    
  void putCodeName (
          _bstr_t prop )
  {
    document->Put_CodeName (
            prop );
  }

    
  _bstr_t getCodeName ( )
  {
    return document->GetCodeName ( );
   }

    
  VARIANT_BOOL getSnapToGrid ( )
  {
    return document->GetSnapToGrid ( );
  }

    
  void putSnapToGrid (
          VARIANT_BOOL prop )
  {
    document->PutSnapToGrid (
            prop );
  }

    
  VARIANT_BOOL getSnapToShapes ( )
  {
    return document->GetSnapToShapes ( );
  }

    
  void putSnapToShapes (
          VARIANT_BOOL prop )
  {
    document->PutSnapToShapes (
            prop );
  }

    
  float getGridDistanceHorizontal ( )
  {
    return document->GetGridDistanceHorizontal ( );
  }

    
  void putGridDistanceHorizontal (
          float prop )
  {
    document->PutGridDistanceHorizontal (
            prop );
  }

    
  float getGridDistanceVertical ( )
  {
    return document->GetGridDistanceVertical ( );
  }

    
  void putGridDistanceVertical (
          float prop )
  {
    document->PutGridDistanceVertical (
            prop );
  }

    
  float getGridOriginHorizontal ( )
  {
    return document-> GetGridOriginHorizontal ( );
  }

    
  void putGridOriginHorizontal (
          float prop )
  {
    document->PutGridOriginHorizontal (
            prop );
  }

    
  float getGridOriginVertical ( )
  {
    return document->GetGridOriginVertical ( );
  }

    
  void putGridOriginVertical (
          float prop )
  {
    document->PutGridOriginVertical (
            prop );
  }

    
  long getGridSpaceBetweenHorizontalLines ( )
  {
    return document->GetGridSpaceBetweenHorizontalLines ( );
  }

    
  void putGridSpaceBetweenHorizontalLines (
          long prop )
  {
    document->PutGridSpaceBetweenHorizontalLines (
            prop );
  }

    
  long getGridSpaceBetweenVerticalLines ( )
  {
    return document->GetGridSpaceBetweenVerticalLines ( );
  }

    
  void putGridSpaceBetweenVerticalLines (
          long prop )
  {
    document->PutGridSpaceBetweenVerticalLines (
            prop );
  }

    
  VARIANT_BOOL getGridOriginFromMargin ( )
  {
    return document->GetGridOriginFromMargin ( );
  }

    
  void putGridOriginFromMargin (
          VARIANT_BOOL prop )
  {
    document->PutGridOriginFromMargin (
            prop );
  }

    
  VARIANT_BOOL getKerningByAlgorithm ( )
  {
    return document->GetKerningByAlgorithm ( );
  }

    
  void putKerningByAlgorithm (
          VARIANT_BOOL prop )
  {
    document->PutKerningByAlgorithm (
            prop );
  }

    
  enum Word::WdJustificationMode getJustificationMode ( )
  {
    return document->GetJustificationMode ( );
  }

    
  void putJustificationMode (
          enum Word::WdJustificationMode prop )
  {
    document->PutJustificationMode (
            prop );
  }

    
  enum Word::WdFarEastLineBreakLevel getFarEastLineBreakLevel ( )
  {
    return document->GetFarEastLineBreakLevel ( );
  }

    
  void putFarEastLineBreakLevel (
          enum Word::WdFarEastLineBreakLevel prop )
  {
    document->PutFarEastLineBreakLevel (
            prop );
  }

    
  _bstr_t getNoLineBreakBefore ( )
  {
    return document->GetNoLineBreakBefore ( );
  }

    
  void putNoLineBreakBefore (
          _bstr_t prop )
  {
    document->PutNoLineBreakBefore (
            prop );
  }

    
  _bstr_t getNoLineBreakAfter ( )
  {
    return document->GetNoLineBreakAfter ( );
  }

    
  void putNoLineBreakAfter (
          _bstr_t prop )
  {
    document->PutNoLineBreakAfter (
            prop );
  }

    
  VARIANT_BOOL getTrackRevisions ( )
  {
    return document->GetTrackRevisions ( );
  }

    
  void putTrackRevisions (
          VARIANT_BOOL prop )
  {
    document->PutTrackRevisions (
            prop );
  }

    
  VARIANT_BOOL getPrintRevisions ( )
  {
    return document->GetPrintRevisions ( );
  }

    
  void putPrintRevisions (
          VARIANT_BOOL prop )
  {
    document->PutPrintRevisions (
            prop );
    }

    
  VARIANT_BOOL getShowRevisions ( )
  {
    return document->GetShowRevisions ( );
  }

    
  void putShowRevisions (
          VARIANT_BOOL prop )
  {
    document->PutShowRevisions (
            prop );
  }

    
  HRESULT close (
          VARIANT * saveChanges = &vtMissing,
    VARIANT * originalFormat = &vtMissing,
    VARIANT * routeDocument = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Close (
            saveChanges,
            originalFormat,
            routeDocument))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT saveAs2000 (
          VARIANT * fileName = &vtMissing,
          VARIANT * fileFormat = &vtMissing,
          VARIANT * lockComments = &vtMissing,
          VARIANT * password = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * writePassword = &vtMissing,
          VARIANT * readOnlyRecommended = &vtMissing,
          VARIANT * embedTrueTypeFonts = &vtMissing,
          VARIANT * saveNativePictureFormat = &vtMissing,
          VARIANT * saveFormsData = &vtMissing,
          VARIANT * saveAsAOCELetter = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document-> SaveAs2000 (
      fileName ,
      fileFormat,
      lockComments,
      password,
      addToRecentFiles,
      writePassword,
      readOnlyRecommended,
      embedTrueTypeFonts,
      saveNativePictureFormat,
      saveFormsData,
      saveAsAOCELetter))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT repaginate ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document-> Repaginate ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT fitToPages ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->FitToPages ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT manualHyphenation ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ManualHyphenation ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT select ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Select ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT dataForm ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->DataForm ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT route ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Route ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT save ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Save ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT printOutOld (
          VARIANT * background = &vtMissing,
          VARIANT * append = &vtMissing,
          VARIANT * range = &vtMissing,
          VARIANT * outputFileName = &vtMissing,
          VARIANT * from = &vtMissing,
          VARIANT * to = &vtMissing,
          VARIANT * item = &vtMissing,
          VARIANT * copies = &vtMissing,
          VARIANT * pages = &vtMissing,
          VARIANT * pageType = &vtMissing,
          VARIANT * printToFile = &vtMissing,
          VARIANT * collate = &vtMissing,
          VARIANT * activePrinterMacGX = &vtMissing,
          VARIANT * manualDuplexPrint = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document-> PrintOutOld (
      background,
      append,
      range,
      outputFileName,
      from,
      to,
      item,
      copies,
      pages,
      pageType,
      printToFile,
      collate,
      activePrinterMacGX,
      manualDuplexPrint))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT sendMail ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SendMail ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Word::RangePtr range (
          VARIANT * start = &vtMissing,
          VARIANT * end = &vtMissing )
  {
    return document->Range (
            start,
            end);
  }

    
  HRESULT runAutoMacro (
          enum Word::WdAutoMacros which )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RunAutoMacro (
            which ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT activate ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Activate ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT printPreview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->PrintPreview ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Word::RangePtr goTo (
          VARIANT * what = &vtMissing,
          VARIANT * which = &vtMissing,
          VARIANT * count = &vtMissing,
          VARIANT * name = &vtMissing )
  {
    return document->GoTo (
            what,
            which,
            count,
            name);
  }

    
  VARIANT_BOOL undo (
          VARIANT * times = &vtMissing )
  {
    return document->Undo (
            times);
  }

    
  VARIANT_BOOL redo (
          VARIANT * times = &vtMissing )
  {
    return document->Redo (
            times);
  }
    
  long computeStatistics (
          enum Word::WdStatistic statistic,
          VARIANT * includeFootnotesAndEndnotes = &vtMissing )
  {
    return document->ComputeStatistics (
            statistic,
            includeFootnotesAndEndnotes);
  }

    
  HRESULT makeCompatibilityDefault ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->MakeCompatibilityDefault ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT protect2002 (
          enum Word::WdProtectionType type,
          VARIANT * noReset = &vtMissing,
          VARIANT * password = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Protect2002 (
            type,
            noReset,
            password))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT unprotect (
          VARIANT * password = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Unprotect (
            password ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT editionOptions (
          enum Word::WdEditionType type,
          enum Word::WdEditionOption option,
           _bstr_t name,
          VARIANT * format = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->EditionOptions (
            type,
            option,
             name,
            format))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT runLetterWizard (
          VARIANT * letterContent = &vtMissing,
          VARIANT * wizardMode = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document-> RunLetterWizard (
            letterContent,
            wizardMode))) {
      throw hr;
    }
    return hr;
  }

    
  Word::_LetterContentPtr getLetterContent ( )
  {
    return document->GetLetterContent ( );
  }

  HRESULT setLetterContent (
          VARIANT * letterContent )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SetLetterContent (
            letterContent ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT copyStylesFromTemplate (
          _bstr_t stemplate )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->CopyStylesFromTemplate (
            stemplate ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT updateStyles ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->UpdateStyles ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT checkGrammar ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->CheckGrammar ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT checkSpelling (
          VARIANT * customDictionary = &vtMissing,
          VARIANT * ignoreUppercase = &vtMissing,
          VARIANT * alwaysSuggest = &vtMissing,
          VARIANT * customDictionary2 = &vtMissing,
          VARIANT * customDictionary3 = &vtMissing,
          VARIANT * customDictionary4 = &vtMissing,
          VARIANT * customDictionary5 = &vtMissing,
          VARIANT * customDictionary6 = &vtMissing,
          VARIANT * customDictionary7 = &vtMissing,
          VARIANT * customDictionary8 = &vtMissing,
          VARIANT * customDictionary9 = &vtMissing,
          VARIANT * customDictionary10 = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->CheckSpelling (
            customDictionary,
            ignoreUppercase,
            alwaysSuggest,
            customDictionary2,
            customDictionary3,
            customDictionary4,
            customDictionary5,
            customDictionary6,
            customDictionary7,
            customDictionary8,
            customDictionary9,
            customDictionary10))) {
      throw hr;
    }
    return hr;
   }

    
  HRESULT followHyperlink (
          VARIANT * address = &vtMissing,
          VARIANT * subAddress = &vtMissing,
          VARIANT * newWindow = &vtMissing,
          VARIANT * addHistory = &vtMissing,
          VARIANT * extraInfo = &vtMissing,
          VARIANT * method = &vtMissing,
          VARIANT * headerInfo = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->FollowHyperlink (
      address,
      subAddress,
      newWindow,
      addHistory,
      extraInfo,
      method,
      headerInfo))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT addToFavorites ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->AddToFavorites ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT reload ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Reload ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Word::RangePtr autoSummarize (
          VARIANT * length = &vtMissing,
          VARIANT * mode = &vtMissing,
          VARIANT * updateProperties = &vtMissing )
  {
    return document->AutoSummarize (
      length,
      mode,
      updateProperties);
  }

    
  HRESULT removeNumbers (
          VARIANT * numberType = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RemoveNumbers (
            numberType ))) {
      throw hr;
    }
    return hr;
  }

   
  HRESULT convertNumbersToText (
          VARIANT * numberType = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ConvertNumbersToText (
            numberType ))) {
      throw hr;
    }
    return hr;
  }

    
  long countNumberedItems (
          VARIANT * numberType = &vtMissing,
          VARIANT * level = &vtMissing )
  {
    return document->CountNumberedItems (
            numberType,
            level );
  }

    
  HRESULT post ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Post ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT toggleFormsDesign ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ToggleFormsDesign ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT compare2000 (
          _bstr_t name )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Compare2000 (
            name ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT updateSummaryProperties ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->UpdateSummaryProperties ( ))) {
      throw hr;
    }
    return hr;
  }

    
  _variant_t getCrossReferenceItems (
          VARIANT * referenceType )
  {
    return document->GetCrossReferenceItems (
            referenceType );
  }

    
  HRESULT autoFormat ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->AutoFormat ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT viewCode ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ViewCode ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT viewPropertyBrowser ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ViewPropertyBrowser ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT forwardMailer ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ForwardMailer ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT reply ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Reply ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT replyAll ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ReplyAll ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT sendMailer (
          VARIANT * fileFormat = &vtMissing,
          VARIANT * priority = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SendMailer (
            fileFormat,
            priority ))) {
      throw hr;
    }
    return hr;
  }


  HRESULT undoClear ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->UndoClear ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT presentIt ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->PresentIt ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT sendFax (
          _bstr_t address,
          VARIANT * subject = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SendFax (
            address,
            subject ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT merge2000 (
          _bstr_t fileName )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Merge2000 (
            fileName ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT closePrintPreview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document-> ClosePrintPreview ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT checkConsistency ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->CheckConsistency ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Word::_LetterContentPtr createLetterContent (
          _bstr_t dateFormat,
          VARIANT_BOOL includeHeaderFooter,
          _bstr_t pageDesign,
          enum Word::WdLetterStyle letterStyle,
          VARIANT_BOOL letterhead,
          enum Word::WdLetterheadLocation letterheadLocation,
          float letterheadSize,
          _bstr_t recipientName,
          _bstr_t recipientAddress,
          _bstr_t salutation,
          enum Word::WdSalutationType salutationType,
          _bstr_t recipientReference,
          _bstr_t mailingInstructions,
          _bstr_t attentionLine,
          _bstr_t subject,
          _bstr_t ccList,
          _bstr_t returnAddress,
          _bstr_t senderName,
          _bstr_t closing,
          _bstr_t senderCompany,
          _bstr_t senderJobTitle,
          _bstr_t senderInitials,
          long enclosureNumber,
          VARIANT * infoBlock = &vtMissing,
          VARIANT * recipientCode = &vtMissing,
          VARIANT * recipientGender = &vtMissing,
          VARIANT * returnAddressShortForm = &vtMissing,
          VARIANT * senderCity = &vtMissing,
          VARIANT * senderCode = &vtMissing,
          VARIANT * senderGender = &vtMissing,
          VARIANT * senderReference = &vtMissing )
  {
    return document->CreateLetterContent (
            dateFormat,
            includeHeaderFooter,
            pageDesign,
            letterStyle,
            letterhead,
            letterheadLocation,
            letterheadSize,
            recipientName,
            recipientAddress,
            salutation,
            salutationType,
            recipientReference,
            mailingInstructions,
            attentionLine,
            subject,
            ccList,
            returnAddress,
            senderName,
            closing,
            senderCompany,
            senderJobTitle,
            senderInitials,
            enclosureNumber,

            infoBlock,
            recipientCode,
            recipientGender,
            returnAddressShortForm,
            senderCity,
            senderCode,
            senderGender,
            senderReference );
  
  }

    
  HRESULT acceptAllRevisions ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->AcceptAllRevisions ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT rejectAllRevisions ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RejectAllRevisions ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT detectLanguage ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->DetectLanguage ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT applyTheme (
          _bstr_t name )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ApplyTheme (
            name ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT removeTheme ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RemoveTheme ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT webPagePreview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->WebPagePreview ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT reloadAs (
          enum Office::MsoEncoding encoding )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ReloadAs (
            encoding ))) {
      throw hr;
    }
    return hr;
  }

    
  _bstr_t getActiveTheme ( )
  {
    return document->GetActiveTheme ( );
  }

    
  _bstr_t getActiveThemeDisplayName ( )
  {
    return document->GetActiveThemeDisplayName ( );
  }

    
  Word::EmailPtr getEmail ( )
  {
    return document->GetEmail ( );
  }

    
  Office::ScriptsPtr getScripts ( )
  {
    return document->GetScripts ( );
  }

    
  VARIANT_BOOL getLanguageDetected ( )
  {
    return document->GetLanguageDetected ( );
  }

    
  void putLanguageDetected (
          VARIANT_BOOL prop )
  {
    document->PutLanguageDetected (
            prop );
  }

    
  enum Word::WdFarEastLineBreakLanguageID getFarEastLineBreakLanguage ( )
  {
    return document->GetFarEastLineBreakLanguage ( );
  }

    
  void putFarEastLineBreakLanguage (
          enum Word::WdFarEastLineBreakLanguageID prop )
  {
    document->PutFarEastLineBreakLanguage (
            prop );
  }

    
  Word::FramesetPtr getFrameset ( )
  {
    return document->GetFrameset ( );
  }

    
  _variant_t getClickAndTypeParagraphStyle ( )
  {
    return document->GetClickAndTypeParagraphStyle ( );
  }

    
  void putClickAndTypeParagraphStyle (
          VARIANT * prop )
  {
    document->PutClickAndTypeParagraphStyle (
            prop );
  }

    
  Office::HTMLProjectPtr getHTMLProject ( )
  {
    return document->GetHTMLProject ( );
  }

    
  Word::WebOptionsPtr getWebOptions ( )
  {
    return document->GetWebOptions ( );
  }

    
  enum Office::MsoEncoding getOpenEncoding ( )
  {
    return document->GetOpenEncoding ( );
  }

    
  enum Office::MsoEncoding getSaveEncoding ( )
  {
    return document->GetSaveEncoding ( );
  }

    
  void putSaveEncoding (
          enum Office::MsoEncoding prop )
  {
    document->PutSaveEncoding (
            prop );
  }

    
  VARIANT_BOOL getOptimizeForWord97 ( )
  {
    return document-> GetOptimizeForWord97 ( );
  }

    
  void putOptimizeForWord97 (
          VARIANT_BOOL prop )
  {
    document->PutOptimizeForWord97 (
            prop );
  }

    
  VARIANT_BOOL getVBASigned ( )
  {
    return document->GetVBASigned ( );
  }

    
  HRESULT printOut2000 (
          VARIANT * background = &vtMissing,
          VARIANT * append = &vtMissing,
          VARIANT * range = &vtMissing,
          VARIANT * outputFileName = &vtMissing,
          VARIANT * from = &vtMissing,
          VARIANT * to = &vtMissing,
          VARIANT * item = &vtMissing,
          VARIANT * copies = &vtMissing,
          VARIANT * pages = &vtMissing,
          VARIANT * pageType = &vtMissing,
          VARIANT * printToFile = &vtMissing,
          VARIANT * collate = &vtMissing,
          VARIANT * activePrinterMacGX = &vtMissing,
          VARIANT * manualDuplexPrint = &vtMissing,
          VARIANT * printZoomColumn = &vtMissing,
          VARIANT * printZoomRow = &vtMissing,
          VARIANT * printZoomPaperWidth = &vtMissing,
          VARIANT * printZoomPaperHeight = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->PrintOut2000 (
            background,
            append,
            range,
            outputFileName,
            from,
            to,
            item,
            copies,
            pages,
            pageType,
            printToFile,
            collate,
            activePrinterMacGX,
            manualDuplexPrint,
            printZoomColumn,
            printZoomRow,
            printZoomPaperWidth,
            printZoomPaperHeight ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT sblt (
          _bstr_t s )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->sblt (
            s ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT convertVietDoc (
          long codePageOrigin )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ConvertVietDoc (
            codePageOrigin ))) {
      throw hr;
    }
    return hr;
  }

      
  HRESULT printOut (
          VARIANT * background = &vtMissing,
           VARIANT * append = &vtMissing,
          VARIANT * range = &vtMissing,
          VARIANT * outputFileName = &vtMissing,
          VARIANT * from = &vtMissing,
          VARIANT * to = &vtMissing,
          VARIANT * item = &vtMissing,
          VARIANT * copies = &vtMissing,
          VARIANT * pages = &vtMissing,
          VARIANT * pageType = &vtMissing,
          VARIANT * printToFile = &vtMissing,
          VARIANT * collate = &vtMissing,
          VARIANT * activePrinterMacGX = &vtMissing,
          VARIANT * manualDuplexPrint = &vtMissing,
          VARIANT * printZoomColumn = &vtMissing,
          VARIANT * printZoomRow = &vtMissing,
          VARIANT * printZoomPaperWidth = &vtMissing,
          VARIANT * printZoomPaperHeight = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->PrintOut (
            background,
            append,
            range,
            outputFileName,
            from,
            to,
            item,
            copies,
            pages,
            pageType,
            printToFile,
            collate,
            activePrinterMacGX,
            manualDuplexPrint,
            printZoomColumn,
            printZoomRow,
            printZoomPaperWidth,
            printZoomPaperHeight ))) {
      throw hr;
    }
    return hr;
  }
    
  Office::IMsoEnvelopeVBPtr getMailEnvelope ( )
  {
    return document->GetMailEnvelope ( );
  }

    
  VARIANT_BOOL getDisableFeatures ( )
  {
    return document->GetDisableFeatures ( );
  }

    
  void putDisableFeatures (
          VARIANT_BOOL prop )
  {
    document->PutDisableFeatures (
            prop );
  }


  VARIANT_BOOL getDoNotEmbedSystemFonts ( )
  {
    return document->GetDoNotEmbedSystemFonts ( );    
  }

  void putDoNotEmbedSystemFonts (
    VARIANT_BOOL prop )
  {
    document->PutDoNotEmbedSystemFonts (
      prop );
  }

    
  Office::SignatureSetPtr getSignatures ( )
  {
    return document->GetSignatures ( );
  }

    
  _bstr_t getDefaultTargetFrame ( )
  {
    return document->GetDefaultTargetFrame ( );
  }

    
  void putDefaultTargetFrame (
          _bstr_t prop )
  {
    document->PutDefaultTargetFrame (
            prop );
  }

    
  Word::HTMLDivisionsPtr getHTMLDivisions ( )
  {
    return document->GetHTMLDivisions ( );
  }

    
  enum Word::WdDisableFeaturesIntroducedAfter getDisableFeaturesIntroducedAfter ( )
  {
    return document->GetDisableFeaturesIntroducedAfter ( );
  }

    
  void putDisableFeaturesIntroducedAfter (
          enum Word::WdDisableFeaturesIntroducedAfter prop )
  {
    document->PutDisableFeaturesIntroducedAfter (
            prop );
  }

    
  VARIANT_BOOL getRemovePersonalInformation ( )
  {
    return document->GetRemovePersonalInformation ( );
  }

    
  void putRemovePersonalInformation (
          VARIANT_BOOL prop )
  {
    document->PutRemovePersonalInformation (
            prop );
  }

    
  Word::SmartTagsPtr getSmartTags ( )
  {
    return document->GetSmartTags ( );
  }

    
  HRESULT compare2002 (
          _bstr_t name,
          VARIANT * authorName = &vtMissing,
          VARIANT * compareTarget = &vtMissing,
          VARIANT * detectFormatChanges = &vtMissing,
          VARIANT * ignoreAllComparisonWarnings = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Compare2002 (
            name,
            authorName,
            compareTarget,
            detectFormatChanges,
            ignoreAllComparisonWarnings,
            addToRecentFiles ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT checkIn (
          VARIANT_BOOL saveChanges,
          VARIANT * comments,
          VARIANT_BOOL makePublic )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->CheckIn (
            saveChanges,
            comments,
            makePublic ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL canCheckin ( )
  {
    return document->CanCheckin ( );
  }

    
  HRESULT merge (
          _bstr_t fileName,
          VARIANT * mergeTarget = &vtMissing,
          VARIANT * detectFormatChanges = &vtMissing,
          VARIANT * useFormattingFrom = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Merge (
      fileName,
            mergeTarget,
            detectFormatChanges,
            useFormattingFrom,
            addToRecentFiles))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getEmbedSmartTags ( )
  {
    return document->GetEmbedSmartTags ( );
  }

    
  void putEmbedSmartTags (
          VARIANT_BOOL prop )
  {
    document->PutEmbedSmartTags (
            prop );
  }

    
  VARIANT_BOOL getSmartTagsAsXMLProps ( )
  {
    return document->GetSmartTagsAsXMLProps ( );
  }

    
  void putSmartTagsAsXMLProps (
          VARIANT_BOOL prop )
  {
    document->PutSmartTagsAsXMLProps (
            prop );
  }

    
  enum Office::MsoEncoding getTextEncoding ( )
  {
    return document->GetTextEncoding ( );
      }

    
  void putTextEncoding (
          enum Office::MsoEncoding prop )
  {
    document->PutTextEncoding (
            prop );
  }

    
  enum Word::WdLineEndingType getTextLineEnding ( )
  {
    return document->GetTextLineEnding ( );
  }

    
  void putTextLineEnding (
          enum Word::WdLineEndingType prop )
  {
    document->PutTextLineEnding (
            prop );
  }

    
  HRESULT sendForReview (
          VARIANT * recipients = &vtMissing,
          VARIANT * subject = &vtMissing,
          VARIANT * showMessage = &vtMissing,
          VARIANT * includeAttachment = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SendForReview (
      recipients,
      subject,
            showMessage,
            includeAttachment ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT replyWithChanges (
          VARIANT * showMessage = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ReplyWithChanges (
      showMessage ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT endReview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->EndReview ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Word::StyleSheetsPtr getStyleSheets ( )
  {
    return document->GetStyleSheets ( );
  }

    
  _variant_t getDefaultTableStyle ( )
  {
    return document->GetDefaultTableStyle ( );
      }

    
  _bstr_t getPasswordEncryptionProvider ( )
  {
    return document->GetPasswordEncryptionProvider ( );
  }

    
  _bstr_t getPasswordEncryptionAlgorithm ( )
  {
    return document->GetPasswordEncryptionAlgorithm ( );
  }

    
  long getPasswordEncryptionKeyLength ( )
  {
    return document->GetPasswordEncryptionKeyLength ( );
  }

    
  VARIANT_BOOL getPasswordEncryptionFileProperties ( )
  {
    return document->GetPasswordEncryptionFileProperties ( );
  }

    
  HRESULT setPasswordEncryptionOptions (
          _bstr_t passwordEncryptionProvider,
           _bstr_t passwordEncryptionAlgorithm,
          long passwordEncryptionKeyLength,
          VARIANT * passwordEncryptionFileProperties = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SetPasswordEncryptionOptions (
            passwordEncryptionProvider,
             passwordEncryptionAlgorithm,
            passwordEncryptionKeyLength,
            passwordEncryptionFileProperties ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT recheckSmartTags ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RecheckSmartTags ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT removeSmartTags ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RemoveSmartTags ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT setDefaultTableStyle (
          VARIANT * style,
          VARIANT_BOOL setInTemplate )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SetDefaultTableStyle (
            style,
            setInTemplate ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT deleteAllComments ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->DeleteAllComments ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT acceptAllRevisionsShown ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->AcceptAllRevisionsShown ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT rejectAllRevisionsShown ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RejectAllRevisionsShown ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT deleteAllCommentsShown ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->DeleteAllCommentsShown ( ))) {
      throw hr;
    }
    return hr;
  }

      
  HRESULT resetFormFields ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->ResetFormFields ( ))) {
      throw hr;
    }
    return hr;
  }

/*
enum WdSaveFormat
{
    wdFormatDocument = 0,
    wdFormatDocument97 = 0,
    wdFormatTemplate = 1,
    wdFormatTemplate97 = 1,
    wdFormatText = 2,
    wdFormatTextLineBreaks = 3,
    wdFormatDOSText = 4,
    wdFormatDOSTextLineBreaks = 5,
    wdFormatRTF = 6,
    wdFormatUnicodeText = 7,
    wdFormatEncodedText = 7,
    wdFormatHTML = 8,
    wdFormatWebArchive = 9,
    wdFormatFilteredHTML = 10,
    wdFormatXML = 11,
    wdFormatXMLDocument = 12,
    wdFormatXMLDocumentMacroEnabled = 13,
    wdFormatXMLTemplate = 14,
    wdFormatXMLTemplateMacroEnabled = 15,
    wdFormatDocumentDefault = 16,
    wdFormatPDF = 17,
    wdFormatXPS = 18,
    wdFormatFlatXML = 19,
    wdFormatFlatXMLMacroEnabled = 20,
    wdFormatFlatXMLTemplate = 21,
    wdFormatFlatXMLTemplateMacroEnabled = 22,
    wdFormatOpenDocumentText = 23
};
*/
  HRESULT saveAs (
          VARIANT * fileName = &vtMissing,
          VARIANT * fileFormat = &vtMissing,
          VARIANT * lockComments = &vtMissing,
          VARIANT * password = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * writePassword = &vtMissing,
          VARIANT * readOnlyRecommended = &vtMissing,
          VARIANT * embedTrueTypeFonts = &vtMissing,
          VARIANT * saveNativePictureFormat = &vtMissing,
          VARIANT * saveFormsData = &vtMissing,
          VARIANT * saveAsAOCELetter = &vtMissing,
          VARIANT * encoding = &vtMissing,
          VARIANT * insertLineBreaks = &vtMissing,
          VARIANT * allowSubstitutions = &vtMissing,
          VARIANT * lineEnding = &vtMissing,
          VARIANT * addBiDiMarks = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SaveAs (
            fileName,
            fileFormat,
            lockComments,
            password,
            addToRecentFiles,
            writePassword,
            readOnlyRecommended,
            embedTrueTypeFonts,
            saveNativePictureFormat,
            saveFormsData,
            saveAsAOCELetter,
            encoding,
            insertLineBreaks,
            allowSubstitutions,
            lineEnding,
            addBiDiMarks ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getEmbedLinguisticData ( )
  {
    return document->GetEmbedLinguisticData ( );
  }

    
  void putEmbedLinguisticData (
          VARIANT_BOOL prop )
  {
    document->PutEmbedLinguisticData (
            prop );
  }


  VARIANT_BOOL getFormattingShowFont ( )
  {
    return document->GetFormattingShowFont ( );
  }

    
  void putFormattingShowFont (
          VARIANT_BOOL prop )
  {
    document->PutFormattingShowFont (
            prop );
  }

    
  VARIANT_BOOL getFormattingShowClear ( )
  {
    return document->GetFormattingShowClear ( );
  }

    
  void putFormattingShowClear (
          VARIANT_BOOL prop )
  {
    document->PutFormattingShowClear (
            prop );
  }

    
  VARIANT_BOOL getFormattingShowParagraph ( )
  {
    return document->GetFormattingShowParagraph ( );
  }

    
  void putFormattingShowParagraph (
          VARIANT_BOOL prop )
  {
    document->PutFormattingShowParagraph (
            prop );
  }

    
  VARIANT_BOOL getFormattingShowNumbering ( )
  {
    return document->GetFormattingShowNumbering ( );
  }

    
  void putFormattingShowNumbering (
          VARIANT_BOOL prop )
  {
    document->PutFormattingShowNumbering (
            prop );
  }

    
  enum Word::WdShowFilter getFormattingShowFilter ( )
  {
    return document->GetFormattingShowFilter ( );
  }

  void putFormattingShowFilter (
          enum Word::WdShowFilter prop )
  {
    document->PutFormattingShowFilter (
            prop );
  }

    
  HRESULT checkNewSmartTags ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->CheckNewSmartTags ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Office::PermissionPtr getPermission ( )
  {
    return document->GetPermission ( );
  }

    
  Word::XMLNodesPtr getXMLNodes ( )
  {
    return document->GetXMLNodes ( );
  }

    
  Word::XMLSchemaReferencesPtr getXMLSchemaReferences ( )
  {
    return document->GetXMLSchemaReferences ( );
  }

    
  Office::SmartDocumentPtr getSmartDocument ( )
  {
    return document->GetSmartDocument ( );
  }

    
  Office::SharedWorkspacePtr getSharedWorkspace ( )
  {
    return document->GetSharedWorkspace ( );
  }

    
  Office::SyncPtr getSync ( )
  {
    return document->GetSync ( );
  }

    
  VARIANT_BOOL getEnforceStyle ( )
  {
    return document->GetEnforceStyle ( );
  }

    
  void putEnforceStyle (
          VARIANT_BOOL prop )
  {
    document-> PutEnforceStyle (
            prop );

  }

    
  VARIANT_BOOL getAutoFormatOverride ( )
  {
    return document->GetAutoFormatOverride ( );
  }

    
  void putAutoFormatOverride (
          VARIANT_BOOL prop )
  {
    document->PutAutoFormatOverride (
            prop );
  }

    
  VARIANT_BOOL getXMLSaveDataOnly ( )
  {
    return document->GetXMLSaveDataOnly ( );
  }

    
  void putXMLSaveDataOnly (
          VARIANT_BOOL prop )
  {
    document->PutXMLSaveDataOnly (
            prop );
  }

    
  VARIANT_BOOL getXMLHideNamespaces ( )
  {
    return document->GetXMLHideNamespaces ( );
  }

    
  void putXMLHideNamespaces (
          VARIANT_BOOL prop )
  {
    document->PutXMLHideNamespaces (
            prop );
  }

    
  VARIANT_BOOL getXMLShowAdvancedErrors ( )
  {
    return document->GetXMLShowAdvancedErrors ( );
  }

    
  void putXMLShowAdvancedErrors (
          VARIANT_BOOL prop )
  {
    document->PutXMLShowAdvancedErrors (
            prop );
  }

    
  VARIANT_BOOL getXMLUseXSLTWhenSaving ( )
  {
    return document->GetXMLUseXSLTWhenSaving ( );
  }

    
  void putXMLUseXSLTWhenSaving (
          VARIANT_BOOL prop )
  {
    document->PutXMLUseXSLTWhenSaving (
            prop );
  }

    
  _bstr_t getXMLSaveThroughXSLT ( )    
  {
    return document->GetXMLSaveThroughXSLT ( );
  }

    
  void putXMLSaveThroughXSLT (
          _bstr_t prop )
  {
    document->PutXMLSaveThroughXSLT (
            prop );
  }
    
  Office::DocumentLibraryVersionsPtr getDocumentLibraryVersions ( )
  {
    return document->GetDocumentLibraryVersions ( );
  }

    
  VARIANT_BOOL getReadingModeLayoutFrozen ( )
  {
    return document->GetReadingModeLayoutFrozen ( );
  }

  void putReadingModeLayoutFrozen (
          VARIANT_BOOL prop )
  {
    document->PutReadingModeLayoutFrozen (
            prop );
  }

  VARIANT_BOOL getRemoveDateAndTime()
  {
    return document->GetRemoveDateAndTime();
  }

  void putRemoveDateAndTime (
          VARIANT_BOOL prop )
  {
    document->PutRemoveDateAndTime (
            prop );
  }
    
  HRESULT sendFaxOverInternet (
          VARIANT * recipients = &vtMissing,
          VARIANT * subject = &vtMissing,
          VARIANT * showMessage = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SendFaxOverInternet (
            recipients,
            subject,
            showMessage))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT transformDocument (
          _bstr_t path,
          VARIANT_BOOL dataOnly )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->TransformDocument (
            path,
            dataOnly ))) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT protect (
          enum Word::WdProtectionType type,
          VARIANT * noReset = &vtMissing,
          VARIANT * password = &vtMissing,
          VARIANT * useIRM = &vtMissing,
          VARIANT * enforceStyleLock = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Protect (
            type,
            noReset,
            password,
            useIRM,
            enforceStyleLock))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT selectAllEditableRanges (
          VARIANT * editorID = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->SelectAllEditableRanges (
            editorID))) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT deleteAllEditableRanges (
          VARIANT * editorID = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->DeleteAllEditableRanges (
            editorID))) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT deleteAllInkAnnotations()
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->DeleteAllInkAnnotations ( ))) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT addDocumentWorkspaceHeader (
          VARIANT_BOOL richFormat,
          _bstr_t url,
          _bstr_t title,
          _bstr_t description,
          _bstr_t id )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->AddDocumentWorkspaceHeader (
            richFormat,
            url,
            title,
            description,
            id ))) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT removeDocumentWorkspaceHeader (
          _bstr_t id )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RemoveDocumentWorkspaceHeader (
            id ))) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT compare (
          _bstr_t name,
          VARIANT * authorName = &vtMissing,
          VARIANT * compareTarget = &vtMissing,
          VARIANT * detectFormatChanges = &vtMissing,
          VARIANT * ignoreAllComparisonWarnings = &vtMissing,
          VARIANT * addToRecentFiles = &vtMissing,
          VARIANT * removePersonalInformation = &vtMissing,
          VARIANT * removeDateAndTime = &vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->Compare (
            name,
            authorName,
            compareTarget,
            detectFormatChanges,
            ignoreAllComparisonWarnings,
            addToRecentFiles,
            removePersonalInformation,
            removeDateAndTime ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT removeLockedStyles()
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = document->RemoveLockedStyles ( ))) {
      throw hr;
    }
    return hr;
  }
    
  Word::XMLChildNodeSuggestionsPtr getChildNodeSuggestions()
  {
    return document->GetChildNodeSuggestions ( );
  }
    
  Word::XMLNodePtr selectSingleNode (
          _bstr_t xPath,
          _bstr_t prefixMapping,
          VARIANT_BOOL fastSearchSkippingTextNodes )
  {
    return document->SelectSingleNode (
            xPath,
            prefixMapping,
            fastSearchSkippingTextNodes );

  }
    
  Word::XMLNodesPtr selectNodes (
          _bstr_t xPath,
          _bstr_t prefixMapping,
          VARIANT_BOOL fastSearchSkippingTextNodes )
  {
    return document->SelectNodes (
            xPath,
            prefixMapping,
            fastSearchSkippingTextNodes );
  }
    
  Word::XMLNodesPtr getXMLSchemaViolations()
  {
    return document->GetXMLSchemaViolations ( );
  }

    
  long getReadingLayoutSizeX()
  {
    return document->GetReadingLayoutSizeX ( );
  }
    
  void putReadingLayoutSizeX (
          long prop )
  {
    document->PutReadingLayoutSizeX (
            prop );
  }
    
  long getReadingLayoutSizeY ()
  {
    return document->GetReadingLayoutSizeY ( );
  }
    
  void putReadingLayoutSizeY (
          long prop )
  {
    document->PutReadingLayoutSizeY (prop );
  }

};


}
