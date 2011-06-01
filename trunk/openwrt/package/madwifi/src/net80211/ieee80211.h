/*-
 * Copyright (c) 2001 Atsushi Onoe
 * Copyright (c) 2002-2005 Sam Leffler, Errno Consulting
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: ieee80211.h 4076 2009-07-11 17:20:58Z benoit $
 */
#ifndef _NET80211_IEEE80211_H_
#define _NET80211_IEEE80211_H_

/*
 * 802.11 protocol definitions.
 */

#define	IEEE80211_ADDR_LEN		6		/* size of 802.11 address */
/* is 802.11 address multicast/broadcast? */
#define	IEEE80211_IS_MULTICAST(_a)	(*(_a) & 0x01)

/* IEEE 802.11 PLCP header */
struct ieee80211_plcp_hdr {
	u_int16_t i_sfd;
	u_int8_t i_signal;
	u_int8_t i_service;
	u_int16_t i_length;
	u_int16_t i_crc;
} __packed;

#define IEEE80211_PLCP_SFD      0xF3A0
#define IEEE80211_PLCP_SERVICE  0x00
#define IEEE80211_PLCP_SERVICE_LOCKED	0x04
#define IEEE80211_PLCL_SERVICE_PBCC	0x08
#define IEEE80211_PLCP_SERVICE_LENEXT5	0x20
#define IEEE80211_PLCP_SERVICE_LENEXT6	0x40
#define IEEE80211_PLCP_SERVICE_LENEXT7	0x80

/*
 * generic definitions for IEEE 802.11 frames
 */
struct ieee80211_frame {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_addr1[IEEE80211_ADDR_LEN];
	u_int8_t i_addr2[IEEE80211_ADDR_LEN];
	u_int8_t i_addr3[IEEE80211_ADDR_LEN];
	u_int8_t i_seq[2];
	/* possibly followed by addr4[IEEE80211_ADDR_LEN]; */
	/* see below */
} __packed;

struct ieee80211_qosframe {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_addr1[IEEE80211_ADDR_LEN];
	u_int8_t i_addr2[IEEE80211_ADDR_LEN];
	u_int8_t i_addr3[IEEE80211_ADDR_LEN];
	u_int8_t i_seq[2];
	u_int8_t i_qos[2];
	/* possibly followed by addr4[IEEE80211_ADDR_LEN]; */
	/* see below */
} __packed;

struct ieee80211_qoscntl {
	u_int8_t i_qos[2];
};

struct ieee80211_frame_addr4 {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_addr1[IEEE80211_ADDR_LEN];
	u_int8_t i_addr2[IEEE80211_ADDR_LEN];
	u_int8_t i_addr3[IEEE80211_ADDR_LEN];
	u_int8_t i_seq[2];
	u_int8_t i_addr4[IEEE80211_ADDR_LEN];
} __packed;


struct ieee80211_qosframe_addr4 {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_addr1[IEEE80211_ADDR_LEN];
	u_int8_t i_addr2[IEEE80211_ADDR_LEN];
	u_int8_t i_addr3[IEEE80211_ADDR_LEN];
	u_int8_t i_seq[2];
	u_int8_t i_addr4[IEEE80211_ADDR_LEN];
	u_int8_t i_qos[2];
} __packed;

struct ieee80211_ctlframe_addr2 {
	u_int8_t i_fc[2];
	__le16 i_aidordur; /* AID or duration */
	u_int8_t i_addr1[IEEE80211_ADDR_LEN];
	u_int8_t i_addr2[IEEE80211_ADDR_LEN];
} __packed;

#define	IEEE80211_FC0_VERSION_MASK		0x03
#define	IEEE80211_FC0_VERSION_SHIFT		0
#define	IEEE80211_FC0_VERSION_0			0x00
#define	IEEE80211_FC0_TYPE_MASK			0x0c
#define	IEEE80211_FC0_TYPE_SHIFT		2
#define	IEEE80211_FC0_TYPE_MGT			0x00
#define	IEEE80211_FC0_TYPE_CTL			0x04
#define	IEEE80211_FC0_TYPE_DATA			0x08

#define	IEEE80211_FC0_SUBTYPE_MASK		0xf0
#define	IEEE80211_FC0_SUBTYPE_SHIFT		4
/* for TYPE_MGT */
#define	IEEE80211_FC0_SUBTYPE_ASSOC_REQ		0x00
#define	IEEE80211_FC0_SUBTYPE_ASSOC_RESP	0x10
#define	IEEE80211_FC0_SUBTYPE_REASSOC_REQ	0x20
#define	IEEE80211_FC0_SUBTYPE_REASSOC_RESP	0x30
#define	IEEE80211_FC0_SUBTYPE_PROBE_REQ		0x40
#define	IEEE80211_FC0_SUBTYPE_PROBE_RESP	0x50
#define	IEEE80211_FC0_SUBTYPE_BEACON		0x80
#define	IEEE80211_FC0_SUBTYPE_ATIM		0x90
#define	IEEE80211_FC0_SUBTYPE_DISASSOC		0xa0
#define	IEEE80211_FC0_SUBTYPE_AUTH		0xb0
#define	IEEE80211_FC0_SUBTYPE_DEAUTH		0xc0
#define IEEE80211_FC0_SUBTYPE_ACTION		0xd0
/* for TYPE_CTL */
#define	IEEE80211_FC0_SUBTYPE_BAR		0x80
#define	IEEE80211_FC0_SUBTYPE_BA		0x90
#define	IEEE80211_FC0_SUBTYPE_PS_POLL		0xa0
#define	IEEE80211_FC0_SUBTYPE_RTS		0xb0
#define	IEEE80211_FC0_SUBTYPE_CTS		0xc0
#define	IEEE80211_FC0_SUBTYPE_ACK		0xd0
#define	IEEE80211_FC0_SUBTYPE_CF_END		0xe0
#define	IEEE80211_FC0_SUBTYPE_CF_END_ACK	0xf0
/* for TYPE_DATA (bit combination) */
#define	IEEE80211_FC0_SUBTYPE_DATA		0x00
#define	IEEE80211_FC0_SUBTYPE_CF_ACK		0x10
#define	IEEE80211_FC0_SUBTYPE_CF_POLL		0x20
#define	IEEE80211_FC0_SUBTYPE_CF_ACPL		0x30
#define	IEEE80211_FC0_SUBTYPE_NULL		0x40
#define	IEEE80211_FC0_SUBTYPE_CFACK		0x50
#define	IEEE80211_FC0_SUBTYPE_CFPOLL		0x60
#define	IEEE80211_FC0_SUBTYPE_CF_ACK_CF_ACK	0x70
#define	IEEE80211_FC0_SUBTYPE_QOS		0x80
#define	IEEE80211_FC0_SUBTYPE_QOS_NULL		0xc0

#define	IEEE80211_FC1_DIR_MASK			0x03
#define	IEEE80211_FC1_DIR_NODS			0x00	/* STA->STA */
#define	IEEE80211_FC1_DIR_TODS			0x01	/* STA->AP  */
#define	IEEE80211_FC1_DIR_FROMDS		0x02	/* AP ->STA */
#define	IEEE80211_FC1_DIR_DSTODS		0x03	/* AP ->AP  */

#define	IEEE80211_IS_DSTODS(wh) \
	(((wh)->i_fc[1] & IEEE80211_FC1_DIR_MASK) == IEEE80211_FC1_DIR_DSTODS)

#define	IEEE80211_FC1_MORE_FRAG			0x04
#define	IEEE80211_FC1_RETRY			0x08
#define	IEEE80211_FC1_PWR_MGT			0x10
#define	IEEE80211_FC1_MORE_DATA			0x20
#define	IEEE80211_FC1_PROT			0x40
#define	IEEE80211_FC1_ORDER			0x80

#define	IEEE80211_SEQ_FRAG_MASK			0x000f
#define	IEEE80211_SEQ_FRAG_SHIFT		0
#define	IEEE80211_SEQ_SEQ_MASK			0xfff0
#define	IEEE80211_SEQ_SEQ_SHIFT			4
#define	IEEE80211_SEQ_RANGE			4096

#define	IEEE80211_SEQ_LEQ(a,b)	((int)((a)-(b)) <= 0)

#define	IEEE80211_NWID_LEN			32
#define	IEEE80211_MESHID_LEN			32

#define	IEEE80211_QOS_TXOP			0x00ff
/* bit 8 is reserved */
#define	IEEE80211_QOS_AMSDU			0x80
#define	IEEE80211_QOS_AMSDU_S			7
#define	IEEE80211_QOS_ACKPOLICY			0x60
#define	IEEE80211_QOS_ACKPOLICY_S		5
#define	IEEE80211_QOS_ACKPOLICY_NOACK		0x20	/* No ACK required */
#define	IEEE80211_QOS_ACKPOLICY_BA		0x60	/* Block ACK */
#define	IEEE80211_QOS_EOSP			0x10	/* EndOfService Period*/
#define	IEEE80211_QOS_EOSP_S			4
#define	IEEE80211_QOS_TID			0x0f

#define IEEE80211_FRM_HAS_BODY(_wh)			\
	(((_wh)->i_fc[0] & IEEE80211_FC0_TYPE_MASK) !=	\
			IEEE80211_FC0_TYPE_CTL)

/*
 * Country/Region Codes from MS WINNLS.H
 * Numbering from ISO 3166
 * XXX belongs elsewhere
 */
enum CountryCode {
	CTRY_ALBANIA              = 8,       /* Albania */
	CTRY_ALGERIA              = 12,      /* Algeria */
	CTRY_ARGENTINA            = 32,      /* Argentina */
	CTRY_ARMENIA              = 51,      /* Armenia */
	CTRY_AUSTRALIA            = 36,      /* Australia */
	CTRY_AUSTRIA              = 40,      /* Austria */
	CTRY_AZERBAIJAN           = 31,      /* Azerbaijan */
	CTRY_BAHRAIN              = 48,      /* Bahrain */
	CTRY_BELARUS              = 112,     /* Belarus */
	CTRY_BELGIUM              = 56,      /* Belgium */
	CTRY_BELIZE               = 84,      /* Belize */
	CTRY_BOLIVIA              = 68,      /* Bolivia */
	CTRY_BRAZIL               = 76,      /* Brazil */
	CTRY_BRUNEI_DARUSSALAM    = 96,      /* Brunei Darussalam */
	CTRY_BULGARIA             = 100,     /* Bulgaria */
	CTRY_CANADA               = 124,     /* Canada */
	CTRY_CHILE                = 152,     /* Chile */
	CTRY_CHINA                = 156,     /* People's Republic of China */
	CTRY_COLOMBIA             = 170,     /* Colombia */
	CTRY_COSTA_RICA           = 188,     /* Costa Rica */
	CTRY_CROATIA              = 191,     /* Croatia */
	CTRY_CYPRUS               = 196,
	CTRY_CZECH                = 203,     /* Czech Republic */
	CTRY_DENMARK              = 208,     /* Denmark */
	CTRY_DOMINICAN_REPUBLIC   = 214,     /* Dominican Republic */
	CTRY_ECUADOR              = 218,     /* Ecuador */
	CTRY_EGYPT                = 818,     /* Egypt */
	CTRY_EL_SALVADOR          = 222,     /* El Salvador */
	CTRY_ESTONIA              = 233,     /* Estonia */
	CTRY_FAEROE_ISLANDS       = 234,     /* Faeroe Islands */
	CTRY_FINLAND              = 246,     /* Finland */
	CTRY_FRANCE               = 250,     /* France */
	CTRY_FRANCE2              = 255,     /* France2 */
	CTRY_GEORGIA              = 268,     /* Georgia */
	CTRY_GERMANY              = 276,     /* Germany */
	CTRY_GREECE               = 300,     /* Greece */
	CTRY_GUATEMALA            = 320,     /* Guatemala */
	CTRY_HONDURAS             = 340,     /* Honduras */
	CTRY_HONG_KONG            = 344,     /* Hong Kong S.A.R., P.R.C. */
	CTRY_HUNGARY              = 348,     /* Hungary */
	CTRY_ICELAND              = 352,     /* Iceland */
	CTRY_INDIA                = 356,     /* India */
	CTRY_INDONESIA            = 360,     /* Indonesia */
	CTRY_IRAN                 = 364,     /* Iran */
	CTRY_IRAQ                 = 368,     /* Iraq */
	CTRY_IRELAND              = 372,     /* Ireland */
	CTRY_ISRAEL               = 376,     /* Israel */
	CTRY_ITALY                = 380,     /* Italy */
	CTRY_JAMAICA              = 388,     /* Jamaica */
	CTRY_JAPAN                = 392,     /* Japan */
	CTRY_JAPAN1               = 393,     /* Japan (JP1) */
	CTRY_JAPAN2               = 394,     /* Japan (JP0) */
	CTRY_JAPAN3               = 395,     /* Japan (JP1-1) */
	CTRY_JAPAN4               = 396,     /* Japan (JE1) */
	CTRY_JAPAN5               = 397,     /* Japan (JE2) */
	CTRY_JAPAN6               = 399,	 /* Japan (JP6) */
	CTRY_JAPAN7               = 900,	 /* Japan */
	CTRY_JAPAN8               = 901,	 /* Japan */
	CTRY_JAPAN9               = 902,	 /* Japan */
	CTRY_JAPAN10	      = 903,	 /* Japan */
	CTRY_JAPAN11	      = 904,	 /* Japan */
	CTRY_JAPAN12	      = 905,	 /* Japan */
	CTRY_JAPAN13	      = 906,	 /* Japan */
	CTRY_JAPAN14	      = 907,	 /* Japan */
	CTRY_JAPAN15	      = 908,	 /* Japan */
	CTRY_JAPAN16	      = 909,	 /* Japan */
	CTRY_JAPAN17	      = 910,	 /* Japan */
	CTRY_JAPAN18	      = 911,	 /* Japan */
	CTRY_JAPAN19	      = 912,	 /* Japan */
	CTRY_JAPAN20	      = 913,	 /* Japan */
	CTRY_JAPAN21	      = 914,	 /* Japan */
	CTRY_JAPAN22	      = 915,	 /* Japan */
	CTRY_JAPAN23	      = 916,	 /* Japan */
	CTRY_JAPAN24	      = 917,	 /* Japan */
	CTRY_JAPAN25	      = 918,	 /* Japan */
	CTRY_JAPAN26	      = 919,	 /* Japan */
	CTRY_JAPAN27	      = 920,	 /* Japan */
	CTRY_JAPAN28	      = 921,	 /* Japan */
	CTRY_JAPAN29	      = 922,	 /* Japan */
	CTRY_JAPAN30	      = 923,	 /* Japan */
	CTRY_JAPAN31	      = 924,	 /* Japan */
	CTRY_JAPAN32	      = 925,	 /* Japan */
	CTRY_JAPAN33	      = 926,	 /* Japan */
	CTRY_JAPAN34	      = 927,	 /* Japan */
	CTRY_JAPAN35	      = 928,	 /* Japan */
	CTRY_JAPAN36	      = 929,	 /* Japan */
	CTRY_JAPAN37	      = 930,	 /* Japan */
	CTRY_JAPAN38	      = 931,	 /* Japan */
	CTRY_JAPAN39	      = 932,	 /* Japan */
	CTRY_JAPAN40	      = 933,	 /* Japan */
	CTRY_JAPAN41	      = 934,	 /* Japan */
	CTRY_JAPAN42	      = 935,	 /* Japan */
	CTRY_JAPAN43	      = 936,	 /* Japan */
	CTRY_JAPAN44	      = 937,	 /* Japan */
	CTRY_JAPAN45	      = 938,	 /* Japan */
	CTRY_JAPAN46	      = 939,	 /* Japan */
	CTRY_JAPAN47	      = 940,	 /* Japan */
	CTRY_JAPAN48	      = 941,	 /* Japan */
	CTRY_JORDAN               = 400,     /* Jordan */
	CTRY_KAZAKHSTAN           = 398,     /* Kazakhstan */
	CTRY_KENYA                = 404,     /* Kenya */
	CTRY_KOREA_NORTH          = 408,     /* North Korea */
	CTRY_KOREA_ROC            = 410,     /* South Korea */
	CTRY_KOREA_ROC2           = 411,     /* South Korea */
	CTRY_KUWAIT               = 414,     /* Kuwait */
	CTRY_LATVIA               = 428,     /* Latvia */
	CTRY_LEBANON              = 422,     /* Lebanon */
	CTRY_LIBYA                = 434,     /* Libya */
	CTRY_LIECHTENSTEIN        = 438,     /* Liechtenstein */
	CTRY_LITHUANIA            = 440,     /* Lithuania */
	CTRY_LUXEMBOURG           = 442,     /* Luxembourg */
	CTRY_MACAU                = 446,     /* Macau */
	CTRY_MACEDONIA            = 807,     /* the Former Yugoslav Republic of Macedonia */
	CTRY_MALAYSIA             = 458,     /* Malaysia */
	CTRY_MEXICO               = 484,     /* Mexico */
	CTRY_MONACO               = 492,     /* Principality of Monaco */
	CTRY_MOROCCO              = 504,     /* Morocco */
	CTRY_NETHERLANDS          = 528,     /* Netherlands */
	CTRY_NEW_ZEALAND          = 554,     /* New Zealand */
	CTRY_NICARAGUA            = 558,     /* Nicaragua */
	CTRY_NORWAY               = 578,     /* Norway */
	CTRY_OMAN                 = 512,     /* Oman */
	CTRY_PAKISTAN             = 586,     /* Islamic Republic of Pakistan */
	CTRY_PANAMA               = 591,     /* Panama */
	CTRY_PARAGUAY             = 600,     /* Paraguay */
	CTRY_PERU                 = 604,     /* Peru */
	CTRY_PHILIPPINES          = 608,     /* Republic of the Philippines */
	CTRY_POLAND               = 616,     /* Poland */
	CTRY_PORTUGAL             = 620,     /* Portugal */
	CTRY_PUERTO_RICO          = 630,     /* Puerto Rico */
	CTRY_QATAR                = 634,     /* Qatar */
	CTRY_ROMANIA              = 642,     /* Romania */
	CTRY_RUSSIA               = 643,     /* Russia */
	CTRY_SAUDI_ARABIA         = 682,     /* Saudi Arabia */
	CTRY_SINGAPORE            = 702,     /* Singapore */
	CTRY_SLOVAKIA             = 703,     /* Slovak Republic */
	CTRY_SLOVENIA             = 705,     /* Slovenia */
	CTRY_SOUTH_AFRICA         = 710,     /* South Africa */
	CTRY_SPAIN                = 724,     /* Spain */
	CTRY_SWEDEN               = 752,     /* Sweden */
	CTRY_SWITZERLAND          = 756,     /* Switzerland */
	CTRY_SYRIA                = 760,     /* Syria */
	CTRY_TAIWAN               = 158,     /* Taiwan */
	CTRY_THAILAND             = 764,     /* Thailand */
	CTRY_TRINIDAD_Y_TOBAGO    = 780,     /* Trinidad y Tobago */
	CTRY_TUNISIA              = 788,     /* Tunisia */
	CTRY_TURKEY               = 792,     /* Turkey */
	CTRY_UAE                  = 784,     /* U.A.E. */
	CTRY_UKRAINE              = 804,     /* Ukraine */
	CTRY_UNITED_KINGDOM       = 826,     /* United Kingdom */
	CTRY_UNITED_STATES        = 840,     /* United States */
	CTRY_UNITED_STATES_FCC49  = 842,     /* United States (Public Safety)*/
	CTRY_URUGUAY              = 858,     /* Uruguay */
	CTRY_UZBEKISTAN           = 860,     /* Uzbekistan */
	CTRY_VENEZUELA            = 862,     /* Venezuela */
	CTRY_VIET_NAM             = 704,     /* Viet Nam */
	CTRY_YEMEN                = 887,     /* Yemen */
	CTRY_ZIMBABWE             = 716      /* Zimbabwe */
};

/* 
 * Generic information element
 */
struct ieee80211_ie {
	u_int8_t id;
	u_int8_t len;
	u_int8_t info[0];
} __packed;

/* 
 * Country information element.
 */
#define IEEE80211_COUNTRY_MAX_TRIPLETS (83)
struct ieee80211_ie_country {
	u_int8_t country_id;
	u_int8_t country_len;
	u_int8_t country_str[3];
	u_int8_t country_triplet[IEEE80211_COUNTRY_MAX_TRIPLETS * 3];
} __packed;

/*
 * Power Constraint information element.
 */
struct ieee80211_ie_pwrcnstr {
	u_int8_t pc_id;			/* IEEE80211_ELEMID_PWRCNSTR */
	u_int8_t pc_len;		/* == 2 */
	u_int8_t pc_lpc;		/* Local Power Constraint [dB] */
} __packed;

/*
 * Power Capability information element.
 */
struct ieee80211_ie_pwrcap {
	u_int8_t pc_id;			/* IEEE80211_ELEMID_PWRCAP */
	u_int8_t pc_len;		/* == 2 */
	int8_t pc_mintxpow;		/* Minimum Transmit Power Capability [dBm] */
	int8_t pc_maxtxpow;		/* Maximum Transmit Power Capability [dBm] */
} __packed;

/*
 * Supported Channels information element.
 */
#define IEEE80211_SUPPCHAN_MAX_PAIRS (127)
struct ieee80211_ie_sc {
	u_int8_t sc_id;			/* IEEE80211_ELEMID_SUPPCHAN */
	u_int8_t sc_len;		/* == 2 * number of sc_subband elements */
	struct {
		u_int8_t sc_first;	/* First Channel Number */
		u_int8_t sc_number;	/* Number of Channels */
	} __packed sc_subband[IEEE80211_SUPPCHAN_MAX_PAIRS];
} __packed;

/*
 * Channel Switch Announcement information element.
 */
struct ieee80211_ie_csa {
	u_int8_t csa_id;	/* IEEE80211_ELEMID_CHANSWITCHANN */
	u_int8_t csa_len;	/* == 3 */
	u_int8_t csa_mode;	/* Channel Switch Mode: 1 == stop transmission until CS */
	u_int8_t csa_chan;	/* New Channel Number */
	u_int8_t csa_count;	/* TBTTs until Channel Switch happens */
} __packed;

/* for Action Category. Table 19a in 802.11h $7.3.1.11 */
#define IEEE80211_ACTION_SPECTRUM_MANAGEMENT 0

/* for Spectrum Management Actions. Table 20e in 802.11h $7.4.1 */
#define IEEE80211_ACTION_S_MEASUREMENT_REQUEST 0
#define IEEE80211_ACTION_S_MEASUREMENT_REPORT  1
#define IEEE80211_ACTION_S_TPC_REQUEST         2
#define IEEE80211_ACTION_S_TPC_REPORT          3
#define IEEE80211_ACTION_S_CHANSWITCHANN       4

/* for csa_mode. It must be either 0 or 1. 1 means that the receiver shall stop
 * sending until CS. 0 imposes no requirement. See 7.3.2.20 */

#define IEEE80211_CSA_CAN_STOP_TX	0
#define IEEE80211_CSA_MUST_STOP_TX	1

/* minimal Channel Switch Count in the initial announcement */
#define IEEE80211_CSA_PROTECTION_PERIOD 3

/* maximum allowed deviance of measurement of intervals between CSA in Beacons */
#define IEEE80211_CSA_SANITY_THRESHOLD 100


/* does frame have QoS sequence control data */
#define	IEEE80211_QOS_HAS_SEQ(wh) \
	(((wh)->i_fc[0] & \
	  (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_QOS)) == \
	  (IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_QOS))

#define WME_QOSINFO_COUNT	0x0f  /* Mask for Param Set Count field */
/*
 * WME/802.11e information element.
 */
struct ieee80211_ie_wme {
	u_int8_t wme_id;		/* IEEE80211_ELEMID_VENDOR */
	u_int8_t wme_len;	/* length in bytes */
	u_int8_t wme_oui[3];	/* 0x00, 0x50, 0xf2 */
	u_int8_t wme_type;	/* OUI type */
	u_int8_t wme_subtype;	/* OUI subtype */
	u_int8_t wme_version;	/* spec revision */
	u_int8_t wme_info;	/* QoS info */
} __packed;

/*
 * WME/802.11e Tspec Element
 */
struct ieee80211_wme_tspec {
	u_int8_t ts_id;
	u_int8_t ts_len;
	u_int8_t ts_oui[3];
	u_int8_t ts_oui_type;
	u_int8_t ts_oui_subtype;
	u_int8_t ts_version;
	u_int8_t ts_tsinfo[3];
	u_int8_t ts_nom_msdu[2];
	u_int8_t ts_max_msdu[2];
	u_int8_t ts_min_svc[4];
	u_int8_t ts_max_svc[4];
	u_int8_t ts_inactv_intv[4];
	u_int8_t ts_susp_intv[4];
	u_int8_t ts_start_svc[4];
	u_int8_t ts_min_rate[4];
	u_int8_t ts_mean_rate[4];
	u_int8_t ts_max_burst[4];
	u_int8_t ts_min_phy[4];
	u_int8_t ts_peak_rate[4];
	u_int8_t ts_delay[4];
	u_int8_t ts_surplus[2];
	u_int8_t ts_medium_time[2];
} __packed;

/*
 * WME AC parameter field
 */

struct ieee80211_wme_acparams {
	u_int8_t acp_aci_aifsn;
	u_int8_t acp_logcwminmax;
	u_int16_t acp_txop;
} __packed;

#define IEEE80211_WME_PARAM_LEN 24
#define WME_NUM_AC		4	/* 4 AC categories */
#define	WME_NUM_TID		16	/* 16 tids */

#define WME_PARAM_ACI		0x60	/* Mask for ACI field */
#define WME_PARAM_ACI_S		5	/* Shift for ACI field */
#define WME_PARAM_ACM		0x10	/* Mask for ACM bit */
#define WME_PARAM_ACM_S		4	/* Shift for ACM bit */
#define WME_PARAM_AIFSN		0x0f	/* Mask for aifsn field */
#define WME_PARAM_AIFSN_S	0	/* Shift for aifsn field */
#define WME_PARAM_LOGCWMIN	0x0f	/* Mask for CwMin field (in log) */
#define WME_PARAM_LOGCWMIN_S	0	/* Shift for CwMin field */
#define WME_PARAM_LOGCWMAX	0xf0	/* Mask for CwMax field (in log) */
#define WME_PARAM_LOGCWMAX_S	4	/* Shift for CwMax field */

#define WME_AC_TO_TID(_ac) (       \
	((_ac) == WME_AC_VO) ? 6 : \
	((_ac) == WME_AC_VI) ? 5 : \
	((_ac) == WME_AC_BK) ? 1 : \
	0)

#define TID_TO_WME_AC(_tid) (      \
	((_tid) == 0 || (_tid) == 3) ? WME_AC_BE : \
	((_tid) < 3) ? WME_AC_BK : \
	((_tid) < 6) ? WME_AC_VI : \
	WME_AC_VO)

/*
 * WME Parameter Element
 */

struct ieee80211_wme_param {
	u_int8_t param_id;
	u_int8_t param_len;
	u_int8_t param_oui[3];
	u_int8_t param_oui_type;
	u_int8_t param_oui_sybtype;
	u_int8_t param_version;
	u_int8_t param_qosInfo;
#define	WME_QOSINFO_COUNT	0x0f	/* Mask for param count field */
	u_int8_t param_reserved;
	struct ieee80211_wme_acparams	params_acParams[WME_NUM_AC];
} __packed;

/*
 * WME U-APSD qos info field defines
 */
#define WME_CAPINFO_UAPSD_EN			0x00000080
#define WME_CAPINFO_UAPSD_VO			0x00000001
#define WME_CAPINFO_UAPSD_VI			0x00000002
#define WME_CAPINFO_UAPSD_BK			0x00000004
#define WME_CAPINFO_UAPSD_BE			0x00000008
#define WME_CAPINFO_UAPSD_ACFLAGS_SHIFT		0
#define WME_CAPINFO_UAPSD_ACFLAGS_MASK		0xF
#define WME_CAPINFO_UAPSD_MAXSP_SHIFT		5
#define WME_CAPINFO_UAPSD_MAXSP_MASK		0x3
#define WME_CAPINFO_IE_OFFSET			8
#define WME_UAPSD_MAXSP(_qosinfo)					\
		(((_qosinfo) >> WME_CAPINFO_UAPSD_MAXSP_SHIFT) & 	\
		 WME_CAPINFO_UAPSD_MAXSP_MASK)
#define WME_UAPSD_AC_ENABLED(_ac, _qosinfo)				\
		((1 << (3 - (_ac))) & (					\
		 ((_qosinfo) >> WME_CAPINFO_UAPSD_ACFLAGS_SHIFT) &	\
		 WME_CAPINFO_UAPSD_ACFLAGS_MASK))

/*
 * Atheros Advanced Capability information element.
 */
struct ieee80211_ie_athAdvCap {
	u_int8_t athAdvCap_id;		/* IEEE80211_ELEMID_VENDOR */
	u_int8_t athAdvCap_len;		/* length in bytes */
	u_int8_t athAdvCap_oui[3];	/* 0x00, 0x03, 0x7f */
	u_int8_t athAdvCap_type;	/* OUI type */
	u_int8_t athAdvCap_subtype;	/* OUI subtype */
	u_int8_t athAdvCap_version;	/* spec revision */
	u_int8_t athAdvCap_capability;	/* Capability info */
	u_int16_t athAdvCap_defKeyIndex;
} __packed;

#define	IEEE80211_A_HT_MIMOPWRSAVE_ENA		0x01	/* PS enabled */
#define	IEEE80211_A_HT_MIMOPWRSAVE_MODE		0x02
#define	IEEE80211_A_HT_MIMOPWRSAVE_MODE_S	1
#define	IEEE80211_A_HT_MIMOPWRSAVE_DYNAMIC	0x02	/* Dynamic Mode */
#define	IEEE80211_A_HT_MIMOPWRSAVE_STATIC	0x00	/* no SM packets */
/* bits 2-7 reserved */

/* Block Ack actions */
#define IEEE80211_ACTION_BA_ADDBA_REQUEST       0   /* ADDBA request */
#define IEEE80211_ACTION_BA_ADDBA_RESPONSE      1   /* ADDBA response */
#define IEEE80211_ACTION_BA_DELBA	        2   /* DELBA */

/* Block Ack Parameter Set */
#define	IEEE80211_BAPS_BUFSIZ	0xffc0		/* buffer size */
#define	IEEE80211_BAPS_BUFSIZ_S	6
#define	IEEE80211_BAPS_TID	0x003c		/* TID */
#define	IEEE80211_BAPS_TID_S	2
#define	IEEE80211_BAPS_POLICY	0x0002		/* block ack policy */
#define	IEEE80211_BAPS_POLICY_S	1

#define	IEEE80211_BAPS_POLICY_DELAYED	(0<<IEEE80211_BAPS_POLICY_S)
#define	IEEE80211_BAPS_POLICY_IMMEDIATE	(1<<IEEE80211_BAPS_POLICY_S)

/* Block Ack Sequence Control */
#define	IEEE80211_BASEQ_START	0xfff0		/* starting seqnum */
#define	IEEE80211_BASEQ_START_S	4
#define	IEEE80211_BASEQ_FRAG	0x000f		/* fragment number */
#define	IEEE80211_BASEQ_FRAG_S	0

/* Delayed Block Ack Parameter Set */
#define	IEEE80211_DELBAPS_TID	0xf000		/* TID */
#define	IEEE80211_DELBAPS_TID_S	12
#define	IEEE80211_DELBAPS_INIT	0x0800		/* initiator */
#define	IEEE80211_DELBAPS_INIT_S 11

/*
 * Atheros XR information element.
 */
struct ieee80211_xr_param {
	u_int8_t param_id;
	u_int8_t param_len;
	u_int8_t param_oui[3];
	u_int8_t param_oui_type;
	u_int8_t param_oui_sybtype;
	u_int8_t param_version;
	u_int8_t param_Info;
	u_int8_t param_base_bssid[IEEE80211_ADDR_LEN];
	u_int8_t param_xr_bssid[IEEE80211_ADDR_LEN];
	u_int16_t param_xr_beacon_interval;
	u_int8_t param_base_ath_capability;
	u_int8_t param_xr_ath_capability;
} __packed;

/* Atheros capabilities */
#define IEEE80211_ATHC_TURBOP	0x0001		/* Turbo Prime */
#define IEEE80211_ATHC_COMP	0x0002		/* Compression */
#define IEEE80211_ATHC_FF	0x0004		/* Fast Frames */
#define IEEE80211_ATHC_XR	0x0008		/* Xtended Range support */
#define IEEE80211_ATHC_AR	0x0010		/* Advanced Radar support */
#define IEEE80211_ATHC_BURST	0x0020		/* Bursting - not negotiated */
#define IEEE80211_ATHC_WME	0x0040		/* CWMin tuning */
#define IEEE80211_ATHC_BOOST	0x0080		/* Boost */

/*
 * Management Notification Frame
 */
struct ieee80211_mnf {
	u_int8_t mnf_category;
	u_int8_t mnf_action;
	u_int8_t mnf_dialog;
	u_int8_t mnf_status;
} __packed;
#define	MNF_SETUP_REQ	0
#define	MNF_SETUP_RESP	1
#define	MNF_TEARDOWN	2

/*
 * Control frames.
 */
struct ieee80211_frame_min {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_addr1[IEEE80211_ADDR_LEN];
	u_int8_t i_addr2[IEEE80211_ADDR_LEN];
	/* FCS */
} __packed;

struct ieee80211_frame_rts {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_ra[IEEE80211_ADDR_LEN];
	u_int8_t i_ta[IEEE80211_ADDR_LEN];
	/* FCS */
} __packed;

struct ieee80211_frame_cts {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_ra[IEEE80211_ADDR_LEN];
	/* FCS */
} __packed;

struct ieee80211_frame_ack {
	u_int8_t i_fc[2];
	__le16 i_dur;
	u_int8_t i_ra[IEEE80211_ADDR_LEN];
	/* FCS */
} __packed;

struct ieee80211_frame_pspoll {
	u_int8_t i_fc[2];
	u_int8_t i_aid[2];
	u_int8_t i_bssid[IEEE80211_ADDR_LEN];
	u_int8_t i_ta[IEEE80211_ADDR_LEN];
	/* FCS */
} __packed;

struct ieee80211_frame_cfend {		/* NB: also CF-End+CF-Ack */
	u_int8_t i_fc[2];
	__le16 i_dur;	/* should be zero */
	u_int8_t i_ra[IEEE80211_ADDR_LEN];
	u_int8_t i_bssid[IEEE80211_ADDR_LEN];
	/* FCS */
} __packed;

/*
 * BEACON management packets
 *
 *	octet timestamp[8]
 *	octet beacon interval[2]
 *	octet capability information[2]
 *	information element
 *		octet elemid
 *		octet length
 *		octet information[length]
 */

typedef u_int8_t *ieee80211_mgt_beacon_t;

#define	IEEE80211_BEACON_INTERVAL(beacon) \
	((beacon)[8] | ((beacon)[9] << 8))
#define	IEEE80211_BEACON_CAPABILITY(beacon) \
	((beacon)[10] | ((beacon)[11] << 8))

#define	IEEE80211_CAPINFO_ESS			0x0001
#define	IEEE80211_CAPINFO_IBSS			0x0002
#define	IEEE80211_CAPINFO_CF_POLLABLE		0x0004
#define	IEEE80211_CAPINFO_CF_POLLREQ		0x0008
#define	IEEE80211_CAPINFO_PRIVACY		0x0010
#define	IEEE80211_CAPINFO_SHORT_PREAMBLE	0x0020
#define	IEEE80211_CAPINFO_PBCC			0x0040
#define	IEEE80211_CAPINFO_CHNL_AGILITY		0x0080
/* bits 8-9 are reserved (8 now for spectrum management) */
#define IEEE80211_CAPINFO_SPECTRUM_MGMT		0x0100
#define	IEEE80211_CAPINFO_SHORT_SLOTTIME	0x0400
#define	IEEE80211_CAPINFO_RSN			0x0800
/* bit 12 is reserved */
#define	IEEE80211_CAPINFO_DSSSOFDM		0x2000
/* bits 14-15 are reserved */

/*
 * 802.11i/WPA information element (maximally sized).
 */
struct ieee80211_ie_wpa {
	u_int8_t wpa_id;			/* IEEE80211_ELEMID_VENDOR */
	u_int8_t wpa_len;		/* length in bytes */
	u_int8_t wpa_oui[3];		/* 0x00, 0x50, 0xf2 */
	u_int8_t wpa_type;		/* OUI type */
	u_int16_t wpa_version;		/* spec revision */
	u_int32_t wpa_mcipher[1];	/* multicast/group key cipher */
	u_int16_t wpa_uciphercnt;	/* # pairwise key ciphers */
	u_int32_t wpa_uciphers[8];	/* ciphers */
	u_int16_t wpa_authselcnt;	/* authentication selector cnt*/
	u_int32_t wpa_authsels[8];	/* selectors */
	u_int16_t wpa_caps;		/* 802.11i capabilities */
	u_int16_t wpa_pmkidcnt;		/* 802.11i pmkid count */
	u_int16_t wpa_pmkids[8];	/* 802.11i pmkids */
} __packed;

/*
 * 802.11n HT Capability IE
 * NB: these reflect D1.10 
 */
struct ieee80211_ie_htcap {
	uint8_t		hc_id;			/* element ID */
	uint8_t		hc_len;			/* length in bytes */
	uint16_t	hc_cap;			/* HT caps (see below) */
	uint8_t		hc_param;		/* HT params (see below) */
	uint8_t 	hc_mcsset[16]; 		/* supported MCS set */
	uint16_t	hc_extcap;		/* extended HT capabilities */
	uint32_t	hc_txbf;		/* txbf capabilities */
	uint8_t		hc_antenna;		/* antenna capabilities */
} __packed;

/* HT capability flags (ht_cap) */
#define	IEEE80211_HTCAP_LDPC		0x0001	/* LDPC supported */
#define	IEEE80211_HTCAP_CHWIDTH40	0x0002	/* 20/40 supported */
#define	IEEE80211_HTCAP_SMPS		0x000c	/* SM Power Save mode */
#define	IEEE80211_HTCAP_SMPS_OFF	0x000c	/* disabled */
#define	IEEE80211_HTCAP_SMPS_DYNAMIC	0x0004	/* send RTS first */
/* NB: SMPS value 2 is reserved */
#define	IEEE80211_HTCAP_SMPS_ENA	0x0000	/* enabled (static mode) */
#define	IEEE80211_HTCAP_GREENFIELD	0x0010	/* Greenfield supported */
#define	IEEE80211_HTCAP_SHORTGI20	0x0020	/* Short GI in 20MHz */
#define	IEEE80211_HTCAP_SHORTGI40	0x0040	/* Short GI in 40MHz */
#define	IEEE80211_HTCAP_TXSTBC		0x0080	/* STBC tx ok */
#define	IEEE80211_HTCAP_RXSTBC		0x0300  /* STBC rx support */
#define	IEEE80211_HTCAP_RXSTBC_S	8
#define	IEEE80211_HTCAP_RXSTBC_1STREAM	0x0100  /* 1 spatial stream */
#define	IEEE80211_HTCAP_RXSTBC_2STREAM	0x0200  /* 1-2 spatial streams*/
#define	IEEE80211_HTCAP_RXSTBC_3STREAM	0x0300  /* 1-3 spatial streams*/
#define	IEEE80211_HTCAP_DELBA		0x0400	/* HT DELBA supported */
#define	IEEE80211_HTCAP_MAXAMSDU	0x0800	/* max A-MSDU length */
#define	IEEE80211_HTCAP_MAXAMSDU_7935	0x0800	/* 7935 octets */
#define	IEEE80211_HTCAP_MAXAMSDU_3839	0x0000	/* 3839 octets */
#define	IEEE80211_HTCAP_DSSSCCK40	0x1000  /* DSSS/CCK in 40MHz */
#define	IEEE80211_HTCAP_PSMP		0x2000  /* PSMP supported */
#define	IEEE80211_HTCAP_40INTOLERANT	0x4000  /* 40MHz intolerant */
#define	IEEE80211_HTCAP_LSIGTXOPPROT	0x8000  /* L-SIG TXOP prot */

#define	IEEE80211_HTCAP_BITS \
	"\20\1LDPC\2CHWIDTH40\5GREENFIELD\6SHORTGI20\7SHORTGI40\10TXSTBC" \
	"\13DELBA\14AMSDU(7935)\15DSSSCCK40\16PSMP\1740INTOLERANT" \
	"\20LSIGTXOPPROT"

/* HT parameters (hc_param) */
#define	IEEE80211_HTCAP_MAXRXAMPDU	0x03	/* max rx A-MPDU factor */
#define	IEEE80211_HTCAP_MAXRXAMPDU_S	0
#define	IEEE80211_HTCAP_MAXRXAMPDU_8K	0
#define	IEEE80211_HTCAP_MAXRXAMPDU_16K	1
#define	IEEE80211_HTCAP_MAXRXAMPDU_32K	2
#define	IEEE80211_HTCAP_MAXRXAMPDU_64K	3
#define	IEEE80211_HTCAP_MPDUDENSITY	0x1c	/* min MPDU start spacing */
#define	IEEE80211_HTCAP_MPDUDENSITY_S	2
#define	IEEE80211_HTCAP_MPDUDENSITY_NA	0	/* no time restriction */
#define	IEEE80211_HTCAP_MPDUDENSITY_025	1	/* 1/4 us */
#define	IEEE80211_HTCAP_MPDUDENSITY_05	2	/* 1/2 us */
#define	IEEE80211_HTCAP_MPDUDENSITY_1	3	/* 1 us */
#define	IEEE80211_HTCAP_MPDUDENSITY_2	4	/* 2 us */
#define	IEEE80211_HTCAP_MPDUDENSITY_4	5	/* 4 us */
#define	IEEE80211_HTCAP_MPDUDENSITY_8	6	/* 8 us */
#define	IEEE80211_HTCAP_MPDUDENSITY_16	7	/* 16 us */

/* HT extended capabilities (hc_extcap) */
#define	IEEE80211_HTCAP_PCO		0x0001	/* PCO capable */
#define	IEEE80211_HTCAP_PCOTRANS	0x0006	/* PCO transition time */
#define	IEEE80211_HTCAP_PCOTRANS_S	1
#define	IEEE80211_HTCAP_PCOTRANS_04	0x0002	/* 400 us */
#define	IEEE80211_HTCAP_PCOTRANS_15	0x0004	/* 1.5 ms */
#define	IEEE80211_HTCAP_PCOTRANS_5	0x0006	/* 5 ms */
/* bits 3-7 reserved */
#define	IEEE80211_HTCAP_MCSFBACK	0x0300	/* MCS feedback */
#define	IEEE80211_HTCAP_MCSFBACK_S	8
#define	IEEE80211_HTCAP_MCSFBACK_NONE	0x0000	/* nothing provided */
#define	IEEE80211_HTCAP_MCSFBACK_UNSOL	0x0200	/* unsolicited feedback */
#define	IEEE80211_HTCAP_MCSFBACK_MRQ	0x0300	/* " "+respond to MRQ */
#define	IEEE80211_HTCAP_HTC		0x0400	/* +HTC support */
#define	IEEE80211_HTCAP_RDR		0x0800	/* reverse direction responder*/
/* bits 12-15 reserved */

/*
 * 802.11n HT Information IE
 */
struct ieee80211_ie_htinfo {
	uint8_t		hi_id;			/* element ID */
	uint8_t		hi_len;			/* length in bytes */
	uint8_t		hi_ctrlchannel;		/* primary channel */
	uint8_t		hi_byte1;		/* ht ie byte 1 */
	uint8_t		hi_byte2;		/* ht ie byte 2 */
	uint8_t		hi_byte3;		/* ht ie byte 3 */
	uint16_t	hi_byte45;		/* ht ie bytes 4+5 */
	uint8_t 	hi_basicmcsset[16]; 	/* basic MCS set */
} __packed;

/* byte1 */
#define	IEEE80211_HTINFO_2NDCHAN	0x03	/* secondary/ext chan offset */
#define	IEEE80211_HTINFO_2NDCHAN_S	0
#define	IEEE80211_HTINFO_2NDCHAN_NONE	0x00	/* no secondary/ext channel */
#define	IEEE80211_HTINFO_2NDCHAN_ABOVE	0x01	/* above private channel */
/* NB: 2 is reserved */
#define	IEEE80211_HTINFO_2NDCHAN_BELOW	0x03	/* below primary channel */ 
#define	IEEE80211_HTINFO_TXWIDTH	0x04	/* tx channel width */
#define	IEEE80211_HTINFO_TXWIDTH_20	0x00	/* 20MHz width */
#define	IEEE80211_HTINFO_TXWIDTH_2040	0x04	/* any supported width */
#define	IEEE80211_HTINFO_RIFSMODE	0x08	/* Reduced IFS (RIFS) use */
#define	IEEE80211_HTINFO_RIFSMODE_PROH	0x00	/* RIFS use prohibited */
#define	IEEE80211_HTINFO_RIFSMODE_PERM	0x08	/* RIFS use permitted */
#define	IEEE80211_HTINFO_PMSPONLY	0x10	/* PSMP required to associate */
#define	IEEE80211_HTINFO_SIGRAN		0xe0	/* shortest Service Interval */
#define	IEEE80211_HTINFO_SIGRAN_S	5
#define	IEEE80211_HTINFO_SIGRAN_5	0x00	/* 5 ms */
/* XXX add rest */

/* bytes 2+3 */
#define	IEEE80211_HTINFO_OPMODE		0x03	/* operating mode */
#define	IEEE80211_HTINFO_OPMODE_S	0
#define	IEEE80211_HTINFO_OPMODE_PURE	0x00	/* no protection */
#define	IEEE80211_HTINFO_OPMODE_PROTOPT	0x01	/* protection optional */
#define	IEEE80211_HTINFO_OPMODE_HT20PR	0x02	/* protection for HT20 sta's */
#define	IEEE80211_HTINFO_OPMODE_MIXED	0x03	/* protection for legacy sta's*/
#define	IEEE80211_HTINFO_NONGF_PRESENT	0x04	/* non-GF sta's present */
#define	IEEE80211_HTINFO_TXBL		0x08	/* transmit burst limit */
#define	IEEE80211_HTINFO_NONHT_PRESENT	0x10	/* non-HT sta's present */
/* bits 5-15 reserved */

/* bytes 4+5 */
#define	IEEE80211_HTINFO_2NDARYBEACON	0x01
#define	IEEE80211_HTINFO_LSIGTXOPPROT	0x02
#define	IEEE80211_HTINFO_PCO_ACTIVE	0x04
#define	IEEE80211_HTINFO_40MHZPHASE	0x08

/* byte5 */
#define	IEEE80211_HTINFO_BASIC_STBCMCS	0x7f
#define	IEEE80211_HTINFO_BASIC_STBCMCS_S 0
#define	IEEE80211_HTINFO_DUALPROTECTED	0x80

/*
 * Management information element payloads.
 */

enum {
	IEEE80211_ELEMID_SSID		= 0,
	IEEE80211_ELEMID_RATES		= 1,
	IEEE80211_ELEMID_FHPARMS	= 2,
	IEEE80211_ELEMID_DSPARMS	= 3,
	IEEE80211_ELEMID_CFPARMS	= 4,
	IEEE80211_ELEMID_TIM		= 5,
	IEEE80211_ELEMID_IBSSPARMS	= 6,
	IEEE80211_ELEMID_COUNTRY	= 7,
	IEEE80211_ELEMID_HOPPATRNPARMS  = 8,
	IEEE80211_ELEMID_HOPPATRNTABLE  = 9,
	IEEE80211_ELEMID_REQINFO	= 10,
	IEEE80211_ELEMID_QBSSLOAD       = 11,
	IEEE80211_ELEMID_EDCAPARAM      = 12,
	IEEE80211_ELEMID_TSPEC		= 13,
	IEEE80211_ELEMID_TRAFCLASS      = 14,
	IEEE80211_ELEMID_SCHEDULE       = 15,
	IEEE80211_ELEMID_CHALLENGE	= 16,
	/* 17-31 reserved for challenge text extension */
	IEEE80211_ELEMID_PWRCNSTR	= 32,
	IEEE80211_ELEMID_PWRCAP		= 33,
	IEEE80211_ELEMID_TPCREQ		= 34,
	IEEE80211_ELEMID_TPCREP		= 35,
	IEEE80211_ELEMID_SUPPCHAN	= 36,
	IEEE80211_ELEMID_CHANSWITCHANN	= 37,
	IEEE80211_ELEMID_MEASREQ	= 38,
	IEEE80211_ELEMID_MEASREP	= 39,
	IEEE80211_ELEMID_QUIET		= 40,
	IEEE80211_ELEMID_IBSSDFS	= 41,
	IEEE80211_ELEMID_ERP		= 42,
	IEEE80211_ELEMID_TSDELAY	= 43,
	IEEE80211_ELEMID_TCLASSPROC     = 44,
	IEEE80211_ELEMID_QOS		= 46,
	IEEE80211_ELEMID_RSN		= 48,
	/* 49 reserved */
	IEEE80211_ELEMID_XRATES		= 50,
	/* 128-129 proprietary elements used by Agere chipsets */
	IEEE80211_ELEMID_AGERE1		= 128,
	IEEE80211_ELEMID_AGERE2		= 129,
	IEEE80211_ELEMID_TPC		= 150,
	IEEE80211_ELEMID_CCKM		= 156,
	IEEE80211_ELEMID_VENDOR		= 221,	/* vendor private */

	/*
	 * 802.11s IEs based on D3.03 spec and were not assigned by
	 * ANA. Beware changing them because some of them are being
	 * kept compatible with Linux.
	 */
	IEEE80211_ELEMID_MESHCONF	= 51,
	IEEE80211_ELEMID_MESHID		= 52,
	IEEE80211_ELEMID_MESHLINK	= 35,
	IEEE80211_ELEMID_MESHCNGST	= 36,
	IEEE80211_ELEMID_MESHPEER	= 55,
	IEEE80211_ELEMID_MESHCSA	= 38,
	IEEE80211_ELEMID_MESHTIM	= 39,
	IEEE80211_ELEMID_MESHAWAKEW	= 40,
	IEEE80211_ELEMID_MESHBEACONT	= 41,
	IEEE80211_ELEMID_MESHPANN	= 48,
	IEEE80211_ELEMID_MESHRANN	= 49,
	IEEE80211_ELEMID_MESHPREQ	= 68,
	IEEE80211_ELEMID_MESHPREP	= 69,
	IEEE80211_ELEMID_MESHPERR	= 70,
	IEEE80211_ELEMID_MESHPXU	= 53,
	IEEE80211_ELEMID_MESHPXUC	= 54,
	IEEE80211_ELEMID_MESHAH		= 60, /* Abbreviated Handshake */
};

#define BITCTL_BUFD_MCAST       	1
#define BITCTL_BUFD_UCAST_AID_MASK 	((u_int8_t)~(BITCTL_BUFD_MCAST))
#define BITCTL_BUFD_UCAST_AID_SHIFT 	1

struct ieee80211_tim_ie {
	u_int8_t	tim_ie;			/* IEEE80211_ELEMID_TIM */
	u_int8_t	tim_len;
	u_int8_t	tim_count;		/* DTIM count */
	u_int8_t	tim_period;		/* DTIM period */
	u_int8_t	tim_bitctl;		/* bitmap control */
	u_int8_t	tim_bitmap[1];		/* variable-length bitmap */
} __packed;

struct ieee80211_country_ie {
	u_int8_t	ie;			/* IEEE80211_ELEMID_COUNTRY */
	u_int8_t	len;
	u_int8_t	cc[3];			/* ISO CC+(I)ndoor/(O)utdoor */
	struct {
		u_int8_t schan;			/* starting channel */
		u_int8_t nchan;			/* number channels */
		u_int8_t maxtxpwr;		/* tx power cap */
	} __packed band[4];			/* up to 4 sub bands */
} __packed;

#define IEEE80211_CHALLENGE_LEN		128

#define IEEE80211_SUPPCHAN_LEN		26

#define	IEEE80211_RATE_BASIC		0x80
#define	IEEE80211_RATE_VAL		0x7f

/* EPR information element flags */
#define	IEEE80211_ERP_NON_ERP_PRESENT	0x01
#define	IEEE80211_ERP_USE_PROTECTION	0x02
#define	IEEE80211_ERP_LONG_PREAMBLE	0x04

/* Atheros private advanced capabilities info */
#define	ATHEROS_CAP_TURBO_PRIME		0x01
#define	ATHEROS_CAP_COMPRESSION		0x02
#define	ATHEROS_CAP_FAST_FRAME		0x04
/* bits 3-6 reserved */
#define	ATHEROS_CAP_BOOST		0x80

#define	ATH_OUI			0x7f0300		/* Atheros OUI */
#define	ATH_OUI_TYPE		0x01
#define	ATH_OUI_SUBTYPE		0x01
#define	ATH_OUI_VERSION		0x00
#define	ATH_OUI_TYPE_XR		0x03
#define	ATH_OUI_SUBTYPE_XR	0x01
#define	ATH_OUI_VER_XR		0x00

#define	WPA_OUI			0xf25000
#define	WPA_OUI_TYPE		0x01
#define	WPA_VERSION		1		/* current supported version */

#define	WPA_CSE_NULL		0x00
#define	WPA_CSE_WEP40		0x01
#define	WPA_CSE_TKIP		0x02
#define	WPA_CSE_CCMP		0x04
#define	WPA_CSE_WEP104		0x05

#define	WPA_ASE_NONE		0x00
#define	WPA_ASE_8021X_UNSPEC	0x01
#define	WPA_ASE_8021X_PSK	0x02

#define	WPS_OUI_TYPE		0x04

#define	RSN_OUI			0xac0f00
#define	RSN_VERSION		1		/* current supported version */

#define	RSN_CSE_NULL		0x00
#define	RSN_CSE_WEP40		0x01
#define	RSN_CSE_TKIP		0x02
#define	RSN_CSE_WRAP		0x03
#define	RSN_CSE_CCMP		0x04
#define	RSN_CSE_WEP104		0x05

#define	RSN_ASE_NONE		0x00
#define	RSN_ASE_8021X_UNSPEC	0x01
#define	RSN_ASE_8021X_PSK	0x02

#define	RSN_CAP_PREAUTH		0x01

#define	WME_OUI			0xf25000
#define	WME_OUI_TYPE		0x02
#define	WME_INFO_OUI_SUBTYPE	0x00
#define	WME_PARAM_OUI_SUBTYPE	0x01
#define	WME_VERSION		1

/* WME stream classes */
#define	WME_AC_BE	0		/* best effort */
#define	WME_AC_BK	1		/* background */
#define	WME_AC_VI	2		/* video */
#define	WME_AC_VO	3		/* voice */

/*
 * AUTH management packets
 *
 *	octet algo[2]
 *	octet seq[2]
 *	octet status[2]
 *	octet chal.id
 *	octet chal.length
 *	octet chal.text[253]
 */

typedef u_int8_t *ieee80211_mgt_auth_t;

#define	IEEE80211_AUTH_ALGORITHM(auth) \
	((auth)[0] | ((auth)[1] << 8))
#define	IEEE80211_AUTH_TRANSACTION(auth) \
	((auth)[2] | ((auth)[3] << 8))
#define	IEEE80211_AUTH_STATUS(auth) \
	((auth)[4] | ((auth)[5] << 8))

#define	IEEE80211_AUTH_ALG_OPEN		0x0000
#define	IEEE80211_AUTH_ALG_SHARED	0x0001
#define	IEEE80211_AUTH_ALG_LEAP		0x0080

enum {
	IEEE80211_AUTH_OPEN_REQUEST		= 1,
	IEEE80211_AUTH_OPEN_RESPONSE		= 2,
};

enum {
	IEEE80211_AUTH_SHARED_REQUEST		= 1,
	IEEE80211_AUTH_SHARED_CHALLENGE		= 2,
	IEEE80211_AUTH_SHARED_RESPONSE		= 3,
	IEEE80211_AUTH_SHARED_PASS		= 4,
};

/*
 * Reason and status codes.
 *
 * Reason codes are used in management frames to indicate why an
 * action took place (e.g. on disassociation).  Status codes are
 * used in management frames to indicate the result of an operation.
 *
 * Unlisted codes are reserved
 */

enum {
	IEEE80211_REASON_UNSPECIFIED		= 1,
	IEEE80211_REASON_AUTH_EXPIRE		= 2,
	IEEE80211_REASON_AUTH_LEAVE		= 3,
	IEEE80211_REASON_ASSOC_EXPIRE		= 4,
	IEEE80211_REASON_ASSOC_TOOMANY		= 5,
	IEEE80211_REASON_NOT_AUTHED		= 6,
	IEEE80211_REASON_NOT_ASSOCED		= 7,
	IEEE80211_REASON_ASSOC_LEAVE		= 8,
	IEEE80211_REASON_ASSOC_NOT_AUTHED	= 9,

	IEEE80211_REASON_PWRCAP_UNACCEPTABLE	= 10,
	IEEE80211_REASON_SUPPCHAN_UNACCEPTABLE	= 11,
	IEEE80211_REASON_RSN_REQUIRED		= 11,
	IEEE80211_REASON_RSN_INCONSISTENT	= 12,
	IEEE80211_REASON_IE_INVALID		= 13,
	IEEE80211_REASON_MIC_FAILURE		= 14,
	IEEE80211_REASON_4WAY_HANDSHAKE_TIMEOUT	= 15,	/* 11i */
	IEEE80211_REASON_GROUP_KEY_UPDATE_TIMEOUT = 16,	/* 11i */
	IEEE80211_REASON_IE_IN_4WAY_DIFFERS	= 17,	/* 11i */
	IEEE80211_REASON_GROUP_CIPHER_INVALID	= 18,	/* 11i */
	IEEE80211_REASON_PAIRWISE_CIPHER_INVALID= 19,	/* 11i */
	IEEE80211_REASON_AKMP_INVALID		= 20,	/* 11i */
	IEEE80211_REASON_UNSUPP_RSN_IE_VERSION	= 21,	/* 11i */
	IEEE80211_REASON_INVALID_RSN_IE_CAP	= 22,	/* 11i */
	IEEE80211_REASON_802_1X_AUTH_FAILED	= 23,	/* 11i */
	IEEE80211_REASON_CIPHER_SUITE_REJECTED	= 24,	/* 11i */
	IEEE80211_REASON_UNSPECIFIED_QOS	= 32,	/* 11e */
	IEEE80211_REASON_INSUFFICIENT_BW	= 33,	/* 11e */
	IEEE80211_REASON_TOOMANY_FRAMES		= 34,	/* 11e */
	IEEE80211_REASON_OUTSIDE_TXOP		= 35,	/* 11e */
	IEEE80211_REASON_LEAVING_QBSS		= 36,	/* 11e */
	IEEE80211_REASON_BAD_MECHANISM		= 37,	/* 11e */
	IEEE80211_REASON_SETUP_NEEDED		= 38,	/* 11e */
	IEEE80211_REASON_TIMEOUT		= 39,	/* 11e */

	/* values not yet allocated by ANA */
	IEEE80211_REASON_PEER_LINK_CANCELED	= 2,	/* 11s */
	IEEE80211_REASON_MESH_MAX_PEERS		= 3,	/* 11s */
	IEEE80211_REASON_MESH_CPVIOLATION	= 4,	/* 11s */
	IEEE80211_REASON_MESH_CLOSE_RCVD	= 5,	/* 11s */
	IEEE80211_REASON_MESH_MAX_RETRIES	= 6,	/* 11s */
	IEEE80211_REASON_MESH_CONFIRM_TIMEOUT	= 7,	/* 11s */
	IEEE80211_REASON_MESH_INVALID_GTK	= 8,	/* 11s */
	IEEE80211_REASON_MESH_INCONS_PARAMS	= 9,	/* 11s */
	IEEE80211_REASON_MESH_INVALID_SECURITY	= 10,	/* 11s */
	IEEE80211_REASON_MESH_PERR_UNSPEC	= 11,	/* 11s */
	IEEE80211_REASON_MESH_PERR_NO_FI	= 12,	/* 11s */
	IEEE80211_REASON_MESH_PERR_DEST_UNREACH	= 13,	/* 11s */

	IEEE80211_STATUS_SUCCESS		= 0,
	IEEE80211_STATUS_UNSPECIFIED		= 1,
	IEEE80211_STATUS_CAPINFO		= 10,
	IEEE80211_STATUS_NOT_ASSOCED		= 11,
	IEEE80211_STATUS_OTHER			= 12,
	IEEE80211_STATUS_ALG			= 13,
	IEEE80211_STATUS_SEQUENCE		= 14,
	IEEE80211_STATUS_CHALLENGE		= 15,
	IEEE80211_STATUS_TIMEOUT		= 16,
	IEEE80211_STATUS_TOOMANY		= 17,
	IEEE80211_STATUS_BASIC_RATE		= 18,
	IEEE80211_STATUS_SP_REQUIRED		= 19,
	IEEE80211_STATUS_PBCC_REQUIRED		= 20,
	IEEE80211_STATUS_CA_REQUIRED		= 21,
	IEEE80211_STATUS_SM_REQUIRED		= 22,
	IEEE80211_STATUS_PWRCAP_UNACCEPTABLE	= 23,
	IEEE80211_STATUS_SUPPCHAN_UNACCEPTABLE	= 24,
	IEEE80211_STATUS_TOO_MANY_STATIONS	= 22,
	IEEE80211_STATUS_RATES			= 23,
	IEEE80211_STATUS_SHORTSLOT_REQUIRED	= 25,
	IEEE80211_STATUS_DSSSOFDM_REQUIRED	= 26,
	IEEE80211_STATUS_MISSING_HT_CAPS	= 27,	/* 11n D3.0 */
	IEEE80211_STATUS_INVALID_IE		= 40,	/* 11i */
	IEEE80211_STATUS_GROUP_CIPHER_INVALID	= 41,	/* 11i */
	IEEE80211_STATUS_PAIRWISE_CIPHER_INVALID = 42,	/* 11i */
	IEEE80211_STATUS_AKMP_INVALID		= 43,	/* 11i */
	IEEE80211_STATUS_UNSUPP_RSN_IE_VERSION	= 44,	/* 11i */
	IEEE80211_STATUS_INVALID_RSN_IE_CAP	= 45,	/* 11i */
	IEEE80211_STATUS_CIPHER_SUITE_REJECTED	= 46,	/* 11i */
};

#define	IEEE80211_WEP_KEYLEN		5	/* 40bit */
#define	IEEE80211_WEP_IVLEN		3	/* 24bit */
#define	IEEE80211_WEP_KIDLEN		1	/* 1 octet */
#define	IEEE80211_WEP_CRCLEN		4	/* CRC-32 */
#define	IEEE80211_WEP_TOTLEN		(IEEE80211_WEP_IVLEN + \
					 IEEE80211_WEP_KIDLEN + \
					 IEEE80211_WEP_CRCLEN)
#define	IEEE80211_WEP_NKID		4	/* number of key ids */

/*
 * 802.11i defines an extended IV for use with non-WEP ciphers.
 * When the EXTIV bit is set in the key id byte an additional
 * 4 bytes immediately follow the IV for TKIP.  For CCMP the
 * EXTIV bit is likewise set but the 8 bytes represent the
 * CCMP header rather than IV+extended-IV.
 */
#define	IEEE80211_WEP_EXTIV		0x20
#define	IEEE80211_WEP_EXTIVLEN		4	/* extended IV length */
#define	IEEE80211_WEP_MICLEN		8	/* trailing MIC */

#define	IEEE80211_CRC_LEN		4

/*
 * Maximum acceptable MTU is:
 *	IEEE80211_MAX_LEN - WEP overhead - CRC -
 *		QoS overhead - RSN/WPA overhead
 * Min is arbitrarily chosen > IEEE80211_MIN_LEN.  The default
 * mtu is Ethernet-compatible; it's set by ether_ifattach.
 */
#define	IEEE80211_MTU_MAX		2290
#define	IEEE80211_MTU_MIN		32

#define	IEEE80211_MAX_LEN		(2300 + IEEE80211_CRC_LEN + \
	(IEEE80211_WEP_IVLEN + IEEE80211_WEP_KIDLEN + IEEE80211_WEP_CRCLEN))
#define	IEEE80211_ACK_LEN \
	(sizeof(struct ieee80211_frame_ack) + IEEE80211_CRC_LEN)
#define	IEEE80211_MIN_LEN \
	(sizeof(struct ieee80211_frame_min) + IEEE80211_CRC_LEN)

/*
 * The 802.11 spec says at most 2007 stations may be
 * associated at once.  For most AP's this is way more
 * than is feasible so we use a default of IEEE80211_AID_DEF.
 * This number may be overridden by the driver and/or by
 * user configuration but may not be less than IEEE80211_AID_MIN
 * (see _ieee80211.h for implementation-specific settings).
 */
#define	IEEE80211_AID_MAX		2007
#define	IEEE80211_AID_DEF		128

#define	IEEE80211_AID(b)	((b) &~ 0xc000)

/* 
 * RTS frame length parameters.  The default is specified in
 * the 802.11 spec.  The max may be wrong for jumbo frames.
 */
#define	IEEE80211_RTS_DEFAULT		512
#define	IEEE80211_RTS_MIN		1
#define	IEEE80211_RTS_MAX		2346

/* 
 * Regulatory extension identifier for country IE.
 */
#define IEEE80211_REG_EXT_ID		201

/*
 * IEEE 802.11 timer synchronization function (TSF) timestamp length
 */
#define IEEE80211_TSF_LEN		8

#endif /* _NET80211_IEEE80211_H_ */