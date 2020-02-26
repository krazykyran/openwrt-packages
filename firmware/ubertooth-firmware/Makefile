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

define Package/ubertooth-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Project Ubertooth firmware
endef

define Build/Compile

endef

define Package/ubertooth-firmware/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_DIR) $(1)/lib/firmware
	$(INSTALL_DIR) $(1)/lib/firmware/ubertooth
	$(INSTALL_DATA) ./files/lib/firmware/ubertooth/* $(1)/lib/firmware/ubertooth
endef

$(eval $(call BuildPackage,ubertooth-firmware))
