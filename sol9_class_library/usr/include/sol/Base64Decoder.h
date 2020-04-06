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
 *  Base64Decoder.h
 *
 *****************************************************************************/

#pragma once

#include <sol\Object.h>
#include <math.h>
#include <sol/Bytes.h>
#include <sol/StringT.h>

/**
 * Base64Decoder class reprents a base64decoder.
 */
namespace SOL {

class Base64Decoder :public Object {

public:
  /**
   */
  Base64Decoder() {

  }


  /**
   */
  ~Base64Decoder() {

  }

public:
  /**
   * Decode base64encoded string.
   * @param string  [in] NULL terminated string of Base64Encoded data.
   * @param bytes    [out] Reference to ByteArray to return decoded data.
   */
  int decode(__in const StringT<char>& string, __out Bytes& bytes) {
    return decode((const char*)string, bytes);
  }

public:
  /**
   * Decode base64encoded string.
   * @param string  [in] NULL terminated string of Base64Encoded data.
   * @param bytes    [out] Reference to ByteArray to return decoded data.
   */
  int decode(__in const char* string, __out Bytes& bytes) {
    unsigned char* outBytes = NULL;
    unsigned int outLen =0;
    int rc = 0;
    if (string == NULL) {
      return rc;
    }

    rc = decode(string, strlen(string), &outBytes, &outLen);
    if (rc>0) {
      bytes.shallowCopy(outBytes, outLen);
    }
    
    return rc;  
  }

public:

  /**
   * Decode base64encoded data.
   * @param data    [in] NULL terminated string of Base64Encoded data.
   * @param len    [in] Byte length of data.
   * @param outBytes  [out] Pointer to pointer for unsigned char* to return decoded data.
   * @param outLen  [out] Pointer to unsigned int to return the lenghth of decoded dta. 
   */
  int decode(__in const char* data, 
      __in unsigned int len,
      __out unsigned char** outBytes,
      __out unsigned int* outLen) {

    static const char table[] ={
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x3F,
      0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
      0x3C, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
      0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
      0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
      0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
      0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
      0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
      0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00};

    if (data == NULL || len == 0) {
      return 0;
    }
    if (outBytes == NULL || outLen ==NULL) {
      return 0;
    }

    const char PADDING = '=';

    // Compute a length of padding.
    int pad = 0;
    for (int s = len - 1; s >=0; s--) {
      if (data[s] == PADDING) {
        pad++;
      }
    }

    // Allocating a memory for decoded area.
    unsigned int length = len * 3 / 4 - pad;

    unsigned char* out = new unsigned char[length];        
    memset(out, 0, length);

    unsigned int n = 0;
    //Convert 4 bytes to 3 bytes.
    for (unsigned int i = 0; i <len; i += 4) {
      int block = (table[data[i]] << 18)
          + (table[data[i + 1]] << 12)
          + (table[data[i + 2]] << 6)
          + (table[data[i + 3]]);

      for (unsigned int j = 0; j < 3 && n + j < length; j++) {
        //printf("%d...\n", n+j);
        out[n + j] = ((block >> (8 * (2 - j))) & 0xff);
      }
      n += 3;
    }

    *outBytes = out;
    *outLen   = length;

    return length;
  }
};

}
