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
 *  OpenCVImageFileReader.cpp
 *
 *****************************************************************************/

#pragma once

#include <sol/File.h>
#include <sol/ModuleFileName.h>
#include <sol/opencv/OpenCVObject.h>

namespace SOL {

class OpenCVImageFileReader {
private:

  ModuleFileName module;

public:
  OpenCVImageFileReader()
  {
  }

  cv::Mat load(const char* filename, int loadingFlag = cv::IMREAD_COLOR)
  {
    char fullpath[MAX_PATH] = {0};
    if (filename[0] == '.') {
      sprintf_s(fullpath, CountOf(fullpath), "%s\\%s", module.getDir(),
               filename);
    } else {
      strcpy(fullpath, filename);
    }

    File file;
    if (file.isExistent(fullpath)) {
      cv::Mat image = cv::imread(fullpath, loadingFlag);
      if (!image.empty()) {
        return image;
      } else {
        throw SOL::IException("Failed to cv::imread %s", fullpath);
      }
    } else {
      throw SOL::IException("Not found %s", fullpath);
    }
  }
};

}

