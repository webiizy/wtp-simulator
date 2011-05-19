#
# Copyright (C) 2010 Ubiquiti Networks, Inc.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=hiwifi-base-files
PKG_RELEASE:=1

#PKG_FILE_DEPEND:=$(PLATFORM_DIR)/ $(GENERIC_PLATFORM_DIR)/hiwifi-base-files/

include $(INCLUDE_DIR)/package.mk

SVN_REV:=$(shell svn info $(TOPDIR)/.. | grep "^Last Changed Rev:" | awk '{print $$4}')
ifeq ($(SVN_REV),)
	SVN_REV:=5090
endif
FULL_VERSION:=HiWiFi-rspro-$(BUILD_TIME)
DSTAMP:=$(shell date +%m%d%H%M%Y)

CONFIG_PACKAGE_hiwifi-base-files$(TARGET):=$(CONFIG_PACKAGE_hiwifi-base-files)

define Package/hiwifi-base-files$(TARGET)
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=Base filesystem for OpenWrt (HiWiFi flavour)
  URL:=http://www.HiWiFi.net/
  VERSION:=$(PKG_RELEASE)-$(REV)
endef

define Package/hiwifi-base-files$(TARGET)/conffiles
$(call $(TARGET)/conffiles)
endef

define Package/hiwifi-base-files$(TARGET)/description
 This package contains a base filesystem and system scripts for OpenWrt (HiWiFi flavour).
endef

define Package/hiwifi-base-files/config
	source $(SOURCE)/config.in
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default
endef

define Build/Compile
	export FULL_VERSION=$(FULL_VERSION)
	$(call Build/Compile/Default)
endef

define Package/hiwifi-base-files$(TARGET)/install
	$(CP) ./files/* $(1)/
	if [ -d $(GENERIC_PLATFORM_DIR)/hiwifi-base-files/. ]; then \
		$(CP) $(GENERIC_PLATFORM_DIR)/hiwifi-base-files/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/hiwifi-base-files/default/. ]; then \
		$(CP) $(PLATFORM_DIR)/hiwifi-base-files/default/* $(1)/; \
	fi
	if [ "$(PROFILE)" != "Default" ]; then \
		if [ -d files-$(PROFILE)/. ]; then \
			$(CP) files-$(PROFILE)/* $(1)/; \
		fi; \
	fi
#	mkdir -p $(1)/HiWiFi
#	echo $(FULL_VERSION) > $(1)/HiWiFi/version
endef

ifneq ($(DUMP),1)
  -include $(PLATFORM_DIR)/hiwifi-base-files.mk
endif

$(eval $(call BuildPackage,hiwifi-base-files$(TARGET)))
