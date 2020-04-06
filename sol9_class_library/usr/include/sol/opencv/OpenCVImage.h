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
 *  OpenCVImage.h
 *
 *****************************************************************************/
// https://fossies.org/linux/opencv/modules/core/include/opencv2/core/types_c.h
#pragma once

#include <sol/ClientDC.h>
#include <sol/opencv/OpenCVBitmap.h>

//See https://github.com/opencv/opencv/wiki/ChangeLog#version420

//Breaking changes:
//Disabled constructors for legacy C API structures.

//In OpenCV-4.2.0, the following naive code causes a compile error
// cv::Mat mat;
// ...
// IplImage ipl = mat;
// 

namespace SOL {
  
/*
  Based on cxtypes.h 
typedef struct _IplImage 
{ 
    int  nSize;            // sizeof(IplImage)  
    int  ID;               // version (=0)
    int  nChannels;        // Most of OpenCV functions support 1,2,3 or 4 channels  
    int  alphaChannel;     // ignored by OpenCV 
    int  depth;            // pixel depth in bits: IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16S, 
                           // IPL_DEPTH_32S, IPL_DEPTH_32F and IPL_DEPTH_64F are supported  
    char colorModel[4];    // ignored by OpenCV 
    char channelSeq[4];    // ditto 
    int  dataOrder;        // 0 - interleaved color channels, 
                           //          1 - separate color channels. 
                           //          cvCreateImage can only create interleaved images 
    int  origin;           //      0 - top-left origin, 
                           //          1 - bottom-left origin (Windows bitmaps style)
    int  align;            //       Alignment of image rows (4 or 8). 
                           //           OpenCV ignores it and uses widthStep instead 
    int  width;            //       image width in pixels 
    int  height;           //       image height in pixels 
    struct _IplROI *roi;       // image ROI. if NULL, the whole image is selected 
    struct _IplImage *maskROI; // must be NULL 
    void  *imageId;            // ditto 
    struct _IplTileInfo *tileInfo; // ditto 
    int  imageSize;            // image data size in bytes 
                               //          (==image->height*image->widthStep 
                               //          in case of interleaved data 
    char *imageData;           // pointer to aligned image data 
    int  widthStep;            //  size of aligned image row in bytes 
    int  BorderMode[4];        // ignored by OpenCV 
    int  BorderConst[4];       //  ditto 
    char *imageDataOrigin;     // pointer to very origin of image data 
                               //             (not necessarily aligned) - 
                               //             needed for correct deallocation 
} 
IplImage;  
  */
  

    
class OpenCVImage :public OpenCVBitmap {
private:
  IplImage*      image;

protected:
  OpenCVImage()
  :OpenCVBitmap(),
  image(NULL)
  {
  }
  
public:
  
  OpenCVImage(const char* filepath, int flag=CV_LOAD_IMAGE_COLOR)
  :OpenCVBitmap(),
  image(NULL)
  {
    cv::Mat mat = cv::imread(filepath, flag);
    if (mat.empty()) {
      throw IException("Failed to imread: %s  %d", filepath, flag);
    }
    
    IplImage ipl = cvIplImage(mat);
    image = &ipl;
    
    if (image == NULL ){
      throw IException("Failed to cvLoadImage: %s", filepath);
    } else {  
      convertToBitmap();
    }
  }
  
  
  OpenCVImage(IplImage* img)
  :OpenCVBitmap(),
  image(img)
  {
    if (image == NULL ){
      throw IException("Invalid parameter");
    } else {  
      convertToBitmap();
    }
  }
  
  ~OpenCVImage()
  {
    if (image) {
      cvReleaseImage(&image);
    }
  }
  

  virtual void convertToBitmap()
  {
    if (image) {
      toBitmap(image);
    }
  }
  
  void toBitmap(const IplImage* image)
  {
    if (image == NULL) {
      throw IException("Invalid image parameter: null.");
    }
    
    int width  = image->width;
    int height = image->height;
    
    if (width <= 0 || height <=0) {
      throw IException("Invalid image size parameter: width=%d, height=%d.", width, height);      
    }
       
    BITMAPINFO bmpInfo;
    
    memset(&bmpInfo, 0, sizeof(bmpInfo));
    int bitCount = image->nChannels * image->depth;
     
    bmpInfo.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth    =  width;
    
    bmpInfo.bmiHeader.biHeight   = height;
    bmpInfo.bmiHeader.biPlanes   = 1;
    bmpInfo.bmiHeader.biBitCount = 32;
    
    bmpInfo.bmiHeader.biCompression = BI_RGB;
    bmpInfo.bmiColors->rgbBlue     = 0;
    bmpInfo.bmiColors->rgbGreen    = 0;
    bmpInfo.bmiColors->rgbRed      = 0;
    bmpInfo.bmiColors->rgbReserved = 0;
 
    int widthStep = image->widthStep;
    uint32_t* bmpData = new uint32_t[width *height];

    const char* p =  image->imageData;
    
      for(int i = 0; i < height; i++){
        int step =widthStep * i;

        for(int j = 0; j < width; j++){
            int w = step + j * 3;

            //imagetData is in BGR order
            uchar b = *(p + w    );
            uchar g = *(p + w + 1);
            uchar r = *(p + w + 2);
                        
          
              uint32_t pixel =  (r << 16) + (g << 8) + b;
              bmpData[j + (height-i-1) * width ] = pixel;
          }
      }
    set(bmpInfo, bmpData);
     
  }
};

}

