/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  QPEncoder.h
 *
 *****************************************************************************/

#pragma once

// SOL9
// 2008/10/10
//

#include <sol\Object.h>
#include <sol\Bytes.h>
#include <sol\String.h>
#include <sol\StringT.h>

namespace SOL {

class QPEncoder :public Object {

public:
  /**
   * Constructor
   */
  QPEncoder() {

  }

public:
  /*
   * Convert byte array to QPEncoded string.
   * @param bytes    [in]  Byte array of data to be encoded.
   * @param string  [out]  QPEncoed string.
   */
  
  int encode(__in Bytes& bytes, __out String& string) {
    int rc = 0;
    char* encoded = NULL;
    int len = encode(bytes.getContents(), bytes.getSize(), &encoded);
    if (len>0) {
      rc = len;
      string = encoded;
      delete [] encoded;
    }
    return rc;
  }

public:
  int encode(__in Bytes& bytes, __out StringT<char>& string) {
    int rc = 0;
    char* encoded = NULL;
    int len = encode(bytes.getContents(), bytes.getSize(), &encoded);
    if (len>0) {
      rc = len;
      string.shallowCopy(encoded);
    }
    return rc;
  }

public:
  /**
   * Encode a byte-array in QuotedPritable format, and return the encoded string (NULL-terminated)
   * to the parameter *enc. Caller should delete the enc after use.
   *
   * @param in [in]  Byte array of data to be encoded.
   * @param enc      QPEncoded NULL-terminated string.
   */
  int encode(unsigned char* in, int len, char** enc)
  {
    int n = 0;

    *enc = NULL;
    if (in == NULL || len<=0) {
      return n;
    }

    static char hex[] = {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F'};

    int slen = len*3 + 3;   
    char* out = new char[slen];
    //Make out to be a NULL-terminated string.
    memset(out, 0, slen);

    int ct = 0;
    int prevc = 255;

    for (int i = 0; i<len; i++) {
      char c = in[i];

      if ((c < 32 && (c != '\n' && c != '\t'))
        || (c == '=')
        || (c >= 127)
        || (ct == 0 && c == '.')) {

        out[n++] = '=';
        out[n++] = hex[c >> 4];
        out[n++] = hex[c & 0xf];
        ct += 3;
        prevc = 'A'; 

      } else if (c == '\n') {
        //If c were a new line.
        if (prevc == ' ' || prevc == '\t') {
          out[n++] = '=';
          out[n++] = c;
        }
        out[n++] = c;
        ct = 0;
        prevc = c;
      } else {
        out[n++] = c;
        ++ct;
        prevc = c;
      }
      if (ct > 72) {
        out[n++] = '=';
        out[n++] = '\n';
        ct = 0;    
        prevc = '\n';
      }
    }

    if (ct != 0) {
      out[n++] = '=';
      out[n++] = '\n';
    }

    *enc = out;
    
    return n;
  }

};

}
