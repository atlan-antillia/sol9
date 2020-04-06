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
 *  DataProtection.h
 *
 *****************************************************************************/

// SOL9
// 2009/04/16

#pragma once

#include <sol/Object.h>
#include <wincrypt.h>


namespace SOL {

class DataProtection :public Object{

private:
  CRYPTPROTECT_PROMPTSTRUCT prompter;
/* 2015/12/21
private:
  DataProtection() 
  {
    ZeroMemory(&prompter, sizeof(prompter));
    prompter.cbSize = sizeof(prompter);
  }
*/
public:
  /**
   * Constructor to
   */
  DataProtection(HWND hParent=NULL, const wchar_t* prompt=NULL) {
    ZeroMemory(&prompter, sizeof(prompter));
    prompter.cbSize = sizeof(prompter);
    prompter.dwPromptFlags = CRYPTPROTECT_PROMPT_ON_PROTECT;    
    prompter.szPrompt = prompt;
  }

public:
  
  CRYPTPROTECT_PROMPTSTRUCT* getPrompter() {
     return &prompter;
  }

};

}
