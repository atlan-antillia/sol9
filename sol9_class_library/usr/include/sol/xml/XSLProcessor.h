/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  XSLProcessor.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/23 Base class for XMLSomthing classes

#pragma once
#include <sol/xml/XMLObject.h>

namespace SOL {

class XSLProcessor : public XMLObject
{
private:
  MSXML2::IXSLProcessorPtr pProcessor;

public:
  XSLProcessor(MSXML2::IXSLProcessorPtr processor)
    :pProcessor(processor)
  {
  }

public:
  ~XSLProcessor()
  {
    pProcessor = NULL;
  }

public:
  MSXML2::IXSLProcessorPtr getProcessorPtr()
  {
    return pProcessor;
  }

public:
  void putInput (const _variant_t & pVar )
  {
    getProcessorPtr()->Putinput (pVar );
  }

  _variant_t getInput ( )
  {
    return getProcessorPtr()->Getinput ();
  }

  IXSLTemplatePtr getOwnerTemplate ( )
  {
    return getProcessorPtr()->GetownerTemplate ();
  }

  HRESULT setStartMode (_bstr_t mode, _bstr_t namespaceURI )
  {
    return getProcessorPtr()->setStartMode (mode, namespaceURI );
  }

  _bstr_t getStartMode ( )
  {
    return getProcessorPtr()->GetstartMode ();
  }

  _bstr_t getStartModeURI ( )
  {
    return getProcessorPtr()->GetstartModeURI ( );
  }

  void putOutput (const _variant_t & pOutput )
  {
    getProcessorPtr()->Putoutput (pOutput );
  }
 
  _variant_t getOutput ( )
  {
    return getProcessorPtr()->Getoutput ( );
  }

  VARIANT_BOOL transform ( )
  {
    return getProcessorPtr()->transform ( );
  }

  HRESULT reset ( )
  {
    return getProcessorPtr()->reset ( );
  }
  
  long getReadyState ( )
  {
    return getProcessorPtr()->GetreadyState ( );
  }

  HRESULT addParameter (_bstr_t baseName, const _variant_t & parameter, _bstr_t namespaceURI )
  {
    return getProcessorPtr()->addParameter (baseName, parameter, namespaceURI );
  }

  HRESULT addObject (IDispatch * obj, _bstr_t namespaceURI )
  {
    return getProcessorPtr()->addObject (obj, namespaceURI );
  }

  MSXML2::IXMLDOMNodePtr getStylesheet ( )
  {
    return getProcessorPtr()->Getstylesheet ();
  }

};


}
