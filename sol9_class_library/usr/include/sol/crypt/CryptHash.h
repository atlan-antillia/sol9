/******************************************************************************
 *
 * Copyright (c) 2009 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  CryptHash.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/13
// 2009/03/29 Added a new method duplicate().
// 2009/03/31 Added a method hashSessionKey(),

#pragma once

#include <sol/crypt/CryptServiceProvider.h>

#include <sol/Bytes.h>

namespace SOL {

class CryptHash :public Object {
private:
  HCRYPTHASH hHash;


protected:
  /**
   * Constructor
   */
  CryptHash()
  :hHash(NULL){

  }

public:
  /**
   * Destructor
   */
  ~CryptHash() {
    clear();
  }

private:
  void clear() {

    if (hHash) {
      CryptDestroyHash(hHash);
      hHash = NULL;
    }
  }

public:
  int create(HCRYPTPROV hProv, ALG_ID algId, 
      HCRYPTKEY hKey=NULL, DWORD dwFlags=0) {
    int rc = NO_ERROR;
    if (!CryptCreateHash(hProv, 
      algId,   
      hKey, 
      dwFlags, 
      &hHash)) {
      //printf("createHash,2,Failed to CryptCreateHash\n");
      rc = GetLastError();
    }
    return rc;
  }

public:
  HCRYPTHASH getHashHandle() {
    return this->hHash;
  }

public:
  //2009/03/29
  void setHashHandle(HCRYPTHASH hHash) {
    this->hHash = hHash;
  }

public:
  //2009/03/29
  int duplicate(CryptHash& dup) {
    int rc = NO_ERROR;
    HCRYPTHASH hDup = NULL;
    if (CryptDuplicateHash(
        this->hHash,
        NULL,
        0,
        &hDup)) {
      //OK
      dup.setHashHandle(hDup);
    } else {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /**
   * Compute a hash value for binary data.
   * @param data  unsigned char binary data
   * @param dataLen bytes-length of data
   *
   */
  int hashData(unsigned char* data, DWORD dataLen, DWORD dwFlags=0) {
    int rc = NO_ERROR;
    if (data !=NULL && dataLen>0) {
      if (!CryptHashData(hHash, data, dataLen, dwFlags)) {
        rc = GetLastError();
      }
    } 
    return rc;
  }


public:
  /**
   * Compute a hash value for a session key.
   * @param hKey A handle to the key object to be hashed.
   *
   */
  //2009/03/31
  int hashSessionKey(HCRYPTKEY hKey, DWORD dwFlags=0) {
    int rc = NO_ERROR;
    //2009/10/23
    if (hKey) {
      if (!CryptHashSessionKey(hHash, hKey, dwFlags)) {
        rc = GetLastError();
      }
    } 
    return rc;
  }

public:
  /**
   * Compute hash value for a binary-content of a filePath.
   *
   * @param filePath  file pathName.
   *
   */
  int hashFile(const TCHAR* filePath, DWORD dwFlags=0) {
    int rc = NO_ERROR;
    if (filePath !=NULL ) {
      HANDLE hFile = CreateFile(filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);
      if (hFile == INVALID_HANDLE_VALUE) {
        //Failed to open the file of filePath.
        rc = GetLastError();

      } else { 
        const int SIZE =1024;

        BYTE buffer[SIZE];
        DWORD readBytes = 0;

        while (ReadFile(hFile, buffer, SIZE, &readBytes, NULL)) {
          if (readBytes ==0) {
            break;
          }
          rc = hashData(buffer, readBytes);
          if (rc != NO_ERROR) {
            break;
          }
        }
        CloseHandle(hFile);
      }      
    } 
    return rc;
  }

public:
  /**
   * Compute hash value for a NULL-terminated string.
   *
   * @param string  NULL-terminated string.
   *
   */
  int hashString(const char* string, DWORD dwFlags=0) {
    int rc = NO_ERROR;
    if (string !=NULL) {
      if (!CryptHashData(hHash, (unsigned char*)string, strlen(string), dwFlags)) {
        rc = GetLastError();
      }
    } 
    return rc;
  }

public:  
  int getAlgId(DWORD* algId, DWORD dwFlags=0) {
    int rc = NO_ERROR;
    if (algId) {
      DWORD id = 0;
      if (CryptGetHashParam(hHash, HP_ALGID, NULL, &id, dwFlags)) {
        *algId = id;
      } else 
      rc = GetLastError();
    }
    return rc;
  }

public:  
  /**
   * Get the hash-value as Bytes.
   * @param bytes Reference to Bytes.
   *
   * Bytes bytes;
   * CrypteHash hash;
   * hash.getHashValue(bytes);
   * 
   */
  int getHashValue(Bytes& bytes) {
    unsigned char* v = NULL;
    unsigned int len = 0;
    int rc = NO_ERROR;
    if ((rc =getHashValue(&v, (DWORD*)&len)) ==NO_ERROR) {
      //It's much better to use shallowcopy
      bytes.shallowCopy(v, len);    
    }
    return rc;  
  }

public:  
  /**
   *
   * Get the hash-value.
   * @param value Pointer to pointer to unsigned char.
   * @param length Pointer to DWORD.
   *
   * Usage:
   * unsigned char* value = NULL;
   * DWORD          length = 0;
   *
   * CryptHash chash;
   *
   * chash.getHashValue(&value, &length);
   * delete [] value;
   * //You have to delete [] value after usage.
   */
  int getHashValue(unsigned char** value, DWORD* length) {
    int rc = NO_ERROR;
    DWORD len = 0;
    if (value != NULL && length != NULL) {
      *value  = '\0';
      *length = 0;
      if (CryptGetHashParam(hHash, HP_HASHVAL, NULL, &len, 0)) {
        *length = len; 
        unsigned char* val = new unsigned char[len];
 
        if (CryptGetHashParam(hHash, HP_HASHVAL, val, &len, 0)) {
          *value = val;    
        } else {
          delete [] val;
          rc = GetLastError();
        } 
      } else {
        rc = GetLastError();
      }
    }
    return rc;
    }
public:
  int setHashParam(DWORD type, BYTE* param)
  {
    int rc = 0;
    if (!CryptSetHashParam(
      hHash,                
      type,  //HP_HMAC_INFO,         
      param,  //(BYTE*)&HmacInfo,     
      0)) {
      rc = GetLastError();
    }
    return rc;
  }
};

}
