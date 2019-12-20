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
	DEPENDS:=+kmod-mac80211 +rs9113-firmware
	TITLE:=Redpine Signals Inc 91x WLAN driver support
	FILES:=$(PKG_BUILD_DIR)/drivers/net/wireless/rsi/rsi_91x.ko
	KCONFIG:=CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_91X=y
endef

define KernelPackage/rsi91x-usb
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-usb2 +kmod-rsi91x +rs9113-firmware
	TITLE:=Redpine Signals USB bus support
	FILES:=$(PKG_BUILD_DIR)/drivers/net/wireless/rsi/rsi_usb.ko
	KCONFIG:=CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_USB=y
	AUTOLOAD:=$(call AutoProbe,rsi_usb)
endef

define KernelPackage/rsi91x-sdio
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-mmc +kmod-rsi91x +rs9113-firmware 
	TITLE:=Redpine Signals SDIO bus support
	FILES:=$(PKG_BUILD_DIR)/drivers/net/wireless/rsi/rsi_sdio.ko
	KCONFIG:=CONFIG_WLAN_VENDOR_RSI=y \
		CONFIG_RSI_SDIO=y
	AUTOLOAD:=$(call AutoProbe,rsi_sdio)
endef

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)/drivers/net/wireless/rsi/
	$(CP) ./files/* $(PKG_BUILD_DIR)/drivers/net/wireless/rsi/
endef

define Build/Configure
endef

$(eval $(call KernelPackage,rsi91x))
$(eval $(call KernelPackage,rsi91x-usb))
$(eval $(call KernelPackage,rsi91x-sdio))
