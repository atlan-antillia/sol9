/******************************************************************************
 *
 * Copyright (c) 1999-2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  StrDef.h
 *
 *****************************************************************************/

// SOL9

// Note: The XmN* notation is from OSF/Motif.
// 2009/11/01 Modified not to use StrDef.cpp

#pragma once

#include <sol\auxdef.h>
#include <tchar.h>

//2009/11/03

const TCHAR* XmNaccessMode       = _T("accessMode");
const TCHAR* XmNacceleratorName  = _T("acceleratorName");
const TCHAR* XmNacceptFiles    = _T("acceptFiles");
const TCHAR* XmNactivateCallback   = _T("activateCallback");
const TCHAR* XmNalignment    = _T("alignment");
const TCHAR* XmNapplyCallback         = _T("applyCallback");
const TCHAR* XmNarmCallback           = _T("armCallback");
const TCHAR* XmNbackground    = _T("background");
const TCHAR* XmNbeginEditCallback = _T("beginEditCallback");

const TCHAR* XmNbitmap    = _T("bitmap");
const TCHAR* XmNborderWidth    = _T("borderWidth");
const TCHAR* XmNbrowseSelectionCallback = _T("browseSelectionCallback");
const TCHAR* XmNcancelCallback  = _T("cancelCallback");
const TCHAR* XmNTCHARSet    = _T("TCHARSet");
const TCHAR* XmNchildId          = _T("childId");
const TCHAR* XmNclassName          = _T("className");
const TCHAR* XmNclassStyle    = _T("classStyle");
const TCHAR* XmNclipPrecision    = _T("clipPrecision");
const TCHAR* XmNclsExtra    = _T("clsExtra");
const TCHAR* XmNcolumn    = _T("column");
const TCHAR* XmNcursor    = _T("cursor");
const TCHAR* XmNcustomFilter          = _T("customFilter");
const TCHAR* XmNdataType    = _T("dataType");
const TCHAR* XmNdc            = _T("dc");
const TCHAR* XmNdefaultActionCallback  = _T("defaultActionCallback");
//const TCHAR* XmNdeleteItemCallback      = _T("deleteItemCallback");

const TCHAR* XmNdialogUnit          = _T("dialogUnit");
const TCHAR* XmNdialogTitle    = _T("dialogTitle");
const TCHAR* XmNdirectory          = _T("directory");
const TCHAR* XmNdirection        = _T("direction");

const TCHAR* XmNdisableNoScroll  = _T("disableNoScroll");
const TCHAR* XmNdisabled    = _T("disabled");
const TCHAR* XmNdragBeginCallback = _T("dragBeginCallback");

const TCHAR* XmNdragFinishedCallback = _T("dragFinishedCallback");

const TCHAR* XmNendEditCallback = _T("endEditCallback");

const TCHAR* XmNescapement    = _T("escapement");
const TCHAR* XmNexposeCallback    = _T("exposeCallback");
const TCHAR* XmNexStyle        = _T("exStyle");
const TCHAR* XmNextendedSel    = _T("extendedSel");
const TCHAR* XmNextension             = _T("extension");
const TCHAR* XmNfaceName    = _T("faceName");
const TCHAR* XmNfileName    = _T("fileName");
const TCHAR* XmNfileTitle    = _T("fileTitle");
const TCHAR* XmNfilter          = _T("filter");
const TCHAR* XmNfilterIndex  = _T("filterIndex");

const TCHAR* XmNfindString    = _T("findString");
const TCHAR* XmNflags            = _T("flags");
const TCHAR* XmNforeground    = _T("foreground");
const TCHAR* XmNframe      = _T("frame");
//const TCHAR* XmNgetDispInfoCallback = _T("getDispInfoCallback");

const TCHAR* XmNgroup      = _T("group");
const TCHAR* XmNheight       = _T("height");
const TCHAR* XmNhelpCallback          = _T("helpCallback");
const TCHAR* XmNhook            = _T("hook");
const TCHAR* XmNhorizScrollBar  = _T("horizScrollBar");
const TCHAR* XmNhorizScrollCallback   = _T("horizScrollCallback");
const TCHAR* XmNhorizScrollMaximum    = _T("horizScrollMaximum");
const TCHAR* XmNhorizScrollMinimum    = _T("horizScrollMinimum");
const TCHAR* XmNhorizThumbPosition  = _T("horizThumbPosition");
const TCHAR* XmNicon      = _T("icon");
const TCHAR* XmNiconFile    = _T("iconFile");
const TCHAR* XmNid          = _T("id");
//const TCHAR* XmNinsertItemCallback = _T("insertItemCallback");

const TCHAR* XmNinstance    = _T("instance");
const TCHAR* XmNinvert    = _T("invert");
const TCHAR* XmNitalic    = _T("italic");
const TCHAR* XmNitemCount    = _T("itemCount");
const TCHAR* XmNitems      = _T("items");
const TCHAR* XmNitemsList    = _T("itemsList");
const TCHAR* XmNlabel         = _T("label");
const TCHAR* XmNlabelString    = _T("labelString");
const TCHAR* XmNlabelType    = _T("labelType");
const TCHAR* XmNlabelWidth    = _T("labelWidth");
const TCHAR* XmNlineIncrement         = _T("lineIncrement");
const TCHAR* XmNloader    = _T("loader");
const TCHAR* XmNlogicalFont    = _T("logicalFont");
const TCHAR* XmNlowerCase    = _T("lowerCase");

const TCHAR* XmNmargin    = _T("margin");
const TCHAR* XmNmaximum          = _T("maximum");
const TCHAR* XmNmaxLength    = _T("maxLength");
const TCHAR* XmNmdiChild          = _T("mdiChild");
const TCHAR* XmNmdiClientStyle        = _T("mdiClientStyle");
const TCHAR* XmNmenuCallback       = _T("menuCallback");
const TCHAR* XmNmenuId          = _T("menuId");
const TCHAR* XmNmenuList    = _T("menuList");
const TCHAR* XmNmenuName    = _T("menuName");
const TCHAR* XmNminimum          = _T("minimum");
const TCHAR* XmNmultiColumn    = _T("multiColumn");
const TCHAR* XmNmultiLine          = _T("multiLine");
const TCHAR* XmNmultipleSel    = _T("multipleSel");
const TCHAR* XmNnoConfiguration  = _T("noConfiguration");
const TCHAR* XmNnoHideSel    = _T("noHideSel");
const TCHAR* XmNnoPrefix    = _T("noPrefix");
const TCHAR* XmNoemConvert    = _T("oemConvert");

const TCHAR* XmNokCallback          = _T("okCallback");
const TCHAR* XmNorientation    = _T("orientation");
const TCHAR* XmNoutputPrecision  = _T("outputPrecision");
const TCHAR* XmNpageIncrement          = _T("pageIncrement");
const TCHAR* XmNparam            = _T("param");
const TCHAR* XmNpassword    = _T("password");
const TCHAR* XmNpattern          = _T("pattern");
const TCHAR* XmNpitchAndFamily  = _T("pitchAndFamily");
const TCHAR* XmNpredefined    = _T("predefined");
const TCHAR* XmNquality    = _T("quality");
const TCHAR* XmNreadOnly    = _T("readOnly");

const TCHAR* XmNrecomputeSize    = _T("recomputeSize");
const TCHAR* XmNreplaceString    = _T("replaceString");
const TCHAR* XmNrgbResult    = _T("rgbResult");
const TCHAR* XmNfileSave    = _T("fileSave");

// SOL++ 1.2
const TCHAR* XmNselChangeCallback = _T("selChangeCallback");

const TCHAR* XmNscrollBar    = _T("scrollBar");
const TCHAR* XmNshadow    = _T("shadow");
const TCHAR* XmNsortItems    = _T("sortItems");
const TCHAR* XmNspacing    = _T("spacing");
const TCHAR* XmNstrikeout    = _T("strikeout");
const TCHAR* XmNstyle         = _T("style");
const TCHAR* XmNtabStop    = _T("tabStop");
const TCHAR* XmNtemplateName  = _T("templateName"); 
const TCHAR* XmNthickness    = _T("thickness");
const TCHAR* XmNthumbPosition  = _T("thumbPosition");
const TCHAR* XmNtype         = _T("type");
const TCHAR* XmNunderline    = _T("underline");
const TCHAR* XmNupperCase    = _T("upperCase");

const TCHAR* XmNuseTabStops    = _T("useTabStops");

const TCHAR* XmNvertScrollBar    = _T("vertScrollBar");
const TCHAR* XmNvertScrollCallback    = _T("vertScrollCallback");
const TCHAR* XmNvertScrollMaximum     = _T("vertScrollMaximum");
const TCHAR* XmNvertScrollMinimum     = _T("vertScrollMinimum");
const TCHAR* XmNvertThumbPosition  = _T("vertThumbPosition");
const TCHAR* XmNvalue      = _T("value");
const TCHAR* XmNvisible    = _T("visible");
const TCHAR* XmNwantKeyboardInput  = _T("wantKeyboardInput");
const TCHAR* XmNweight    = _T("weight");
const TCHAR* XmNwidth         = _T("width");
const TCHAR* XmNwindowIcon    = _T("windowIcon");
const TCHAR* XmNwndExtra    = _T("wndExtra");
const TCHAR* XmNwndProc    = _T("wndProc");
const TCHAR* XmNx         = _T("x");
const TCHAR* XmNy         = _T("y");

// SOL++2.0
const TCHAR* XmNfocusId        = _T("focusId");

const TCHAR* XmNchangeCallback = _T("changeCallback");
const TCHAR* XmNerrorSpaceCallback = _T("errorSpaceCallback");
const TCHAR* XmNkillFocusCallback = _T("killFocusCallback");
const TCHAR* XmNmaxTextCallback = _T("maxTextCallback");
const TCHAR* XmNsetFocusCallback = _T("setFocusCallback");
const TCHAR* XmNupdateCallback = _T("updateCallback");

const TCHAR* XmNcloseUpCallback = _T("closeUpCallback");
const TCHAR* XmNdropDownCallback = _T("dropDownCallback");
const TCHAR* XmNeditChangeCallback = _T("editChangeCallback");
const TCHAR* XmNeditUpdateCallback = _T("editUpdateCallback");

const TCHAR* XmNselEndCancelCallback = _T("selEndCancelCallback");
const TCHAR* XmNselEndOkCallback = _T("selEndOkCallback");

const TCHAR* XmNselCancelCallback = _T("selCancelCallback");


// TreeView CommonControl callbacks
const TCHAR*   XmNgetDispInfoCallback = _T("getDispInfoCallback");
const TCHAR*  XmNbeginLabelEditCallback = _T("beginLabelEditCallback");
const TCHAR*  XmNendLabelEditCallback = _T("endLabelEditCallback");
const TCHAR*  XmNbeginDragCallback = _T("beginDragCallback");
const TCHAR*  XmNbeginRDragCallback = _T("beginRDragCallback");
const TCHAR*  XmNitemExpandingCallback = _T("itemExpandingCallback");
const TCHAR*  XmNitemExpandedCallback = _T("itemExpandedCallback");
const TCHAR*  XmNdeleteItemCallback = _T("deleteItemCallback");
const TCHAR*   XmNkeyDownCallback  = _T("keyDownCallback");

// PropertyDialog 
const TCHAR*  XmNstartPage         = _T("startPage");
const TCHAR*  XmNpages      = _T("pages");

// PropertySheetPage 
const TCHAR*  XmNsetActiveCallback  = _T("setActiveCallback");
const TCHAR*  XmNkillActiveCallback = _T("killActiveCallback");
const TCHAR*  XmNresetCallback   = _T("resetCallback");
const TCHAR*  XmNhasHelpCallback = _T("hasHelpCallback");
const TCHAR*  XmNwizBackCallback = _T("wizBackCallback");
const TCHAR*  XmNwizNextCallback = _T("wizNextCallback");
const TCHAR*  XmNwizFinishCallback = _T("wizFinishCallback");
const TCHAR*  XmNqueryCancelCallback = _T("queryCancelCallback");

// SOL++1.2 ListView NotifyCallback

const TCHAR* XmNitemChangingCallback   = _T("itemChangingCallback");
const TCHAR* XmNitemChangedCallback    = _T("itemChangedCallback");
const TCHAR* XmNinsertItemCallback     = _T("insertItemCallback");
const TCHAR* XmNenableEditCallback     = _T("enableEditCallback");
const TCHAR* XmNdeleteAllItemsCallback = _T("deleteAllItemsCallback");
const TCHAR* XmNcolumnClickCallback  = _T("columnClickCallback");
const TCHAR* XmNsetDispInfoCallback  = _T("setDispInfoCallback");

const TCHAR* XmNselChangingCallback  = _T("selChangingCallback");
const TCHAR* XmNselChangedCallback      = _T("selChangedCallback");

// Header control 
const TCHAR* XmNitemClickCallback    = _T("itemClickCallback");
const TCHAR* XmNitemDoubleClickCallback  = _T("itemDoubleClickCallback");
const TCHAR* XmNdividerDoubleClickCallback = _T("dividerDoubleClickCallback");
const TCHAR* XmNbeginTrackCallback    = _T("beginTrackCallback");
const TCHAR* XmNendTrackCallback    = _T("endTrackCallback");
const TCHAR* XmNtrackCallback      = _T("trackCallback");

// Toolbar
const TCHAR* XmNgetButtonInfoCallback = _T("getButtonInfoCallback");
const TCHAR* XmNendDragCallback    = _T("endDragCallback");
const TCHAR* XmNbeginAdjustCallback  = _T("beginAdjustCallback");
const TCHAR* XmNendAdjustCallback    = _T("endAdjustCallback");

const TCHAR* XmNqueryInsertCallback  = _T("queryInsertCallback");
const TCHAR* XmNqueryDeleteCallback  = _T("queryDeleteCallback");

const TCHAR* XmNtoolbarChangeCallback  = _T("toolbarChangeCallback");
const TCHAR* XmNcustHelpCallback    = _T("custHelpCallback");

// Tooltips
const TCHAR* XmNneedTextCallback  = _T("needTextCallback");
const TCHAR* XmNpopupCallback    = _T("popupCallback");
const TCHAR* XmNshowCallback    = _T("showCallback");

// ToolBar
const TCHAR* XmNenableThumbTrack = _T("enableThumbTrack");
const TCHAR* XmNtoolBarBitmapID  = _T("toolBarBitmapID");

const TCHAR* XmNdefaultToolBar = _T("defaultToolBar");
const TCHAR* XmNdefaultStatusBar = _T("defaultStatusBar");

const TCHAR* XmNnumBitmaps    = _T("numBitmaps");

// RichText
const TCHAR* XmNcorrectTextCallback = _T("correctTextCallback");
const TCHAR* XmNdropFilesCallback   = _T("dropFilesCallback");
const TCHAR* XmNmsgFilterCallback   = _T("msgFilterCallback");
const TCHAR* XmNprotectedCallback   = _T("protecteCallback");
const TCHAR* XmNrequestResizeCallback = _T("requestResizeCallback");
const TCHAR* XmNstopNoUndoCallback    = _T("stopUndoCallback");


// Common notification

const TCHAR* XmNclickCallback    = _T("clickCallback");
const TCHAR* XmNdoubleClickCallback = _T("doubleClickCallback");
const TCHAR* XmNreturnCallback    = _T("returnCallback");
const TCHAR* XmNrightClickCallback = _T("rightClickCallback");
const TCHAR* XmNrightDoubleClickCallback = _T("rightDoubleClickCallback");

const TCHAR* XmNdeltaPosCallback = _T("deltaPosCallback");

// SOL++ 2.1
const TCHAR* XmNimageName  = _T("imageName");
const TCHAR* XmNxImageSize = _T("xImageSize");
const TCHAR* XmNyImageSize = _T("yImageSize");
const TCHAR* XmNkeyInCallback = _T("keyInCallback");

const TCHAR* XmNcentering  = _T("centering");

// SOL++ 2.2
// 2008/07/02
const TCHAR* XmNuseDefaultFont = _T("useDefaultFont");
const TCHAR* XmNgradientBaseColor = _T("gradientBaseColor");
const TCHAR* XmNpointSize    = _T("pointSize");

// SOL9
// 2008/09/15
const TCHAR* XmNlink = _T("link");

// 2009/09/07
const TCHAR* XmNiconId  = _T("iconId");
const TCHAR* XmNiconName = _T("iconName");

// 2009/10/08
const TCHAR* XmNcharSet  = _T("charSet");
// 2009/10/08
const TCHAR* XmNurl  = _T("url");


// 2012/04/07
const TCHAR* XmNimageFileName  = _T("imageFileName");
const TCHAR* XmNscaling  = _T("scaling");

const TCHAR* XmNitemHeight = _T("itemHeight");
const TCHAR* XmNrgbStep       = _T("rgbStep");

// 2012/06/09
const TCHAR* XmNsliderTitle = _T("sliderTitle");
const TCHAR* XmNsliderRange = _T("sliderRange");
const TCHAR* XmNsliderPosition = _T("sliderPosition");

const TCHAR* XmNcolorChooserTitle = _T("colorChooserTitle");

const TCHAR* XmNhIcon = _T("hIcon");
const TCHAR* XmNiconResourceName = _T("iconResourceName");

const TCHAR* XmNtextColor = _T("textColor");
const TCHAR* XmNtextAlignment = _T("textAlignment");

const TCHAR* XmNbackgroundColor = _T("backgroundColor");

//GradientToolBar
const TCHAR* XmNgradientColor = _T("gradientColor");  //GradientToolBar::BACKGROUND enum
const TCHAR* XmNgradientContrast = _T("gradientContrast");  //Graident color contrast

//2012/07/10
const TCHAR* XmNfontSize = _T("fontSize"); 

//2015/10/01
const TCHAR* XmNtextString = _T("textString"); 
const TCHAR* XmNapplicationName = _T("applicationName");

const TCHAR* XmNapplicationDirectory = _T("applicationDirectory");

//2015/10/13
//DXGI_SWAP_CHAIN_DESC
const TCHAR* XmNbufferCount            = _T("bufferCount");
const TCHAR* XmNformat                 = _T("format");
const TCHAR* XmNrefreshRateNumerator   = _T("refreshRateNumerator");
const TCHAR* XmNrefreshRateDenominator = _T("refreshRateDenominator");
const TCHAR* XmNbufferUsage            = _T("bufferUsage");
const TCHAR* XmNsampleDescCount        = _T("sampleDescCount");
const TCHAR* XmNsampleDescQuality      = _T("sampleDescQuality");
const TCHAR* XmNoutputWindow           = _T("outputWindow");
const TCHAR* XmNwindowed               = _T("windowed");


const TCHAR* XmNmipLevels              = _T("mipLevels");

const TCHAR* XmNadapterIndex           = _T("adapterIndex");

//D3D10_TEXTURE2D_DESC
const TCHAR* XmNdescDepthUsage          = _T("descDepthUsage");
const TCHAR* XmNdescDepthBindFlags      = _T("descDepthBindFlags");
const TCHAR* XmNdescDepthCPUAccessFlags = _T("descDepthCPUAccessFlags");
const TCHAR* XmNdescDepthMiscFlags      = _T("descDepthMiscFlags");

    
const TCHAR* XmNrenderingInterval       = _T("renderingInterval");  //Specify interval(milliseconds) to call a virtual Window::render.

//EffectVariables 
const TCHAR* XmNtechnique               = _T("technique");

const TCHAR* XmNasScalar                = _T("asScaler");
const TCHAR* XmNasVector                = _T("asVector");
const TCHAR* XmNasMatrix                = _T("asMatrix");
const TCHAR* XmNasString                = _T("asString");
const TCHAR* XmNasShaderResource        = _T("asShaderResource");
const TCHAR* XmNasRenderTargetView      = _T("asRenderTargetView");
const TCHAR* XmNasDepthStencilView      = _T("asDepthStencilView");
const TCHAR* XmNasConstantBuffer        = _T("asConstantBuffer");
const TCHAR* XmNasShader                = _T("asShader");
const TCHAR* XmNasBlend                 = _T("asBlend");
const TCHAR* XmNasDepthStencil          = _T("asDepthStencil");
const TCHAR* XmNasRasterizer            = _T("asRasterizer");
const TCHAR* XmNasSampler               = _T("asSampler");

const TCHAR* XmNview                    = _T("view");
const TCHAR* XmNworld                   = _T("world");
const TCHAR* XmNprojection              = _T("projection");

const TCHAR* XmNshaderTexture           = _T("shaderTexture");   //ShaderResourceVariable

const TCHAR* XmNlightDirection          = _T("lightDirection");  //Vector
const TCHAR* XmNlightColor              = _T("lightColor");  //Vector
const TCHAR* XmNoutputColor             = _T("outputColor");  //Vector

const TCHAR* XmNambientColor            = _T("ambientColor");    //Vector
const TCHAR* XmNdiffuseColor            = _T("diffuseColor");    //Vector

const TCHAR* XmNcameraPosition          = _T("cameraPosition");  //Vector
const TCHAR* XmNspecularColor           = _T("specularColor");   //Vector
const TCHAR* XmNspecularPower           = _T("specularPower");   //Scaler

//2015/11/24
const TCHAR* XmNrenderTechnique         = _T("renderTechnique");
const TCHAR* XmNrenderLightTechnique    = _T("renderLightTechnique");

//2016/07/10
const TCHAR* XmNmajorVersion            = _T("majorVersion");
const TCHAR* XmNminorVersion            = _T("minorVersion");

const TCHAR* XmNeraseBackground         = _T("eraseBackground");

const TCHAR* XmNargc                    = _T("argc");
const TCHAR* XmNargv                    = _T("argv");
      
//2017/03/26
const TCHAR* XmNimageLoadingFlag        = _T("imageLoadingFlag");
const TCHAR* XmNtitle                   = _T("title");
const TCHAR* XmNstartingDirectory       = _T("startingDirectory");

const TCHAR* XmNimageResizePolicy       = _T("imageResizePolicy");

const TCHAR* XmNposition                = _T("position");
const TCHAR* XmNtrackBarScrollCallback  = _T("trackBarScrollCallback");
const TCHAR* XmNdisplayDigit            = _T("displayDigit");
const TCHAR* XmNdisplayOddValue         = _T("displayOddValue");
const TCHAR* XmNdisplayFloatValue       = _T("displayFloatValue");

const TCHAR* XmNdropCallback            = _T("dropCallback");

const TCHAR* XmNmouseCallback           = _T("mouseCallback");

//2017/07/20
const TCHAR* XmNcaptureAutoStart        = _T("captureAutoStart");

const TCHAR* XmNvideoDeviceIndex        = _T("videoDeviceIndex");
const TCHAR* XmNvideoFileName           = _T("videoFileName");

const TCHAR* XmNcaptureInterval         = _T("captureInterval");

const TCHAR* XmNfps                     = _T("fps");

const TCHAR* XmNimageScalingRatio       = _T("imageScalingRatio");
const TCHAR* XmNdefaultScale            = _T("defaultScale");

//2017/09/26
//Callback for RadioBox
const TCHAR* XmNcheckedCallback        = _T("checkedCallback");
//Callback for CheckBox
const TCHAR* XmNstateChangedCallback   = _T("stateChangedCallback");

const TCHAR* XmNitemWidth              = _T("itemWidth");
const TCHAR* XmNrgbColor               = _T("rgbColor");
const TCHAR* XmNtopPosition            = _T("topPosition");

