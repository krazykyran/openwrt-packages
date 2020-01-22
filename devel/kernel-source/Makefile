#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=kernel-source-$(LINUX_VERSION)
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)/description
	Installs the kernel source files into 
	/lib/modules/<kernel-version>/build
endef

define Package/$(PKG_NAME)
  SECTION:=devel
  CATEGORY:=Development
  TITLE:=$(PKG_NAME)
  MAINTAINER:=Simon Crawley <simon.crawley@gotosage.com>
  DEPENDS:=+libncurses-dev +make +gcc +pkg-config +ldconfig
endef

define Build/Compile
	
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib/modules/$(LINUX_VERSION)/build
	$(INSTALL_DATA) $(LINUX_DIR)/* $(1)/lib/modules/$(LINUX_VERSION)/build
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
