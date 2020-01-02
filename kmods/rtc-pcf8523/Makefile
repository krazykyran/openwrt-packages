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

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
	SUBMENU:=Other modules
	TITLE:=NXP PCF8523 RTC support
	DEFAULT:=m if ALL_KMODS && RTC_SUPPORT
	DEPENDS:=+kmod-i2c-core
	KCONFIG:=CONFIG_RTC_DRV_PCF8523 \
		CONFIG_RTC_CLASS=y
	FILES:=$(LINUX_DIR)/drivers/rtc/rtc-pcf8523.ko
	AUTOLOAD:=$(call AutoProbe,rtc-pcf8523)
endef

define KernelPackage/$(PKG_NAME)/description
	Kernel module for NXP PCF8523 Real-Time Clock (RTC) 
	and calendar device.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Configure
endef

define Build/Compile
endef

$(eval $(call KernelPackage,$(PKG_NAME)))