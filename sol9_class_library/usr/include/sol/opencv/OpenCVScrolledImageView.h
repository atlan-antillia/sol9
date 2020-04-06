/******************************************************************************
 *
 * Copyright (c) 2017 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  OpenCVScrolledImageView.h
 *
 *****************************************************************************/

//2017/04/10 Simple ScrolledImageView based on OpenCVBitmap and OpenCVMat.
// We convert thecv::Mat image converted to Window Bitmap format, and display it.
//2017/04/25 Updated an event handler for WM_DROPFILES.

//2017/12/15 Udated 
#pragma once

#include <sol/Composite.h>
#include <sol/PaintDC.h>
#include <sol/Brush.h>
#include <sol/FileDialog.h>
#include <sol/DropFiles.h>
#include <sol/Folder.h>
#include <sol/com\Stream.h>
#include <sol/CriticalSection.h>

#include <sol/opencv/OpenCVBitmap.h>
#include <sol/opencv/OpenCVImage.h>
#include <sol/opencv/OpenCVMat.h>

namespace SOL {
  
class OpenCVScrolledImageView :public Composite {

private:
  SmartPtr<OpenCVMat> image;
  
public:
  OpenCVScrolledImageView()
  :Composite()
  {
  }

public:
  /**
   * Constructor
   */
  OpenCVScrolledImageView(View* parent, const char* name, Args& args)
  :Composite()
  {
    create(parent, name, args);
  }

public:
  Boolean create(View* parent, const char* name, Args& args)
  {
    Boolean rc = Composite::create(parent, name,
      args.set(XmNclassName, "_OpenCVScrolledImageView_")
        .set(XmNbackgroundColor, (COLOR_BTNFACE+1))
        .set(XmNstyle, (LONG_PTR)WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_CLIPCHILDREN|WS_CLIPSIBLINGS)
        .set(XmNexStyle,(LONG_PTR)WS_EX_ACCEPTFILES) );

    addEventHandler(WM_ERASEBKGND, this, 
      (Handler)&OpenCVScrolledImageView::erase, NULL);

    addEventHandler(WM_PAINT, this, 
      (Handler)&OpenCVScrolledImageView::paint, NULL);

    addEventHandler(WM_SIZE, this, 
      (Handler)&OpenCVScrolledImageView::size, NULL);

    //1 Let this view accept WM_DROPFILES message.
    dragAcceptFiles(TRUE);
    
    //2 Add a event handler for WM_DROPFILES. 2017/04/25
    addEventHandler(WM_DROPFILES, this, 
      (Handler)&OpenCVScrolledImageView::dropFiles, NULL);

    image = NULL;
    
    return rc;
  }

public:
  ~OpenCVScrolledImageView()
  {
  }

public:
  virtual void doHorizScroll(Action& action)
  {
    int diff = (int)action.getValue();
    if (diff) {
      //For simplicy, we invalidate all client area.
      refresh();
    }
  }
public:
  void addCallback(const char* name, Object* object, Callback callback, void* data)
  {
    View::addCallback(name, (const Key)getWindow(), object, callback, data);
  }  
  
private:
  long erase(Event& event)
  {
    if (image) {
        return 1;
    } else {
      return defaultProc(event);
    }
    
    return 1;
  }

private:
  //WM_DROPFILES event handler.
 long dropFiles(Event& event)
  {
    HWND hwnd = getWindow();
    callCallback(XmNdropCallback, (Key)hwnd, NULL, event);
    event.handled();
    return 1;
  }
 

public:
  void refreshImage()
  {
    if (image) {
      setScrollPos(HORIZONTAL, 0);
      setScrollPos(VERTICAL, 0);

      int width  = image->getWidth();
      int height = image->getHeight();

      setScrollExtent(width, height);
      refresh();
    }
  }
  
  //2017/12/15 Added
  void refreshImageKeepingThumbPosition()
  {
    if (image) {
     //    setScrollPos(HORIZONTAL, 0);
     //    setScrollPos(VERTICAL, 0);

      int width  = image->getWidth();
      int height = image->getHeight();

      setScrollExtent(width, height);
      refresh();
    }
  }
  
  void convertToBitmap()
  {
    image -> convertToBitmap();
    refreshImage();
  }

  void updateImage(cv::Mat& mat)
  {
    image -> setMat(mat);
    image -> convertToBitmap();
    //2017/04/22
    //refreshImage();
  }


  cv::Mat readImage(const char* filename, int flag=CV_LOAD_IMAGE_COLOR)
  {
    
    cv::Mat mat =imread(filename, flag);
    if (mat.empty()) {
      throw IException("Failed to imread: %s  %d", filename, flag);
    }
    image = new OpenCVMat(mat, RESIZE_FULLSCREEN_WIDTH );
        
    return mat;
  }

  void reload()
  {
    image->reload();
    refreshImage();   
  }

  void writeImage(const char* filename)
  {
    cv::Mat& mat = image->getMat();
    if (!cv::imwrite(filename, mat)) {
      throw IException("Failed to imwrite %s", filename);
    }
  }
  
public:
  void loadImage(const char* filename, int flag = CV_LOAD_IMAGE_COLOR, int resizePolicy=RESIZE_FULLSCREEN_WIDTH)
  {
    try {
      image = new OpenCVMat(filename, flag, resizePolicy);
      
      refreshImage();
      
    } catch (Exception& ex) {
      caught(ex);
    }
  }
 
  OpenCVBitmap* getImage()
  {
    return image;
  }
  
 
  virtual void setImage(cv::Mat& mat)
  {
    image = new OpenCVMat(mat);
    refreshImage();
  }
  
  /*
  In multithread application, your can redefine setImage method in a subclass derived from this class in the
  following way:
  virtual void setImage(cv::Mat& mat)
  {
    if (criticalsection.tryEnter()) {
      OpenCVScrolleImageView::setImage(mat);
      critcalsection.leave();
    }
  }
  */
  
  virtual void setScaledImage(cv::Mat& mat, int scale=100)
  {
    double ratio = (double)scale/100.0f;
    cv::Mat scaled;
    cv::resize(mat, scaled, cv::Size(), ratio, ratio);
    image = new OpenCVMat(scaled);
    refreshImage();
  }
  /*
  In multithread application, your can redefine setImage method in a subclass derived from this class in the
  following way:
  virtual void setScaledImage(cv::Mat& mat, int scale=100)
  {
    if (criticalsection.tryEnter()) {
      OpenCVScrolleImageView::setScaledImage(mat, scale);
      critcalsection.leave();
    }
  }
  */

  //2017/12/15 Added
  virtual void setScaledImageKeepingThumbPosition(cv::Mat& mat, int scale=100)
  {
    double ratio = (double)scale/100.0f;
    cv::Mat scaled;
    cv::resize(mat, scaled, cv::Size(), ratio, ratio);
    image = new OpenCVMat(scaled);
  //  image->update();
  //	convertToBitmap();
  	
    refreshImageKeepingThumbPosition();
  }

  /*
  In multithread application, your can redefine setImage method in a subclass derived from this class in the
  following way:
  virtual void setScaledImageKeepingThumbPosition(cv::Mat& mat, int scale=100)
  {
    if (criticalsection.tryEnter()) {
      OpenCVScrolleImageView::setScaledImage(mat, scale);
      critcalsection.leave();
    }
  }
  */
  
  cv::Mat& getMatImage()
  {
    return image->getMat();
  }
  
  virtual void rescale(int scalingRatio) //Percentage
  {
    double ratio = (double)scalingRatio/100.0;
    image->resize(ratio);
  }
  
private:
  void updateScrollRange()
  {
    if (image) {
      uint w, h;
      getScrollExtent(&w, &h);
    
      int width  = image->getWidth();
      int height = image->getHeight();
      setScrollExtent(width, height);
    }
  }

public:
  long size(Event& event)
  {
    updateScrollRange();
    return 0;
  }

  void resizeImageFullscreenWidth()
  {
    if (image) {
      image -> resizeFullscreenWidth();
    }
  }
  
  virtual void resizeImage(double ratio, int algorithm = cv::INTER_AREA)
  {
    if (image) {
      image->resize(ratio, algorithm);
    }
  }
  
public:
  virtual long paint(Event& event)
  {  
  	PaintDC pdc(this);

    if (image) {
      int x = getScrollPos(Composite::HORIZONTAL);
      int y = getScrollPos(Composite::VERTICAL);
      UINT width  = image->getWidth();
      UINT height = image->getHeight();
      RECT r;
      getClientRect(&r);
      uint w = r.right  -r.left;
      uint h = r.bottom - r.top;
      
      int dw = w;
      int dh = h;
      int sw = w;
      int sh = h;
      //We don't resize the image.
      image->draw(pdc, -x, -y, width, height, 0,  0, width, height);
      

      if (w>width) {
          RECT rr= {(LONG)width, (LONG)0, (LONG)w, (LONG)height};
        if (h>height) {
          rr.bottom = h;
        }
        Brush br(GetSysColor(COLOR_BTNFACE));
        pdc.fillRect(&rr, br);
      }
      if (h>height) {
        RECT rr = {(LONG)0, (LONG)height, (LONG)width, (LONG)h};
        if (w>width) {
          rr.right = w;
        }
        Brush br(GetSysColor(COLOR_BTNFACE));
        pdc.fillRect(&rr, br);
      }
    }
    return 0;
  }

  //2017/12/15
  /* In multithread application, you may redfine this paint method in a subclass derirved from this class 
  in the following way.
  virtual long paint(Event& event)
  {
    if (criticalsection.tryEntry()) {
      OpenCVScrolledImageView::paint(event);
      criticalsection.leave();
    }
  }
  */
};

}
