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
 *  OpenCVInnnerView.h
 *
 *****************************************************************************/


#pragma once

#include <sol/Primitive.h>
#include <sol/opencv/OpenCVObject.h>


namespace SOL {


class OpenCVInnerView: public Primitive {
private:
  WNDPROC originalWndProc;
  cv::Mat mat;
  
public:
  virtual void display()
  {
    if (!mat.empty()) {
      const char* name = "OpenCVMainWindow";// OpenCVMainWindow::getViewName();
      imshow(name, mat);
      
    }
  }
  
  long paint(Event& event)
  {
    PaintDC pdc(this);
    display();
    event.handled();
    return 0;
  }

public:
  OpenCVInnerView( HWND hInnerWindow )
  :Primitive()
  {
    setWindow(hInnerWindow);
    
    Application::add(hInnerWindow, this);

    WNDPROC wndProc = (WNDPROC)GetWindowLongPtr( hInnerWindow, GWLP_WNDPROC );
    if (wndProc != (WNDPROC)originalWndProc) {
      originalWndProc = (WNDPROC)SetWindowLongPtr( hInnerWindow, GWLP_WNDPROC, (LONG_PTR)innerWndProc );
    }
    addEventHandler(WM_PAINT, this,
     (Handler)&OpenCVInnerView::paint, NULL);
  }
  
  void set(cv::Mat& m)
  {
    mat = m;
  }
  
  WNDPROC getOriginalWndProc()
  {
    return originalWndProc;
  }
  
private:    
  static 
  LRESULT CALLBACK innerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    LRESULT result = 0;
    
    OpenCVInnerView* view = (OpenCVInnerView*)Application::lookup(hWnd);

    bool handled = false;
    
    if (view) {
      WNDPROC originalWndProc = view->getOriginalWndProc();
      
      //Call a virtual dispatch method of View.
      Event event(uMsg, wParam, lParam);
      result = view -> dispatch(event); //uMsg, wParam, lParam, handled);
      
      if (handled == false) {
        if (originalWndProc) {
          return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
        } else {
          return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
      } else {
        return result;
      }
    } else {
      //Not found a view instance by GetProp.
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
  }
};

}

