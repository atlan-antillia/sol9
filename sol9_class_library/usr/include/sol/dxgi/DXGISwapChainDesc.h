/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DXGISwapChainDesc.h
 *
 *****************************************************************************/
 
#pragma once

#include <sol/Args.h>
#include <sol/Exception.h>
#include <dxgi.h>
//#include <d3dx10.h>

namespace SOL {

class DXGISwapChainDesc {
private:
  static const int WIDTH = 640;
  static const int HEIGHT = 480;
	
  DXGI_SWAP_CHAIN_DESC swapChainDesc;

  void setDefault(HWND hwnd, UINT width, UINT height)
  {
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount      = 1;
    swapChainDesc.BufferDesc.Width  = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format  = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator  = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow                       = hwnd;
    swapChainDesc.SampleDesc.Count                   = 1;
    swapChainDesc.SampleDesc.Quality                 = 0;
    swapChainDesc.Windowed                           = TRUE;
  }

public:
  DXGISwapChainDesc(HWND hwnd, UINT width, UINT height)
  {
  	setDefault(hwnd, width, height);
  }

	/*
  Args args;
  args.set(XmNbufferCount), 1);
  args.set(XmNwidth,   640);
  args.set(XmNheight,  480);
  args.set(XmNformat, DXGI_FORMAT_R8G8B8A8_UNORM);
  args.set(XmNnumerator, 60);
  args.set(XmNdenominator, 1);
  args.set(XmNsampleDescCount, 1);
  args.set(XmNsampleDescQuality, 0);
  args.set(XmNwindowed, TRUE)
  DirectXGISwapChainDesc swapChainDesc(hwnd, args);
  DXGI_SWAP_CHAIN_DESC* desc = (DXGI_SWAP_CHAIN_DESC*)swapChainDesc;

  */
public:
  DXGISwapChainDesc(HWND hwnd, Args& args)
  {
  	setDefault(hwnd, WIDTH, HEIGHT);
  	if (args.has(XmNbufferCount)) {
  		swapChainDesc.BufferCount  = (UINT)args.get(XmNbufferCount);
  	}
  	
  	if (args.has(XmNwidth)) {
  		swapChainDesc.BufferDesc.Width  = (UINT)args.get(XmNwidth);
  	}
  	if (args.has(XmNheight)) {
  		swapChainDesc.BufferDesc.Height  = (UINT)args.get(XmNheight);
  	}
  	if (args.has(XmNformat)) {
  		swapChainDesc.BufferDesc.Format  = (DXGI_FORMAT)args.get(XmNformat);
  	}
  	if (args.has(XmNrefreshRateNumerator)) {
  		swapChainDesc.BufferDesc.RefreshRate.Numerator  = (UINT)args.get(XmNrefreshRateNumerator);
  	}
  	
  	if (args.has(XmNrefreshRateDenominator)) {
  		swapChainDesc.BufferDesc.RefreshRate.Denominator  = (UINT)args.get(XmNrefreshRateDenominator);
  	}
  	if (args.has(XmNbufferUsage)) {
  		swapChainDesc.BufferUsage  = (UINT)args.get(XmNbufferUsage);
  	}
  	if (args.has(XmNsampleDescCount)) {
  		swapChainDesc.SampleDesc.Count = (UINT)args.get(XmNsampleDescCount);
  	}
  	if (args.has(XmNsampleDescQuality)) {
  		swapChainDesc.SampleDesc.Quality = (UINT)args.get(XmNsampleDescQuality);
  	}
  	if (args.has(XmNwindowed)) {
  		swapChainDesc.Windowed = (BOOL)args.get(XmNwindowed);
  	}
  	
  }

  operator DXGI_SWAP_CHAIN_DESC*() 
  { 
    return &swapChainDesc;
  }
};

}
