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
 *  D3D12ResourceBarrier.h
 *
 *****************************************************************************/

// 2016/09/25

#pragma once

#include <sol/direct3d12/Direct3D12Object.h>

/*

typedef enum D3D12_RESOURCE_BARRIER_TYPE { 
  D3D12_RESOURCE_BARRIER_TYPE_TRANSITION  = 0,
  D3D12_RESOURCE_BARRIER_TYPE_ALIASING    = ( D3D12_RESOURCE_BARRIER_TYPE_TRANSITION + 1 ),
  D3D12_RESOURCE_BARRIER_TYPE_UAV         = ( D3D12_RESOURCE_BARRIER_TYPE_ALIASING + 1 )
} D3D12_RESOURCE_BARRIER_TYPE;

typedef enum D3D12_RESOURCE_STATES { 
  D3D12_RESOURCE_STATE_COMMON                      = 0,
  D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER  = 0x1,
  D3D12_RESOURCE_STATE_INDEX_BUFFER                = 0x2,
  D3D12_RESOURCE_STATE_RENDER_TARGET               = 0x4,
  D3D12_RESOURCE_STATE_UNORDERED_ACCESS            = 0x8,
  D3D12_RESOURCE_STATE_DEPTH_WRITE                 = 0x10,
  D3D12_RESOURCE_STATE_DEPTH_READ                  = 0x20,
  D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE   = 0x40,
  D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE       = 0x80,
  D3D12_RESOURCE_STATE_STREAM_OUT                  = 0x100,
  D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT           = 0x200,
  D3D12_RESOURCE_STATE_COPY_DEST                   = 0x400,
  D3D12_RESOURCE_STATE_COPY_SOURCE                 = 0x800,
  D3D12_RESOURCE_STATE_RESOLVE_DEST                = 0x1000,
  D3D12_RESOURCE_STATE_RESOLVE_SOURCE              = 0x2000,
  D3D12_RESOURCE_STATE_GENERIC_READ                = ( ( ( ( ( 0x1 | 0x2 ) | 0x40 ) | 0x80 ) | 0x200 ) | 0x800 ),
  D3D12_RESOURCE_STATE_PRESENT                     = 0,
  D3D12_RESOURCE_STATE_PREDICATION                 = 0x200
} D3D12_RESOURCE_STATES;

 */
namespace SOL {

class D3D12ResourceBarrier  {
private:
  D3D12_RESOURCE_BARRIER barrier;
  
/*
typedef struct D3D12_RESOURCE_BARRIER {
  D3D12_RESOURCE_BARRIER_TYPE  Type;
  D3D12_RESOURCE_BARRIER_FLAGS Flags;
  union {
    D3D12_RESOURCE_TRANSITION_BARRIER Transition;
    D3D12_RESOURCE_ALIASING_BARRIER   Aliasing;
    D3D12_RESOURCE_UAV_BARRIER        UAV;
  };
} D3D12_RESOURCE_BARRIER;
  
typedef struct D3D12_RESOURCE_TRANSITION_BARRIER {
  ID3D12Resource        *pResource;
  UINT                  Subresource;
  D3D12_RESOURCE_STATES StateBefore;
  D3D12_RESOURCE_STATES StateAfter;
} D3D12_RESOURCE_TRANSITION_BARRIER;

typedef struct D3D12_RESOURCE_ALIASING_BARRIER {
  ID3D12Resource *pResourceBefore;
  ID3D12Resource *pResourceAfter;
} D3D12_RESOURCE_ALIASING_BARRIER;

  typedef struct D3D12_RESOURCE_UAV_BARRIER {
  ID3D12Resource *pResource;
} D3D12_RESOURCE_UAV_BARRIER;


  */
public:  
  //Simple barrier for rending.
  D3D12ResourceBarrier()
  {

    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource   = nullptr; //resource; //
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  }

public:
  //Simple barrier for rending.
  D3D12ResourceBarrier(__in ID3D12Resource* resource, 
       D3D12_RESOURCE_BARRIER_TYPE type= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION )
  {
    if (resource == nullptr) {
      throw IException("Invalid parameter."); 
    }
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type                   = type; //D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource   = resource; //
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  }

public:
  //ResourceBarrier for subresource acceess.
  D3D12ResourceBarrier(__in ID3D12Resource* resource,
       UINT subresources,   // = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
       D3D12_RESOURCE_BARRIER_TYPE type= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION )
  {
    if (resource == nullptr) {
      throw IException("Invalid parameter."); 
    }
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type                   = type; //D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource   = resource; //
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
    barrier.Transition.Subresource = subresources; //D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,;
  }
  
 
  void setResource(__in ID3D12Resource* resource)
  {
    barrier.Transition.pResource   = resource;
  }
  
  void setType(D3D12_RESOURCE_BARRIER_TYPE type)
  {
    barrier.Type                   = type;
  }
  
  void setFlags(D3D12_RESOURCE_BARRIER_FLAGS flags)
  {
    barrier.Flags = flags;
  }
  
  void setTransitionState(
          D3D12_RESOURCE_STATES before, 
          D3D12_RESOURCE_STATES after)
  {
    barrier.Transition.StateBefore = before; 
    barrier.Transition.StateAfter  = after ;  
  }
    
  void setTransitionSubresource(UINT subresource)
  {
    barrier.Transition.Subresource = subresource;
  }
  
  void setAliasingResourceBefore(ID3D12Resource *resource)
  {
    barrier.Aliasing.pResourceBefore = resource;
  }
  
  void setAliasingResourceAfter(ID3D12Resource *resource)
  {
    barrier.Aliasing.pResourceAfter = resource;
  }

  void setUAVResource(ID3D12Resource *resource)
  {
    barrier.UAV.pResource = resource;
  }
  
  operator D3D12_RESOURCE_BARRIER*()
  {
    return &barrier;
  }

  void startCopyTransition()
  {
    setTransitionState(D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
  }
  
  void endCopyTransition()
  {
    setTransitionState(D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
  }
  
  void startTransition()
  {
    setTransitionState(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
  }

  void startRendering()
  {
    setTransitionState(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
  }

  void endTransition()
  {
    setTransitionState(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
  }

  void endRendering()
  {
    setTransitionState(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
  }

};

}
    
