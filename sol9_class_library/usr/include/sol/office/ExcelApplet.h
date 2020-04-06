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
 *  ExcelApplet.h
 *
 *****************************************************************************/

//2010/04/08
//2010/05/05 Added a lot of public methods.

#pragma once

#include <sol/office/OfficeApplet.h>

//2015/12/25
#ifndef WIN64
#ifdef OFFICE2013
#import "C:\Program Files (x86)\Microsoft Office\OFFICE15\EXCEL.EXE" \
  rename("DocumentProperties","DocumentPropertiesEXL") \
  rename("RGB","RBGEXL") \
  rename("DialogBox","DialogBoxEXL") \
  rename("CopyFile","CopyFileEXL") \
  rename("ReplaceText","ReplaceTextEXL") \
  rename("FindText","FindTextEXL") \
  rename("ExitWindows","_ExitWindowsX") \
  exclude("IFont", "IPicture")

#elif OFFICE2010
#import "C:\Program Files (x86)\Microsoft Office\OFFICE14\EXCEL.EXE"  \
  rename("DocumentProperties","DocumentPropertiesEXL") \
  rename("RGB","RBGEXL") \
  rename("DialogBox","DialogBoxEXL") \
  rename("CopyFile","CopyFileEXL") \
  rename("ReplaceText","ReplaceTextEXL") \
  rename("FindText","FindTextEXL") \
  rename("ExitWindows","_ExitWindowsX") \
  exclude("IFont", "IPicture")


#else
#import "C:\Program Files (x86)\Microsoft Office\OFFICE12\EXCEL.EXE" \
  rename("DocumentProperties","DocumentPropertiesEXL") \
  rename("RGB","RBGEXL") \
  rename("DialogBox","DialogBoxEXL") \
  rename("CopyFile","CopyFileEXL") \
  rename("ReplaceText","ReplaceTextEXL") \
  rename("FindText","FindTextEXL") \
  rename("ExitWindows","_ExitWindowsX") \
  exclude("IFont", "IPicture")

#endif

#else
#ifdef OFFICE2013
#import "C:\Program Files\Microsoft Office\OFFICE15\EXCEL.EXE" \
  rename("DocumentProperties","DocumentPropertiesEXL") \
  rename("RGB","RBGEXL") \
  rename("DialogBox","DialogBoxEXL") \
  rename("CopyFile","CopyFileEXL") \
  rename("ReplaceText","ReplaceTextEXL") \
  rename("FindText","FindTextEXL") \
  rename("ExitWindows","_ExitWindowsX") \
  exclude("IFont", "IPicture")

#elif OFFICE2010
#import "C:\Program Files\Microsoft Office\OFFICE14\EXCEL.EXE" \
  rename("DocumentProperties","DocumentPropertiesEXL") \
  rename("RGB","RBGEXL") \
  rename("DialogBox","DialogBoxEXL") \
  rename("CopyFile","CopyFileEXL") \
  rename("ReplaceText","ReplaceTextEXL") \
  rename("FindText","FindTextEXL") \
  rename("ExitWindows","_ExitWindowsX") \
  exclude("IFont", "IPicture")

#else
#import "C:\Program Files\Microsoft Office\OFFICE12\EXCEL.EXE" \
  rename("DocumentProperties","DocumentPropertiesEXL") \
  rename("RGB","RBGEXL") \
  rename("DialogBox","DialogBoxEXL") \
  rename("CopyFile","CopyFileEXL") \
  rename("ReplaceText","ReplaceTextEXL") \
  rename("FindText","FindTextEXL") \
  rename("ExitWindows","_ExitWindowsX") \
  exclude("IFont", "IPicture")

#endif

#endif

namespace SOL {

class ExcelApplet: public OfficeApplet {

private:
  Excel::_ApplicationPtr excel;

private:
  Excel::WorkbooksPtr workBooks;

private:
  bool isCreated;

public:
  ExcelApplet()
  :excel(NULL),
  workBooks(NULL),
  isCreated(false)
  {
    IDispatch* pDisp = NULL;
    const wchar_t* application = L"Excel.Application";

    if (getActiveObject(application, &pDisp)) {
      this->excel = pDisp;    
      printf( "ExcelApplet#ExcelApplet,1,Found an active Excel object\n");
    } else {
      HRESULT hr= this->excel.CreateInstance(application);
      if (FAILED(hr)) {
        throw hr;
      } else {
        printf( "ExcelApplet#ExcelApplet,2,Created an Excel object\n");
        isCreated = true;
      }
    }

    if (this->excel) {
      this->workBooks = excel->Workbooks;
    }
  }

public:
  ~ExcelApplet()
  {
    if (this->excel) {
      if (this->workBooks) {
        int count = this->workBooks->GetCount();
        if (count == 0) {
          if (isCreated) {
            workBooks = NULL;    
            this->excel->Quit();
          }
        }
        this-> workBooks = NULL;
        this->excel = NULL;
      }
    }
  }

public:
  Excel::_WorkbookPtr open(const BSTR docName, bool visible=false)
  {

    if (isCreated) {
      if (visible==false) {
        this->excel->PutVisible(0, VARIANT_FALSE);
      }
      else {
        this->excel->PutVisible(0, VARIANT_TRUE);
      }
    }
  
    Excel::_WorkbookPtr workBook = NULL;

    try {
      workBook = this->workBooks->Open(docName, &vtMissing, &vtMissing, &vtMissing,
        &vtMissing, &vtMissing, &vtMissing, &vtMissing, 
        &vtMissing, &vtMissing, &vtMissing, &vtMissing, 
        &vtMissing, &vtMissing, &vtMissing, 0);
    } catch (...) {

    }

    return workBook;
  }


  //2010/05/04
public:
  Excel::_ApplicationPtr getApplication ( )  
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->GetApplication ( )) ){
      throw hr;
    }
    return hr;
  }

  enum Excel::XlCreator getCreator ( )
  {
    return excel->GetCreator ( );
  }
    
  Excel::_ApplicationPtr getParent ( )
  {
    return excel->GetParent ( );
  }
    
  Excel::RangePtr getActiveCell ( )
  {
    return excel->GetActiveCell ( );
  }
  
  Excel::_ChartPtr getActiveChart ( )
  {
    return excel->GetActiveChart ( );
  }
    
  Excel::DialogSheetPtr getActiveDialog ( )
  {
    return excel->GetActiveDialog ( );
  }
    
  Excel::MenuBarPtr getActiveMenuBar ( )
  {
    return excel->GetActiveMenuBar ( );
  }
    
  _bstr_t getActivePrinter (
          long lcid = 0 )
  {
    return excel->GetActivePrinter (
            lcid );
  }
    
  void putActivePrinter (
          long lcid,
          _bstr_t rhs )
  {
      excel->PutActivePrinter (
            lcid,
            rhs );
  }
    
  IDispatchPtr getActiveSheet ( )
  {
    return excel->GetActiveSheet ( );
  }
    
  Excel::WindowPtr getActiveWindow ( )
  {
    return excel->GetActiveWindow ( );
  }
    
  Excel::_WorkbookPtr getActiveWorkbook ( )
  {
    return excel->GetActiveWorkbook ( );
  }
    
  Excel::AddInsPtr getAddIns ( )
  {
    return excel->GetAddIns ( );
  }
    
  Office::AssistantPtr getAssistant ( )
  {
    return excel->GetAssistant ( );
  }
    
  HRESULT calculate (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Calculate (
            lcid )) ){
      throw hr;
    }
    return hr;
      
  }

  Excel::RangePtr getCells ( )
  {
    return excel->GetCells ( );
  }
    
  Excel::SheetsPtr getCharts ( )
  {
    return excel->GetCharts ( );
  }
    
  Excel::RangePtr getColumns ( )
  {
    return excel->GetColumns ( );
  }
    
  Office::_CommandBarsPtr getCommandBars ( )
  {
    return excel->GetCommandBars ( );
  }
    
  long getDDEAppReturnCode (
          long lcid = 0 )
  {
    return excel->GetDDEAppReturnCode (
            lcid );
  }
    
  HRESULT ddeExecute (
          long channel,
          _bstr_t string,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DDEExecute (
            channel,
            string,
            lcid )) ){
      throw hr;
    }
    return hr;
      
  }
    
  long ddeInitiate (
          _bstr_t app,
          _bstr_t topic,
          long lcid = 0 )
  {
    return excel->DDEInitiate (
            app,
            topic,
            lcid );
  }
    
  HRESULT ddePoke (
          long channel,
          const _variant_t & item,
          const _variant_t & data,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DDEPoke (
            channel,
            item,
            data,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  _variant_t ddeRequest (
          long channel,
          _bstr_t item,
          long lcid = 0 )
  {
    return excel->DDERequest (
            channel,
            item,
            lcid );
  }
    
  HRESULT ddeTerminate (
          long channel,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DDETerminate (
            channel,
            lcid )) ){
      throw hr;
    }
    return hr;
      
  }
    
  Excel::SheetsPtr getDialogSheets ( )
  {
    return excel->GetDialogSheets ( );
  }
    
  _variant_t evaluate (
          const _variant_t & name,
          long lcid = 0 )
  {
    return excel->Evaluate (
            name,
            lcid );
  }
        
  _variant_t executeExcel4Macro (
          _bstr_t string,
          long lcid = 0 )
  {
    return excel->ExecuteExcel4Macro (
            string,
            lcid );
  }
    
  Excel::RangePtr intersect (
          struct Excel::Range * arg1,
          struct Excel::Range * arg2,
          const _variant_t & arg3 = vtMissing,
          const _variant_t & arg4 = vtMissing,
          const _variant_t & arg5 = vtMissing,
          const _variant_t & arg6 = vtMissing,
          const _variant_t & arg7 = vtMissing,
          const _variant_t & arg8 = vtMissing,
          const _variant_t & arg9 = vtMissing,
          const _variant_t & arg10 = vtMissing,
          const _variant_t & arg11 = vtMissing,
          const _variant_t & arg12 = vtMissing,
          const _variant_t & arg13 = vtMissing,
          const _variant_t & arg14 = vtMissing,
          const _variant_t & arg15 = vtMissing,
          const _variant_t & arg16 = vtMissing,
          const _variant_t & arg17 = vtMissing,
          const _variant_t & arg18 = vtMissing,
          const _variant_t & arg19 = vtMissing,
          const _variant_t & arg20 = vtMissing,
          const _variant_t & arg21 = vtMissing,
          const _variant_t & arg22 = vtMissing,
          const _variant_t & arg23 = vtMissing,
          const _variant_t & arg24 = vtMissing,
          const _variant_t & arg25 = vtMissing,
          const _variant_t & arg26 = vtMissing,
          const _variant_t & arg27 = vtMissing,
          const _variant_t & arg28 = vtMissing,
          const _variant_t & arg29 = vtMissing,
          const _variant_t & arg30 = vtMissing,
          long lcid = 0 )
  {
    return excel->Intersect (
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6,
            arg7,
            arg8,
            arg9,
            arg10,
            arg11,
            arg12,
            arg13,
            arg14,
            arg15,
            arg16,
            arg17,
            arg18,
            arg19,
            arg20,
            arg21,
            arg22,
            arg23,
            arg24,
            arg25,
            arg26,
            arg27,
            arg28,
            arg29,
            arg30,
            lcid );
  }
    
  Excel::MenuBarsPtr getMenuBars ( )
  {
    return excel->GetMenuBars ( );
  }
    
  Excel::ModulesPtr getModules ( )
  {
    return excel->GetModules ( );
  }
    
  Excel::NamesPtr getNames ( )
  {
    return excel->GetNames ( );
  }
    
  Excel::RangePtr getRange (
          const _variant_t & cell1,
          const _variant_t & cell2 = vtMissing )
  {
    return excel->GetRange (
            cell1,
            cell2 );
  }
    
  Excel::RangePtr getRows ( )
  {
    return excel->GetRows ( );
  }
    
  _variant_t run (
          const _variant_t & macro = vtMissing,
          const _variant_t & arg1 = vtMissing,
          const _variant_t & arg2 = vtMissing,
          const _variant_t & arg3 = vtMissing,
          const _variant_t & arg4 = vtMissing,
          const _variant_t & arg5 = vtMissing,
          const _variant_t & arg6 = vtMissing,
          const _variant_t & arg7 = vtMissing,
          const _variant_t & arg8 = vtMissing,
          const _variant_t & arg9 = vtMissing,
          const _variant_t & arg10 = vtMissing,
          const _variant_t & arg11 = vtMissing,
          const _variant_t & arg12 = vtMissing,
          const _variant_t & arg13 = vtMissing,
          const _variant_t & arg14 = vtMissing,
          const _variant_t & arg15 = vtMissing,
          const _variant_t & arg16 = vtMissing,
          const _variant_t & arg17 = vtMissing,
          const _variant_t & arg18 = vtMissing,
          const _variant_t & arg19 = vtMissing,
          const _variant_t & arg20 = vtMissing,
          const _variant_t & arg21 = vtMissing,
          const _variant_t & arg22 = vtMissing,
          const _variant_t & arg23 = vtMissing,
          const _variant_t & arg24 = vtMissing,
          const _variant_t & arg25 = vtMissing,
          const _variant_t & arg26 = vtMissing,
          const _variant_t & arg27 = vtMissing,
          const _variant_t & arg28 = vtMissing,
          const _variant_t & arg29 = vtMissing,
          const _variant_t & arg30 = vtMissing )
  {
    return excel->Run (
            macro,
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6,
            arg7,
            arg8,
            arg9,
            arg10,
            arg11,
            arg12,
            arg13,
            arg14,
            arg15,
            arg16,
            arg17,
            arg18,
            arg19,
            arg20,
            arg21,
            arg22,
            arg23,
            arg24,
            arg25,
            arg26,
            arg27,
            arg28,
            arg29,
            arg30 );
  
  }
    
  _variant_t run2 (
          const _variant_t & macro = vtMissing,
          const _variant_t & arg1 = vtMissing,
          const _variant_t & arg2 = vtMissing,
          const _variant_t & arg3 = vtMissing,
          const _variant_t & arg4 = vtMissing,
          const _variant_t & arg5 = vtMissing,
          const _variant_t & arg6 = vtMissing,
          const _variant_t & arg7 = vtMissing,
          const _variant_t & arg8 = vtMissing,
          const _variant_t & arg9 = vtMissing,
          const _variant_t & arg10 = vtMissing,
          const _variant_t & arg11 = vtMissing,
          const _variant_t & arg12 = vtMissing,
          const _variant_t & arg13 = vtMissing,
          const _variant_t & arg14 = vtMissing,
          const _variant_t & arg15 = vtMissing,
          const _variant_t & arg16 = vtMissing,
          const _variant_t & arg17 = vtMissing,
          const _variant_t & arg18 = vtMissing,
          const _variant_t & arg19 = vtMissing,
          const _variant_t & arg20 = vtMissing,
          const _variant_t & arg21 = vtMissing,
          const _variant_t & arg22 = vtMissing,
          const _variant_t & arg23 = vtMissing,
          const _variant_t & arg24 = vtMissing,
          const _variant_t & arg25 = vtMissing,
          const _variant_t & arg26 = vtMissing,
          const _variant_t & arg27 = vtMissing,
          const _variant_t & arg28 = vtMissing,
          const _variant_t & arg29 = vtMissing,
          const _variant_t & arg30 = vtMissing,
          long lcid = 0 )
  {
    return excel->_Run2 (
            macro,
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6,
            arg7,
            arg8,
            arg9,
            arg10,
            arg11,
            arg12,
            arg13,
            arg14,
            arg15,
            arg16,
            arg17,
            arg18,
            arg19,
            arg20,
            arg21,
            arg22,
            arg23,
            arg24,
            arg25,
            arg26,
            arg27,
            arg28,
            arg29,
            arg30,
            lcid );
  }
    
  IDispatchPtr getSelection (
          long lcid = 0 )
  {
    return excel->GetSelection (
            lcid );
  }
    
  HRESULT sendKeys (
          const _variant_t & keys,
          const _variant_t & wait = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->SendKeys (
            keys,
            wait,
            lcid )) ){
      throw hr;
    }
    return hr;
      
  }
    
  Excel::SheetsPtr getSheets ( )
  {
    return excel->GetSheets ( );
  }
    
  Excel::MenuPtr getShortcutMenus (
          long index )
  {
    return excel->GetShortcutMenus (
            index );
  }
    
  Excel::_WorkbookPtr getThisWorkbook (
          long lcid = 0 )
  {
    return excel->GetThisWorkbook (
            lcid );
  }
    
  Excel::ToolbarsPtr getToolbars ( )
  {
    return excel->GetToolbars ( );
  }
    
  Excel::RangePtr doUnion (
          struct Excel::Range * arg1,
          struct Excel::Range * arg2,
          const _variant_t & arg3 = vtMissing,
          const _variant_t & arg4 = vtMissing,
          const _variant_t & arg5 = vtMissing,
          const _variant_t & arg6 = vtMissing,
          const _variant_t & arg7 = vtMissing,
          const _variant_t & arg8 = vtMissing,
          const _variant_t & arg9 = vtMissing,
          const _variant_t & arg10 = vtMissing,
          const _variant_t & arg11 = vtMissing,
          const _variant_t & arg12 = vtMissing,
          const _variant_t & arg13 = vtMissing,
          const _variant_t & arg14 = vtMissing,
          const _variant_t & arg15 = vtMissing,
          const _variant_t & arg16 = vtMissing,
          const _variant_t & arg17 = vtMissing,
          const _variant_t & arg18 = vtMissing,
          const _variant_t & arg19 = vtMissing,
          const _variant_t & arg20 = vtMissing,
          const _variant_t & arg21 = vtMissing,
          const _variant_t & arg22 = vtMissing,
          const _variant_t & arg23 = vtMissing,
          const _variant_t & arg24 = vtMissing,
          const _variant_t & arg25 = vtMissing,
          const _variant_t & arg26 = vtMissing,
          const _variant_t & arg27 = vtMissing,
          const _variant_t & arg28 = vtMissing,
          const _variant_t & arg29 = vtMissing,
          const _variant_t & arg30 = vtMissing,
          long lcid = 0 )
  {
    return excel->Union (
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6,
            arg7,
            arg8,
            arg9,
            arg10,
            arg11,
            arg12,
            arg13,
            arg14,
            arg15,
            arg16,
            arg17,
            arg18,
            arg19,
            arg20,
            arg21,
            arg22,
            arg23,
            arg24,
            arg25,
            arg26,
            arg27,
            arg28,
            arg29,
            arg30,
            lcid  );
  }
    
  Excel::WindowsPtr getWindows ( )
  {
    return excel->GetWindows ( );
  }
    
  Excel::WorkbooksPtr getWorkbooks ( )
  {
    return excel->GetWorkbooks ( );
  }
    
  Excel::WorksheetFunctionPtr getWorksheetFunction ( )
  {
    return excel->GetWorksheetFunction ( );
  }
    
  Excel::SheetsPtr getWorksheets ( )
  {
    return excel->GetWorksheets ( );
  }
    
  Excel::SheetsPtr getExcel4IntlMacroSheets ( )
  {
    return excel->GetExcel4IntlMacroSheets ( );
  }
    
  Excel::SheetsPtr getExcel4MacroSheets ( )
  {
    return excel->GetExcel4MacroSheets ( );
  }
    
  HRESULT activateMicrosoftApp (
          enum Excel::XlMSApplication index,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->ActivateMicrosoftApp (
            index,
            lcid )) ){
      throw hr;
    }
    return hr;
      }
    
  HRESULT addChartAutoFormat (
          const _variant_t & chart,
          _bstr_t name,
          const _variant_t & description = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->AddChartAutoFormat (
            chart,
            name,
            description,
            lcid )) ){
      throw hr;
    }
    return hr;
      }
    
  HRESULT addCustomList (
          const _variant_t & listArray,
          const _variant_t & byRow = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->AddCustomList (
            listArray,
            byRow,
            lcid )) ){
      throw hr;
    }
    return hr;
      }
    

  VARIANT_BOOL getAlertBeforeOverwriting (
          long lcid = 0 )
  {
    return excel->GetAlertBeforeOverwriting (
            lcid );
  }
    
  void putAlertBeforeOverwriting (
          long lcid,
          VARIANT_BOOL rhs )
  {
     excel->PutAlertBeforeOverwriting (
            lcid,
            rhs );
      }
    
  _bstr_t getAltStartupPath (
          long lcid = 0 )
  {
    return excel->GetAltStartupPath (
            lcid );
  }
    
  void putAltStartupPath (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutAltStartupPath (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getAskToUpdateLinks (
          long lcid = 0 )
  {
    return excel->GetAskToUpdateLinks (
            lcid );
  }
    
  void putAskToUpdateLinks (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutAskToUpdateLinks (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getEnableAnimations (
          long lcid = 0 )
  {
    return excel->GetEnableAnimations (
            lcid );
  }
    
  void putEnableAnimations (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutEnableAnimations (
            lcid,
            rhs );
  }
    
  Excel::AutoCorrectPtr getAutoCorrect ( )
  {
    return excel->GetAutoCorrect ( );
  }
    
  long getBuild (
          long lcid = 0 )
  {
    return excel->GetBuild (
            lcid );
  }
    
  VARIANT_BOOL getCalculateBeforeSave (
          long lcid = 0 )
  {
    return excel->GetCalculateBeforeSave (
            lcid );
  }
    
  void putCalculateBeforeSave (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutCalculateBeforeSave (
            lcid,
            rhs );
  }
    
  enum Excel::XlCalculation getCalculation (
          long lcid = 0 )
  {
    return excel->GetCalculation (
            lcid );
  }
    
  void putCalculation (
          long lcid,
          enum Excel::XlCalculation rhs )
  {
    excel->PutCalculation (
            lcid,
            rhs );
  }
    
  _variant_t getCaller (
          const _variant_t & index = vtMissing,
          long lcid = 0 )
  {
    return excel->GetCaller (
            index,
            lcid );
  }
    
  VARIANT_BOOL getCanPlaySounds (
          long lcid = 0 )
  {
    return excel->GetCanPlaySounds (
            lcid );
  }

      VARIANT_BOOL getCanRecordSounds (
          long lcid = 0 )
  {
    return excel->GetCanRecordSounds (
            lcid );
  }
    
  _bstr_t getCaption ( )
  {
    return excel->GetCaption ( );
  }
    
  void putCaption (
          _bstr_t rhs )
  {
    excel->PutCaption (
            rhs );
  }
    
  VARIANT_BOOL getCellDragAndDrop (
          long lcid = 0 )
  {
    return excel->GetCellDragAndDrop (
            lcid );
  }
    
  void putCellDragAndDrop (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutCellDragAndDrop (
            lcid,
            rhs );
  }
    
  double centimetersToPoints (
          double centimeters,
          long lcid = 0 )
  {
    return excel->CentimetersToPoints (
            centimeters,
            lcid );
  }
    
  VARIANT_BOOL CheckSpelling (
          _bstr_t word,
          const _variant_t & customDictionary = vtMissing,
          const _variant_t & ignoreUppercase = vtMissing,
          long lcid = 0 )
  {
    return excel->CheckSpelling (
            word,
            customDictionary,
            ignoreUppercase,
            lcid );
  }
    
  _variant_t getClipboardFormats (
          const _variant_t & index = vtMissing,
          long lcid = 0 )
  {
    return excel->GetClipboardFormats (
            index,
            lcid );
  }
    
  VARIANT_BOOL getDisplayClipboardWindow (
          long lcid = 0 )
  {
    return excel->GetDisplayClipboardWindow (
            lcid );
  }
    
  void putDisplayClipboardWindow (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayClipboardWindow (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getColorButtons ( )
  {
    return excel->GetColorButtons ( );

  }
    
  void putColorButtons (
          VARIANT_BOOL rhs )
  {
    return excel->PutColorButtons (
            rhs );
  }
    
  enum Excel::XlCommandUnderlines getCommandUnderlines (
          long lcid = 0 )
  {
    return excel->GetCommandUnderlines (
            lcid );
  }
    
  void putCommandUnderlines (
          long lcid,
          enum Excel::XlCommandUnderlines rhs )
  {
    excel->PutCommandUnderlines (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getConstrainNumeric (
          long lcid = 0 )
  {
    return excel->GetConstrainNumeric (
            lcid );
  }
    
  void putConstrainNumeric (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutConstrainNumeric (
            lcid,
            rhs );
  }
    
  _variant_t convertFormula (
          const _variant_t & formula,
          enum Excel::XlReferenceStyle fromReferenceStyle,
          const _variant_t & toReferenceStyle = vtMissing,
          const _variant_t & toAbsolute = vtMissing,
          const _variant_t & relativeTo = vtMissing,
          long lcid = 0 )
  {
    return excel->ConvertFormula (
            formula,
            fromReferenceStyle,
            toReferenceStyle,
            toAbsolute,
            relativeTo,
            lcid );
  }
    
  VARIANT_BOOL getCopyObjectsWithCells (
          long lcid = 0 )
  {
    return excel->GetCopyObjectsWithCells (
            lcid );
  }
    
  void putCopyObjectsWithCells (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutCopyObjectsWithCells (
            lcid,
            rhs );
  }
    
  enum Excel::XlMousePointer getCursor (
          long lcid = 0 )
  {
    return excel->GetCursor (
            lcid );
  }
    
  void putCursor (
          long lcid,
          enum Excel::XlMousePointer rhs )
  {
    excel->PutCursor (
            lcid,
            rhs );
  }
    
  long getCustomListCount (
          long lcid = 0 )
  {
    return excel->GetCustomListCount (
            lcid );
  }
    
  enum Excel::XlCutCopyMode getCutCopyMode (
          long lcid = 0 )
  {
    return excel->GetCutCopyMode (
            lcid );
  }
    
  void putCutCopyMode (
          long lcid,
          enum Excel::XlCutCopyMode rhs)
  {
    excel->PutCutCopyMode (
            lcid,
            rhs);
  }
    
  long getDataEntryMode (
          long lcid = 0 )
  {
    return excel->GetDataEntryMode (
            lcid );
  }
    
  void putDataEntryMode (
          long lcid,
          long rhs )
  {
    excel->PutDataEntryMode (
            lcid,
            rhs );
  }
    
  _bstr_t getDefault ( )
  {
    return excel->Get_Default ( );
  }

    
  _bstr_t getDefaultFilePath (
          long lcid = 0 )
  {
    return excel->GetDefaultFilePath (
            lcid );
  }

    
  void putDefaultFilePath (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutDefaultFilePath (
            lcid,
            rhs );
  }

    
  HRESULT deleteChartAutoFormat (
          _bstr_t name,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DeleteChartAutoFormat (
            name,
            lcid )) ){
      throw hr;
    }
    return hr;
      }

    
  HRESULT deleteCustomList (
          long listNum,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DeleteCustomList (
            listNum,
            lcid )) ){
      throw hr;
    }
    return hr;
      }
    
  Excel::DialogsPtr getDialogs ( )
  {
    return excel->GetDialogs ( );
  }
    
  VARIANT_BOOL getDisplayAlerts (
          long lcid = 0 )
  {
    return excel->GetDisplayAlerts (
            lcid );
  }
    
  void putDisplayAlerts (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayAlerts (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getDisplayFormulaBar (
          long lcid = 0 )
  {
    return excel->GetDisplayFormulaBar (
            lcid );
  }
    
  void putDisplayFormulaBar (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayFormulaBar (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getDisplayFullScreen (
          long lcid = 0 )
  {
    return excel->GetDisplayFullScreen (
            lcid );
  }
    
  void putDisplayFullScreen (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayFullScreen (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getDisplayNoteIndicator ( )
  {
    return excel->GetDisplayNoteIndicator ( );
  }
    
  void putDisplayNoteIndicator (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayNoteIndicator (
            rhs );
  }
    
  enum Excel::XlCommentDisplayMode getDisplayCommentIndicator ( )
  {
    return excel->GetDisplayCommentIndicator ( );
  }
    
  void PutDisplayCommentIndicator (
          enum Excel::XlCommentDisplayMode rhs )
  {
    excel->PutDisplayCommentIndicator (
            rhs );
  }
    
  VARIANT_BOOL getDisplayExcel4Menus (
          long lcid = 0 )
  {
    return excel->GetDisplayExcel4Menus (
            lcid );
  }
    
  void putDisplayExcel4Menus (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayExcel4Menus (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getDisplayRecentFiles ( )
  {
    return excel->GetDisplayRecentFiles ( );
  }
    
  void putDisplayRecentFiles (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayRecentFiles (
            rhs );
  }
    
  VARIANT_BOOL getDisplayScrollBars (
          long lcid = 0 )
  {
    return excel->GetDisplayScrollBars (
            lcid );
  }
    
  void putDisplayScrollBars (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayScrollBars (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getDisplayStatusBar (
          long lcid = 0 )
  {
    return excel->GetDisplayStatusBar (
            lcid );
  }
    
  void putDisplayStatusBar (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayStatusBar (
            lcid,
            rhs );
  }
    
  HRESULT doubleClick (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DoubleClick (
            lcid )) ){
      throw hr;
    }
    return hr;
    }
    
  VARIANT_BOOL getEditDirectlyInCell (
          long lcid = 0 )
  {
    return excel->GetEditDirectlyInCell (
            lcid );
  }
    
  void putEditDirectlyInCell (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutEditDirectlyInCell (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getEnableAutoComplete ( )
  {
    return excel->GetEnableAutoComplete ( );
  }
    
  void putEnableAutoComplete (
          VARIANT_BOOL rhs )
  {
    excel->PutEnableAutoComplete (
            rhs );
  }
    
  enum Excel::XlEnableCancelKey getEnableCancelKey (
          long lcid = 0 )
  {
    return excel->GetEnableCancelKey (
            lcid );
  }
    
  void putEnableCancelKey (
          long lcid,
          enum Excel::XlEnableCancelKey rhs )
  {
    excel->PutEnableCancelKey (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getEnableSound ( )
  {
    return excel->GetEnableSound ( );
  }
    
  void putEnableSound (
          VARIANT_BOOL rhs )
  {
    excel->PutEnableSound (
            rhs );
  }
    
  VARIANT_BOOL getEnableTipWizard (
          long lcid = 0 )
  {
    return excel->GetEnableTipWizard (
            lcid );
  }
    
  void putEnableTipWizard (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutEnableTipWizard (
            lcid,
            rhs );
  }
    
  _variant_t getFileConverters (
          const _variant_t & index1 = vtMissing,
          const _variant_t & index2 = vtMissing,
          long lcid = 0 )
  {
    return excel->GetFileConverters (
            index1,
            index2,
            lcid );
  }
    
  Office::FileSearchPtr getFileSearch ( )
  {
    return excel->GetFileSearch ( );
  }
    
  Office::IFindPtr getFileFind ( )
  {
    return excel->GetFileFind ( );
  }
    /*
  HRESULT findFile (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->_FindFile (
            lcid )) ){
      throw hr;
    }
    return hr;
      }
    */
  VARIANT_BOOL getFixedDecimal (
          long lcid = 0 )
  {
    return excel->GetFixedDecimal (
            lcid );
  }
    
  void putFixedDecimal (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutFixedDecimal (
            lcid,
            rhs );
  }
    
  long getFixedDecimalPlaces (
          long lcid = 0 )
  {
    return excel->GetFixedDecimalPlaces (
            lcid );
  }
    
  void putFixedDecimalPlaces (
          long lcid,
          long rhs )
  {
    excel->PutFixedDecimalPlaces (
            lcid,
            rhs );
  }
    
  _variant_t getCustomListContents (
          long listNum,
          long lcid = 0 )
  {
    return excel->GetCustomListContents (
            listNum,
            lcid );
  }
    
  long getCustomListNum (
          const _variant_t & listArray,
          long lcid = 0 )
  {
    return excel->GetCustomListNum (
            listArray,
            lcid = 0 );
  }
    
  _variant_t getOpenFilename (
          const _variant_t & fileFilter = vtMissing,
          const _variant_t & filterIndex = vtMissing,
          const _variant_t & title = vtMissing,
          const _variant_t & buttonText = vtMissing,
          const _variant_t & multiSelect = vtMissing,
          long lcid = 0 )
  {
    return excel->GetOpenFilename (
            fileFilter,
            filterIndex,
            title,
            buttonText,
            multiSelect,
            lcid );
  }
    
  _variant_t getSaveAsFilename (
          const _variant_t & initialFilename = vtMissing,
          const _variant_t & fileFilter = vtMissing,
          const _variant_t & filterIndex = vtMissing,
          const _variant_t & title = vtMissing,
          const _variant_t & buttonText = vtMissing,
          long lcid = 0 )
  {
    return excel->GetSaveAsFilename (
            initialFilename,
            fileFilter,
            filterIndex,
            title,
            buttonText,
            lcid );
  }
    

  HRESULT _goto (
          const _variant_t & reference = vtMissing,
          const _variant_t & scroll = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Goto (
            reference,
            scroll,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  double getHeight (
          long lcid = 0 )
  {
    return excel->GetHeight (
            lcid );
  }
    
  void putHeight (
          long lcid,
          double rhs )
  {
    excel->PutHeight (
            lcid,
            rhs );
  }
    
  HRESULT help (
          const _variant_t & helpFile = vtMissing,
          const _variant_t & helpContextID = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Help (
            helpFile,
            helpContextID,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getIgnoreRemoteRequests (
          long lcid = 0 )
  {
    return excel->GetIgnoreRemoteRequests (
            lcid );
  }
    
  void putIgnoreRemoteRequests (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutIgnoreRemoteRequests (
            lcid,
            rhs );
  }
    
  double inchesToPoints (
          double inches,
          long lcid = 0 )
  {
    return excel->InchesToPoints (
            inches,
            lcid );
  }
    
  _variant_t inputBox (
          _bstr_t prompt,
      const _variant_t & title = vtMissing,
          const _variant_t & default = vtMissing,
          const _variant_t & left = vtMissing,
          const _variant_t & top = vtMissing,
          const _variant_t & helpFile = vtMissing,
          const _variant_t & helpContextID = vtMissing,
          const _variant_t & type = vtMissing,
          long lcid = 0 )
  {
    return excel->InputBox (
            prompt,
      title,
            default,
            left,
            top,
            helpFile,
            helpContextID,
            type,
            lcid );
  }
    
  VARIANT_BOOL getInteractive (
          long lcid = 0 )
  {
    return excel->GetInteractive (
            lcid );
  }
    
  void putInteractive (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutInteractive (
            lcid,
            rhs );
  }
    
  _variant_t getInternational (
          const _variant_t & index = vtMissing,
          long lcid = 0 )
  {
    return excel->GetInternational (
            index,
            lcid );
  }

  VARIANT_BOOL getIteration (
          long lcid = 0 )
  {
    return excel->GetIteration (
            lcid );
  }
    
  void putIteration (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutIteration (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getLargeButtons ( )
  {
    return excel->GetLargeButtons ( );
  }
    
  void putLargeButtons (
          VARIANT_BOOL rhs )
  {
    return excel->PutLargeButtons (
            rhs );
  }
    
  double getLeft (
          long lcid = 0 )
  {
    return excel->GetLeft (
            lcid );
  }
    
  void putLeft (
          long lcid,
          double rhs )
  {
    excel->PutLeft (
            lcid,
            rhs );
  }
    
  _bstr_t getLibraryPath (
          long lcid = 0 )
  {
    return excel->GetLibraryPath (
            lcid );
  }
    
  HRESULT macroOptions (
          const _variant_t & macro = vtMissing,
          const _variant_t & description = vtMissing,
          const _variant_t & hasMenu = vtMissing,
          const _variant_t & menuText = vtMissing,
          const _variant_t & hasShortcutKey = vtMissing,
          const _variant_t & shortcutKey = vtMissing,
          const _variant_t & category = vtMissing,
          const _variant_t & statusBar = vtMissing,
          const _variant_t & helpContextID = vtMissing,
          const _variant_t & helpFile = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->MacroOptions (
            macro,
            description,
            hasMenu,
            menuText,
            hasShortcutKey,
            shortcutKey,
            category,
            statusBar,
            helpContextID,
            helpFile,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  HRESULT mailLogoff (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->MailLogoff (
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  HRESULT mailLogon (
          const _variant_t & name = vtMissing,
          const _variant_t & password = vtMissing,
          const _variant_t & downloadNewMail = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->MailLogon (
            name,
            password,
            downloadNewMail,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  _variant_t getMailSession (
          long lcid = 0 )
  {
    return excel->GetMailSession (
            lcid );
  }
    
  enum Excel::XlMailSystem getMailSystem (
          long lcid = 0 )
  {
    return excel->GetMailSystem (
            lcid );
  }
    
  VARIANT_BOOL getMathCoprocessorAvailable (
          long lcid = 0 )
  {
    return excel->GetMathCoprocessorAvailable (
            lcid );
  }
    
  double getMaxChange (
          long lcid = 0 )
  {
    return excel->GetMaxChange (
            lcid );
  }
    
  void putMaxChange (
          long lcid,
          double rhs )
  {
    excel->PutMaxChange (
            lcid,
            rhs );
  }
    
  long getMaxIterations (
          long lcid = 0 )
  {
    return excel->GetMaxIterations (
            lcid );
  }
    
  void putMaxIterations (
          long lcid,
          long rhs )
  {
    excel->PutMaxIterations (
            lcid,
            rhs );
  }
    
  long getMemoryFree (
          long lcid = 0 )
  {
    return excel->GetMemoryFree (
            lcid );
  }
    
  long getMemoryTotal (
          long lcid = 0 )
  {
    return excel->GetMemoryTotal (
            lcid );
  }
    
  long getMemoryUsed (
          long lcid = 0 )
  {
    return excel-> GetMemoryUsed (
            lcid );
  }
    
  VARIANT_BOOL getMouseAvailable (
          long lcid = 0 )
  {
    return excel->GetMouseAvailable (
            lcid );
  }
    
  VARIANT_BOOL getMoveAfterReturn (
          long lcid = 0 )
  {
    return excel->GetMoveAfterReturn (
            lcid );
  }
    
  void putMoveAfterReturn (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutMoveAfterReturn (
            lcid,
            rhs );
  }
    
  enum Excel::XlDirection getMoveAfterReturnDirection (
          long lcid = 0 )
  {
    return excel->GetMoveAfterReturnDirection (
            lcid );
  }
    
  void putMoveAfterReturnDirection (
          long lcid,
          enum Excel::XlDirection rhs )
  {
    excel->PutMoveAfterReturnDirection (
            lcid,
            rhs );
  }
    
  Excel::RecentFilesPtr getRecentFiles ( )
  {
    return excel->GetRecentFiles ( );
  }
        
  _bstr_t getName ( )
  {
    return excel->GetName ( );
  }
  
  Excel::_WorkbookPtr NextLetter (
          long lcid = 0 )
  {
    return excel->NextLetter (
            lcid );
  }
    
  _bstr_t getNetworkTemplatesPath (
          long lcid = 0 )
  {
    return excel->GetNetworkTemplatesPath (
            lcid );
  }
    
  Excel::ODBCErrorsPtr getODBCErrors ( )
  {
    return excel->GetODBCErrors ( );
  }
    
  long getODBCTimeout ( )
  {
    return excel->GetODBCTimeout ( );
  }
    
  void putODBCTimeout (
          long rhs )
  {
    excel->PutODBCTimeout (
            rhs );
  }
    
  _bstr_t getOnCalculate (
          long lcid = 0 )
  {
    return excel->GetOnCalculate (
            lcid );
  }
    
  void putOnCalculate (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnCalculate (
            lcid,
            rhs );
  }
    
  _bstr_t getOnData (
          long lcid = 0 )
  {
    return excel->GetOnData (
            lcid );
  }
    
  void putOnData (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnData (
            lcid,
            rhs );
  }
    
  _bstr_t getOnDoubleClick (
          long lcid = 0 )
  {
    return excel->GetOnDoubleClick (
            lcid );
  }
    
  void putOnDoubleClick (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnDoubleClick (
            lcid,
            rhs );
  }
    
  _bstr_t getOnEntry (
          long lcid = 0 )
  {
    return excel->GetOnEntry (
            lcid );
  }
    
  void putOnEntry (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnEntry (
            lcid,
            rhs );
  }
    
  HRESULT onKey (
          _bstr_t key,
          const _variant_t & procedure = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->OnKey (
            key,
            procedure,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  HRESULT onRepeat (
          _bstr_t text,
          _bstr_t procedure,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->OnRepeat (
            text,
            procedure,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  _bstr_t getOnSheetActivate (
          long lcid = 0 )
  {
    return excel->GetOnSheetActivate (
            lcid );
  }
    
  void putOnSheetActivate (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnSheetActivate (
            lcid,
            rhs );
  }
    
  _bstr_t getOnSheetDeactivate (
          long lcid = 0 )
  {
    return excel->GetOnSheetDeactivate (
            lcid );
  }
    
  void putOnSheetDeactivate (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnSheetDeactivate (
            lcid,
            rhs );
  }
    
  HRESULT onTime (
          const _variant_t & earliestTime,
          _bstr_t procedure,
          const _variant_t & latestTime = vtMissing,
          const _variant_t & schedule = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->OnTime (
            earliestTime,
            procedure,
            latestTime,
            schedule,
            lcid )) ){
      throw hr;
    }
    return hr;
   }
    
  HRESULT onUndo (
          _bstr_t text,
          _bstr_t procedure,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->OnUndo (
            text,
            procedure,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  _bstr_t getOnWindow (
          long lcid = 0 )
  {
    return excel->GetOnWindow (
            lcid );
  }
    
  void putOnWindow (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutOnWindow (
            lcid,
            rhs );
  }
    
  _bstr_t getOperatingSystem (
          long lcid = 0 )
  {
    return excel->GetOperatingSystem (
            lcid );
  }
    
  _bstr_t getOrganizationName (
          long lcid = 0 )
  {
    return excel->GetOrganizationName (
            lcid );
  }
    
  _bstr_t getPath (
          long lcid = 0 )
  {
    return excel->GetPath (
            lcid );
  }
    
  _bstr_t getPathSeparator (
          long lcid = 0 )
  {
    return excel->GetPathSeparator (
            lcid );
  }
    
  _variant_t GetPreviousSelections (
          const _variant_t & index = vtMissing,
          long lcid = 0 )
  {
    return excel->GetPreviousSelections (
            index,
            lcid );
  }
    
  VARIANT_BOOL getPivotTableSelection ( )
  {
    return excel->GetPivotTableSelection ( );
  }
    
  void putPivotTableSelection (
          VARIANT_BOOL rhs )
  {
    excel->PutPivotTableSelection (
            rhs );
  }
    
  VARIANT_BOOL getPromptForSummaryInfo (
          long lcid = 0 )
  {
    return excel->GetPromptForSummaryInfo (
            lcid );
  }
    
  void putPromptForSummaryInfo (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutPromptForSummaryInfo (
            lcid,
            rhs );
  }
    
  HRESULT quit ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Quit ( )) ){
      throw hr;
    }
    return hr;
   }
    
  HRESULT recordMacro (
          const _variant_t & basicCode = vtMissing,
          const _variant_t & xlmCode = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->RecordMacro (
            basicCode,
            xlmCode,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getRecordRelative (
          long lcid = 0 )
  {
    return excel->GetRecordRelative (
            lcid );
  }

  enum Excel::XlReferenceStyle getReferenceStyle (
          long lcid = 0 )
  {
    return excel->GetReferenceStyle (
            lcid );
  }
    
  void putReferenceStyle (
          long lcid,
          enum Excel::XlReferenceStyle rhs )
  {
    excel->PutReferenceStyle (
            lcid,
            rhs );
  }
    
  _variant_t getRegisteredFunctions (
          const _variant_t & index1 = vtMissing,
          const _variant_t & index2 = vtMissing,
          long lcid = 0 )
  {
    return excel->GetRegisteredFunctions (
            index1,
            index2,
            lcid );
  }
    
  VARIANT_BOOL RegisterXLL (
          _bstr_t filename,
          long lcid = 0 )
  {
    return excel->RegisterXLL (
            filename,
            lcid );
  }
    
  HRESULT repeat (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Repeat (
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  HRESULT resetTipWizard (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->ResetTipWizard (
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getRollZoom ( )
  {
    return excel->GetRollZoom ( );
  }
    
  void putRollZoom (
          VARIANT_BOOL rhs )
  {
    excel->PutRollZoom (
            rhs );
  }
    
  HRESULT save (
          const _variant_t & filename = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Save (
            filename,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  HRESULT saveWorkspace (
          const _variant_t & filename = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->SaveWorkspace (
            filename,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getScreenUpdating (
          long lcid = 0 )
  {
    return excel->GetScreenUpdating (
            lcid );
  }
    
  void putScreenUpdating (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutScreenUpdating (
            lcid,
            rhs );
  }
    
  HRESULT setDefaultChart (
          const _variant_t & formatName = vtMissing,
          const _variant_t & gallery = vtMissing )
  {
    HRESULT hr = S_OK;

    if (FAILED(hr = excel->SetDefaultChart (
            formatName,
            gallery ) )){
      throw hr;
    }
    return hr;
  }
    
  long getSheetsInNewWorkbook (
          long lcid = 0 )
  {
    return excel->GetSheetsInNewWorkbook (
            lcid );
  }
    
  void putSheetsInNewWorkbook (
          long lcid,
          long rhs )
  {
    excel->PutSheetsInNewWorkbook (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getShowChartTipNames ( )
  {
    return excel->GetShowChartTipNames ( );
  }
    
  void putShowChartTipNames (
          VARIANT_BOOL rhs )
  {
    excel->PutShowChartTipNames (
            rhs );
  }
    
  VARIANT_BOOL getShowChartTipValues ( )
  {
    return excel->GetShowChartTipValues ( );
  }
    
  void putShowChartTipValues (
          VARIANT_BOOL rhs )
  {
    excel->PutShowChartTipValues (
            rhs );
  }
    
  _bstr_t getStandardFont (
          long lcid = 0 )
  {
    return excel->GetStandardFont (
            lcid );
  }
    
  void putStandardFont (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutStandardFont (
            lcid,
            rhs );
  }
    
  double getStandardFontSize (
          long lcid = 0 )
  {
    return excel->GetStandardFontSize (
            lcid );
  }
    
  void putStandardFontSize (
          long lcid,
          double rhs )
  {
    excel->PutStandardFontSize (
            lcid,
            rhs );
  }
    
  _bstr_t getStartupPath (
          long lcid = 0 )
  {
    return excel->GetStartupPath (
            lcid );
  }
    
  _variant_t GetStatusBar (
          long lcid = 0 )
  {
    return excel->GetStatusBar (
            lcid );
  }
    
  void putStatusBar (
          long lcid,
          const _variant_t & rhs )
  {
    excel->PutStatusBar (
            lcid,
            rhs );
  }
    
  _bstr_t getTemplatesPath (
          long lcid = 0 )
  {
    return excel->GetTemplatesPath (
            lcid );
  }
    
  VARIANT_BOOL getShowToolTips ( )
  {
    return excel->GetShowToolTips ( );
  }
    
  void putShowToolTips (
          VARIANT_BOOL rhs )
  {
    excel->PutShowToolTips (
            rhs );
  }
    
  double getTop (
          long lcid = 0 )
  {
    return excel->GetTop (
            lcid );
  }
    
  void putTop (
          long lcid,
          double rhs )
  {
    excel->PutTop (
            lcid,
            rhs );
  }
    
  enum Excel::XlFileFormat getDefaultSaveFormat ( )
  {
    return excel->GetDefaultSaveFormat ( );
  }
    
  void putDefaultSaveFormat (
          enum Excel::XlFileFormat rhs )
  {
    excel->PutDefaultSaveFormat (
            rhs );
  }
    
  _bstr_t getTransitionMenuKey (
          long lcid = 0 )
  {
    return excel->GetTransitionMenuKey (
            lcid );
  }
    
  void putTransitionMenuKey (
          long lcid,
          _bstr_t rhs )
  {
    excel-> PutTransitionMenuKey (
            lcid,
            rhs );
  }
    
  long getTransitionMenuKeyAction (
          long lcid = 0 )
  {
    return excel->GetTransitionMenuKeyAction (
            lcid );
  }
    
  void putTransitionMenuKeyAction (
          long lcid,
          long rhs )
  {
    excel->PutTransitionMenuKeyAction (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getTransitionNavigKeys (
          long lcid = 0 )
  {
    return excel->GetTransitionNavigKeys (
            lcid );
  }
    
  void putTransitionNavigKeys (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutTransitionNavigKeys (
            lcid,
            rhs );
  }
    
  HRESULT undo (
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Undo (
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  double getUsableHeight (
          long lcid = 0 )
  {
    return excel->GetUsableHeight (
            lcid );
  }
    
  double getUsableWidth (
          long lcid = 0 )
  {
    return excel->GetUsableWidth (
            lcid );
  }
    
  VARIANT_BOOL getUserControl ( )
  {
    return excel->GetUserControl ( );
  }
    
  void putUserControl (
          VARIANT_BOOL rhs )
  {
    excel->PutUserControl (
            rhs );
  }
    
  _bstr_t getUserName (
          long lcid = 0 )
  {
    return excel->GetUserName (
            lcid );
  }
    
  void putUserName (
          long lcid,
          _bstr_t rhs )
  {
    excel->PutUserName (
            lcid,
            rhs );
  }
    
  _bstr_t getValue ( )
  {
    return excel->GetValue ( );
  }
    
  VBIDE::VBEPtr getVBE ( )
  {
    return excel->GetVBE ( );
  }
    
  _bstr_t getVersion (
          long lcid = 0 )
  {
    return excel->GetVersion (
            lcid );
  }
    
  VARIANT_BOOL getVisible (
          long lcid = 0 )
  {
    return excel->GetVisible (
            lcid );
  }
    
  void putVisible (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutVisible (
            lcid,
            rhs );
  }
    
  HRESULT _volatile (
          const _variant_t & vvolatile = vtMissing,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->Volatile (
            vvolatile,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  HRESULT wait (
          const _variant_t & time,
          long lcid = 0 )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->_Wait (
            time,
            lcid )) ){
      throw hr;
    }
    return hr;
  }
    
  double getWidth (
          long lcid = 0 )
  {
    return excel->GetWidth (
            lcid );
  }
    
  void putWidth (
          long lcid,
          double rhs )
  {
    excel->PutWidth (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getWindowsForPens (
          long lcid = 0 )
  {
    return excel->GetWindowsForPens (
            lcid );
  }
    
  enum Excel::XlWindowState getWindowState (
          long lcid = 0 )
  {
    return excel-> GetWindowState (
            lcid );
  }
    
  void putWindowState (
          long lcid,
          enum Excel::XlWindowState rhs )
  {
    excel->PutWindowState (
            lcid,
            rhs );
  }
    
  long getUILanguage (
          long lcid = 0 )
  {
    return excel->GetUILanguage (
            lcid );
  }
    
  void putUILanguage (
          long lcid,
          long rhs )
  {
    excel->PutUILanguage (
            lcid,
            rhs );
  }
    
  long getDefaultSheetDirection (
          long lcid = 0 )
  {
    return excel->GetDefaultSheetDirection (
            lcid );
  }
    
  void putDefaultSheetDirection (
          long lcid,
          long rhs )
  {
    excel->PutDefaultSheetDirection (
            lcid,
            rhs );
  }
    
  long getCursorMovement (
          long lcid = 0 )
  {
    return excel->GetCursorMovement (
            lcid );
  }
    
  void putCursorMovement (
          long lcid,
          long rhs )
  {
    excel->PutCursorMovement (
            lcid,
            rhs );
  }
    
  VARIANT_BOOL getControlCharacters (
          long lcid = 0 )
  {
    return excel->GetControlCharacters (
            lcid );
  }
    
  void putControlCharacters (
          long lcid,
          VARIANT_BOOL rhs )
  {
    excel->PutControlCharacters (
            lcid,
            rhs );

  }
    
  _variant_t wsFunction (
          const _variant_t & arg1 = vtMissing,
          const _variant_t & arg2 = vtMissing,
          const _variant_t & arg3 = vtMissing,
          const _variant_t & arg4 = vtMissing,
          const _variant_t & arg5 = vtMissing,
          const _variant_t & arg6 = vtMissing,
          const _variant_t & arg7 = vtMissing,
          const _variant_t & arg8 = vtMissing,
          const _variant_t & arg9 = vtMissing,
          const _variant_t & arg10 = vtMissing,
          const _variant_t & arg11 = vtMissing,
          const _variant_t & arg12 = vtMissing,
          const _variant_t & arg13 = vtMissing,
          const _variant_t & arg14 = vtMissing,
          const _variant_t & arg15 = vtMissing,
          const _variant_t & arg16 = vtMissing,
          const _variant_t & arg17 = vtMissing,
          const _variant_t & arg18 = vtMissing,
          const _variant_t & arg19 = vtMissing,
          const _variant_t & arg20 = vtMissing,
          const _variant_t & arg21 = vtMissing,
          const _variant_t & arg22 = vtMissing,
          const _variant_t & arg23 = vtMissing,
          const _variant_t & arg24 = vtMissing,
          const _variant_t & arg25 = vtMissing,
          const _variant_t & arg26 = vtMissing,
          const _variant_t & arg27 = vtMissing,
          const _variant_t & arg28 = vtMissing,
          const _variant_t & arg29 = vtMissing,
          const _variant_t & arg30 = vtMissing,
          long lcid = 0 )
  {
    return excel->_WSFunction (
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6,
            arg7,
            arg8,
            arg9,
            arg10,
            arg11,
            arg12,
            arg13,
            arg14,
            arg15,
            arg16,
            arg17,
            arg18,
            arg19,
            arg20,
            arg21,
            arg22,
            arg23,
            arg24,
            arg25,
            arg26,
            arg27,
            arg28,
            arg29,
            arg30,
            lcid  );
  }
    
  VARIANT_BOOL getEnableEvents ( )
  {
    return excel->GetEnableEvents ( );
  }
    
  void putEnableEvents (
          VARIANT_BOOL rhs )
  {
    excel->PutEnableEvents (
            rhs );
  }
    
  VARIANT_BOOL getDisplayInfoWindow ( )
  {
    return excel->GetDisplayInfoWindow ( );
  }
    
  void putDisplayInfoWindow (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayInfoWindow (
            rhs );
  }
    
  /*
  //VARIANT_BOOL
  HRESULT wait (
          const _variant_t & time,
          long lcid = 0 )
  {
    return excel->Wait (
            time,
            lcid );
  }
    */
  VARIANT_BOOL getExtendList ( )
  {
    return excel->GetExtendList ( );
  }
    
  void putExtendList (
          VARIANT_BOOL rhs )
  {
    excel->PutExtendList (
            rhs );
  }
    
  Excel::OLEDBErrorsPtr getOLEDBErrors ( )
  {
    return excel->GetOLEDBErrors ( );
  }
    
  _bstr_t getPhonetic (
          const _variant_t & text = vtMissing )
  {
    return excel->GetPhonetic (
            text );
  }
    
  Office::COMAddInsPtr getCOMAddIns ( )
  {
    return excel->GetCOMAddIns ( );
  }
    
  Excel::DefaultWebOptionsPtr getDefaultWebOptions ( )
  {
    return excel->GetDefaultWebOptions ( );
  }
    
  _bstr_t getProductCode ( )
  {
    return excel->GetProductCode ( );
  }
    
  _bstr_t getUserLibraryPath ( )
  {
    return excel->GetUserLibraryPath ( );
  }
    
  VARIANT_BOOL getAutoPercentEntry ( )
  {
    return excel->GetAutoPercentEntry ( );
  }
    
  void putAutoPercentEntry (
          VARIANT_BOOL rhs )
  {
    excel->PutAutoPercentEntry (
            rhs );
  }
    
  Office::LanguageSettingsPtr getLanguageSettings ( )
  {
    return excel->GetLanguageSettings ( );
  }
        
  Office::AnswerWizardPtr getAnswerWizard ( )
  {
    return excel->GetAnswerWizard ( );
  }
    
  HRESULT calculateFull ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->CalculateFull ( )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL findFile (
          long lcid = 0 )
  {
    return excel-> FindFile (
            lcid );
  }
    
  long getCalculationVersion ( )
  {
    return excel->GetCalculationVersion ( );
  }
    
  VARIANT_BOOL getShowWindowsInTaskbar ( )
   {
    return excel->GetShowWindowsInTaskbar ( );
  }
   
  void putShowWindowsInTaskbar (
          VARIANT_BOOL rhs )
  {
    excel->PutShowWindowsInTaskbar (
            rhs );
  }
      
  enum Office::MsoFeatureInstall getFeatureInstall ( )
  {
    return excel->GetFeatureInstall ( );
  }
    
  void putFeatureInstall (
          enum Office::MsoFeatureInstall rhs )
  {
    excel->PutFeatureInstall (
            rhs );
  }
    
  VARIANT_BOOL getReady ( )
  {
    return excel->GetReady ( );
  }
    
  Excel::CellFormatPtr getFindFormat ( )
  {
    return excel->GetFindFormat ( );
  }
    
  void putRefFindFormat (
          struct Excel::CellFormat * rhs )
  {
    excel->PutRefFindFormat (
            rhs );
  }
    
  Excel::CellFormatPtr getReplaceFormat ( )
  {
    return excel->GetReplaceFormat ( );
  }
    
  void putRefReplaceFormat (
          struct Excel::CellFormat * rhs )
  {
    excel->PutRefReplaceFormat (
            rhs );
  }
    
  Excel::UsedObjectsPtr getUsedObjects ( )
  {
    return excel->GetUsedObjects ( );
  }
    
  enum Excel::XlCalculationState getCalculationState ( )
  {
    return excel->GetCalculationState ( );
  }
    
  enum Excel::XlCalculationInterruptKey getCalculationInterruptKey ( )
  {
    return excel->GetCalculationInterruptKey ( );
  }
    
  void putCalculationInterruptKey (
          enum Excel::XlCalculationInterruptKey rhs )
  {
    excel->PutCalculationInterruptKey (
            rhs );
  }
    
  Excel::WatchesPtr getWatches ( )
  {
    return excel->GetWatches ( );
  }
    
  VARIANT_BOOL getDisplayFunctionToolTips ( )
  {
    return excel->GetDisplayFunctionToolTips ( );
  }
    
  void putDisplayFunctionToolTips (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayFunctionToolTips (
            rhs );
  }
    
  enum Office::MsoAutomationSecurity getAutomationSecurity ( )
  {
    return excel->GetAutomationSecurity ( );
  }
    
  void putAutomationSecurity (
          enum Office::MsoAutomationSecurity rhs )
  {
    excel->PutAutomationSecurity (
            rhs );
  }
    
  Office::FileDialogPtr getFileDialog (
          enum Office::MsoFileDialogType fileDialogType )
  {
    return excel->GetFileDialog (
            fileDialogType );
  }
    
  HRESULT calculateFullRebuild ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->CalculateFullRebuild ( )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getDisplayPasteOptions ( )
  {
    return excel->GetDisplayPasteOptions ( );
  }
    
  void putDisplayPasteOptions (
          VARIANT_BOOL rhs )
  {
    return excel->PutDisplayPasteOptions (
            rhs );
  }
    
  VARIANT_BOOL getDisplayInsertOptions ( )
  {
    return excel->GetDisplayInsertOptions ( );
  }
    
  void putDisplayInsertOptions (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayInsertOptions (
            rhs );
  }
    
  VARIANT_BOOL getGenerateGetPivotData ( )
  {
    return excel->GetGenerateGetPivotData ( );
  }
    
  void putGenerateGetPivotData (
          VARIANT_BOOL rhs )
  {
    excel->PutGenerateGetPivotData (
            rhs );
  }
    
  Excel::AutoRecoverPtr getAutoRecover ( )
  {
    return excel->GetAutoRecover ( );
  }
    
  long getHwnd ( )
  {
    return excel->GetHwnd ( );
  }
    
  long getHinstance ( )
  {
    return excel->GetHinstance ( );
  }
    
  HRESULT checkAbort (
          const _variant_t & keepAbort = vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->CheckAbort (
            keepAbort)) ){
      throw hr;
    }
    return hr;
  }
    
  Excel::ErrorCheckingOptionsPtr getErrorCheckingOptions ( )
  {
    return excel->GetErrorCheckingOptions ( );
  }
    
  VARIANT_BOOL getAutoFormatAsYouTypeReplaceHyperlinks ( )
  {
    return excel->GetAutoFormatAsYouTypeReplaceHyperlinks ( );
  }
    
  void putAutoFormatAsYouTypeReplaceHyperlinks (
          VARIANT_BOOL rhs )
  {
    excel->PutAutoFormatAsYouTypeReplaceHyperlinks (
            rhs );
  }
    
  Excel::SmartTagRecognizersPtr getSmartTagRecognizers ( )
  {
    return excel->GetSmartTagRecognizers ( );
  }
    
  Office::NewFilePtr getNewWorkbook ( )
  {
    return excel->GetNewWorkbook ( );
  }
    
  Excel::SpellingOptionsPtr getSpellingOptions ( )
  {
    return excel->GetSpellingOptions ( );
  }
    
  Excel::SpeechPtr getSpeech ( )
  {
    return excel->GetSpeech ( );
  }
    
  VARIANT_BOOL getMapPaperSize ( )
  {
    return excel->GetMapPaperSize ( );
  }
    
  void putMapPaperSize (
          VARIANT_BOOL rhs )
  {
    excel->PutMapPaperSize (
            rhs );
  }
    
  VARIANT_BOOL getShowStartupDialog ( )
  {
    return excel->GetShowStartupDialog ( );
  }
    
  void putShowStartupDialog (
          VARIANT_BOOL rhs )
  {
    excel->PutShowStartupDialog (
            rhs );
  }
    
  _bstr_t getDecimalSeparator ( )
  {
    return excel->GetDecimalSeparator ( );
  }
    
  void putDecimalSeparator (
          _bstr_t rhs )
  {
    excel->PutDecimalSeparator (
            rhs );
  }
    
  _bstr_t getThousandsSeparator ( )
  {
    return excel->GetThousandsSeparator ( );
  }
    
  void putThousandsSeparator (
          _bstr_t rhs )
  {
    excel->PutThousandsSeparator (
            rhs );
  }
    
  VARIANT_BOOL getUseSystemSeparators ( )
  {
    return excel->GetUseSystemSeparators ( );
  }
    
  void putUseSystemSeparators (
          VARIANT_BOOL rhs )
  {
    excel->PutUseSystemSeparators (
            rhs );
  }

  Excel::RangePtr getThisCell ( )
  {
    return excel->GetThisCell ( );
  }
    
  Excel::RTDPtr getRTD ( )
  {
    return excel->GetRTD ( );
  }
    
  VARIANT_BOOL getDisplayDocumentActionTaskPane ( )
  {
    return excel->GetDisplayDocumentActionTaskPane ( );
  }
    
  void putDisplayDocumentActionTaskPane (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayDocumentActionTaskPane (
            rhs );
  }
    
  HRESULT displayXMLSourcePane (
          const _variant_t & xmlMap = vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->DisplayXMLSourcePane (
            xmlMap )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getArbitraryXMLSupportAvailable ( )
  {
    return excel->GetArbitraryXMLSupportAvailable ( );
  }
    
  _variant_t support (
          IDispatch * object,
          long id,
          const _variant_t & arg = vtMissing )
  {
    return excel->Support (
            object,
            id,
            arg );
  }
    
  long getMeasurementUnit ( )
  {
    return excel->GetMeasurementUnit ( );
  }
    
  void putMeasurementUnit (
          long rhs )
  {
    excel->PutMeasurementUnit (
            rhs );
  }
    
  VARIANT_BOOL getShowSelectionFloaties ( )
  {
    return excel->GetShowSelectionFloaties ( );
  }
    
  void putShowSelectionFloaties (
          VARIANT_BOOL rhs )
  {
    excel->PutShowSelectionFloaties (
            rhs );
  }
    
  VARIANT_BOOL getShowMenuFloaties ( )
  {
    return excel->GetShowMenuFloaties ( );
  }
    
  void putShowMenuFloaties (
          VARIANT_BOOL rhs )
  {
    excel->PutShowMenuFloaties (
            rhs );
  }
    
  VARIANT_BOOL getShowDevTools ( )
  {
    return excel->GetShowDevTools ( );
  }
    
  void putShowDevTools (
          VARIANT_BOOL rhs )
  {
    excel->PutShowDevTools (
              rhs );
  }
    
  VARIANT_BOOL getEnableLivePreview ( )
  {
    return excel->GetEnableLivePreview ( );
  }
    
  void putEnableLivePreview (
          VARIANT_BOOL rhs )
  {
    excel->PutEnableLivePreview (
            rhs );
  }
    
  VARIANT_BOOL getDisplayDocumentInformationPanel ( )
  {
    return excel->GetDisplayDocumentInformationPanel ( );
  }
    
  void putDisplayDocumentInformationPanel (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayDocumentInformationPanel (
            rhs );
  }
    
  VARIANT_BOOL getAlwaysUseClearType ( )
  {
    return excel->GetAlwaysUseClearType ( );
  }
    
  void putAlwaysUseClearType (
          VARIANT_BOOL rhs )
  {
    excel->PutAlwaysUseClearType (
              rhs );
  }
    
  VARIANT_BOOL getWarnOnFunctionNameConflict ( )
  {
    return excel->GetWarnOnFunctionNameConflict ( );
  }
    
  void putWarnOnFunctionNameConflict (
          VARIANT_BOOL rhs )
  {
    excel->PutWarnOnFunctionNameConflict (
            rhs);
  }
    
  long getFormulaBarHeight ( )
  {
    return excel->GetFormulaBarHeight ( );
  }
    
  void putFormulaBarHeight (
          long rhs )
  {
    excel->PutFormulaBarHeight (
            rhs );
  }
    
  VARIANT_BOOL getDisplayFormulaAutoComplete ( )
  {
    return excel->GetDisplayFormulaAutoComplete ( );
  }
    
  void putDisplayFormulaAutoComplete (
          VARIANT_BOOL rhs )
  {
    excel->PutDisplayFormulaAutoComplete (
            rhs);
  }
    
  enum Excel::XlGenerateTableRefs getGenerateTableRefs (
          long lcid = 0 )
  {
    return excel->GetGenerateTableRefs (
            lcid );
  }
    
  void putGenerateTableRefs (
          long lcid,
          enum Excel::XlGenerateTableRefs rhs )
  {
    excel->PutGenerateTableRefs (
            lcid,
            rhs );
  }
    
  Office::IAssistancePtr getAssistance ( )
  {
    return excel->GetAssistance ( );
  }
    
  HRESULT calculateUntilAsyncQueriesDone ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = excel->CalculateUntilAsyncQueriesDone ( )) ){
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getEnableLargeOperationAlert ( )
  {
    return excel->GetEnableLargeOperationAlert ( );
  }
    
  void putEnableLargeOperationAlert (
          VARIANT_BOOL rhs )
  {
    excel->PutEnableLargeOperationAlert (
            rhs);
  }
    
  long getLargeOperationCellThousandCount ( )
  {
    return excel->GetLargeOperationCellThousandCount ( );
  }
    
  void putLargeOperationCellThousandCount (
          long rhs )
  {
    excel->PutLargeOperationCellThousandCount (
            rhs );
  }
    
  VARIANT_BOOL getDeferAsyncQueries ( )
  {
    return excel->GetDeferAsyncQueries ( );
  }
    
  void putDeferAsyncQueries (
          VARIANT_BOOL rhs )
  {
    excel->PutDeferAsyncQueries (
            rhs);
  }
    
  Excel::MultiThreadedCalculationPtr getMultiThreadedCalculation ( )
  {
    return excel->GetMultiThreadedCalculation ( );
  }
    
  long sharePointVersion (
          _bstr_t bstrUrl )
  {
    return excel->SharePointVersion (
            bstrUrl );
  }
    
  long getActiveEncryptionSession ( )
  {
    return excel->GetActiveEncryptionSession ( );
  }
    
  VARIANT_BOOL getHighQualityModeForGraphics ( )
  {
    return excel->GetHighQualityModeForGraphics ( );
  }
    
  void putHighQualityModeForGraphics (
          VARIANT_BOOL rhs )
  {
    excel->PutHighQualityModeForGraphics (
            rhs );
  }

    
  Excel::FileExportConvertersPtr getFileExportConverters ( )
  {
    return excel->GetFileExportConverters ( );
  }


};


}
