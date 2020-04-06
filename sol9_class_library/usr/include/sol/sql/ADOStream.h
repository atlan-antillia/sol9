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
 *  ADOStream.h
 *
 *****************************************************************************/

// SOL9
// 2009/05/11

#pragma once

#include <sol/sql/ADOObject.h>



namespace SOL {

class ADOStream :public ADOObject {

public:
  /**
   *
   */
  ADOStream()
  {
   }

public:
  ~ADOStream() 
  {
    close();
  }

public:
  HRESULT createInstance()
  {
    return ADOObject::createInstance(__uuidof(ADODB::Stream));
  }

public:
  /**
   *
   */
  void set(__in ADODB::_StreamPtr pStream)
  {
    close();
    setObject((IDispatchPtr)pStream);
  }

public:
  /**
   *
   */
  ADODB::_StreamPtr getStreamPtr()
  {
    return (ADODB::_StreamPtr)getObject();
  }

 
public:
  ADODB::ADO_LONGPTR getSize()
  {
    return getStreamPtr()->GetSize();
  }

public:
  VARIANT_BOOL getEOS()
  {
    return getStreamPtr()->GetEOS();
  }
    
public:
  ADODB::ADO_LONGPTR getPosition()
  {
    return getStreamPtr()->GetPosition();
  }
    
public:
  void putPosition(__in long pPos) //ADODB::ADO_LONGPTR pPos)
  {
    getStreamPtr()->PutPosition(pPos);
  }
    
public:
  /**
  StreamTypeEnum
  {
    adTypeBinary = 1,
    adTypeText = 2
  };
   */
  ADODB::StreamTypeEnum getType()
  {
    return getStreamPtr()->GetType();
  }
    
public:
  void putType(__in ADODB::StreamTypeEnum ptype)
  {
    getStreamPtr()->PutType(ptype);
  }
    
public:
  /**
  LineSeparatorEnum
  {
    adLF = 10,
    adCR = 13,
    adCRLF = -1
  };
   */
  ADODB::LineSeparatorEnum getLineSeparator()
  {
    return getStreamPtr()->GetLineSeparator();
  }
    
public:
  void putLineSeparator(__in ADODB::LineSeparatorEnum pLS)
  {
    getStreamPtr()->PutLineSeparator(pLS);
  }
    
public:
  ADODB::ObjectStateEnum getState()
  {
    return getStreamPtr()->GetState();
  }
    
public:
  ADODB::ConnectModeEnum getMode()
  {
    return getStreamPtr()->GetMode();
  }
    
public:
  void putMode(__in ADODB::ConnectModeEnum pMode)
  {
    getStreamPtr()->PutMode(pMode);
  }
    
public:
  _bstr_t getCharset()
  {
    return getStreamPtr()->GetCharset();
  }
    
public:
  void putCharset(__in _bstr_t pbstrCharset)
  {
    getStreamPtr()->PutCharset(pbstrCharset);
  }
    
public:
  _variant_t read(__in long numBytes)
  {
    return getStreamPtr()->Read(numBytes);
  }
    
public:
  /**
   @param source Data source 
   @param  mode  Specify one of values of the following enum
  ConnectModeEnum
  {
    adModeUnknown = 0,
    adModeRead = 1,
    adModeWrite = 2,
    adModeReadWrite = 3,
    adModeShareDenyRead = 4,
    adModeShareDenyWrite = 8,
    adModeShareExclusive = 12,
    adModeShareDenyNone = 16,
    adModeRecursive = 4194304
  };
 
   @optins  Specify one of values of the following enum.
  StreamOpenOptionsEnum
  {
    adOpenStreamUnspecified = -1,
    adOpenStreamAsync = 1,
    adOpenStreamFromRecord = 4
  };

   */
  HRESULT open(
    const _variant_t& source,
    ADODB::ConnectModeEnum mode,
    ADODB::StreamOpenOptionsEnum options,
    _bstr_t userName,
    _bstr_t password)
  {
    HRESULT hr = getStreamPtr()->Open(
      source,
      mode,
      options,
      userName,
      password);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  /**
   * This opens a stream for source of vtMissing. adModeUnknow, adOpenStreamUnspecified, 
   * empty uid and empty pwd.
   * This may be called in prior to call loadFromFile or saveToFile methods.
   */
  HRESULT open()
  {
    HRESULT hr = open(vtMissing,
                        ADODB::adModeUnknown,
                         ADODB::adOpenStreamUnspecified,
                         "",
                         "");
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  void close()
  {
    try {
      getStreamPtr()->Close();
    } catch (...) {

    }
    clear();

  }
    
public:
  HRESULT skipLine()
  {
    HRESULT hr = getStreamPtr()->SkipLine();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT write(const _variant_t& buffer)
  {
    HRESULT hr = getStreamPtr()->Write(buffer);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }
    
public:
  HRESULT setEOS()
  {
    HRESULT hr = getStreamPtr()->SetEOS();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }
    
public:
  HRESULT copyTo(
    ADODB::_Stream* destStream,
    long charNumber) //ADODB::ADO_LONGPTR charNumber)
  {
    HRESULT hr = getStreamPtr()->CopyTo(
      destStream,
      charNumber);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }
  

public:
  HRESULT flush()
  {
    HRESULT hr = getStreamPtr()->Flush();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }
    
public:
  /**
  SaveOptionsEnum
  {
    adSaveCreateNotExist = 1,
    adSaveCreateOverWrite = 2
  };
   */
  HRESULT saveToFile(_bstr_t fileName,
    ADODB::SaveOptionsEnum options)
  {
    HRESULT hr = getStreamPtr()->SaveToFile(fileName,
        options);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }

public:
  HRESULT loadFromFile(_bstr_t fileName)
  {
    HRESULT hr = getStreamPtr()->LoadFromFile(fileName);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }
    
public:
  _bstr_t readText(long numChars)
  {
    return getStreamPtr()->ReadText(numChars);
  }
    
public:
  /**
  StreamWriteEnum
  {
    adWriteChar = 0,
    adWriteLine = 1,
    stWriteChar = 0,
    stWriteLine = 1
  };
   */
  HRESULT writeText(_bstr_t data,
    ADODB::StreamWriteEnum options)
  {
    HRESULT hr = getStreamPtr()->WriteText(data,
      options);
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;
  }
    
public:
  HRESULT cancel()
  {
    HRESULT hr = getStreamPtr()->Cancel();
    if (FAILED(hr)) {
      throw Exception(hr, "%s", __FUNCTION__);
    }
    return hr;  
  }

};

}
