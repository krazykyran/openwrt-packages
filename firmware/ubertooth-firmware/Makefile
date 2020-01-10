#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ubertooth-firmware
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Project Ubertooth firmware
endef

define Build/Compile

endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib/firmware/ubertooth
	$(INSTALL_DATA) ./files/*.bin $(1)/lib/firmware/ubertooth
	$(INSTALL_DATA) ./files/*.dfu $(1)/lib/firmware/ubertooth
	$(INSTALL_DATA) ./files/*.hex $(1)/lib/firmware/ubertooth
endef
$(eval $(call BuildPackage,$(PKG_NAME)))
