/******************************************************************************
 *
 * Copyright (c) 2017  Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *      OpenCVScaleComboBox.h
 *
 *****************************************************************************/

#pragma once

#include <sol/LabeledComboBox.h>
#include <sol/StrDef.h>

namespace SOL {

class OpenCVScaleComboBox : public LabeledComboBox {
  
public:
  OpenCVScaleComboBox(View* parent, const char* name, Args& args)
  :LabeledComboBox(parent, name, args)
  {
    static const char* items[] = {
     "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%","100%",
     "110%", "120%", "130%", "140%", "150%", "160%", "170%","180%", "190%", "200%"};

    const char* defaultScale = "80%";
    if (args.has(XmNdefaultScale)) {
      defaultScale = (const char*)args.get(XmNdefaultScale);
    }
    int index = 0;
    for (int i = 0; i<CountOf(items); i++) {
      if (strcmp(items[i], defaultScale) == 0) {
        index = i;
        break;
      }
    }
    
    for (int i = 0; i<CountOf(items); i++) {
      addString(items[i]);
    }
    setCurrentSelection(index);
  }

  int getScale()
  {
    String item = getCurrentSelection();
    int scale = atoi((const char*)item);
    
    return scale;
  }
};
}

