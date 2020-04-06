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
 *  SAXXMLWriter.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/03
// 2011/02/15 Update constructor to try a few versions of GUID of IMXWriter interface 
// 2015/12/19 Modified SAXWriter constructor.

#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/xml/SAXXMLAttributes.h>
#pragma comment(lib, "shlwapi.lib")

//SAXXMLWriter writes an XML document to a file.
//SAXXMLWriter is a C++ wrapper class to IMXWriter interface which 
//implements 
// ISAXContentHandler,
// ISAXDTDHandler,
// ISAXErrorHandler,
// ISAXDeclHandler, 
// and ISAXLexicalHandler interfaces. 

namespace SOL {

//This is a base class to SAXXMLWriter and SAXHTMLWriter

class SAXWriter :public XMLObject {

private:
  MSXML2::IMXWriterPtr pWriter;

private:
  MSXML2::ISAXContentHandlerPtr pHandler;

private:
  IStream* pStream;

public:
  /**
   * Constructor
   */
  SAXWriter(const GUID clsId) 
    :pWriter(NULL),
    pHandler(NULL),
    pStream(NULL) 
  {
    //2015/12/19 Updated
   
    HRESULT hr = pWriter.CreateInstance(clsId); 
    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    pHandler = pWriter;
    pWriter->Putindent(VARIANT_TRUE);
  }


public:
  /**
   * Destructor
   */
  ~SAXWriter()
  {
    close();
    pWriter = NULL;
    pHandler = NULL;
  }


  //Accessor methods to member variables.
protected:
  MSXML2::IMXWriterPtr getWriterPtr()
  {
    if (pWriter == NULL ) {
      throw Exception(E_FATAL, "Error: SAXWriter::IMXWriterPtr is NULL");
    }
    return pWriter;
  }

protected:
  MSXML2::ISAXContentHandlerPtr getHandlerPtr()
  {
    if (pHandler == NULL ) {
      throw Exception(E_FATAL, "Error: SAXWriter::ISAXContentHandlerPtr is NULL");
    }

    return pHandler;
  }

protected:
  IStream* getStreamPtr()
  {
    if (pStream == NULL) {
      throw Exception(E_FATAL, "Error: SAXWriter::pStream is NULL");
    }
    return pStream;
  }

protected:
  void setStreamPtr(IStream* stream)
  {
    if (pStream != NULL) {
      pStream ->Release();
    }
    pStream = stream;
  }

  //<IXMLWriterMethods>
public:
  void flush()
  {
    getWriterPtr()->flush();
  }
  void putOutput(const _variant_t & varDestination)
  {
    getWriterPtr()->Putoutput(varDestination);
  }

  _variant_t getOutput()
  {
    return getWriterPtr()->Getoutput();
  }

  void putEncoding(_bstr_t strEncoding)
  {
    return getWriterPtr()->Putencoding(strEncoding);
  }

  _bstr_t getEncoding()
  {
    return getWriterPtr()->Getencoding();
  }

  void putByteOrderMark(VARIANT_BOOL fWriteByteOrderMark)
  {
    getWriterPtr()->PutbyteOrderMark(fWriteByteOrderMark);
  }

  VARIANT_BOOL getByteOrderMark()
  {
    return getWriterPtr()->GetbyteOrderMark();
  }

  void putIndent(VARIANT_BOOL fIndentMode)
  {
    return getWriterPtr()->Putindent(fIndentMode);
  }

  VARIANT_BOOL getIndent()
  {
    return getWriterPtr()->Getindent();
  }

  void putStandalone(VARIANT_BOOL fValue)
  {
    getWriterPtr()->Putstandalone(fValue);
  }

  VARIANT_BOOL getStandalone()
  {
    return getWriterPtr()->Getstandalone();
  }

  void putOmitXMLDeclaration(VARIANT_BOOL fValue)
  {
    getWriterPtr()->PutomitXMLDeclaration(fValue);
  }

  VARIANT_BOOL getOmitXMLDeclaration()
  {
    return getWriterPtr()->GetomitXMLDeclaration();
  }

  void putVersion(_bstr_t strVersion)
  {
    getWriterPtr()->Putversion(strVersion);
  }

  _bstr_t getVersion()
  {
    return getWriterPtr()->Getversion();
  }

  void putDisableOutputEscaping(VARIANT_BOOL fValue)
  {
    getWriterPtr()->PutdisableOutputEscaping(fValue);
  }

  VARIANT_BOOL getDisableOutputEscaping()
  {
    return getWriterPtr()->GetdisableOutputEscaping();
  }
  //</IXMLWriterMethods>

public:
  unsigned short* toShort(wchar_t* string)
  {
    return(unsigned short*)(void*)string;
  }

public:
  unsigned short* toShort(const _bstr_t string)
  {
    const wchar_t* wstring =(const wchar_t*)string;
    return(unsigned short*)(void*)wstring;
  }

public:
  //Create a file stream.
  virtual bool create(const TCHAR* fileName)
  {
    bool rc = false;
    HRESULT hr = SHCreateStreamOnFile(fileName,
        STGM_WRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
        &pStream); 
    if(SUCCEEDED(hr)) {
      //OK. Set the pStream to the output of IMXWriter object 
      getWriterPtr()->Putoutput(_variant_t((IUnknown*)pStream));
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return rc;
  }

public:
  //Create a memory stream on a global memory specified by HGLOBAL handle.
  virtual bool create(DWORD size = 64000)
  {
    bool rc = false;
    DWORD dwSize = size;
    if (dwSize<1024) {
      dwSize = 1024;
    }
     HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwSize);

    HRESULT hr = CreateStreamOnHGlobal(hGlobal, FALSE, &pStream);
    if(SUCCEEDED(hr)) {
      //OK. Set the pStream to the output property of IMXWriter object 
      getWriterPtr()->Putoutput(_variant_t((IUnknown*)pStream));
      rc = true;
    } else {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return rc;
  }

public:
  bool getXML(__out _bstr_t& xml)
  {
    bool rc = false;
    IStream* stream = getStreamPtr();
    if (stream) {
      HGLOBAL hGlobal = NULL;
      HRESULT hr= GetHGlobalFromStream(stream, &hGlobal);
      if (SUCCEEDED(hr)) {
        unsigned char* data = (unsigned char*)GlobalLock(hGlobal);
        //Check UTF-16 BOM mark
        if ((*data == 0xff && *(data+1) == 0xfe) ||
          (*data == 0xfe && *(data+1) == 0xff) ) {
          xml = (wchar_t*)data;
        } else {
          xml = (char*)data;
        }
        GlobalUnlock(hGlobal);
        rc = true;
      }
    }
    return rc;
  }

public:
  virtual void close()
  {
    if(pStream) {
      HGLOBAL hGlobal = NULL;
      HRESULT hr= GetHGlobalFromStream(pStream, &hGlobal);
      pStream->Release();
      pStream = NULL;
      if (SUCCEEDED(hr)) {
        //printf("GlobalFree\n");
        GlobalFree(hGlobal);
      }
    }
  }

  //<ISAXContentHanlderMethods>
public:
  virtual void startDocument()
  {
    getHandlerPtr()->startDocument();
  }

  virtual void endDocument()
  {
    getHandlerPtr()->endDocument();
  }

  virtual void startElement(__in const _bstr_t qName, ISAXAttributes* attributes=NULL)
  {
    const wchar_t* null = L"";
    getHandlerPtr()->startElement(toShort(null), 0,
        toShort(null), 0, 
        toShort(qName), qName.length(), 
        attributes);
  }

  virtual void endElement(__in const _bstr_t qName)
  {
    const wchar_t* null = L"";
    getHandlerPtr()->endElement(toShort(null), 0,
        toShort(null), 0, 
        toShort(qName), qName.length()); 
  }

  virtual void startElement(__in const _bstr_t uri, __in const _bstr_t localName, 
    __in const _bstr_t qName, 
    ISAXAttributes* attributes=NULL)
  {
    getHandlerPtr()->startElement(toShort(uri), uri.length(), 
        toShort(localName), localName.length(), 
        toShort(qName), qName.length(), 
        attributes);
  }

  virtual void endElement(__in const _bstr_t uri, __in const _bstr_t localName, 
    __in const _bstr_t qName)
  {
    getHandlerPtr()->endElement(toShort(uri), uri.length(), 
        toShort(localName), localName.length(), 
        toShort(qName), qName.length()) ;
  }

  virtual void characters(__in const _bstr_t text)
  {
    getHandlerPtr()->characters(toShort(text), text.length());    
  }

  virtual void startPrefixMapping(__in const _bstr_t prefix, __in const _bstr_t uri)
  {
    getHandlerPtr()->startPrefixMapping(toShort(prefix), prefix.length(),
      toShort(uri), uri.length());
  }

  virtual void endPrefixMapping(__in const _bstr_t prefix)
  {
    getHandlerPtr()->endPrefixMapping(toShort(prefix), prefix.length());
  }
  virtual void ignorableWhitespace(__in const _bstr_t  chars)
  {
    getHandlerPtr()->ignorableWhitespace(toShort(chars), chars.length());
  }

  virtual void processingInstruction(
    __in const _bstr_t target,
    __in const _bstr_t data)
  {
    getHandlerPtr()->processingInstruction(toShort(target), target.length(),
      toShort(data), data.length());
  }

  virtual void skippedEntity(__in const _bstr_t&  name)
  {
    getHandlerPtr()->skippedEntity(toShort(name), name.length());
  }
  //</ISAXContentHanlderMethods>

};

}
