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
 *  SAXErrorHandlerImpl.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLObject.h>

#include <sol/xml/SAXLocator.h>

//Implementation class ISAXErrorHandler COM interface.
//But, this is used to be a C++ class not COM object.
//Therefore we create an instance of this class by ordinary C++ constructor,
// not using ::CoCreateInstance API.

class SAXErrorHandlerImpl :public ISAXErrorHandler
{

public:
  SAXErrorHandlerImpl()
  {
  }

private:
  long __stdcall QueryInterface(const struct _GUID &,void **)   
  { 
    return 0;
  }

  unsigned long __stdcall AddRef(void) 
  { 
    return 0;
  }

  unsigned long __stdcall Release(void) 
  { 
    return 0;
  }

private:
  void display(const char* type, 
    ISAXLocator * locator, 
    unsigned short* message, 
    HRESULT error)
  {
    printf("%s \n", type);

    SAXLocator saxLocator(locator);
    saxLocator.display();
    printf("Message  :%S\n",  message);
    printf("ErrorCode:0x%x\n", error);

  }

private:
  virtual HRESULT __stdcall raw_error(
    __in ISAXLocator * pLocator,
    __in unsigned short * pwchErrorMessage,
    __in HRESULT hrErrorCode) 
  {
    display("Error", pLocator, pwchErrorMessage, hrErrorCode);
    return S_OK;
  } 

  virtual HRESULT __stdcall raw_fatalError(
    __in ISAXLocator * pLocator,
    __in unsigned short * pwchErrorMessage,
    __in HRESULT hrErrorCode)
  {
    display("Fatal", pLocator, pwchErrorMessage,hrErrorCode);
    return S_OK;
  }
    
  virtual HRESULT __stdcall raw_ignorableWarning(
    __in ISAXLocator * pLocator,
    __in unsigned short * pwchErrorMessage,
    __in HRESULT hrErrorCode)
  {
    display("Warning", pLocator, pwchErrorMessage,hrErrorCode);
    return S_OK;
  }

};

