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
 *  CryptKey.h
 *
 *****************************************************************************/

// SOL9
// 2009/02/22
// 2009/03/01 Modified exportKey method.
// 2010/04/08 Modified not to use Error macro.

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

// 2009/02/28
#include <sol/Bytes.h>

namespace SOL {

class CryptKey :public Object {

private:
  HCRYPTKEY hKey;

public:
  /**
   * Constructor
   */
  CryptKey()
  :hKey(NULL) {
  }

public:
  /**
   * Destructor
   */
  ~CryptKey() {
    if (hKey) {
      CryptDestroyKey(hKey);
      hKey = NULL;
    }
  }


public:
  /**
   *
   */
  int generate(HCRYPTPROV hProv, ALG_ID algId, DWORD flags=0) {
    int rc = NO_ERROR;
    if (!CryptGenKey(hProv, 
        algId, 
        flags,  
           &hKey)) {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /**
   *
   */
  int derive(HCRYPTPROV hProv, ALG_ID algId, HCRYPTHASH hCryptHash, DWORD flags=0) {
    int rc = NO_ERROR;
    if (!CryptDeriveKey(hProv, 
        algId, 
        hCryptHash,
        flags,  
           &hKey)) {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /**
   *
   */
  int getUserKey(HCRYPTPROV hProv, DWORD keySpec) {
    int rc = NO_ERROR;
    if (!CryptGetUserKey(   
           hProv,    
           keySpec,  //AT_KEYEXCHANGE or AT_SIGNATURE. 
           &hKey)) {
      rc = GetLastError();
    }
    return rc;
  }

public:
  void setKeyHandle(HCRYPTKEY key) {
    this->hKey = key;
  }

public:
  HCRYPTKEY getKeyHandle() {
    return this->hKey;
  }


public:
  int getKeyParam(DWORD dwParam,   BYTE *pbData,     /*[in]*/
      DWORD *pdwDataLen,  /*[inout]*/
      DWORD dwFlags)     /*[in]*/
  {
    int rc = NO_ERROR;
    if (!CryptGetKeyParam(
       this->hKey,
        dwParam,
       pbData,
        pdwDataLen,
      dwFlags)) {
      rc = GetLastError();
    }
    return rc;
  }


public:
  int setKeyParam(DWORD dwParam, const BYTE *pbData, DWORD flags) 
  {
    int rc = NO_ERROR;
    if (!CryptSetKeyParam(
       this->hKey,
        dwParam,
       pbData,
        flags)) {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /** 
   * Set padding mode.
   * @param paddingMode  Padding Mode
   *  Default:PKCS5_PADDING;
   */
  int setPaddingMode(DWORD paddingMode=PKCS5_PADDING) {
    return setKeyParam(KP_PADDING, (BYTE*)&paddingMode, 0);
  }

public:
  /**
   * Extract binary key data.
   *
   *
    CryptKey cryptkey;
    Bytes key;
    cryptKey.exportKey(SIMPLEBLOB, key, 0);

   */
  int exportKey(DWORD keyBlob, Bytes& bytes, DWORD flags) {
    int rc = NO_ERROR;

    unsigned char* key = NULL;
    unsigned int  length = 0;

    if (exportKey(keyBlob, &key, &length, flags) == NO_ERROR) {
        bytes.shallowCopy(key, length);
    } else {
      rc = -1;
    }
    return rc;
  }

public:
  /**
   * Export keyBlob.
   *
   * @param  keyBlob specifies one of the following values.
      OPAQUEKEYBLOB
      PRIVATEKEYBLOB
      PUBLICKEYBLOB
      SIMPLEBLOB
      PLAINTEXTKEYBLOB
      SYMMETRICWRAPKEYBLOB
    --
   * @param dwFlags specifies 0 or one or some combination of the following values.
      CRYPT_BLOB_VER3
      CRYPT_DESTROYKEY 
      CRYPT_OAEP
      CRYPT_SSL2_FALLBACK
   */
  // 2009/03/01 Added the dwFlags parameter
  int exportKey(DWORD keyBlob, unsigned char** key, unsigned int* length, DWORD flags) {
     int rc = 0;
    // Get the length of keyBlob
    HCRYPTKEY hKey = getKeyHandle();
    DWORD len = NO_ERROR;
    if (CryptExportKey(hKey,    
         NULL,    
         keyBlob,
         flags,    
         NULL, 
         &len)) {

      // Allocate memory of size len for the keyBlob.
      unsigned char* buffer = new unsigned char[len];

      if (CryptExportKey(hKey, 
        NULL,    
        keyBlob,
        flags,    
         buffer,    
           &len)){
        //OK
        *length = len;
        *key    = buffer;
      } else {
        //FAILED
        delete [] buffer;
        rc = GetLastError();
      }      
    } else {
      rc = GetLastError();
    }
    return rc;
  }

public:
  /**
   * Import keyBlob data.
   *
   */
  //2009/03/05 Added.
  int importKey(HCRYPTPROV hProv, Bytes& bytes,
        HCRYPTKEY hPubKey = NULL, DWORD flags = 0)
  {
    return importKey(hProv, bytes.getData(), bytes.getSize(), hPubKey, flags);
  }


public:
  /**
   * Import keyBlob data.
   *
   */
  //2009/03/02 Added.
  int importKey(HCRYPTPROV hProv, unsigned char* data, size_t dataLen,
        HCRYPTKEY hPubKey = NULL, DWORD flags = 0)
  {
    int rc = NO_ERROR;
    if (data !=NULL && dataLen > 0) {
      if (!CryptImportKey(
        hProv,
        data,
        dataLen,
        hPubKey,
        flags,
        &hKey)) {

        rc = GetLastError();
      }
    } else {
      rc = -1;
    }
    return rc;
  }


public:
  int encrypt(unsigned char* buffer, size_t* dataLen,  
        size_t buffLen, BOOL isEnd)

  {
    int rc = NO_ERROR;

    if (buffer !=NULL && *dataLen <=buffLen) {
      if (!CryptEncrypt(hKey, 0, isEnd, 0, 
        buffer, (DWORD*)dataLen, buffLen)) {
        rc = GetLastError();
      }
    } else {
      rc = -1;
    }
    return rc;
  }

public:
  /**
   * @param dataLen  [in,out] Pointer to size_t.
   *    In case itstores the original encrypted data size of buffer
   *    Out case it stores the decrypted data size of buffer.
   */
  int decrypt(unsigned char* buffer, 
        size_t* dataLen,  
        BOOL isEnd)

  {
    int rc = NO_ERROR;
    if (buffer !=NULL) {
      if (!CryptDecrypt(hKey, 0, isEnd, 0, 
        buffer, (DWORD*)dataLen)) {
        rc = GetLastError();
      }
    } else {
      rc = -1;
    }
    return rc;
  }

public:
  int encryptFile(const TCHAR* inFilePath, const TCHAR* outFilePath)
  {
    int rc = NO_ERROR;
    HANDLE hIn = CreateFile(inFilePath, 
        GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hIn == INVALID_HANDLE_VALUE) {
      return -1;
    }

    HANDLE hOut = CreateFile(outFilePath, 
        GENERIC_WRITE, FILE_SHARE_READ,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hOut == INVALID_HANDLE_VALUE) {
      return -1;
    }
    //Files are ready!

    const int READ_SIZE = 1024;
    const int BUFF_SIZE = READ_SIZE + 128;
    unsigned char buffer[BUFF_SIZE];
    BOOL isEnd = FALSE;
    DWORD dwRead = 0;
    DWORD dwWritten = 0;
    
    while (ReadFile(hIn, buffer, READ_SIZE, &dwRead, NULL)) {
      if (dwRead < READ_SIZE) {
        isEnd = TRUE;
      }
      if (!CryptEncrypt(hKey, 0, isEnd, 0, buffer, &dwRead, BUFF_SIZE)) {
        rc = GetLastError();
        break;
      }

      if (!WriteFile(hOut, buffer, dwRead, &dwWritten, NULL) ) {
        rc = GetLastError();
        break;
      }
    }

    CloseHandle(hIn);
    CloseHandle(hOut);

    return rc;
  }

public:
  int decryptFile(const TCHAR* inFilePath, const TCHAR* outFilePath)
  {
    int rc = NO_ERROR;

    HANDLE hIn = CreateFile(inFilePath, 
        GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hIn == INVALID_HANDLE_VALUE) {
      return -1;
    }

    HANDLE hOut = CreateFile(outFilePath, 
        GENERIC_WRITE, FILE_SHARE_READ,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hOut == INVALID_HANDLE_VALUE) {
      return -1;
    }
    //Files are ready!

    const int READ_SIZE = 1024;
    const int BUFF_SIZE = READ_SIZE + 128;
    unsigned char buffer[BUFF_SIZE];
    BOOL isEnd = FALSE;
    DWORD dwRead = 0;
    DWORD dwWritten = 0;
  
    while (ReadFile(hIn, buffer, READ_SIZE, &dwRead, NULL)) {
      if (dwRead < READ_SIZE) {
        isEnd = TRUE;
      }
      if (!CryptDecrypt(hKey, 0, isEnd, 0, buffer, &dwRead)) {
        rc = GetLastError();
        break;
      }
      if (!WriteFile(hOut, buffer, dwRead, &dwWritten, NULL)) {
        rc = GetLastError();
        break;
      }
    }
    CloseHandle(hIn);
    CloseHandle(hOut);

    return rc;
  }
};

}
