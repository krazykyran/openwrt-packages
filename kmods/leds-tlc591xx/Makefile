#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=leds-tlc591xx
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
	SUBMENU:=LED modules
	DEPENDS:=+kmod-i2c-core +kmod-regmap
	TITLE:=TLC591xx LED support
	KCONFIG:=CONFIG_LEDS_TLC591XX
	FILES:=$(LINUX_DIR)/drivers/leds/leds-tlc591xx.ko
	AUTOLOAD:=$(call AutoLoad,60,leds-tlc591xx,1)
endef

define KernelPackage/$(PKG_NAME)/description
	Driver for the TI TLC59108 and TLC59116 I2C LED controllers.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Configure
endef

define Build/Compile
endef

$(eval $(call KernelPackage,$(PKG_NAME)))