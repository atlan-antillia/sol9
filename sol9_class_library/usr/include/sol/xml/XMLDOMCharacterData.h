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
 *  XMLDOCharacterData.h
 *
 *****************************************************************************/

// SOL9
// 2011/01/27
#pragma once

#include <sol/xml/XMLDOMNode.h>
//

namespace SOL {

class XMLDOMCharacterData : public XMLDOMNode {
public:
  XMLDOMCharacterData(MSXML2::IXMLDOMCharacterDataPtr pData)
    :XMLDOMNode((MSXML2::IXMLDOMNodePtr)pData)
  {
  }

public:
  MSXML2::IXMLDOMCharacterDataPtr getDataPtr()
  {
    return(MSXML2::IXMLDOMCharacterDataPtr)XMLDOMNode::getNodePtr();
  }

  _bstr_t getData()
  {
    return getDataPtr()-> Getdata();
  }

  void putData(_bstr_t data)
  {
    return getDataPtr()-> Putdata(data);
  }
    
  long getLength()
  {
    return getDataPtr()-> Getlength();
  }
    
  _bstr_t substringData(long offset, long count)
  {
    return getDataPtr()-> substringData(offset, count);;
  }
    
  HRESULT appendData(_bstr_t data)
  {
    return getDataPtr()-> appendData(data);
  }
    
  HRESULT insertData(long offset, _bstr_t data) 
  {
    return getDataPtr()-> insertData(offset, data);
  }
    
  HRESULT deleteData(long offset, long count)
  {
    return getDataPtr()-> deleteData(offset, count);
  }
    
  HRESULT replaceData(long offset, long count, _bstr_t data)
  {
    return getDataPtr()-> replaceData(offset, count, data);
  }
};

}
