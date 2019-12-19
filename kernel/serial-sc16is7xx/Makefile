#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=serial-sc16is7xx
PKG_RELEASE:=1
PKG_BUILD_DIR=$(LINUX_DIR)/drivers/tty/serial

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
	SUBMENU:=Other modules
	DEPENDS:=+kmod-i2c-core +kmod-regmap
	TITLE:=NXP SC16IS7xx serial UART bridge SPI/I2C
	FILES:=$(PKG_BUILD_DIR)/sc16is7xx.ko \
	$(PKG_BUILD_DIR)/serial_core.ko
	AUTOLOAD:=$(call AutoProbe,sc16is7xx)
endef

define KernelPackage/$(PKG_NAME)/description
	Kernel module for NXP SC16IS740/SC16IS750/SC16IS752,
	serial UART chips connected via I2C or SPI.
endef

MAKE_OPTS:= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	M="$(PKG_BUILD_DIR)"
	
define Build/Prepare
	$(CP) ./files/sc16is7xx.c $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		CONFIG_SERIAL_SC16IS7XX=m \
		CONFIG_SERIAL_SC16IS7XX_CORE=y \
		CONFIG_SERIAL_SC16IS7XX_I2C=y \
		CONFIG_SERIAL_SC16IS7XX_SPI=y
		modules
endef

$(eval $(call KernelPackage,$(PKG_NAME)))