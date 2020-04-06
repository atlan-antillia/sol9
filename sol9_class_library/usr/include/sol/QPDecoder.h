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
 *  QPDecoder.h
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

class QPDecoder :public Object {
private:
  bool underScoreToSpace;

public:
  /**
   *
   */
  QPDecoder(bool toSpace=true) {
    //2009/12/18
    this->underScoreToSpace = toSpace;
  }

public:
  /**
   * Decode QPEncoded string.
   * @param string  [in] NULL terminated string of QPEncoded data.
   * @param bytes    [out] Reference to ByteArray to return decoded data.
   */
  int decode(__in const char* string, __out Bytes& bytes)
  {
    int rc = 0;
    if (string == NULL) {
      return rc;
    }

    unsigned char* dec = NULL;
    unsigned int  len  = 0;
    rc = decode(string, &dec, &len);
    if (rc>0) {
      bytes.shallowCopy(dec, len);
    }
    return rc;
  }

public:
  int decode(__in const StringT<char>& cstring, __out Bytes& bytes)
  {
    int rc = 0;
    const char* string = (const char*)cstring;

    if (string == NULL) {
      return rc;
    }

    unsigned char* dec = NULL;
    unsigned int  len  = 0;
    rc = decode(string, &dec, &len);
    if (rc>0) {
      bytes.shallowCopy(dec, len);
    }
    return rc;
  }


public:
  /**
   * Decode a QPEncoded string (NULL terminated), and return the decoded bytes array to the parameter
   * dec, and the length of the bytes to the parameter len.
   *
   *
   */
  int decode(const char* string, unsigned char** dec, unsigned int* len)
  {
    int n = 0;

    *dec = NULL;
    *len = 0;

    if (string == NULL) {
      return n;
    }

    size_t  slen = strlen(string);

    //Do allocate a lot of memory buffer to store decoded bytes. 
    unsigned char* data = new unsigned char[slen+1];
    
    memset(data, 0, slen);


    for (size_t i = 0; i < slen; i++) {
      //printf("%d %c\n", i, string[i]);    
      if (string[i] == '_') {
        
        if (underScoreToSpace) {
          data[n++] = ' ';
        } else {
          data[n++] = string[i];
        }
        continue;
      }
      
      if (string[i] == '=') {
      
        if (++i>= slen) {
          break;
        }

        if (string[i] != '\n') {
           int c1 = toInteger(string[i]);
          if (++i>= slen) {
            break;
          }
          int c2 = toInteger(string[i]);
          data[n++] = (unsigned char)(c1 << 4 | c2);
        } else {
          //Ignore the new line '\n'
        }
      } else {
        data[n++] =(unsigned char)string[i];
       }
    }

    *dec = data;
    *len = n;

    return n;
  }

private:
  int toInteger(char c) {


    static char hex[] = {
     '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F' };

    c = toUpper(c);

    int r = -1;
    for (int i = 0; i < 16; i++) {
      if (hex[i] == c) {
        r = i;
        break;
      }
    }
    return r;
  }


private:
  char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
            c = c - ('a' - 'A');
    }
    return c;
  }

};


}
