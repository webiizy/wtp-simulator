/*-
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
 * $Id: ieee80211_scan.c 4134 2011-02-02 21:10:53Z proski $
 */
#ifndef EXPORT_SYMTAB
#define	EXPORT_SYMTAB
#endif

/*
 * IEEE 802.11 scanning support.
 */
#if !defined(AUTOCONF_INCLUDED) && !defined(CONFIG_LOCALVERSION)
#include <linux/config.h>
#endif
#include <linux/version.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/random.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

#include "if_media.h"

#include <net80211/ieee80211_var.h>
#include <net80211/if_athproto.h>

struct scan_state {
	struct ieee80211_scan_state base;	/* public state */

	u_int ss_iflags;			/* flags used internally */
#define	ISCAN_MINDWELL 	0x0001			/* min dwell time reached */
#define	ISCAN_DISCARD	0x0002			/* discard rx'd frames */
#define	ISCAN_CANCEL	0x0004			/* cancel current scan */
#define	ISCAN_START	0x0008			/* 1st time through next_scan */
	unsigned long ss_chanmindwell;		/* min dwell on curchan */
	unsigned long ss_scanend;		/* time scan must stop */
	u_int ss_duration;			/* duration for next scan */
	struct tasklet_struct ss_pwrsav;	/* sta ps ena tasklet */
	struct timer_list ss_scan_timer;	/* scan timer */
};
#define	SCAN_PRIVATE(_ss)	((struct scan_state *)(_ss))

/*
 * Amount of time to go off-channel during a background
 * scan.  This value should be large enough to catch most
 * APs but short enough that we can return on-channel
 * before our listen interval expires.
 *
 * XXX tunable
 * XXX check against configured listen interval
 */
#define	IEEE80211_SCAN_OFFCHANNEL	msecs_to_jiffies(150)

/*
 * Roaming-related defaults.  RSSI thresholds are as returned by the
 * driver (dBm).  Transmit rate thresholds are IEEE rate codes (i.e
 * .5M units).
 */
#define	SCAN_VALID_DEFAULT		60	/* scan cache valid age (secs) */
#define	ROAM_RSSI_11A_DEFAULT		9	/* rssi threshold for 11a bss */
#define	ROAM_RSSI_11G_DEFAULT		9	/* rssi threshold for 11g bss */
#define	ROAM_RSSI_11BONLY_DEFAULT	9	/* rssi threshold for 11b-only bss */
#define	ROAM_RATE_11A_DEFAULT		2 * 24	/* tx rate threshold for 11a bss */
#define	ROAM_RATE_11G_DEFAULT		2 * 9	/* tx rate threshold for 11g bss */
#define	ROAM_RATE_11BONLY_DEFAULT	2 * 5	/* tx rate threshold for 11b-only bss */

static void scan_restart_pwrsav(unsigned long);
static void scan_next(unsigned long);

void
ieee80211_scan_attach(struct ieee80211com *ic)
{
	struct scan_state *ss;

	ic->ic_roaming = IEEE80211_ROAMING_AUTO;

	MALLOC(ss, struct scan_state *, sizeof(struct scan_state),
		M_80211_SCAN, M_NOWAIT | M_ZERO);
	if (ss != NULL) {
		init_timer(&ss->ss_scan_timer);
		ss->ss_scan_timer.function = scan_next;
		ss->ss_scan_timer.data = (unsigned long) ss;
		tasklet_init(&ss->ss_pwrsav, scan_restart_pwrsav,
			(unsigned long) ss);
		ic->ic_scan = &ss->base;
	} else
		ic->ic_scan = NULL;
}

void
ieee80211_scan_detach(struct ieee80211com *ic)
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss != NULL) {
		del_timer(&SCAN_PRIVATE(ss)->ss_scan_timer);
		tasklet_kill(&SCAN_PRIVATE(ss)->ss_pwrsav);
		if (ss->ss_ops != NULL) {
			ss->ss_ops->scan_detach(ss);
			ss->ss_ops = NULL;
		}
		ic->ic_flags &= ~IEEE80211_F_SCAN;
		ic->ic_scan = NULL;
		FREE(SCAN_PRIVATE(ss), M_80211_SCAN);
	}
}

void
ieee80211_scan_vattach(struct ieee80211vap *vap)
{
	vap->iv_bgscanidle = msecs_to_jiffies(IEEE80211_BGSCAN_IDLE_DEFAULT);
	vap->iv_bgscanintvl = IEEE80211_BGSCAN_INTVAL_DEFAULT * HZ;
	vap->iv_scanvalid = SCAN_VALID_DEFAULT * HZ;
	vap->iv_roam.rssi11a = ROAM_RSSI_11A_DEFAULT;
	vap->iv_roam.rssi11g = ROAM_RSSI_11G_DEFAULT;
	vap->iv_roam.rssi11bOnly = ROAM_RSSI_11BONLY_DEFAULT;
	vap->iv_roam.rate11a = ROAM_RATE_11A_DEFAULT;
	vap->iv_roam.rate11g = ROAM_RATE_11G_DEFAULT;
	vap->iv_roam.rate11bOnly = ROAM_RATE_11BONLY_DEFAULT;
}

void
ieee80211_scan_vdetach(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;

	IEEE80211_LOCK_IRQ(ic);
	if (ss->ss_vap == vap) {
		if (ic->ic_flags & IEEE80211_F_SCAN) {
			del_timer(&SCAN_PRIVATE(ss)->ss_scan_timer);
			ic->ic_flags &= ~IEEE80211_F_SCAN;
		}
		if (ss->ss_ops != NULL) {
			ss->ss_ops->scan_detach(ss);
			ss->ss_ops = NULL;
		}
	}
	IEEE80211_UNLOCK_IRQ(ic);
}

/*
 * Simple-minded scanner module support.
 */
#define	IEEE80211_SCANNER_MAX	(IEEE80211_M_MONITOR+1)

static const char *scan_modnames[IEEE80211_SCANNER_MAX] = {
	[IEEE80211_M_IBSS]	= "wlan_scan_sta",
	[IEEE80211_M_STA]	= "wlan_scan_sta",
	[IEEE80211_M_AHDEMO]	= "wlan_scan_sta",
	[IEEE80211_M_HOSTAP]	= "wlan_scan_ap",
};
static const struct ieee80211_scanner *scanners[IEEE80211_SCANNER_MAX];

/* If try load is set, this function will attempt to automatically load the
 * requested module if it is not present. This is on operation that may sleep.
 * Therefore:
 * if !!tryload, then Context: process
 */
const struct ieee80211_scanner *
ieee80211_scanner_get(enum ieee80211_opmode mode, int tryload)
{
	int err;
	if (mode >= IEEE80211_SCANNER_MAX)
		return NULL;
	if (scan_modnames[mode] == NULL)
		return NULL;
	if (scanners[mode] == NULL && tryload) {
		err = ieee80211_load_module(scan_modnames[mode]);
		if (scanners[mode] == NULL || err)
			printk(KERN_WARNING "unable to load %s\n", scan_modnames[mode]);
	}
	return scanners[mode];
}
EXPORT_SYMBOL(ieee80211_scanner_get);

void
ieee80211_scanner_register(enum ieee80211_opmode mode,
	const struct ieee80211_scanner *scan)
{
	if (mode >= IEEE80211_SCANNER_MAX)
		return;
	scanners[mode] = scan;
}
EXPORT_SYMBOL(ieee80211_scanner_register);

void
ieee80211_scanner_unregister(enum ieee80211_opmode mode,
	const struct ieee80211_scanner *scan)
{
	if (mode >= IEEE80211_SCANNER_MAX)
		return;
	if (scanners[mode] == scan)
		scanners[mode] = NULL;
}
EXPORT_SYMBOL(ieee80211_scanner_unregister);

void
ieee80211_scanner_unregister_all(const struct ieee80211_scanner *scan)
{
	int m;

	for (m = 0; m < IEEE80211_SCANNER_MAX; m++)
		if (scanners[m] == scan)
			scanners[m] = NULL;
}
EXPORT_SYMBOL(ieee80211_scanner_unregister_all);

static void
change_channel(struct ieee80211com *ic,
	struct ieee80211_channel *chan)
{
	ic->ic_curchan = chan;
	ic->ic_set_channel(ic);
}

static char
channel_type(const struct ieee80211_channel *c)
{
	if (IEEE80211_IS_CHAN_ST(c))
		return 'S';
	if (IEEE80211_IS_CHAN_108A(c))
		return 'T';
	if (IEEE80211_IS_CHAN_108G(c))
		return 'G';
	if (IEEE80211_IS_CHAN_A(c))
		return 'a';
	if (IEEE80211_IS_CHAN_ANYG(c))
		return 'g';
	if (IEEE80211_IS_CHAN_B(c))
		return 'b';
	return 'f';
}

void
ieee80211_scan_dump_channels(const struct ieee80211_scan_state *ss)
{
	struct ieee80211com *ic = ss->ss_vap->iv_ic;
	const char *sep;
	int i;

	sep = "";
	for (i = ss->ss_next; i < ss->ss_last; i++) {
		const struct ieee80211_channel *c = ss->ss_chans[i];

		printk("%s%u%c", sep, ieee80211_chan2ieee(ic, c),
			channel_type(c));
		sep = ", ";
	}
}
EXPORT_SYMBOL(ieee80211_scan_dump_channels);

/*
 * Enable station power save mode and start/restart the scanning thread.
 */
static void
scan_restart_pwrsav(unsigned long arg)
{
	struct scan_state *ss = (struct scan_state *)arg;
	struct ieee80211vap *vap = ss->base.ss_vap;
	struct ieee80211com *ic = vap->iv_ic;
	int delay;

	if (vap->iv_opmode != IEEE80211_M_IBSS)
	    ieee80211_sta_pwrsave(vap, 1);
	/*
	 * Use an initial 1ms delay to ensure the null
	 * data frame has a chance to go out.
	 * XXX: 1ms is a lot, better to trigger scan
	 * on TX complete.
	 */
	delay = msecs_to_jiffies(1);
	if (delay < 1)
		delay = 1;
	ic->ic_scan_start(ic);			/* notify driver */
	ss->ss_scanend = jiffies + delay + ss->ss_duration;
	ss->ss_iflags |= ISCAN_START;
	mod_timer(&ss->ss_scan_timer, jiffies + delay);
}

/*
 * Start/restart scanning.  If we're operating in station mode
 * and associated notify the ap we're going into power save mode
 * and schedule a callback to initiate the work (where there's a
 * better context for doing the work).  Otherwise, start the scan
 * directly.
 */
static int
scan_restart(struct scan_state *ss, u_int duration)
{
	struct ieee80211vap *vap = ss->base.ss_vap;
	struct ieee80211com *ic = vap->iv_ic;

	if (ss->base.ss_next == ss->base.ss_last) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: no channels to scan\n", __func__);
		return 0;
	} else {
		if ((vap->iv_opmode == IEEE80211_M_STA) &&
			(vap->iv_state == IEEE80211_S_RUN) &&
			!(IEEE80211_VAP_IS_SLEEPING(vap))) {
			/*
			 * Initiate power save before going off-channel.
			 * Note that we cannot do this directly because
			 * of locking issues; instead we defer it to a
			 * tasklet.
			 */
			ss->ss_duration = duration;
			tasklet_schedule(&ss->ss_pwrsav);
		} else {
			ic->ic_scan_start(ic);		/* notify driver */
			ss->ss_scanend = jiffies + duration;
			ss->ss_iflags |= ISCAN_START;
			mod_timer(&ss->ss_scan_timer, jiffies);
		}
		return 1;
	}
}

static void
copy_ssid(struct ieee80211vap *vap, struct ieee80211_scan_state *ss,
	int nssid, const struct ieee80211_scan_ssid ssids[])
{
	if (nssid > IEEE80211_SCAN_MAX_SSID) {
		/* XXX printk */
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: too many ssid %d, ignoring all of them\n",
			__func__, nssid);
		return;
	}
	memcpy(ss->ss_ssid, ssids, nssid * sizeof(ssids[0]));
	ss->ss_nssid = nssid;
}

/*
 * Start a scan unless one is already going.
 */
int
ieee80211_start_scan(struct ieee80211vap *vap, int flags, u_int duration,
	u_int nssid, const struct ieee80211_scan_ssid ssids[])
{
	struct ieee80211com *ic = vap->iv_ic;
	const struct ieee80211_scanner *scan;
	struct ieee80211_scan_state *ss = ic->ic_scan;
	int scanning;

	scan = ieee80211_scanner_get(vap->iv_opmode, 0);
	if (scan == NULL) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: no scanner support for mode %u\n",
			__func__, vap->iv_opmode);
		/* XXX stat */
		return 0;
	}

	IEEE80211_LOCK_IRQ(ic);
	if ((ic->ic_flags & IEEE80211_F_SCAN) == 0) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: %s scan, duration %lu, desired mode %s, %s%s%s%s\n",
			__func__,
			flags & IEEE80211_SCAN_ACTIVE ? "active" : "passive",
		 	duration,
			ieee80211_phymode_name[vap->iv_des_mode],
			flags & IEEE80211_SCAN_FLUSH ? "flush" : "append",
			flags & IEEE80211_SCAN_NOPICK ? ", nopick" : "",
			flags & IEEE80211_SCAN_PICK1ST ? ", pick1st" : "",
			flags & IEEE80211_SCAN_ONCE ? ", once" : "");

		ss->ss_vap = vap;
		if (ss->ss_ops != scan) {
			/* switch scanners; detach old, attach new */
			if (ss->ss_ops != NULL)
				ss->ss_ops->scan_detach(ss);
			if (!scan->scan_attach(ss)) {
				/* XXX attach failure */
				/* XXX stat+msg */
				ss->ss_ops = NULL;
			} else
				ss->ss_ops = scan;
		}
		if (ss->ss_ops != NULL) {
			if ((flags & IEEE80211_SCAN_NOSSID) == 0)
				copy_ssid(vap, ss, nssid, ssids);

			/* NB: top 4 bits for internal use */
			ss->ss_flags = flags & 0xfff;
			if (ss->ss_flags & IEEE80211_SCAN_ACTIVE)
				vap->iv_stats.is_scan_active++;
			else
				vap->iv_stats.is_scan_passive++;
			if (flags & IEEE80211_SCAN_FLUSH)
				ss->ss_ops->scan_flush(ss);

			/* NB: flush frames rx'd before 1st channel change */
			SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_DISCARD;
			ss->ss_ops->scan_start(ss, vap);
			if (scan_restart(SCAN_PRIVATE(ss), duration))
				ic->ic_flags |= IEEE80211_F_SCAN;
		}
	} else {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: %s scan already in progress\n", __func__,
			ss->ss_flags & IEEE80211_SCAN_ACTIVE ? "active" : "passive");

		/* If the running scanning has the flag SCAN_NOPICK set, but
		 * the requested scan has not, then we update the running scan
		 * flag. This is needed when wpa_supplicant is used with
		 * ap_scan=1. Without it, the driver will never associate. */
		if (((flags & IEEE80211_SCAN_NOPICK) == 0) &&
		    (ss->ss_flags & IEEE80211_SCAN_NOPICK)) {
			IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
					  "%s: clearing SCAN_NOPICK flag\n",
					  __func__);
			ss->ss_flags &= ~IEEE80211_SCAN_NOPICK;
		}
	}
	
	scanning = (ic->ic_flags & IEEE80211_F_SCAN);
	IEEE80211_UNLOCK_IRQ(ic);

	return scanning;
}
EXPORT_SYMBOL(ieee80211_start_scan);

/*
 * Check the scan cache for an ap/channel to use; if that
 * fails then kick off a new scan.
 */
int
ieee80211_check_scan(struct ieee80211vap *vap, int flags, u_int duration,
	u_int nssid, const struct ieee80211_scan_ssid ssids[],
	int (*action)(struct ieee80211vap *, const struct ieee80211_scan_entry *))
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;
	int checkscanlist = 0;

	/*
	 * Check if there's a list of scan candidates already.
	 * XXX want more than the ap we're currently associated with
	 */
	IEEE80211_LOCK_IRQ(ic);
	IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
		"%s: %s scan, duration %lu, desired mode %s, %s%s%s%s\n",
		__func__,
		flags & IEEE80211_SCAN_ACTIVE ? "active" : "passive",
		duration,
		ieee80211_phymode_name[vap->iv_des_mode],
		flags & IEEE80211_SCAN_FLUSH ? "flush" : "append",
		flags & IEEE80211_SCAN_NOPICK ? ", nopick" : "",
		flags & IEEE80211_SCAN_PICK1ST ? ", pick1st" : "",
		flags & IEEE80211_SCAN_ONCE ? ", once" : "",
		flags & IEEE80211_SCAN_USECACHE ? ", usecache" : "");

	if (ss->ss_ops != NULL) {
		/* XXX verify ss_ops matches vap->iv_opmode */
		if ((flags & IEEE80211_SCAN_NOSSID) == 0) {
			/*
			 * Update the ssid list and mark flags so if
			 * we call start_scan it doesn't duplicate work.
			 */
			copy_ssid(vap, ss, nssid, ssids);
			flags |= IEEE80211_SCAN_NOSSID;
		}
		if ((ic->ic_flags & IEEE80211_F_SCAN) == 0 &&
		     time_before(jiffies, ic->ic_lastscan + vap->iv_scanvalid)) {
			/*
			 * We're not currently scanning and the cache is
			 * deemed hot enough to consult.  Lock out others
			 * by marking IEEE80211_F_SCAN while we decide if
			 * something is already in the scan cache we can
			 * use.  Also discard any frames that might come
			 * in while temporarily marked as scanning.
			 */
			SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_DISCARD;
			ic->ic_flags |= IEEE80211_F_SCAN;
			checkscanlist = 1;
		}
	}
	IEEE80211_UNLOCK_IRQ(ic);
	if (checkscanlist) {
		/*
		 * ss must be filled out so scan may be restarted "outside"
		 * of the current callstack.
		 */
		ss->ss_flags = flags;
		ss->ss_duration = duration;
		if (ss->ss_ops->scan_end(ss, ss->ss_vap, action, flags & IEEE80211_SCAN_KEEPMODE)) {
			/* found an ap, just clear the flag */
			ic->ic_flags &= ~IEEE80211_F_SCAN;
			return 1;
		}
		/* no ap, clear the flag before starting a scan */
		ic->ic_flags &= ~IEEE80211_F_SCAN;
	}
	if ((flags & IEEE80211_SCAN_USECACHE) == 0)
		return ieee80211_start_scan(vap, flags, duration, nssid, ssids);
	else {
		/* If we *must* use the cache and no ap was found, return failure */
		return 0;
	}
}

/*
 * Restart a previous scan.  If the previous scan completed
 * then we start again using the existing channel list.
 */
int
ieee80211_bg_scan(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;
	int scanning;

	IEEE80211_LOCK_IRQ(ic);
	if ((ic->ic_flags & IEEE80211_F_SCAN) == 0) {
		u_int duration;
		/*
		 * Go off-channel for a fixed interval that is large
		 * enough to catch most APs but short enough that
		 * we can return on-channel before our listen interval
		 * expires.
		 */
		duration = IEEE80211_SCAN_OFFCHANNEL;

		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: %s scan, jiffies %lu duration %lu\n", __func__,
			ss->ss_flags & IEEE80211_SCAN_ACTIVE ? "active" : "passive",
			jiffies, duration);

		if (ss->ss_ops != NULL) {
			ss->ss_vap = vap;
			/*
			 * A background scan does not select a new STA; it
			 * just refreshes the scan cache.  Also, indicate
			 * the scan logic should follow the beacon schedule:
			 * we go off-channel and scan for a while, then
			 * return to the bss channel to receive a beacon,
			 * then go off-channel again.  All during this time
			 * we notify the ap we're in power save mode.  When
			 * the scan is complete, we leave power save mode.
			 * If any beacon indicates there are frames pending
			 * for us then we drop out of power save mode
			 * (and background scan) automatically by way of the
			 * usual STA power save logic.
			 */
			ss->ss_flags |= IEEE80211_SCAN_NOPICK |
				IEEE80211_SCAN_BGSCAN;

			/* If previous scan completed, restart */
			if (ss->ss_next >= ss->ss_last) {
				ss->ss_next = 0;
				if (ss->ss_flags & IEEE80211_SCAN_ACTIVE)
					vap->iv_stats.is_scan_active++;
				else
					vap->iv_stats.is_scan_passive++;
				ss->ss_ops->scan_restart(ss, vap);
			}

			/* NB: Flush frames RX'd before 1st channel change */
			SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_DISCARD;
			ss->ss_mindwell = duration;
			if (scan_restart(SCAN_PRIVATE(ss), duration)) {
				ic->ic_flags |= IEEE80211_F_SCAN;
				ic->ic_flags_ext |= IEEE80211_FEXT_BGSCAN;
			}
		} else {
			/* XXX msg+stat */
		}
	} else {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: %s scan already in progress\n", __func__,
			ss->ss_flags & IEEE80211_SCAN_ACTIVE ? "active" : "passive");
	}
	
	scanning = (ic->ic_flags & IEEE80211_F_SCAN);
	IEEE80211_UNLOCK_IRQ(ic);

	return scanning;
}
EXPORT_SYMBOL(ieee80211_bg_scan);
EXPORT_SYMBOL(ieee80211_cancel_scan);

/*
 * Cancel any scan currently going on.
 */
void
ieee80211_cancel_scan(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;

	IEEE80211_LOCK_IRQ(ic);
	if (ic->ic_flags & IEEE80211_F_SCAN) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: cancel %s scan\n", __func__,
			ss->ss_flags & IEEE80211_SCAN_ACTIVE ? "active" : "passive");

		/* clear bg scan NOPICK and mark cancel request */
		ss->ss_flags &= ~IEEE80211_SCAN_NOPICK;
		SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_CANCEL;
		ss->ss_ops->scan_cancel(ss, vap);
		/* force it to fire asap */
		mod_timer(&SCAN_PRIVATE(ss)->ss_scan_timer, jiffies);
	}
	IEEE80211_UNLOCK_IRQ(ic);
}

/*
 * Switch to the next channel marked for scanning.
 */
static void
scan_next(unsigned long arg)
{
#define	ISCAN_REP	(ISCAN_MINDWELL | ISCAN_START | ISCAN_DISCARD)
	struct ieee80211_scan_state *ss = (struct ieee80211_scan_state *)arg;
	struct ieee80211vap *vap = ss->ss_vap;
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_channel *chan;
	unsigned long maxdwell, scanend;
	int scanning, scandone, i;

	IEEE80211_LOCK_IRQ(ic);
	scanning = (ic->ic_flags & IEEE80211_F_SCAN) != 0;
	IEEE80211_UNLOCK_IRQ(ic);
	if (!scanning)			/* canceled */
		return;

again:
	scandone = (ss->ss_next >= ss->ss_last) ||
		((SCAN_PRIVATE(ss)->ss_iflags & ISCAN_CANCEL) != 0);
	scanend = SCAN_PRIVATE(ss)->ss_scanend;
	if (!scandone &&
	    (ss->ss_flags & IEEE80211_SCAN_GOTPICK) == 0 &&
	    ((SCAN_PRIVATE(ss)->ss_iflags & ISCAN_START) ||
	     time_before(jiffies + ss->ss_mindwell, scanend))) {
		chan = ss->ss_chans[ss->ss_next++];

		/*
		 * Watch for truncation due to the scan end time.
		 */
		if (time_after(jiffies + ss->ss_maxdwell, scanend))
			maxdwell = scanend - jiffies;
		else
			maxdwell = ss->ss_maxdwell;

		IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
			"%s: chan %3d%c -> %3d%c [%s, dwell min %lu max %lu]\n",
			__func__,
			ieee80211_chan2ieee(ic, ic->ic_curchan),
		        	channel_type(ic->ic_curchan),
			ieee80211_chan2ieee(ic, chan), channel_type(chan),
			(ss->ss_flags & IEEE80211_SCAN_ACTIVE) &&
				  (!IEEE80211_IS_CHAN_PASSIVE(chan)) ?
				"active" : "passive",
			ss->ss_mindwell, maxdwell);

		/*
		 * Potentially change channel and phy mode.
		 */
		change_channel(ic, chan);

		/*
		 * If doing an active scan and the channel is not
		 * marked passive-only then send a probe request.
		 * Otherwise just listen for traffic on the channel.
		 */
		if ((ss->ss_flags & IEEE80211_SCAN_ACTIVE) &&
		    !IEEE80211_IS_CHAN_PASSIVE(chan)) {
			struct net_device *dev = vap->iv_dev;
			/*
			 * Send a broadcast probe request followed by
			 * any specified directed probe requests.
			 * XXX suppress broadcast probe req?
			 * XXX remove dependence on vap/vap->iv_bss
			 * XXX move to policy code?
			 */
			ieee80211_send_probereq(vap->iv_bss,
				vap->iv_myaddr, dev->broadcast,
				dev->broadcast,
				"", 0,
				vap->iv_opt_ie, vap->iv_opt_ie_len);
			for (i = 0; i < ss->ss_nssid; i++)
				ieee80211_send_probereq(vap->iv_bss,
					vap->iv_myaddr, dev->broadcast,
					dev->broadcast,
					ss->ss_ssid[i].ssid,
					ss->ss_ssid[i].len,
					vap->iv_opt_ie, vap->iv_opt_ie_len);
		}
		SCAN_PRIVATE(ss)->ss_chanmindwell = jiffies + ss->ss_mindwell;
		mod_timer(&SCAN_PRIVATE(ss)->ss_scan_timer, jiffies + maxdwell);
		/* clear mindwell lock and initial channel change flush */
		SCAN_PRIVATE(ss)->ss_iflags &= ~ISCAN_REP;
	} else {
		ic->ic_scan_end(ic);		/* notify driver */
		/*
		 * Record scan complete time.  Note that we also do
		 * this when canceled so any background scan will
		 * not be restarted for a while.
		 */
		if (scandone)
			ic->ic_lastscan = jiffies;
		/* return to the bss channel */
		if ((ic->ic_bsschan != IEEE80211_CHAN_ANYC) &&
		    (ic->ic_curchan != ic->ic_bsschan))
			change_channel(ic, ic->ic_bsschan);
		/* clear internal flags and any indication of a pick */
		SCAN_PRIVATE(ss)->ss_iflags &= ~ISCAN_REP;
		ss->ss_flags &= ~IEEE80211_SCAN_GOTPICK;

		/*
		 * If not canceled and scan completed, do post-processing.
		 * If the callback function returns 0, then it wants to
		 * continue/restart scanning.  Unfortunately we needed to
		 * notify the driver to end the scan above to avoid having
		 * rx frames alter the scan candidate list.
		 */
		if (((SCAN_PRIVATE(ss)->ss_iflags & ISCAN_CANCEL) == 0) &&
		    !ss->ss_ops->scan_end(ss, vap, NULL, 0) &&
		    ((ss->ss_flags & IEEE80211_SCAN_ONCE) == 0) &&
		    time_before(jiffies + ss->ss_mindwell, scanend)) {
			IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
				"%s: done, restart "
				"[jiffies %lu, dwell min %lu scanend %lu]\n",
				__func__,
				jiffies, ss->ss_mindwell, scanend);
			ss->ss_next = 0;	/* reset to beginning */
			if (ss->ss_flags & IEEE80211_SCAN_ACTIVE)
				vap->iv_stats.is_scan_active++;
			else
				vap->iv_stats.is_scan_passive++;

			ic->ic_scan_start(ic);	/* notify driver */
			goto again;
		} else {
			if ((ss->ss_flags & IEEE80211_SCAN_BGSCAN) == 0)
				scandone = 1;

			IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
				"%s: %s, "
				"[jiffies %lu, dwell min %lu scanend %lu]\n",
				__func__, scandone ? "done" : "stopped",
				jiffies, ss->ss_mindwell, scanend);

			/*
			 * Clear the SCAN bit first in case frames are
			 * pending on the station power save queue.  If
			 * we defer this then the dispatch of the frames
			 * may generate a request to cancel scanning.
			 */
			ic->ic_flags &= ~IEEE80211_F_SCAN;

			/*
			 * Drop out of power save mode when a scan has
			 * completed.  If this scan was prematurely terminated
			 * because it is a background scan then don't notify
			 * the ap; we'll either return to scanning after we
			 * receive the beacon frame or we'll drop out of power
			 * save mode because the beacon indicates we have frames
			 * waiting for us.
			 */
			if (scandone) {
				ieee80211_sta_pwrsave(vap, 0);
				if (ss->ss_next >= ss->ss_last) {
					ieee80211_notify_scan_done(vap);
					ic->ic_flags_ext &= ~IEEE80211_FEXT_BGSCAN;
				}
			}
			SCAN_PRIVATE(ss)->ss_iflags &= ~ISCAN_CANCEL;
			ss->ss_flags &=
			    ~(IEEE80211_SCAN_ONCE | IEEE80211_SCAN_PICK1ST);
		}
	}
#undef ISCAN_REP
}

#ifdef IEEE80211_DEBUG
static void
dump_probe_beacon(u_int8_t subtype, int isnew,
	const u_int8_t mac[IEEE80211_ADDR_LEN],
	const struct ieee80211_scanparams *sp)
{

	printk("[" MAC_FMT "] %s%s on chan %u (bss chan %u) ",
		MAC_ADDR(mac), isnew ? "new " : "",
		ieee80211_mgt_subtype_name[subtype >> IEEE80211_FC0_SUBTYPE_SHIFT],
		sp->chan, sp->bchan);
	ieee80211_print_essid(sp->ssid + 2, sp->ssid[1]);
	printk("\n");

	if (isnew) {
		printk("[" MAC_FMT "] caps 0x%x bintval %u erp 0x%x",
			MAC_ADDR(mac), sp->capinfo, sp->bintval, sp->erp);
		if (sp->country != NULL) {
#ifdef __FreeBSD__
			printk(" country info %*D",
				sp->country[1], sp->country + 2, " ");
#else
			int i;
			printk(" country info");
			for (i = 0; i < sp->country[1]; i++)
				printk(" %02x", sp->country[i + 2]);
#endif
		}
		printk("\n");
	}
}
#endif /* IEEE80211_DEBUG */

/*
 * Process a beacon or probe response frame.
 */
void
ieee80211_add_scan(struct ieee80211vap *vap,
	const struct ieee80211_scanparams *sp,
	const struct ieee80211_frame *wh,
	int subtype, int rssi, u_int64_t rtsf)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;

	/*
	 * Frames received during startup are discarded to avoid
	 * using scan state setup on the initial entry to the timer
	 * callback.  This can occur because the device may enable
	 * rx prior to our doing the initial channel change in the
	 * timer routine (we defer the channel change to the timer
	 * code to simplify locking on linux).
	 */
	if (SCAN_PRIVATE(ss)->ss_iflags & ISCAN_DISCARD)
		return;
#ifdef IEEE80211_DEBUG
	if (ieee80211_msg_scan(vap) && (ic->ic_flags & IEEE80211_F_SCAN))
		dump_probe_beacon(subtype, 1, wh->i_addr2, sp);
#endif
	if (ss->ss_ops != NULL &&
	    ss->ss_ops->scan_add(ss, sp, wh, subtype, rssi, rtsf)) {
		/*
		 * If we've reached the min dwell time terminate
		 * the timer so we'll switch to the next channel.
		 */
		if ((SCAN_PRIVATE(ss)->ss_iflags & ISCAN_MINDWELL) == 0 &&
		    time_after_eq(jiffies, SCAN_PRIVATE(ss)->ss_chanmindwell)) {
			IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN,
				"%s: chan %3d%c min dwell met (%lu > %lu)\n",
				__func__,
				ieee80211_chan2ieee(ic, ic->ic_curchan),
					channel_type(ic->ic_curchan),
				jiffies, SCAN_PRIVATE(ss)->ss_chanmindwell);
			/*
			 * XXX
			 * We want to just kick the timer and still
			 * process frames until it fires but linux
			 * will livelock unless we discard frames.
			 */
#if 0
			SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_MINDWELL;
#else
			SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_DISCARD;
#endif
			/* NB: trigger at next clock tick */
			mod_timer(&SCAN_PRIVATE(ss)->ss_scan_timer, jiffies);
		}
	}
}

/*
 * Timeout/age scan cache entries; called from sta timeout
 * timer (XXX should be self-contained).
 */
void
ieee80211_scan_timeout(struct ieee80211com *ic)
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss->ss_ops != NULL)
		ss->ss_ops->scan_age(ss);
}

/*
 * Mark a scan cache entry after a successful associate.
 */
void
ieee80211_scan_assoc_success(struct ieee80211com *ic, const u_int8_t mac[])
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss->ss_ops != NULL) {
		IEEE80211_NOTE_MAC(ss->ss_vap, IEEE80211_MSG_SCAN,
			mac, "%s",  __func__);
		ss->ss_ops->scan_assoc_success(ss, mac);
	}
}

/*
 * Demerit a scan cache entry after failing to associate.
 */
void
ieee80211_scan_assoc_fail(struct ieee80211com *ic,
	const u_int8_t mac[], int reason)
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss->ss_ops != NULL) {
		IEEE80211_NOTE_MAC(ss->ss_vap, IEEE80211_MSG_SCAN, mac,
			"%s: reason %u", __func__, reason);
		ss->ss_ops->scan_assoc_fail(ss, mac, reason);
	}
}

/*
 * Iterate over the contents of the scan cache.
 */
int
ieee80211_scan_iterate(struct ieee80211com *ic,
	ieee80211_scan_iter_func *f, void *arg)
{
  int res = 0;
  struct ieee80211_scan_state *ss = ic->ic_scan;

  if (ss->ss_ops != NULL) {
	res = ss->ss_ops->scan_iterate(ss, f, arg);
  }
  return res;
}

/*
 * Flush the contents of the scan cache.
 */
void
ieee80211_scan_flush(struct ieee80211com *ic)
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss->ss_ops != NULL) {
		IEEE80211_DPRINTF(ss->ss_vap, IEEE80211_MSG_SCAN,
			"%s\n",  __func__);
		ss->ss_ops->scan_flush(ss);
	}
}

/* Check if a channel is usable for a DFS channel switch */
static int
ieee80211_dfs_is_channel_usable(struct ieee80211com *ic,
				struct ieee80211_channel *channel)
{
	u_int16_t curChanBandFlags, curChanOutdoorFlags;

	/*
	 * Criteria for the new frequency:
	 * - it must be different from the current frequency
	 * - it must not have radar detected
	 * - it must be an active channel
	 * - it must be in the same band (2.4Ghz/5Ghz)
	 * - it must be suitable for indoor/outdoor use according to what the
	 *   user selected
	 */

	curChanBandFlags = ic->ic_bsschan->ic_flags &
		(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_5GHZ);
	curChanOutdoorFlags = ic->ic_country_outdoor ?
		IEEE80211_CHAN_OUTDOOR : IEEE80211_CHAN_INDOOR;

	return ((channel->ic_freq != ic->ic_bsschan->ic_freq) &&
		(!IEEE80211_IS_CHAN_RADAR(channel) &&
		 (ic->ic_flags & IEEE80211_F_DOTH)) &&
		(isset(ic->ic_chan_active, channel->ic_ieee)) &&
		(channel->ic_flags & curChanBandFlags) &&
		(channel->ic_flags & curChanOutdoorFlags));
}

/*
 * Execute radar channel change. This is called when a radar signal is
 * detected. AP/IBSS mode only. Return 1 on success, 0 on failure
 */
void
ieee80211_scan_dfs_action(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_channel *new_channel = NULL;
	int chanStart, i, count;

	if (!IEEE80211_IS_MODE_DFS_MASTER(vap->iv_opmode)) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
				  "%s: called but not in DFS master mode\n",
				  __func__);
		return;
	}

	/* Do nothing if a channel switch is already in progress */
	if (ic->ic_flags & IEEE80211_F_CHANSWITCH) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
				  "%s: channel switch already in progress\n",
				  __func__);
		return;
	}

	if ((ic->ic_curchan != NULL) &&
	    (ic->ic_curchan != IEEE80211_CHAN_ANYC)) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
				  "%s: ic_curchan is %3d (%4d MHz)\n",
				  __func__, ic->ic_curchan->ic_ieee,
				  ic->ic_curchan->ic_freq);
	}

	if ((ic->ic_bsschan != NULL) &&
	    (ic->ic_bsschan != IEEE80211_CHAN_ANYC)) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
				  "%s: ic_bsschan is %3d (%4d MHz)\n",
				  __func__, ic->ic_bsschan->ic_ieee,
				  ic->ic_bsschan->ic_freq);
	}

	/* According to FCC/ETSI rules on uniform spreading, we shall select a
	 * channel out of the list of usable channels so that the probability
	 * of selecting a given channel shall be the same for all channels
	 * (reference: ETSI 301 893 v1.3.1 $4.6.2.5.1 */
	/* First, we count the usable channels */
	count = 0;

	for (i = 0; i < ic->ic_nchans; i++) {
		if (ieee80211_dfs_is_channel_usable(
			    ic, &ic->ic_channels[i])) {
			IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
					  "%s: usable channel %3d "
					  "(%4d MHz)\n",
					  __func__,
					  ic->ic_channels[i].ic_ieee,
					  ic->ic_channels[i].ic_freq);
			count ++;
		}
	}

	if (count != 0) {
		/* Next, we pickup a random usable channel */
		chanStart = jiffies % count;

		count = 0;
		for (i = 0; i < ic->ic_nchans; i++) {
			/* must be the same formula as above */
			if (ieee80211_dfs_is_channel_usable(
				    ic, &ic->ic_channels[i])) {
				if (count++ == chanStart) {
					new_channel =
						&ic->ic_channels[i];
					break;
				}
			}
		}
	}

	if (new_channel == NULL) {
		/* We found no channel to switch to (for instance, all
		 * available channels are under Non-Occupancy Period). In this
		 * case, we still need to send an action frame and beacon with
		 * CSA IE to tell other nodes to stop their transmission, in
		 * order to meet the Channel Closing Transmission Time
		 * requirement of FCC/ETSI */

		if ((ic->ic_bsschan != NULL) &&
		    (ic->ic_bsschan != IEEE80211_CHAN_ANYC)) {
			new_channel = ic->ic_bsschan;
		}
	}

	if (new_channel != NULL) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
				  "%s: new channel found %3d "
				  "(%4d MHz)\n", __func__,
				  new_channel->ic_ieee,
				  new_channel->ic_freq);

		/* send a CSA frame immediately */
		ieee80211_send_csa_frame(vap,
					 IEEE80211_CSA_MUST_STOP_TX,
					 new_channel->ic_ieee,
					 IEEE80211_RADAR_CHANCHANGE_TBTT_COUNT);

		/* A suitable scan entry was found, so change channels */
		if (vap->iv_state == IEEE80211_S_RUN) {
			IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
			  "%s: CSA switching to channel %3d (%4d MHz)\n",
					  __func__,
					  new_channel->ic_ieee,
					  new_channel->ic_freq);

			ieee80211_start_new_csa(vap,
				IEEE80211_CSA_MUST_STOP_TX, new_channel,
				IEEE80211_RADAR_CHANCHANGE_TBTT_COUNT, 0);
		} else {

			IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
					"%s: directly switching to channel "
					"%3d (%4d MHz)\n", __func__,
					new_channel->ic_ieee,
					new_channel->ic_freq);

			/* VAP is not in run state yet. so
			 * change the channel here. */
			change_channel(ic, new_channel);
			ic->ic_bsschan = new_channel;
			if (vap->iv_bss)
				vap->iv_bss->ni_chan = new_channel;
		}
	} else {
		/* A suitable scan entry was not found */
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_DOTH,
				  "%s: new channel not found\n", __func__);
	}
}
EXPORT_SYMBOL(ieee80211_scan_dfs_action);
