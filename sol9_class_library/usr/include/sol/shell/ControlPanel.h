/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ControlPanel.h
 *
 *****************************************************************************/


// 2012/11/18

#pragma once

#include <sol/com/ComIUnknown.h>
#include <shobjidl.h>



/*  
Usage:
    ControlPanel controlPanel;
    _bstr_t name = "Microsoft.InternetOptions";
    _bstr_t page = "3";
    controlPanel.open(name, page);
  //or
    controlPanel.open(L"Microsoft.InternetOptions", L"3");
 */

namespace SOL {

class ControlPanel: public ComIUnknown {

public:
  ControlPanel()
  {
    IOpenControlPanel *pPanel = NULL;

    HRESULT hr = CoCreateInstance(CLSID_OpenControlPanel, NULL, 
        CLSCTX_INPROC_SERVER, IID_IOpenControlPanel, 
        (void**)&pPanel);
    if (FAILED(hr)) {
      throw hr;
    } else {
      set(pPanel);
    }
  }
  
public:
  IOpenControlPanel* getPanel()
  {
    return (IOpenControlPanel*)getIUnknown();
  }



public:
  //This opens the Control Panel itself. 
  HRESULT open()
  {
    IOpenControlPanel* pPanel = getPanel();
    HRESULT hr = pPanel -> Open( 
        NULL,
        NULL,
        NULL);
    if (FAILED(hr)) {
      throw hr;
    }  
    return hr;
  }

public:

  HRESULT open( 
            /* [in] */ LPCWSTR pszName, //A pointer to the item's canonical name as a Unicode string. 
            /* [in] */ LPCWSTR pszPage = NULL,
            /* [in] */ IUnknown *punkSite = NULL)
  {
    IOpenControlPanel* pPanel = getPanel();
    HRESULT hr = pPanel -> Open( 
        pszName,
        pszPage,
        punkSite);
    if (FAILED(hr)) {
      throw hr;
    }  
    return hr;
  }

        
public:
  HRESULT getPath( 
            /* [in] */ LPCWSTR pszName,
            /* [out] */ LPWSTR pszPath,
            /* [in] */ UINT cchPath)
  {
    IOpenControlPanel* pPanel = getPanel();
    HRESULT hr = pPanel -> GetPath( 
        pszName,
        pszPath,
        cchPath);
    if (FAILED(hr)) {
      throw hr;
    }  
    return hr;
  }

public:
  _bstr_t getPath(/* [in] */ LPCWSTR pszName)
  {
    wchar_t path[1024];
    UINT    cchPath = CountOf(path);
    IOpenControlPanel* pPanel = getPanel();
    HRESULT hr = pPanel -> GetPath( 
        pszName,
        path,
        cchPath);
    if (FAILED(hr)) {
      throw hr;
    }  
    return _bstr_t(path);
  }

        
public:
  HRESULT getCurrentView( 
            /* [out] */ CPVIEW *pView)
  {
    IOpenControlPanel* pPanel = getPanel();
    HRESULT hr = pPanel -> GetCurrentView( 
      pView);
    if (FAILED(hr)) {
      throw hr;
    }  
    return hr;
  }

public:
  CPVIEW getCurrentView()
  {
    CPVIEW pView;
    IOpenControlPanel* pPanel = getPanel();
    HRESULT hr = pPanel -> GetCurrentView( 
      &pView);
    if (FAILED(hr)) {
      throw hr;
    }  
    return pView;
  }

  //Control Panel Canonical name
public:
  HRESULT actionCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.ActionCenter", pPage); // (Windows 7 and later only)    
  }
  HRESULT administrativeTools(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.AdministrativeTools", pPage);
  }

  HRESULT autoPlay(const wchar_t* pPage=NULL)
  {

    return open(L"Microsoft.AutoPlay", pPage);
  }

  HRESULT backupAndRestore(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.BackupAndRestore", pPage); //(Windows 7 and later only)  
  }

  HRESULT biometricDevices(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.BiometricDevices", pPage); //(Windows 7 and later only)  
  }

  HRESULT bitLockerDriveEncryption(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.BitLockerDriveEncryption", pPage);  
  }

  HRESULT colorManagement(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.ColorManagement", pPage); 
  }

  HRESULT credentialManager(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.CredentialManager", pPage); //(Windows 7 and later only) 
  }

  HRESULT dateAndTime(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.DateAndTime", pPage); 
  }

  HRESULT defaultLocation(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.DefaultLocation", pPage); //(Windows 7 and later only) 
  }

  HRESULT defaultPrograms(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.DefaultPrograms", pPage); 
  }

  HRESULT desktopGadgets(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.DesktopGadgets", pPage); //(Windows 7 and later only) 
  }

  HRESULT deviceManager(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.DeviceManager", pPage); 
  }

  HRESULT devicesAndPrinters(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.DevicesAndPrinters", pPage); //(Windows 7 and later only) 
  }

  HRESULT display(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Display", pPage); //(Windows 7 and later only) 
  }

  HRESULT easeOfAccessCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.EaseOfAccessCenter", pPage); 
  }

  HRESULT folderOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.FolderOptions", pPage); 
  }

  HRESULT fonts(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Fonts", pPage); 
  }

  HRESULT gameControllers(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.GameControllers", pPage); 
  }

  HRESULT getPrograms(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.GetPrograms", pPage); 
  }

  HRESULT gettingStarted(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.GettingStarted", pPage); //(Windows 7 and later only) 
  }

  HRESULT homeGroup(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.HomeGroup", pPage); //(Windows 7 and later only) 
  }

  HRESULT indexingOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.IndexingOptions", pPage); 
  }

  HRESULT infrared(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Infrared", pPage); //(Windows 7 and later only) 
  }

  HRESULT internetOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.InternetOptions", pPage); 
  }

  HRESULT iSCSIInitiator(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.iSCSIInitiator", pPage); 
  }

  HRESULT keyboard(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Keyboard", pPage); 
  }

  HRESULT locationAndOtherSensors(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.LocationAndOtherSensors", pPage); //(Windows 7 and later only)  
  }

  HRESULT mouse(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Mouse", pPage); 
  }

  HRESULT networkAndSharingCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.NetworkAndSharingCenter", pPage); 
  }

  HRESULT notificationAreaIcons(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.NotificationAreaIcons", pPage); //(Windows 7 and later only) 
  }

  HRESULT offlineFiles(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.OfflineFiles", pPage);
  }

  HRESULT parentalControls(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.ParentalControls", pPage); 
  }

  HRESULT penAndTouch(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PenAndTouch", pPage); //(Windows 7 and later only) 
  }

  HRESULT peopleNearMe(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PeopleNearMe", pPage); 
  }

  HRESULT performanceInformationAndTools(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PerformanceInformationAndTools", pPage); 
  }

  HRESULT personalization(const wchar_t* pPage=NULL)
  {  
    return open(L"Microsoft.Personalization", pPage); 
  }

  HRESULT phoneAndModem(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PhoneAndModem", pPage); //(Windows 7 and later only) 
  }

  HRESULT powerOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PowerOptions", pPage); 
  }

  HRESULT programsAndFeatures(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.ProgramsAndFeatures", pPage); 
  }

  HRESULT recovery(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Recovery", pPage); //(Windows 7 and later only)  
  }

  HRESULT regionAndLanguage(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.RegionAndLanguage", pPage); //(Windows 7 and later only) 
  }

  HRESULT remoteAppAndDesktopConnections(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.RemoteAppAndDesktopConnections", pPage); //(Windows 7 and later only) 
  }

  HRESULT scannersAndCameras(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.ScannersAndCameras", pPage); 
  }

  HRESULT sound(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Sound", pPage); //(Windows 7 and later only) 
  }

  HRESULT speechRecognition(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.SpeechRecognition", pPage); //(Windows 7 and later only) 
  }

  HRESULT syncCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.SyncCenter", pPage);  
  }

  HRESULT system(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.System", pPage); 
  }

  HRESULT tabletPCSettings(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.TabletPCSettings", pPage); 
  }

  HRESULT taskbarAndStartMenu(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.TaskbarAndStartMenu", pPage); 
  }

  HRESULT textToSpeech(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.TextToSpeech", pPage); 
  }

  HRESULT troubleshooting(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Troubleshooting", pPage); //(Windows 7 and later only) 
  }

  HRESULT userAccounts(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.UserAccounts", pPage); 
  }

  HRESULT windowsAnytimeUpgrade(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WindowsAnytimeUpgrade", pPage); 
  }

  HRESULT cardSpace(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.CardSpace", pPage); 
  }

  HRESULT windowsDefender(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WindowsDefender", pPage); 
  }

  HRESULT windowsFirewall(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WindowsFirewall", pPage); 
  }

  HRESULT mobilityCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.MobilityCenter", pPage); 
  }

  HRESULT windowsSideShow(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WindowsSideShow", pPage); 
  }

  HRESULT windowsUpdate(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WindowsUpdate", pPage); 
  }

  //Windows Vista Control Panel Canonical Names

  HRESULT addHardware(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.AddHardware", pPage);
  }

  HRESULT audioDevicesAndSoundThemes(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.AudioDevicesAndSoundThemes", pPage);
  }

  HRESULT backupAndRestoreCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.BackupAndRestoreCenter", pPage);
  }

  HRESULT getProgramsOnline(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.GetProgramsOnline", pPage);
  }

  HRESULT infraredOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.InfraredOptions", pPage);
  }

  HRESULT penAndInputDevices(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PenAndInputDevices", pPage);
  }

  HRESULT phoneAndModemOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.PhoneAndModemOptions", pPage);
  }

  HRESULT printers(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.Printers", pPage);
  }

  HRESULT problemReportsAndSolutions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.ProblemReportsAndSolutions", pPage);
  }

  HRESULT regionalAndLanguageOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.RegionalAndLanguageOptions", pPage);
  }

  HRESULT securityCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.SecurityCenter", pPage);
  }

  HRESULT speechRecognitionOptions(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.SpeechRecognitionOptions", pPage);
  }

  HRESULT welcomeCenter(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WelcomeCenter", pPage);
  }

  HRESULT windowsSidebarProperties(const wchar_t* pPage=NULL)
  {
    return open(L"Microsoft.WindowsSidebarProperties", pPage);
  }
};

}
