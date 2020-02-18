#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rtc-pcf8523
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
	SUBMENU:=Other modules
	TITLE:=NXP PCF8523 RTC support
	DEPENDS:=+kmod-i2c-core
	FILES:=$(PKG_BUILD_DIR)/rtc-pcf8523.ko
	KCONFIG:= \
		CONFIG_RTC_CLASS=y
	AUTOLOAD:=$(call AutoProbe,rtc-pcf8523)
endef

define KernelPackage/$(PKG_NAME)/description
	Kernel module for NXP PCF8523 Real-Time Clock (RTC) 
	and calendar device.
endef

EXTRA_KCONFIG:= \
	CONFIG_RTC_PCF8523=m \
	CONFIG_RTC_CLASS=y \
	CONFIG_RTC_INTF_DEV=y
	
EXTRA_CFLAGS:= \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=m,%,$(filter %=m,$(EXTRA_KCONFIG)))) \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=y,%,$(filter %=y,$(EXTRA_KCONFIG))))

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		$(EXTRA_KCONFIG) \
		modules
endef

$(eval $(call KernelPackage,$(PKG_NAME)))