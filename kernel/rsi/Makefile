#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rsi
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/rsi91x
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-bluetooth +rs9113-firmware
	TITLE:=Redpine Signals Inc 91x WLAN driver support
	FILES:=$(PKG_BUILD_DIR)/rsi_91x.ko
endef

define KernelPackage/rsi91x-usb
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-usb2 +kmod-rsi91x +kmod-bluetooth +rs9113-firmware
	TITLE:=Redpine Signals USB bus support
	FILES:=$(PKG_BUILD_DIR)/rsi_usb.ko
	AUTOLOAD:=$(call AutoProbe,rsi_usb)
endef

define KernelPackage/rsi91x-sdio
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-mmc +kmod-rsi91x +kmod-bluetooth +rs9113-firmware
	TITLE:=Redpine Signals SDIO bus support
	FILES:=$(PKG_BUILD_DIR)/rsi_sdio.ko
	AUTOLOAD:=$(call AutoProbe,rsi_sdio)
endef

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

MAKE_OPTS:= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	SUBDIRS="$(PKG_BUILD_DIR)"

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_DEBUGFS=y \
		CONFIG_RSI_COEX=y \
		CONFIG_HW_SCAN_OFFLOAD=y \
		CONFIG_RSI_91X=m \
		CONFIG_RSI_SDIO=m \
		CONFIG_RSI_USB=m \
		modules
endef

$(eval $(call KernelPackage,rsi91x))
$(eval $(call KernelPackage,rsi91x-usb))
$(eval $(call KernelPackage,rsi91x-sdio))
