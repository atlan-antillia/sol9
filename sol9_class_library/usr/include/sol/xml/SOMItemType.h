/******************************************************************************
 *
 * Copyright(c) 2011 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  SchemaConstant.h
 *
 *****************************************************************************/

// SOL9
// 2011/02/13
#pragma once

#include <sol/xml/XMLObject.h>
#include <sol/ArgListT.h>

namespace SOL {

class SOMItemType : public Object {

public:
  const TCHAR* getType(int value)
  {
    static const ArgT<TCHAR> names[] = {

    {_T("Schema"), SOMITEM_SCHEMA},
    {_T("Attribute"), SOMITEM_ATTRIBUTE},
    {_T("AttributeGroup"), SOMITEM_ATTRIBUTEGROUP},
    {_T("Notation"), SOMITEM_NOTATION},
  //  {_T("Annotation"), SOMITEM_ANNOTATION}, 2015/07/15
    {_T("IdentityConstraint"), SOMITEM_IDENTITYCONSTRAINT},
    {_T("Key"), SOMITEM_KEY},
    {_T("KeyRef"), SOMITEM_KEYREF},
    {_T("Unique"), SOMITEM_UNIQUE},
    {_T("AnyType"), SOMITEM_ANYTYPE},
    {_T("DataType"), SOMITEM_DATATYPE},
    {_T("DataType_AnyType"), SOMITEM_DATATYPE_ANYTYPE},
    {_T("DataType_AnyUri"), SOMITEM_DATATYPE_ANYURI},
    {_T("DataType_Base64Binary"), SOMITEM_DATATYPE_BASE64BINARY},
    {_T("DataType_Boolean"), SOMITEM_DATATYPE_BOOLEAN},
    {_T("DataType_Byte"), SOMITEM_DATATYPE_BYTE},
    {_T("DataType_Date"), SOMITEM_DATATYPE_DATE},
    {_T("DataType_DateTime"), SOMITEM_DATATYPE_DATETIME},
    {_T("DataType_Daty"), SOMITEM_DATATYPE_DAY},
    {_T("DataType_Decimal"), SOMITEM_DATATYPE_DECIMAL},
    {_T("DataType_Double"), SOMITEM_DATATYPE_DOUBLE},
    {_T("DataType_Duration"), SOMITEM_DATATYPE_DURATION},
    {_T("DataType_Entities"), SOMITEM_DATATYPE_ENTITIES},
    {_T("DataType_Entity"), SOMITEM_DATATYPE_ENTITY},
    {_T("DataType_Float"), SOMITEM_DATATYPE_FLOAT},
    {_T("DataType_HexBinary"), SOMITEM_DATATYPE_HEXBINARY},
    {_T("DataType_ID"), SOMITEM_DATATYPE_ID},
    {_T("DataType_IDRef"), SOMITEM_DATATYPE_IDREF},
    {_T("DataType_IDRefs"), SOMITEM_DATATYPE_IDREFS},
    {_T("DataType_Int"), SOMITEM_DATATYPE_INT},
    {_T("DataType_Integer"), SOMITEM_DATATYPE_INTEGER},
    {_T("DataType_Language"), SOMITEM_DATATYPE_LANGUAGE},
    {_T("DataType_Long"), SOMITEM_DATATYPE_LONG},
    {_T("DataType_Month"), SOMITEM_DATATYPE_MONTH},
    {_T("DataType_MonthDay"), SOMITEM_DATATYPE_MONTHDAY},
    {_T("DataType_Name"), SOMITEM_DATATYPE_NAME},
    {_T("DataType_Ncname"),     SOMITEM_DATATYPE_NCNAME},
    {_T("DataType_NegativeInteger"), SOMITEM_DATATYPE_NEGATIVEINTEGER},
    {_T("DataType_NMToken"), SOMITEM_DATATYPE_NMTOKEN},
    {_T("DataType_NMTokens"), SOMITEM_DATATYPE_NMTOKENS},
    {_T("DataType_NonNegatvieInteger"), SOMITEM_DATATYPE_NONNEGATIVEINTEGER},
    {_T("DataType_NonPositiveInteger"), SOMITEM_DATATYPE_NONPOSITIVEINTEGER},
    {_T("DataType_NormalizedString"), SOMITEM_DATATYPE_NORMALIZEDSTRING},
    {_T("DataType_Notation"), SOMITEM_DATATYPE_NOTATION},
    {_T("DataType_PositiveInteger"), SOMITEM_DATATYPE_POSITIVEINTEGER},
    {_T("DataType_QName"), SOMITEM_DATATYPE_QNAME},
    {_T("DataType_Short"), SOMITEM_DATATYPE_SHORT},
    {_T("DataType_String"), SOMITEM_DATATYPE_STRING},
    {_T("DataType_Time"), SOMITEM_DATATYPE_TIME},
    {_T("DataType_Token"), SOMITEM_DATATYPE_TOKEN},
    {_T("DataType_UnsignedByte"), SOMITEM_DATATYPE_UNSIGNEDBYTE},
    {_T("DataType_UnsignedInt"), SOMITEM_DATATYPE_UNSIGNEDINT},
    {_T("DataType_UnsignedLong"), SOMITEM_DATATYPE_UNSIGNEDLONG},
    {_T("DataType_UnsignedShort"), SOMITEM_DATATYPE_UNSIGNEDSHORT},
    {_T("DataType_Year"), SOMITEM_DATATYPE_YEAR},
    {_T("DataType_YearMonth"), SOMITEM_DATATYPE_YEARMONTH},
    {_T("DataType_AnySimpleType"), SOMITEM_DATATYPE_ANYSIMPLETYPE},
    {_T("SimpleType"), SOMITEM_SIMPLETYPE},
    {_T("ComplexType"), SOMITEM_COMPLEXTYPE},
    {_T("Particle"), SOMITEM_PARTICLE},
    {_T("Any"), SOMITEM_ANY},
    {_T("AnyAttribute"), SOMITEM_ANYATTRIBUTE},
    {_T("Element"), SOMITEM_ELEMENT},
    {_T("Group"), SOMITEM_GROUP},
    {_T("All"), SOMITEM_ALL},
    {_T("Choice"), SOMITEM_CHOICE},
    {_T("Sequence"), SOMITEM_SEQUENCE},
    {_T("EmptyParticle"), SOMITEM_EMPTYPARTICLE},
    {_T("Null"), SOMITEM_NULL},
    {_T("Null_Type"), SOMITEM_NULL_TYPE},
    {_T("Null_Any"), SOMITEM_NULL_ANY},
    {_T("Null_Attribute"), SOMITEM_NULL_ANYATTRIBUTE},
    {_T("Null_Element"), SOMITEM_NULL_ELEMENT}
    };
    ArgListT<TCHAR> list(names, CountOf(names));
    return list.getName(value);
  }
};


}
