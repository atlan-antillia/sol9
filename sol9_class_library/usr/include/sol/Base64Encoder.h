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
 *  Base64Encoder.h
 *
 *****************************************************************************/

#pragma once

#include <sol\Object.h>

#include <sol\Bytes.h>
#include <sol\StringT.h>
#include <sol\String.h>

#include <math.h>

/**
 * Base64Encoder class reprents a base64encoder.
 */
namespace SOL {

class Base64Encoder :public Object {

public:
  /**
   */
  Base64Encoder() {

  }


  /**
   */
  ~Base64Encoder() {

  } 
  
public:
  /**
   * Convert byte array to base64encoded string.
   * @param bytes    [in]  Byte array of data to be encoded.
   *
   * @return char*  Base64Encoded data(NULL terminated string).
   *        You have to delete [] this return value after use.
   */

  char* encode(Bytes& bytes) {
    return encode(bytes.getContents(), bytes.getSize());
  }

public:
  /*
   * Convert byte array to base64encoded string.
   * @param bytes    [in]  Byte array of data to be encoded.
   * @param string  [out]  base64encoed string.
   */
  
  int encode(__in Bytes& bytes, __out StringT<char>& string) {
    int rc = 0;
    char* encoded = encode(bytes.getContents(), bytes.getSize());
    if (encoded) {
      rc = strlen(encoded);
      string.shallowCopy(encoded);
    }
    return rc;
  }

public:
  int encode(__in Bytes& bytes, __out String& string) {
    int rc = 0;
    char* encoded = encode(bytes.getContents(), bytes.getSize());
    if (encoded) {
      rc = strlen(encoded);
      string = encoded;    //This converts char string to wchar_t(TCHAR) string.
      delete [] encoded;
    }
    return rc;
  }

public:

  /**
   * Convert byte array to base64encoded string.
   * @param data    [in]  Byte array of data to be encoded.
   * @param len    [in]  Byte length of data.
   *
   * @return char*  Base64Encoded data(NULL terminated string).
   *        You have to delete [] this return value after use.
   */
  char* encode(__in const unsigned char* data, 
      __in unsigned int slen) {

    static const char table[] = {
      0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
      0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
      0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
      0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
      0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
      0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
      0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33,
      0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F};
    
    if (data == NULL || slen == 0) {
      return NULL;
    }
    unsigned int outlen = ((slen+2)/3)*4;

    // We create a NULL terminated character string.
    char* out = new char[outlen+1];
    memset(out, 0, outlen+1);
    out[outlen] = '\0';

    const char PADDING = '=';

    int n = 0;
    // Convert 3 bytes to 4 bytes.
    for (unsigned int i = 0; i < slen; i += 3) {
      int remain = slen - i;
      int len = (remain>=3) ? 3: remain;
      int a, b, c;
      if (len == 1) {
            a = data[i];
            out[n++] = table[(a >> 2) & 0x3F];
            out[n++] = table[((a << 4) & 0x30)];
          out[n++] = PADDING;  
          out[n++] = PADDING;  
      } else if (len == 2) {
            a = data[i];
            b = data[i+1];
            out[n++] = table[(a >> 2) & 0x3F];
            out[n++] = table[((a << 4) & 0x30) + ((b >> 4) & 0xF)];
            out[n++] = table[((b << 2) & 0x3C)];
          out[n++] = PADDING;  
      } else {
            a = data[i];
            b = data[i+1];
            c = data[i+2];
            out[n++] = table[(a >> 2) & 0x3F];
            out[n++] = table[((a << 4) & 0x30) + ((b >> 4) & 0xF)];
            out[n++] = table[((b << 2) & 0x3C) + ((c >> 6) & 0x3)];
            out[n++] = table[c & 0x3F];
      }
    }
    return out;
  }
};

}

  
