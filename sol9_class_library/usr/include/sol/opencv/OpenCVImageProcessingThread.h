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
 *  OpenCVImageProcessingThread.h
 *
 *****************************************************************************/

//2017/12/25  Simple Thread for OpenCVImage processings.
// Getting an opencv image from a queued OpenCVImage ,
// and render the image on an imageView.

#pragma once

#include <sol/Thread.h>
//#include <sol/opencv/OpenCVMatImage.h>
#include <sol/opencv/OpenCVImageQueue.h>

namespace SOL {

class OpenCVImageProcessingThread :public Thread {
private:
  OpenCVImageQueue imageQueue;

  //bool       looping;
  //int        interval;

public:
  OpenCVImageProcessingThread()
  :Thread()
  //,looping(true)
  //,interval(40)  //40msec
  {
  }
  
  ~OpenCVImageProcessingThread()
  {
  }

  //Thread main procedure, which can be called by the start method of
  //the Thread class.

  //Define your own run method in a subclass derived from this class. 
  virtual void run()
  {
    /*
    int microsec = interval*1000;
 
    while(looping) {
      //1 Get an object of OpenCVMat from the imageQueue.

      SmartPtr<OpenCVMatImage> cvmat = imageQueue.get();
      if (cvmat) {
        //2 Get a cv::Mat from the OpenCVMat object.
        cv::Mat& mat = cvmat->getMat();
        //3 Do some operations to the mat if needed. 
        //
        //4 Render the mat on an imageView.
        imageView->render(mat);
      }
      nanosleep(microsec);
    }
    */    
  }

  void addToQueue(OpenCVMatImage* image)
  {
    imageQueue.add(image); 
  }

  OpenCVMatImage* getFromQueue()
  {
    return imageQueue.get();
  }

  void clearQueue()
  {
    imageQueue.clear();
  }

  //Define your own terminate method in a subclass derived from this class.
  virtual void terminate()
  {
    //looping = false;
  }
};

}

