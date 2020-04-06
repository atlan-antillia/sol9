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
 *  SWbemDateTime.h
 *
 *****************************************************************************/

// 2012/03/08 Updated

#pragma once

#include <sol/wmi/SWbemBaseObject.h>


namespace SOL {
    
class SWbemDateTime : public SWbemBaseObject {

public:
  SWbemDateTime(IDispatch* pDisp=NULL)
  :SWbemBaseObject(pDisp)
  {

  }

public:
  ISWbemDateTime* get()
  {
    return (ISWbemDateTime*)getIDispatch();
  }

public:
  SWbemDateTime& operator=(ISWbemDateTime* pDisp)
  { 
    set(pDisp);
    return *this;
  }

public:
  //2009/12/21
  _bstr_t getValue()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    BSTR strValue = NULL;
    if (FAILED(hr = dateTime -> get_Value( 
        &strValue)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(strValue, false);
  }        

        
public:
  HRESULT putValue( 
            __in _bstr_t strValue)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_Value( 
      (BSTR)strValue)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        
public:
  //2009/12/21
  long getYear()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iYear = 0;

    if (FAILED(hr = dateTime -> get_Year( 
      &iYear)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iYear;
  }        

        
public:
  HRESULT putYear( 
            __in long iYear)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_Year( 
      iYear)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  //2009/12/21
  bool isYearSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    VARIANT_BOOL bYearSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_YearSpecified( 
      bYearSpecified)) ) {

        throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    return toBool(bYearSpecified);
  }        


public:
  HRESULT putYearSpecified( 
            __in bool bYearSpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_YearSpecified( 
      toVariantBool(bYearSpecified) ))) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        
public:
  long getMonth()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iMonth = 0;

    if (FAILED(hr = dateTime -> get_Month( 
      &iMonth)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iMonth;
  }        

        
public:
  HRESULT putMonth( 
            __in long iMonth)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_Month( 
      iMonth)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  bool isMonthSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    VARIANT_BOOL bMonthSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_MonthSpecified( 
      &bMonthSpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bMonthSpecified);
  }        



public:
  HRESULT putMonthSpecified( 
            __in bool bMonthSpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_MonthSpecified( 
      toVariantBool(bMonthSpecified) )) ) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  long getDay()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iDay = 0;

    if (FAILED(hr = dateTime -> get_Day( 
        &iDay)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return lDay;
  }        

        
public:
  HRESULT putDay( 
            __in long iDay)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_Day( 
      iDay)) ) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  bool isDaySpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    VARIANT_BOOL bDaySpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_DaySpecified( 
      &bDaySpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }

    return toBool(bDaySpecified);
  }        


        
public:
  HRESULT putDaySpecified( 
            __in bool bDaySpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_DaySpecified( 
      toVariantBool(bDaySpecified) )) ){
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  long getHours()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iHours = 0;

    if (FAILED(hr = dateTime -> get_Hours( 
      &iHours)) ) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        
        
public:
  HRESULT putHours( 
            __in long iHours)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    hr = dateTime ->  put_Hours( 
      iHours);

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  bool isHoursSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    VARIANT_BOOL bHoursSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_HoursSpecified( 
      &bHoursSpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bHoursSpecified);
  }        


    
public:
  HRESULT putHoursSpecified( 
            __in bool bHoursSpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    hr = dateTime -> put_HoursSpecified(
        toVariantBool(bHoursSpecified));

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

public:
  long getMinutes()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iMinutes = 0;

    if (FAILED(hr = dateTime -> get_Minutes( 
      &iMinutes)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iMinutes;
  }        
        
public:
  HRESULT putMinutes( 
            __in long iMinutes)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    hr = dateTime ->put_Minutes( 
        iMinutes); 

    if (FAILED(hr)) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

public:
  bool isMinutesSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    VARIANT_BOOL bMinutesSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_MinutesSpecified( 
      &bMinutesSpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bMinutesSpecified);
  }        
        
    
public:
  HRESULT putMinutesSpecified( 
            __in bool bMinutesSpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_MinutesSpecified( 
      toVariantBool(bMinutesSpecified) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        
public:
  long getSeconds( 
            )
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iSeconds = 0;

    if (FAILED(hr = dateTime -> get_Seconds( 
      &iSeconds)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iSeconds;
  }        


        
public:
  HRESULT putSeconds( 
            __in long iSeconds)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_Seconds( 
      iSeconds)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        
public:
  bool isSecondsSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    VARIANT_BOOL bSecondsSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_SecondsSpecified( 
      &bSecondsSpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bSecondsSpecified);
  }        

        
public:
  HRESULT putSecondsSpecified( 
            __in bool bSecondsSpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_SecondsSpecified( 
      toVariantBool(bSecondsSpecified) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  long getMicroseconds()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iMicroseconds = 0;

    if (FAILED(hr = dateTime -> get_Microseconds( 
      &iMicroseconds)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iMicroseconds;
  }        
        
        
public:
  HRESULT putMicroseconds( 
            __in long iMicroseconds)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_Microseconds( 
      iMicroseconds)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  bool isMicrosecondsSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    VARIANT_BOOL bMicrosecondsSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_MicrosecondsSpecified( 
      &bMicrosecondsSpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bMicrosecondsSpecified);
  }        
        

public:
  HRESULT putMicrosecondsSpecified( 
            __in bool bMicrosecondsSpecified)       
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_MicrosecondsSpecified( 
      toVariantBool(bMicrosecondsSpecified) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        
        

public:
  long getUTC()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    long iUTC = 0;

    if (FAILED(hr = dateTime -> get_UTC( 
      &iUTC)) ) {
      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return iUTC;
  }        


public:
  HRESULT putUTC( 
            __in long iUTC)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_UTC( 
      iUTC)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        
public:
  bool isUTCSpecified()
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();
    VARIANT_BOOL bUTCSpecified = VARIANT_FALSE;

    if (FAILED(hr = dateTime -> get_UTCSpecified( 
      &bUTCSpecified)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(bUTCSpecified);
  }        
        

public:
  HRESULT putUTCSpecified( 
            __in bool bUTCSpecified)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_UTCSpecified( 
      toVariantBool(bUTCSpecified) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        


public:
  bool isInterval()
  {
    VARIANT_BOOL vbool;
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> get_IsInterval( 
      &vbool)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return toBool(vbool);
  }        


public:
  HRESULT getIsInterval( 
            __out VARIANT_BOOL *bIsInterval)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> get_IsInterval( 
      bIsInterval)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        
public:
  HRESULT putIsInterval( 
            __in bool bIsInterval)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> put_IsInterval( 
      toVariantBool(bIsInterval) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }

        

public:
  HRESULT getVarDate( 
           __in bool bIsLocal,
            __out DATE *dVarDate)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> GetVarDate( 
          toVariantBool(bIsLocal),
          dVarDate)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        

public:
  HRESULT setVarDate( 
            __in DATE dVarDate,
           __in bool bIsLocal = TRUE)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> SetVarDate( 
        dVarDate,
        toVariantBool(bIsLocal) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

        

public:
  _bstr_t getFileTime( 
           __in bool bIsLocal)
  {
    BSTR bstr = NULL;
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> GetFileTime( 
        toVariantBool(bIsLocal),
        &bstr)) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return _bstr_t(bstr, false);
  }        

        
public:
  HRESULT setFileTime( 
            __in _bstr_t strFileTime,
           __in bool bIsLocal = true)
  {
    HRESULT hr = E_FAIL;
    ISWbemDateTime* dateTime = get();

    if (FAILED(hr = dateTime -> SetFileTime( 
        (BSTR)strFileTime,
        toVariantBool(bIsLocal) )) ) {

      throw Exception(E_FAIL, "%s: %s", "E_FAIL",__FUNCTION__);
    }
    return hr;
  }        

};

}
    
