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
 *  QuickSorter.h
 *
 *****************************************************************************/

// SOL++2000
//1999.09.04 Modifed run method to match the run method in Thread class.
//2009/10/14 Modified to accept wchar_t* array.

#pragma once

#include <sol\Sorter.h>
#include <sol/View.h>

namespace SOL {

class View;

#define  WM_SORTED  (WM_USER+555)

class QuickSorter :public Sorter {
private:
  View*  view;    // View to receive a completion message
  long  message;  // Thread completion message to be sent the view.

  int*  integers;
  char**  strings;
  wchar_t** wstrings;

  Object** objects;
  int    size;

private:
  void sort(int array[], int low0, int high0)
  {
    int low = low0;
    int high = high0;

    if (high0 > low0) {
      int mid = array[( low0 + high0 ) / 2];

      while (low <= high) {
         while (low < high0  && array[low] < mid) {
          ++low;
        }
         while (high > low0  && array[high] > mid) {
          --high;
        }

        if (low <= high) {
          int t = array[low];
          array[low] = array[high];
          array[high] = t;
          ++low;
          --high;
        }
      }

      if (low0 < high) {
        sort(array, low0, high);
      }

      if (low < high0) {
        sort(array, low, high0);
      }
    }
  }

private:
  void sort(char* array[], int low0, int high0)
  {
    int low = low0;
    int high = high0;

    if (high0 > low0) {
  
      char* mid = array[(low0 + high0) / 2];

      while (low <= high) {
         while (low < high0  && strcmp(array[low], mid) < 0) {
          ++low;
        }

         while (high > low0  && strcmp(array[high], mid) > 0) {
          --high;
        }

        if (low <= high) {
          char* t = array[low];
          array[low]  = array[high];
          array[high] = t;
          ++low;
          --high;
        }
      }

      if (low0 < high) {
        sort(array, low0, high);
      }

      if (low < high0) {
        sort(array, low, high0);
      }
    }
  }


private:
  void sort(wchar_t* array[], int low0, int high0)
  {
    int low = low0;
    int high = high0;

    if (high0 > low0) {
  
      wchar_t* mid = array[(low0 + high0) / 2];

      while (low <= high) {
         while (low < high0  && strcmp(array[low], mid) < 0) {
          ++low;
        }

         while (high > low0  && strcmp(array[high], mid) > 0) {
          --high;
        }

        if (low <= high) {
          wchar_t* t = array[low];
          array[low]  = array[high];
          array[high] = t;
          ++low;
          --high;
        }
      }

      if (low0 < high) {
        sort(array, low0, high);
      }

      if (low < high0) {
        sort(array, low, high0);
      }
    }
  }


private:
  void sort(Object* array[], int low0, int high0)
  {
    int low = low0;
    int high = high0;

    if (high0 > low0) {

      Object* mid = array[(low0 + high0) / 2];

      while (low <= high) {
         while (low < high0  && array[low]->compare(mid) <0) {
          ++low;
        }

         while (high > low0  && array[high] -> compare(mid) >0) {
          --high;
        }

        if (low <= high) {
          Object* t = array[low];
          array[low] = array[high];
          array[high] = t;
          ++low;
          --high;
        }
      }

      if (low0 < high) {
        sort(array, low0, high);
      }

      if (low < high0) {
        sort(array, low, high0);
      }
    }
  }

public:
  QuickSorter(View* view1=NULL, long message1= WM_SORTED)
  :Sorter(),
    view(view1),
    message(message1),
    integers(NULL),
    strings(NULL),
    wstrings(NULL),
    objects(NULL),
    size(0)
  {
  }

public:
  ~QuickSorter() { }

public:
//   
  void QuickSorter::sort(int* array1, int size1)
  {
    integers = array1;
    strings  = NULL;
    objects  = NULL;
    size   = size1;
    resume();
  }



//
public:
  void sort(char** array1, int size1)
  {
    integers = NULL;
    strings  = array1;
    objects  = NULL;
    size   = size1;

    resume();
  }

public:
  void sort(wchar_t** array1, int size1)
  {
    integers = NULL;
    wstrings  = array1;
    objects  = NULL;
    size   = size1;

    resume();
  }


public:
// 
  void sort(Object** objects1, int size1)
  {
    integers = NULL;
    strings  = NULL;
    objects  = objects1;
    size   = size1;

    resume();
  }

//  virtual void run(); // 1999.09.04 Modifed
public:
  // 1999.09.04 Modified the return-value and the argument.
  virtual void run() 
  {
    if(integers && size>0) {
      sort(integers, 0, size-1);
    }

    if(strings && size>0) {
      sort(strings, 0, size-1);
    }
    if(wstrings && size>0) {
      sort(wstrings, 0, size-1);
    }
    if(objects && size>0) {
      sort(objects, 0, size-1);
    }
    if (view) {
      view-> post(message, 0, (LPARAM)this);
    }
  }
};

}
