#
# Copyright (C) 2007-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_BASENAME:=util-linux
PKG_VERSION:=2.29.2
PKG_RELEASE:=1
PKG_NAME:=$(PKG_BASENAME)-$(PKG_VERSION)

PKG_SOURCE:=$(PKG_BASENAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@KERNEL/linux/utils/$(PKG_BASENAME)/v2.29
PKG_HASH:=accea4d678209f97f634f40a93b7e9fcad5915d1f4749f6c47bee6bf110fe8e3

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=	COPYING					\
			getopt/COPYING				\
			libblkid/COPYING			\
			libmount/COPYING			\
			Documentation/licenses/COPYING.GPLv2	\
			Documentation/licenses/COPYING.LGPLv2.1	\
			libuuid/COPYING				\
			Documentation/licenses/COPYING.BSD-3

PKG_BUILD_PARALLEL:=1

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)/Default
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:= +librt
  URL:=http://www.kernel.org/pub/linux/utils/util-linux/
endef

define Package/hwclock-$(PKG_VERSION)
$(call Package/$(PKG_NAME)/Default)
  TITLE:=query or set the hardware clock
endef

define Package/hwclock-$(PKG_VERSION)/description
 hwclock is a tool for accessing the Hardware Clock
endef

CONFIGURE_ARGS += \
	--disable-use-tty-group \
	--disable-rpath \
	--disable-tls		\
	--disable-sulogin	\
	--without-python	\
	--without-udev		\
	--without-readline	\
	--disable-more		\
	--with-ncursesw

TARGET_CFLAGS += $(FPIC) -std=gnu99

define Package/hwclock/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/hwclock $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,hwclock-$(PKG_VERSION)))