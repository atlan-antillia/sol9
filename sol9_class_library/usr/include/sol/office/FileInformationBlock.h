/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FileInformationBlock.h
 *
 *****************************************************************************/

// 2012/05/15


// This is based on MS-DOC on Miscroft Office Word file format.

#pragma once

// Word's File-Information-Block (FIB) structure...
/*
   typedef struct _fib {
      short magicNumber;
      // Word 6.0: 0xA5DC
      // Word 7.0 (95): 0xA5DC
      // Word 8.0 (97): 0xA5EC

      short version;   // >= 101 for Word 6.0 and higher...
      // Word 6.0: 101
      // Word 7.0 (95): 104
      // Word 8.0 (97): 105
   } FIB, *LPFIB;
*/


namespace SOL {

struct FileInformationBlock {
//0  
  //Beginning of the FIB header 

  unsigned short  wIdent;   
    //magic number 
    // Word 6.0: 0xA5DC
    // Word 7.0 (95): 0xA5DC
        // Word 8.0 (97): 0xA5EC
//2 
  unsigned short  nFib;     
    //FIB version written. This will be >= 101 for all 
    //Word 6.0 for Windows and after documents. 

//4 
  unsigned short   nProduct;   
    //product version written by 
//6 
  unsigned short  lid;     
    //Language stamp -- localized version
    //In pre-WinWord 2.0 files this value was the nLocale. 
    //If value is < 999, then it is the nLocale, otherwise it is the lid. 

//8
  short  pnNext;     //short    

//10 
  unsigned char fDot:1;     
    //0x0001 Set if this document is a template  

  unsigned char fGlsy:1;     
    //0x0002 Set if this document is a glossary 

  unsigned char fComplex:1;  
    //0x0004 when 1, file is in complex, fast-saved format. 

  unsigned char fHasPic:1;  
    //0x0008 set if file contains 1 or more pictures 

  unsigned char cQuickSaves:4;  
    //0x00F0 count of times file was quicksaved 
  
//11
  unsigned char fEncrypted:1;  
    //0x0100 Set if file is encrypted

  unsigned char fWhichTblStm:1;  
    //0x0200 When 0, this fib refers to the table       
    //stream named "0Table", when 1, this fib refers to the table stream named "1Table". 
    //Normally, a file will have only one table stream, but under unusual 
    //circumstances a file may have table streams with both names. 
    //In that case, this flag must be used to decide which table stream is valid. 

  unsigned char fReadOnlyRecommended:1;  
    //0x0400 Set when user has recommended that file be read read-only 

  unsigned char fWriteReservation:1;  
    //0x0800 Set when file owner has made the file write reserved 

  unsigned char fExtChar:1;    
    //0x1000 Set when using extended character set in file 

  unsigned char fLoadOverride:1;     
    //0x2000 REVIEW 
  
  unsigned char fFarEast:1;    
    //0x4000 REVIEW 

  unsigned char fCrypto:1;    
    //0x8000 REVIEW 


//12 0
  unsigned short   nFibBack;    
    //This file format it compatible with readers that understand 
    //nFib at or above this value. 

//14  
  unsigned char lKey[4];          
    //File encrypted key, only valid if fEncrypted. 

//18   unsigned char   envr;    
    //Environment in which file was created
    //0 created by Win Word
    //1 created by Mac Word 

};

}
