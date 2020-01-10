#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rsi-edge
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/rsi91x-edge
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-bluetooth +rs9113-firmware-edge
	TITLE:=Redpine Signals Inc 91x WLAN driver support (for SAGE EDGE)
	FILES:=$(PKG_BUILD_DIR)/rsi_91x.ko
endef

define KernelPackage/rsi91x-usb-edge
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-usb2 +kmod-rsi91x-edge +kmod-bluetooth +rs9113-firmware-edge
	TITLE:=Redpine Signals USB bus support (for SAGE EDGE)
	FILES:=$(PKG_BUILD_DIR)/rsi_usb.ko
	AUTOLOAD:=$(call AutoProbe,rsi_usb)
endef

define KernelPackage/rsi91x-sdio-edge
	SUBMENU:=Wireless Drivers
	DEPENDS:=+kmod-mac80211 +kmod-mmc +kmod-rsi91x-edge +kmod-bluetooth +rs9113-firmware-edge
	TITLE:=Redpine Signals SDIO bus support (for SAGE EDGE)
	FILES:=$(PKG_BUILD_DIR)/rsi_sdio.ko
	AUTOLOAD:=$(call AutoProbe,rsi_sdio)
endef

EXTRA_KCONFIG:= \
	CONFIG_RSI_91X=m \
	CONFIG_RSI_USB=m \
	CONFIG_RSI_SDIO=m \
	CONFIG_RSI_DEBUGFS=y \
	CONFIG_RSI_COEX=y \
	CONFIG_RSI_MULTI_MODE=y \
	CONFIG_HW_SCAN_OFFLOAD=y

EXTRA_CFLAGS:= \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=m,%,$(filter %=m,$(EXTRA_KCONFIG)))) \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=y,%,$(filter %=y,$(EXTRA_KCONFIG))))

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
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

$(eval $(call KernelPackage,rsi91x-edge))
$(eval $(call KernelPackage,rsi91x-usb-edge))
$(eval $(call KernelPackage,rsi91x-sdio-edge))
