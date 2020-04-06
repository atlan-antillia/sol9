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
 *  ExcelWorkBook.h
 *
 *****************************************************************************/

//2010/04/08
//2010/05/05

#pragma once

#include <sol/office/ExcelApplet.h>

namespace SOL {


class ExcelWorkBook :public Object {

private:
  Excel::_WorkbookPtr workBook;

public:
  ExcelWorkBook(Excel::_WorkbookPtr book)
    :workBook(book)
  {

  }

public:
  ~ExcelWorkBook()
  {
    workBook = NULL;
  }
/*
public:

    HRESULT close(
        const _variant_t & saveChanges = vtMissing,
        const _variant_t & filename = vtMissing,
        const _variant_t & routeWorkbook = vtMissing,
        long lcid = 0 )
  {
    return workBook->Close (
           saveChanges,
          filename,
           routeWorkbook,
          lcid);

  }

public:
  HRESULT save(long lcid=0)
  {
    return workBook->Save(lcid);
  }

public:
*/
/*
enum XlFileFormat
{
    xlAddIn = 18,
    xlCSV = 6,
    xlCSVMac = 22,
    xlCSVMSDOS = 24,
    xlCSVWindows = 23,
    xlDBF2 = 7,
    xlDBF3 = 8,
    xlDBF4 = 11,
    xlDIF = 9,
    xlExcel2 = 16,
    xlExcel2FarEast = 27,
    xlExcel3 = 29,
    xlExcel4 = 33,
    xlExcel5 = 39,
    xlExcel7 = 39,
    xlExcel9795 = 43,
    xlExcel4Workbook = 35,
    xlIntlAddIn = 26,
    xlIntlMacro = 25,
    xlWorkbookNormal = -4143,
    xlSYLK = 2,
    xlTemplate = 17,
    xlCurrentPlatformText = -4158,
    xlTextMac = 19,
    xlTextMSDOS = 21,
    xlTextPrinter = 36,
    xlTextWindows = 20,
    xlWJ2WD1 = 14,
    xlWK1 = 5,
    xlWK1ALL = 31,
    xlWK1FMT = 30,
    xlWK3 = 15,
    xlWK4 = 38,
    xlWK3FM3 = 32,
    xlWKS = 4,
    xlWorks2FarEast = 28,
    xlWQ1 = 34,
    xlWJ3 = 40,
    xlWJ3FJ3 = 41,
    xlUnicodeText = 42,
    xlHtml = 44,
    xlWebArchive = 45,
    xlXMLSpreadsheet = 46,
    xlExcel12 = 50,
    xlOpenXMLWorkbook = 51,
    xlOpenXMLWorkbookMacroEnabled = 52,
    xlOpenXMLTemplateMacroEnabled = 53,
    xlTemplate8 = 17,
    xlOpenXMLTemplate = 54,
    xlAddIn8 = 18,
    xlOpenXMLAddIn = 55,
    xlExcel8 = 56,
    xlOpenDocumentSpreadsheet = 60,
    xlWorkbookDefault = 51
};
enum XlSaveAsAccessMode
{
    xlExclusive = 3,
    xlNoChange = 1,
    xlShared = 2
};
  
*/

  HRESULT saveAs (
        const _variant_t & filename,
        const _variant_t & fileFormat,
        const _variant_t & password=vtMissing,
        const _variant_t & writeResPassword=vtMissing,
        const _variant_t & readOnlyRecommended=vtMissing,
        const _variant_t & createBackup=vtMissing,
    enum Excel::XlSaveAsAccessMode accessMode=Excel::xlNoChange,
        const _variant_t & conflictResolution = vtMissing,
        const _variant_t & addToMru = vtMissing,
        const _variant_t & textCodepage = vtMissing,
        const _variant_t & textVisualLayout = vtMissing,
        const _variant_t & local = vtMissing,
        long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = workBook-> SaveAs (
          filename,
          fileFormat,
          password,
          writeResPassword,
          readOnlyRecommended,
          createBackup,
          accessMode,
          conflictResolution,
          addToMru,
          textCodepage,
          textVisualLayout,
          local,
      lcid)) ) {
      throw hr;
    }
    return hr;
  }

public:

  Excel::_ApplicationPtr getApplication ( )
  {
    return workBook->GetApplication ( );
  }

    
  enum Excel::XlCreator getCreator ( )
  {
    return workBook->GetCreator ( );
  }

    
  IDispatchPtr getParent ( )
  {
    return workBook->GetParent ( );
  }

    
  VARIANT_BOOL getAcceptLabelsInFormulas ( )
  {
    return workBook->GetAcceptLabelsInFormulas ( );
  }

    
  void putAcceptLabelsInFormulas (
          VARIANT_BOOL RHS )
  {
    workBook->PutAcceptLabelsInFormulas (
            RHS );
  }

    
  HRESULT activate (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Activate (
            lcid))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::_ChartPtr getActiveChart ( )
  {
    return workBook->GetActiveChart ( );
  }

    
  IDispatchPtr getActiveSheet ( )
  {
    return workBook->GetActiveSheet ( );
  }

    
  _bstr_t getAuthor (
          long lcid = 0 )
  {
    return workBook->GetAuthor (
            lcid);
  }

    
  void putAuthor (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutAuthor (
            lcid,
            rhs );
  }

    
  long getAutoUpdateFrequency ( )
  {
    return workBook->GetAutoUpdateFrequency ( );
  }

    
  void putAutoUpdateFrequency (
          long rhs )
  {
    workBook->PutAutoUpdateFrequency (
            rhs );
  }

    
  VARIANT_BOOL getAutoUpdateSaveChanges ( )
  {
    return workBook->GetAutoUpdateSaveChanges ( );
  }

    
  void putAutoUpdateSaveChanges (
          VARIANT_BOOL rhs )
  {
    workBook->PutAutoUpdateSaveChanges (
            rhs );
  }

    
  long getChangeHistoryDuration ( )
  {
    return workBook->GetChangeHistoryDuration ( );
  }

    
  void putChangeHistoryDuration (
          long rhs )
  {
    workBook->PutChangeHistoryDuration (
            rhs );
  }

    
  IDispatchPtr getBuiltinDocumentProperties ( )
  {
    return workBook->GetBuiltinDocumentProperties ( );
  }

    
  HRESULT changeFileAccess (
          enum Excel::XlFileAccess mode,
          const _variant_t & writePassword = vtMissing,
          const _variant_t & notify = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ChangeFileAccess (
            mode,
            writePassword,
            notify,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT changeLink (
          _bstr_t name,
          _bstr_t newName,
          enum Excel::XlLinkType type,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ChangeLink (
            name,
            newName,
            type,
            lcid  ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::SheetsPtr getCharts ( )
  {
    return workBook->GetCharts ( );
  }

    
  HRESULT close (
          const _variant_t & saveChanges = vtMissing,
          const _variant_t & filename = vtMissing,
          const _variant_t & routeWorkbook = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Close (
            saveChanges ,
            filename,
            routeWorkbook,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  _bstr_t getCodeName ( )
  {
    return workBook->GetCodeName ( );
  }

    
  _bstr_t get_CodeName ( )
  {
    return workBook->Get_CodeName ( );
  }

    
  void put_CodeName (
          _bstr_t rhs )
  {
    workBook->Put_CodeName (
            rhs );
  }

    
  _variant_t getColors (
          const _variant_t & index = vtMissing,
          long lcid = 0 )
  {
    return workBook->GetColors (
            index,
            lcid );
  }

    
  void putColors (
          const _variant_t & index,
          long lcid = 0,
          const _variant_t & rhs = vtMissing )
  {
    workBook->PutColors (
            index,
            lcid,
            rhs );
  }

    
  Office::_CommandBarsPtr getCommandBars ( )
  {
    return workBook->GetCommandBars ( );
  }

    
  _bstr_t getComments (
          long lcid = 0 )
  {
    return workBook->GetComments (
            lcid);
  }

    
  void putComments (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutComments (
            lcid,
            rhs );
  }

    
  enum Excel::XlSaveConflictResolution getConflictResolution ( )
  {
    return workBook->GetConflictResolution ( );
  }

    
  void putConflictResolution (
          enum Excel::XlSaveConflictResolution rhs )
  {
    workBook->PutConflictResolution (
            rhs );
  }

    
  IDispatchPtr getContainer ( )
  {
    return workBook->GetContainer ( );
  }

    
  VARIANT_BOOL getCreateBackup (
          long lcid = 0 )
  {
    return workBook->GetCreateBackup (
            lcid );
  }

    
  IDispatchPtr getCustomDocumentProperties ( )
  {
    return workBook->GetCustomDocumentProperties ( );
  }

    
  VARIANT_BOOL getDate1904 (
          long lcid = 0 )
  {
    return workBook->GetDate1904 (
            lcid );

  }

    
  void putDate1904 (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutDate1904 (
            lcid,
            rhs );
  }

    
  HRESULT deleteNumberFormat (
          _bstr_t numberFormat,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->DeleteNumberFormat (
            numberFormat,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::SheetsPtr getDialogSheets ( )
  {
    return workBook->GetDialogSheets ( );
  }

      enum Excel::XlDisplayDrawingObjects getDisplayDrawingObjects (
          long lcid = 0 )
  {
    return workBook->GetDisplayDrawingObjects (
            lcid );
  }

      void putDisplayDrawingObjects (
          long lcid,
          enum Excel::XlDisplayDrawingObjects rhs )
  {
    workBook->PutDisplayDrawingObjects (
            lcid,
            rhs );
  }

    
  VARIANT_BOOL exclusiveAccess (
          long lcid = 0 )
  {
    return workBook->ExclusiveAccess (
            lcid );
  }

      
  enum Excel::XlFileFormat getFileFormat (
          long lcid = 0 )
  {
    return workBook->GetFileFormat (
            lcid );
  }

    
  HRESULT forwardMailer (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ForwardMailer (
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  _bstr_t getFullName (
          long lcid = 0 )
  {
    return workBook->GetFullName (
            lcid );
  }

    
  VARIANT_BOOL getHasMailer (
          long lcid = 0 )
  {
    return workBook->GetHasMailer (
            lcid );
  }

    
  void putHasMailer (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutHasMailer (
            lcid,
            rhs );
  }

    
  VARIANT_BOOL getHasPassword (
          long lcid = 0 )
  {
    return workBook->GetHasPassword (
            lcid );
  }

    
  VARIANT_BOOL getHasRoutingSlip (
          long lcid = 0 )
  {
    return workBook->GetHasRoutingSlip (
            lcid );
  }

    
  void putHasRoutingSlip (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutHasRoutingSlip (
            lcid,
            rhs );
  }

    
  VARIANT_BOOL getIsAddin ( )
  {
    return workBook->GetIsAddin ( );
  }

    
  void putIsAddin (
          VARIANT_BOOL rhs )
  {
    workBook->PutIsAddin (
            rhs );
  }

    
  _bstr_t getKeywords (
          long lcid = 0 )
  {
    return workBook->GetKeywords (
            lcid );
  }

    
  void putKeywords (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutKeywords (
            lcid,
            rhs );
  }

    
  _variant_t linkInfo (
          _bstr_t name,
          enum Excel::XlLinkInfo linkInfo,
          const _variant_t & type = vtMissing,
          const _variant_t & editionRef = vtMissing,
          long lcid = 0 )
  {
    return workBook-> LinkInfo (
            name,
            linkInfo,
            type,
            editionRef,
            lcid );
  }

    
  _variant_t linkSources (
          const _variant_t & type = vtMissing,
          long lcid = 0 )
  {
    return workBook->LinkSources (
            type,
            lcid );
  }

    
  Excel::MailerPtr getMailer ( )
  {
    return workBook->GetMailer ( );
  }

    
  HRESULT mergeWorkbook (
          const _variant_t & filename )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->MergeWorkbook (
            filename ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::SheetsPtr getModules ( )
  {
    return workBook->GetModules ( );
  }

    
  VARIANT_BOOL getMultiUserEditing (
          long lcid = 0 )
  {
    return workBook->GetMultiUserEditing (
            lcid );
  }

    
  _bstr_t getName ( )
  {
    return workBook->GetName ( );
  }

    
  Excel::NamesPtr getNames ( )
  {
    return workBook->GetNames ( );
  }

    
  Excel::WindowPtr newWindow (
          long lcid = 0 )
  {
    return workBook->NewWindow (
            lcid );
  }

    
  _bstr_t getOnSave (
          long lcid = 0 )
  {
    return workBook->GetOnSave (
            lcid );
  }

    
  void putOnSave (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutOnSave (
            lcid,
            rhs );
  }

    
  _bstr_t getOnSheetActivate (
          long lcid = 0 )
  {
    return workBook-> GetOnSheetActivate (
            lcid );
  }

    
  void putOnSheetActivate (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutOnSheetActivate (
            lcid,
            rhs );
  }

      _bstr_t getOnSheetDeactivate (
          long lcid = 0 )
  {
    return workBook->GetOnSheetDeactivate (
            lcid );
  }

    
  void putOnSheetDeactivate (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutOnSheetDeactivate (
            lcid,
            rhs );
  }

    
  HRESULT openLinks (
          _bstr_t name,
          const _variant_t & readOnly = vtMissing,
          const _variant_t & type = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->OpenLinks (
            name,
            readOnly,
            type,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  _bstr_t getPath (
          long lcid = 0 )
  {
    return workBook->GetPath (
            lcid );
  }


    
  VARIANT_BOOL getPersonalViewListSettings ( )
  {
    return workBook->GetPersonalViewListSettings ( );
  }

    
  void putPersonalViewListSettings (
          VARIANT_BOOL rhs )
  {
    workBook->PutPersonalViewListSettings (
            rhs );
  }

    
  VARIANT_BOOL getPersonalViewPrintSettings ( )
  {
    return workBook->GetPersonalViewPrintSettings ( );
  }

    
  void putPersonalViewPrintSettings (
          VARIANT_BOOL rhs )
  {
    workBook->PutPersonalViewPrintSettings (
            rhs );
  }

    
  Excel::PivotCachesPtr pivotCaches ( )
  {
    return workBook->PivotCaches ( );
  }

    
  HRESULT post (
          const _variant_t & destName = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Post (
            destName,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getPrecisionAsDisplayed (
          long lcid = 0 )
  {
    return workBook->GetPrecisionAsDisplayed (
            lcid );
  }

    
  void putPrecisionAsDisplayed (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutPrecisionAsDisplayed (
            lcid,
            rhs );
  }

    
  HRESULT printOut (
          const _variant_t & from = vtMissing,
          const _variant_t & to = vtMissing,
          const _variant_t & copies = vtMissing,
          const _variant_t & preview = vtMissing,
          const _variant_t & activePrinter = vtMissing,
          const _variant_t & printToFile = vtMissing,
          const _variant_t & collate = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->_PrintOut (
            from,
            to,
            copies,
            preview,
            activePrinter,
            printToFile,
            collate,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT printPreview (
          const _variant_t & enableChanges = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->PrintPreview (
            enableChanges,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT protectSharing (
          const _variant_t & filename = vtMissing,
          const _variant_t & password = vtMissing,
          const _variant_t & writeResPassword = vtMissing,
          const _variant_t & readOnlyRecommended = vtMissing,
          const _variant_t & createBackup = vtMissing,
          const _variant_t & sharingPassword = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ProtectSharing (
            filename,
            password,
            writeResPassword,
            readOnlyRecommended,
            createBackup,
            sharingPassword ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getProtectStructure ( )
  {
    return workBook->GetProtectStructure ( );
  }

    
  VARIANT_BOOL getProtectWindows ( )
  {
    return workBook->GetProtectWindows ( );
  }

    
  VARIANT_BOOL getReadOnly (
          long lcid = 0 )
  {
    return workBook->GetReadOnly (
            lcid );
  }

    
  VARIANT_BOOL getReadOnlyRecommended (
          long lcid = 0 )
  {
    return workBook->Get_ReadOnlyRecommended (
            lcid );
  }

  ////    
  HRESULT refreshAll ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->RefreshAll ( ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT reply (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Reply (
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT replyAll (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ReplyAll (
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT removeUser (
          long Index )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->RemoveUser (
            Index ))) {
      throw hr;
    }
    return hr;
  }

    
  long getRevisionNumber (
          long lcid = 0 )
  {
    return workBook->GetRevisionNumber (
            lcid );
  }

    
  HRESULT route (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Route (
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getRouted (
          long lcid = 0 )
  {
    return workBook->GetRouted (
            lcid );
  }

    
  Excel::RoutingSlipPtr getRoutingSlip ( )
  {
    return workBook->GetRoutingSlip ( );
  }

    
  HRESULT runAutoMacros (
          enum Excel::XlRunAutoMacro which,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->RunAutoMacros (
            which,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT save (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Save (
            lcid ))) {
      throw hr;
    }
    return hr;
  }


  HRESULT _saveAs (
          const _variant_t & filename,
          const _variant_t & fileFormat,
          const _variant_t & password,
          const _variant_t & writeResPassword,
          const _variant_t & readOnlyRecommended,
          const _variant_t & createBackup,
          enum Excel::XlSaveAsAccessMode accessMode,
          const _variant_t & conflictResolution = vtMissing,
          const _variant_t & addToMru = vtMissing,
          const _variant_t & textCodepage = vtMissing,
          const _variant_t & textVisualLayout = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->_SaveAs (
            filename,
            fileFormat,
            password,
            writeResPassword,
            readOnlyRecommended,
            createBackup,
            accessMode,
            conflictResolution,
            addToMru,
            textCodepage,
            textVisualLayout,
            lcid ))) {
      throw hr;
    }
    return hr;
  }
  
    
  HRESULT saveCopyAs (
          const _variant_t & filename = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SaveCopyAs (
            filename,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getSaved (
          long lcid = 0 )
  {
    return workBook->GetSaved (
            lcid );
  }

      void putSaved (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutSaved (
            lcid,
            rhs );
  }

      VARIANT_BOOL getSaveLinkValues (
          long lcid = 0 )
  {
    return workBook->GetSaveLinkValues (
            lcid );
  }

    
  void putSaveLinkValues (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutSaveLinkValues (
            lcid,
            rhs );
  }

    
  HRESULT sendMail (
          const _variant_t & recipients,
          const _variant_t & subject = vtMissing,
          const _variant_t & returnReceipt = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SendMail (
            recipients,
            subject,
            returnReceipt,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT sendMailer (
          const _variant_t & fileFormat,
          enum Excel::XlPriority priority,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SendMailer (
            fileFormat,
            priority,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT setLinkOnData (
          _bstr_t name,
          const _variant_t & procedure = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SetLinkOnData (
            name,
            procedure,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::SheetsPtr getSheets ( )
  {
    return workBook->GetSheets ( );
  }

    
  VARIANT_BOOL getShowConflictHistory (
          long lcid = 0 )
  {
    return workBook->GetShowConflictHistory (
            lcid );
  }

    
  void putShowConflictHistory (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutShowConflictHistory (
            lcid,
            rhs );
  }

    
  Excel::StylesPtr getStyles ( )
  {
    return workBook->GetStyles ( );
  }

    
  _bstr_t getSubject (
          long lcid = 0 )
  {
    return workBook->GetSubject (
            lcid );
  }

    
  void putSubject (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutSubject (
            lcid,
            rhs );
  }

    
  _bstr_t getTitle (
          long lcid = 0 )
  {
    return workBook->GetTitle (
            lcid );
  }

    
  void putTitle (
          long lcid,
          _bstr_t rhs )
  {
    workBook->PutTitle (
            lcid,
            rhs );
  }

    
  HRESULT unprotect (
          const _variant_t & password = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Unprotect (
            password,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT unprotectSharing (
          const _variant_t & sharingPassword = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->UnprotectSharing (
            sharingPassword ))) {
      throw hr;
    }
    return hr;
  }

  HRESULT updateFromFile (
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->UpdateFromFile (
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT updateLink (
          const _variant_t & name = vtMissing,
          const _variant_t & type = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->UpdateLink (
            name,
            type,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getUpdateRemoteReferences (
          long lcid = 0 )
  {
    return workBook->GetUpdateRemoteReferences (
            lcid );
  }

    
  void putUpdateRemoteReferences (
          long lcid,
          VARIANT_BOOL rhs )
  {
    workBook->PutUpdateRemoteReferences (
            lcid,
            rhs );
  }

    
  VARIANT_BOOL getUserControl ( )
  {
    return workBook->GetUserControl ( );
  }

  void putUserControl (
          VARIANT_BOOL rhs )
  {
    workBook->PutUserControl (
            rhs );
  }

    
  _variant_t getUserStatus (
          long lcid = 0 )
  {
    return workBook->GetUserStatus (
            lcid );
  }
    
  Excel::CustomViewsPtr getCustomViews ( )
  {
    return workBook->GetCustomViews ( );
  }

    
  Excel::WindowsPtr getWindows ( )
  {
    return workBook->GetWindows ( );
  }

    
  Excel::SheetsPtr getWorksheets ( )
  {
    return workBook->GetWorksheets ( );
  }
  ////

    
  VARIANT_BOOL getWriteReserved (
          long lcid = 0 )
  {
    return workBook->GetWriteReserved (
            lcid );
  }

    
  _bstr_t getWriteReservedBy (
          long lcid = 0 )
  {
    return workBook->GetWriteReservedBy (
            lcid );
  }

    
  Excel::SheetsPtr getExcel4IntlMacroSheets ( )
  {
    return workBook->GetExcel4IntlMacroSheets ( );
  }

    
  Excel::SheetsPtr getExcel4MacroSheets ( )
  {
    return workBook->GetExcel4MacroSheets ( );
  }

    
  VARIANT_BOOL getTemplateRemoveExtData ( )
  {
    return workBook->GetTemplateRemoveExtData ( );

  }

  void putTemplateRemoveExtData (
          VARIANT_BOOL rhs )
  {
    workBook->PutTemplateRemoveExtData (
            rhs );
  }

    
  HRESULT highlightChangesOptions (
          const _variant_t & when = vtMissing,
          const _variant_t & who = vtMissing,
          const _variant_t & where = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->HighlightChangesOptions (
            when,
            who,
            where ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getHighlightChangesOnScreen ( )
  {
    return workBook->GetHighlightChangesOnScreen ( );
  }

    
  void putHighlightChangesOnScreen (
          VARIANT_BOOL rhs )
  {
    workBook->PutHighlightChangesOnScreen (
            rhs );
  }

    
  VARIANT_BOOL getKeepChangeHistory ( )
  {
    return workBook->GetKeepChangeHistory ( );
  }

  void putKeepChangeHistory (
          VARIANT_BOOL rhs )
  {
    workBook->PutKeepChangeHistory (
            rhs );
  }

    
  VARIANT_BOOL getListChangesOnNewSheet ( )
  {
    return workBook->GetListChangesOnNewSheet ( );
  }

    
  void putListChangesOnNewSheet (
          VARIANT_BOOL rhs )
  {
    workBook->PutListChangesOnNewSheet (
            rhs );
  }

    
  HRESULT purgeChangeHistoryNow (
          long days,
          const _variant_t & sharingPassword = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->PurgeChangeHistoryNow (
            days,
            sharingPassword ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT acceptAllChanges (
          const _variant_t & when = vtMissing,
          const _variant_t & who = vtMissing,
          const _variant_t & where = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->AcceptAllChanges (
            when,
            who,
            where ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT rejectAllChanges (
          const _variant_t & when = vtMissing,
          const _variant_t & who = vtMissing,
          const _variant_t & where = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->RejectAllChanges (
            when,
            who,
            where ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT pivotTableWizard (
          const _variant_t & sourceType = vtMissing,
          const _variant_t & sourceData = vtMissing,
          const _variant_t & tableDestination = vtMissing,
          const _variant_t & tableName = vtMissing,
          const _variant_t & rowGrand = vtMissing,
          const _variant_t & columnGrand = vtMissing,
          const _variant_t & saveData = vtMissing,
          const _variant_t & hasAutoFormat = vtMissing,
          const _variant_t & autoPage = vtMissing,
          const _variant_t & reserved = vtMissing,
          const _variant_t & backgroundQuery = vtMissing,
          const _variant_t & optimizeCache = vtMissing,
          const _variant_t & pageFieldOrder = vtMissing,
          const _variant_t & pageFieldWrapCount = vtMissing,
          const _variant_t & readData = vtMissing,
          const _variant_t & connection = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->PivotTableWizard (
            sourceType,
            sourceData,
            tableDestination,
            tableName,
            rowGrand,
            columnGrand,
            saveData,
            hasAutoFormat,
            autoPage,
            reserved,
            backgroundQuery,
            optimizeCache,
            pageFieldOrder,
            pageFieldWrapCount,
            readData,
            connection,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT resetColors ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ResetColors ( ))) {
      throw hr;
    }
    return hr;
  }

    
  VBIDE::_VBProjectPtr getVBProject ( )
  {
    return workBook->GetVBProject ( );
  }

    
  HRESULT followHyperlink (
          _bstr_t address,
          const _variant_t & subAddress = vtMissing,
          const _variant_t & newWindow = vtMissing,
          const _variant_t & addHistory = vtMissing,
          const _variant_t & extraInfo = vtMissing,
          const _variant_t & method = vtMissing,
          const _variant_t & headerInfo = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->FollowHyperlink (
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
    if (FAILED(hr = workBook->AddToFavorites ( ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getIsInplace ( )
  {
    return workBook->GetIsInplace ( );
  }

    
  HRESULT printOut (
          const _variant_t & from = vtMissing,
          const _variant_t & to = vtMissing,
          const _variant_t & copies = vtMissing,
          const _variant_t & preview = vtMissing,
          const _variant_t & activePrinter = vtMissing,
          const _variant_t & printToFile = vtMissing,
          const _variant_t & collate = vtMissing,
          const _variant_t & prToFileName = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->PrintOut (
            from,
            to,
            copies,
            preview,
            activePrinter,
            printToFile,
            collate,
            prToFileName,
            lcid ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT webPagePreview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->WebPagePreview ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::PublishObjectsPtr getPublishObjects ( )
  {
    return workBook->GetPublishObjects ( );
  }

    
  Excel::WebOptionsPtr getWebOptions ( )
  {
    return workBook->GetWebOptions ( );
  }

    
  HRESULT reloadAs (
          enum Office::MsoEncoding encoding )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ReloadAs (
            encoding ))) {
      throw hr;
    }
    return hr;
  }

    
  Office::HTMLProjectPtr getHTMLProject ( )
  {
    return workBook->GetHTMLProject ( );
  }

    
  VARIANT_BOOL getEnvelopeVisible ( )
  {
    return workBook->GetEnvelopeVisible ( );
  }

    
  void putEnvelopeVisible (
          VARIANT_BOOL rhs )
  {
    workBook->PutEnvelopeVisible (
            rhs );
  }

    
  long getCalculationVersion ( )
  {
    return workBook->GetCalculationVersion ( );
  }
    
  HRESULT sblt (
          _bstr_t s )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->sblt (
            s ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getVBASigned ( )
  {
    return workBook->GetVBASigned ( );
  }

    
  VARIANT_BOOL getShowPivotTableFieldList ( )
  {
    return workBook->GetShowPivotTableFieldList ( );
  }

    
  void putShowPivotTableFieldList (
          VARIANT_BOOL rhs )
  {
    workBook->PutShowPivotTableFieldList (
            rhs );
  }

    
  enum Excel::XlUpdateLinks getUpdateLinks ( )
  {
    return workBook->GetUpdateLinks ( );
  }

    
  void putUpdateLinks (
          enum Excel::XlUpdateLinks rhs )
  {
    workBook->PutUpdateLinks (
            rhs );
  }

    
  HRESULT breakLink (
          _bstr_t name,
          enum Excel::XlLinkType type )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->BreakLink (
            name,
            type ))) {
      throw hr;
    }
    return hr;
  }

/*        
  HRESULT saveAs (
          const _variant_t & filename,
          const _variant_t & fileFormat,
          const _variant_t & password,
          const _variant_t & writeResPassword,
          const _variant_t & readOnlyRecommended,
          const _variant_t & createBackup,
          enum Excel::XlSaveAsAccessMode accessMode,
          const _variant_t & conflictResolution = vtMissing,
          const _variant_t & addToMru = vtMissing,
          const _variant_t & textCodepage = vtMissing,
          const _variant_t & textVisualLayout = vtMissing,
          const _variant_t & local = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SaveAs (
            filename,
            fileFormat,
            password,
            writeResPassword,
            readOnlyRecommended,
            createBackup,
            accessMode,
            conflictResolution,
            addToMru,
            textCodepage,
            textVisualLayout,
            local,
            lcid ))) {
      throw hr;
    }
    return hr;
  }
*/
    
  VARIANT_BOOL getEnableAutoRecover ( )
  {
    return workBook->GetEnableAutoRecover ( );
  }

    
  void putEnableAutoRecover (
          VARIANT_BOOL rhs )
  {
    workBook->PutEnableAutoRecover (
            rhs );
  }

    
  VARIANT_BOOL getRemovePersonalInformation ( )
  {
    return workBook->GetRemovePersonalInformation ( );
  }

    
  void putRemovePersonalInformation (
          VARIANT_BOOL rhs )
  {
    workBook->PutRemovePersonalInformation (
            rhs);
  }

    
  _bstr_t getFullNameURLEncoded (
          long lcid = 0 )
  {
    return workBook->GetFullNameURLEncoded (
            lcid );
  }

      HRESULT checkIn (
          const _variant_t & saveChanges = vtMissing,
          const _variant_t & comments = vtMissing,
          const _variant_t & makePublic = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->CheckIn (
            saveChanges,
            comments,
            makePublic ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL canCheckIn ( )
  {
    return workBook->CanCheckIn ( );
  }

    
  HRESULT sendForReview (
          const _variant_t & recipients = vtMissing,
          const _variant_t & subject = vtMissing,
          const _variant_t & showMessage = vtMissing,
          const _variant_t & includeAttachment = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SendForReview (
            recipients,
            subject,
            showMessage,
            includeAttachment ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT replyWithChanges (
          const _variant_t & showMessage = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ReplyWithChanges (
            showMessage ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT endReview ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->EndReview ( ))) {
      throw hr;
    }
    return hr;
  }

    
  _bstr_t getPassword ( )
  {
    return workBook->GetPassword ( );
  }

    
  void putPassword (
          _bstr_t rhs )
  {
    workBook->PutPassword (
            rhs );
  }

    
  _bstr_t getWritePassword ( )
  {
    return workBook->GetWritePassword ( );
  }

    
  void putWritePassword (
          _bstr_t rhs )
  {
    workBook->PutWritePassword (
            rhs );
  }

    
  _bstr_t getPasswordEncryptionProvider ( )
  {
    return workBook->GetPasswordEncryptionProvider ( );
  }

    
  _bstr_t getPasswordEncryptionAlgorithm ( )
  {
    return workBook->GetPasswordEncryptionAlgorithm ( );
  }

    
  long getPasswordEncryptionKeyLength ( )
  {
    return workBook->GetPasswordEncryptionKeyLength ( );
  }

    
  HRESULT setPasswordEncryptionOptions (
          const _variant_t & passwordEncryptionProvider = vtMissing,
          const _variant_t & passwordEncryptionAlgorithm = vtMissing,
          const _variant_t & passwordEncryptionKeyLength = vtMissing,
          const _variant_t & passwordEncryptionFileProperties = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SetPasswordEncryptionOptions (
            passwordEncryptionProvider,
            passwordEncryptionAlgorithm,
            passwordEncryptionKeyLength,
            passwordEncryptionFileProperties ))) {
      throw hr;
    }
    return hr;
  }

    
  VARIANT_BOOL getPasswordEncryptionFileProperties ( )
  {
    return workBook->GetPasswordEncryptionFileProperties ( );
  }

    
  VARIANT_BOOL getReadOnlyRecommended ( )
  {
    return workBook->GetReadOnlyRecommended ( );
  }

    
  void putReadOnlyRecommended (
          VARIANT_BOOL rhs )
  {
    workBook->PutReadOnlyRecommended (
            rhs );
  }

    //
  HRESULT protect (
          const _variant_t & password = vtMissing,
          const _variant_t & structure = vtMissing,
          const _variant_t & windows = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->Protect (
            password,
            structure,
            windows ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::SmartTagOptionsPtr getSmartTagOptions ( )
  {
    return workBook->GetSmartTagOptions ( );
  }

    
  HRESULT recheckSmartTags ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->RecheckSmartTags ( ))) {
      throw hr;
    }
    return hr;
  }

    
  Office::PermissionPtr getPermission ( )
  {
    return workBook->GetPermission ( );
  }

    
  Office::SharedWorkspacePtr getSharedWorkspace ( )
  {
    return workBook->GetSharedWorkspace ( );
  }

    
  Office::SyncPtr getSync ( )
  {
    return workBook->GetSync ( );
  }

    
  HRESULT sendFaxOverInternet (
          const _variant_t & recipients = vtMissing,
          const _variant_t & subject = vtMissing,
          const _variant_t & showMessage = vtMissing )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->SendFaxOverInternet (
            recipients,
            subject,
            showMessage ))) {
      throw hr;
    }
    return hr;
  }

    
  Excel::XmlNamespacesPtr getXmlNamespaces ( )
  {
    return workBook->GetXmlNamespaces ( );
  }

    
  Excel::XmlMapsPtr getXmlMaps ( )
  {
    return workBook->GetXmlMaps ( );
  }

    
  enum Excel::XlXmlImportResult xmlImport (
          _bstr_t url,
          struct Excel::XmlMap * * importMap,
          const _variant_t & overwrite = vtMissing,
          const _variant_t & destination = vtMissing )
  {
    return workBook->XmlImport (
            url,
            importMap,
            overwrite,
            destination );
  }

    
  Office::SmartDocumentPtr getSmartDocument ( )
  {
    return workBook->GetSmartDocument ( );
  }

    
  Office::DocumentLibraryVersionsPtr getDocumentLibraryVersions ( )
  {
    return workBook->GetDocumentLibraryVersions ( );
  }

    
  VARIANT_BOOL getInactiveListBorderVisible ( )
  {
    return workBook->GetInactiveListBorderVisible ( );
  }

    
  void putInactiveListBorderVisible (
          VARIANT_BOOL rhs )
  {
    workBook->PutInactiveListBorderVisible (
            rhs );
  }

    
  VARIANT_BOOL getDisplayInkComments ( )
  {
    return workBook->GetDisplayInkComments ( );
  }

    
  void putDisplayInkComments (
          VARIANT_BOOL rhs )
  {
    workBook->PutDisplayInkComments (
            rhs );
  }

    
  enum Excel::XlXmlImportResult xmlImportXml (
          _bstr_t data,
          struct Excel::XmlMap * * importMap,
          const _variant_t & overwrite = vtMissing,
          const _variant_t & destination = vtMissing )
  {
    return workBook-> XmlImportXml (
            data,
            importMap,
            overwrite,
            destination );
  }

    
  HRESULT saveAsXMLData (
          _bstr_t filename,
          struct Excel::XmlMap * map )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook-> SaveAsXMLData (
            filename,
            map ))) {
      throw hr;
    }
    return hr;
  }

    
  HRESULT toggleFormsDesign ( )
  {
    HRESULT hr = S_OK; 
    if (FAILED(hr = workBook->ToggleFormsDesign ( ))) {
      throw hr;
    }
    return hr;
  }

};

}
