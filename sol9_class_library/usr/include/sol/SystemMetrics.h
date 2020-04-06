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
 *  SystemMetrics.h
 *
 *****************************************************************************/

// SOL9
// 2012/07/25

#pragma once
#include <sol\Object.h>

/**
The comments on the methods of SystemMetrics class were taken from the following page: 
 http://msdn.microsoft.com/en-us/library/windows/desktop/ms724385(v=vs.85).aspx
*/

namespace SOL {

class SystemMetrics :public Object {

public:
  /*
  The flags that specify how the system arranged minimized windows.
  */
  int arrange()
  {
    return GetSystemMetrics(SM_ARRANGE);
  }

  /**
  The value that specifies how the system is started: 
  0 Normal boot
  1 Fail-safe boot
  2 Fail-safe with network boot
  */
  int cleanBoot()
  {
    return GetSystemMetrics(SM_CLEANBOOT);
  }
 

  /**
   The number of display monitors on a desktop. For more information, see the Remarks section in this topic. 
  */
  int monitors()
  {
    return GetSystemMetrics(SM_CMONITORS); 
  }

  /**
   The number of buttons on a mouse, or zero if no mouse is installed.
  */
  int mouseButton()
  {
    return GetSystemMetrics(SM_CMOUSEBUTTONS); 
  }
 

  /**
   The width of a window border, in pixels. This is equivalent to the SM_CXEDGE value for windows with the 3-D look.
  */
  int borderWidth()
  { 
    return GetSystemMetrics(SM_CXBORDER); 
  }

 
  /**
  The width of a cursor, in pixels.
  */
  int cursorWidth()
  {
    return GetSystemMetrics(SM_CXCURSOR); 
  }

 
  /**
  This value is the same as SM_CXFIXEDFRAME.
  */
  int dlgFrameWidth()
  {
    return GetSystemMetrics(SM_CXDLGFRAME); 
  }

 
  /**
  The width of the rectangle around the location of a first click in a double-click sequence, in pixels.
  */
  int doubleClkWidth()
  {
    return GetSystemMetrics(SM_CXDOUBLECLK); 
  }


  /**
  The number of pixels on either side of a mouse-down point that the mouse pointer can move before a drag operation begins.
  */
  int dragWidth()
  {
    return GetSystemMetrics(SM_CXDRAG); 
  }
  
 
  /**
  The width of a 3-D border, in pixels. This metric is the 3-D counterpart of SM_CXBORDER.
  */
  int edgeWidth()
  {
    return GetSystemMetrics(SM_CXEDGE); 
  }

 

  /**
  The thickness of the frame around the perimeter of a window that has a caption but is not sizable, in pixels.
  */
  int fixedFrameWidth()
  {
    return GetSystemMetrics(SM_CXFIXEDFRAME);
  }
 
  /**
  The width of the left and right edges of the focus rectangle that the DrawFocusRect draws. This value is in pixels. 
  */
  int focusBorderWidth()
  {
    return GetSystemMetrics(SM_CXFOCUSBORDER);
  }


  /**
  This value is the same as SM_CXSIZEFRAME.
  */
  int frameWidth()
  {
    return GetSystemMetrics(SM_CXFRAME);
  }
 

  /**
  The width of the client area for a full-screen window on the primary display monitor, in pixels.
  */
  int fullScreenWidth()
  {
    return GetSystemMetrics(SM_CXFULLSCREEN);
  }
 
  /**
  The width of the arrow bitmap on a horizontal scroll bar, in pixels.
  */
  int hScrollWidth()
  {
    return GetSystemMetrics(SM_CXHSCROLL); 
  }

 

  /**
  The width of the thumb box in a horizontal scroll bar, in pixels.
  */
  int hThumbWidth()
  {
    return GetSystemMetrics(SM_CXHTHUMB);
  }
 

  /**
  The default width of an icon, in pixels. 
  The LoadIcon function can load only icons with the dimensions that SM_CXICON and SM_CYICON specifies.
  */
  int iconWidth()
  {
    return GetSystemMetrics(SM_CXICON);
  }
 

  /**
  The width of a grid cell for items in large icon view, in pixels.
  */
  int iconSpacingWidth()
  {
    return GetSystemMetrics(SM_CXICONSPACING); 
   }

  /**
  The default width, in pixels, of a maximized top-level window on the primary display monitor.
  */
  int maximizedWidth()
  {
    return GetSystemMetrics(SM_CXMAXIMIZED); 
  }
 

  /**
  The default maximum width of a window that has a caption and sizing borders, in pixels.
  */
  int maxTrackWidth()
  {
    return GetSystemMetrics(SM_CXMAXTRACK); 
  }
 

  /**
  The width of the default menu check-mark bitmap, in pixels.
  */
  int menuCheckWidth()
  {
    return GetSystemMetrics(SM_CXMENUCHECK);
  }
 

  /**
  The width of menu bar buttons, such as the child window close button that is used in the multiple document interface, in pixels.
  */
  int menuSizeWidth()
  {
    return GetSystemMetrics(SM_CXMENUSIZE);
  }
 

  /**
  The minimum width of a window, in pixels.
  */
  int minWidth()
  {
    return GetSystemMetrics(SM_CXMIN); 
  }
 

  /**
  The width of a minimized window, in pixels.
  */
  int minimizedWidth()
  {
    return GetSystemMetrics(SM_CXMINIMIZED);
  }
 

  /**
  The width of a grid cell for a minimized window, in pixels.
  */
  int minSpacingWidth()
  {
    return GetSystemMetrics(SM_CXMINSPACING);
  }
 

  /**
  The minimum tracking width of a window, in pixels.
  */
  int minTrackWidth()
  {
    return GetSystemMetrics(SM_CXMINTRACK); 
  }

 

  /**
  The amount of border padding for captioned windows, in pixels.
  */
  int paddedBorderWidth()
  {
    return GetSystemMetrics(SM_CXPADDEDBORDER);
  }
 


  /**
  The width of the screen of the primary display monitor, in pixels.
  */
  int screenWidth()
  {
    return GetSystemMetrics(SM_CXSCREEN); 
  }

  /**
  The width of a button in a window caption or title bar, in pixels.
  */
  int sizeWidth()
  {
    return GetSystemMetrics(SM_CXSIZE); 
  }

 

  /**
  The thickness of the sizing border around the perimeter of a window that can be resized, in pixels.
  */
  int sizeFrameWidth()
  {
    return GetSystemMetrics(SM_CXSIZEFRAME); 
  }
 

  /**
  The recommended width of a small icon, in pixels. Small icons typically appear in window captions and in small icon view.
  */
  int smallIconWidth()
  {
    return GetSystemMetrics(SM_CXSMICON); 
  }
 

  /**
  The width of small caption buttons, in pixels.
  */
  int smallSizeWidth()
  {
    return GetSystemMetrics(SM_CXSMSIZE); 
  }
 

  /**
  The width of the virtual screen, in pixels.
  */
  int virtualScreenWidth()
  {
    return GetSystemMetrics(SM_CXVIRTUALSCREEN); 
  }


  /**
  The width of a vertical scroll bar, in pixels.
  */
  int vScrollWidth()
  {
    return GetSystemMetrics(SM_CXVSCROLL); 
  }
 

  /**
  The height of a window border, in pixels. This is equivalent to the SM_CYEDGE value for windows with the 3-D look.
  */
  int borderHeight()
  {
    return GetSystemMetrics(SM_CYBORDER); 
  }
 

  /**
  The height of a caption area, in pixels.
  */
  int captionHeight()
  {
    return GetSystemMetrics(SM_CYCAPTION); 
  }
 

  /**
  The height of a cursor, in pixels. The system cannot create cursors of other sizes.
  */
  int cursorHeight()
  {
    return GetSystemMetrics(SM_CYCURSOR); 
  }
 

  /**
  This value is the same as SM_CYFIXEDFRAME.
  */
  int dlgFrameHeight()
  {
    return GetSystemMetrics(SM_CYDLGFRAME); 
  }
 

  /**
  The height of the rectangle around the location of a first click in a double-click sequence, in pixels.
  */
  int doubleClkHeight()
  {
    return GetSystemMetrics(SM_CYDOUBLECLK); 
  }
 
  /**
  The number of pixels above and below a mouse-down point that the mouse pointer can move before a drag operation begins.
  */
  int dragHeight()
  {
    return GetSystemMetrics(SM_CYDRAG); 
  }


  /**
  The height of a 3-D border, in pixels. This is the 3-D counterpart of SM_CYBORDER.
  */
  int edgeHeight()
  {
    return GetSystemMetrics(SM_CYEDGE); 
  }
 

  /**
  The thickness of the frame around the perimeter of a window that has a caption but is not sizable, in pixels.
  */
  int fixedFrameHeight()
  {
    return GetSystemMetrics(SM_CYFIXEDFRAME); 
  }
 

  /**
  The height of the top and bottom edges of the focus rectangle drawn by DrawFocusRect. This value is in pixels.
  */
  int focusBorderHeight()
  {
    return GetSystemMetrics(SM_CYFOCUSBORDER); 
  }
 

 
  /**
  This value is the same as SM_CYSIZEFRAME.
  */
  int frameHeight()
  {
    return GetSystemMetrics(SM_CYFRAME); 
  }
 

  /**
  The height of the client area for a full-screen window on the primary display monitor, in pixels.
  */
  int fullScreenHeight()
  {
    return GetSystemMetrics(SM_CYFULLSCREEN); 
  }
 

  /**
  The height of a horizontal scroll bar, in pixels.
  */
  int hScrollHeight()
  {
    return GetSystemMetrics(SM_CYHSCROLL);
  }
 

  /**
  The default height of an icon, in pixels. 
  */
  int iconHeight()
  {
    return GetSystemMetrics(SM_CYICON); 
  }
 

  /**
  The height of a grid cell for items in large icon view, in pixels.
  */
  int iconSpacingHeight()
  {
    return GetSystemMetrics(SM_CYICONSPACING); 
  }

  /**
  For double byte character set versions of the system, this is the height of the Kanji window at the bottom of the screen, in pixels.
   */
  int kanjiWindowHeight()
  {
    return GetSystemMetrics(SM_CYKANJIWINDOW); 
  }


  /**
  The default height, in pixels, of a maximized top-level window on the primary display monitor.
  */
  int maximizedHeight()
  {
    return GetSystemMetrics(SM_CYMAXIMIZED); 
  }
 

  /**
  The default maximum height of a window that has a caption and sizing borders, in pixels. 
  */
  int maxTrackHeight()
  {
    return GetSystemMetrics(SM_CYMAXTRACK);
  }

  /**
  The height of a single-line menu bar, in pixels.
  */
  int menuHeight()
  {
    return GetSystemMetrics(SM_CYMENU); 
  }
 

  /**
  The height of the default menu check-mark bitmap, in pixels.
  */
  int menuCheckHeight()
  {
    return GetSystemMetrics(SM_CYMENUCHECK); 
  }
 

  /**
  The height of menu bar buttons, such as the child window close button that is used in the multiple document interface, in pixels.
  */
  int menuSizeHeight()
  {
    return GetSystemMetrics(SM_CYMENUSIZE);
  }
 

  /**
  The minimum height of a window, in pixels.
  */
  int minHeight()
  {
    return GetSystemMetrics(SM_CYMIN);
  }
 

  /**
  The height of a minimized window, in pixels.
  */
  int minimizedHeight()
  {
    return GetSystemMetrics(SM_CYMINIMIZED); 
  }
 

  /**
  The height of a grid cell for a minimized window, in pixels.
  */
  int minSpacingHeight()
  {
    return GetSystemMetrics(SM_CYMINSPACING); 
  } 

  /**
  The minimum tracking height of a window, in pixels. 
  */
  int minTrackHeight()
  {
    return GetSystemMetrics(SM_CYMINTRACK); 
  }
 

  /**
  The height of the screen of the primary display monitor, in pixels.
  */
  int screenHeight()
  {
    return GetSystemMetrics(SM_CYSCREEN); 
  }
 

  /**
  The height of a button in a window caption or title bar, in pixels.
  */
  int sizeHeight()
  {
    return GetSystemMetrics(SM_CYSIZE); 
  }
 

  /**
  The thickness of the sizing border around the perimeter of a window that can be resized, in pixels. 
  */
  int sizeFrameHeight()
  {
    return GetSystemMetrics(SM_CYSIZEFRAME); 
  }
 

  /**
  The height of a small caption, in pixels.
  */
  int smallCaptionHeight()
  {
    return GetSystemMetrics(SM_CYSMCAPTION); 
  }
 

  /**
  The recommended height of a small icon, in pixels. Small icons typically appear in window captions and in small icon view.
  */
  int smallIconHeight()
  {
    return GetSystemMetrics(SM_CYSMICON); 
  }
 

  /**
  The height of small caption buttons, in pixels.
  */
  int smallSizeHeight()
  {
    return GetSystemMetrics(SM_CYSMSIZE); 
  }
 

  /**
  The height of the virtual screen, in pixels. 
  */
  int virtualScreenHeight()
  {
    return GetSystemMetrics(SM_CYVIRTUALSCREEN); 
  }
 

  /**
  The height of the arrow bitmap on a vertical scroll bar, in pixels.
  */
  int vscrollHeight()
  {
    return GetSystemMetrics(SM_CYVSCROLL); 
  }
 

  /**
  The height of the thumb box in a vertical scroll bar, in pixels.
  */
  int vThumbHeight()
  {
    return GetSystemMetrics(SM_CYVTHUMB); 
  }

 

  /**
  Nonzero if User32.dll supports DBCS; otherwise, 0. 
  */
  int dbcsEnabled()
  {
    return GetSystemMetrics(SM_DBCSENABLED); 
  }




  /**
  Nonzero if the debug version of User.exe is installed; otherwise, 0.
  */
  int debug()
  {
    return GetSystemMetrics(SM_DEBUG); 
   }

  /**
  Nonzero if the current operating system is Windows 7 or Windows Server 2008 R2 and the Tablet PC Input service is started; otherwise, 0. 
  The return GetSystemMetrics(value is a bitmask that specifies the type of digitizer input supported by the device.
  */
  int digitizer()
  {
    return GetSystemMetrics(SM_DIGITIZER); 
  }


 

  /**
  Nonzero if Input Method Manager/Input Method Editor features are enabled; otherwise, 0.
  */
  int immEnabled()
  {
    return GetSystemMetrics(SM_IMMENABLED); 
  }
 

  /**
  Nonzero if there are digitizers in the system; otherwise, 0. 
  */
  int maxIMUMTouches()
  {
    return GetSystemMetrics(SM_MAXIMUMTOUCHES); 
  }

 

  /**
  Nonzero if the current operating system is the Windows XP, Media Center Edition, 0 if not.
  */
  int mediaCenter()
  {
    return GetSystemMetrics(SM_MEDIACENTER); 
  }
 

  /**
  Nonzero if drop-down menus are right-aligned with the corresponding menu-bar item; 0 if the menus are left-aligned.
  */
  int menuDropAlignment()
  {
    return GetSystemMetrics(SM_MENUDROPALIGNMENT); 
  }
 

  /**
  Nonzero if the system is enabled for Hebrew and Arabic languages, 0 if not.
  */
  int midEeastEnabled()
  {
    return GetSystemMetrics(SM_MIDEASTENABLED); 
  }
 
  /**
  Nonzero if a mouse is installed; otherwise, 0. This value is rarely zero, 
  because of support for virtual mice and because some systems detect the presence of the port instead of the presence of a mouse.
  */
  int mousePresent()
  {
    return GetSystemMetrics(SM_MOUSEPRESENT); 
  }
 

  /**
  Nonzero if a mouse with a horizontal scroll wheel is installed; otherwise 0.
  */
  int mouseHorizontalWheelPresent()
  {
    return GetSystemMetrics(SM_MOUSEHORIZONTALWHEELPRESENT);
  }
 
  /**
  Nonzero if a mouse with a vertical scroll wheel is installed; otherwise 0. 
  */
  int mouseWheelPresent()
  {
    return GetSystemMetrics(SM_MOUSEWHEELPRESENT); 
  }



  /**
  The least significant bit is set if a network is present; otherwise, it is cleared. The other bits are reserved for future use.
  */
  int network()
  {
    return GetSystemMetrics(SM_NETWORK); 
  }
 

  /**
  Nonzero if the Microsoft Windows for Pen computing extensions are installed; zero otherwise.
  */
  int penWindows()
  {
    return GetSystemMetrics(SM_PENWINDOWS); 
  }
 

  /**
  This system metric is used in a Terminal Services environment to determine if the current Terminal Server 
  session is being remotely controlled. Its value is nonzero if the current session is remotely controlled; otherwise, 0.
  */
  int remoteControl()
  {  
    return GetSystemMetrics(SM_REMOTECONTROL); 
  }
 
 

  /**
  This system metric is used in a Terminal Services environment. 
  */
  int remoteSession()
  {
    return GetSystemMetrics(SM_REMOTESESSION); 
  }

 

  /**
  Nonzero if all the display monitors have the same color format, otherwise, 0. 
  */
  int sameDisplayFormat()
  {  
    return GetSystemMetrics(SM_SAMEDISPLAYFORMAT); 
  }


  /**
  This system metric should be ignored; it always returns 0.
  */
  int secure()
  {
    return GetSystemMetrics(SM_SECURE); 
  }
 

  /**
  The build number if the system is Windows Server 2003 R2; otherwise, 0.
  */
  int serverR2()
  {
    return GetSystemMetrics(SM_SERVERR2); 
  }
 

  /**
  Nonzero if the user requires an application to present information visually in situations 
  where it would otherwise present the information only in audible form; otherwise, 0.
  */
  int showSounds()
  {
    return GetSystemMetrics(SM_SHOWSOUNDS); 
  }
 

  /**
  Nonzero if the current session is shutting down; otherwise, 0. 
  */
  int shuttingDown()
  {
    return GetSystemMetrics(SM_SHUTTINGDOWN); 
  }
 

  /**
  Nonzero if the computer has a low-end (slow) processor; otherwise, 0.
  */
  int slowMachine()
  {
    return GetSystemMetrics(SM_SLOWMACHINE); 
  }
 

  /**
  Nonzero if the current operating system is Windows 7 Starter Edition, Windows Vista Starter,
   or Windows XP Starter Edition; otherwise, 0.
  */
  int starter()
  {
    return GetSystemMetrics(SM_STARTER); 
  }

 
  /**
  Nonzero if the meanings of the left and right mouse buttons are swapped; otherwise, 0.
  */
  int swapButton()
  {
    return GetSystemMetrics(SM_SWAPBUTTON); 
  }
 

  /**
  Nonzero if the current operating system is the Windows XP Tablet PC edition or 
  if the current operating system is Windows Vista or Windows 7 and the Tablet PC Input service is started; otherwise, 0.
  */
  int tabletPC()
  {
    return GetSystemMetrics(SM_TABLETPC); 
  }

  /**
  The coordinates for the left side of the virtual screen. The virtual screen is the bounding rectangle of all display monitors.
  The SM_CXVIRTUALSCREEN metric is the width of the virtual screen. 
  */
  int virtualScreenLeftPos()
  {
    return GetSystemMetrics(SM_XVIRTUALSCREEN); 
  }


  /**
  The coordinates for the top of the virtual screen. The virtual screen is the bounding rectangle of all display monitors. 
  The SM_CYVIRTUALSCREEN metric is the height of the virtual screen. 
  */
  int virtualScreenTopPos()
  {
  
    return GetSystemMetrics(SM_YVIRTUALSCREEN); 
  }

public:
  void display()
  {
    _tprintf(_T("arrange: %d\n"), arrange());

    _tprintf(_T("cleanBoot: %d\n"), cleanBoot());
    _tprintf(_T("monitors: %d\n"), monitors());
    _tprintf(_T("mouseButton: %d\n"), mouseButton());
    _tprintf(_T("borderWidth: %d\n"), borderWidth());
    _tprintf(_T("cursorWidth: %d\n"), cursorWidth());
    _tprintf(_T("dlgFrameWidth: %d\n"), dlgFrameWidth());
    _tprintf(_T("doubleClkWidth: %d\n"), doubleClkWidth());
    _tprintf(_T("dragWidth: %d\n"), dragWidth());
    _tprintf(_T("edgeWidth: %d\n"), edgeWidth());
    _tprintf(_T("fixedFrameWidth: %d\n"), fixedFrameWidth());
    _tprintf(_T("focusBorderWidth: %d\n"), focusBorderWidth());
    _tprintf(_T("frameWidth: %d\n"), frameWidth());
    _tprintf(_T("fullScreenWidth: %d\n"), fullScreenWidth());
    _tprintf(_T("hScrollWidth: %d\n"), hScrollWidth());
    _tprintf(_T("hThumbWidth: %d\n"), hThumbWidth());
    _tprintf(_T("iconWidth: %d\n"), iconWidth());
    _tprintf(_T("iconSpacingWidth: %d\n"), iconSpacingWidth());
    _tprintf(_T("maximizedWidth: %d\n"), maximizedWidth());
    _tprintf(_T("maxTrackWidth: %d\n"), maxTrackWidth());
    _tprintf(_T("menuCheckWidth: %d\n"), menuCheckWidth());
    _tprintf(_T("menuSizeWidth: %d\n"), menuSizeWidth());
    _tprintf(_T("minWidth: %d\n"), minWidth());
    _tprintf(_T("minimizedWidth: %d\n"), minimizedWidth());
    _tprintf(_T("minSpacingWidth: %d\n"), minSpacingWidth());
    _tprintf(_T("minTrackWidth: %d\n"), minTrackWidth());
    _tprintf(_T("paddedBorderWidth: %d\n"), paddedBorderWidth());
    _tprintf(_T("screenWidth: %d\n"), screenWidth());
    _tprintf(_T("sizeWidth: %d\n"), sizeWidth());
    _tprintf(_T("sizeFrameWidth: %d\n"), sizeFrameWidth());
    _tprintf(_T("smallIconWidth: %d\n"), smallIconWidth());
    _tprintf(_T("smallSizeWidth: %d\n"), smallSizeWidth());
    _tprintf(_T("virtualScreenWidth: %d\n"), virtualScreenWidth());
    _tprintf(_T("vScrollWidth: %d\n"), vScrollWidth());
    _tprintf(_T("borderHeight: %d\n"), borderHeight());
    _tprintf(_T("captionHeight: %d\n"), captionHeight());
    _tprintf(_T("cursorHeight: %d\n"), cursorHeight());
    _tprintf(_T("dlgFrameHeight: %d\n"), dlgFrameHeight());
    _tprintf(_T("doubleClkHeight: %d\n"), doubleClkHeight());
    _tprintf(_T("dragHeight: %d\n"), dragHeight());
    _tprintf(_T("edgeHeight: %d\n"), edgeHeight());
    _tprintf(_T("fixedFrameHeight: %d\n"), fixedFrameHeight());
    _tprintf(_T("focusBorderHeight: %d\n"), focusBorderHeight());
    _tprintf(_T("frameHeight: %d\n"), frameHeight());
    _tprintf(_T("fullScreenHeight: %d\n"), fullScreenHeight());
    _tprintf(_T("hScrollHeight: %d\n"), hScrollHeight());
    _tprintf(_T("iconHeight: %d\n"), iconHeight());
    _tprintf(_T("iconSpacingHeight: %d\n"), iconSpacingHeight());
    _tprintf(_T("kanjiWindowHeight: %d\n"), kanjiWindowHeight());
    _tprintf(_T("maximizedHeight: %d\n"), maximizedHeight());
    _tprintf(_T("maxTrackHeight: %d\n"), maxTrackHeight());
    _tprintf(_T("menuHeight: %d\n"), menuHeight());
    _tprintf(_T("menuCheckHeight: %d\n"), menuCheckHeight());
    _tprintf(_T("menuSizeHeight: %d\n"), menuSizeHeight());
    _tprintf(_T("minHeight: %d\n"), minHeight());
    _tprintf(_T("minimizedHeight: %d\n"), minimizedHeight());
    _tprintf(_T("minSpacingHeight: %d\n"), minSpacingHeight());
    _tprintf(_T("minTrackHeight: %d\n"), minTrackHeight());
    _tprintf(_T("screenHeight: %d\n"), screenHeight());
    _tprintf(_T("sizeHeight: %d\n"), sizeHeight());
    _tprintf(_T("sizeFrameHeight: %d\n"), sizeFrameHeight());
    _tprintf(_T("smallCaptionHeight: %d\n"), smallCaptionHeight());
    _tprintf(_T("smallIconHeight: %d\n"), smallIconHeight());
    _tprintf(_T("smallSizeHeight: %d\n"), smallSizeHeight());
    _tprintf(_T("virtualScreenHeight: %d\n"), virtualScreenHeight());
    _tprintf(_T("vscrollHeight: %d\n"), vscrollHeight());
    _tprintf(_T("vThumbHeight: %d\n"), vThumbHeight());
    _tprintf(_T("dbcsEnabled: %d\n"), dbcsEnabled());
    _tprintf(_T("debug: %d\n"), debug());
    _tprintf(_T("digitizer: %d\n"), digitizer());
    _tprintf(_T("immEnabled: %d\n"), immEnabled());
    _tprintf(_T("maxIMUMTouches: %d\n"), maxIMUMTouches());
    _tprintf(_T("mediaCenter: %d\n"), mediaCenter());
    _tprintf(_T("menuDropAlignment: %d\n"), menuDropAlignment());
    _tprintf(_T("mousePresent: %d\n"), mousePresent());
    _tprintf(_T("mouseHorizontalWheelPresent: %d\n"), mouseHorizontalWheelPresent());
    _tprintf(_T("mouseWheelPresent: %d\n"), mouseWheelPresent());
    _tprintf(_T("network: %d\n"), network());
    _tprintf(_T("penWindows: %d\n"), penWindows());
    _tprintf(_T("remoteControl: %d\n"), remoteControl());
    _tprintf(_T("remoteSession: %d\n"), remoteSession());
    _tprintf(_T("sameDisplayFormat: %d\n"), sameDisplayFormat());
    _tprintf(_T("secure: %d\n"), secure());
    _tprintf(_T("serverR2: %d\n"), serverR2());
    _tprintf(_T("showSounds: %d\n"), showSounds());
    _tprintf(_T("shuttingDown: %d\n"), shuttingDown());
    _tprintf(_T("slowMachine: %d\n"), slowMachine());
    _tprintf(_T("starter: %d\n"), starter());
    _tprintf(_T("swapButton: %d\n"), swapButton());
    _tprintf(_T("tabletPC: %d\n"), tabletPC());
    _tprintf(_T("virtualScreenLeftPos: %d\n"), virtualScreenLeftPos());
    _tprintf(_T("virtualScreenTopPos: %d\n"), virtualScreenTopPos());

  }


 
};

}

