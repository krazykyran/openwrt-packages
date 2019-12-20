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

define Package/$(PKG_NAME)
    TITLE:=$(PKG_NAME)
    SECTION:=libs
    DEPENDS:=+libpthread +zlib +librt +libopenssl
    CATEGORY:=Libraries
    URL:=https://github.com/edenhill/librdkafka
endef

define Package/$(PKG_NAME)/description
	Apache Kafka C library
endef

TARGET_CONFIGURE_OPTS = \
  AR=$(TARGET_CROSS)ar \
  AS="$(TARGET_CC) -c $(TARGET_CFLAGS)" \
  LD=$(TARGET_CROSS)gcc \
  NM=$(TARGET_CROSS)nm \
  CC="$(TARGET_CC)" \
  GCC="$(TARGET_CC)" \
  CXX="$(TARGET_CXX)" \
  RANLIB=$(TARGET_CROSS)ranlib \
  STRIP=$(TARGET_CROSS)strip \
  OBJCOPY=$(TARGET_CROSS)objcopy \
  OBJDUMP=$(TARGET_CROSS)objdump \
  SIZE=$(TARGET_CROSS)size \
  PREFIX=$(PKG_INSTALL_DIR)/usr

define Build/Configure
        (cd $(PKG_BUILD_DIR); ./configure);
endef

define Package/$(PKG_NAME)/prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/usr/include
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/usr/lib
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))