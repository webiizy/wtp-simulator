#
# Copyright (C) 2010 HiWiFi Networks, Inc.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hiwifi-web
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/ipkg-install

FULL_VERSION:=$(BUILD_TIME)

include $(INCLUDE_DIR)/package.mk

define Package/hiwifi-web
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+hiwifi-base-files +lighttpd +php5 +wireless-tools @BUSYBOX_CONFIG_TRACEROUTE
  TITLE:=HiWiFi WEBGUI system.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/prepare
	tar -C files/ --exclude .svn -cf - . | tar -C $(PKG_BUILD_DIR)/prepare -xvf -
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/hiwifi-web/install
	$(INSTALL_DIR) $(1)/www
	$(CP) -a $(PKG_BUILD_DIR)/prepare/* $(1)/
endef

$(eval $(call BuildPackage,hiwifi-web))
