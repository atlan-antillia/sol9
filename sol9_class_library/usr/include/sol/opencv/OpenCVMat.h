
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
 *  OpenCVMat.h
 *
 *****************************************************************************/

// 2017/03/15

#pragma once
#include <sol/SystemMetrics.h>
#include <sol/StringT.h>
#include <sol/opencv/OpenCVImage.h>

namespace SOL {
  
enum {
  RESIZE_NONE,
  RESIZE_FULLSCREEN_WIDTH,
  RESIZE_FULLSCREEN_HEIGHT
} OpenCVResizePolicy;
  
class OpenCVMat :public OpenCVImage {

private:
  static const int defaultResizeMargin = 200;
  int           RESIZE_MARGIN;
  
  cv::Mat       mat;
  StringT<char> filename;
  int           loadFlag;
  
  int           resizePolicy; 

private:
  void resizeOnPolicy(int policy)
  {
    switch (policy) {
      
    case RESIZE_FULLSCREEN_WIDTH:
      resizeFullscreenWidth();
      break;
      
    case RESIZE_FULLSCREEN_HEIGHT:
      resizeFullscreenHeight();
      break;
      
    case RESIZE_NONE:
      convertToBitmap();
      break;
      
    }
  }
  
public:
  OpenCVMat(const char* filepath, int flag=CV_LOAD_IMAGE_COLOR, 
              int resizePolicy = RESIZE_NONE, 
              int margin = defaultResizeMargin)
  :OpenCVImage(),
  filename(filepath),
  loadFlag(flag),
  resizePolicy(resizePolicy),
  RESIZE_MARGIN(margin)
  {
    load(filepath, flag, resizePolicy);
  }
  
  void load(const char* filepath, int flag, int resizePolicy)
  {
    mat = cv::imread(filepath, flag);
    if (mat.empty()) {
      throw IException("Failed to cv::imread: %s", filepath);
    } 
    resizeOnPolicy(resizePolicy);
  }
  
public:
  OpenCVMat(const cv::Mat& m, int resizePolicy=RESIZE_NONE,
      int margin = defaultResizeMargin)
  :OpenCVImage(),
  mat(m),
  resizePolicy(resizePolicy),
  RESIZE_MARGIN(margin)
  {
    if (m.empty()) {
      throw IException("Invalid parameter: Mat is empty");
    }
    
    resizeOnPolicy(resizePolicy);
  }

public:
  //Copy constructor
  OpenCVMat(const OpenCVMat& ocvmat)
  :OpenCVImage(),
  mat(ocvmat.mat),
  resizePolicy(ocvmat.resizePolicy),
  RESIZE_MARGIN(ocvmat.RESIZE_MARGIN)
  {
    resizeOnPolicy(resizePolicy);
  }

  ~OpenCVMat()
  {
  }

  virtual void convertToBitmap()
  {
    //2017/09/10 Modified to check whether cv::Mat image channels is 1 (grayscale)
    cv::Mat bgra = mat;
    if ( mat.channels() == 1) {
      // if mat is grayscale, we convert  to bgra
      cv::cvtColor(mat, bgra, cv::COLOR_GRAY2BGR);
    }
    
    IplImage ipl = cvIplImage(mat);
    IplImage* image = &ipl;
    
    
    OpenCVImage::toBitmap(image);
    
  }
  
  void reload()
  {
    load(filename, loadFlag, resizePolicy);
  }

  //Since mat has been updated, we have convert the mat to a bitmap image 
  void update()
  {
    //2017/09/10 Modified to check whether cv::Mat image channels is 1 (grayscale)
    cv::Mat bgra = mat;
    if ( mat.channels() == 1) {
      // if mat is grayscale, we convert  to bgra
      cv::cvtColor(mat, bgra, cv::COLOR_GRAY2BGR);
    }
    IplImage ipl = cvIplImage(mat);
    IplImage* image = &ipl;

    OpenCVImage::toBitmap(image);
  }
  

  void setMat(cv::Mat& m, int resizePolicy=RESIZE_FULLSCREEN_WIDTH, int margin=defaultResizeMargin)
  {
    this -> mat = m;
    this -> resizePolicy = resizePolicy;
    this -> RESIZE_MARGIN = margin;
    
    resizeOnPolicy(resizePolicy);
  }

  cv::Mat& getMat()
  {
    return mat;
  }

  
  void resizeFullscreenWidth()
  {
    SystemMetrics metrics;
    int screenWidth = metrics.virtualScreenWidth(); //screenWidth();
    
    if (this->mat.cols > screenWidth) {
      double ratio = (double)(screenWidth - RESIZE_MARGIN) / (double)this->mat.cols;
      //ratio = ratio;
      resize(ratio, cv::INTER_AREA);
    } else {
      convertToBitmap();
    }
  }
  
  void resizeFullscreenHeight()
  {
    SystemMetrics metrics;
    int screenHeight = metrics.virtualScreenHeight();
    if (this->mat.rows > screenHeight) {
      double ratio = (double)(screenHeight - RESIZE_MARGIN) / (double)this->mat.rows;
      ;
      resize(ratio, cv::INTER_AREA);
    } else {
      convertToBitmap();
    }
  }

  void resize(double ratio, int algorithm = cv::INTER_AREA)
  {
    double width  = (double)this->mat.rows * ratio ;
    double height = (double)this->mat.cols * ratio;
    
    cv::Mat dst = cv::Mat::ones((int)width, (int)height, this->mat.type());

    cv::resize(this->mat, dst, dst.size(), algorithm);
    
    this->mat = dst;
    
    update(); //This calls convertToBitmap
  }
  
};

}

