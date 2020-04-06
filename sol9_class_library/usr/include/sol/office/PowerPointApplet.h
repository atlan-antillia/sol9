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
 *  PowerPointApplet.h
 *
 *****************************************************************************/

//2010/04/08
//2010/05/05 Added a lot of public methods.
//2012/05/16 Added methods setTransparentAttributes and unsetTransparentAttributes

#pragma once

#include <sol/office/OfficeApplet.h>

//PowerPoint
//2015/12/25
#ifndef WIN64
#ifdef OFFICE2013
#import "C:\Program Files (x86)\Microsoft Office\OFFICE15\MSPPT.OLB" \
  rename("DocumentProperties","DocumentPropertiesPXL") \
  rename("RGB","RBGPXL") \
  rename("DialogBox","DialogBoxPXL") \
  rename("CopyFile","CopyFilePXL") \
  rename("ReplaceText","ReplaceTextPXL") \
  rename("FindText","FindTextPXL") \
  rename("ExitWindows","_ExitWindowsP")
#elif OFFICE2010
#import "C:\Program Files (x86)\Microsoft Office\OFFICE14\MSPPT.OLB" \
  rename("DocumentProperties","DocumentPropertiesPXL") \
  rename("RGB","RBGPXL") \
  rename("DialogBox","DialogBoxPXL") \
  rename("CopyFile","CopyFilePXL") \
  rename("ReplaceText","ReplaceTextPXL") \
  rename("FindText","FindTextPXL") \
  rename("ExitWindows","_ExitWindowsP")
#else
#import "C:\Program Files (x86)\Microsoft Office\OFFICE14\MSPPT.OLB" \
  rename("DocumentProperties","DocumentPropertiesPXL") \
  rename("RGB","RBGPXL") \
  rename("DialogBox","DialogBoxPXL") \
  rename("CopyFile","CopyFilePXL") \
  rename("ReplaceText","ReplaceTextPXL") \
  rename("FindText","FindTextPXL") \
  rename("ExitWindows","_ExitWindowsP")
#endif

#else 

#ifdef OFFICE2013
#import "C:\Program Files\Microsoft Office\OFFICE15\MSPPT.OLB" \
  rename("DocumentProperties","DocumentPropertiesPXL") \
  rename("RGB","RBGPXL") \
  rename("DialogBox","DialogBoxPXL") \
  rename("CopyFile","CopyFilePXL") \
  rename("ReplaceText","ReplaceTextPXL") \
  rename("FindText","FindTextPXL") \
  rename("ExitWindows","_ExitWindowsP")

#elif OFFICE2010
#import "C:\Program Files\Microsoft Office\OFFICE14\MSPPT.OLB" \
  rename("DocumentProperties","DocumentPropertiesPXL") \
  rename("RGB","RBGPXL") \
  rename("DialogBox","DialogBoxPXL") \
  rename("CopyFile","CopyFilePXL") \
  rename("ReplaceText","ReplaceTextPXL") \
  rename("FindText","FindTextPXL") \
  rename("ExitWindows","_ExitWindowsP")

#else
#import "C:\Program Files\Microsoft Office\OFFICE12\MSPPT.OLB" \
  rename("DocumentProperties","DocumentPropertiesPXL") \
  rename("RGB","RBGPXL") \
  rename("DialogBox","DialogBoxPXL") \
  rename("CopyFile","CopyFilePXL") \
  rename("ReplaceText","ReplaceTextPXL") \
  rename("FindText","FindTextPXL") \
  rename("ExitWindows","_ExitWindowsP")
#endif

#endif

namespace SOL {

/////////////////////////////////////////////////////////////////

class PowerPointApplet :public OfficeApplet {

private:
  PowerPoint::_ApplicationPtr powerPoint;

private:      
  PowerPoint::PresentationsPtr presentations;

private:
  bool isCreated;

public:
  PowerPointApplet()
  :powerPoint(NULL),
  presentations(NULL),
  isCreated(false)
  {
  
    IDispatch* pDisp = NULL;
    const wchar_t* application = L"PowerPoint.Application";

    if (getActiveObject(application, &pDisp)) {
      this->powerPoint = pDisp;    
      printf( "PowerPoint#PowerPoint,1,Found an active PowerPoint object\n");
    } else {
      HRESULT hr= this->powerPoint.CreateInstance(application);
      if (FAILED(hr)) {
        throw hr;
      } else {
        printf( "PowerPoint#PowerPoint,2,Created a PowerPoint object\n");
        isCreated = true;
      }
    }

    if (this->powerPoint) {
      this->presentations = powerPoint->Presentations;
    }
  }

public:
  ~PowerPointApplet()
  {
    if (this->powerPoint) {
      if (this->presentations != NULL) {
        int count = this->presentations->GetCount();  
        if (count == 0) {
          if (isCreated) {
            this->presentations = NULL;
            this->powerPoint->Quit();
          }
        }
        this->presentations = NULL;
        this->powerPoint = NULL;
      }
    }
  }

public:
  PowerPoint::_PresentationPtr open(const BSTR docName, bool visible=false)
  {
    if (isCreated) {
      this->powerPoint->PutWindowState(PowerPoint::ppWindowMinimized);

      if (visible==false) {
        this->powerPoint->PutVisible(Office::msoFalse);
      } else {
        this->powerPoint->PutVisible(Office::msoTrue);
      }
    }

    PowerPoint::_PresentationPtr presentation = NULL;

    try {
      presentation = this->presentations ->Open(docName, 
        Office::msoFalse, 
        Office::msoFalse, 
        Office::msoTrue);
    } catch (...) {

    }

    return presentation;

  }
  //2010/05/04

public:    
  PowerPoint::PresentationsPtr getPresentations ( )
  {
    return powerPoint->GetPresentations ( );
  }
    
  PowerPoint::DocumentWindowsPtr getWindows ( )
  {
    return powerPoint->GetWindows ( );
  }
    
  IUnknownPtr getDialogs ( )
  {
    return powerPoint->GetDialogs ( );
  }
    
  PowerPoint::DocumentWindowPtr getActiveWindow ( )
  {
    return powerPoint->GetActiveWindow ( );
  }
    
  PowerPoint::_PresentationPtr getActivePresentation ( )
  {
    return powerPoint->GetActivePresentation ( );
  }
    
  PowerPoint::SlideShowWindowsPtr getSlideShowWindows ( )
  {
    return powerPoint->GetSlideShowWindows ( );
  }
    
  Office::_CommandBarsPtr getCommandBars ( )
  {
    return powerPoint->GetCommandBars ( );
  }
    
  _bstr_t getPath ( )
  {
    return powerPoint->GetPath ( );
  }
    
  _bstr_t getName ( )
  {
    return powerPoint->GetName ( );
  }
    
  _bstr_t getCaption ( )
  {
    return powerPoint->GetCaption ( );
  }
    
  void putCaption (
          _bstr_t caption )
  {
    powerPoint->PutCaption (
            caption );
  }
    
  Office::AssistantPtr getAssistant ( )
  {
    return powerPoint->GetAssistant ( );
  }
    
  Office::FileSearchPtr getFileSearch ( )
  {
    return powerPoint->GetFileSearch ( );
  }
    
  Office::IFindPtr getFileFind ( )
  {
    return powerPoint->GetFileFind ( );
  }
    
  _bstr_t getBuild ( )
  {
    return powerPoint->GetBuild ( );
  }
    
  _bstr_t getVersion ( )
  {
    return powerPoint->GetVersion ( );
  }
    
  _bstr_t getOperatingSystem ( )
  {
    return powerPoint->GetOperatingSystem ( );
  }
    
  _bstr_t getActivePrinter ( )
  {
    return powerPoint->GetActivePrinter ( );
  }
    
  long getCreator ( )
  {
    return powerPoint->GetCreator ( );
  }
    
  PowerPoint::AddInsPtr getAddIns ( )
  {
    return powerPoint->GetAddIns ( );
  }
    
  VBIDE::VBEPtr getVBE ( )
  {
    return powerPoint->GetVBE ( );
  }
    
  HRESULT help (
          _bstr_t helpFile,
          int contextID )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->Help (
            helpFile,
            contextID )) ) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT quit ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->Quit ( )) ) {
      throw hr;
    }
    return hr;
  }
    
  _variant_t run (
          _bstr_t macroName,
          SAFEARRAY * * safeArrayOfParams )
  {
    return powerPoint->Run (
            macroName,
            safeArrayOfParams );
  }
    
  IUnknownPtr ppFileDialog (
          enum PowerPoint::PpFileDialogType type )
  {
    return powerPoint->PPFileDialog (
            type );
  }
    
  HRESULT launchSpelling (
          struct PowerPoint::DocumentWindow * pWindow )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->LaunchSpelling (
            pWindow )) ) {
      throw hr;
    }
    return hr;
  }
    
  float getLeft ( )
  {
    return powerPoint->GetLeft ( );
  }
    
  void putLeft (
          float left )
  {
    powerPoint->PutLeft (
            left );
  }
    
  float getTop ( )
  {
    return powerPoint->GetTop ( );
  }
    
  void putTop (
          float top )
  {
    powerPoint->PutTop (
            top );
  }
    
  float getWidth ( )
  {
    return powerPoint->GetWidth ( );
  }
    
  void putWidth (
          float width )
  {
    powerPoint->PutWidth (
            width );
  }
    
  float getHeight ( )
  {
    return powerPoint->GetHeight ( );
  }
    
  void putHeight (
          float height )
  {
    powerPoint->PutHeight (
            height );
  }
    
  enum PowerPoint::PpWindowState getWindowState ( )
  {
    return powerPoint->GetWindowState ( );
  }
    
  void putWindowState (
          enum PowerPoint::PpWindowState windowState )
  {
    powerPoint->PutWindowState (
            windowState );

  }
    
  enum Office::MsoTriState getVisible ( )
  {
    return powerPoint->GetVisible ( );
  }
    
  void putVisible (
          enum Office::MsoTriState visible )
  {
    powerPoint->PutVisible (
            visible );
  }
    
  long getHWND ( )
  {
    return powerPoint->GetHWND ( );
  }
    
  enum Office::MsoTriState getActive ( )
  {
    return powerPoint->GetActive ( );
  }
    
  HRESULT activate ( )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->Activate ( )) ) {
      throw hr;
    }
    return hr;
  }
    
  Office::AnswerWizardPtr getAnswerWizard ( )
  {
    return powerPoint->GetAnswerWizard ( );
  }
    
  Office::COMAddInsPtr getCOMAddIns ( )
  {
    return powerPoint->GetCOMAddIns ( );
  }
    
  _bstr_t getProductCode ( )
  {
    return powerPoint->GetProductCode ( );
  }
    
  PowerPoint::DefaultWebOptionsPtr getDefaultWebOptions ( )
  {
    return powerPoint->GetDefaultWebOptions ( );
  }
    
  Office::LanguageSettingsPtr getLanguageSettings ( )
  {
    return powerPoint->GetLanguageSettings ( );
  }
    
  Office::MsoDebugOptionsPtr getMsoDebugOptions ( )
  {
    return powerPoint->GetMsoDebugOptions ( );
  }
    
  enum Office::MsoTriState getShowWindowsInTaskbar ( )
  {
    return powerPoint->GetShowWindowsInTaskbar ( );
  }
    
  void putShowWindowsInTaskbar (
          enum Office::MsoTriState showWindowsInTaskbar )
  {
    powerPoint->PutShowWindowsInTaskbar (
            showWindowsInTaskbar );
  }
    
  IUnknownPtr getMarker ( )
  {
    return powerPoint->GetMarker ( );
  }
    
  enum Office::MsoFeatureInstall getFeatureInstall ( )
  {
    return powerPoint->GetFeatureInstall ( );
  }
    
  void putFeatureInstall (
          enum Office::MsoFeatureInstall featureInstall )
  {
    powerPoint->PutFeatureInstall (
            featureInstall );
  }
    
  VARIANT_BOOL getOptionFlag (
          long option,
          VARIANT_BOOL persist )
  {
    return powerPoint->GetOptionFlag (
            option,
            persist );
  }
    
  HRESULT setOptionFlag (
          long option,
          VARIANT_BOOL state,
          VARIANT_BOOL persist )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->SetOptionFlag (
            option,
            state,
            persist )) ) {
      throw hr;
    }
    return hr;
  }
    
  Office::FileDialogPtr getFileDialog (
            enum Office::MsoFileDialogType type )
  {
    return powerPoint->GetFileDialog (
            type );
  }
    
  enum Office::MsoTriState getDisplayGridLines ( )
  {
    return powerPoint->GetDisplayGridLines ( );
  }
    
  void putDisplayGridLines (
          enum Office::MsoTriState displayGridLines )
  {
    powerPoint->PutDisplayGridLines (
            displayGridLines );
  }
    
  enum Office::MsoAutomationSecurity getAutomationSecurity ( )
  {
    return powerPoint->GetAutomationSecurity ( );
  }
    
  void putAutomationSecurity (
          enum Office::MsoAutomationSecurity automationSecurity )
  {
    powerPoint->PutAutomationSecurity (
            automationSecurity );
  }
    
  Office::NewFilePtr getNewPresentation ( )
  {
    return powerPoint->GetNewPresentation ( );
  }
    
  enum PowerPoint::PpAlertLevel getDisplayAlerts ( )
  {
    return powerPoint->GetDisplayAlerts ( );
  }
    
  void putDisplayAlerts (
          enum PowerPoint::PpAlertLevel displayAlerts )
  {
    powerPoint->PutDisplayAlerts (
            displayAlerts );
  }
    
  enum Office::MsoTriState getShowStartupDialog ( )
  {
    return powerPoint->GetShowStartupDialog ( );
  }
    
  void putShowStartupDialog (
          enum Office::MsoTriState showStartupDialog )
  {
    powerPoint->PutShowStartupDialog (
            showStartupDialog );
  }
    
  HRESULT setPerfMarker (
          int marker )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->SetPerfMarker (
            marker )) ) {
      throw hr;
    }
    return hr;
  }
    
  PowerPoint::AutoCorrectPtr getAutoCorrect ( )
  {
    return powerPoint->GetAutoCorrect ( );
  }
    
  PowerPoint::OptionsPtr getOptions ( )
  {
    return powerPoint->GetOptions ( );
  }
    
  HRESULT launchPublishSlidesDialog (
          _bstr_t slideLibraryUrl )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->LaunchPublishSlidesDialog (
            slideLibraryUrl )) ) {
      throw hr;
    }
    return hr;
  }
    
  HRESULT launchSendToPPTDialog (
          VARIANT * slideUrls )
  {
    HRESULT hr = S_OK;
    if (FAILED(hr = powerPoint->LaunchSendToPPTDialog (
            slideUrls )) ) {
      throw hr;
    }
    return hr;
  }
    
  VARIANT_BOOL getDisplayDocumentInformationPanel ( )
  {
    return powerPoint->GetDisplayDocumentInformationPanel ( );
  }
    
  void putDisplayDocumentInformationPanel (
          VARIANT_BOOL displayDocumentInformationPanel )
  {
    powerPoint->PutDisplayDocumentInformationPanel (
            displayDocumentInformationPanel );
  }
    
  Office::IAssistancePtr getAssistance ( )
  {
    return powerPoint->GetAssistance ( );
  }
    
  long getActiveEncryptionSession ( )
  {
    return powerPoint->GetActiveEncryptionSession ( );
  }
    
  PowerPoint::FileConvertersPtr getFileConverters ( )
  {
    return powerPoint->GetFileConverters ( );
  }

public:
  //2012/05/16
  void setTransparentAttribute()
  {
    HWND hwnd = (HWND)powerPoint->HWND;
    if (hwnd) {
      SetWindowLong(hwnd, GWL_EXSTYLE, 
        GetWindowLong(hwnd, GWL_EXSTYLE)|WS_EX_LAYERED );
      SetLayeredWindowAttributes(hwnd,0,0, LWA_ALPHA|LWA_COLORKEY);
          
      if (isCreated) {
        ShowWindow(hwnd, SW_FORCEMINIMIZE);
        ShowWindow(hwnd, SW_SHOWMINIMIZED);
      }
    }
  }

public:
  //2012/05/16
  void unsetTransparentAttribute()
  {
    HWND hwnd = (HWND)powerPoint->HWND;
    if (hwnd) {
      if (isCreated) {
        ShowWindow(hwnd, SW_HIDE);
      }
      SetWindowLong(hwnd, GWL_EXSTYLE, 
        GetWindowLong(hwnd, GWL_EXSTYLE)^WS_EX_LAYERED);
      SetLayeredWindowAttributes(hwnd, 0, 0, 0);//LWA_ALPHA|LWA_COLORKEY);
    }
  }
};


}
