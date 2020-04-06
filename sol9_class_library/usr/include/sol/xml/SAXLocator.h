/******************************************************************************
 *
 * Copyright(c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  SAXLocator.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>

namespace SOL {

class SAXLocator : public XMLObject {

private:
  MSXML2::ISAXLocatorPtr pLocator;

public:
  SAXLocator(MSXML2::ISAXLocator* locator)
  :pLocator(locator)
  {
  }

public:
  ~SAXLocator()
  {
    pLocator = NULL;
  }

public:
  MSXML2::ISAXLocatorPtr getLocatorPtr()
  {
    if (pLocator == NULL) {
      throw Exception(E_FATAL, "Error: SAXLocator is NULL");
    }
    return pLocator;
  }

public:
  int getColumnNumber()
  {
    return getLocatorPtr() -> getColumnNumber();
  }

    
  int getLineNumber()
  {
    return getLocatorPtr() -> getLineNumber();
  }

  unsigned short * getPublicId()
  {
    return getLocatorPtr() -> getPublicId();
  }

  unsigned short * getSystemId()
  {
    return getLocatorPtr() -> getSystemId();
  }

public:
  void display()
  {
    printf("Column:%d Line:%d [PublicId:%S] [SystemId:%S]\n", 
      getColumnNumber(),
      getLineNumber(),
      getPublicId(),
      getSystemId());
  }
};

}
