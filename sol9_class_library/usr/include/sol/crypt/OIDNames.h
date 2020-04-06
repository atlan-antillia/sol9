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
 *  OIDNames.h
 *
 *****************************************************************************/

// SOL9
// 2009/10/04

#pragma once


#include <sol/Object.h>

namespace SOL {

class OIDNames :public Object {

public:
  OIDNames()
  {
  }

public:
  const char* getName(const char* oid)
  {
    typedef struct {
      const char* name;
      const char* id;
    } NamePair;

    static const NamePair names[] =
    { 
      {"RSA",  "1.2.840.113549"},
      {"PKCS",  "1.2.840.113549.1"},
      {"RSA_HASH",  "1.2.840.113549.2"},
      {"RSA_ENCRYPT",  "1.2.840.113549.3"},
      {"PKCS_1",  "1.2.840.113549.1.1"},
      {"PKCS_2",  "1.2.840.113549.1.2"},
      {"PKCS_3",  "1.2.840.113549.1.3"},
      {"PKCS_4",  "1.2.840.113549.1.4"},
      {"PKCS_5",  "1.2.840.113549.1.5"},
      {"PKCS_6",  "1.2.840.113549.1.6"},
      {"PKCS_7",  "1.2.840.113549.1.7"},
      {"PKCS_8",  "1.2.840.113549.1.8"},
      {"PKCS_9",  "1.2.840.113549.1.9"},
      {"PKCS_10",  "1.2.840.113549.1.10"},
      {"PKCS_11",  "1.2.840.113549.1.12"},
      {"RSA_RSA",  "1.2.840.113549.1.1.1"},
      {"RSA_MD2RSA",  "1.2.840.113549.1.1.2"},
      {"RSA_MD4RSA",  "1.2.840.113549.1.1.3"},
      {"RSA_MD5RSA",  "1.2.840.113549.1.1.4"},
      {"RSA_SHA1RSA",  "1.2.840.113549.1.1.5"},
      {"RSA_SET0AEP_RSA",  "1.2.840.113549.1.1.6"},
      {"RSA_DH",  "1.2.840.113549.1.3.1"},
      {"RSA_data",  "1.2.840.113549.1.7.1"},
      {"RSA_signedData",  "1.2.840.113549.1.7.2"},
      {"RSA_envelopedData",  "1.2.840.113549.1.7.3"},
      {"RSA_signEnvData",  "1.2.840.113549.1.7.4"},
      {"RSA_digestedData",  "1.2.840.113549.1.7.5"},
      {"RSA_hashedData",  "1.2.840.113549.1.7.5"},
      {"RSA_encryptedData",  "1.2.840.113549.1.7.6"},
      {"RSA_emailAddr",  "1.2.840.113549.1.9.1"},
      {"RSA_unstructName",  "1.2.840.113549.1.9.2"},
      {"RSA_contentType",  "1.2.840.113549.1.9.3"},
      {"RSA_messageDigest",  "1.2.840.113549.1.9.4"},
      {"RSA_signingTime",  "1.2.840.113549.1.9.5"},
      {"RSA_counterSign",  "1.2.840.113549.1.9.6"},
      {"RSA_challengePwd",  "1.2.840.113549.1.9.7"},
      {"RSA_unstructAddr",  "1.2.840.113549.1.9.9"},
      {"RSA_extCertAttrs",  "1.2.840.113549.1.9.9"},
      {"RSA_certExtensions",  "1.2.840.113549.1.9.14"},
      {"RSA_SMIMECapabilities",  "1.2.840.113549.1.9.15"},
      {"RSA_preferSignedData",  "1.2.840.113549.1.9.15.1"},
      {"RSA_SMIMEalg",  "1.2.840.113549.1.9.16.3"},
      {"RSA_SMIMEalgESDH",  "1.2.840.113549.1.9.16.3.5"},
      {"RSA_SMIMEalgCMS3DESwrap",  "1.2.840.113549.1.9.16.3.6"},
      {"RSA_SMIMEalgCMSRC2wrap",  "1.2.840.113549.1.9.16.3.7"},
      {"RSA_MD2",  "1.2.840.113549.2.2"},
      {"RSA_MD4",  "1.2.840.113549.2.4"},
      {"RSA_MD5",  "1.2.840.113549.2.5"},
      {"RSA_RC2CBC",  "1.2.840.113549.3.2"},
      {"RSA_RC4",  "1.2.840.113549.3.4"},
      {"RSA_DES_EDE3_CBC",  "1.2.840.113549.3.7"},
      {"RSA_RC5_CBCPad",  "1.2.840.113549.3.9"},
      {"ANSI_X942",  "1.2.840.10046"},
      {"ANSI_X942_DH",  "1.2.840.10046.2.1"},
      {"X957",  "1.2.840.10040"},
      {"X957_DSA",  "1.2.840.10040.4.1"},
      {"X957_SHA1DSA",  "1.2.840.10040.4.3"},
      {"DS",  "2.5"},
      {"DSALG",  "2.5.8"},
      {"DSALG_CRPT",  "2.5.8.1"},
      {"DSALG_HASH",  "2.5.8.2"},
      {"DSALG_SIGN",  "2.5.8.3"},
      {"DSALG_RSA",  "2.5.8.1.1"},
      {"OIW",  "1.3.14"},
      {"OIWSEC",  "1.3.14.3.2"},
      {"OIWSEC_md4RSA",  "1.3.14.3.2.2"},
      {"OIWSEC_md5RSA",  "1.3.14.3.2.3"},
      {"OIWSEC_md4RSA2",  "1.3.14.3.2.4"},
      {"OIWSEC_desECB",  "1.3.14.3.2.6"},
      {"OIWSEC_desCBC",  "1.3.14.3.2.7"},
      {"OIWSEC_desOFB",  "1.3.14.3.2.8"},
      {"OIWSEC_desCFB",  "1.3.14.3.2.9"},
      {"OIWSEC_desMAC",  "1.3.14.3.2.10"},
      {"OIWSEC_rsaSign",  "1.3.14.3.2.11"},
      {"OIWSEC_dsa",  "1.3.14.3.2.12"},
      {"OIWSEC_shaDSA",  "1.3.14.3.2.13"},
      {"OIWSEC_mdc2RSA",  "1.3.14.3.2.14"},
      {"OIWSEC_shaRSA",  "1.3.14.3.2.15"},
      {"OIWSEC_dhCommMod",  "1.3.14.3.2.16"},
      {"OIWSEC_desEDE",  "1.3.14.3.2.17"},
      {"OIWSEC_sha",  "1.3.14.3.2.18"},
      {"OIWSEC_mdc2",  "1.3.14.3.2.19"},
      {"OIWSEC_dsaComm",  "1.3.14.3.2.20"},
      {"OIWSEC_dsaCommSHA",  "1.3.14.3.2.21"},
      {"OIWSEC_rsaXchg",  "1.3.14.3.2.22"},
      {"OIWSEC_keyHashSeal",  "1.3.14.3.2.23"},
      {"OIWSEC_md2RSASign",  "1.3.14.3.2.24"},
      {"OIWSEC_md5RSASign",  "1.3.14.3.2.25"},
      {"OIWSEC_sha1",  "1.3.14.3.2.26"},
      {"OIWSEC_dsaSHA1",  "1.3.14.3.2.27"},
      {"OIWSEC_dsaCommSHA1",  "1.3.14.3.2.28"},
      {"OIWSEC_sha1RSASign",  "1.3.14.3.2.29"},
      {"OIWDIR",  "1.3.14.7.2"},
      {"OIWDIR_CRPT",  "1.3.14.7.2.1"},
      {"OIWDIR_HASH",  "1.3.14.7.2.2"},
      {"OIWDIR_SIGN",  "1.3.14.7.2.3"},
      {"OIWDIR_md2",  "1.3.14.7.2.2.1"},
      {"OIWDIR_md2RSA",  "1.3.14.7.2.3.1"},
      {"INFOSEC",  "2.16.840.1.101.2.1"},
      {"INFOSEC_sdnsSignature",  "2.16.840.1.101.2.1.1.1"},
      {"INFOSEC_mosaicSignature",  "2.16.840.1.101.2.1.1.2"},
      {"INFOSEC_sdnsConfidentiality",  "2.16.840.1.101.2.1.1.3"},
      {"INFOSEC_mosaicConfidentiality",  "2.16.840.1.101.2.1.1.4"},
      {"INFOSEC_sdnsIntegrity",  "2.16.840.1.101.2.1.1.5"},
      {"INFOSEC_mosaicIntegrity",  "2.16.840.1.101.2.1.1.6"},
      {"INFOSEC_sdnsTokenProtection",  "2.16.840.1.101.2.1.1.7"},
      {"INFOSEC_mosaicTokenProtection",  "2.16.840.1.101.2.1.1.8"},
      {"INFOSEC_sdnsKeyManagement",  "2.16.840.1.101.2.1.1.9"},
      {"INFOSEC_mosaicKeyManagement",  "2.16.840.1.101.2.1.1.10"},
      {"INFOSEC_sdnsKMandSig",  "2.16.840.1.101.2.1.1.11"},
      {"INFOSEC_mosaicKMandSig",  "2.16.840.1.101.2.1.1.12"},
      {"INFOSEC_SuiteASignature",  "2.16.840.1.101.2.1.1.13"},
      {"INFOSEC_SuiteAConfidentiality",  "2.16.840.1.101.2.1.1.14"},
      {"INFOSEC_SuiteAIntegrity",  "2.16.840.1.101.2.1.1.15"},
      {"INFOSEC_SuiteATokenProtection",  "2.16.840.1.101.2.1.1.16"},
      {"INFOSEC_SuiteAKeyManagement",  "2.16.840.1.101.2.1.1.17"},
      {"INFOSEC_SuiteAKMandSig",  "2.16.840.1.101.2.1.1.18"},
      {"INFOSEC_mosaicUpdatedSig",  "2.16.840.1.101.2.1.1.19"},
      {"INFOSEC_mosaicKMandUpdSig",  "2.16.840.1.101.2.1.1.20"},
      {"INFOSEC_mosaicUpdateInteg",  "2.16.840.1.101.2.1.1.21"},
      {"COMMON_NAME",  "2.5.4.3"},
      {"SUR_NAME",  "2.5.4.4"},
      {"DEVICE_SERIAL_NUMBER",  "2.5.4.5"},
      {"COUNTRY_NAME",  "2.5.4.6"},
      {"LOCALITY_NAME",  "2.5.4.7"},
      {"STATE_OR_PROVINCE_NAME",  "2.5.4.8"},
      {"STREET_ADDRESS",  "2.5.4.9"},
      {"ORGANIZATION_NAME",  "2.5.4.10"},
      {"ORGANIZATIONAL_UNIT_NAME",  "2.5.4.11"},
      {"TITLE",  "2.5.4.12"},
      {"DESCRIPTION",  "2.5.4.13"},
      {"SEARCH_GUIDE",  "2.5.4.14"},
      {"BUSINESS_CATEGORY",  "2.5.4.15"},
      {"POSTAL_ADDRESS",  "2.5.4.16"},
      {"POSTAL_CODE",  "2.5.4.17"},
      {"POST_OFFICE_BOX",  "2.5.4.18"},
      {"PHYSICAL_DELIVERY_OFFICE_NAME",  "2.5.4.19"},
      {"TELEPHONE_NUMBER",  "2.5.4.20"},
      {"TELEX_NUMBER",  "2.5.4.21"},
      {"TELETEXT_TERMINAL_IDENTIFIER",  "2.5.4.22"},
      {"FACSIMILE_TELEPHONE_NUMBER",  "2.5.4.23"},
      {"X21_ADDRESS",  "2.5.4.24"},
      {"INTERNATIONAL_ISDN_NUMBER",  "2.5.4.25"},
      {"REGISTERED_ADDRESS",  "2.5.4.26"},
      {"DESTINATION_INDICATOR",  "2.5.4.27"},
      {"PREFERRED_DELIVERY_METHOD",  "2.5.4.28"},
      {"PRESENTATION_ADDRESS",  "2.5.4.29"},
      {"SUPPORTED_APPLICATION_CONTEXT",  "2.5.4.30"},
      {"MEMBER",  "2.5.4.31"},
      {"OWNER",  "2.5.4.32"},
      {"ROLE_OCCUPANT",  "2.5.4.33"},
      {"SEE_ALSO",  "2.5.4.34"},
      {"USER_PASSWORD",  "2.5.4.35"},
      {"USER_CERTIFICATE",  "2.5.4.36"},
      {"CA_CERTIFICATE",  "2.5.4.37"},
      {"AUTHORITY_REVOCATION_LIST",  "2.5.4.38"},
      {"CERTIFICATE_REVOCATION_LIST",  "2.5.4.39"},
      {"CROSS_CERTIFICATE_PAIR",  "2.5.4.40"},
      {"GIVEN_NAME",  "2.5.4.42"},
      {"INITIALS",  "2.5.4.43"},
      {"DN_QUALIFIER",  "2.5.4.46"},
      {"AUTHORITY_KEY_IDENTIFIER",  "2.5.29.1"},
      {"KEY_ATTRIBUTES",  "2.5.29.2"},
      {"CERT_POLICIES_95",  "2.5.29.3"},
      {"KEY_USAGE_RESTRICTION",  "2.5.29.4"},
      {"LEGACY_POLICY_MAPPINGS",  "2.5.29.5"},
      {"SUBJECT_ALT_NAME",  "2.5.29.7"},
      {"ISSUER_ALT_NAME",  "2.5.29.8"},
      {"SUBJECT_DIR_ATTRS",  "2.5.29.9"},
      {"BASIC_CONSTRAINTS",  "2.5.29.10"},
      {"SUBJECT_KEY_IDENTIFIER",  "2.5.29.14"},
      {"KEY_USAGE",  "2.5.29.15"},
      {"PRIVATEKEY_USAGE_PERIOD",  "2.5.29.16"},
      {"SUBJECT_ALT_NAME2",  "2.5.29.17"},
      {"ISSUER_ALT_NAME2",  "2.5.29.18"},
      {"BASIC_CONSTRAINTS2",  "2.5.29.19"},
      {"CRL_NUMBER",  "2.5.29.20"},
      {"CRL_REASON_CODE",  "2.5.29.21"},
      {"REASON_CODE_HOLD",  "2.5.29.23"},
      {"DELTA_CRL_INDICATOR",  "2.5.29.27"},
      {"ISSUING_DIST_POINT",  "2.5.29.28"},
      {"NAME_CONSTRAINTS",  "2.5.29.30"},
      {"CRL_DIST_POINTS",  "2.5.29.31"},
      {"CERT_POLICIES",  "2.5.29.32"},
      {"ANY_CERT_POLICY",  "2.5.29.32.0"},
      {"POLICY_MAPPINGS",  "2.5.29.33"},
      {"AUTHORITY_KEY_IDENTIFIER2",  "2.5.29.35"},
      {"POLICY_CONSTRAINTS",  "2.5.29.36"},
      {"ENHANCED_KEY_USAGE",  "2.5.29.37"},
      {"FRESHEST_CRL",  "2.5.29.46"},
      {"DOMAIN_COMPONENT",  "0.9.2342.19200300.100.1.25"},
      {"PKCS_12_FRIENDLY_NAME_ATTR",  "1.2.840.113549.1.9.20"},
      {"PKCS_12_LOCAL_KEY_ID",  "1.2.840.113549.1.9.21"},
      {"CERT_EXTENSIONS",  "1.3.6.1.4.1.311.2.1.14"},
      {"NEXT_UPDATE_LOCATION",  "1.3.6.1.4.1.311.10.2"},
      {"REMOVE_CERTIFICATE",  "1.3.6.1.4.1.311.10.8.1"},
      {"CROSS_CERT_DIST_POINTS",  "1.3.6.1.4.1.311.10.9.1"},
      {"CTL",  "1.3.6.1.4.1.311.10.10.1"},
      {"SORTED_CTL",  "1.3.6.1.4.1.311.10.10.1.1"},
      {"ANY_APPLICATION_POLICY",  "1.3.6.1.4.1.311.10.12.1"},
      {"RENEWAL_CERTIFICATE",  "1.3.6.1.4.1.311.13.1"},
      {"ENROLLMENT_NAME_VALUE_PAIR",  "1.3.6.1.4.1.311.13.2.1"},
      {"ENROLLMENT_CSP_PROVIDER",  "1.3.6.1.4.1.311.13.2.2"},
      {"OS_VERSION",  "1.3.6.1.4.1.311.13.2.3"},
      {"PKCS_12_KEY_PROVIDER_NAME_ATTR",  "1.3.6.1.4.1.311.17.1"},
      {"LOCAL_MACHINE_KEYSET",  "1.3.6.1.4.1.311.17.2"},
      {"AUTO_ENROLL_CTL_USAGE",  "1.3.6.1.4.1.311.20.1"},
      {"ENROLL_CERTTYPE_EXTENSION",  "1.3.6.1.4.1.311.20.2"},
      {"ENROLLMENT_AGENT",  "1.3.6.1.4.1.311.20.2.1"},
      {"CERT_MANIFOLD",  "1.3.6.1.4.1.311.20.3"},
      {"CERTSRV_PREVIOUS_CERT_HASH",  "1.3.6.1.4.1.311.21.2"},
      {"CRL_VIRTUAL_BASE",  "1.3.6.1.4.1.311.21.3"},
      {"CRL_NEXT_PUBLISH",  "1.3.6.1.4.1.311.21.4"},
      {"KP_CA_EXCHANGE",  "1.3.6.1.4.1.311.21.5"},
      {"KP_KEY_RECOVERY_AGENT",  "1.3.6.1.4.1.311.21.6"},
      {"CERTIFICATE_TEMPLATE",  "1.3.6.1.4.1.311.21.7"},
      {"ENTERPRISE_OID_ROOT",  "1.3.6.1.4.1.311.21.8"},
      {"RDN_DUMMY_SIGNER",  "1.3.6.1.4.1.311.21.9"},
      {"APPLICATION_CERT_POLICIES",  "1.3.6.1.4.1.311.21.10"},
      {"APPLICATION_POLICY_MAPPINGS",  "1.3.6.1.4.1.311.21.11"},
      {"APPLICATION_POLICY_CONSTRAINTS",  "1.3.6.1.4.1.311.21.12"},
      {"ARCHIVED_KEY_ATTR",  "1.3.6.1.4.1.311.21.13"},
      {"CRL_SELF_CDP",  "1.3.6.1.4.1.311.21.14"},
      {"REQUIRE_CERT_CHAIN_POLICY",  "1.3.6.1.4.1.311.21.15"},
      {"ARCHIVED_KEY_CERT_HASH",  "1.3.6.1.4.1.311.21.16"},
      {"ISSUED_CERT_HASH",  "1.3.6.1.4.1.311.21.17"},
      {"DS_EMAIL_REPLICATION",  "1.3.6.1.4.1.311.21.19"},
      {"REQUEST_CLIENT_INFO",  "1.3.6.1.4.1.311.21.20"},
      {"ENCRYPTED_KEY_HASH",  "1.3.6.1.4.1.311.21.21"},
      {"CERTSRV_CROSSCA_VERSION",  "1.3.6.1.4.1.311.21.22"},
      {"KEYID_RDN",  "1.3.6.1.4.1.311.10.7.1"},
      {"PKIX",  "1.3.6.1.5.5.7"},
      {"PKIX_PE",  "1.3.6.1.5.5.7.1"},
      {"AUTHORITY_INFO_ACCESS",  "1.3.6.1.5.5.7.1.1"},
      {"PKIX_POLICY_QUALIFIER_CPS",  "1.3.6.1.5.5.7.2.1"},
      {"PKIX_POLICY_QUALIFIER_USERNOTICE",  "1.3.6.1.5.5.7.2.2"},
      {"PKIX_KP",  "1.3.6.1.5.5.7.3"},
      {"PKIX_KP_SERVER_AUTH",  "1.3.6.1.5.5.7.3.1"},
      {"PKIX_KP_CLIENT_AUTH",  "1.3.6.1.5.5.7.3.2"},
      {"PKIX_KP_CODE_SIGNING",  "1.3.6.1.5.5.7.3.3"},
      {"PKIX_KP_EMAIL_PROTECTION",  "1.3.6.1.5.5.7.3.4"},
      {"PKIX_KP_IPSEC_END_SYSTEM",  "1.3.6.1.5.5.7.3.5"},
      {"PKIX_KP_IPSEC_TUNNEL",  "1.3.6.1.5.5.7.3.6"},
      {"PKIX_KP_IPSEC_USER",  "1.3.6.1.5.5.7.3.7"},
      {"PKIX_KP_TIMESTAMP_SIGNING",  "1.3.6.1.5.5.7.3.8"},
      {"IPSEC_KP_IKE_INTERMEDIATE",  "1.3.6.1.5.5.8.2.2"},
      {"SERIALIZED",  "1.3.6.1.4.1.311.10.3.3.1"},
      {"NT_PRINCIPAL_NAME",  "1.3.6.1.4.1.311.20.2.3"},
      {"CERTSRV_CA_VERSION",  "1.3.6.1.4.1.311.21.1"},
      {"PRODUCT_UPDATE",  "1.3.6.1.4.1.311.31.1"},

    };

    int count = sizeof(names)/sizeof(names[0]);

    const char* name = "";
    for (int i = 0; i<count; i++) {

      if (strcmp(names[i].id, oid) == 0) {
        name = names[i].name;
        break;
      }
    }
    return name;
  }

};

}
