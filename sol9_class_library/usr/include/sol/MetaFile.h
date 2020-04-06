/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  MetaFile.h
 *
 *****************************************************************************/

// SOL++2000
#pragma once

#include <sol\Resource.h>

namespace SOL {

class MetaFile :public Resource {
  public:
  MetaFile(UINT size, const BYTE* data)
    :Resource("", SetEnhMetaFileBits(size, data)) { }
  MetaFile(HENHMETAFILE handle)
    :Resource("", (HANDLE)handle) { }
  MetaFile(const char* filename)
    :Resource(filename, GetEnhMetaFile(filename)) { }
  ~MetaFile() { 
      ::DeleteEnhMetaFile((HENHMETAFILE)getHandle());
  }
  void  draw(HDC hdc, const RECT* rect) {
      HENHMETAFILE handle = (HENHMETAFILE)getHandle();
      if(handle) ::PlayEnhMetaFile(hdc, handle, rect);
  }
  UINT   getBits(UINT size, BYTE* buffer) {
      return ::GetEnhMetaFileBits((HENHMETAFILE)getHandle(), size, buffer);
  }
  UINT  getFileDescription(UINT size, LPTSTR description) {
      return ::GetEnhMetaFileDescription((HENHMETAFILE)getHandle(),
        size, description);
  }  
  UINT  getFileHeader(UINT size, ENHMETAHEADER* emh) {
      return ::GetEnhMetaFileHeader((HENHMETAFILE)getHandle(), size, emh);
  }
  UINT  getFilePaletteEntries(UINT entries, PALETTEENTRY* pe) {
      return ::GetEnhMetaFilePaletteEntries((HENHMETAFILE)getHandle(),
        entries, pe);
  }

  HENHMETAFILE copy(char* filename) {
    return ::CopyEnhMetaFile((HENHMETAFILE)getHandle(), filename);
  }
};

}

