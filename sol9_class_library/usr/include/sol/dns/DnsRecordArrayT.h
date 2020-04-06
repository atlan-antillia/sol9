/******************************************************************************
 *
 * Copyright (c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  DnsRecordArrayT.h
 *
 *****************************************************************************/

// SOL9
// 2010/1/2
// 2011/1/14 Updated

#pragma once
#include <sol/dns/DnsObject.h>
#include <sol/net/IPv4Address.h>
#include <sol/net/IPv6Address.h>
#include <sol/dns/DnsData.h>
#include <sol/dns/DnsRecordT.h>

namespace SOL {

template <typename T> class DnsRecordArrayT :public DnsObject {

private:
  WORD  type;

  size_t  count;

  DnsRecordT<T>* records;

public:
  /**
   * Constructor
   */
  DnsRecordArrayT()
  :type(0),
   count(0),
   records(NULL)
  {

  }

public:
  ~DnsRecordArrayT()
  {
    clear();
  }

public:
  void clear()
  {
    if (this->records) {
      delete [] this->records;
      this->records = NULL;
    }
  }

public:
  WORD getType()
  {
    return this->type;
  }

public:
  size_t getCount()
  {
    return this->count;
  }

public:
  //2011/1/14
  DnsRecordT<T>& getNth(int n) 
  {
    if (this->records) {
      if (n >= 0 && n < (int)this->count) {
        return  this->records[n];
      } else {
        throw Exception("DnsDataArrayT::getNth; OutOfIndex");
      }
    } else {
      throw Exception("DnsDataArrayT::getNth; No data.");
    }
  }

public:
  DnsRecordT<T>* alloc(WORD type, size_t count) 
  {
    isValidType(type);

    if (count <1) {
      throw Exception("DnsDataArrayT::alloc; Invalid count");
    }

    this->type = type;
  
    this->count = count;
    this->records = new DnsRecordT<T>[count];

    return this->records;
  }

public:
  bool isValidType(WORD type) 
  {
    bool rc = false;
    if ((type >= DNS_TYPE_A     && type<=DNS_TYPE_OPT) ||
      (type >= DNS_TYPE_ADDRS && type<=DNS_TYPE_ANY)) {
      rc = true;
    } else {
      throw Exception("DnsDataArrayT::isValidType; Invalid type");
    }
    return rc;
  }


public:
  void display()
  {
    if (records && count>0) {
      for (size_t i=0; i<count; i++) {
        records[i].display();
      }
    }
  }
};

}


