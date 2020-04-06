/******************************************************************************
 *
 * Copyright (c) 2008-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED. 
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
 *  HTMLFileEncoder.h
 *
 *****************************************************************************/

//2012/06/23

#pragma once

#include <sol\HTMLEncoder.h>
#include <sol\Folder.h>

// 2008/09/24 Modified to create an output folder if it does not exists.
// 2008/09/30 Created a HTMLFileEncoder.h and added to the folder include\sol.

namespace SOL {

class HTMLFileEncoder: public HTMLEncoder {

public:
  HTMLFileEncoder() {

  }

public:
  /**
   * Write HTML encoded string to an output file.
   * The tab code in the string is converted to 4 space characters.
   */
  virtual bool write(const char* enc, const int len, FILE* out)
  {
    bool rc = false;

    char* spaces_4 = "    ";
    int rlen = 0;
    for (int i = 0; i<len; i++) {
      if (enc[i] == '\t') {
        rlen += fwrite(spaces_4, 1, strlen(spaces_4), out);
      } else {
        rlen +=fwrite(&enc[i], 1, 1, out);
      }

    }
  
    //nt rx = fwrite(enc, 1, len, out);
    if (rlen>0) {
      printf("input =%d bytes: fwritten %d bytes\n", len, rlen);
      rc = true;
    }
    return rc;
  }

public:
  /**
   * HTML-encoding for the file specified by the first argument,
   * and write the encoded string to the file specified by the second argument.
   * If the output file already exists, then the contents of the file will be 
   * replaced by new encoded string.
   */
  bool encode(const TCHAR* htmlFile, const TCHAR* encodeFile) {
    bool rc = false;

    if (GetFileAttributes(htmlFile) == 0xffffffff) {
      _tprintf(_T("HTML File not found: %s\n"), htmlFile); 
      return rc;
    }
      
    FILE* in = NULL;
    errno_t err = fopen_s(&in, htmlFile, _T("r"));
    if (err == 0 && in) {
      _tprintf(_T("Opened %s\n"), htmlFile);
      Folder folder(encodeFile);
      if (folder.exists() == false) {
        if (folder.createFolder() == false) {
          fclose(in);
          _tprintf(_T("Failed to create a folder for %s\n"), encodeFile);
          return rc;
        }
      }

      FILE* out = NULL;
      errno_t er = fopen_s(&out, encodeFile, _T("w"));

      if (er == 0 && out) {
        _tprintf(_T("Opened write file=%s\n"), encodeFile);
        try {
          int len = _filelength(_fileno(in));
          _tprintf(_T("In file %d bytes\n"), len);
          char* html = new char[len+1];
          int rlen = fread(html, 1, len, in) ;
          if (rlen>0) {
            _tprintf(_T("fread %d bytes\n"), rlen);
            html[rlen] = '\0';
            char* enc = HTMLEncoder::encode(html);
            if (enc) {
              rc = write(enc, strlen(enc), out);
            }
            delete [] enc;  
          }
          delete [] html;
        } catch (...) {

        }
        fclose(out);
      } else {
        _tprintf(_T("Faild to open an output file %s\n"), encodeFile);
      }
      fclose(in);
    } else {
      _tprintf(_T("Failed to open an HTML file %s.\n"), htmlFile);

    }
    return rc;
  }
};

}
 
