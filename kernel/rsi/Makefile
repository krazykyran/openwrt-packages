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
	TITLE:=Redpine Signals Inc 91x WLAN driver support
	KCONFIG:=CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_91X=y
		CONFIG_RSI_DEBUGFS=y \
		CONFIG_RSI_BT_ALONE=n \
		CONFIG_RSI_COEX=y \
		CONFIG_RSI_WOW=n \
		CONFIG_RSI_P2P=n \
		CONFIG_HW_SCAN_OFFLOAD=n \
		CONFIG_CARACALLA_BOARD=n \
		CONFIG_RSI_ZIGB=n
	DEPENDS:=+kmod-mac80211 +rs9113-firmware
	FILES:=$(LINUX_DIR)/drivers/net/wireless/rsi/rsi_91x.ko
endef

define KernelPackage/rsi91x-sdio
	SUBMENU:=Wireless Drivers
	TITLE:=Redpine Signals SDIO bus support
	KCONFIG:=CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_SDIO=y
	DEPENDS:=+kmod-mac80211 +kmod-rsi91x +rs9113-firmware 
	FILES:=$(LINUX_DIR)/drivers/net/wireless/rsi/rsi_sdio.ko
endef

define KernelPackage/rsi91x-usb
	SUBMENU:=Wireless Drivers
	TITLE:=Redpine Signals USB bus support
	KCONFIG:=CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_USB=y
	DEPENDS:=+kmod-mac80211 +kmod-usb2 +kmod-rsi91x +rs9113-firmware
	FILES:=$(LINUX_DIR)/drivers/net/wireless/rsi/rsi_usb.ko
endef

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	rm -rf $(LINUX_DIR)/drivers/net/wireless/rsi/*
	$(CP) ./files/* $(LINUX_DIR)/drivers/net/wireless/rsi
endef

define Build/Configure
endef

define Build/Compile
endef

$(eval $(call KernelPackage,rsi91x))
$(eval $(call KernelPackage,rsi91x-usb))
$(eval $(call KernelPackage,rsi91x-sdio))
