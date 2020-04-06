/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  Animator.h
 *
 *****************************************************************************/

// SOL++2000
// 2000.02.18
// 2012/06/21

#pragma once

#include <sol\Primitive.h>


/**
 * Animator class.
 */

namespace SOL {

class Animator :public Primitive {
public:
  Animator(): Primitive() { }

public:
  Animator(View* parent, const TCHAR* name, Args& args)
  :Primitive()
  {
    create(parent, name, args);
  }

public:
  virtual Boolean create(View* parent, const TCHAR* name, Args& args)
  {
    Boolean rc = Primitive::create(parent, name, 
      args.set(XmNpredefined, TRUE)
          .set(XmNclassName, (LONG_PTR)ANIMATE_CLASS));

    setValues(args);

    return rc;
  }

  Boolean  open(TCHAR* szName) {
      return  (Boolean)send(ACM_OPEN, 0, (LPARAM)(LPTSTR)(szName));
  }

  Boolean  play(int from, int to, int rep) {
      return  (Boolean)send(ACM_PLAY, (WPARAM)(UINT)(rep), (LPARAM)MAKELONG(from, to));
  }

  Boolean  stop() {
      return (Boolean)send(ACM_STOP, 0, 0);
  }

  Boolean   close() {
      return open(NULL);
  }
  Boolean   seek(int frame) {
      return play(frame, frame, 1);
  }
};

}



