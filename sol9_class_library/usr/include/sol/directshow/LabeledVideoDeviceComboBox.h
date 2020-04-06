/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  LabeledVideoDeviceComboBox.h
 *
 *****************************************************************************/

#pragma once

#include <sol/LabeledComboBox.h>
#include <sol/directshow/VideoInputDeviceEnumerator.h>

namespace SOL {

class LabeledVideoDeviceComboBox: public LabeledComboBox {

private:
  VideoInputDeviceEnumerator  deviceEnumrator;

public:
  LabeledVideoDeviceComboBox()
  :LabeledComboBox()
  {
  }
  
public:
  LabeledVideoDeviceComboBox(View* parent, const TCHAR* label, Args& args)
  :LabeledComboBox()
  {
    create(parent, label, args);
  }
  
  Boolean create(View* parent, const TCHAR* label, Args& args)
  {
    LabeledComboBox::create(parent, label, args); 
    listupDevices();
    
    return True;
  }
  
  
public:
  int getDeviceIndex()
  {
    return getCurSel();
  }
  
  bool listupDevices()
  {
    bool rc = false;
    clear();
    try {
      int n = 0;
      LinkedList friendlyNames;
      int count = deviceEnumrator.enumerate(friendlyNames);
      for (int i = 0; i<count; i++) {
        WString* name = (WString*)friendlyNames.getNth(i);
        addString(name);
      }
      rc = true;
    } catch (SOL::Exception& ex) {
      caught(ex);
    }
    return rc;    
  }
};

}

