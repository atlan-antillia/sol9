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
 *  IfTable.h
 *
 *****************************************************************************/

// SOL9
// 2009/08/22

#pragma once
#include <sol/net/MibTable.h>

#include <sol/String.h>

//#include <iphlpapi.h>   //iphlpapi.lib 
 
namespace SOL {

class IfTable :public MibTable {
/*
typedef struct _MIB_IFTABLE {
  DWORD     dwNumEntries;
  MIB_IFROW table[ANY_SIZE];
}MIB_IFTABLE, *PMIB_IFTABLE;
*/
private:
  PMIB_IFTABLE table;
  
public:
  /**
   * Constructor
   */
  IfTable(HWND hwnd = NULL)
  :table(NULL)
  {

  }

public:
  /**
   * Destructor
   */
  ~IfTable()
  {
    clear();
  }

public:
  bool getTable()
  {
    bool rc = false;
    DWORD dwSize = 0 ;
 
    GetIfTable(NULL, &dwSize, FALSE);

    if (dwSize >0) {
      table = (PMIB_IFTABLE)new char[dwSize];;
      DWORD r = NO_ERROR;
      if ((r = GetIfTable(table, &dwSize, FALSE)) == NO_ERROR) {
        rc = true;
      } else {
        clear();
        throw r;  
      }
    }
    return rc;
  }


public:
  virtual void clear()
  {
    if (table) {
      delete [] (char*)table;
      table = NULL;
    }
  }

/*
typedef struct _MIB_IFROW {
  WCHAR wszName[MAX_INTERFACE_NAME_LEN];
  DWORD dwIndex;
  DWORD dwType;
  DWORD dwMtu;
  DWORD dwSpeed;
  DWORD dwPhysAddrLen;
  BYTE  bPhysAddr[MAXLEN_PHYSADDR];
  DWORD dwAdminStatus;
  DWORD dwOperStatus;
  DWORD dwLastChange;
  DWORD dwInOctets;
  DWORD dwInUcastPkts;
  DWORD dwInNUcastPkts;
  DWORD dwInDiscards;
  DWORD dwInErrors;
  DWORD dwInUnknownProtos;
  DWORD dwOutOctets;
  DWORD dwOutUcastPkts;
  DWORD dwOutNUcastPkts;
  DWORD dwOutDiscards;
  DWORD dwOutErrors;
  DWORD dwOutQLen;
  DWORD dwDescrLen;
  BYTE  bDescr[MAXLEN_IFDESCR];
}MIB_IFROW, *PMIB_IFROW;
*/
public:
  /**
   * 
   */
  virtual void display(MIB_IFROW& table) 
  {
    table.bDescr[table.dwDescrLen]='\0';
    printf("Description = %d\n",(int)table.bDescr);

    printf("Name = %S\n", table.wszName);
    printf("Index = 0x%8.8x\n",(int)table.dwIndex);
 
    printf("Type = %s\n",
          getInterfaceType((int)table.dwType) );
 
    printf("Mtu = %d\n",(int)table.dwMtu);
    printf("Speed = %d\n",(int)table.dwSpeed);

    StringT<char> address;
    getPhysicalAddress(table.bPhysAddr, table.dwPhysAddrLen, address);

    printf("PhysicalAddress = %s\n", (const char*)address); 

    printf("AdminStatus = %s\n",
          getAdiminStatus((int)table.dwAdminStatus) );
 
    printf("OperationStatus = %s\n",
          getOperationStatus((int)table.dwOperStatus) );
         
    printf("LastChange = %d\n",(int)table.dwLastChange);
 
    printf("InOctets =  %d\n",(int)table.dwInOctets);
    printf("InUcastPkts = %d\n",(int)table.dwInUcastPkts);
 
    printf("InNUcastPkts = %d\n",(int)table.dwInNUcastPkts);
 
    printf("InDiscards = %d\n",(int)table.dwInDiscards);
    printf("InErrors = %d\n",(int)table.dwInErrors);
 
    printf("InUnknownProtos = %d\n",(int)table.dwInUnknownProtos);
     printf("OutOctets = %d\n",(int)table.dwOutOctets);
    printf("OutUcastPkts = %d\n",(int)table.dwOutUcastPkts);
 
     printf("OutNUcastPkts = %d\n",(int)table.dwOutNUcastPkts);
 
    printf("OutDiscards = %d\n",(int)table.dwOutDiscards);
 
    printf("OutErrors = %d\n",(int)table.dwOutErrors);
 
    printf("OutQLen = %d\n",(int)table.dwOutQLen);
  }

public:
  virtual void display() 
  {
    if (table) {
      printf("Number of IFTable=%d\n", (int)table->dwNumEntries);
      for(int i=0;i< (int)table->dwNumEntries;i++ ){
        display(table->table[i]);  
        printf("\n");
      }
    }
  }

protected:
  const char* getAdiminStatus(DWORD value)
  {
    static const ArgT<char> types[] = {
    {"UP",  MIB_IF_ADMIN_STATUS_UP},
    {"DOWN", MIB_IF_ADMIN_STATUS_DOWN},
    {"TESTING", MIB_IF_ADMIN_STATUS_TESTING},
    };

    const char* name = ""; 
    int count = XtNumber(types);
    for (int i = 0; i<count; i++) {
      if (types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }

public:
  const char* getInterfaceType(DWORD value)
  {
    static const ArgT<char> types[] = {
    {"OTHER",  IF_TYPE_OTHER},
    {"REGULAR_1822",  IF_TYPE_REGULAR_1822},
    {"HDH_1822",  IF_TYPE_HDH_1822},
    {"DDN_X25",  IF_TYPE_DDN_X25}, 
    {"RFC877_X25",  IF_TYPE_RFC877_X25},
    {"ETHERNET_CSMACD",  IF_TYPE_ETHERNET_CSMACD},
    {"IS088023_CSMACD",  IF_TYPE_IS088023_CSMACD},
    {"ISO88024_TOKENBUS",  IF_TYPE_ISO88024_TOKENBUS},
    {"ISO88025_TOKENRING",  IF_TYPE_ISO88025_TOKENRING},
    {"ISO88026_MAN",  IF_TYPE_ISO88026_MAN},
    {"STARLAN",  IF_TYPE_STARLAN},
    {"PROTEON_10MBIT",  IF_TYPE_PROTEON_10MBIT},
    {"PROTEON_80MBIT",  IF_TYPE_PROTEON_80MBIT},
    {"HYPERCHANNEL",  IF_TYPE_HYPERCHANNEL},
    {"FDDI",  IF_TYPE_FDDI},
    {"LAP_B",  IF_TYPE_LAP_B},
    {"SDLC",  IF_TYPE_SDLC},
    {"DS1",  IF_TYPE_DS1},
    {"E1",  IF_TYPE_E1},
    {"BASIC_ISDN",  IF_TYPE_BASIC_ISDN},
    {"PRIMARY_ISDN",  IF_TYPE_PRIMARY_ISDN},
    {"PROP_POINT2POINT_SERIAL",  IF_TYPE_PROP_POINT2POINT_SERIAL},
    {"PPP",  IF_TYPE_PPP},
    {"SOFTWARE_LOOPBACK",  IF_TYPE_SOFTWARE_LOOPBACK},
    {"EON",  IF_TYPE_EON},
    {"ETHERNET_3MBIT",  IF_TYPE_ETHERNET_3MBIT},
    {"NSIP",  IF_TYPE_NSIP},
    {"SLIP",  IF_TYPE_SLIP},
    {"ULTRA",  IF_TYPE_ULTRA},
    {"DS3",  IF_TYPE_DS3},
    {"SIP",  IF_TYPE_SIP},
    {"FRAMERELAY",  IF_TYPE_FRAMERELAY},
    {"RS232",  IF_TYPE_RS232},
    {"PARA",  IF_TYPE_PARA},
    {"ARCNET",  IF_TYPE_ARCNET},
    {"RCNET_PLUS",  IF_TYPE_ARCNET_PLUS},
    {"ATM",  IF_TYPE_ATM},
    {"MIO_X25",  IF_TYPE_MIO_X25},
    {"SONET",  IF_TYPE_SONET},
    {"X25_PLE",  IF_TYPE_X25_PLE},
    {"ISO88022_LLC",  IF_TYPE_ISO88022_LLC},
    {"LOCALTALK",  IF_TYPE_LOCALTALK},
    {"SMDS_DXI",  IF_TYPE_SMDS_DXI},
    {"FRAMERELAY_SERVICE",  IF_TYPE_FRAMERELAY_SERVICE},
    {"V35",  IF_TYPE_V35},
    {"HSSI",  IF_TYPE_HSSI},
    {"HIPPI",  IF_TYPE_HIPPI},
    {"MODEM",  IF_TYPE_MODEM},
    {"AAL5",  IF_TYPE_AAL5},
    {"SONET_PATH}",  IF_TYPE_SONET_PATH},
    {"SONET_VT",  IF_TYPE_SONET_VT},
    {"SMDS_ICIP",  IF_TYPE_SMDS_ICIP},
    {"PROP_VIRTUAL",  IF_TYPE_PROP_VIRTUAL},
    {"PROP_MULTIPLEXOR",  IF_TYPE_PROP_MULTIPLEXOR},
    {"IEEE80212",  IF_TYPE_IEEE80212},
    {"FIBRECHANNEL",  IF_TYPE_FIBRECHANNEL},
    {"HIPPIINTERFACE",  IF_TYPE_HIPPIINTERFACE},
    {"FRAMERELAY_INTERCONNECT",  IF_TYPE_FRAMERELAY_INTERCONNECT},
    {"AFLANE_8023",  IF_TYPE_AFLANE_8023},
    {"AFLANE_8025",  IF_TYPE_AFLANE_8025},
    {"CCTEMUL",  IF_TYPE_CCTEMUL},
    {"FASTETHER",  IF_TYPE_FASTETHER},
    {"ISDN",  IF_TYPE_ISDN},
    {"V11",  IF_TYPE_V11},
    {"V36",  IF_TYPE_V36},
    {"G703_64K",  IF_TYPE_G703_64K},
    {"G703_2MB",  IF_TYPE_G703_2MB},
    {"QLLC",  IF_TYPE_QLLC},
    {"FASTETHER_FX",  IF_TYPE_FASTETHER_FX},
    {"CHANNEL",  IF_TYPE_CHANNEL},
    {"IEEE80211",  IF_TYPE_IEEE80211},
    {"BM370PARCHAN",  IF_TYPE_IBM370PARCHAN},
    {"ESCON",  IF_TYPE_ESCON},
    {"DLSW",  IF_TYPE_DLSW},
    {"ISDN_S",  IF_TYPE_ISDN_S},
    {"ISDN_U",  IF_TYPE_ISDN_U},
    {"LAP_D",  IF_TYPE_LAP_D},
    {"PSWITCH",  IF_TYPE_IPSWITCH},
    {"RSRB",  IF_TYPE_RSRB},
    {"ATM_LOGICAL",  IF_TYPE_ATM_LOGICAL},
    {"DS0",  IF_TYPE_DS0},
    {"DS0_BUNDLE",  IF_TYPE_DS0_BUNDLE},
    {"BSC",  IF_TYPE_BSC},
    {"ASYNC",  IF_TYPE_ASYNC},
    {"CNR",  IF_TYPE_CNR},
    {"ISO88025R_DTR",  IF_TYPE_ISO88025R_DTR},
    {"EPLRS",  IF_TYPE_EPLRS},
    {"ARAP",  IF_TYPE_ARAP},
    {"PROP_CNLS",  IF_TYPE_PROP_CNLS},
    {"HOSTPAD",  IF_TYPE_HOSTPAD},
    {"ERMPAD",  IF_TYPE_TERMPAD},
    {"FRAMERELAY_MPI",  IF_TYPE_FRAMERELAY_MPI},
    {"X213",  IF_TYPE_X213},
    {"ADSL",  IF_TYPE_ADSL},
    {"RADSL",  IF_TYPE_RADSL},
    {"SDSL",  IF_TYPE_SDSL},
    {"VDSL",  IF_TYPE_VDSL},
    {"ISO88025_CRFPRINT",  IF_TYPE_ISO88025_CRFPRINT},
    {"MYRINET",  IF_TYPE_MYRINET},
    {"VOICE_EM",  IF_TYPE_VOICE_EM},
    {"VOICE_FXO",  IF_TYPE_VOICE_FXO},
    {"VOICE_FXS",  IF_TYPE_VOICE_FXS},
    {"VOICE_ENCAP",  IF_TYPE_VOICE_ENCAP},
    {"VOICE_OVERIP",  IF_TYPE_VOICE_OVERIP},
    {"ATM_DXI",  IF_TYPE_ATM_DXI},
    {"ATM_FUNI",  IF_TYPE_ATM_FUNI},
    {"ATM_IMA",  IF_TYPE_ATM_IMA},
    {"PPPMULTILINKBUNDLE",  IF_TYPE_PPPMULTILINKBUNDLE},
    {"IPOVER_CDLC",  IF_TYPE_IPOVER_CDLC},
    {"IPOVER_CLAW",  IF_TYPE_IPOVER_CLAW},
    {"STACKTOSTACK",  IF_TYPE_STACKTOSTACK},
    {"VIRTUALIPADDRESS",  IF_TYPE_VIRTUALIPADDRESS},
    {"MPC",  IF_TYPE_MPC},
    {"IPOVER_ATM",  IF_TYPE_IPOVER_ATM},
    {"ISO88025_FIBER",  IF_TYPE_ISO88025_FIBER},
    {"TDLC",  IF_TYPE_TDLC},
    {"GIGABITETHERNET",  IF_TYPE_GIGABITETHERNET},
    {"HDLC",  IF_TYPE_HDLC},
    {"LAP_F",  IF_TYPE_LAP_F},
    {"V37",  IF_TYPE_V37},
    {"X25_MLP",  IF_TYPE_X25_MLP},
    {"X25_HUNTGROUP",  IF_TYPE_X25_HUNTGROUP},
    {"TRANSPHDLC",  IF_TYPE_TRANSPHDLC},
    {"INTERLEAVE",  IF_TYPE_INTERLEAVE},
    {"FAST",  IF_TYPE_FAST},
    {"IP",  IF_TYPE_IP},
    {"DOCSCABLE_MACLAYER",  IF_TYPE_DOCSCABLE_MACLAYER},
    {"DOCSCABLE_DOWNSTREAM",  IF_TYPE_DOCSCABLE_DOWNSTREAM},
    {"DOCSCABLE_UPSTREAM",  IF_TYPE_DOCSCABLE_UPSTREAM},
    {"A12MPPSWITCH",  IF_TYPE_A12MPPSWITCH},
    {"TUNNEL",  IF_TYPE_TUNNEL},
    {"COFFEE",  IF_TYPE_COFFEE},
    {"CES",  IF_TYPE_CES},
    {"ATM_SUBINTERFACE",  IF_TYPE_ATM_SUBINTERFACE},
    {"L2_VLAN",  IF_TYPE_L2_VLAN},
    {"L3_IPVLAN",  IF_TYPE_L3_IPVLAN},
    {"L3_IPXVLAN",  IF_TYPE_L3_IPXVLAN},
    {"DIGITALPOWERLINE",  IF_TYPE_DIGITALPOWERLINE},
    {"MEDIAMAILOVERIP",  IF_TYPE_MEDIAMAILOVERIP},
    {"DTM",  IF_TYPE_DTM},
    {"DCN",  IF_TYPE_DCN},
    {"IPFORWARD",  IF_TYPE_IPFORWARD},
    {"MSDSL",  IF_TYPE_MSDSL},
    {"IEEE1394",  IF_TYPE_IEEE1394},
    {"IF_GSN",  IF_TYPE_IF_GSN},
    {"DVBRCC_MACLAYER",  IF_TYPE_DVBRCC_MACLAYER},
    {"DVBRCC_DOWNSTREAM",  IF_TYPE_DVBRCC_DOWNSTREAM},
    {"DVBRCC_UPSTREAM",  IF_TYPE_DVBRCC_UPSTREAM},
    {"ATM_VIRTUAL",  IF_TYPE_ATM_VIRTUAL},
    {"MPLS_TUNNEL",  IF_TYPE_MPLS_TUNNEL},
    {"SRP",  IF_TYPE_SRP},
    {"VOICEOVERATM",  IF_TYPE_VOICEOVERATM},
    {"VOICEOVERFRAMERELAY",  IF_TYPE_VOICEOVERFRAMERELAY},
    {"IDSL",  IF_TYPE_IDSL},
    {"COMPOSITELINK",  IF_TYPE_COMPOSITELINK},
    {"SS7_SIGLINK",  IF_TYPE_SS7_SIGLINK},
    {"PROP_WIRELESS_P2P",  IF_TYPE_PROP_WIRELESS_P2P},
    {"FR_FORWARD",  IF_TYPE_FR_FORWARD},
    {"RFC1483",  IF_TYPE_RFC1483},
    {"USB",  IF_TYPE_USB},
    {"IEEE8023AD_LAG",  IF_TYPE_IEEE8023AD_LAG},
    {"BGP_POLICY_ACCOUNTING",  IF_TYPE_BGP_POLICY_ACCOUNTING},
    {"FRF16_MFR_BUNDLE",  IF_TYPE_FRF16_MFR_BUNDLE},
    {"H323_GATEKEEPER",  IF_TYPE_H323_GATEKEEPER},
    {"H323_PROXY",  IF_TYPE_H323_PROXY},
    {"MPLS",  IF_TYPE_MPLS},
    {"MF_SIGLINK",  IF_TYPE_MF_SIGLINK},
    {"HDSL2",  IF_TYPE_HDSL2},
    {"SHDSL",  IF_TYPE_SHDSL},
    {"DS1_FDL",  IF_TYPE_DS1_FDL},
    {"POS",  IF_TYPE_POS},
    {"DVB_ASI_IN",  IF_TYPE_DVB_ASI_IN},
    {"DVB_ASI_OUT",  IF_TYPE_DVB_ASI_OUT},
    {"PLC",  IF_TYPE_PLC},
    {"NFAS",  IF_TYPE_NFAS},
    {"TR008",  IF_TYPE_TR008},
    {"GR303_RDT",  IF_TYPE_GR303_RDT},
    {"GR303_IDT",  IF_TYPE_GR303_IDT},
    {"ISUP",  IF_TYPE_ISUP},
    {"PROP_DOCS_WIRELESS_MACLAYER",  IF_TYPE_PROP_DOCS_WIRELESS_MACLAYER},
    {"PROP_DOCS_WIRELESS_DOWNSTREAM",  IF_TYPE_PROP_DOCS_WIRELESS_DOWNSTREAM},
    {"PROP_DOCS_WIRELESS_UPSTREAM",  IF_TYPE_PROP_DOCS_WIRELESS_UPSTREAM},
    {"HIPERLAN2",  IF_TYPE_HIPERLAN2},
    {"PROP_BWA_P2MP",  IF_TYPE_PROP_BWA_P2MP},
    {"SONET_OVERHEAD_CHANNEL",  IF_TYPE_SONET_OVERHEAD_CHANNEL},
    {"DIGITAL_WRAPPER_OVERHEAD_CHANNEL",  IF_TYPE_DIGITAL_WRAPPER_OVERHEAD_CHANNEL},
    {"AAL2",  IF_TYPE_AAL2},
    {"RADIO_MAC",  IF_TYPE_RADIO_MAC},
    {"ATM_RADIO",  IF_TYPE_ATM_RADIO},
    {"IMT",  IF_TYPE_IMT},
    {"MVL",  IF_TYPE_MVL},
    {"REACH_DSL",  IF_TYPE_REACH_DSL},
    {"FR_DLCI_ENDPT",  IF_TYPE_FR_DLCI_ENDPT},
    {"ATM_VCI_ENDPT",  IF_TYPE_ATM_VCI_ENDPT},
    {"OPTICAL_CHANNEL",  IF_TYPE_OPTICAL_CHANNEL},
    {"OPTICAL_TRANSPORT",  IF_TYPE_OPTICAL_TRANSPORT},
    };

    const char* name = ""; 
    int count = XtNumber(types);
    for (int i = 0; i<count; i++) {
      if (types[i].value == value) {
        name = types[i].name;
        break;
      }
    }
    return name;
  }

protected:

  const char* getOperationStatus(DWORD value)
  {
    static const ArgT<char> arg[] = {
    {"NON_OPERATIONAL",  MIB_IF_OPER_STATUS_NON_OPERATIONAL},
    // LAN adapter has been disabled, for example because of an address conflict.
 
    {"UNREACHABLE", MIB_IF_OPER_STATUS_UNREACHABLE},
    //WAN adapter that is not connected.
 
    {"DISCONNECTED", MIB_IF_OPER_STATUS_DISCONNECTED},
    // For LAN adapters: network cable disconnected. For WAN adapters: no carrier. 
 
    {"CONNECTING", MIB_IF_OPER_STATUS_CONNECTING},
     //WAN adapter that is in the process of connecting.
 
    {"CONNECTED", MIB_IF_OPER_STATUS_CONNECTED},
    //WAN adapter that is connected to a remote peer.
    {"OPERATIONAL", MIB_IF_OPER_STATUS_OPERATIONAL}
    };

    const char* name = ""; 
    int count = XtNumber(arg);
    for (int i = 0; i<count; i++) {
      if (arg[i].value == value) {
        name = arg[i].name;
        break;
      }
    }
    return name;
  }

public:
  void dump()
  {
    display();
  }
};

}

