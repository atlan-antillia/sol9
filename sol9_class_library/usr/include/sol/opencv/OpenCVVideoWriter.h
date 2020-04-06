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
 *  OpenCVVideoWriter.h
 *
 *****************************************************************************/


#pragma once


#include <sol/opencv/OpenCVObject.h>

namespace SOL {
    
class OpenCVVideoWriter :public OpenCVObject {
private:
  cv::VideoWriter writer;
  
  int getCodec(const char* name)
  {
    StringT<char> filename = name;
    Pair<const char*, int> codecs[] = {
      {".mp4",  cv::VideoWriter::fourcc('M', 'P', '4', 'S')},
      {".avi",  cv::VideoWriter::fourcc('M', 'J', 'P', 'G')}, 
      {".wmv",  cv::VideoWriter::fourcc('M', 'P', 'G', '1')}, 
      {".mov",  cv::VideoWriter::fourcc('m', 'p', '4', 'v')},
    };
    int codec = -1;
    bool found = false;
    for (int i = 0; CountOf(codecs); i++) {
      if (filename.endsWithIgnoreCase(codecs[i].first)) {
        codec = codecs[i].second;
        found = true;
        break;
      }
    }
    if (found == false) {
      throw IException("Invalid file name %s", (const char*)filename); 
    } else {
      return codec;
    }
  }
  
public:
  OpenCVVideoWriter()
  {
  }
  
  void open(cv::VideoCapture& cap, const char* filename, int fps, double scaling=1.0)
  {
    int codec =  getCodec(filename);
    if (fps == 0) {
      fps = cap.get(cv::CAP_PROP_FPS);
    }
    double w = cap.get(cv::CAP_PROP_FRAME_WIDTH)  * scaling;
    double h = cap.get(cv::CAP_PROP_FRAME_HEIGHT) * scaling;
    
    writer.open(std::string(filename), codec, 
                          (double)fps, 
                          cv::Size((int)w, (int)h));
    if (!writer.isOpened()) {
      throw IException("Failed to open a videoWriter:%s\n", filename);
    }         
  }
  
  bool isOpened()
  {
    return writer.isOpened();
  }
  
  void write(cv::Mat& frame)
  {
    if (writer.isOpened()) {
      writer.write(frame);
    }
  }
  
  void close()
  {
    if (writer.isOpened()) {
      writer.release();
    }
  }
};

}


