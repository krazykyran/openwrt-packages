#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=kernel-source
PKG_VERSION:=$(LINUX_VERSION)
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)/description
	Installs the kernel source files into the image
endef

define Package/$(PKG_NAME)
  SECTION:=devel
  CATEGORY:=Development
  TITLE:=$(PKG_NAME)
  DEPENDS:=+libncurses-dev +make +gcc +pkg-config +ldconfig +bc
endef

define Build/Compile
	
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib/modules/$(LINUX_VERSION)/build
	$(INSTALL_DATA) $(LINUX_DIR)/* $(1)/lib/modules/$(LINUX_VERSION)/build
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
