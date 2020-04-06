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
 *  OpenCVColorFilter.h
 *
 *****************************************************************************/

// 2017/10/10

#pragma once

#include <sol/RowColumnT.h>
#include <sol/TextField.h>
#include <sol/opencv/OpenCVObject.h>

namespace SOL {
  
static const int KSIZE = 3;
  
class OpenCVColorFilter :public RowColumnT<TextField, KSIZE, KSIZE> {
private:
  cv::Mat         filter;
  float           value[KSIZE][KSIZE];
  
public:
  OpenCVColorFilter(View* parent, const TCHAR* name, Args& args)
  :RowColumnT(parent, name, args)
  {
    for (int i = 0; i<KSIZE; i++) {
      for (int j = 0; j<KSIZE; j++) {
        value[i][j] = 1.0f;
        set(i, j, 1.0f); 
      }
    }
  }
  
  void setValue(int column, int r, int g, int b)
  {
    if (column >=0 && column < KSIZE) {
      int i = 0;
      float blue  = (float)b/255.0f;
      float green = (float)g/255.0f;
      float red   = (float)r/255.0f;
      
      value[i][column] =  blue;
      set(i++, column, blue); 

      value[i][column] =  green;
      set(i++, column, green);
        
      value[i][column] =  red;
      set(i++, column, red);
    } else {
      throw IException("Invalid column parameter %d", column);
    }
  }

  cv::Mat& getFilter()
  {
    //Create a value matrix filter from three Vector3fs. 
    filter = ( cv::Mat_<float>(3,3) <<
          value[0][0], value[0][1], value[0][2],
          value[1][0], value[1][1], value[1][2],
          value[2][0], value[2][1], value[2][2] );
    return filter;
  }
};

}


