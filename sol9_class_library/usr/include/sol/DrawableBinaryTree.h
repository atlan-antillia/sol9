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
 *  DrawableBinaryTree.h
 *
 *****************************************************************************/

// SOL++2000
// 2009/10/10
#pragma once

#include <sol\BinaryTree.h>
#include <sol\DrawableBinaryNode.h>
#include <sol\Font.h>
#include <sol\Pen.h>
#include <sol\FileStream.h>
#include <sol\StringTokenizerT.h>
#include <sol\StringConverter.h>


namespace SOL {

class DrawableBinaryTree :public BinaryTree {
private:
  int   arranged;
  int   leftMargin;
  int   topMargin;
  int   horizSpacing;
  int    vertSpacing;
  int    arrangementPolicy;
  int    connectionPolicy;  
  int    width;
  int    height;

  DrawableBinaryNode* activeNode;  
  Font*  font;
  Pen*  pen;

public:
  static const int CONSTANT = 0;
  static const int VARIABLE = 1;

public:
  DrawableBinaryTree()
  {
    arranged    = FALSE;
    leftMargin  = 20;
    topMargin   = 20;

    horizSpacing = 20;
    vertSpacing  = 15;
    arrangementPolicy = VARIABLE;
    connectionPolicy  = DrawableBinaryNode::LINEAR;

    activeNode = NULL;
    width       = 0;
    height      = 0;
    font    = NULL;
    pen      = NULL; //new Pen(PS_SOLID, 1, RGB(128,128,128));  //gray
  }

public:
  ~DrawableBinaryTree()
  {
  }

public:
  void draw(DC* dc, int x, int y)
  {
    DrawableBinaryNode* root = (DrawableBinaryNode*) getRoot();
    if(root) {
  
      HGDIOBJ hfont = NULL;
      if(font) {
        hfont = dc-> select(font);
      }
      HPEN hpen = NULL;
      if(pen) {
        hpen =(HPEN) dc->select(pen);
      }

      if(arranged == FALSE) {
        TCHAR* name = root -> getName();
        SIZE size;

        dc -> getTextExtent(name, strlen(name), &size);
        int height  = size.cy;
        if(arrangementPolicy == VARIABLE) {
          root -> arrange(dc, horizSpacing, 
            height + vertSpacing,
            leftMargin, topMargin);
        }
        else {
          int maxLen = root -> nodeMaxLength(dc, 0);
          root -> arrange(maxLen+ horizSpacing,
            height + vertSpacing,
            leftMargin, topMargin);
        }
        arranged = TRUE;
      }
      root -> draw(dc, root, connectionPolicy, x, y);

      if(pen) {
        dc->select(hpen);
      }
      if(font) {
        dc -> select(hfont);
      }
    }
  }

public:

  DrawableBinaryNode* search(DC* dc, int x, int y)
  {
    DrawableBinaryNode* root = (DrawableBinaryNode*) getRoot();
    if(root) {
      HGDIOBJ hfont = NULL;
      if(font) {
        hfont = dc-> select(font);
      }
      DrawableBinaryNode* node = root->search(dc, x, y);
      if(font) {
        dc -> select(hfont);
      }
      return node;
    }
    else {
      return NULL;
    }
  }

public:

  int load(const TCHAR* fileName)
  {
    int status = 0;
    char buffer[MAX_PATH];
    char parent[MAX_PATH];
    char word[MAX_PATH];

    FileStream stream;
    if(stream.openReadOnly(fileName) < 0) {
      return FALSE;
    }

    DrawableBinaryNode* node;
    DrawableBinaryNode* root;

    StringTokenizerT<char> analyzer;
          
    StringConverter converter;
          
    StringT<TCHAR> parentNode;

    while(stream.getLine(buffer, sizeof(buffer)-1) != FALSE) {
      if(strcmp(buffer, "") == 0) continue;

      analyzer.getToken(buffer, word, sizeof(word)-1);
      if(strcmp(word, "") == 0) continue;
      if(strcmp(word, "{") == 0) {
        status = 1;
        continue;
      }
      if(strcmp(word, "}") == 0) {
        status = 0;
        continue;
      }
      if(strcmp(word, "") !=0 && status == 0) {
        strcpy_s(parent, sizeof(parent), word);
          
        converter.convert(parent, parentNode);

        if(getRoot() == NULL) {
          setRoot(new DrawableBinaryNode(NULL, (const TCHAR*)parentNode));
        }
        continue;
      }
      if(strcmp(word, "") != 0 && status == 1) {
        root = (DrawableBinaryNode*) getRoot();
        if (root) {
          StringT<TCHAR> leafNode;
          converter.convert(word, leafNode);
          node = root -> search((const TCHAR*)parentNode);
          if (node) {
            if (node ->getLeft() == NULL) {
              node -> setLeft(new DrawableBinaryNode(node, (const TCHAR*)leafNode));
              continue;
            }
            if (node ->getRight() == NULL) {
              node -> setRight(new DrawableBinaryNode(node, (const TCHAR*)leafNode));
              continue;
            }
          }
        }
        continue;
      }
    }
    stream.close();

    root = (DrawableBinaryNode*) getRoot();
    root -> configure(0, 0);
    root -> reconfigure();
    return TRUE;
  }

public:

  void setActiveNode(DrawableBinaryNode* node, DC* dc, int x, int y)
  {
    HGDIOBJ hfont = NULL;
    if(font) {
      hfont = dc->select(font);
    }
    SIZE size;
    if(activeNode && node) {
      activeNode->setStatus(FALSE);
      activeNode->drawSelf(dc, -x, -y, &size);
    }
    activeNode = node;
    if(activeNode) {
      activeNode->setStatus(TRUE);
      activeNode->drawSelf(dc, -x, -y, &size);
    }

    if(font) {
      dc -> select(hfont);
    }
  }

public:
  void setBackground(COLORREF normal, COLORREF active)
  {
    DrawableBinaryNode* root = (DrawableBinaryNode*)getRoot();
    if(root) {
      root -> setBackground(normal, active);
    }
  }

public:
  void setTextColor(COLORREF normal, COLORREF active)
  {
    DrawableBinaryNode* root = (DrawableBinaryNode*)getRoot();
    if(root) {
      root -> setTextColor(normal, active);
    }
  }

public:
  void computeExtent(DC* dc, int* w, int* h)
  {
    width  = 0;
    height = 0;
    DrawableBinaryNode* root = (DrawableBinaryNode*)getRoot();

    HGDIOBJ hfont = NULL;
    if(font) {
      hfont = dc->select(font);
    }

    if(root) {  
      root -> getExtent(dc, &width, &height);
      width  += leftMargin;
      height += topMargin;
    }
    *w = width;
    *h = height;

    if(font) {
      dc -> select(hfont);
    }
  }

  void  getExtent(int* w, int* h) { 
    *w = width; *h = height; 
  }

  int    getLeftMargin() { 
    return leftMargin; 
  }

  int    getHorizSpacing() { 
    return horizSpacing; 
  }

  int    getVertSpacing()  { 
    return vertSpacing; 
  }

  int    getTopMargin() { 
    return topMargin; 
  }


  void  setArrangementPolicy(int value) {
      arrangementPolicy = value;
  }

  void  setConnectionPolicy(int value) {
      connectionPolicy = value;
  }

  void  setHorizSpacing(int value) { 
    horizSpacing = value; 
  }

  void  setVertSpacing(int value) { 
    vertSpacing = value; 
  }

  void  setLeftMargin(int margin) { 
    leftMargin = margin; 
  }

  void  setTopMargin(int margin) { 
    topMargin = margin; 
  }

  void  setFont(Font* afont) { 
    font = afont; 
  }

  void  setPen(Pen* apen) { 
    pen = apen; 
  }
};

}


