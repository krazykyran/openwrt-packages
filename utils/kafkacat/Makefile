#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=kafkacat
PKG_VERSION:=1.3.1

PKG_SOURCE:=$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/edenhill/kafkacat/archive
PKG_SOURCE_VERSION:=1.3.1
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_HASH:=a1acc822efd9aebc460f0f7e7db2bb767591e770e3b15b1c3cd5f9732f066cb6
PKG_BUILD_DEPENDS:=librdkafka
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Package/kafkacat
    TITLE:=kafkacat
    SECTION:=utils
    DEPENDS:=+libc +librdkafka
    CATEGORY:=Utilities
    URL:=https://github.com/edenhill/kafkacat
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		$(TARGET_CONFIGURE_OPTS) \
		./configure \
			--arch="$(ARCH)" \
	)
endef

define Package/kafkacat/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/kafkacat $(1)/usr/bin
endef

$(eval $(call BuildPackage,kafkacat))
