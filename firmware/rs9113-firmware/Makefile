#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rs9113-firmware
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=RedPine Signals rs9113 firmware
endef

define Build/Compile

endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib/firmware/rsi
	$(INSTALL_DATA) ./files/*.rps $(1)/lib/firmware/rsi
endef
$(eval $(call BuildPackage,rs9113-firmware))
