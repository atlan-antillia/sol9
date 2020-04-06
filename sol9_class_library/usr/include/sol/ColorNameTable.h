/******************************************************************************
 *
 * Copyright (c) 2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  ColorNameTable.h
 *
 *****************************************************************************/

// 2012/05/03

#pragma once

#include <sol\Object.h>
#include <sol\String.h>
#include <sol\StringT.h>

namespace SOL {

typedef struct {
  char* name;
  char* color;
} NameTable;


class ColorNameTable :public Object {

public:
  ColorNameTable()
  {
  }

public:
  int getSize()
  {
    int size = 0;
    getNameTable(size);
    return size;
  }

public:
  NameTable* getNameTable(int& size)
  {
    static NameTable table[] = {

      {"White","#FFFFFF"},
      {"WhiteSmoke","#F5F5F5"},
      {"Snow","#FFFAFA"},
      {"MistyRose","#FFE4E1"},
      {"Seashell","#FFF5EE"},
      {"Linen","#FAF0E6"},
      {"AntiqueWhite","#FAEBD7"},
      {"BlanchedAlmond","#FFEBCD"},
      {"PapayaWhip","#FFEFD5"},
      {"OldLace","#FDF5E6"},
      {"FloralWhite","#FFFAF0"},
      {"Cornsilk","#FFF8DC"},
      {"LemonChiffon","#FFFACD"},
      {"Beige","#F5F5DC"},
      {"LightGoldenrodYellow","#FAFAD2"},
      {"Ivory","#FFFFF0"},
      {"LightYellow","#FFFFE0"},
      {"Honeydew","#F0FFF0"},
      {"MintCream","#F5FFFA"},
      {"Azure","#F0FFFF"},
      {"LightCyan","#E0FFFF"},
      {"AliceBlue","#F0F8FF"},
      {"Lavender","#E6E6FA"},
      {"GhostWhite","#F8F8FF"},
      {"LavenderBlush","#FFF0F5"},
      {"Gainsboro","#DCDCDC"},
      {"LightGrey","#D3D3D3"},
      {"PeachPuff","#FFDAB9"},
      {"Bisque","#FFE4C4"},
      {"NavajoWhite","#FFDEAD"},
      {"Moccasin","#FFE4B5"},
      {"Wheat","#F5DEB3"},
      {"PaleGoldenrod","#EEE8AA"},
      {"PaleTurquoise","#AFEEEE"},
      {"Pink","#FFC0CB"},
      {"LightPink","#FFB6C1"},
      {"Silver","#C0C0C0"},
      {"LightCoral","#F08080"},
      {"Salmon","#FA8072"},
      {"LightSalmon","#FFA07A"},
      {"BurlyWood","#DEB887"},
      {"Khaki","#F0E68C"},
      {"LightGreen","#90EE90"},
      {"PaleGreen","#98FB98"},
      {"Aquamarine","#7FFFD4"},
      {"PowderBlue","#B0E0E6"},
      {"LightBlue","#ADD8E6"},
      {"SkyBlue","#87CEEB"},
      {"LightSkyBlue","#87CEFA"},
      {"LightSteelBlue","#B0C4DE"},
      {"Thistle","#D8BFD8"},
      {"Plum","#DDA0DD"},
      {"Violet","#EE82EE"},
      {"HotPink","#FF69B4"},
      {"DarkGray","#A9A9A9"},
      {"RosyBrown","#BC8F8F"},
      {"Tomato","#FF6347"},
      {"DarkSalmon","#E9967A"},
      {"Coral","#FF7F50"},
      {"SandyBrown","#F4A460"},
      {"Tan","#D2B48C"},
      {"DarkSeaGreen","#8FBC8F"},
      {"MediumAquamarine","#66CDAA"},
      {"CornflowerBlue","#6495ED"},
      {"MediumSlateBlue","#7B68EE"},
      {"MediumPurple","#9370DB"},
      {"Orchid","#DA70D6"},
      {"PaleVioletRed","#DB7093"},
      {"Gray","#808080"},
      {"IndianRed","#CD5C5C"},
      {"Red","#FF0000"},
      {"OrangeRed","#FF4500"},
      {"Peru","#CD853F"},
      {"DarkOrange","#FF8C00"},
      {"Orange","#FFA500"},
      {"Gold","#FFD700"},
      {"DarkKhaki","#BDB76B"},
      {"Yellow","#FFFF00"},
      {"YellowGreen","#9ACD32"},
      {"GreenYellow","#ADFF2F"},
      {"Chartreuse","#7FFF00"},
      {"LimeGreen","#32CD32"},
      {"Lime","#00FF00"},
      {"SpringGreen","#00FF7F"},
      {"Turquoise","#40E0D0"},
      {"MediumTurquoise","#48D1CC"},
      {"Cyan","#00FFFF"},
      {"Aqua","#00FFFF"},
      {"CadetBlue","#5F9EA0"},
      {"DeepSkyBlue","#00BFFF"},
      {"DodgerBlue","#1E90FF"},
      {"LightSlateGray","#778899"},
      {"SlateGray","#708090"},
      {"RoyalBlue","#4169E1"},
      {"Blue","#0000FF"},
      {"SlateBlue","#6A5ACD"},
      {"BlueViolet","#8A2BE2"},
      {"MediumOrchid","#BA55D3"},
      {"Magenta","#FF00FF"},
      {"Fuchsia","#FF00FF"},
      {"DeepPink","#FF1493"},
      {"DimGray","#696969"},
      {"Brown","#A52A2A"},
      {"FireBrick","#B22222"},
      {"Sienna","#A0522D"},
      {"Chocolate","#D2691E"},
      {"Goldenrod","#DAA520"},
      {"LawnGreen","#7CFC00"},
      {"MediumSeaGreen","#3CB371"},
      {"MediumSpringGreen","#00FA9A"},
      {"LightSeaGreen","#20B2AA"},
      {"DarkTurquoise","#00CED1"},
      {"SteelBlue","#4682B4"},
      {"MediumBlue","#0000CD"},
      {"DarkOrchid","#9932CC"},
      {"DarkViolet","#9400D3"},
      {"MediumVioletRed","#C71585"},
      {"Crimson","#DC143C"},
      {"SaddleBrown","#8B4513"},
      {"DarkGoldenrod","#B8860B"},
      {"OliveDrab","#6B8E23"},
      {"DarkOliveGreen","#556B2F"},
      {"ForestGreen","#228B22"},
      {"SeaGreen","#2E8B57"},
      {"DarkSlateBlue","#483D8B"},
      {"DarkRed","#8B0000"},
      {"Maroon","#800000"},
      {"Olive","#808000"},
      {"Green","#008000"},
      {"DarkSlateGray","#2F4F4F"},
      {"DarkCyan","#008B8B"},
      {"Teal","#008080"},
      {"MidnightBlue","#191970"},
      {"DarkBlue","#00008B"},
      {"Navy","#000080"},
      {"Indigo","#4B0082"},
      {"DarkMagenta","#8B008B"},
      {"Purple","#800080"},
      {"DarkGreen","#006400"},
      {"Black","#000000"},
      };
    size = CountOf(table);

    return table;
  }

public:
  // @name: This is a name of color such as "White",..., "Black".
  // @color: This is a rgb string of format #RRGGBB.
  // It is a hex format string of red, green, and blue.
  bool getNth(int n, __out String& name, __out String& color, __out COLORREF& rgb)
  {
    bool rc = false;
    int size = 0;
    NameTable* table = getNameTable(size);
    if (n >= 0 && n<size) {
      name = table[n].name;
      color = table[n].color;
      getRGB(table[n].color, rgb);
      rc = true;
    }
    return rc;
  }


public:
  // @name: name is a name of color such as "White",..., "Black".
  bool lookup(__in const char* name, __out COLORREF& rgb)
  {
    bool rc = false;
    int size = 0;
    NameTable* table = getNameTable(size);

    for (int i = 0; i<size; i++) {
      if (_stricmp(table[i].name, name) == 0) {
        if (getRGB(table[i].color, rgb)) {
          rc = true;
        }
        break;
      }
    }
    return rc;
  }


public:
  //
  // @color: takes the format "#RRGGBB";
  //
  bool getRGB(__in const char* color, __out COLORREF& rgb)
  {
    bool rc = false;
    rgb = 0;
    if (color && *color == '#') {
      color++;
      if (strlen(color) == 6) {
        char r[3], g[3], b[3];
        memcpy(r, color, 2);
        r[2] = NULL;
        color +=2;

        memcpy(g, color, 2);
        g[2] = NULL;
        color +=2;
        memcpy(b, color, 2);
        b[2] = NULL;
      
        unsigned int rvalue = strtoul(r, NULL, 16);    
        unsigned int gvalue = strtoul(g, NULL, 16);
        unsigned int bvalue = strtoul(b, NULL, 16);

        rgb = RGB(rvalue,gvalue,bvalue);
        rc = true;
      }
    }
    return rc;
  }

public:
  //
  // @color: takes the format "#RRGGBB";
  //
  bool getRGB(__in const char* color, 
        __out unsigned int& red, 
        __out unsigned int& green, 
        __out unsigned int& blue)
  {
    bool rc = false;
    if (*color == '#') {
      color++;
      if (strlen(color) == 6) {
        char r[3], g[3], b[3];
        memcpy(r, color, 2);
        r[2] = NULL;
        color +=2;

        memcpy(g, color, 2);
        g[2] = NULL;
        color +=2;
        memcpy(b, color, 2);
        b[2] = NULL;

        red = strtoul(r, NULL, 16);
        green = strtoul(g, NULL, 16);
        blue = strtoul(b, NULL, 16);
        rc = true;
      }
    }
    return rc;
  }

public:
  //
  // @color: takes the format "#RRGGBB";
  //
  bool getRGB(__in const char* color,
        __out String& redHex, 
        __out String& greenHex, 
        __out String& blueHex)
  {
    bool rc = false;
    if (*color == '#') {
      color++;
      if (strlen(color) == 6) {
        char r[3], g[3], b[3];
        memcpy(r, color, 2);
        r[2] = NULL;
        color +=2;

        memcpy(g, color, 2);
        g[2] = NULL;
        color +=2;
        memcpy(b, color, 2);
        b[2] = NULL;

        redHex   = r;
        greenHex = g;
        blueHex  = b;
        rc = true;
      }
    }
    return rc;
  }
};

}
