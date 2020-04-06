/******************************************************************************
 *
 * Copyright (c) 2015 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions, and the following disclaimer.
 * 
 * 2. The name of the author may not be used to endorse or promote products
 *  derived from this software without specific prior written permission.
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
 * LocalTime.h
 *
 *****************************************************************************/

//2015/12/27

#pragma once

#include <sol/Object.h>
#include <sol/String.h>
#include <time.h>

namespace SOL {

class LocalTime :Object {

private:
  time_t time;
  struct tm tm;
  
public:
  LocalTime() {
    this -> time = ::time(0);
    ::localtime_s(&(this->tm), &(this ->time)); 
  }

  LocalTime(const LocalTime& t) {
    this -> time = t.time;
    this -> tm  = t.tm; 
  }

  LocalTime(time_t t) {
    this -> time = t;
    ::localtime_s(&(this->tm), &(this ->time)); 
  }

  time_t getTime()
  {
    return this->time;
  }

  struct tm getTm()
  {
    return this -> tm;
  }
  
public:
  time_t now()
  {
    this -> time = ::time(0);
    ::localtime_s(&(this->tm), &(this ->time));
    return this -> time;
  }
  
  
public:
  LocalTime add(time_t t)
  {
    return LocalTime(this -> time + t);
  }
  
public:
  LocalTime add(int year, int month, int day, int hour, int min, int sec)
  { 
    struct tm tmp;
  
    tmp.tm_year = this -> tm.tm_year + year;
    tmp.tm_mon = this -> tm.tm_mon + month;
    tmp.tm_mday = this -> tm.tm_mday + day;
    tmp.tm_hour = this -> tm.tm_hour + hour;
    tmp.tm_min = this -> tm.tm_min + min;
    tmp.tm_sec = this -> tm.tm_sec + sec;
  
    //mktime
    time_t result = ::mktime(&tmp);

    return LocalTime(result);
  }

  LocalTime sub(int year, int month, int day, int hour, int min, int sec)
  { 
    struct tm tmp;
  
    tmp.tm_year = this -> tm.tm_year - year;
    tmp.tm_mon = this -> tm.tm_mon - month;
    tmp.tm_mday = this -> tm.tm_mday - day;
    tmp.tm_hour = this -> tm.tm_hour - hour;
    tmp.tm_min = this -> tm.tm_min - min;
    tmp.tm_sec = this -> tm.tm_sec - sec;
  
    //mktime
    time_t result = ::mktime(&tmp);

    return LocalTime(result);
  }

  
  LocalTime operator+(LocalTime& t)
  {
    time_t result = this -> time + t.getTime();
    return LocalTime(result);
  }

  LocalTime operator-(LocalTime& t)
  {
    time_t result = this -> time - t.getTime();
    return LocalTime(result);
  }

  String toCharString(const char* year_delim="/", const char* time_delim=":") 
  {
    char buffer[40];
    memset(buffer, 0, sizeof(buffer));
 

   sprintf_s(buffer, CountOf(buffer), "%04d%s%02d%s%02d %02d%s%02d%s%02d", 
     tm.tm_year + 1900, 
     year_delim,
     tm.tm_mon + 1,
     year_delim,
     tm.tm_mday,
   
     tm.tm_hour,
     time_delim,
     tm.tm_min,
     time_delim,
     tm.tm_sec);

    return String(buffer);
  }

  void display()
  {
    printf("%s\n", (const char*)toCharString());
  }
};

}



