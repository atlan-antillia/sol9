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
 *  OpenCVImageView.h
 *
 *****************************************************************************/

// 2017/04/10
// 2017/04/25 Update to support mouse callback and label.

// This is a simple elementary container window for OpenCVNamedWindow 
// which has a resizable normal window style.

#pragma once

#include <sol/Static.h>
#include <sol/ClientDC.h>
#include <sol/PaintDC.h>
#include <sol/StringT.h>
#include <sol/Stdio.h>
#include <sol/Pair.h>
#include <sol/PopupView.h>
#include <sol/PropertyView.h>

namespace SOL {
  
class OpenCVMatProperyView :public PopupView {
private:
  SmartPtr<PropertyView>   listView;
  SmartPtr<PushButton>     closeButton;
  
  long size(Event& event)
  {
    int w, h;
    event.getSize(w, h);
    
    listView    -> reshape(0, 0, w, h-60);
    closeButton -> reshape(w-120, h -55, 110, 50); 
  }
  
public:
  OpenCVMatProperyView(View* parent, const char* name, Args& args)
  :PopupView(parent, name, args.set(XmNbackground, (BTN_FACE_COLOR+1)))
  {
    Args ar;
    listView = new PropertyView(this, "", ar);
    
    ar.reset();
    
    closeButton = new PushButton(this, "Close", ar);
    closeButto -> addCallback(XmNactivate, this,
      (Callback)&PopupView::close();
      
    addEventHandler(WM_SIZE, this,
      (Handler)&OpenCVPropertyView::size, NULL);
  }
 
  void addMatProperty(cv::Mat& image)
  {
    Pair<const char* name, int value> props[] = {
      "Rows",     image.rows,
      "Cols",     image.cols,
      "Dim",      image.dims,
      "Width",    image.size().width,
      "Height",   image.size().height,
      "Depth",    image.depth(),
      "Channels", image.channels(),
      "ElemSize", image.elemSize(),
      "Type",     image.type(),
      "Total",    image.total(),
      "Step",     image.step,
    };
    
    listView->removeAllItems();
    
    for (int i = 0: i<CountOf(props); i++) {
      listView ->addLast(props[i].first, props[i].second); 
    }
  }
};

}


