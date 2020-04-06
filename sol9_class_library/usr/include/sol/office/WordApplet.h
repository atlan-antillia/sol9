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
 *  WordApplet.h
 *
 *****************************************************************************/

//2010/04/08
//2010/05/05 Added a lot of public methods.

#pragma once

#include <sol/office/OfficeApplet.h>

//MSWORD
//2015/12/25
#ifndef WIN64
#ifdef OFFICE2013
#import "C:\Program Files (x86)\Microsoft Office\OFFICE15\MSWORD.OLB" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("DialogBox","DialogBoxXL") \
  rename("CopyFile","CopyFileXL") \
  rename("ReplaceText","ReplaceTextXL") \
  rename("FindText","FindTextXL") \
  rename("ExitWindows","_ExitWindowsW")

#elif OFFICE2010
#import "C:\Program Files (x86)\Microsoft Office\OFFICE14\MSWORD.OLB" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("DialogBox","DialogBoxXL") \
  rename("CopyFile","CopyFileXL") \
  rename("ReplaceText","ReplaceTextXL") \
  rename("FindText","FindTextXL") \
  rename("ExitWindows","_ExitWindowsW")

#else
#import "C:\Program Files (x86)\Microsoft Office\OFFICE12\MSWORD.OLB" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("DialogBox","DialogBoxXL") \
  rename("CopyFile","CopyFileXL") \
  rename("ReplaceText","ReplaceTextXL") \
  rename("FindText","FindTextXL") \
  rename("ExitWindows","_ExitWindowsW")
#endif

#else
#ifdef OFFICE2013
#import "C:\Program Files\Microsoft Office\OFFICE15\MSWORD.OLB" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("DialogBox","DialogBoxXL") \
  rename("CopyFile","CopyFileXL") \
  rename("ReplaceText","ReplaceTextXL") \
  rename("FindText","FindTextXL") \
  rename("ExitWindows","_ExitWindowsW")

#elif OFFICE2010
#import "C:\Program Files\Microsoft Office\OFFICE14\MSWORD.OLB" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("DialogBox","DialogBoxXL") \
  rename("CopyFile","CopyFileXL") \
  rename("ReplaceText","ReplaceTextXL") \
  rename("FindText","FindTextXL") \
  rename("ExitWindows","_ExitWindowsW")

#else
#import "C:\Program Files\Microsoft Office\OFFICE12\MSWORD.OLB" \
  rename("DocumentProperties","DocumentPropertiesXL") \
  rename("RGB","RBGXL") \
  rename("DialogBox","DialogBoxXL") \
  rename("CopyFile","CopyFileXL") \
  rename("ReplaceText","ReplaceTextXL") \
  rename("FindText","FindTextXL") \
  rename("ExitWindows","_ExitWindowsW")
#endif

#endif

namespace SOL {


class WordApplet :public OfficeApplet {
private:
  Word::_ApplicationPtr word;

private:
  Word::DocumentsPtr documents;

private:
  bool isCreated;

public:
  WordApplet()
    :word(NULL),
    documents(NULL),
    isCreated(false)
  {
    IDispatch* pDisp = NULL;
    const wchar_t* application = L"Word.Application";
    if (getActiveObject(application, &pDisp)) {
      this->word = pDisp;    
      printf( "WordApplet#WordApplet,1,Found an active word object\n");
    } else {

      HRESULT hr= this->word.CreateInstance(application);
      if (FAILED(hr)) {
        throw hr;
      } else {
        printf( "WordApplet#WordApplet,2,Created a word object\n");
        isCreated = true;
      }
    }

    if (this->word) {
      this->documents = word->Documents;
    }
  }

public:
  ~WordApplet()
  {
    if (this->word) {
      if (isCreated) {
        this->documents = NULL;
        this->word->Quit();
      }
      this->documents = NULL;
      this->word = NULL;
    }  
  }


public:
  Word::_DocumentPtr open(const BSTR docName, bool visible=false)
  {
    VARIANT name;
    VariantClear(&name);
    name.vt = VT_BSTR;
    name.bstrVal = docName;

    if (isCreated) {
      if (visible==false) {
        this->word->PutVisible(FALSE);
      } else {
        this->word->PutVisible(TRUE);
      }
    }

    Word::_DocumentPtr document = NULL;

    try {
      document = this->documents->
        Open(&name, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, 
          &vtMissing, &vtMissing, &vtMissing, &vtMissing,
          &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing, &vtMissing);
    } catch (...) {

    }

    return document;
  }

  //2010/05/01 Added the following
public:
  Word::_ApplicationPtr getApplication ( )
  {
    return word->GetApplication ( );
     }

  long getCreator ( )
  {
    return word->GetCreator ( );
  }
    
  IDispatchPtr getParent ( )
  {
    return word->GetParent ( );
  }
    
  _bstr_t getName ( )
  {
    return word->GetName ( );
  }
    
  Word::DocumentsPtr getDocuments ( )
  {
    return word->GetDocuments ( );
  }
    
  Word::WindowsPtr getWindows ( )
  {
    return word->GetWindows ( );
  }
    
  Word::_DocumentPtr getActiveDocument ( )
  {
    return word->GetActiveDocument ( );
  }
    
  Word::WindowPtr getActiveWindow ( )
  {
    return word->GetActiveWindow ( );
  }
    
  Word::SelectionPtr getSelection ( )
  {
    return word->GetSelection ( );
  }
    
  IDispatchPtr getWordBasic ( )
  {
    return word->GetWordBasic ( );
  }
    
  Word::RecentFilesPtr getRecentFiles ( )
  {
    return word->GetRecentFiles ( );
  }
    
  Word::TemplatePtr getNormalTemplate ( )
  {
    return word->GetNormalTemplate ( );
  }
    
  Word::SystemPtr getSystem ( )
  {
    return word->GetSystem ( );
  }
    
  Word::AutoCorrectPtr getAutoCorrect ( )
  {
    return word->GetAutoCorrect ( );
  }
    
  Word::FontNamesPtr getFontNames ( )
  {
    return word->GetFontNames ( );
  }
    
  Word::FontNamesPtr getLandscapeFontNames ( )
  {
    return word->GetLandscapeFontNames ( );
  }
    
  Word::FontNamesPtr getPortraitFontNames ( )
  {
    return word->GetPortraitFontNames ( );
  }
    
  Word::LanguagesPtr getLanguages ( )
  {
    return word->GetLanguages ( );
  }
    
  Office::AssistantPtr getAssistant ( )
  {
    return word->GetAssistant ( );
  }
    
  Word::BrowserPtr getBrowser ( )
  {
    return word->GetBrowser ( );
  }
    
  Word::FileConvertersPtr getFileConverters ( )
  {
    return word->GetFileConverters ( );
  }
    
  Word::MailingLabelPtr getMailingLabel ( )
  {
    return word->GetMailingLabel ( );
  }
    
  Word::DialogsPtr getDialogs ( )
  {
    return word->GetDialogs ( );
  }
    
  Word::CaptionLabelsPtr getCaptionLabels ( )
  {
    return word->GetCaptionLabels ( );
  }
    
  Word::AutoCaptionsPtr getAutoCaptions ( )
  {
    return word->GetAutoCaptions ( );
  }
    
  Word::AddInsPtr getAddIns ( )
  {
    return word->GetAddIns ( );
  }
    
  VARIANT_BOOL getVisible ( )
  {
    return word->GetVisible ( );
  }
    
  void putVisible (
          VARIANT_BOOL prop )
  {
    word->PutVisible (
            prop );
  }
    
  _bstr_t getVersion ( )
  {
    return word->GetVersion ( );
  }
    
  VARIANT_BOOL getScreenUpdating ( )
  {
    return word->GetScreenUpdating ( );
  }
    
  void putScreenUpdating (
          VARIANT_BOOL prop )
  {
    word->PutScreenUpdating (
            prop );
  }
    
  VARIANT_BOOL getPrintPreview ( )
  {
    return word->GetPrintPreview ( );
  }
    
  void putPrintPreview (
          VARIANT_BOOL prop )
  {
    word->PutPrintPreview (
            prop );
  }
    
  Word::TasksPtr getTasks ( )
  {
    return word->GetTasks ( );
  }
    
  VARIANT_BOOL getDisplayStatusBar ( )
  {
    return word->GetDisplayStatusBar ( );
  }
    
  void putDisplayStatusBar (
          VARIANT_BOOL prop )
  {
    word->PutDisplayStatusBar (
            prop );
  }
    
  VARIANT_BOOL getSpecialMode ( )
  {
    return word->GetSpecialMode ( );
  }
    
  long getUsableWidth ( )
  {
    return word->GetUsableWidth ( );
  }
    
  long getUsableHeight ( )
  {
    return word->GetUsableHeight ( );
  }
    
  VARIANT_BOOL getMathCoprocessorAvailable ( )
  {
    return word->GetMathCoprocessorAvailable ( );
  }
    
  VARIANT_BOOL getMouseAvailable ( )
  {
    return word->GetMouseAvailable ( );
  }
    
  _variant_t getInternational (
          enum Word::WdInternationalIndex index )
  {
    return word->GetInternational (
            index );
  }
    
  _bstr_t getBuild ( )
  {
    return word->GetBuild ( );
  }
    
  VARIANT_BOOL getCapsLock ( )
  {
    return word->GetCapsLock ( );
  }
    
  VARIANT_BOOL getNumLock ( )
  {
    return word->GetNumLock ( );
  }
    
  _bstr_t getUserName ( )
  {
    return word->GetUserName ( );
  }
    
  void putUserName (
          _bstr_t prop )
  {
    word->PutUserName (
            prop );
  }
    
  _bstr_t getUserInitials ( )
  {
    return word->GetUserInitials ( );
  }
    
  void putUserInitials (
          _bstr_t prop )
  {
    word->PutUserInitials (
            prop );
  }
    
  _bstr_t getUserAddress ( )
  {
    return word->GetUserAddress ( );
  }
    
  void putUserAddress (
          _bstr_t prop )
  {
    word->PutUserAddress (
            prop );
  }
    
  IDispatchPtr getMacroContainer ( )
  {
    return word->GetMacroContainer ( );
  }
    
  VARIANT_BOOL getDisplayRecentFiles ( )
  {
    return word->GetDisplayRecentFiles ( );
  }
    
  void putDisplayRecentFiles (
          VARIANT_BOOL prop )
  {
    word->PutDisplayRecentFiles (
            prop );
  }
    
  Office::_CommandBarsPtr getCommandBars ( )
  {
    return word->GetCommandBars ( );
  }
    
  Word::SynonymInfoPtr getSynonymInfo (
          _bstr_t sword,
          VARIANT * languageID = &vtMissing )
  {
    return word->GetSynonymInfo (
            sword,
            languageID );
  }
    
  VBIDE::VBEPtr getVBE ( )
  {
    return word->GetVBE ( );
  }
    
  _bstr_t getDefaultSaveFormat ( )
  {
    return word->GetDefaultSaveFormat ( );
  }
    
  void putDefaultSaveFormat (
          _bstr_t prop )
  {
    word->PutDefaultSaveFormat (
            prop );
  }
    
  Word::ListGalleriesPtr getListGalleries ( )
  {
    return word->GetListGalleries ( );
  }
    
  _bstr_t getActivePrinter ( )
  {
    return word->GetActivePrinter ( );
  }
    
  void putActivePrinter (
          _bstr_t prop )
  {
    word->PutActivePrinter (
            prop );
  }
    
  Word::TemplatesPtr getTemplates ( )
  {
    return word->GetTemplates ( );
  }
    
  IDispatchPtr getCustomizationContext ( )
  {
    return word->GetCustomizationContext ( );
  }
    
  void putCustomizationContext (
          IDispatch * prop )
  {
    word->PutCustomizationContext (
            prop );
  }
    
  Word::KeyBindingsPtr getKeyBindings ( )
  {
    return word->GetKeyBindings ( );
  }
    
  Word::KeysBoundToPtr getKeysBoundTo (
          enum Word::WdKeyCategory keyCategory,
          _bstr_t command,
          VARIANT * commandParameter = &vtMissing )
  {
    return word->GetKeysBoundTo (
            keyCategory,
            command,
            commandParameter);
  }
    

  Word::KeyBindingPtr getFindKey (
          long keyCode,
          VARIANT * keyCode2 = &vtMissing )
  {
    return word->GetFindKey (
            keyCode,
            keyCode2 );
  }
    
  _bstr_t getCaption ( )
  {
    return word->GetCaption ( );
  }
    
  void putCaption (
          _bstr_t prop )
  {
    word->PutCaption (
            prop );
  }

  _bstr_t getPath ( )
  {
    return word->GetPath ( );
  }

    
  VARIANT_BOOL getDisplayScrollBars ( )
  {
    return word->GetDisplayScrollBars ( );
  }
    
  void putDisplayScrollBars (
          VARIANT_BOOL prop )
  {
    word->PutDisplayScrollBars (
            prop );
  }
    
  _bstr_t getStartupPath ( )
  {
    return word->GetStartupPath ( );
  }
    
  void putStartupPath (
          _bstr_t prop )
  {
    word->PutStartupPath (
            prop );
  }
    
  long getBackgroundSavingStatus ( )
  {
    return word->GetBackgroundSavingStatus ( );
  }
    
  long getBackgroundPrintingStatus ( )
  {
    return word->GetBackgroundPrintingStatus ( );
  }
    
  long getLeft ( )
  {
    return word->GetLeft ( );
  }
    
  void putLeft (
          long prop )
  {
    word->PutLeft (
            prop );
  }
    
  long getTop ( )
  {
    return word->GetTop ( );
  }
    
  void putTop (
          long prop )
  {
    word->PutTop (
            prop );
  }
    
  long getWidth ( )
  {
    return word->GetWidth ( );
  }
    
  void putWidth (
          long prop )
  {
    word->PutWidth (
            prop );
  }
    
  long getHeight ( )
  {
    return word->GetHeight ( );
  }
    
  void putHeight (
          long prop )
  {
    word->PutHeight (
            prop );
  }
    
  enum Word::WdWindowState getWindowState ( )
  {
    return word->GetWindowState ( );
  }
    
  void putWindowState (
          enum Word::WdWindowState prop )
  {
    word->PutWindowState (
            prop );
  }
    
  VARIANT_BOOL getDisplayAutoCompleteTips ( )
  {
    return word->GetDisplayAutoCompleteTips ( );
  }
    
  void putDisplayAutoCompleteTips (
          VARIANT_BOOL prop )
  {
    word->PutDisplayAutoCompleteTips (
            prop );
  }
    
  Word::OptionsPtr getOptions ( )
  {
    return word->GetOptions ( );
  }
    
  enum Word::WdAlertLevel getDisplayAlerts ( )
  {
    return word->GetDisplayAlerts ( );
  }
    
  void putDisplayAlerts (
          enum Word::WdAlertLevel prop )
  {
    word->PutDisplayAlerts (
            prop );
  }
    
  Word::DictionariesPtr getCustomDictionaries ( )
  {
    return word->GetCustomDictionaries ( );
  }
    
  _bstr_t getPathSeparator ( )
  {
    return word->GetPathSeparator ( );
  }
    
  void putStatusBar (
          _bstr_t _arg1 )
  {
    word->PutStatusBar (
            _arg1 );
  }
    
  VARIANT_BOOL getMAPIAvailable ( )
  {
    return word->GetMAPIAvailable ( );
  }
    
  VARIANT_BOOL getDisplayScreenTips ( )
  {
    return word->GetDisplayScreenTips ( );
  }
    
  void putDisplayScreenTips (
          VARIANT_BOOL prop )
  {
    word->PutDisplayScreenTips (
            prop );
  }
    
  enum Word::WdEnableCancelKey getEnableCancelKey ( )
  {
    return word-> GetEnableCancelKey ( );
  }
    
  void putEnableCancelKey (
          enum Word::WdEnableCancelKey prop )
  {
    word->PutEnableCancelKey (
            prop );
  }
    
  VARIANT_BOOL getUserControl ( )
  {
    return word->GetUserControl ( );
  }
    
  Office::FileSearchPtr getFileSearch ( )
  {
    return word->GetFileSearch ( );
  }
    
  enum Word::WdMailSystem getMailSystem ( )
  {
    return word->GetMailSystem ( );
  }
    
  _bstr_t getDefaultTableSeparator ( )
  {
    return word->GetDefaultTableSeparator ( );
  }
    
  void putDefaultTableSeparator (
          _bstr_t prop )
  {
    word->PutDefaultTableSeparator (
            prop );
  }
    
  VARIANT_BOOL getShowVisualBasicEditor ( )
  {
    return word->GetShowVisualBasicEditor ( );
  }
    
  void putShowVisualBasicEditor (
          VARIANT_BOOL prop )
  {
    word->PutShowVisualBasicEditor (
            prop );
  }
    
  _bstr_t getBrowseExtraFileTypes ( )
  {
    return word->GetBrowseExtraFileTypes ( );
  }
    
  void putBrowseExtraFileTypes (
          _bstr_t prop )
  {
    word->PutBrowseExtraFileTypes (
            prop );
  }
    
  VARIANT_BOOL getIsObjectValid (
          IDispatch * object )
  {
    return word->GetIsObjectValid (
            object );
  }
   
  Word::HangulHanjaConversionDictionariesPtr getHangulHanjaDictionaries ( )
  {
    return word->GetHangulHanjaDictionaries ( );
  }
    
  Word::MailMessagePtr getMailMessage ( )
  {
    return word->GetMailMessage ( );
  }
    
  VARIANT_BOOL getFocusInMailHeader ( )
  {
    return word->GetFocusInMailHeader ( );
  }
    
  HRESULT quit (
          VARIANT * saveChanges = &vtMissing,
          VARIANT * originalFormat = &vtMissing,
          VARIANT * routeDocument = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->Quit (
            saveChanges,
            originalFormat,
            routeDocument ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT screenRefresh ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->ScreenRefresh ( ))) {
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
          VARIANT * fileName = &vtMissing,
          VARIANT * activePrinterMacGX = &vtMissing,
          VARIANT * manualDuplexPrint = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word-> PrintOutOld (
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
            fileName,
            activePrinterMacGX,
            manualDuplexPrint ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT lookupNameProperties (
          _bstr_t name ) 
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word-> LookupNameProperties (
            name ))) {  
      throw hr;
    }
    return hr; 
  }

  HRESULT substituteFont (
          _bstr_t unavailableFont,
          _bstr_t substituteFont )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word-> SubstituteFont (
            unavailableFont,
            substituteFont ))) {   
      throw hr;
    }
    return hr; 
  }
    
  VARIANT_BOOL repeat (
          VARIANT * times = &vtMissing )
  {
    return word->Repeat (
            times );
  }
    
  HRESULT ddeExecute (
          long channel,
          _bstr_t command )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->DDEExecute (
            channel,
            command ))) {
      throw hr;
    }
    return hr; 
  }
    
  long ddeInitiate (
          _bstr_t app,
          _bstr_t topic )
  {
    return word->DDEInitiate (
            app,
            topic );
  }
    
  HRESULT ddePoke (
          long channel,
          _bstr_t item,
          _bstr_t data )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->DDEPoke (
            channel,
            item,
            data ))) {
      throw hr;
    }
    return hr; 
  }
    
  _bstr_t ddeRequest (
          long channel,
          _bstr_t item )
  {
    return word-> DDERequest (
            channel,
            item );
  }
    
  HRESULT ddeTerminate (
          long channel )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->DDETerminate (
            channel ))) { 
      throw hr;
    }
    return hr; 
  }
    
  HRESULT ddeTerminateAll ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->DDETerminateAll ( ))) { 
      throw hr;
    }
    return hr; 
  }
    
  long buildKeyCode (
          enum Word::WdKey arg1,
          VARIANT * arg2 = &vtMissing,
          VARIANT * arg3 = &vtMissing,
          VARIANT * arg4 = &vtMissing )
  {
    return word->BuildKeyCode (
            arg1,
            arg2,
            arg3,
            arg4 );
  }
    
  _bstr_t keyString (
          long keyCode,
          VARIANT * keyCode2 = &vtMissing )
  {
    return word->KeyString (
            keyCode,
            keyCode2 );
  }
    
  HRESULT organizerCopy (
          _bstr_t source,
          _bstr_t destination,
          _bstr_t name,
          enum Word::WdOrganizerObject object )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->OrganizerCopy (
            source,
            destination,
            name,
            object ))) {
      throw hr;
    }
    return hr; 
  }

      HRESULT organizerDelete (
          _bstr_t source,
          _bstr_t name,
          enum Word::WdOrganizerObject object )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->OrganizerDelete (
            source,
            name,
            object ))) {  
      throw hr;
    }
    return hr; 
  }
    
  HRESULT organizerRename (
          _bstr_t source,
          _bstr_t name,
          _bstr_t newName,
          enum Word::WdOrganizerObject object )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->OrganizerRename (
            source,
            name,
            newName,
            object ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT addAddress (
          SAFEARRAY** tagID,
          SAFEARRAY** value )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->AddAddress (
            tagID,
            value ))) {
      throw hr;
    }
    return hr; 
  }
    
  _bstr_t getAddress (
          VARIANT * name = &vtMissing,
          VARIANT * addressProperties = &vtMissing,
          VARIANT * useAutoText = &vtMissing,
          VARIANT * displaySelectDialog = &vtMissing,
          VARIANT * selectDialog = &vtMissing,
          VARIANT * checkNamesDialog = &vtMissing,
          VARIANT * recentAddressesChoice = &vtMissing,
          VARIANT * updateRecentAddresses = &vtMissing )
  {
    return word->GetAddress (
            name,
            addressProperties,
            useAutoText,
            displaySelectDialog,
            selectDialog,
            checkNamesDialog,
            recentAddressesChoice,
            updateRecentAddresses );
  }
    
  VARIANT_BOOL checkGrammar (
          _bstr_t string )
  {
    return word->CheckGrammar (
            string );
  }
    
  VARIANT_BOOL checkSpelling (
          _bstr_t sword,
          VARIANT * customDictionary = &vtMissing,
          VARIANT * ignoreUppercase = &vtMissing,
          VARIANT * mainDictionary = &vtMissing,
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
    return word->CheckSpelling (
            sword,
            customDictionary,
            ignoreUppercase,
            mainDictionary,
            customDictionary2,
            customDictionary3,
            customDictionary4,
            customDictionary5,
            customDictionary6,
            customDictionary7,
            customDictionary8,
            customDictionary9,
            customDictionary10 );
  }
    
  HRESULT resetIgnoreAll ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->ResetIgnoreAll ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  Word::SpellingSuggestionsPtr getSpellingSuggestions (
          _bstr_t sword,
          VARIANT * customDictionary = &vtMissing,
          VARIANT * ignoreUppercase = &vtMissing,
          VARIANT * mainDictionary = &vtMissing,
          VARIANT * suggestionMode = &vtMissing,
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
    return word->GetSpellingSuggestions (
            sword,
            customDictionary,
            ignoreUppercase,
            mainDictionary,
            suggestionMode,
            customDictionary2,
            customDictionary3,
            customDictionary4,
            customDictionary5,
            customDictionary6,
            customDictionary7,
            customDictionary8,
            customDictionary9,
            customDictionary10 );
  }
    
  HRESULT goBack ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->GoBack ( ))) {  
      throw hr;
    }
    return hr; 
  }
    
  HRESULT help (
          VARIANT * helpType )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->Help (
            helpType ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT automaticChange ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->AutomaticChange ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT showMe ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->ShowMe ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT helpTool ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->HelpTool ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  Word::WindowPtr newWindow ( )
  {
    return word->NewWindow ( );
  }
    
  HRESULT listCommands (
          VARIANT_BOOL listAllCommands )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word-> ListCommands (
            listAllCommands ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT showClipboard ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->ShowClipboard ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT onTime (
          VARIANT * when,
          _bstr_t name,
          VARIANT * tolerance = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->OnTime (
            when,
            name,
            tolerance ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT nextLetter ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word-> NextLetter ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  short mountVolume (
          _bstr_t zone,
          _bstr_t server,
          _bstr_t volume,
          VARIANT * user = &vtMissing,
          VARIANT * userPassword = &vtMissing,
          VARIANT * volumePassword = &vtMissing )
  {
    return word->MountVolume (
            zone,
            server,
            volume,
            user,
            userPassword,
            volumePassword );
  }
    
  _bstr_t cleanString (
          _bstr_t string )
  {
    return word->CleanString (
            string );
  }
    
  HRESULT sendFax ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->SendFax ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT changeFileOpenDirectory (
          _bstr_t path )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->ChangeFileOpenDirectory (
            path ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT runOld (
          _bstr_t macroName )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->RunOld (
            macroName ))) {  
      throw hr;
    }
    return hr; 
  }
    
  HRESULT goForward ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->GoForward ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT move (
          long left,
          long top )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->Move (
            left,
            top ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT resize (
          long width,
          long height )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->Resize (
            width,
            height ))) {
      throw hr;
    }
    return hr; 
  }
    
  float inchesToPoints (
          float inches )
  {
    return word->InchesToPoints (
            inches );
  }
    
  float centimetersToPoints (
          float centimeters )
  {
    return word->CentimetersToPoints (
            centimeters );
  }
    
  float millimetersToPoints (
          float millimeters )
  {
    return word->MillimetersToPoints (
            millimeters );
  }
    
  float picasToPoints (
          float picas )
  {
    return word->PicasToPoints (
            picas );
  }
    
  float linesToPoints (
          float lines )
  {
    return word->LinesToPoints (
            lines );
  }
    
  float pointsToInches (
          float points )
  {
    return word->PointsToInches (
            points );
  }
    
  float pointsToCentimeters (
          float points )
  {
    return word->PointsToCentimeters (
            points );
  }
    
  float pointsToMillimeters (
          float points )
  {
    return word->PointsToMillimeters (
            points );
  }
    
  float pointsToPicas (
          float points )
  {
    return word->PointsToPicas (
            points );
  }
    
  float pointsToLines (
          float Points )
  {
    return word->PointsToLines (
            Points );
  }
    
  HRESULT activate ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->Activate( ))) {
      throw hr;
    }
    return hr; 
  }
    
  float pointsToPixels (
          float points,
    VARIANT * fVertical = &vtMissing )
  {
    return word->PointsToPixels (
            points,
      fVertical );
  }
    
  float pixelsToPoints (
          float pixels,
          VARIANT * fVertical = &vtMissing )
  {
    return word->PixelsToPoints (
            pixels,
            fVertical );
  }
    
  HRESULT keyboardLatin ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->KeyboardLatin ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT keyboardBidi ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->KeyboardBidi ( ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT toggleKeyboard ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->ToggleKeyboard ( ))) {
      throw hr;
    }
    return hr; 
    }
  
  long keyboard (
          long langId )
  {
    return word->Keyboard (
            langId ); 
  }
    
  _bstr_t productCode ( )
  {
    return word->ProductCode ( );
  }
    
  Word::DefaultWebOptionsPtr defaultWebOptions ( )
  {
    return word->DefaultWebOptions ( );
  }
    
  HRESULT discussionSupport (
          VARIANT * range,
          VARIANT * cid,
          VARIANT * piCSE )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->DiscussionSupport (
            range,
            cid,
            piCSE ))) {
      throw hr;
    }
    return hr; 
  }
    
  HRESULT setDefaultTheme (
          _bstr_t name,
          enum Word::WdDocumentMedium documentType )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->SetDefaultTheme (
            name,
            documentType ))) {
      throw hr;
    }
    return hr; 
  }
    
  _bstr_t getDefaultTheme (
          enum Word::WdDocumentMedium documentType )
  {
    return word->GetDefaultTheme (
            documentType );
  }
    
  Word::EmailOptionsPtr getEmailOptions ( )
  {
    return word->GetEmailOptions ( );
  }
    
  enum Office::MsoLanguageID getLanguage ( )
  {
    return word->GetLanguage ( );
  }
    
  Office::COMAddInsPtr getCOMAddIns ( )
  {
    return word->GetCOMAddIns ( );
  }
    
  VARIANT_BOOL getCheckLanguage ( )
  {
    return word->GetCheckLanguage ( );
  }
    
  void putCheckLanguage (
          VARIANT_BOOL prop )
  {
    word->PutCheckLanguage (
            prop );
  }
    
  Office::LanguageSettingsPtr getLanguageSettings ( )
  {
    return word->GetLanguageSettings ( );
  }
        
  Office::AnswerWizardPtr getAnswerWizard ( )
  {
    return word->GetAnswerWizard ( );
  }
    
  enum Office::MsoFeatureInstall getFeatureInstall ( )
  {
    return word->GetFeatureInstall ( );
  }
    
  void putFeatureInstall (
          enum Office::MsoFeatureInstall prop )
  {
    word->PutFeatureInstall (
            prop );
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
          VARIANT * fileName = &vtMissing,
          VARIANT * activePrinterMacGX = &vtMissing,
          VARIANT * manualDuplexPrint = &vtMissing,
          VARIANT * printZoomColumn = &vtMissing,
          VARIANT * printZoomRow = &vtMissing,
          VARIANT * printZoomPaperWidth = &vtMissing,
          VARIANT * printZoomPaperHeight = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word-> PrintOut2000 (
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
            fileName,
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
    
  _variant_t run (
          _bstr_t macroName,
          VARIANT * varg1 = &vtMissing,
          VARIANT * varg2 = &vtMissing,
          VARIANT * varg3 = &vtMissing,
          VARIANT * varg4 = &vtMissing,
          VARIANT * varg5 = &vtMissing,
          VARIANT * varg6 = &vtMissing,
          VARIANT * varg7 = &vtMissing,
          VARIANT * varg8 = &vtMissing,
          VARIANT * varg9 = &vtMissing,
          VARIANT * varg10 = &vtMissing,
          VARIANT * varg11 = &vtMissing,
          VARIANT * varg12 = &vtMissing,
          VARIANT * varg13 = &vtMissing,
          VARIANT * varg14 = &vtMissing,
          VARIANT * varg15 = &vtMissing,
          VARIANT * varg16 = &vtMissing,
          VARIANT * varg17 = &vtMissing,
          VARIANT * varg18 = &vtMissing,
          VARIANT * varg19 = &vtMissing,
          VARIANT * varg20 = &vtMissing,
          VARIANT * varg21 = &vtMissing,
          VARIANT * varg22 = &vtMissing,
          VARIANT * varg23 = &vtMissing,
          VARIANT * varg24 = &vtMissing,
          VARIANT * varg25 = &vtMissing,
          VARIANT * varg26 = &vtMissing,
          VARIANT * varg27 = &vtMissing,
          VARIANT * varg28 = &vtMissing,
          VARIANT * varg29 = &vtMissing,
          VARIANT * varg30 = &vtMissing )
  {
    return word->Run (
            macroName,
            varg1,
            varg2,
            varg3,
            varg4,
            varg5,
            varg6,
            varg7,
            varg8,
            varg9,
            varg10,
            varg11,
            varg12,
            varg13,
            varg14,
            varg15,
            varg16,
            varg17,
            varg18,
            varg19,
            varg20,
            varg21,
            varg22,
            varg23,
            varg24,
            varg25,
            varg26,
            varg27,
            varg28,
            varg29,
            varg30 );
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
          VARIANT * fileName = &vtMissing,
          VARIANT * activePrinterMacGX = &vtMissing,
          VARIANT * manualDuplexPrint = &vtMissing,
          VARIANT * printZoomColumn = &vtMissing,
          VARIANT * printZoomRow = &vtMissing,
          VARIANT * printZoomPaperWidth = &vtMissing,
          VARIANT * printZoomPaperHeight = &vtMissing )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->PrintOut (
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
            fileName,
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
    
  enum Office::MsoAutomationSecurity getAutomationSecurity ( )
  {
    return word->GetAutomationSecurity ( );
  }
    
  void putAutomationSecurity (
          enum Office::MsoAutomationSecurity prop )
  {
    word->PutAutomationSecurity (
            prop );
  }
    
  Office::FileDialogPtr getFileDialog (
          enum Office::MsoFileDialogType fileDialogType )
  {
    return word->GetFileDialog (
            fileDialogType );
  }
    
  _bstr_t getEmailTemplate ( )
  {
    return word->GetEmailTemplate ( );
  }
    
  void putEmailTemplate (
          _bstr_t prop )
  {
    word->PutEmailTemplate (
            prop );
  }
    
  VARIANT_BOOL getShowWindowsInTaskbar ( )
  {
    return word->GetShowWindowsInTaskbar ( );
  }
    
  void putShowWindowsInTaskbar (
          VARIANT_BOOL prop )
  {
    word->PutShowWindowsInTaskbar (
            prop );
  }
    
  Office::NewFilePtr getNewDocument ( )
  {
    return word->GetNewDocument ( );
  }
    
  VARIANT_BOOL getShowStartupDialog ( )
  {
    return word->GetShowStartupDialog ( );
  }
    
  void putShowStartupDialog (
          VARIANT_BOOL prop )
  {
    word->PutShowStartupDialog (
            prop );
  }
    
  Word::AutoCorrectPtr getAutoCorrectEmail ( )
  {
    return word->GetAutoCorrectEmail ( );
  }
    
  Word::TaskPanesPtr getTaskPanes ( )
  {
    return word->GetTaskPanes ( );
  }
    
  VARIANT_BOOL getDefaultLegalBlackline ( )
  {
    return word->GetDefaultLegalBlackline ( );
  }
    
  void putDefaultLegalBlackline (
          VARIANT_BOOL prop )
  {
    word->PutDefaultLegalBlackline (
            prop );
  }
    
    
  Word::SmartTagRecognizersPtr getSmartTagRecognizers ( )
  {
    return word->GetSmartTagRecognizers ( );
  }
    
  Word::SmartTagTypesPtr getSmartTagTypes ( )
  {
    return word->GetSmartTagTypes ( );
  }
    
  Word::XMLNamespacesPtr getXMLNamespaces ( )
  {
    return word->GetXMLNamespaces ( );
  }
    
  HRESULT putFocusInMailHeader ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->PutFocusInMailHeader ( ))) {
      throw hr;
    }
    return hr; 
  }
      
  VARIANT_BOOL getArbitraryXMLSupportAvailable ( )
  {
    return word->GetArbitraryXMLSupportAvailable ( );
  }
    
  _bstr_t getBuildFull ( )
  {
    return word->GetBuildFull ( );
  }
    
  _bstr_t getBuildFeatureCrew ( )
  {
    return word->GetBuildFeatureCrew ( );
  }
    
  HRESULT loadMasterList (
          _bstr_t fileName )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = word->LoadMasterList (
            fileName ))) {
      throw hr;
    }
    return hr; 
  }
    
  Word::_DocumentPtr compareDocuments (
          struct Word::_Document * originalDocument,
          struct Word::_Document * revisedDocument,
          enum Word::WdCompareDestination destination,
          enum Word::WdGranularity granularity,
          VARIANT_BOOL compareFormatting,
          VARIANT_BOOL compareCaseChanges,
          VARIANT_BOOL compareWhitespace,
          VARIANT_BOOL compareTables,
          VARIANT_BOOL compareHeaders,
          VARIANT_BOOL compareFootnotes,
          VARIANT_BOOL compareTextboxes,
          VARIANT_BOOL compareFields,
          VARIANT_BOOL compareComments,
          VARIANT_BOOL compareMoves,
          _bstr_t revisedAuthor,
          VARIANT_BOOL ignoreAllComparisonWarnings )
  {
    return word->CompareDocuments (
            originalDocument,
            revisedDocument,
            destination,
            granularity,
            compareFormatting,
            compareCaseChanges,
            compareWhitespace,
            compareTables,
            compareHeaders,
            compareFootnotes,
            compareTextboxes,
            compareFields,
            compareComments,
            compareMoves,
            revisedAuthor,
            ignoreAllComparisonWarnings );

  }
    
  Word::_DocumentPtr mergeDocuments (
          struct Word::_Document * originalDocument,
          struct Word::_Document * revisedDocument,
          enum Word::WdCompareDestination destination,
          enum Word::WdGranularity granularity,
          VARIANT_BOOL compareFormatting,
          VARIANT_BOOL compareCaseChanges,
          VARIANT_BOOL compareWhitespace,
          VARIANT_BOOL compareTables,
          VARIANT_BOOL compareHeaders,
          VARIANT_BOOL compareFootnotes,
          VARIANT_BOOL compareTextboxes,
          VARIANT_BOOL compareFields,
          VARIANT_BOOL compareComments,
          VARIANT_BOOL compareMoves,
          _bstr_t originalAuthor,
          _bstr_t revisedAuthor,
          enum Word::WdMergeFormatFrom formatFrom )
  {
    return word->MergeDocuments (
            originalDocument,
            revisedDocument,
            destination,
            granularity,
            compareFormatting,
            compareCaseChanges,
            compareWhitespace,
            compareTables,
            compareHeaders,
            compareFootnotes,
            compareTextboxes,
            compareFields,
            compareComments,
            compareMoves,
            originalAuthor,
            revisedAuthor,
            formatFrom );
  }

    
  Word::BibliographyPtr getBibliography ( )
  {
    return word->GetBibliography ( );
  }

    
  VARIANT_BOOL getShowStylePreviews ( )
  {
    return word->GetShowStylePreviews ( );
  }
    
  void putShowStylePreviews (
          VARIANT_BOOL prop )
  {
    word->PutShowStylePreviews (
            prop );
  }
    
  VARIANT_BOOL getRestrictLinkedStyles ( )
  {
    return word->GetRestrictLinkedStyles ( );
  }
    
  void putRestrictLinkedStyles (
          VARIANT_BOOL prop )
  {
    word->PutRestrictLinkedStyles (
            prop );
  }
    
  Word::OMathAutoCorrectPtr getOMathAutoCorrect ( )
  {
    return word->GetOMathAutoCorrect ( );
  }

    
  VARIANT_BOOL getDisplayDocumentInformationPanel ( )
  {
    return word->GetDisplayDocumentInformationPanel ( );
  }
    
  void putDisplayDocumentInformationPanel (
          VARIANT_BOOL prop )
  {
    word->PutDisplayDocumentInformationPanel (
            prop );
  }
    
  Office::IAssistancePtr getAssistance ( )
  {
    return word->GetAssistance ( );
  }
    
  VARIANT_BOOL getOpenAttachmentsInFullScreen ( )
  {
    return word->GetOpenAttachmentsInFullScreen ( );
  }
    
  void putOpenAttachmentsInFullScreen (
          VARIANT_BOOL prop )
  {
    word->PutOpenAttachmentsInFullScreen (
            prop );
  }
    
  long getActiveEncryptionSession ( )
  {
    return word->GetActiveEncryptionSession ( );
  }
    
  VARIANT_BOOL getDontResetInsertionPointProperties ( )
  {
    return word->GetDontResetInsertionPointProperties ( );
  }
    
  void putDontResetInsertionPointProperties (
          VARIANT_BOOL prop )
  {
    word->PutDontResetInsertionPointProperties (
            prop );
  }

};

}
