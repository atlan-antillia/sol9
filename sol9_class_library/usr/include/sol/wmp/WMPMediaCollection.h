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
 *  WMPMediaCollection.h
 *
 *****************************************************************************/

// SOL9
// 2011/12/07

#pragma once

#include <sol/wmp/WMPObject.h>

namespace SOL {

class WMPMediaCollection :public WMPObject{

private:
  IWMPMediaCollection2Ptr collection;

public:
  WMPMediaCollection(IWMPMediaCollectionPtr ptr)
  :collection(ptr)
  {
    if (ptr == NULL) {
      throw NullPointerException("WMPMediaCollection is NULL", 0);
    }
  }

public:
  ~WMPMediaCollection()
  {
    collection = NULL;
  }

    //<iWMPMediaCollection> interface
public:
    
  IWMPMediaPtr add(_bstr_t bstrURL)
  {
    return collection->add(bstrURL);    
  }

public:
  IWMPPlaylistPtr getAll()
  {
    return collection->getAll();

  }

public:
  IWMPPlaylistPtr getByName(_bstr_t bstrName)
  {
    return collection->getByName(bstrName);
  }


public:
  IWMPPlaylistPtr getByGenre(_bstr_t bstrGenre)
  {
    return collection->getByGenre(bstrGenre);
  }

public:
  IWMPPlaylistPtr getByAuthor(_bstr_t bstrAuthor)
  {
    return collection->getByAuthor(bstrAuthor);
  }

public:
  IWMPPlaylistPtr getByAlbum(_bstr_t bstrAlbum)
  {
    return collection->getByAlbum(bstrAlbum);
  }

public:
  IWMPPlaylistPtr getByAttribute(_bstr_t bstrAttribute, _bstr_t bstrValue)
  {
    return collection->getByAttribute(bstrAttribute, bstrValue);
  }


public:
  HRESULT remove(struct IWMPMedia * pItem, VARIANT_BOOL varfDeleteFile)
  {
    return collection->remove(pItem, varfDeleteFile);
  }

public:
  IWMPStringCollectionPtr getAttributeStringCollection(_bstr_t bstrAttribute, _bstr_t bstrMediaType)
  {
    return collection->getAttributeStringCollection(bstrAttribute, bstrMediaType);
  }

public:
  long getMediaAtom(_bstr_t bstrItemName)
  {
    return collection->getMediaAtom(bstrItemName);
  }

public:
  HRESULT setDeleted(struct IWMPMedia * pItem, VARIANT_BOOL varfIsDeleted)
  {
    return collection->setDeleted(pItem, varfIsDeleted);
  }

public:
  VARIANT_BOOL isDeleted(struct IWMPMedia * pItem)
  {
    return collection->isDeleted(pItem);
  }
  //</IWMPMediaCollection>


public:
  //<IWMPMediaCollection2> interface

  IWMPQueryPtr createQuery ( )
  {
    return collection->createQuery ( );
  }

  IWMPPlaylistPtr getPlaylistByQuery (
    struct IWMPQuery * pQuery,
    _bstr_t bstrMediaType,
    _bstr_t bstrSortAttribute,
    VARIANT_BOOL fSortAscending )
  {
    return collection->getPlaylistByQuery (
        pQuery,
        bstrMediaType,
        bstrSortAttribute,
        fSortAscending );
  }
  
  IWMPStringCollectionPtr getStringCollectionByQuery (
        _bstr_t bstrAttribute,
        struct IWMPQuery * pQuery,
        _bstr_t bstrMediaType,
        _bstr_t bstrSortAttribute,
        VARIANT_BOOL fSortAscending )
  {
    return collection->getStringCollectionByQuery (
      bstrAttribute,
      pQuery,
      bstrMediaType,
      bstrSortAttribute,
      fSortAscending );
  }
    
  IWMPPlaylistPtr getByAttributeAndMediaType (
    _bstr_t bstrAttribute,
    _bstr_t bstrValue,
    _bstr_t bstrMediaType )
  {
    return collection->  getByAttributeAndMediaType (
      bstrAttribute,
      bstrValue,
      bstrMediaType );
  }
  //</IWMPMediaCollection2> 

};

}
