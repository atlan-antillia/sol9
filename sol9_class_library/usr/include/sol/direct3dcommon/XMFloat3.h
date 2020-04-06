/******************************************************************************
 *
 * Copyright (c) 2016 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  XMFloat3.h
 *
 *****************************************************************************/


//2016/03/10 Updated.

#pragma once

#include <xnamath.h>

namespace SOL {

#define DIM_THREE (3)
  
class XMFloat3 {
private:
  float value[DIM_THREE];

public:
  XMFloat3(float x=0.0f, float y=0.0f, float z=0.0f)
  {
    const float v[] = {x, y, z};
    
    for (int i = 0; i<DIM_THREE; i++) {
     value[i] = v[i];
    }
  }

public:
  XMFloat3(const XMFloat3& float3)
  {
	  const float* v = float3.value;
    for (int i = 0; i<DIM_THREE; i++) {
     value[i] = v[i];
    }
  }
  
  
  const float* getValue()
  {
    return value;
  }
  
  operator const float*()
  {
    return (float*)value;

  }

};

}

