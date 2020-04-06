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
 *  ADOXEnumNames.h
 *
 *****************************************************************************/

// SOL9
// 2009/06/05

#pragma once

#include <sol/Object.h>
#include <sol/Arg.h>
#include <sol/ArgT.h>
#include <sol/ArgListT.h>

namespace SOL {

class ADOXEnumNames :public Object {

public:
  /**
   * Constructor
   */
  ADOXEnumNames()
  {
  }

public:
  /**
   * Destructor
   */
  ~ADOXEnumNames()
  {
  }

public:
  //2009/06/05
  const char* getName(ADOX::RuleEnum type)
  {
    static const ArgT<char> names[] =
    {
        {"adRINone",   (LONG_PTR)ADOX::adRINone},
      {"adRICascade",  (LONG_PTR)ADOX::adRICascade},
      {"adRISetNull",  (LONG_PTR)ADOX::adRISetNull},
      {"adRISetDefault", (LONG_PTR)ADOX::adRISetDefault},
    };

    return findName(names, XtNumber(names), (int)type);
  }

public:
  //2009/06/05
  const char* getName(ADOX::KeyTypeEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adKeyPrimary", (LONG_PTR)ADOX::adKeyPrimary},
      {"adKeyForeign", (LONG_PTR)ADOX::adKeyForeign},
      {"adKeyUnique",  (LONG_PTR)ADOX::adKeyUnique}
    };
    return findName(names, XtNumber(names), (int)type);

  }
public:
  //2009/06/05
  const char* getName(ADOX::ColumnAttributesEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adColFixed",    (LONG_PTR)ADOX::adColFixed},
      {"adColNullable", (LONG_PTR)ADOX::adColNullable}
    };
    return findName(names, XtNumber(names), (int)type);
  }
  
public:
  //2009/06/05
  const char* getName(ADOX::SortOrderEnum type)
  {
    static const ArgT<char> names[] =
    {    
      {"adSortAscending", (LONG_PTR)ADOX::adSortAscending},
      {"dSortDescending", (LONG_PTR)ADOX::adSortDescending}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  //2009/06/05

  const char* getName(ADOX::AllowNullsEnum type)
  {
    static const ArgT<char> names[] =
    {    
      {"adIndexNullsAllow",    (LONG_PTR)ADOX::adIndexNullsAllow},
      {"adIndexNullsDisallow", (LONG_PTR)ADOX::adIndexNullsDisallow},
      {"adIndexNullsIgnor",    (LONG_PTR)ADOX::adIndexNullsIgnore},
      {"dIndexNullsIgnoreAny", (LONG_PTR)ADOX::adIndexNullsIgnoreAny}
    };

    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADOX::ObjectTypeEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adPermObjProviderSpecific", (LONG_PTR)ADOX::adPermObjProviderSpecific},
      {"adPermObjTable",            (LONG_PTR)ADOX::adPermObjTable},
      {"adPermObjColumn",           (LONG_PTR)ADOX::adPermObjColumn},
      {"adPermObjDatabase",         (LONG_PTR)ADOX::adPermObjDatabase},
      {"adPermObjProcedure",        (LONG_PTR)ADOX::adPermObjProcedure},
      {"adPermObjView",             (LONG_PTR)ADOX::adPermObjView}
    };

    return findName(names, XtNumber(names), (int)type);
  }

  
public:
  const char* getName(ADOX::RightsEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adRightNone",        (LONG_PTR)ADOX::adRightNone},
      {"adRightDrop",        (LONG_PTR)ADOX::adRightDrop},
      {"adRightExclusive",   (LONG_PTR)ADOX::adRightExclusive},
      {"adRightReadDesign",  (LONG_PTR)ADOX::adRightReadDesign},
      {"adRightWriteDesign", (LONG_PTR)ADOX::adRightWriteDesign},
      {"adRightWithGrant",   (LONG_PTR)ADOX::adRightWithGrant},
      {"adRightReference",   (LONG_PTR)ADOX::adRightReference},
      {"adRightCreate",      (LONG_PTR)ADOX::adRightCreate},
      {"adRightInsert",      (LONG_PTR)ADOX::adRightInsert},
      {"adRightDelete",      (LONG_PTR)ADOX::adRightDelete},
      {"adRightReadPermissions", (LONG_PTR)ADOX::adRightReadPermissions},
      {"adRightWritePermissions", (LONG_PTR)ADOX::adRightWritePermissions},
      {"adRightWriteOwner",  (LONG_PTR)ADOX::adRightWriteOwner},
      {"adRightMaximumAllowed", (LONG_PTR)ADOX::adRightMaximumAllowed},
      {"adRightFull",        (LONG_PTR)ADOX::adRightFull},
      {"adRightExecute",     (LONG_PTR)ADOX::adRightExecute},
      {"adRightUpdate",      (LONG_PTR)ADOX::adRightUpdate},
      {"adRightRead",        (LONG_PTR)ADOX::adRightRead}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADOX::ActionEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adAccessGrant",  (LONG_PTR)ADOX::adAccessGrant},
      {"adAccessSet",    (LONG_PTR)ADOX::adAccessSet},
      {"adAccessDeny",   (LONG_PTR)ADOX::adAccessDeny},
      {"adAccessRevoke", (LONG_PTR)ADOX::adAccessRevoke}
    };

    return findName(names, XtNumber(names), (int)type);
  }

  
public:
  const char* getName(ADOX::InheritTypeEnum type)
  {
    static const ArgT<char> names[] =
    {
      {"adInheritNone",        (LONG_PTR)ADOX::adInheritNone},
      {"adInheritObjects",     (LONG_PTR)ADOX::adInheritObjects},
      {"adInheritContainers",  (LONG_PTR)ADOX::adInheritContainers},
      {"adInheritBoth",        (LONG_PTR)ADOX::adInheritBoth},
      {"adInheritNoPropogate", (LONG_PTR)ADOX::adInheritNoPropogate}
    };
    return findName(names, XtNumber(names), (int)type);
  }

public:
  const char* getName(ADOX::DataTypeEnum type)
  {
    static const ArgT<char> names[] = {
      {"Empty",        (LONG_PTR)ADOX::adEmpty},
      {"TineyInt",     (LONG_PTR)ADOX::adTinyInt},
      {"SmallInt",     (LONG_PTR)ADOX::adSmallInt},
      {"Integer",      (LONG_PTR)ADOX::adInteger},
      {"BigInt",       (LONG_PTR)ADOX::adBigInt},
      {"UnsignedTinyInt", (LONG_PTR)ADOX::adUnsignedTinyInt},
      {"UnsignedSmallInt",(LONG_PTR)ADOX::adUnsignedSmallInt},
      {"UnsignedIn",    (LONG_PTR)ADOX::adUnsignedInt},
      {"UnsignedBigInt",  (LONG_PTR)ADOX::adUnsignedBigInt},
      {"Single",       (LONG_PTR)ADOX::adSingle},
      {"Double",       (LONG_PTR)ADOX::adDouble},
      {"Currency",     (LONG_PTR)ADOX::adCurrency},
      {"Decimal",      (LONG_PTR)ADOX::adDecimal},
      {"Numeric",      (LONG_PTR)ADOX::adNumeric},
      {"Boolean",      (LONG_PTR)ADOX::adBoolean},
      {"Error",        (LONG_PTR)ADOX::adError},
      {"UserDefined",  (LONG_PTR)ADOX::adUserDefined},
      {"Variant",      (LONG_PTR)ADOX::adVariant},
      {"IDispatch",    (LONG_PTR)ADOX::adIDispatch},
      {"IUnknown",     (LONG_PTR)ADOX::adIUnknown},
      {"GUID",         (LONG_PTR)ADOX::adGUID},
      {"Date",         (LONG_PTR)ADOX::adDate},
      {"DBDate",       (LONG_PTR)ADOX::adDBDate},
      {"DBTime",       (LONG_PTR)ADOX::adDBTime},
      {"DBTimeStamp",  (LONG_PTR)ADOX::adDBTimeStamp},
      {"BSTR",         (LONG_PTR)ADOX::adBSTR},
      {"Char",         (LONG_PTR)ADOX::adChar},
      {"VarChar",      (LONG_PTR)ADOX::adVarChar},
      {"LongVarChar",  (LONG_PTR)ADOX::adLongVarChar},
      {"WChar",        (LONG_PTR)ADOX::adWChar},
      {"VarWChar",     (LONG_PTR)ADOX::adVarWChar},
      {"LongVarWChar", (LONG_PTR)ADOX::adLongVarWChar},
      {"Binary",       (LONG_PTR)ADOX::adBinary},
      {"VarBinary",    (LONG_PTR)ADOX::adVarBinary},
      {"LongVarBinary",(LONG_PTR)ADOX::adLongVarBinary},
      {"Chapter",      (LONG_PTR)ADOX::adChapter},
      {"FileTime",     (LONG_PTR)ADOX::adFileTime},
      {"PropVariant",  (LONG_PTR)ADOX::adPropVariant},
      {"VarNumeric",   (LONG_PTR)ADOX::adVarNumeric},
      //{"Array",      ADOX::adArray}
    };
    return findName(names, XtNumber(names), (int)type);
  }

private:
  const char* findName(const ArgT<char>* names, const int count, int type)
  {
    const char* name = "";
    for(int i = 0; i<count; i++) {
      if ((int)names[i].value == type) {
        name = names[i].name;
        break;
      }
    }
    return name;
  }

};

}
