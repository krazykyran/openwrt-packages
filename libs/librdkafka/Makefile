#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=librdkafka
PKG_VERSION:=0.11.3

PKG_SOURCE:=v$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/edenhill/librdkafka/archive
PKG_SOURCE_VERSION:=0.11.3
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_MD5SUM:=965ce8db67565e983d8f2bd5ce7bba21
PKG_INSTALL:=1
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Package/librdkafka
    TITLE:=librdkafka
    SECTION:=libs
    DEPENDS:=+libstdcpp +libpthread +zlib +librt +libopenssl
    CATEGORY:=Libraries
    URL:=https://github.com/edenhill/librdkafka
endef

define Package/librdkafka/description
	Apache Kafka C library
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		./configure \
			--arch="$(ARCH)" \
      --cc="$(TARGET_CC)" \
			--cxx="$(TARGET_CXX)" \
			--disable-ssl \
			--disable-sasl \
	)
endef

define Package/librdkafka/prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/usr/include
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/usr/lib
endef

define Package/librdkafka/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/*.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/include/librdkafka
	$(CP) $(PKG_INSTALL_DIR)/usr/local/include/librdkafka/*.h $(1)/usr/include/librdkafka/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig/
endef

$(eval $(call BuildPackage,librdkafka))
