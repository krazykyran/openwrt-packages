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

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
	SUBMENU:=Other modules
	DEPENDS:=+kmod-regmap
	TITLE:=NXP SC16IS7xx serial UART bridge SPI/I2C
	FILES:=$(PKG_BUILD_DIR)/sc16is7xx.ko
	AUTOLOAD:=$(call AutoProbe,sc16is7xx)
endef

define KernelPackage/$(PKG_NAME)/description
	Kernel module for NXP SC16IS740/SC16IS750/SC16IS752,
	serial UART chips connected via I2C or SPI.
endef

EXTRA_KCONFIG:= \
	CONFIG_SERIAL_SC16IS7XX=m \
	CONFIG_SERIAL_SC16IS7XX_CORE=m \
	CONFIG_SERIAL_SC16IS7XX_I2C=n \
	CONFIG_SERIAL_SC16IS7XX_SPI=y
	
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
