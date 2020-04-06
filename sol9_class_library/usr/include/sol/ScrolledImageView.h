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
 *  ScrolledImageView.h
 *
 *****************************************************************************/

// SOL9

// 2012/07/15 
// 2012/08/07 Updated to use SOL::Stream class in 'drawImage' method.
#include <sol\Composite.h>
#include <sol\PaintDC.h>
#include <sol\Brush.h>
#include <sol\FileDialog.h>
#include <sol\DropFiles.h>
#include <sol\Folder.h>
#include <sol\com\Stream.h>

namespace SOL {

class ScrolledImageView :public Composite {

private:
  _bstr_t imageFileName;
  Gdiplus::Image*  image;

public:
  ScrolledImageView()
    :Composite(),
    image(NULL),
    imageFileName(_T(""))
  {
  }

public:
  /**
   * Constructor
   */
  ScrolledImageView(View* parent, const TCHAR* name, Args& args)
    :Composite()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name,
      args.set(XmNclassName, _T("_ScrolledImageView_"))
        .set(XmNbackgroundColor, (COLOR_BTNFACE+1))
        .set(XmNstyle, (LONG_PTR)WS_VSCROLL|WS_HSCROLL)
        .set(XmNexStyle,(LONG_PTR)WS_EX_ACCEPTFILES) );

    addEventHandler(WM_ERASEBKGND, this, 
      (Handler)&ScrolledImageView::erase, NULL);

    addEventHandler(WM_PAINT, this, 
      (Handler)&ScrolledImageView::paint, NULL);

    addEventHandler(WM_DROPFILES, this, 
      (Handler)&ScrolledImageView::dropFiles, NULL);

    addEventHandler(WM_SIZE, this, 
      (Handler)&ScrolledImageView::size, NULL);

    image = NULL;
    
    imageFileName = _T("");

    return rc;
  }

public:
  ~ScrolledImageView()
  {
    clear();
  }

private:
  bool isTransparentImage(Gdiplus::Image* image)
  {
    bool rc = false;
    if (image) {
      GUID guid;
      Gdiplus::Status stat = image->GetRawFormat(&guid);
      if (guid == Gdiplus::ImageFormatIcon ||
        guid == Gdiplus::ImageFormatPNG ||
        guid == Gdiplus::ImageFormatTIFF) {
          rc = true;
      }
    }
    return rc;
  }

public:
  //2012/07/15
  virtual void doHorizScroll(Action& action)
  {
    int diff = (int)action.getValue();
    if (diff) {
      if (isTransparentImage(image)) {
        invalidateAll();
      }
      scroll(diff, 0, NULL, NULL);
      update();
    }
  }

public:
  //2012/07/15
  virtual void doVertScroll(Action& action)
  {
    int diff = (int)action.getValue();
    if (diff) {
      if (isTransparentImage(image)) {
        invalidateAll();
      }
      scroll(0, diff, NULL, NULL);
      update();
    }
  }


private:
  long erase(Event& event)
  {
    if (image) {
      if (isTransparentImage(image)) {
        //You have to erase the background
        return defaultProc(event);
      } else {
        //Don't erase the background
        return TRUE;
      }
    } else {
      return defaultProc(event);
    }
    
    return TRUE;
  }


public:
  void clear()
  {
    if (image) {
      delete image;
      image = NULL;
    }
  }
  
public:
  void drawImage(const wchar_t* fileName)
  {
    clear();

    try {
      imageFileName = fileName;

      //image = new Gdiplus::Image((const wchar_t*)imageFileName, TRUE);
      //2012/08/07
      Stream stream(imageFileName);
      image = Gdiplus::Bitmap::FromStream((IStream*)stream);

      if (image) {
        setScrollPos(HORIZONTAL, 0);
        setScrollPos(VERTICAL, 0);

        UINT width  = image->GetWidth();
        UINT height = image->GetHeight();

        setScrollExtent(width, height);

        invalidateAll(); 
        update();
      }
    } catch (...) {

    }
  }

private:
  //2012/04/16 EventHandler for WM_DROPFILES
  long dropFiles(Event& event) 
  {
    TCHAR fileName[1024];
    DropFiles drop((HDROP)event.getWParam());
    fileName[0] = ZERO;
    int num = drop.queryFile(0, fileName, CountOf(fileName));

    if(num > 0) {
      imageFileName = fileName;
      drawImage(imageFileName);
    }
    return 0;
  }



private:
  void updateScrollRange()
  {
    if (image) {
      uint w, h;
      getScrollExtent(&w, &h);
    
      UINT width = image->GetWidth();
      UINT height = image->GetHeight();
      setScrollExtent(width, height);
    }
  }

private:
  long size(Event& event)
  {
    updateScrollRange();
    return 0;
  }


private:
  long paint(Event& event)
  {
    PaintDC pdc(this);
    Gdiplus::Graphics graphics(pdc.get());

    if (image) {
      int x = getScrollPos(Composite::HORIZONTAL);
      int y = getScrollPos(Composite::VERTICAL);
      UINT width  = image->GetWidth();
      UINT height = image->GetHeight();
      RECT r;
      getClientRect(&r);
      uint w = r.right-r.left;
      uint h = r.bottom - r.top;
      
      int dw = w;
      int dh = h;
      int sw = w;
      int sh = h;

      GUID guid;
      Gdiplus::Status stat = image->GetRawFormat(&guid);
      
      if (guid == Gdiplus::ImageFormatIcon) {
        dw = width;
        dh = height;
        sw = width;
        sh = height;
      
      }

      if (guid == Gdiplus::ImageFormatIcon) {
  
        graphics.DrawImage(image, 
          Gdiplus::RectF(
          (Gdiplus::REAL)(-x),
          (Gdiplus::REAL)(-y), 
          (Gdiplus::REAL)(dw), 
          (Gdiplus::REAL)(dh)),

          (Gdiplus::REAL)0,
          (Gdiplus::REAL)0,
          (Gdiplus::REAL)sw,  
          (Gdiplus::REAL)sh, 
          Gdiplus::UnitPixel);
        
      } else {
        graphics.DrawImage(image, 
          Gdiplus::RectF(
          (Gdiplus::REAL)(0),
          (Gdiplus::REAL)(0), 
          (Gdiplus::REAL)(dw), 
          (Gdiplus::REAL)(dh)),

          (Gdiplus::REAL)x,
          (Gdiplus::REAL)y,
          (Gdiplus::REAL)sw,  
          (Gdiplus::REAL)sh, 
          Gdiplus::UnitPixel);
      }
      
      if (w>width) {
        RECT rr= {width, 0, w, height};
        if (h>height) {
          rr.bottom = h;
        }
        Brush br(GetSysColor(COLOR_BTNFACE));
        pdc.fillRect(&rr, br);
      }
      if (h>height) {
        RECT rr = {0, height, width, h};
        if (w>width) {
          rr.right = w;
        }
        Brush br(GetSysColor(COLOR_BTNFACE));
        pdc.fillRect(&rr, br);
      }      
    }
    return 0;
  }

};

}
