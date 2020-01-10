#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=cc2564-firmware
PKG_VERSION:=6.7
PKG_RELEASE:=16

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Texas Instruments cc2564 firmware
endef

define Build/Compile

endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib/firmware/ti-connectivity
	$(INSTALL_DATA) ./files/*.bts $(1)/lib/firmware/ti-connectivity
endef
$(eval $(call BuildPackage,$(PKG_NAME)))
