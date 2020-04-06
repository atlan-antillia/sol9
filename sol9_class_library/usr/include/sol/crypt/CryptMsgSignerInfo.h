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
 *  CryptMsgSignerInfo.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/25
// 2009/04/08 Added a method getSigningTime(String&).

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>

namespace SOL {

class CryptMsgSignerInfo :public Object {

private:
  PCMSG_SIGNER_INFO pSignerInfo;

private:
  DWORD encodingType;

public:
  /**
   * Constructor
   */
  CryptMsgSignerInfo(__in_opt PCMSG_SIGNER_INFO pInfo=NULL, 
      __in_opt DWORD encoding=(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING)) 
  :pSignerInfo(pInfo),
  encodingType(encoding)
  {

  }

public:
  /**
   * Destructor
   */
  ~CryptMsgSignerInfo() 
  {
    clear();
  }

private:
  void clear()
  {
    if (pSignerInfo) {
      delete pSignerInfo;
      pSignerInfo = NULL;
    }
  }

public:
  PCMSG_SIGNER_INFO getSignerInfo() 
  {
    return this->pSignerInfo;
  }

public:
  void setSignerInfo(PCMSG_SIGNER_INFO pInfo) 
  {
    this->pSignerInfo = pInfo;
  }


public:
  /**
   * Find a counterSignerInfo of szOID_RSA_counterSign OID, and return it to
   * the parameter counterSingerInfo.
   */  
  int getCounterSignerInfo(__out CryptMsgSignerInfo& counterSignerInfo)
  {
    int rc = 0xffffffff;
    
    PCMSG_SIGNER_INFO pCounterSignerInfo = NULL;

    // Find an attribute of szOID_RSA_counterSign OID from 
    // the array of pSignerInfo->UnauthAttrs.rgAttr.

    for (DWORD n = 0; n < pSignerInfo->UnauthAttrs.cAttr; n++) {
            
      if (strcmp(pSignerInfo->UnauthAttrs.rgAttr[n].pszObjId, 
                           szOID_RSA_counterSign) == 0) {

        // Get the size of CMSG_SIGNER_INFO.
        DWORD dwSize = 0;
        if (!CryptDecodeObject(this->encodingType,
                               PKCS7_SIGNER_INFO,
                               pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].pbData,
                               pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].cbData,
                               0,
                               NULL,
                               &dwSize)) {
          //Failed to get the size
          rc = GetLastError();
          break;
        }             

        pCounterSignerInfo = (PCMSG_SIGNER_INFO)new BYTE[dwSize];

        if (CryptDecodeObject(this->encodingType,
          PKCS7_SIGNER_INFO,
          pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].pbData,
          pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].cbData,
                               0,
                               pCounterSignerInfo,
                               &dwSize)) {

          //OK
          counterSignerInfo.setSignerInfo(pCounterSignerInfo);
          rc = NO_ERROR;
        } else {
          //Failed to get pCounterSignerInfo
          delete pCounterSignerInfo;
          rc = GetLastError();
        }
        break;

      } // if strcmp
    } //for

    return rc;
  }

public:
  /*
    string  signingTime of the format "YYYY/MM/DD HH:MM"
    sprintf(dateTime, "%04d/%02d/%02d %02d:%02d\n",
                                            st.wYear,
                                            st.wMonth,
                                            st.wDay,
                                            st.wHour,
                                            st.wMinute);
   */
  //2009/04/08
  int getSigningTime(__out String& string) 
  {
    int rc = -1;

    SYSTEMTIME st;
    if (getSigningTime(st) ==NO_ERROR) { 
      char dateTime[128];
  
      sprintf_s(dateTime, CountOf(dateTime), "%04d/%02d/%02d %02d:%02d\n",
                                            st.wYear,
                                            st.wMonth,
                                            st.wDay,
                                            st.wHour,
                                            st.wMinute);
      string = dateTime;
      rc = NO_ERROR;
    }
    return rc;
  }
public:
  // Get a signing time from a pSignerInfo of counterSignerInfo  

  int getSigningTime(__out SYSTEMTIME& st)
  {   
        int rc = 0xffffffff; 
    
        // Find an authAttr of szOID_RSA_signingTime OID.
    for (DWORD n = 0; n < pSignerInfo->AuthAttrs.cAttr; n++) {           
  
      if (strcmp(szOID_RSA_signingTime, 
                        pSignerInfo->AuthAttrs.rgAttr[n].pszObjId) == 0) {               
     
        FILETIME ft;   
       
        DWORD dwData = sizeof(ft);
        if (CryptDecodeObject(this->encodingType,
          szOID_RSA_signingTime,
          pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].pbData,
          pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].cbData,
          0,
          &ft,
           &dwData)) {

          //OK
    
          FILETIME lft;   
          FileTimeToLocalFileTime(&ft, &lft);
          FileTimeToSystemTime(&lft, &st);

          rc = NO_ERROR;
        } else {
          rc = GetLastError();
        }
        break;
      } 
    }
    return rc;
  }

};

}

