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
 *  CryptError.h
 *
 *****************************************************************************/

// SOL9
// 2009/03/15

#pragma once

#include <sol/Object.h>
#include <sol/Arg.h>
#include <wincrypt.h>


namespace SOL {

class CertTrustError :public Object {

public:
  static const TCHAR* getErrorMessage(DWORD errId)
  {
    const TCHAR* message = _T("Unknown");

    static const Arg errors[] = {

    {_T("No error found for this certificate or chain."),
      CERT_TRUST_NO_ERROR},

    {_T("This certificate or one of the certificates in the certificate chain is not time-valid"),
      CERT_TRUST_IS_NOT_TIME_VALID},

    {_T("Certificates in the chain are not properly time-nested"),
      CERT_TRUST_IS_NOT_TIME_NESTED},

    {_T("Trust for this certificate or one of the certificates in the certificate chain has been revoked"),
      CERT_TRUST_IS_REVOKED},
    

    {_T("The certificate or one of the certificates in the certificate chain does not have a valid signature."),
      CERT_TRUST_IS_NOT_SIGNATURE_VALID},


    {_T("The certificate or certificate chain is not valid in its proposed usage."),
      CERT_TRUST_IS_NOT_VALID_FOR_USAGE},

    {_T("The certificate or certificate chain is based on an untrusted root."),
      CERT_TRUST_IS_UNTRUSTED_ROOT},


    {_T("The revocation status of the certificate or one of the certificates in the certificate chain is unknown."),
      CERT_TRUST_REVOCATION_STATUS_UNKNOWN},


    {_T("One of the certificates in the chain was issued by a certification authority that the original certificate had certified"),
      CERT_TRUST_IS_CYCLIC},
 
    {_T("The certificate chain is not complete."),
      CERT_TRUST_IS_PARTIAL_CHAIN},

    {_T("A CTL used to create this chain was not time-valid."),
      CERT_TRUST_CTL_IS_NOT_TIME_VALID}, 

    {_T("A CTL used to create this chain did not have a valid signature."),
      CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID},

    {_T("A CTL used to create this chain is not valid for this usage."),
      CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE},
    };

  
    int num = XtNumber(errors);
    for (int i = 0; i<num; i++) {
      if (errors[i].value == errId) {
        message = errors[i].name;
        break;
      }
    }
    return message;
  }
};

}
